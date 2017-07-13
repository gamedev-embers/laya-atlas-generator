//
// Created by wengxiang on 2017/2/4.
//

#ifndef ATLASGENERATOR_UTILS_H
#define ATLASGENERATOR_UTILS_H

namespace file_utils
{
    QString GetRelativeToInputDirectoryPath(QString path);
    bool Copy(const QString &from, const QString &to);
    void CopyToResourceDirectory(const QString &path);
    void mkdirs(QString root, QString relative);
}

namespace math_utils
{
    int CeilPOT(int value);
}

#endif //ATLASGENERATOR_UTILS_H
