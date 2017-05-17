//
// Created by wengxiang on 2017/1/28.
//

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFile>
#include <iostream>
#include <QDir>
#include <QVector>
#include <QFileInfo>
#include <QDebug>
#include "cli_args.h"

using namespace args;
using std::cout;
using std::cerr;

QDir args::input_directory;
QDir args::output_directory;
QDir args::resource_directory;
QVector<QFileInfo> args::exclude_files;
bool args::force;

void args::ParseCommandLine(const QCoreApplication &application)
{
    QCommandLineOption input_option(
            QStringList() << "d" << "input",
            "The root directory of input files",
            "input directory"
    );
    QCommandLineOption output_option(
            QStringList() << "o" << "output",
            "The root directory of export atlas.",
            "output directory"
    );
    QCommandLineOption resource_option(
            QStringList() << "r" << "resource",
            "Thr root directory of resources cannot be packed.",
            "resource directory"
    );
    QCommandLineOption exclude_option(
            QStringList() << "x" << "exclude",
            "The picture in exclude list will not packed. Picture pass by full path and split by ','.",
            "exclude directory"
    );

    QCommandLineOption force_option(
            QStringList() << "f" << "force",
            "If true, then publish even if picture never be modified.");

    QCommandLineParser command_line_parser;
    command_line_parser.addOption(input_option);
    command_line_parser.addOption(output_option);
    command_line_parser.addOption(resource_option);
    command_line_parser.addOption(exclude_option);
    command_line_parser.addOption(force_option);
    command_line_parser.addHelpOption();
    command_line_parser.addVersionOption();

    command_line_parser.process(application);

//    cout << command_line_parser.helpText().toStdString();

    if (command_line_parser.isSet("input"))
    {
        input_directory = QDir(command_line_parser.value(input_option));

        if (input_directory.exists())
        {
            cout << qPrintable(QString("%1 : %2\n")
                                       .arg("input directory", 20)
                                       .arg(input_directory.path()));

            SetupOutputDirectory(command_line_parser.isSet(output_option), command_line_parser.value(output_option));
            SetupResourceDirectory(command_line_parser.isSet(resource_option),command_line_parser.value(resource_option));
            SetupExcludeDirectory(command_line_parser.isSet(exclude_option),command_line_parser.value(exclude_option));

            force = command_line_parser.isSet(force_option);

            cout << '\n';
        } else
        {
            cerr << qPrintable(QString("%1 not found.").arg(input_directory.path()));
        }
    } else
    {
        application.exit(EXIT_FAILURE);
    }
}

void args::SetupOutputDirectory(bool is_set, const QString &value)
{
    if (is_set)
    {
        output_directory = QDir(value);
    } else
    {
        output_directory = input_directory;
        output_directory.cdUp();
        QString default_output("default_output");
        output_directory.mkdir(default_output);
        output_directory.cd(default_output);
    }

    cout << qPrintable(QString("%1 : %2\n")
                               .arg("output directory", 20)
                               .arg(output_directory.path()));
}


void args::SetupResourceDirectory(bool is_set, const QString &value)
{
    if (is_set)
    {
        resource_directory = QDir(value);
    } else
    {
        resource_directory = input_directory;
        resource_directory.cdUp();
        QString default_output("default_resource");
        resource_directory.mkdir(default_output);
        resource_directory.cd(default_output);
    }

    cout << qPrintable(QString("%1 : %2\n")
                               .arg("resource directory", 20)
                               .arg(resource_directory.path()));
}

void ::args::SetupExcludeDirectory(bool is_set, const QString &value)
{
    if(!is_set) return;

    cout << '\n';

    QStringList exclude_files_in_string = value.split(',');
    for (int i = 0; i < exclude_files_in_string.size(); ++i)
    {
        QString file_path(exclude_files_in_string.at(i));
        QFileInfo file_info(file_path);
        exclude_files.push_back(file_info);

        cout << qPrintable(QString("exclude %1\n")
                                   .arg(file_path));
    }
}

bool ::args::isExclude(const QFileInfo &file)
{
    return exclude_files.contains(file);
}
