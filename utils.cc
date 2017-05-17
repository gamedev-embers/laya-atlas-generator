//
// Created by wengxiang on 2017/2/4.
//
#include <iostream>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include "utils.h"
#include "cli_args.h"

using std::cerr;
using std::cout;
using std::endl;

void file_utils::Copy(const QString &from, const QString &to)
{
    if (TARGET_OS_WIN32)
    {

    } else if (TARGET_OS_MAC)
    {
        QString command, arg;
        arg = QFileInfo(from).isDir() ? "rf" : "f";

        // 先移除文件，避免文件夹替换同名文件时失败。
        command = QString("rm -%1 %2").arg(arg).arg(to);
        system(command.toStdString().c_str());

        // 使用系统命令复制文件。
        command = QString("cp -%1 %2 %3")
                .arg(arg)
                .arg(from)
                .arg(to);

        system(command.toStdString().c_str());

        cout << qPrintable(command) << '\n';
    } else
    {
        cerr << "failed to Copy files." << endl;
        exit(EXIT_FAILURE);
    }
}

#include <QDebug>
void ::file_utils::CopyToResourceDirectory(const QString &path)
{
    QString relative_path = args::input_directory.relativeFilePath(path);

    qDebug() << args::resource_directory.path() << relative_path;
    args::resource_directory.mkpath(relative_path);

    QString to_path = args::resource_directory.path() + QDir::separator() + relative_path;
    Copy(path, to_path);
}
