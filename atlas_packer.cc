//
// Created by wengxiang on 2017/1/30.
//

#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>

#include "atlas_packer.h"
#include "cli_args.h"

using FreeRectChoiceHeuristic = rbp::MaxRectsBinPack::FreeRectChoiceHeuristic;
using rbp::MaxRectsBinPack;
using rbp::Rect;
using std::accumulate;
using std::min;
using std::cout;
using std::setw;

AtlasPacker::AtlasPacker()
{
    sheet_index = 0;
}

int AtlasPacker::getCeilPowOfTwo(int value)
{
    int retVal = 1;
    while (retVal < value)
        retVal <<= 1;
    return retVal;
}

QImage* AtlasPacker::ImageCropAlpha(const QImage *input, Bounds &new_bounds)
{
    int x = 0, y = 0, w = input->width(), h = input->height();

    // crop top
    for(int row = 0; row < input->height(); ++row)
    {
        uchar result = accumulate(
                input->scanLine(row),
                input->scanLine(row) + input->bytesPerLine(),
                0,
                std::bit_or<uchar>());
        if(result != 0)
        {
            y = row;
            break;
        }
    }

    // crop bottom
    for(int row = input->height() - 1; row >= 0; --row)
    {
        uchar result = accumulate(
                input->scanLine(row),
                input->scanLine(row) + input->bytesPerLine(),
                0,
                std::bit_or<uchar>());
        if(result != 0)
        {
            h = row - y;
            break;
        }

        ++new_bounds.bottom;
    }

    // crop left
    for(int col = 0; col < input->width(); ++col)
    {
        uchar result = 0;
        for(int row = 0; row < input->height(); ++row)
        {
            const uchar* pixel = input->scanLine(row) + col * 4;
            result |= *(pixel + 0);
            result |= *(pixel + 1);
            result |= *(pixel + 2);
            result |= *(pixel + 3);
        }

        if(result != 0)
        {
            x = col;
            break;
        }
    }

    // crop right
    for(int col = input->width() - 1; col >= 0; --col)
    {
        uchar result = 0;
        for(int row = 0; row < input->height(); ++row)
        {
            const uchar* pixel = input->scanLine(row) + col * 4;
            result |= *(pixel + 0);
            result |= *(pixel + 1);
            result |= *(pixel + 2);
            result |= *(pixel + 3);
        }

        if(result != 0)
        {
            w = col - x;
            break;
        }

        ++new_bounds.right;
    }

    new_bounds.x = x;
    new_bounds.y = y;
    new_bounds.w = w;
    new_bounds.h = h;
    return new QImage(input->copy(x, y, w, h));
}

QImage *AtlasPacker::ImageExtrude(QImage *input, bool trimmed, Bounds bounds) {
    int new_width = input->width() + Args::extrude * 2,
            new_height = input->height() + Args::extrude * 2;

    QImage *output = new QImage(new_width, new_height, QImage::Format_ARGB32);
    output->fill(0);

    // copy image
    for(int row = 0; row < input->height(); ++row)
    {
        memcpy(output->scanLine(row + Args::extrude) + Args::extrude * 4, input->scanLine(row), input->bytesPerLine());
    }
    // ImageExtrude
    for(int i = 0; i < Args::extrude; ++i)
    {
        // ImageExtrude top
        if(bounds.y == 0)
            memcpy(
                    output->scanLine(i) + Args::extrude * 4,
                    input->scanLine(0),
                    input->bytesPerLine());

        // ImageExtrude bottom
        if(bounds.bottom == 0)
            memcpy(
                    output->scanLine(input->height() + Args::extrude + i) + Args::extrude * 4,
                    input->scanLine(input->height() - 1),
                    input->bytesPerLine());

        for(int row = 0; row < input->height(); ++row)
        {
            // ImageExtrude left
            if(bounds.x == 0)
                memcpy(
                        output->scanLine(row + Args::extrude) + i * 4,
                        input->scanLine(row),
                        4);
            // ImageExtrude right
            if(bounds.right == 0)
                memcpy(
                        output->scanLine(row + Args::extrude) + (i + Args::extrude + input->width()) * 4,
                        input->scanLine(row) + (input->width() - 1) * 4,
                        4);
        }
    }

    return output;
}

void AtlasPacker::ImageDrawImage(QImage &canvas, const QImage &image, int dest_x, int dest_y)
{
    for(int row = 0; row < image.height(); ++row)
    {
        for(int col = 0; col < image.width(); ++col)
        {
            canvas.setPixel(
                    dest_x + col,
                    dest_y + row,
                    image.pixel(col, row));
        }
//        memcpy(
//                canvas.scanLine(row + dest_y) + dest_x * 4,
//                image.scanLine(row),
//                image.bytesPerLine()
//        );
    }
}

void AtlasPacker::evaluateAppropriateSize(QVector<ImageInfo> &images, FreeRectChoiceHeuristic choiceHeuristic, Size& opacity_bounds, Size& bin_size)
{
    int bin_width = 128;
    int bin_height = 128;

//    if (Args::power_of_two)
//    {
//        bin_width = getCeilPowOfTwo(bin_width);
//        bin_height = getCeilPowOfTwo(bin_height);
//    }

//    if (bin_width > Args::max_size)
//        bin_width = Args::max_size;
//    if (bin_height > Args::max_size)
//        bin_height = Args::max_size;

    const unsigned step = 32;
    while (!canAccommodate(choiceHeuristic, images, bin_width, bin_height, opacity_bounds))
    {
        if(Args::power_of_two)
        {
            bin_width += step;
            bin_height += step;
        }
        else
        {
            if (bin_height < bin_width)
                bin_width += step;
            else
                bin_height += step;
        }

        if (bin_width > Args::max_size ||
                bin_height > Args::max_size)
            break;

        opacity_bounds.w = 0;
        opacity_bounds.h = 0;
    }

    bin_size.w = bin_width;
    bin_size.h = bin_height;
}

bool AtlasPacker::canAccommodate(
        FreeRectChoiceHeuristic choice_heuristic,
        QVector<ImageInfo> &images,
        int w, int h,
        Size& opacity_size)
{
    bin_pack.Init(w + Args::shape_padding, h + Args::shape_padding);
    for (ImageInfo &imgInfo : images)
    {
        const Bounds &bounds = imgInfo.spriteSourceSize;

        Rect result = bin_pack.Insert(
                imgInfo.image->width()  + Args::shape_padding,
                imgInfo.image->height() + Args::shape_padding,
                choice_heuristic);

        opacity_size.w = std::max(
                opacity_size.w,
                result.x + result.width + Args::extrude * 2 - Args::shape_padding);
        opacity_size.h = std::max(
                opacity_size.h,
                result.y + result.height + Args::extrude * 2 - Args::shape_padding);

        if (result.width == 0)
            return false;
    }

    return true;
}

void AtlasPacker::storageHeuristicResult(QVector<ImageInfo> &images, QVector<HeuristicResult> &heuristic_results, MaxRectsBinPack::FreeRectChoiceHeuristic choiceHeuristic)
{
    Size opacity_size = { 0, 0 };
    Size bin_size = { 0, 0 };

    evaluateAppropriateSize(images, choiceHeuristic, opacity_size, bin_size);
    heuristic_results.push_back({
                                        choiceHeuristic,
                                        opacity_size,
                                        bin_size
                                });
}

bool AtlasPacker::Insert(QImage &canvas, ImageInfo &image_info, FreeRectChoiceHeuristic heuristic) {
    Rect result = bin_pack.Insert(
            image_info.image->width()  + Args::shape_padding,
            image_info.image->height() + Args::shape_padding,
            heuristic
    );

    if(result.width != image_info.image->width() + Args::shape_padding)
    {
        image_info.rotated = true;

        QMatrix rotate;
        rotate.rotate(90);
        QImage rotated_image = image_info.image->transformed(rotate);

        delete image_info.image;

        image_info.image = new QImage(rotated_image);
    }

    QFileInfo file(image_info.filename);
    cout
            << setw(30)
            << file.fileName().toStdString()
            << " ("
            << setw(5)
            << result.x << " "
            << setw(5)
            << result.y << " "
            << setw(5)
            << result.width << " "
            << setw(4)
            << result.height
            << ")" << "\n";

    if (result.width == 0)
    {
        return false;
    }
    else
    {
        result.width  -= Args::shape_padding;
        result.height -= Args::shape_padding;

        image_info.frame = {
                result.x + Args::extrude,
                result.y + Args::extrude,
                result.width - Args::extrude * 2,
                result.height - Args::extrude * 2,
                sheet_index
        };

        ImageDrawImage(canvas, *image_info.image, result.x, result.y);

        return true;
    }
}

void AtlasPacker::PackImages(QVector<ImageInfo> &images, const QDir &in_dir) {
    // sort images by area.
    auto CompareImageArea = [](const ImageInfo &a, const ImageInfo &b) -> bool {
        QImage *image_a = a.image;
        QImage *image_b = b.image;

        return image_a->width() * image_a->height() > image_b->width() * image_b->height();
    };
//    std::sort(images.begin(), images.end(), CompareImageArea);

    for (ImageInfo &imageInfo : images)
    {
        QImage *image = imageInfo.image;

        imageInfo.sourceSize.w = image->width();
        imageInfo.sourceSize.h = image->height();

        if (Args::crop_alpha) {
            image = ImageCropAlpha(image, imageInfo.spriteSourceSize);

            if (
                    imageInfo.spriteSourceSize.x != 0 ||
                    imageInfo.spriteSourceSize.y != 0 ||
                    imageInfo.spriteSourceSize.w != imageInfo.image->width() ||
                    imageInfo.spriteSourceSize.h != imageInfo.image->height())
                imageInfo.trimmed = true;

            delete imageInfo.image;
            imageInfo.image = image;
        }

        if (Args::extrude) {
            image = ImageExtrude(image, imageInfo.trimmed, imageInfo.spriteSourceSize);
            delete imageInfo.image;
            imageInfo.image = image;
        }
    }

    // get export atlas filename.
    QDir in_parent(in_dir);
    in_parent.cdUp();

    QString relative = Args::input_directory.relativeFilePath(in_parent.path());
    QDir    out_dir(Args::output_directory.filePath(relative));
    QString output_name = in_dir.dirName() + ".png";

    QDir().mkpath(out_dir.path());

    export_dir = out_dir.filePath(output_name);
    bool make_absolute_success = export_dir.makeAbsolute();
    assert(make_absolute_success);
    generateAtlas(images);
}

void AtlasPacker::ExportAtlas(const QImage &canvas)
{
    canvas.save(export_dir.path());
    cout << "SAVE " << export_dir.path().toStdString() << "\n\n";
}

void AtlasPacker::generateAtlas(QVector<ImageInfo> &images) {

    // 计算各种排列方式的优劣
    QVector<HeuristicResult> heuristic_result;

    storageHeuristicResult(images, heuristic_result, MaxRectsBinPack::RectBestAreaFit);
    storageHeuristicResult(images, heuristic_result, MaxRectsBinPack::RectBestLongSideFit);
    storageHeuristicResult(images, heuristic_result, MaxRectsBinPack::RectBestShortSideFit);
    storageHeuristicResult(images, heuristic_result, MaxRectsBinPack::RectBottomLeftRule);
    storageHeuristicResult(images, heuristic_result, MaxRectsBinPack::RectContactPointRule);

    // 找出最小代价的排列方式
    std::sort(heuristic_result.begin(), heuristic_result.end(), [](
            const HeuristicResult &resultA, const HeuristicResult &resultB
    ) -> bool {
        const Size &opacity_sizeA = resultA.opacity_size;
        const Size &opacity_sizeB = resultB.opacity_size;

        return opacity_sizeA.w * opacity_sizeA.h < opacity_sizeB.w * opacity_sizeB.h;
    });

    int max_tile_width = 0;
    int max_tile_height = 0;

    std::for_each(images.cbegin(), images.cend(),
                  [&max_tile_width, &max_tile_height](const ImageInfo &imageInfo) -> void {
                      const Bounds &bounds = imageInfo.spriteSourceSize;
                      max_tile_width = bounds.w > max_tile_width ? bounds.w : max_tile_width;
                      max_tile_height = bounds.h > max_tile_height ? bounds.h : max_tile_height;
                  });

    // 取出第一个元素，即最低消耗排列
    MaxRectsBinPack::FreeRectChoiceHeuristic choiceHeuristic = heuristic_result.at(0).heuristic;
    const Size &opacity_size = heuristic_result.at(0).opacity_size;
    const Size &bin_size = heuristic_result.at(0).bin_size;

    int opacity_width = opacity_size.w;
    int opacity_height = opacity_size.h;

    // 如果指定<powerOfTwo>，将宽高设置成2的整次幂。
    if (Args::power_of_two) {
        opacity_width = getCeilPowOfTwo(opacity_width);
        opacity_height = getCeilPowOfTwo(opacity_height);
        opacity_width = min(opacity_width, Args::max_size);
        opacity_height = min(opacity_height, Args::max_size);

        while (opacity_width < max_tile_width)
            opacity_width *= 2;
        while (opacity_height < max_tile_height)
            opacity_height *= 2;
    }

    // Reset.
    bin_pack.Init(bin_size.w + Args::shape_padding, bin_size.h + Args::shape_padding);
    QImage canvas(bin_size.w + Args::shape_padding, bin_size.h + Args::shape_padding, QImage::Format_ARGB32);

    while (images.size() > 0) {
        ImageInfo &imageInfo = images.front();

        bool success = Insert(canvas, imageInfo, choiceHeuristic);

        if (success)
        {
            images.removeFirst();
//            jsonDataFormat.addFrame(packResult);
        } else
        {
//            ExportAtlas(canvas);
            ++sheet_index;
            generateAtlas(images);
//            return;
        }
    }

    ExportAtlas(canvas);
//    exportData();
}
