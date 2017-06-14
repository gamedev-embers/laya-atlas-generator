//
// Created by wengxiang on 2017/1/30.
//

#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>

#include "AtlasPacker.h"
#include "Utils.h"
#include "Configuration.h"
#include "JsonExport.h"

using FreeRectChoiceHeuristic = rbp::MaxRectsBinPack::FreeRectChoiceHeuristic;
using rbp::MaxRectsBinPack;
using rbp::Rect;
using rbp::RectSize;
using std::accumulate;
using std::min;
using std::cout;
using std::setw;
using std::vector;

AtlasPacker::AtlasPacker() :
        bin_pack(),
        images(),
        canvases(),
        data_export(new JsonExport)
{
}

AtlasPacker::~AtlasPacker()
{
    // free canvases.
    for (int i = 0; i < canvases.size(); ++i)
    {
        delete canvases[i];
        canvases[i] = nullptr;
    }
}

QImage *AtlasPacker::ImageCropAlpha(const QImage *input, Rect &newBounds)
{
    int x = 0, y = 0, w = input->width(), h = input->height();

    // crop top
    for (int row = 0; row < input->height(); ++row)
    {
        uchar result = accumulate(
                input->scanLine(row),
                input->scanLine(row) + input->bytesPerLine(),
                0,
                std::bit_or<uchar>());
        if (result != 0)
        {
            y = row;
            break;
        }
    }

    // crop bottom
    for (int row = input->height() - 1; row >= 0; --row)
    {
        uchar result = accumulate(
                input->scanLine(row),
                input->scanLine(row) + input->bytesPerLine(),
                0,
                std::bit_or<uchar>());
        if (result != 0)
        {
            h = row - y + 1;
            break;
        }
    }

    // crop left
    for (int col = 0; col < input->width(); ++col)
    {
        uchar result = 0;
        for (int row = 0; row < input->height(); ++row)
        {
            const uchar *pixel = input->scanLine(row) + col * 4;
            result |= *(pixel + 0);
            result |= *(pixel + 1);
            result |= *(pixel + 2);
            result |= *(pixel + 3);
        }

        if (result != 0)
        {
            x = col;
            break;
        }
    }

    // crop right
    for (int col = input->width() - 1; col >= 0; --col)
    {
        uchar result = 0;
        for (int row = 0; row < input->height(); ++row)
        {
            const uchar *pixel = input->scanLine(row) + col * 4;
            result |= *(pixel + 0);
            result |= *(pixel + 1);
            result |= *(pixel + 2);
            result |= *(pixel + 3);
        }

        if (result != 0)
        {
            w = col - x + 1;
            break;
        }
    }

    newBounds.x = x;
    newBounds.y = y;
    newBounds.width = w;
    newBounds.height = h;
    return new QImage(input->copy(x, y, w, h));
}

QImage *AtlasPacker::ImageExtrude(QImage *input, ImageInfo &image_info)
{
    int new_width = input->width() + cfg::extrude * 2,
            new_height = input->height() + cfg::extrude * 2;

    QImage *output = new QImage(new_width, new_height, QImage::Format_ARGB32);
    output->fill(0);

    // copy image
    for (int row = 0; row < input->height(); ++row)
    {
        memcpy(output->scanLine(row + cfg::extrude) + cfg::extrude * 4, input->scanLine(row), input->bytesPerLine());
    }
    // ImageExtrude
    for (int i = 0; i < cfg::extrude; ++i)
    {
        // ImageExtrude top
        if (image_info.sprite_source_size.y == 0)
            memcpy(
                    output->scanLine(i) + cfg::extrude * 4,
                    input->scanLine(0),
                    input->bytesPerLine());

        // ImageExtrude bottom
        if (image_info.sprite_source_size.y + image_info.sprite_source_size.height == image_info.source_size.height)
            memcpy(
                    output->scanLine(input->height() + cfg::extrude + i) + cfg::extrude * 4,
                    input->scanLine(input->height() - 1),
                    input->bytesPerLine());

        for (int row = 0; row < input->height(); ++row)
        {
            // ImageExtrude left
            if (image_info.sprite_source_size.x == 0)
                memcpy(
                        output->scanLine(row + cfg::extrude) + i * 4,
                        input->scanLine(row),
                        4);
            // ImageExtrude right
            if (image_info.sprite_source_size.x + image_info.sprite_source_size.width == image_info.source_size.width)
                memcpy(
                        output->scanLine(row + cfg::extrude) + (i + cfg::extrude + input->width()) * 4,
                        input->scanLine(row) + (input->width() - 1) * 4,
                        4);
        }
    }
    return output;
}

void AtlasPacker::ImageDrawImage(QImage &canvas, const QImage &image, int destX, int destY)
{
    for (int row = 0; row < image.height(); ++row)
    {
//        for (int col = 0; col < image.width(); ++col)
//        {
//            canvas.setPixel(
//                    destX + col,
//                    destY + row,
//                    image.pixel(col, row));
//        }
        memcpy(
                canvas.scanLine(row + destY) + destX * 4,
                image.scanLine(row),
                image.bytesPerLine()
        );
    }
}

void AtlasPacker::ExportAtlas(QString relative_path)
{
    if(canvases.empty())
        return;

    // create directories
    QDir out_dir(cfg::outputDirectory.filePath(relative_path));
    out_dir.mkpath("..");

    QString images;

    for (int i = 0; i < canvases.size(); ++i)
    {
        QString file_name = relative_path + (i > 0 ? std::to_string(i).c_str() : "") + "." + cfg::textureFormat;
        QString file_path = cfg::outputDirectory.filePath(file_name);

        if(i > 0)
            images += ',';
        images += file_name;

        bool need_free = false;
        QImage* canvas = canvases[i];
        if(cfg::pixelFormat != canvas->format())
        {
            need_free = true;
            canvas = new QImage(canvas->convertToFormat(cfg::pixelFormat));
        }
        canvas->save(file_path, cfg::textureFormat.toStdString().c_str(), cfg::textureQuality);
        if(need_free)
            delete canvas;
        cout << "SAVE " << file_path.toStdString() << "\n";
    }



    QString data_export_file = cfg::outputDirectory.filePath(relative_path + ".atlas");
    data_export->SetMetaImages(images);
    data_export->Export(data_export_file);
    cout << "SAVE " << data_export_file.toStdString() << "\n\n";
}

bool AtlasPacker::AddImage(QString filename)
{
    QImage *image = new QImage(filename);

    // this indicate <filename> is not a image.
    if (image->isNull())
    {
        return false;
    }

    // convert image format to ARGB32
    if (image->format() != QImage::Format_ARGB32)
    {
        auto new_image = image->convertToFormat(QImage::Format_ARGB32);
        delete image;
        image = new QImage(new_image);
    }

    // print information. We are loading image now.
    cout << "LOAD "
         << file_utils::GetRelativeToInputDirectoryPath(filename).toStdString()
         << "\n";

    ImageInfo image_info;
    image_info.image = image;
    image_info.filename = filename;

    // storage image information
    images.push_back(image_info);

    return true;
}

void AtlasPacker::PackBin()
{
    if(!images.size()) return;

    data_export->Clear();

    std::sort(images.begin(), images.end(), [](const ImageInfo& a, const ImageInfo& b)->bool
    {
        return a.image->width() * a.image->height() > b.image->width() * b.image->height();
    });

    for (ImageInfo &image_info : images)
    {
        QImage *image = image_info.image;

        // set origin image size.
        image_info.source_size.width  = image->width();
        image_info.source_size.height = image->height();

        // crop alpha if needed.
        if (cfg::cropAlpha)
        {
            image = ImageCropAlpha(image, image_info.sprite_source_size);

            if (
                    image_info.sprite_source_size.x != 0 ||
                    image_info.sprite_source_size.y != 0 ||
                    image_info.sprite_source_size.width != image_info.image->width() ||
                    image_info.sprite_source_size.height != image_info.image->height())
                    image_info.trimmed = true;

            delete image_info.image;
            image_info.image = image;
        }
        else
        {
            image_info.sprite_source_size.x = 0;
            image_info.sprite_source_size.y = 0;
            image_info.sprite_source_size.width = image->width();
            image_info.sprite_source_size.height = image->height();
        }

        // extrude if needed.
        if (cfg::extrude)
        {
            image = ImageExtrude(image, image_info.trimmed, image_info);
            delete image_info.image;
            image_info.image = image;
        }
    }

    GenerateAtlas();
}

void AtlasPacker::GenerateAtlas()
{
    // 计算各种排列方式的优劣
    QVector<HeuristicResult> heuristic_results;

    StorageInsertResult(heuristic_results, MaxRectsBinPack::RectBestAreaFit);
    StorageInsertResult(heuristic_results, MaxRectsBinPack::RectBestLongSideFit);
    StorageInsertResult(heuristic_results, MaxRectsBinPack::RectBestShortSideFit);
    StorageInsertResult(heuristic_results, MaxRectsBinPack::RectBottomLeftRule);
    StorageInsertResult(heuristic_results, MaxRectsBinPack::RectContactPointRule);

    // sort by the number of inserted images.
    std::sort(
            heuristic_results.begin(),
            heuristic_results.end(),
            [](const HeuristicResult &a, const HeuristicResult &b) -> bool
            {
                return a.images.size() < b.images.size();
            });
    // stable sort by size of bin.
    std::stable_sort(
            heuristic_results.begin(),
            heuristic_results.end(),
            [](const HeuristicResult &a, const HeuristicResult &b) -> bool
            {
                return a.bin_size.width * a.bin_size.height <
                       b.bin_size.width * b.bin_size.height;
            });

    HeuristicResult best_method = heuristic_results.at(0);
    cout << "SIZE bin(" << best_method.bin_size.width << ", " << best_method.bin_size.height << ") "
         << "canvas(" << best_method.opacity_size.width << ", " << best_method.opacity_size.height << ")\n";

    QImage *canvas = new QImage(best_method.opacity_size.width, best_method.opacity_size.height, QImage::Format_ARGB32);
    canvas->fill(0);

    for (int i = 0; i < best_method.images.size(); ++i)
    {
        Rect& rect = best_method.rects.at(i);
        ImageInfo& image_info = best_method.images.at(i);
        image_info.image_index = canvases.size();

        if (rect.width != image_info.image->width())
        {
            image_info.rotated = true;

            QMatrix rotate;
            rotate.rotate(90);
            QImage rotated_image = image_info.image->transformed(rotate);

            delete image_info.image;

            image_info.image = new QImage(rotated_image);
        }

        cout
                << setw(30) << std::left
                << file_utils::GetRelativeToInputDirectoryPath(image_info.filename).toStdString()
                << "( "
                << setw(5) << rect.x << setw(5) << rect.y
                << setw(5) << rect.width << setw(4) << rect.height
                << ")"
                << "\n";

        image_info.frame.x = rect.x;
        image_info.frame.y = rect.y;
        image_info.frame.width = rect.width;
        image_info.frame.height = rect.height;

        data_export->AddImageDescription(image_info);
        ImageDrawImage(*canvas, *(image_info.image), rect.x, rect.y);

        // remove the image we had processed.
        images.erase(images.begin());
    }

    // storage canvas
    canvases.push_back(canvas);

    // if all images have processed, images's size will be zero.
    if(images.size())
    {
        GenerateAtlas();
    }
}

void AtlasPacker::StorageInsertResult(QVector<HeuristicResult> &heuristicResult,
                                      MaxRectsBinPack::FreeRectChoiceHeuristic method)
{
    // bin's initial size.
    int bin_width = 64;
    int bin_height = 64;

    HeuristicResult heuristic_result;

    while (true)
    {
        // clear before pack.
        heuristic_result.opacity_size.width  = 0;
        heuristic_result.opacity_size.height = 0;
        heuristic_result.images.clear();
        heuristic_result.rects.clear();

        bool can_accommodate = Insert(bin_width, bin_height, heuristic_result, method);
        if (can_accommodate)
            break;

        if (cfg::POT)
        {
            if (bin_height >= bin_width)
                bin_width *= 2;
            else
                bin_height *= 2;
        } else
        {
            float w_ceil_pot = (float) math_utils::CeilPOT(bin_width);
            float h_ceil_pot = (float) math_utils::CeilPOT(bin_height);
            // make w_ceil_pot not equal to h_ceil_pot
            if(w_ceil_pot == h_ceil_pot)
                w_ceil_pot = std::min((float)cfg::maxSize, w_ceil_pot * 2);

            float expect_ratio = w_ceil_pot / h_ceil_pot;
            float now_ratio    = (float) bin_width / (float)bin_height;
            if (now_ratio < expect_ratio)
                bin_width += 32;
            else
                bin_height += 32;
        }

        // limit bin'size lower than max size.
        if (bin_width >= cfg::maxSize && bin_height >= cfg::maxSize)
        {
            heuristic_result.bin_size.width  = cfg::maxSize;
            heuristic_result.bin_size.height = cfg::maxSize;
            break;
        }
        if(bin_width > cfg::maxSize)
            bin_width = cfg::maxSize;
        if(bin_height > cfg::maxSize)
            bin_height = cfg::maxSize;
    }

    heuristicResult.push_back(heuristic_result);
}

bool AtlasPacker::Insert(int bin_width, int bin_height, HeuristicResult &result, rbp::MaxRectsBinPack::FreeRectChoiceHeuristic method)
{
    bin_pack.Init(bin_width + cfg::shapePadding, bin_height + cfg::shapePadding);

    for(ImageInfo& image_info : images)
    {
        // rect to insert must plus shape padding.
        Rect rect = bin_pack.Insert(
                image_info.image->width()  + cfg::shapePadding,
                image_info.image->height() + cfg::shapePadding,
                method);

        if(rect.width == 0)
        {
            return false;
        }

        // after we retrieve bounds in bin, we subtract bounds'size from shape padding.
        rect.width  -= cfg::shapePadding;
        rect.height -= cfg::shapePadding;

        result.opacity_size.width  = std::max(result.opacity_size.width,  rect.x + rect.width);
        result.opacity_size.height = std::max(result.opacity_size.height, rect.y + rect.height);

        result.rects.push_back(rect);
        result.images.push_back(image_info);
    }

    result.bin_size.width  = bin_width;
    result.bin_size.height = bin_height;
    result.occupancy = bin_pack.Occupancy();
    result.method = method;

    return true;
}

bool AtlasPacker::IsEmpty()
{
    return images.empty();
}
