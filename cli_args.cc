//
// Created by wengxiang on 2017/1/28.
//

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFile>
#include <iostream>
#include <cassert>

#include <QVector>
#include <QFileInfo>
#include <QDebug>
#include <iomanip>
#include "cli_args.h"

using std::cout;
using std::cerr;

QDir Args::input;
QDir Args::input_directory;
QDir Args::output_directory;
QDir Args::resource_directory;

int Args::max_size, Args::tile_size;
int Args::shape_padding;
QString Args::textureFormat;

QVector<QFileInfo> Args::exclude_files;

int Args::extrude;
bool Args::crop_alpha;
bool Args::force;
bool Args::power_of_two;

void Args::ParseCommandLine(const QCoreApplication &application)
{
    QCommandLineOption output_option(
            QStringList() << "o" << "output",
            "The directory for exporting atlas.",
            "output directory"
    );
    QCommandLineOption resource_option(
            QStringList() << "r" << "resource",
            "Thr directory of files cannot be packed.",
            "resource directory"
    );
    QCommandLineOption max_size_option(
            QStringList() << "S" << "maxSize",
            "Max size of atlas.",
            "max atlas size",
            "2048"
    );
    QCommandLineOption tile_size_option(
            QStringList() << "s" << "tileSize",
            "Max size of tile.",
            "max tile size",
            "512"
    );
    QCommandLineOption extrude_option(
            QStringList() << "e" << "extrude",
            "Repeat the sprite's pixels at the borders.",
            "vvvvname",
            "0"
    );
    QCommandLineOption include_images_option(
            QStringList() << "includeImages",
            "The picture in include list have to packed anyway, split by ','"
    );
    QCommandLineOption exclude_images_option(
            QStringList() << "x" << "exclude",
            "The picture in exclude list will not packed, split by ','.",
            "exclude directory"
    );
    QCommandLineOption tile_padding_option(
            QStringList() << "p" << "tilePadding",
            "Tile padding is the space between sprites. Value adds transparent pixels between sprites to avoid artifacts from neighbor sprites. The transparent pixels are not added to the sprites. Default is 2.",
            "padding",
            "2"
    );
    QCommandLineOption force_option(
            QStringList() << "f" << "force",
            "If true, then publish even if picture never be modified.");
    QCommandLineOption power_of_2_option(
            QStringList() << "2" << "powerOfTwo",
            "If the atlas should be in units of power of 2 or irregular."
    );
    QCommandLineOption crop_alpha_option(
            QStringList() << "c" << "cropAlpha",
            "If source sprites should be cropped to their transparency bounds to pack them even tighter."
    );
    QCommandLineOption texture_format_option(
            QStringList() << "f" << "textFormat",
            "Choose the output texture format. Support png32 and png8 now.",
            "png8"
    );
    QCommandLineOption init_option(
            QStringList() << "init",
            "Generate a configuration file."
    );

    QCommandLineParser command_line_parser;

    command_line_parser.addOption(output_option);
    command_line_parser.addOption(resource_option);

    command_line_parser.addOption(max_size_option);
    command_line_parser.addOption(tile_size_option);

    command_line_parser.addOption(extrude_option);

    command_line_parser.addOption(include_images_option);
    command_line_parser.addOption(exclude_images_option);

    command_line_parser.addOption(tile_padding_option);
    command_line_parser.addOption(force_option);
    command_line_parser.addOption(power_of_2_option);
    command_line_parser.addOption(crop_alpha_option);
    command_line_parser.addOption(texture_format_option);
    command_line_parser.addOption(init_option);

    command_line_parser.addHelpOption();
    command_line_parser.addVersionOption();
    command_line_parser.addPositionalArgument("input",
                                              QCoreApplication::translate("main", "input directory or config file."));

    command_line_parser.process(application);

    SetupInputDirectory   (command_line_parser.positionalArguments());
    SetupOutputDirectory  (command_line_parser.isSet(output_option),   command_line_parser.value(output_option));
    SetupResourceDirectory(command_line_parser.isSet(resource_option), command_line_parser.value(resource_option));
    SetupExcludeDirectory (command_line_parser.isSet(exclude_images_option),  command_line_parser.value(exclude_images_option));

    extrude = std::stoi(command_line_parser.value(extrude_option).toStdString());
    max_size = std::stoi(command_line_parser.value(max_size_option).toStdString());
    tile_size = std::stoi(command_line_parser.value(tile_size_option).toStdString());
    shape_padding = std::stoi(command_line_parser.value(tile_padding_option).toStdString());
    power_of_two = command_line_parser.isSet(power_of_2_option);
    crop_alpha = command_line_parser.isSet(crop_alpha_option);
    force = command_line_parser.isSet(force_option);
}

void Args::SetupInputDirectory(const QStringList &positional_arguments)
{
//    if (positional_arguments.size() == 1)
//    {
        input = QDir(positional_arguments.at(0));
        bool success = input.makeAbsolute();
        assert(success);
        input_directory = input;

        if (input.exists())
        {
            cout << "input    directory : " << input.path().toStdString() << "\n";
        } else
        {
            cout << "input \"" << input.path().toStdString() << "\" not found.\n";
            exit(EXIT_FAILURE);
        }
//    } else
//    {
//        cout << "wrong count of input files, expected 1.\n";
//        exit(EXIT_FAILURE);
//    }
}


void Args::SetupOutputDirectory(bool is_set, const QString &value)
{
    if (is_set)
    {
        output_directory = QDir(value);
        bool success = output_directory.makeAbsolute();
        assert(success);
    } else
    {
        output_directory = input_directory;
        output_directory.cdUp();
        QString default_output("default_output");
        output_directory.mkdir(default_output);
        output_directory.cd(default_output);
    }

    printf("output   directory : %s\n", output_directory.path().toStdString().c_str());
}

void Args::SetupResourceDirectory(bool is_set, const QString &value)
{
    if (is_set)
    {
        resource_directory = QDir(value);
        bool success = resource_directory.makeAbsolute();
        assert(success);
    } else
    {
        resource_directory = input_directory;
        resource_directory.cdUp();
        QString default_output("default_resource");
        resource_directory.mkdir(default_output);
        resource_directory.cd(default_output);
    }

    cout << "resource directory : " << resource_directory.path().toStdString() << "\n\n";
}

void ::Args::SetupExcludeDirectory(bool is_set, const QString &value)
{
    if (!is_set) return;

    cout << "EXCLUDE IMAGES\n";

    QStringList exclude_files_in_string = value.split(',');
    for (int i = 0; i < exclude_files_in_string.size(); ++i)
    {
        QString file_path(exclude_files_in_string.at(i));
        QFileInfo file_info(file_path);
        if(file_info.isRelative())
        {
            file_info.setFile(input_directory.filePath(file_path));
        }

        exclude_files.push_back(file_info);

        cout << "    " << file_info.absoluteFilePath().toStdString() << "\n";
    }
    cout << "\n";
}

bool ::Args::isExclude(const QFileInfo &file)
{
    auto find_index = std::find(exclude_files.cbegin(), exclude_files.cend(), file);
    return find_index != exclude_files.cend();
}