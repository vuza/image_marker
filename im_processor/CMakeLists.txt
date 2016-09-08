cmake_minimum_required(VERSION 3.2)

# Name of the project (will be the name of the plugin)
project (im_processor)

# OpenCV
FIND_PACKAGE (OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

# Boost dependency
find_package(Boost REQUIRED COMPONENTS system serialization program_options filesystem regex)
include_directories(${Boost_INCLUDE_DIR})

# Essential include files to build a node addon,
# you should add this line in every CMake.js based project.
include_directories(${CMAKE_JS_INC})

# Declare the location of the source files
#file(GLOB SOURCE_FILES "src/*.cc" "src/*.h" "src/lib/*.cc" "src/lib/*.hpp" "src/lib/*.cpp" "src/lib/*.h")
file(GLOB SOURCE_FILES
        "src/lib/DataContainer.hh"
        "src/lib/RecursiveSuperpixelClustering.hh"
        "src/lib/Slic.h"
        "src/lib/toString.hpp"
        "src/lib/ColorMap.hpp"
        "src/lib/DataMatrix2D.hpp"
        "src/lib/FilesystemUtils.hh"
        "src/lib/SmartPtr.hpp"
        "src/lib/Vector.hpp"
        "src/lib/im_processor_api.h"
        "src/prepareImg.h"
        "src/getImageMatrix.h"
        "src/fillSegment.h"
        "src/fillAllUnlabeledSegments.h"
        "src/lib/FilesystemUtils.cc"
        "src/lib/RecursiveSuperpixelClustering.cc"
        "src/lib/ColorMap.cc"
        "src/lib/Slic.cpp"
        "src/lib/im_processor_api.cpp"
        "src/prepareImg.cc"
        "src/getImageMatrix.cc"
        "src/fillSegment.cc"
        "src/fillAllUnlabeledSegments.cc"
        "src/im_processor.cc"
        )

# This line will tell CMake that we're building a shared library
# from the above source files
# named after the project's name
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# This line will give our library file a .node extension without any "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

# Essential library files to link to a node addon,
# you should add this line in every CMake.js based project.
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${OpenCV_LIBS} ${Boost_LIBRARIES})