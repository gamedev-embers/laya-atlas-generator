//
// Created by wengxiang on 2017/1/28.
//

#ifndef ATLASGENERATOR_CLI_ARGS_H
#define ATLASGENERATOR_CLI_ARGS_H

#include <QString>
#include <QDir>
#include <QtGui/QImage>

class QCoreApplication;

class Configuration
{
public:
    // static member declarations
    // --------------------------
    // directories
    static QDir input,
                inputDirectory,
                outputDirectory,
                resourceDirectory;

    // sprite properties
    static bool cropAlpha,
                rotate;
    static int spriteSize,
               shapePadding,
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
    static void ReadFromConfigFile(const QString file_path);

private:
    static QString getDefaultConfigContent();

    static void SetupInputDirectory(const QStringList &positional_arguments);

    static void SetupOutputDirectory(bool is_set, const QString &value);

    static void SetupResourceDirectory(bool is_set, const QString &value);

    static void SetupExcludeDirectory(bool is_set, const QString &value);

    static void SetupPixelFormat(QString pixel_format_string);

    static void ProcessInitDirective(bool is_init);
};

#endif //ATLASGENERATOR_CLI_ARGS_H
