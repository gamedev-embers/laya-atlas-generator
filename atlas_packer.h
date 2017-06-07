//
// Created by wengxiang on 2017/1/30.
//

#ifndef ATLASGENERATOR_ATLAS_PACKER_H
#define ATLASGENERATOR_ATLAS_PACKER_H

#include <QVector>
#include <QImage>
#include <QtCore/QDir>

#include "RectangleBinPack/MaxRectsBinPack.h"

struct Bounds
{
    int x = 0, y = 0, w = 0, h = 0;
    int bottom = 0, right = 0;
};
struct Size
{
    int w = 0, h = 0;
};
struct ImageInfo
{
    QImage *image = nullptr;
    QString filename;
    Bounds frame;
    bool rotated = false;
    bool trimmed = false;
    Bounds spriteSourceSize;
    Size sourceSize;
};
struct HeuristicResult
{
    rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic;
    Size opacity_size;
    Size bin_size;
};

class AtlasPacker
{
private:
    int getCeilPowOfTwo(int value);
    QImage* ImageCropAlpha(const QImage *input, Bounds &new_bounds);

    QImage* ImageExtrude(QImage *input, bool trimmed, Bounds bounds);
    void ImageDrawImage(QImage &canvas, const QImage &image, int dest_x, int dest_y);
    void evaluateAppropriateSize(QVector<ImageInfo>& images,
                                 rbp::MaxRectsBinPack::FreeRectChoiceHeuristic  choice_heuristic,
                                 Size& opacity_bounds, Size& bin_size);
    bool canAccommodate(rbp::MaxRectsBinPack::FreeRectChoiceHeuristic choice_heuristic, QVector<ImageInfo> &images, int w, int h,
                   Size& opacity_bounds);
    void storageHeuristicResult(QVector<ImageInfo> &images, QVector<HeuristicResult> &heuristic_result,
                                rbp::MaxRectsBinPack::FreeRectChoiceHeuristic choiceHeuristic);
    bool Insert(QImage &canvas, ImageInfo &image_info, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic heuristic);
    void generateAtlas(QVector<ImageInfo> &images);
    void ExportAtlas(const QImage &canvas);

    rbp::MaxRectsBinPack bin_pack;

    int sheet_index;

    QDir export_dir;

public:

    AtlasPacker();

    void PackImages(QVector<ImageInfo> &images, const QDir &in_dir);
};

#endif //ATLASGENERATOR_ATLAS_PACKER_H