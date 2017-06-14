//
// Created by wengxiang on 2017/1/28.
//

#ifndef ATLASGENERATOR_CLI_ARGS_H
#define ATLASGENERATOR_CLI_ARGS_H

#include <QString>
#include <QDir>
#include <QtGui/QImage>

class QCoreApplication;

class cfg
{
public:
    static QDir input;
    static QDir inputDirectory;
    static QDir outputDirectory;
    static QDir resourceDirectory;

    static int maxSize, spriteSize;
    static int shapePadding;

    static QVector<QFileInfo> excludeFiles;

    static int extrude;
    static bool cropAlpha;
    static bool force;
    static bool POT;
    static bool rotate;

    // for image control
    static QImage::Format pixelFormat;
    static int textureQuality;
    static QString textureFormat;

    static void ParseCommandLine(const QCoreApplication &application);
    static bool IsExclude(const QFileInfo &file);
    static void ReadFromConfigFile(const QString file_path);

private:
    static QString getDefaultConfigContent();

    static void SetupInputDirectory   (const QStringList &positional_arguments);
    static void SetupOutputDirectory  (bool is_set, const QString &value);
    static void SetupResourceDirectory(bool is_set, const QString &value);
    static void SetupExcludeDirectory (bool is_set, const QString &value);

    static void SetupPixelFormat(QString pixel_format_string);
    static void ProcessInitDirective(bool is_init);
};

#endif //ATLASGENERATOR_CLI_ARGS_H
