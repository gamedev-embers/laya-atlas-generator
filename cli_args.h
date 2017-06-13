//
// Created by wengxiang on 2017/1/28.
//

#ifndef ATLASGENERATOR_CLI_ARGS_H
#define ATLASGENERATOR_CLI_ARGS_H

#include <QString>
#include <QDir>
#include <QtGui/QImage>

class QCoreApplication;

class Args
{
public:
    static QDir input;
    static QDir input_directory;
    static QDir output_directory;
    static QDir resource_directory;

    static int max_size, tile_size;
    static int shape_padding;

    static QVector<QFileInfo> exclude_files;

    static int extrude;
    static bool crop_alpha;
    static bool force;
    static bool power_of_two;
    static bool rotate;

    // for image control
    static QImage::Format pixel_format;
    static int texture_qulity;

    static void ParseCommandLine(const QCoreApplication &application);

    static bool isExclude(const QFileInfo& file);
private:
    static void SetupInputDirectory   (const QStringList &positional_arguments);
    static void SetupOutputDirectory  (bool is_set, const QString &value);
    static void SetupResourceDirectory(bool is_set, const QString &value);
    static void SetupExcludeDirectory (bool is_set, const QString &value);

    static void SetupPixelFormat(QString pixel_format);
};

#endif //ATLASGENERATOR_CLI_ARGS_H
