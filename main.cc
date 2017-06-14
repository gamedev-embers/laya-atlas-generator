#include <QCoreApplication>
#include <QDir>
#include <QImage>
#include <QTextStream>
#include <QDateTime>
#include <QTimer>

#include <fstream>
#include <iostream>

#include "Configuration.h"
#include "Utils.h"
#include "AtlasPacker.h"

using std::cout;
using std::cerr;
using std::vector;

// pre-definitions.
void ProcessFile(const QFileInfo &file_info, AtlasPacker& atlas_packer, vector<QDir>& directories);
void ProcessRegularFile(QString filename, AtlasPacker &atlas_packer);
void GenerateAtlas(AtlasPacker& atlas_packer, const QDir &dir);

// 检查资源（输入目录下的所有文件）是否被修改过（自上次打包）。
// 在资源已修改的情况下，将在调用处继续执行程序。
// 在资源未修改的情况下：
// - 用户指定了<force>，将在调用处继续执行程序。
// - 用户未指定<force>，直接exit。
void CheckResourceModification()
{
    // 用户指定了强制打包时，不需要检查后续步骤
    if (cfg::force)
    {
        cout << "Force Publication.\n";
        return;
    }

    QFile record_file(cfg::outputDirectory.filePath(".rec"));

    // 检查打包记录并且得出是否重新打包
    bool need_repack = true;
    QFileInfo input_file_info(cfg::input.path());
    qint64 last_write_time = input_file_info.lastModified().msecsTo(QDateTime());

    if (record_file.exists())
    {
        if (record_file.open(QFile::ReadOnly))
        {
            QString prev_pack_time;
            QTextStream in(&record_file);
            in.readLineInto(&prev_pack_time);
            record_file.close();

            need_repack = (prev_pack_time.toLongLong() != last_write_time);
        }
    }

    // 覆盖打包记录
    if (need_repack)
    {
        if (record_file.open(QFile::WriteOnly))
        {
            QTextStream out(&record_file);
            out << last_write_time
                << "\nThe precede value represent a timestamp is for atlas packing.";
            record_file.close();
        }

        cout << "Resources have been modified.\n";
    }

    if (!need_repack)
    {
        cout << "Resources have no change.\n";
        exit(EXIT_SUCCESS);
    }
}

void PackDirectory(const QDir &dir)
{
    // 检查目录是否被用户排除
    if (cfg::IsExclude(QFileInfo(dir.path())))
    {
        cout << "EXCLUDE " << dir.absolutePath().toStdString() << "\n";
        file_utils::CopyToResourceDirectory(dir.path());
        return;
    }

    vector<QDir> directories;
    // 处理指定目录下所有文件
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    AtlasPacker atlas_packer;

    for(QFileInfo& file_info : file_list)
        ProcessFile(file_info, atlas_packer, directories);

    cout << "\n";

    GenerateAtlas(atlas_packer, dir);

    // 打包子目录
    while (directories.size() > 0)
    {
        PackDirectory(directories.back());
        directories.pop_back();
    }
}

void GenerateAtlas(AtlasPacker& atlas_packer, const QDir &dir)
{
    if(atlas_packer.IsEmpty())
        return;

    atlas_packer.PackBin();

    // get export atlas filename.
    QString relative = cfg::inputDirectory.relativeFilePath(dir.path());
    atlas_packer.ExportAtlas(relative);
}

void ProcessFile(const QFileInfo &file_info, AtlasPacker &atlas_packer, vector<QDir> &directories)
{
    QString file_path = file_info.filePath();
    // 检查到目录
    if (file_info.isDir())
        directories.push_back(QDir(file_path));
    // 检查到常规文件
    else
        ProcessRegularFile(file_path, atlas_packer);
}

void ProcessRegularFile(QString filename, AtlasPacker &atlas_packer)
{
    // 检查文件是否被用户排除
    bool is_exclude = cfg::IsExclude(QFileInfo(filename));
    if (is_exclude)
        cout << "EXCLUDE " << filename.toStdString() << "\n";

    bool is_image = atlas_packer.AddImage(filename);
    if (!is_image)
        cout << "NOT IMAGE " << filename.toStdString() << "\n";

    if(is_exclude || !is_image)
        file_utils::CopyToResourceDirectory(filename);
}

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);

    cfg::ParseCommandLine(a);
    CheckResourceModification();

    PackDirectory(cfg::input);
    return EXIT_SUCCESS;
}
