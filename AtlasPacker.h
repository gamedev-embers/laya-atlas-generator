//
// Created by wengxiang on 2017/1/30.
//

#ifndef ATLASGENERATOR_ATLAS_PACKER_H
#define ATLASGENERATOR_ATLAS_PACKER_H

#include <QVector>
#include <QImage>
#include <QtCore/QDir>

#include "RectangleBinPack/Rect.h"
#include "RectangleBinPack/MaxRectsBinPack.h"
#include "DataExport.h"

struct ImageInfo
{
    QImage *image = nullptr;
    QString filename;
    rbp::Rect frame;
    bool rotated = false;
    bool trimmed = false;
    int image_index;

    rbp::Rect sprite_source_size;
    rbp::RectSize source_size;
};
struct HeuristicResult
{
    rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method;
    std::vector<rbp::Rect> rects;
    std::vector<ImageInfo> images;
    double occupancy;
    rbp::RectSize opacity_size;
    rbp::RectSize bin_size;
};

class AtlasPacker
{
private:
    QImage* ImageCropAlpha(const QImage *input, rbp::Rect &new_bounds);

    QImage* ImageExtrude(QImage *input, bool trimmed, ImageInfo& bounds);
    void ImageDrawImage(QImage &canvas, const QImage &image, int dest_x, int dest_y);
    void StorageInsertResult(QVector<HeuristicResult> &heuristic_result,
                             rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method);
    void GenerateAtlas();
    bool Insert(int bin_width, int bin_height, HeuristicResult &result, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method);

    int sheet_index;

    rbp::MaxRectsBinPack bin_pack;
    std::vector<ImageInfo> images;
    std::vector<QImage*> canvases;
    DataExport* data_export;

public:

    AtlasPacker();
    ~AtlasPacker();
    /*
     * try to add a image to AtlasPacker.
     * <filename> is the path to image.
     * if this isn't a image file, or file not exist, return false.
     */
    bool AddImage(QString filename);
    /*
     * pack all images into bin.
     * if there is no image storage in this atlas packer.
     * then ignore.
     */
    void PackBin();
    /*
     * export atlas.
     * if there is no image to export.
     * then ignore.
     */
    void ExportAtlas(QString relative_path);
    bool IsEmpty();
};

#endif //ATLASGENERATOR_ATLAS_PACKER_H