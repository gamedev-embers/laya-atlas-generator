# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/clion/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/survivor/Documents/cpp/atlas-generator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel

# Include any dependencies generated for this target.
include CMakeFiles/atlas_generator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/atlas_generator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/atlas_generator.dir/flags.make

CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o: ../RectangleBinPack/GuillotineBinPack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/GuillotineBinPack.cpp

CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/GuillotineBinPack.cpp > CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.i

CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/GuillotineBinPack.cpp -o CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.s

CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.requires

CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.provides: CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.provides

CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o


CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o: ../RectangleBinPack/MaxRectsBinPack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/MaxRectsBinPack.cpp

CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/MaxRectsBinPack.cpp > CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.i

CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/MaxRectsBinPack.cpp -o CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.s

CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.requires

CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.provides: CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.provides

CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o


CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o: ../RectangleBinPack/Rect.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/Rect.cpp

CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/Rect.cpp > CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.i

CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/Rect.cpp -o CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.s

CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.requires

CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.provides: CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.provides

CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o


CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o: ../RectangleBinPack/ShelfBinPack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/ShelfBinPack.cpp

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/ShelfBinPack.cpp > CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.i

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/ShelfBinPack.cpp -o CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.s

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.requires

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.provides: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.provides

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o


CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o: ../RectangleBinPack/ShelfNextFitBinPack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/ShelfNextFitBinPack.cpp

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/ShelfNextFitBinPack.cpp > CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.i

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/ShelfNextFitBinPack.cpp -o CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.s

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.requires

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.provides: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.provides

CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o


CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o: ../RectangleBinPack/SkylineBinPack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/SkylineBinPack.cpp

CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/SkylineBinPack.cpp > CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.i

CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/RectangleBinPack/SkylineBinPack.cpp -o CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.s

CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.requires

CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.provides: CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.provides

CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o


CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o: ../AtlasPacker.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o -c /home/survivor/Documents/cpp/atlas-generator/AtlasPacker.cc

CMakeFiles/atlas_generator.dir/AtlasPacker.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/AtlasPacker.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/AtlasPacker.cc > CMakeFiles/atlas_generator.dir/AtlasPacker.cc.i

CMakeFiles/atlas_generator.dir/AtlasPacker.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/AtlasPacker.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/AtlasPacker.cc -o CMakeFiles/atlas_generator.dir/AtlasPacker.cc.s

CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.requires

CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.provides: CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.provides

CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.provides.build: CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o


CMakeFiles/atlas_generator.dir/Configuration.cc.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/Configuration.cc.o: ../Configuration.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/atlas_generator.dir/Configuration.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/Configuration.cc.o -c /home/survivor/Documents/cpp/atlas-generator/Configuration.cc

CMakeFiles/atlas_generator.dir/Configuration.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/Configuration.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/Configuration.cc > CMakeFiles/atlas_generator.dir/Configuration.cc.i

CMakeFiles/atlas_generator.dir/Configuration.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/Configuration.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/Configuration.cc -o CMakeFiles/atlas_generator.dir/Configuration.cc.s

CMakeFiles/atlas_generator.dir/Configuration.cc.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/Configuration.cc.o.requires

CMakeFiles/atlas_generator.dir/Configuration.cc.o.provides: CMakeFiles/atlas_generator.dir/Configuration.cc.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/Configuration.cc.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/Configuration.cc.o.provides

CMakeFiles/atlas_generator.dir/Configuration.cc.o.provides.build: CMakeFiles/atlas_generator.dir/Configuration.cc.o


CMakeFiles/atlas_generator.dir/main.cc.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/main.cc.o: ../main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/atlas_generator.dir/main.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/main.cc.o -c /home/survivor/Documents/cpp/atlas-generator/main.cc

CMakeFiles/atlas_generator.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/main.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/main.cc > CMakeFiles/atlas_generator.dir/main.cc.i

CMakeFiles/atlas_generator.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/main.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/main.cc -o CMakeFiles/atlas_generator.dir/main.cc.s

CMakeFiles/atlas_generator.dir/main.cc.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/main.cc.o.requires

CMakeFiles/atlas_generator.dir/main.cc.o.provides: CMakeFiles/atlas_generator.dir/main.cc.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/main.cc.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/main.cc.o.provides

CMakeFiles/atlas_generator.dir/main.cc.o.provides.build: CMakeFiles/atlas_generator.dir/main.cc.o


CMakeFiles/atlas_generator.dir/Utils.cc.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/Utils.cc.o: ../Utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/atlas_generator.dir/Utils.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/Utils.cc.o -c /home/survivor/Documents/cpp/atlas-generator/Utils.cc

CMakeFiles/atlas_generator.dir/Utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/Utils.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/Utils.cc > CMakeFiles/atlas_generator.dir/Utils.cc.i

CMakeFiles/atlas_generator.dir/Utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/Utils.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/Utils.cc -o CMakeFiles/atlas_generator.dir/Utils.cc.s

CMakeFiles/atlas_generator.dir/Utils.cc.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/Utils.cc.o.requires

CMakeFiles/atlas_generator.dir/Utils.cc.o.provides: CMakeFiles/atlas_generator.dir/Utils.cc.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/Utils.cc.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/Utils.cc.o.provides

CMakeFiles/atlas_generator.dir/Utils.cc.o.provides.build: CMakeFiles/atlas_generator.dir/Utils.cc.o


CMakeFiles/atlas_generator.dir/JsonExport.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/JsonExport.cpp.o: ../JsonExport.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/atlas_generator.dir/JsonExport.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/JsonExport.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/JsonExport.cpp

CMakeFiles/atlas_generator.dir/JsonExport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/JsonExport.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/JsonExport.cpp > CMakeFiles/atlas_generator.dir/JsonExport.cpp.i

CMakeFiles/atlas_generator.dir/JsonExport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/JsonExport.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/JsonExport.cpp -o CMakeFiles/atlas_generator.dir/JsonExport.cpp.s

CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.requires

CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.provides: CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.provides

CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/JsonExport.cpp.o


CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o: CMakeFiles/atlas_generator.dir/flags.make
CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o: atlas_generator_automoc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o -c /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/atlas_generator_automoc.cpp

CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/atlas_generator_automoc.cpp > CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.i

CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/atlas_generator_automoc.cpp -o CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.s

CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.requires:

.PHONY : CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.requires

CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.provides: CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.requires
	$(MAKE) -f CMakeFiles/atlas_generator.dir/build.make CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.provides.build
.PHONY : CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.provides

CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.provides.build: CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o


# Object files for target atlas_generator
atlas_generator_OBJECTS = \
"CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o" \
"CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o" \
"CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o" \
"CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o" \
"CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o" \
"CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o" \
"CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o" \
"CMakeFiles/atlas_generator.dir/Configuration.cc.o" \
"CMakeFiles/atlas_generator.dir/main.cc.o" \
"CMakeFiles/atlas_generator.dir/Utils.cc.o" \
"CMakeFiles/atlas_generator.dir/JsonExport.cpp.o" \
"CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o"

# External object files for target atlas_generator
atlas_generator_EXTERNAL_OBJECTS =

atlas_generator: CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o
atlas_generator: CMakeFiles/atlas_generator.dir/Configuration.cc.o
atlas_generator: CMakeFiles/atlas_generator.dir/main.cc.o
atlas_generator: CMakeFiles/atlas_generator.dir/Utils.cc.o
atlas_generator: CMakeFiles/atlas_generator.dir/JsonExport.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o
atlas_generator: CMakeFiles/atlas_generator.dir/build.make
atlas_generator: /opt/Qt5.9.0/5.9/gcc_64/lib/libQt5Gui.so.5.9.0
atlas_generator: /opt/Qt5.9.0/5.9/gcc_64/lib/libQt5Core.so.5.9.0
atlas_generator: CMakeFiles/atlas_generator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable atlas_generator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/atlas_generator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/atlas_generator.dir/build: atlas_generator

.PHONY : CMakeFiles/atlas_generator.dir/build

CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/RectangleBinPack/GuillotineBinPack.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/RectangleBinPack/MaxRectsBinPack.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/RectangleBinPack/Rect.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfBinPack.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/RectangleBinPack/ShelfNextFitBinPack.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/RectangleBinPack/SkylineBinPack.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/AtlasPacker.cc.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/Configuration.cc.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/main.cc.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/Utils.cc.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/JsonExport.cpp.o.requires
CMakeFiles/atlas_generator.dir/requires: CMakeFiles/atlas_generator.dir/atlas_generator_automoc.cpp.o.requires

.PHONY : CMakeFiles/atlas_generator.dir/requires

CMakeFiles/atlas_generator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/atlas_generator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/atlas_generator.dir/clean

CMakeFiles/atlas_generator.dir/depend:
	cd /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/survivor/Documents/cpp/atlas-generator /home/survivor/Documents/cpp/atlas-generator /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel /home/survivor/Documents/cpp/atlas-generator/cmake-build-minsizerel/CMakeFiles/atlas_generator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/atlas_generator.dir/depend

