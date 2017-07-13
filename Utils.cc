//
// Created by wengxiang on 2017/2/4.
//
#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QRegularExpression>

#include <fstream>
#include <iostream>

#include "Utils.h"
#include "Configuration.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::cerr;
using std::endl;

bool file_utils::Copy(const QString &from, const QString &to)
{
    if(QFileInfo(from).isDir())
    {
        QDir fromDir(from), toDir(to);

        QFileInfoList fileList = fromDir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
        for(const QFileInfo &file : fileList)
        {
            QString relative = fromDir.relativeFilePath(file.filePath());
            Copy(file.filePath(), toDir.filePath(relative));
        }
    }
    else
    {
        FILE *in, *out;
        in = fopen(from.toStdString().c_str(), "rb");
        out = fopen(to.toStdString().c_str(), "wb");
        if(in && out)
        {
            void *buf;
            while(!feof(in))
            {
                fread(&buf, 1, 1, in);
                fwrite(&buf, 1, 1, out);
            }
            fclose(in);
            fclose(out);
            return true;
        }
        else
        {
            return false;
        }
    }

    return false;
}

void ::file_utils::CopyToResourceDirectory(const QString &path)
{
    QString relative_path = Configuration::inputDirectory.relativeFilePath(path);

    Configuration::resourceDirectory.mkpath(QFileInfo(relative_path).dir().path());

    QString to_path = Configuration::resourceDirectory.filePath(relative_path);
    Copy(path, to_path);
}

QString file_utils::GetRelativeToInputDirectoryPath(QString path)
{
    return Configuration::inputDirectory.relativeFilePath(path);
}

void file_utils::mkdirs(QString root, QString relative)
{
    QDir dir(root);
    QStringList parts = relative.split(QRegularExpression("/|\\\\"), QString::SkipEmptyParts);
    for(int i = 0; i < parts.length(); ++i)
    {
        dir.mkdir(parts[i]);
        dir.cd(parts[i]);
    }
}

int ::math_utils::CeilPOT(int value)
{
    int val = 2;
    while(val < value) val *= 2;
    return val;
}
