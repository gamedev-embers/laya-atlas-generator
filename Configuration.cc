//
// Created by wengxiang on 2017/1/28.
//

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QFile>
#include <QVector>
#include <QFileInfo>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#include <QtCore/QTextStream>

#include <cassert>
#include <iomanip>
#include <iostream>
#include "Configuration.h"

// open namespaces
using std::cout;
using std::cerr;

// static member definitions
QDir Args::input;
QDir Args::input_directory;
QDir Args::output_directory;
QDir Args::resource_directory;
int Args::max_size, Args::tile_size;
int Args::shape_padding;
QImage::Format Args::pixel_format;
int Args::texture_quality;
QVector<QFileInfo> Args::exclude_files;
int  Args::extrude;
bool Args::crop_alpha;
bool Args::force;
bool Args::power_of_two;
bool Args::rotate;

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
            "1"
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
            "1"
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
    QCommandLineOption rotate_option(
            QStringList() << "r" << "rotate",
            "Allow sprite rotation to fit area better."
    );
    QCommandLineOption pixel_format_option(
            QStringList() << "m" << "format",
            "Choose the output texture pixel format. Mono | MonoLSB | Indexed8 | RGB32 | ARGB32 | ARGB32_Premultiplied | RGB16 | ARGB8565_Premultiplied | RGB666 | ARGB6666_Premultiplied | RGB555 | ARGB8555_Premultiplied | RGB888 | RGB444 | ARGB4444_Premultiplied | RGBX8888 | RGBA8888 | RGBA8888_Premultiplied | BGR30 | A2BGR30_Premultiplied | RGB30 | A2RGB30_Premultiplied | Alpha8 | Grayscale8",
            "pixel format", "ARGB32"
    );
    QCommandLineOption texture_quality_option(
            QStringList() << "q" << "textureQuality",
            "",
            "texture quality", "-1"
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
    command_line_parser.addOption(rotate_option);
    command_line_parser.addOption(pixel_format_option);
    command_line_parser.addOption(texture_quality_option);
    command_line_parser.addOption(init_option);

    command_line_parser.addHelpOption();
    command_line_parser.addVersionOption();
    command_line_parser.addPositionalArgument("input",
                                              QCoreApplication::translate("main", "input directory or config file."));

    command_line_parser.process(application);

    ProcessInitDirective(command_line_parser.isSet(init_option));

    SetupInputDirectory   (command_line_parser.positionalArguments());
    SetupOutputDirectory  (command_line_parser.isSet(output_option),   command_line_parser.value(output_option));
    SetupResourceDirectory(command_line_parser.isSet(resource_option), command_line_parser.value(resource_option));
    SetupExcludeDirectory (command_line_parser.isSet(exclude_images_option),  command_line_parser.value(exclude_images_option));
    SetupPixelFormat      (command_line_parser.value(pixel_format_option));

    extrude = command_line_parser.value(extrude_option).toInt();
    max_size = command_line_parser.value(max_size_option).toInt();
    tile_size = command_line_parser.value(tile_size_option).toInt();
    shape_padding = std::stoi(command_line_parser.value(tile_padding_option).toStdString());
    power_of_two = command_line_parser.isSet(power_of_2_option);
    crop_alpha = command_line_parser.isSet(crop_alpha_option);
    rotate = command_line_parser.isSet(rotate_option);
    force = command_line_parser.isSet(force_option);
    texture_quality = command_line_parser.value(texture_quality_option).toInt();
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

bool ::Args::IsExclude(const QFileInfo &file)
{
    auto find_index = std::find(exclude_files.cbegin(), exclude_files.cend(), file);
    return find_index != exclude_files.cend();
}

void Args::SetupPixelFormat(QString pixel_format_string)
{
    if(pixel_format_string == "Mono")
        pixel_format = QImage::Format::Format_Mono;
    else if(pixel_format_string == "MonoLSB")
        pixel_format = QImage::Format::Format_MonoLSB;
    else if(pixel_format_string == "Indexed8")
        pixel_format = QImage::Format::Format_Indexed8;
    else if(pixel_format_string == "RGB32")
        pixel_format = QImage::Format::Format_RGB32;
    else if(pixel_format_string == "ARGB32")
        pixel_format = QImage::Format::Format_ARGB32;
    else if(pixel_format_string == "ARGB32_Premultiplied")
        pixel_format = QImage::Format::Format_ARGB32_Premultiplied;
    else if(pixel_format_string == "RGB16")
        pixel_format = QImage::Format::Format_RGB16;
    else if(pixel_format_string == "ARGB8565_Premultiplied")
        pixel_format = QImage::Format::Format_ARGB8565_Premultiplied;
    else if(pixel_format_string == "RGB666")
        pixel_format = QImage::Format::Format_RGB666;
    else if(pixel_format_string == "ARGB6666_Premultiplied")
        pixel_format = QImage::Format::Format_ARGB6666_Premultiplied;
    else if(pixel_format_string == "RGB555")
        pixel_format = QImage::Format::Format_RGB555;
    else if(pixel_format_string == "ARGB8555_Premultiplied")
        pixel_format = QImage::Format::Format_ARGB8555_Premultiplied;
    else if(pixel_format_string == "RGB888")
        pixel_format = QImage::Format::Format_RGB888;
    else if(pixel_format_string == "RGB444")
        pixel_format = QImage::Format::Format_RGB444;
    else if(pixel_format_string == "ARGB4444_Premultiplied")
        pixel_format = QImage::Format::Format_ARGB4444_Premultiplied;
    else if(pixel_format_string == "RGBX8888")
        pixel_format = QImage::Format::Format_RGBX8888;
    else if(pixel_format_string == "RGBA8888")
        pixel_format = QImage::Format::Format_RGBA8888;
    else if(pixel_format_string == "RGBA8888_Premultiplied")
        pixel_format = QImage::Format::Format_RGBA8888_Premultiplied;
    else if(pixel_format_string == "BGR30")
        pixel_format = QImage::Format::Format_BGR30;
    else if(pixel_format_string == "A2BGR30_Premultiplied")
        pixel_format = QImage::Format::Format_A2BGR30_Premultiplied;
    else if(pixel_format_string == "RGB30")
        pixel_format = QImage::Format::Format_RGB30;
    else if(pixel_format_string == "A2RGB30_Premultiplied")
        pixel_format = QImage::Format::Format_A2RGB30_Premultiplied;
    else if(pixel_format_string == "Alpha8")
        pixel_format = QImage::Format::Format_Alpha8;
    else if(pixel_format_string == "Grayscale8")
        pixel_format = QImage::Format::Format_Grayscale8;
    else
        std::cerr << "NO FORMAT " << pixel_format_string.toStdString() << '\n';
}

void Args::ReadFromConfigFile(const QString file_path)
{

}

QString Args::getDefaultConfigContent()
{
    QJsonDocument document;
    QJsonObject rootObject;

    rootObject.insert("inputDir", "required");
    rootObject.insert("outputDir", "");
    rootObject.insert("resDir", "");
    rootObject.insert("force", true);
    rootObject.insert("includeList", QJsonArray());
    rootObject.insert("excludeList", QJsonArray());

    QJsonObject atlasObject;
    atlasObject.insert("size", 2048);
    atlasObject.insert("POT", false);
    atlasObject.insert("spritePadding", 1);
    atlasObject.insert("pixelFormat", "ARGB32");
    atlasObject.insert("quality", -1);
    rootObject.insert("atlas", atlasObject);

    QJsonObject spriteObject;
    spriteObject.insert("size", 512);
    spriteObject.insert("cropAlpha", true);
    rootObject.insert("sprite", spriteObject);

    document.setObject(rootObject);
    return document.toJson();
}

void Args::ProcessInitDirective(bool is_init)
{
    QFile out_file("atlasConfig");
    if(!out_file.open(QFile::WriteOnly | QFile::Text))
    {
        cerr << "Can not open file 'atlasConfig' for writing." << std::endl;
        exit(EXIT_FAILURE);
    }

    QTextStream out_stream(&out_file);
    out_stream << getDefaultConfigContent();
    out_stream.flush();
    out_file.close();

    cout << "SAVE " << QFileInfo(out_file).absoluteFilePath().toStdString() << std::endl;
    exit(EXIT_SUCCESS);
}
