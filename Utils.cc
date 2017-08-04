//
// Created by wengxiang on 2017/2/4.
//
#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QRegularExpression>

#include <fstream>
#include <iostream>
#include <io.h>

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
        mkdirs(to.toStdString());
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
    if(Configuration::noCopyResources) return;

    QString relative_path = Configuration::inputDirectory.relativeFilePath(path);

    Configuration::resourceDirectory.mkpath(QFileInfo(relative_path).dir().path());

    QString to_path = Configuration::resourceDirectory.filePath(relative_path);
    Copy(path, to_path);
}

QString file_utils::GetRelativeToInputDirectoryPath(QString path)
{
    return Configuration::inputDirectory.relativeFilePath(path);
}

bool file_utils::mkdirs(std::string path)
{
    using namespace  std;

    vector<string> folders;
    while(access(path.c_str(), 0) == -1)
    {
        auto pos = path.find_last_of("\\/");

        if(pos == string::npos)
            break;

        folders.push_back(path.substr(pos+1));
        path = path.substr(0, pos);
    }

    bool ret = false;
    while(folders.size())
    {
        path += '/' + folders.back();
        folders.pop_back();
        ret = mkdir(path.c_str()) == 0;
    }
    return ret;
}

int ::math_utils::CeilPOT(int value)
{
    int val = 2;
    while(val < value) val *= 2;
    return val;
}
