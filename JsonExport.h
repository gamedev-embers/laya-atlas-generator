//
// Created by survivor on 17-6-9.
//

#ifndef ATLAS_GENERATOR_JSONEXPORT_H
#define ATLAS_GENERATOR_JSONEXPORT_H

#include <QJsonDocument>
#include <QJsonObject>

#include "DataExport.h"

class JsonExport : public DataExport
{
public:
    JsonExport();

    virtual void AddImageDescription(const ImageInfo &image_info);
    virtual void Export(const QString &file_path);
    virtual void Clear();

    void SetMetaImages(QString images) override;

    void SetMetaFormat(QString format) override;

    void SetMetaSize(int width, int height) override;

private:
    QJsonDocument json_document;
    QJsonObject frames_object;
    QJsonObject meta_object;
};


#endif //ATLAS_GENERATOR_JSONEXPORT_H
