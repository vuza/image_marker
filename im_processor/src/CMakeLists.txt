  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  cmake_minimum_required ( VERSION 2.6 )

  #SET(OpenCV_DIR "/home/andreas/opencv-2.4.9/build")

  PROJECT(main_test_im_processor_api)

  FIND_PACKAGE (OpenCV)
  include_directories(${OpenCV_INCLUDE_DIRS})

  find_package(PkgConfig REQUIRED)
  pkg_search_module(EIGEN3 REQUIRED eigen3)
  include_directories(${EIGEN3_INCLUDE_DIRS})

  #find_package(Boost 1.40 COMPONENTS system serialization program_options filesystem REQUIRED)
  find_package(Boost REQUIRED COMPONENTS system serialization program_options filesystem regex)
  include_directories(${Boost_INCLUDE_DIR})


  set(SOURCE_H
          lib/DataContainer.hh
          lib/RecursiveSuperpixelClustering.hh
          lib/Slic.h
          lib/toString.hpp
          lib/ColorMap.hpp
          lib/DataMatrix2D.hpp
          lib/FilesystemUtils.hh
          lib/SmartPtr.hpp
          lib/Vector.hpp
          lib/im_processor_api.h
          )

  set(SOURCE_CPP
          lib/FilesystemUtils.cc
          lib/RecursiveSuperpixelClustering.cc
          lib/ColorMap.cc
          lib/Slic.cpp
          lib/im_processor_api.cpp
          lib/main_test_im_processor_api.cpp)

  SET(BINARY_NAME main_test_im_processor_api)
  add_executable(${BINARY_NAME} ${SOURCE_H} ${SOURCE_CPP} lib/main_test_im_processor_api.cpp)
  target_link_libraries(${BINARY_NAME} ${OpenCV_LIBS} ${Boost_LIBRARIES} )
