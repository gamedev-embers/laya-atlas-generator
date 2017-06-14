cmake_minimum_required(VERSION 3.7)
project(atlas_generator)

set(CMAKE_PREFIX_PATH /opt/Qt5.8.0/5.8/gcc_64/lib/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        RectangleBinPack/GuillotineBinPack.cpp
        RectangleBinPack/MaxRectsBinPack.cpp
        RectangleBinPack/Rect.cpp
        RectangleBinPack/ShelfBinPack.cpp
        RectangleBinPack/ShelfNextFitBinPack.cpp
        RectangleBinPack/SkylineBinPack.cpp
        AtlasPacker.cc
        Configuration.cc
        main.cc
        Utils.cc
        DataExport.h
        JsonExport.cpp)

add_executable(atlas_generator ${SOURCE_FILES})
target_link_libraries(atlas_generator Qt5::Widgets)
