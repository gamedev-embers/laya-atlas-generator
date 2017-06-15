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
// ---------------
using std::cout;
using std::cerr;

// static member definitions
// -------------------------
// directories
QFileInfo Configuration::input;
QDir Configuration::inputDirectory,
     Configuration::outputDirectory,
     Configuration::resourceDirectory;

// sprite properties
bool Configuration::cropAlpha,
     Configuration::rotation;
int Configuration::spriteSize,
    Configuration::spritePadding,
    Configuration::extrude;

// texture properties
QImage::Format Configuration::pixelFormat;
QString        Configuration::textureFormat;
int Configuration::textureQuality,
    Configuration::maxSize;
bool Configuration::POT;

// other properties
bool Configuration::force;
QVector<QFileInfo> Configuration::excludeFiles;
QString Configuration::pixelFormatString;

// static function definitions
void Configuration::ParseCommandLine(const QCoreApplication &application)
{
    // command line options
    QCommandLineOption outputOption(
            QStringList() << "o" << "output",
            "The directory for exporting atlas.",
            "directory"
    );

    QCommandLineOption resourceOption(
            QStringList() << "r" << "resource",
            "Thr directory of files cannot be packed.",
            "directory"
    );
    QCommandLineOption maxSizeOption(
            QStringList() << "S" << "maxSize",
            "Max size of atlas.",
            "value",
            "2048"
    );
    QCommandLineOption spriteSizeOption(
            QStringList() << "s" << "spriteSize",
            "Max size of sprite.",
            "value",
            "512"
    );
    QCommandLineOption extrudeOption(
            QStringList() << "e" << "extrude",
            "Repeat the sprite's pixels at the borders.",
            "value",
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
            "value",
            "1"
    );
    QCommandLineOption force_option(
            QStringList() << "f" << "force",
            "If true, then publish even if picture never be modified.");
    QCommandLineOption POTOption(
            QStringList() << "2" << "POT",
            "If the atlas should be in units of power of 2 or irregular."
    );
    QCommandLineOption cropAlphaOption(
            QStringList() << "c" << "cropAlpha",
            "If source sprites should be cropped to their transparency bounds to pack them even tighter."
    );
    QCommandLineOption rotateOption(
            QStringList() << "r" << "rotation",
            "Allow sprite rotation to fit area better."
    );
    QCommandLineOption pixelFormatOption(
            QStringList() << "pixelFormat",
            "Mono | MonoLSB | Indexed8 | RGB32 | ARGB32 | ARGB32_Premultiplied | RGB16 | ARGB8565_Premultiplied | RGB666 | ARGB6666_Premultiplied | RGB555 | ARGB8555_Premultiplied | RGB888 | RGB444 | ARGB4444_Premultiplied | RGBX8888 | RGBA8888 | RGBA8888_Premultiplied | BGR30 | A2BGR30_Premultiplied | RGB30 | A2RGB30_Premultiplied | Alpha8 | Grayscale8, default ARGB32",
            "pixel format", "ARGB32"
    );
    QCommandLineOption textureQualityOption(
            QStringList() << "q" << "textureQuality",
            "The quality of texture images. The quality factor must be in the range 0 to 100 or -1. Specify 0 to obtain small compressed files, 100 for large uncompressed files, and -1 (the default) to use the default settings.",
            "quality", "-1"
    );
    QCommandLineOption textureFormatOption(
            QStringList() << "textureFormat",
            "The format of texture images. The value is BMP | JPG | JPEG | PNG | XBM | XPM, default PNG.",
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
    commandLineParser.addOption(textureFormatOption);
    commandLineParser.addOption(initOption);

    commandLineParser.addHelpOption();
    commandLineParser.addVersionOption();
    commandLineParser.addPositionalArgument("input",
                                            QCoreApplication::translate("main", "input directory or config file."));

    commandLineParser.process(application);

    // process user input
    ProcessInitDirective(commandLineParser.isSet(initOption));

    input = QFileInfo(commandLineParser.positionalArguments().at(0));
    bool success = input.makeAbsolute();
    assert(success);

    if (input.exists())
    {
        if(input.isDir())
        {
            inputDirectory    = QDir(input.filePath());
            extrude           = commandLineParser.value(extrudeOption).toInt();
            maxSize           = commandLineParser.value(maxSizeOption).toInt();
            spriteSize        = commandLineParser.value(spriteSizeOption).toInt();
            spritePadding     = commandLineParser.value(spritePaddingOption).toInt();
            textureQuality    = commandLineParser.value(textureQualityOption).toInt();
            textureFormat     = commandLineParser.value(textureFormatOption);
            POT               = commandLineParser.isSet(POTOption);
            cropAlpha         = commandLineParser.isSet(cropAlphaOption);
            rotation          = commandLineParser.isSet(rotateOption);
            force             = commandLineParser.isSet(force_option);

            SetupPixelFormat(commandLineParser.value(pixelFormatOption));
            SetupExcludeDirectory(commandLineParser.value(excludeImagesOption));
        } else
        {
            ReadConfigurationFile(input.filePath());
        }
        SetupOutputDirectory(commandLineParser.value(outputOption));
        SetupResourceDirectory(commandLineParser.value(resourceOption));

        PrintConfiguration();
    } else
    {
        cout << "input \"" << input.filePath().toStdString() << "\" not found.\n";
        exit(EXIT_FAILURE);
    }
}

void Configuration::ReadConfigurationFile(QString configFilePath)
{
    QFile configFile(configFilePath);
    configFile.open(QFile::ReadOnly | QFile::Text);
    if(!configFile.isOpen())
    {
        cerr << "Cannot open " << configFilePath.toStdString() << " for reading" << std::endl;
        exit(EXIT_FAILURE);
    }

    // read content
    QTextStream in_stream(&configFile);

    // parse content
    auto content = in_stream.readAll().toUtf8();
    QJsonParseError error;
    QJsonDocument config_document = QJsonDocument::fromJson(content, &error);

    // process parser error
    if(error.error != QJsonParseError::ParseError::NoError)
    {
        cerr << "JSON Parser Error: " << error.errorString().toStdString() << std::endl;
        exit(EXIT_FAILURE);
    }

    // retrieve data
    QJsonObject rootObject   = config_document.object();
    QJsonObject atlasObject  = rootObject.value("atlas").toObject();
    QJsonObject spriteObject = rootObject.value("sprite").toObject();
    QJsonArray excludeArray  = rootObject.value("excludeList").toArray();
    QJsonArray includeArray  = rootObject.value("includeList").toArray();
    POT                      = atlasObject.value("POT").toBool();
    textureQuality           = atlasObject.value("quality").toInt();
    maxSize                  = atlasObject.value("size").toInt();
    textureFormat            = atlasObject.value("textureFormat").toString();
    force                    = rootObject.value("force").toBool();
    inputDirectory           = rootObject.value("inputDir").toString();
    outputDirectory          = rootObject.value("outputDir").toString();
    resourceDirectory        = rootObject.value("resDir").toString();
    cropAlpha                = spriteObject.value("cropAlpha").toBool();
    extrude                  = spriteObject.value("extrude").toInt();
    spritePadding            = spriteObject.value("padding").toInt();
    rotation                 = spriteObject.value("rotation").toBool();
    spriteSize               = spriteObject.value("size").toInt();

    bool success = inputDirectory.makeAbsolute();
    assert(success);

    SetupExcludeDirectory(rootObject.value("excludeList").toArray());
    SetupPixelFormat(atlasObject.value("pixelFormat").toString());
}

void Configuration::SetupOutputDirectory(const QString &value)
{
    if (value.isEmpty())
        outputDirectory = inputDirectory.filePath("../default_output");
    else
        outputDirectory = QDir(value);

    bool success = outputDirectory.mkpath(".");
    assert(success);
    success = outputDirectory.makeAbsolute();
    assert(success);
}

void Configuration::SetupResourceDirectory(const QString &value)
{
    if (value.isEmpty())
        resourceDirectory = inputDirectory.filePath("../default_resource");
    else
        resourceDirectory = QDir(value);

    bool success = resourceDirectory.mkpath(".");
    assert(success);
    success = resourceDirectory.makeAbsolute();
    assert(success);
}

void ::Configuration::SetupExcludeDirectory(const QString &value)
{
    if(value.isEmpty())
    {
        return;
    }

    QStringList exclude_files_in_string = value.split(',');
    for (int i = 0; i < exclude_files_in_string.size(); ++i)
    {
        QString file_path(exclude_files_in_string.at(i));
        QFileInfo file_info(file_path);
        if (file_info.isRelative())
        {
            file_info.setFile(inputDirectory.filePath(file_path));
        }

        excludeFiles.push_back(file_info);
    }
    cout << "\n";
}

void Configuration::SetupExcludeDirectory(const QJsonArray &list)
{
    for(auto pos = list.constBegin(); pos != list.constEnd(); ++pos)
    {
        QString path((*pos).toString());
        QFileInfo fileInfo(path);
        if(fileInfo.isRelative())
            fileInfo.setFile(inputDirectory.filePath(path));
        excludeFiles.push_back(fileInfo);
    }
}

bool ::Configuration::IsExclude(const QFileInfo &file)
{
    auto find_index = std::find(excludeFiles.cbegin(), excludeFiles.cend(), file);
    return find_index != excludeFiles.cend();
}

void Configuration::SetupPixelFormat(QString pixelFormatString)
{
    Configuration::pixelFormatString = pixelFormatString;
    if (pixelFormatString == "Mono")
        pixelFormat = QImage::Format::Format_Mono;
    else if (pixelFormatString == "MonoLSB")
        pixelFormat = QImage::Format::Format_MonoLSB;
    else if (pixelFormatString == "Indexed8")
        pixelFormat = QImage::Format::Format_Indexed8;
    else if (pixelFormatString == "RGB32")
        pixelFormat = QImage::Format::Format_RGB32;
    else if (pixelFormatString == "ARGB32")
        pixelFormat = QImage::Format::Format_ARGB32;
    else if (pixelFormatString == "ARGB32_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB32_Premultiplied;
    else if (pixelFormatString == "RGB16")
        pixelFormat = QImage::Format::Format_RGB16;
    else if (pixelFormatString == "ARGB8565_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB8565_Premultiplied;
    else if (pixelFormatString == "RGB666")
        pixelFormat = QImage::Format::Format_RGB666;
    else if (pixelFormatString == "ARGB6666_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB6666_Premultiplied;
    else if (pixelFormatString == "RGB555")
        pixelFormat = QImage::Format::Format_RGB555;
    else if (pixelFormatString == "ARGB8555_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB8555_Premultiplied;
    else if (pixelFormatString == "RGB888")
        pixelFormat = QImage::Format::Format_RGB888;
    else if (pixelFormatString == "RGB444")
        pixelFormat = QImage::Format::Format_RGB444;
    else if (pixelFormatString == "ARGB4444_Premultiplied")
        pixelFormat = QImage::Format::Format_ARGB4444_Premultiplied;
    else if (pixelFormatString == "RGBX8888")
        pixelFormat = QImage::Format::Format_RGBX8888;
    else if (pixelFormatString == "RGBA8888")
        pixelFormat = QImage::Format::Format_RGBA8888;
    else if (pixelFormatString == "RGBA8888_Premultiplied")
        pixelFormat = QImage::Format::Format_RGBA8888_Premultiplied;
    else if (pixelFormatString == "BGR30")
        pixelFormat = QImage::Format::Format_BGR30;
    else if (pixelFormatString == "A2BGR30_Premultiplied")
        pixelFormat = QImage::Format::Format_A2BGR30_Premultiplied;
    else if (pixelFormatString == "RGB30")
        pixelFormat = QImage::Format::Format_RGB30;
    else if (pixelFormatString == "A2RGB30_Premultiplied")
        pixelFormat = QImage::Format::Format_A2RGB30_Premultiplied;
    else if (pixelFormatString == "Alpha8")
        pixelFormat = QImage::Format::Format_Alpha8;
    else if (pixelFormatString == "Grayscale8")
        pixelFormat = QImage::Format::Format_Grayscale8;
    else
        std::cerr << "NO PIXEL FORMAT " << pixelFormatString.toStdString() << '\n';
}

QString Configuration::GetDefaultConfigContent()
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
    atlasObject.insert("pixelFormat", "ARGB32");
    atlasObject.insert("quality", -1);
    atlasObject.insert("textureFormat", "PNG");
    rootObject.insert("atlas", atlasObject);

    QJsonObject spriteObject;
    spriteObject.insert("padding", 1);
    spriteObject.insert("rotation", false);
    spriteObject.insert("size", 512);
    spriteObject.insert("cropAlpha", true);
    spriteObject.insert("extrude", 1);
    rootObject.insert("sprite", spriteObject);

    document.setObject(rootObject);
    return document.toJson();
}

void Configuration::ProcessInitDirective(bool is_init)
{
    if(!is_init)
        return;

    QFile out_file("atlasConfig");
    if (!out_file.open(QFile::WriteOnly | QFile::Text))
    {
        cerr << "Can not open file 'atlasConfig' for writing." << std::endl;
        exit(EXIT_FAILURE);
    }

    QTextStream out_stream(&out_file);
    out_stream << GetDefaultConfigContent();
    out_stream.flush();
    out_file.close();

    cout << "SAVE " << QFileInfo(out_file).absoluteFilePath().toStdString() << std::endl;
    exit(EXIT_SUCCESS);
}

void Configuration::PrintConfiguration()
{
    cout
         << std::setw(25) << std::left << "input directory" << input.path().toStdString() << "\n"
         << std::setw(25) << std::left << "output directory" << outputDirectory.path().toStdString() << "\n"
         << std::setw(25) << std::left << "resource directory" << resourceDirectory.path().toStdString() << "\n"
         << std::setw(25) << std::left << "crop alpha" << std::boolalpha << cropAlpha << "\n"
         << std::setw(25) << std::left << "allow rotation" << rotation << "\n"
         << std::setw(25) << std::left << "max sprite size" << spriteSize << "\n"
         << std::setw(25) << std::left << "max texture size" << maxSize <<"\n"
         << std::setw(25) << std::left << "sprite padding" << spritePadding << "\n"
         << std::setw(25) << std::left << "extrude" << extrude << "\n"
         << std::setw(25) << std::left << "pixel format" << pixelFormatString.toStdString() << "\n"
         << std::setw(25) << std::left << "texture format" << textureFormat.toStdString() << "\n"
         << std::setw(25) << std::left << "texture quality" << textureQuality << "\n"
         << std::setw(25) << std::left << "POT" << POT << "\n\n"
         << "EXCLUDE IMAGES\n";
    for(const QFileInfo& fileInfo : excludeFiles)
        cout << "    " << fileInfo.absoluteFilePath().toStdString() << "\n";
    cout << "\n";
}
