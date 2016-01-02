
  cmake_minimum_required ( VERSION 2.6 )

  SET(OpenCV_DIR "/home/andreas/opencv-2.4.9/build")

  PROJECT(ImageLabelling)

  FIND_PACKAGE (OpenCV)
  include_directories(${OpenCV_INCLUDE_DIRS})

  find_package(PkgConfig REQUIRED)
  pkg_search_module(EIGEN3 REQUIRED eigen3)
  include_directories(${EIGEN3_INCLUDE_DIRS})

  #find_package(Boost 1.40 COMPONENTS system serialization program_options filesystem REQUIRED)
  find_package(Boost REQUIRED COMPONENTS system serialization program_options filesystem regex)
  include_directories(${Boost_INCLUDE_DIR})


  set(SOURCE_H
    DataContainer.hh
    RecursiveSuperpixelClustering.hh
    Slic.h
    toString.hpp
    ColorMap.hpp
    DataMatrix2D.hpp
    FilesystemUtils.hh
    RecursiveSuperpixelClustering.cc
    SmartPtr.hpp
    Vector.hpp
  )

  set(SOURCE_CPP
    FilesystemUtils.cc
    RecursiveSuperpixelClustering.cc
    Slic.cpp
  )

  SET(BINARY_NAME labelImageSoilCover)
  add_executable(${BINARY_NAME} ${SOURCE_H} ${SOURCE_CPP} labelImageSoilCover.cpp)
  target_link_libraries(${BINARY_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES} )
