//
// Created by wengxiang on 2017/2/4.
//
#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>

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
    ifstream in;
    ofstream out;
    in.open(from.toStdString(), ios::binary);

    if(in.fail())
    {
       cerr<<"Error: Fail to open the source file."<<endl;
       in.close();
       out.close();
       return false;
    }

    out.open(to.toStdString(), ios::binary);
    if(out.fail())
    {
       cerr<<"Error: Fail to create the new file."<<endl;
       out.close();
       in.close();
       return false;
    }
    else
    {
       out<<in.rdbuf();
       out.close();
       in.close();
       return true;
    }
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

int ::math_utils::CeilPOT(int value)
{
    int val = 2;
    while(val < value) val *= 2;
    return val;
}
