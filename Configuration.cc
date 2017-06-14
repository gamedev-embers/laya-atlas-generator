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
QDir cfg::input;
QDir cfg::inputDirectory;
QDir cfg::outputDirectory;
QDir cfg::resourceDirectory;
int cfg::maxSize, cfg::spriteSize;
int cfg::shapePadding;
QImage::Format cfg::pixelFormat;
int cfg::textureQuality;
QVector<QFileInfo> cfg::excludeFiles;
int  cfg::extrude;
bool cfg::cropAlpha;
bool cfg::force;
bool cfg::POT;
bool cfg::rotate;

void cfg::ParseCommandLine(const QCoreApplication &application)
{
    // command line options
    QCommandLineOption outputOption(
            QStringList() << "o" << "output",
            "The directory for exporting atlas.",
            "output directory"
    );
    QCommandLineOption resourceOption(
            QStringList() << "r" << "resource",
            "Thr directory of files cannot be packed.",
            "resource directory"
    );
    QCommandLineOption maxSizeOption(
            QStringList() << "S" << "maxSize",
            "Max size of atlas.",
            "max atlas size",
            "2048"
    );
    QCommandLineOption spriteSizeOption(
            QStringList() << "s" << "spriteSize",
            "Max size of sprite.",
            "max sprite size",
            "512"
    );
    QCommandLineOption extrudeOption(
            QStringList() << "e" << "extrude",
            "Repeat the sprite's pixels at the borders.",
            "extrude",
            "1"
    );
    QCommandLineOption includeImagesOption(
            QStringList() << "includeImages",
            "The picture in include list have to packed anyway, split by ','"
    );
    QCommandLineOption excludeImagesOption(
            QStringList() << "x" << "exclude",
            "The picture in exclude list will not packed, split by ','.",
            "exclude directory"
    );
    QCommandLineOption spritePaddingOption(
            QStringList() << "p" << "spritePadding",
            "Tile padding is the space between sprites. Value adds transparent pixels between sprites to avoid artifacts from neighbor sprites. The transparent pixels are not added to the sprites. Default is 2.",
            "padding",
            "1"
    );
    QCommandLineOption force_option(
            QStringList() << "f" << "force",
            "If true, then publish even if picture never be modified.");
    QCommandLineOption POTOption(
            QStringList() << "2" << "powerOfTwo",
            "If the atlas should be in units of power of 2 or irregular."
    );
    QCommandLineOption cropAlphaOption(
            QStringList() << "c" << "cropAlpha",
            "If source sprites should be cropped to their transparency bounds to pack them even tighter."
    );
    QCommandLineOption rotateOption(
            QStringList() << "r" << "rotate",
            "Allow sprite rotation to fit area better."
    );
    QCommandLineOption pixelFormatOption(
            QStringList() << "m" << "format",
            "Choose the output texture pixel format. Mono | MonoLSB | Indexed8 | RGB32 | ARGB32 | ARGB32_Premultiplied | RGB16 | ARGB8565_Premultiplied | RGB666 | ARGB6666_Premultiplied | RGB555 | ARGB8555_Premultiplied | RGB888 | RGB444 | ARGB4444_Premultiplied | RGBX8888 | RGBA8888 | RGBA8888_Premultiplied | BGR30 | A2BGR30_Premultiplied | RGB30 | A2RGB30_Premultiplied | Alpha8 | Grayscale8",
            "pixel format", "ARGB32"
    );
    QCommandLineOption textureQualityOption(
            QStringList() << "q" << "textureQuality",
            "",
            "texture quality", "-1"
    );
    QCommandLineOption textureFormatOption(
            QStringList() << "textureFormat",
            "place holder",
            "texture format", "PNG"
    );
    QCommandLineOption initOption(
            QStringList() << "init",
            "Generate a configuration file."
    );

    // parse options
    QCommandLineParser commandLineParser;

    commandLineParser.addOption(outputOption);
    commandLineParser.addOption(resourceOption);
    commandLineParser.addOption(maxSizeOption);
    commandLineParser.addOption(spriteSizeOption);
    commandLineParser.addOption(extrudeOption);
    commandLineParser.addOption(includeImagesOption);
    commandLineParser.addOption(excludeImagesOption);
    commandLineParser.addOption(spritePaddingOption);
    commandLineParser.addOption(force_option);
    commandLineParser.addOption(POTOption);
    commandLineParser.addOption(cropAlphaOption);
    commandLineParser.addOption(rotateOption);
    commandLineParser.addOption(pixelFormatOption);
    commandLineParser.addOption(textureQualityOption);
    commandLineParser.addOption(initOption);

    commandLineParser.addHelpOption();
    commandLineParser.addVersionOption();
    commandLineParser.addPositionalArgument("input",
                                              QCoreApplication::translate("main", "input directory or config file."));

    commandLineParser.process(application);

    // process user input
    ProcessInitDirective(commandLineParser.isSet(initOption));

    SetupInputDirectory   (commandLineParser.positionalArguments());
    SetupOutputDirectory  (commandLineParser.isSet(outputOption)         , commandLineParser.value(outputOption));
    SetupResourceDirectory(commandLineParser.isSet(resourceOption)       , commandLineParser.value(resourceOption));
    SetupExcludeDirectory (commandLineParser.isSet(excludeImagesOption)  , commandLineParser.value(excludeImagesOption));
    SetupPixelFormat      (commandLineParser.value(pixelFormatOption));

    extrude        = commandLineParser.value(extrudeOption)        . toInt();
    maxSize        = commandLineParser.value(maxSizeOption)        . toInt();
    spriteSize     = commandLineParser.value(spriteSizeOption)     . toInt();
    shapePadding   = commandLineParser.value(spritePaddingOption)  . toInt();
    textureQuality = commandLineParser.value(textureQualityOption) . toInt();
    textureFormat  = commandLineParser.value(textureFormatOption);
    POT            = commandLineParser.isSet(POTOption);
    cropAlpha      = commandLineParser.isSet(cropAlphaOption);
    rotate         = commandLineParser.isSet(rotateOption);
    force          = commandLineParser.isSet(force_option);
}

void cfg::SetupInputDirectory(const QStringList &positional_arguments)
{
//    if (positional_arguments.size() == 1)
//    {
        input = QDir(positional_arguments.at(0));
        bool success = input.makeAbsolute();
        assert(success);
        inputDirectory = input;

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


void cfg::SetupOutputDirectory(bool is_set, const QString &value)
{
    if (is_set)
    {
        outputDirectory = QDir(value);
        bool success = outputDirectory.makeAbsolute();
        assert(success);
    } else
    {
        outputDirectory = inputDirectory;
        outputDirectory.cdUp();
        QString default_output("default_output");
        outputDirectory.mkdir(default_output);
        outputDirectory.cd(default_output);
    }

    printf("output   directory : %s\n", outputDirectory.path().toStdString().c_str());
}

void cfg::SetupResourceDirectory(bool is_set, const QString &value)
{
    if (is_set)
    {
        resourceDirectory = QDir(value);
        bool success = resourceDirectory.makeAbsolute();
        assert(success);
    } else
    {
        resourceDirectory = inputDirectory;
        resourceDirectory.cdUp();
        QString default_output("default_resource");
        resourceDirectory.mkdir(default_output);
        resourceDirectory.cd(default_output);
    }

    cout << "resource directory : " << resourceDirectory.path().toStdString() << "\n\n";
}

void ::cfg::SetupExcludeDirectory(bool is_set, const QString &value)
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
            file_info.setFile(inputDirectory.filePath(file_path));
        }

        excludeFiles.push_back(file_info);

        cout << "    " << file_info.absoluteFilePath().toStdString() << "\n";
    }
    cout << "\n";
}

bool ::cfg::IsExclude(const QFileInfo &file)
{
    auto find_index = std::find(excludeFiles.cbegin(), excludeFiles.cend(), file);
    return find_index != excludeFiles.cend();
}

void cfg::SetupPixelFormat(QString pixel_format_string)
{
    if(pixel_format_string == "Mono")
        pixelFormat = QImage::Format::Format_Mono;
    else if(pixel_format_string == "MonoLSB")
        pixelFormat = QImage::Format::Format_MonoLSB;
    else if(pixel_format_string == "Indexed8")
        pixelFormat = QImage::Format::Format_Indexed8;
    else if(pixel_format_string == "RGB32")
        pixelFormat = QImage::Format::Format_RGB32;
    else if(pixel_format_string == "ARGB32")
        pixelFormat = QImage::Format::Format_ARGB32;
    else if(pixel_format_string == "ARGB32_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB32_Premultiplied;
    else if(pixel_format_string == "RGB16")
        pixelFormat = QImage::Format::Format_RGB16;
    else if(pixel_format_string == "ARGB8565_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB8565_Premultiplied;
    else if(pixel_format_string == "RGB666")
        pixelFormat = QImage::Format::Format_RGB666;
    else if(pixel_format_string == "ARGB6666_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB6666_Premultiplied;
    else if(pixel_format_string == "RGB555")
        pixelFormat = QImage::Format::Format_RGB555;
    else if(pixel_format_string == "ARGB8555_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB8555_Premultiplied;
    else if(pixel_format_string == "RGB888")
        pixelFormat = QImage::Format::Format_RGB888;
    else if(pixel_format_string == "RGB444")
        pixelFormat = QImage::Format::Format_RGB444;
    else if(pixel_format_string == "ARGB4444_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB4444_Premultiplied;
    else if(pixel_format_string == "RGBX8888")
        pixelFormat = QImage::Format::Format_RGBX8888;
    else if(pixel_format_string == "RGBA8888")
        pixelFormat = QImage::Format::Format_RGBA8888;
    else if(pixel_format_string == "RGBA8888_Premultiplied")
        pixelFormat = QImage::Format::Format_RGBA8888_Premultiplied;
    else if(pixel_format_string == "BGR30")
        pixelFormat = QImage::Format::Format_BGR30;
    else if(pixel_format_string == "A2BGR30_Premultiplied")
        pixelFormat = QImage::Format::Format_A2BGR30_Premultiplied;
    else if(pixel_format_string == "RGB30")
        pixelFormat = QImage::Format::Format_RGB30;
    else if(pixel_format_string == "A2RGB30_Premultiplied")
        pixelFormat = QImage::Format::Format_A2RGB30_Premultiplied;
    else if(pixel_format_string == "Alpha8")
        pixelFormat = QImage::Format::Format_Alpha8;
    else if(pixel_format_string == "Grayscale8")
        pixelFormat = QImage::Format::Format_Grayscale8;
    else
        std::cerr << "NO FORMAT " << pixel_format_string.toStdString() << '\n';
}

void cfg::ReadFromConfigFile(const QString file_path)
{

}

QString cfg::getDefaultConfigContent()
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
    atlasObject.insert("textureFormat", "PNG");
    rootObject.insert("atlas", atlasObject);

    QJsonObject spriteObject;
    spriteObject.insert("size", 512);
    spriteObject.insert("cropAlpha", true);
    rootObject.insert("sprite", spriteObject);

    document.setObject(rootObject);
    return document.toJson();
}

void cfg::ProcessInitDirective(bool is_init)
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
