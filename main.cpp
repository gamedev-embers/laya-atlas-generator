#include <QCoreApplication>
#include <QDir>
#include <iostream>
#include <QImage>
#include <fstream>
#include <QTextStream>
#include <QDateTime>
#include <QVector>

#include "cli_args.h"
#include "utils.h"
#include "atlas_packer.h"

using std::cout;
using std::endl;

// 检查资源（输入目录下的所有文件）是否被修改过（自上次打包）。
// 在资源已修改的情况下，将在调用处继续执行程序。
// 在资源未修改的情况下：
//     - 用户指定了<force>，将在调用处继续执行程序。
//     - 用户未指定<force>，直接exit。
void CheckResourceModification()
{
    // 用户指定了强制打包时，不需要检查后续步骤
    if (args::force)
    {
        cout << "Force publication.\n";
        return;
    }

    QFile record_file(args::output_directory.filePath(".rec"));

    // 检查打包记录并且得出是否重新打包
    bool need_repack = true;
    QFileInfo input_file_info(args::input_directory.path());
    qint64 last_write_time = input_file_info.lastModified().msecsTo(QDateTime());

    if (record_file.exists())
    {
        if(record_file.open(QFile::ReadOnly))
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
        if(record_file.open(QFile::WriteOnly))
        {
            QTextStream out(&record_file);
            out << last_write_time
                << "\nThe precede value represent a timestamp is for atlas packing.";
            record_file.close();
        }

        cout << "Resources has been modified." << endl;
    }

    if (!need_repack)
    {
        cout << "The resources have not been modified." << endl;
        exit(EXIT_SUCCESS);
    }
}

void PackDirectory(const QDir &dir)
{
    // 检查目录是否被用户排除
    if(args::isExclude(QFileInfo(dir.path())))
    {
        file_utils::CopyToResourceDirectory(dir.path());
        return;
    }

    QVector<QImage*> images;
    QVector<QDir> dirs;
    // 处理指定目录下所有文件
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    for (int i = 0; i < file_list.size(); ++i)
    {
        QFileInfo file_info = file_list.at(i);
        QString file_path = file_info.filePath();
        // 检查到目录
        if(file_info.isDir())
        {
            dirs.push_back(QDir(file_path));
        }
        // 检查到常规文件
        else
        {
            // 尝试当作图片加载
            // 加载失败则复制到资源目录
            // 加载成功则push入images，稍后会打包这些images
            QImage image(file_path);
            if(image.isNull())
                file_utils::CopyToResourceDirectory(file_path);
            else
                images.push_back(&image);
        }
    }

    // 处理图片文件
    if(images.size() > 0)
        atlas::PackImages(images);

    // 打包子目录
    while(dirs.size() > 0)
    {
        PackDirectory(dirs.back());
        dirs.pop_back();
    }
}

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);

    args::ParseCommandLine(a);
    CheckResourceModification();
    PackDirectory(args::input_directory);

    return a.exec();
}

