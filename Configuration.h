//
// Created by wengxiang on 2017/1/28.
//

#ifndef ATLASGENERATOR_CLI_ARGS_H
#define ATLASGENERATOR_CLI_ARGS_H

#include <QString>
#include <QDir>
#include <QtGui/QImage>
#include <QCommandLineParser>

class QCoreApplication;

class Configuration
{
public:
    // static member declarations
    // --------------------------
    // directories
    static QFileInfo input;
    static QDir inputDirectory,
                outputDirectory,
                resourceDirectory;

    // sprite properties
    static bool cropAlpha,
                rotation;
    static int spriteSize,
               spritePadding,
               extrude;

    // texture properties
    static QImage::Format pixelFormat;
    static QString        textureFormat;
    static int textureQuality,
               maxSize;
    static bool POT;

    // other properties
    static bool force;
    static QVector<QFileInfo> excludeFiles;

    // static function declarations
    static void ParseCommandLine(const QCoreApplication &application);
    static bool IsExclude(const QFileInfo &file);

private:
    static void ReadConfigurationFile(QString configFilePath);
    static QString getDefaultConfigContent();
    static void SetupOutputDirectory    (const QString &value);
    static void SetupResourceDirectory  (const QString &value);
    static void SetupExcludeDirectory   (const QString &value);
    static void SetupPixelFormat        (QString pixel_format_string);
    static void ProcessInitDirective  (bool is_init);
};

#endif //ATLASGENERATOR_CLI_ARGS_H
