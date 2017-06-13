//
// Created by wengxiang on 2017/2/4.
//
#include <QString>
#include <QFileInfo>
#include <QDir>

#include "utils.h"
#include "cli_args.h"

using std::string;

void file_utils::Copy(const QString &from, const QString &to)
{
    QString command, arg;
#ifdef Q_OS_WIN
    if(QFileInfo(from).isDir())
    {

    }
#else
    arg = QFileInfo(from).isDir() ? "rf" : "f";

    // 先移除文件，避免文件夹和文件同名时出问题
    command = QString("rm -rf %2").arg(to);
    system(command.toStdString().c_str());

    // 使用系统命令复制文件。
    command = QString("cp -%1 %2 %3")
            .arg(arg)
            .arg(from)
            .arg(to);
#endif
    system(command.toStdString().c_str());
}

void ::file_utils::CopyToResourceDirectory(const QString &path)
{
    QString relative_path = Args::input_directory.relativeFilePath(path);

    Args::resource_directory.mkpath(QFileInfo(relative_path).dir().path());

    QString to_path = Args::resource_directory.filePath(relative_path);
    Copy(path, to_path);
}

QString file_utils::GetRelativeToInputDirectoryPath(QString path)
{
    return Args::input_directory.relativeFilePath(path);
}

int ::math_utils::CeilPOT(int value)
{
    int val = 2;
    while(val < value) val *= 2;
    return val;
}
