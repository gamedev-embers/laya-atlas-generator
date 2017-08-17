#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtGui/QImage>
#include <QTextCodec>

#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>

#include "Configuration.h"
#include "Utils.h"
#include "AtlasPacker.h"

#include "CRC32/CRC32.h"

using namespace std;

using RecordItem = map<string, unsigned int>;
struct RecordItems
{
    RecordItem pictures;
    RecordItem regularFiles;
};
using Record = vector<pair<QString, RecordItems*>>;

Record record;
RecordItems *processingDirRecordItems;
vector<QDir> directories;
vector<tuple<QString, QImage*, unsigned int>> imagesInCurrentDirectory;
stringstream recordSStream;

CRC32 crc;

void ProcessFile(QFileInfo &file_info, AtlasPacker &atlas_packer, vector<QDir> &directories);

void GenerateAtlas(AtlasPacker &atlas_packer, const QDir &dir);
void readRecord();
void PackDirectories();
void ProcessFile(QFileInfo &file_info, AtlasPacker &atlas_packer, vector<QDir> &directories);
void ProcessRegularFile(QString filePath);
bool isRegularFileModified(QString filePath, unsigned int crc);
bool isImageFileModified(QString filePath, unsigned int crc);
bool needRepack();
void writeRecord();
void free();

void GenerateAtlas(AtlasPacker &atlas_packer, const QDir &dir)
{
    if (atlas_packer.IsEmpty())
        return;

    atlas_packer.PackBin();

    // get export atlas filename.
    QString relative = Configuration::inputDirectory.relativeFilePath(dir.path());
    atlas_packer.ExportAtlas(relative);
}

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);

    Configuration::parseCommandLine(a);

    readRecord();

    recordSStream << std::hex << std::uppercase;
    // 资源的根目录和其他目录不一样
    // 位于资源根目录下的图片不会被打包
    recordSStream << "D ." << '\n';
    QFileInfoList file_list = Configuration::inputDirectory.entryInfoList(
            QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (const QFileInfo &fileInfo : file_list)
    {
        QString filePath(fileInfo.filePath());
        // 根目录下的目录稍后会被打包成图集
        if (fileInfo.isDir())
        {
            directories.push_back(QDir(filePath));
        }
            // 根目录下的文件被直接复制
        else
        {
            recordSStream << "R " << crc.fileCrc(filePath.toStdString()) << ' ' << fileInfo.fileName().toStdString()
                          << '\n';
            file_utils::CopyToResourceDirectory(filePath);
            cout << "INROOT " << filePath.toStdString() << "\n";
        }
    }

    while (directories.size() > 0)
        PackDirectories();

    writeRecord();

    cout << std::flush;

    free();

    return EXIT_SUCCESS;
}

void readRecord()
{
    if (Configuration::force)
    {
        cout << "Force Publication.\n";
        return;
    }

    QFile record_file(Configuration::outputDirectory.filePath(".rec"));
    if (record_file.exists())
    {
        if (record_file.open(QFile::ReadOnly))
        {
            QString line;
            QTextStream in(&record_file);
            in.setCodec("utf8");

            RecordItems *recordItems;
            while (!in.atEnd())
            {
                in.readLineInto(&line);

                QChar fileType = line.at(0);

                if (fileType == 'D')
                {
                    QString file = line.mid(2);
                    recordItems = new RecordItems;
                    record.push_back({ file, recordItems });
//                    cout << "D " << stringList.at(1).toStdString() << std::endl;
                } else
                {
                    QString crcString = line.mid(2, 8);
                    QString file = line.mid(11);
                    unsigned int crc;
                    sscanf(crcString.toStdString().c_str(), "%x", &crc);
                    pair<string, unsigned int> value = { file.toStdString(), crc };
                    if (fileType == 'R')
                    {
                        recordItems->regularFiles.insert(value);
                    } else if (fileType == 'P')
                    {
                        recordItems->pictures.insert(value);
                    }
                }

            }
            record_file.close();
        }
    }
}

void PackDirectories()
{
    imagesInCurrentDirectory.clear();
    QDir dir = directories.front();

    recordSStream << "D " << file_utils::GetRelativeToInputDirectoryPath(dir.path()).toStdString() << '\n';

    // 在record中找到这个目录的记录（可能没有记录）
    for(auto &item : record)
    {
        if(item.first == file_utils::GetRelativeToInputDirectoryPath(dir.path()))
        {
            processingDirRecordItems = item.second;
            break;
        }
    }
    cout << "DIRECTORY " << dir.path().toStdString() << '\n';

    directories.erase(directories.begin());

    // 检查目录是否被用户排除
    if (Configuration::IsExclude(QFileInfo(dir.path())))
    {
        cout << "EXCLUDE " << dir.absolutePath().toStdString() << "\n";
        file_utils::CopyToResourceDirectory(dir.path());
        return;
    }

    // 处理指定目录下所有文件
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    AtlasPacker atlas_packer;

    for (QFileInfo &file_info : file_list)
        ProcessFile(file_info, atlas_packer, directories);

    if(needRepack())
    {
        cout << "directory has been changed\n";
        for(auto &image : imagesInCurrentDirectory)
        {
            atlas_packer.AddImage(std::get<0>(image), std::get<1>(image));
        }
    }
    else
    {
        cout << "directory has not changes\n";
    }

    // 重置目录记录为空指针，否则下次未找到记录时会使用上次的目录记录
    processingDirRecordItems = nullptr;

    cout << "\n";

    GenerateAtlas(atlas_packer, dir);
}

void ProcessFile(QFileInfo &file_info, AtlasPacker &atlas_packer, vector<QDir> &directories)
{
    QString file_path = file_info.filePath();
    // 检查到目录
    if (file_info.isDir())
        directories.push_back(QDir(file_path));
        // 检查到常规文件
    else
        ProcessRegularFile(file_path);
}

bool isRegularFileModified(QString filePath, unsigned int crc)
{
    if(processingDirRecordItems == nullptr) return true;

    std::string fileName = QFileInfo(filePath).fileName().toStdString();
    auto files = processingDirRecordItems->regularFiles;

    if(files.find(fileName) != files.end())
    {
        if(files.at(fileName) == crc)
            return false;
    }
    return true;
}

bool isImageFileModified(QString filePath, unsigned int crc)
{
    if(processingDirRecordItems == nullptr) return true;

    std::string fileName = QFileInfo(filePath).fileName().toStdString();
    auto files = processingDirRecordItems->pictures;

    if(files.find(fileName) != files.end())
    {
        if(files.at(fileName) == crc)
            return false;
    }
    return true;
}

void ProcessRegularFile(QString filePath)
{
    std::string fileName = QFileInfo(filePath).fileName().toStdString();
    unsigned int crc32 = crc.fileCrc(filePath.toStdString());
    bool isModified = true;

    // 检查文件是否被用户排除
    if (Configuration::IsExclude(QFileInfo(filePath)))
    {
        isModified = isRegularFileModified(filePath, crc32);
        if(isModified)
            file_utils::CopyToResourceDirectory(filePath);
        recordSStream << "R ";
        cout << (isModified ? "*" : "=") << " EXCLUDE " << fileName << "\n";
    } else
    {
        QImage *image = new QImage(filePath);

        // is not a image.
        if (image->isNull())
        {
            recordSStream << "R ";
            isModified = isRegularFileModified(filePath, crc32);
            if(isModified)
                file_utils::CopyToResourceDirectory(filePath);
            cout << (isModified ? "*" : "=") << " NOTIMAGE " << fileName << "\n";
        } else
        {

            // image's size is overflow.
            if (image->width() > Configuration::spriteSize || image->height() > Configuration::spriteSize)
            {
                if (Configuration::IsInclude(QFileInfo(filePath)))
                {
                    recordSStream << "P ";
                    isModified = isImageFileModified(filePath, crc32);
                    cout << (isModified ? "*" : "=") << " INCLUDE ";
                } else
                {
                    recordSStream << "R ";
                    isModified = isRegularFileModified(filePath, crc32);
                    if(isModified)
                        file_utils::CopyToResourceDirectory(filePath);
                    cout << (isModified ? "*" : "=") << " OVERFLOW " << fileName << "\n";
                    recordSStream
                            << setfill('0')
                            << setw(8)
                            << crc32
                            << ' ' << fileName << '\n';
                    return;
                }
            } else
            {
                recordSStream << "P ";

                isModified = isImageFileModified(filePath, crc32);
                cout << (isModified ? "*" : "=") << " LOAD ";
            }

            imagesInCurrentDirectory.push_back(make_tuple(filePath, image, crc32));
            cout << fileName << "\n";
        }
    }
    recordSStream
            << setfill('0')
            << setw(8)
            << crc32
            << ' ' << fileName << '\n';
}

bool needRepack()
{
    // 记录中没有这个目录的打包记录，或者强制发布的情况
    if(processingDirRecordItems == nullptr || Configuration::force)
        return true;

    auto pictures = processingDirRecordItems->pictures;
    if(imagesInCurrentDirectory.size() == pictures.size())
    {
        for(auto &image : imagesInCurrentDirectory)
        {
            auto fileName = QFileInfo(std::get<0>(image)).fileName().toStdString();
            if(pictures.find(fileName) != pictures.end())
            {
                if(pictures.at(fileName) != std::get<2>(image))
                    return true;
            } else
            {
                return true;
            }
        }
    } else{
        return true;
    }

    return false;
}

void writeRecord()
{
    QString path = Configuration::outputDirectory.filePath(".rec");

    QFile outFile(path);
    if(outFile.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream outStream(&outFile);
        outStream.setCodec("utf8");

        QString outString(recordSStream.str().c_str());
#ifdef WIN32
        QTextCodec *codec = QTextCodec::codecForName("utf8");
        outString = codec->fromUnicode(outString);
#endif
        outStream << outString;
        outStream.flush();
        outFile.close();
    }
    else
    {
        cerr << "Unable to open " << Configuration::outputDirectory.filePath(".rec").toStdString() << std::flush;
    }
}

void free()
{
    int n = record.size();
    while(n--)
    {
        delete record.at(n).second;
    }
}
