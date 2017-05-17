//
// Created by wengxiang on 2017/1/28.
//

#ifndef ATLASGENERATOR_CLI_ARGS_H
#define ATLASGENERATOR_CLI_ARGS_H

#include <QString>

class QCoreApplication;
class QDir;

namespace args
{
    extern QDir input_directory;
    extern QDir output_directory;
    extern QDir resource_directory;
    extern QVector<QFileInfo> exclude_files;

    extern bool force;

    void ParseCommandLine(const QCoreApplication &application);
    void SetupOutputDirectory(bool is_set, const QString &value);
    void SetupResourceDirectory(bool is_set, const QString &value);
    void SetupExcludeDirectory(bool is_set, const QString &value);

    bool isExclude(const QFileInfo& file);
}

#endif //ATLASGENERATOR_CLI_ARGS_H
