# image_marker frontend
Web application to mark objects on images.

# image_marker c++
##How to build the program
Ihr benötigt auf jeden Fall die üblichen Develop-Sachen:

- C++ (apt-get install build-essential)
- CMake (sudo apt-get install cmake cmake-curses-gui)
- Pkg-config (sudo apt-get install pkg-config)

und 

- Boost (sudo apt-get install libboost-all-dev)
- Eigen3 (sudo apt-get install libeigen3-dev)
- OpenCV 2.x (http://opencv.org/): Ich verwende die src-Version. Es sollte aber auch das Ubuntu-Package funktionieren.
(install instructions: http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html)

Dann:

cd ImageLabelling
mkdir build
cd build
cmake ..
make


## How to start the program
./labelImageSoilCover --help
./labelImageSoilCover -d "path/to/input/directory/" -s 100 -c 10

## c++ api (not implemented)
```c++
/**
 * returns the path of the next image
 */
String nextImgPath getNextImg(String actualImgName) 

/**
 * returns the path of the previous image
 */
String prevImgPath getPrevImg(String actualImgName)

/**
 * returns a Matrix including Meta information for each Pixel of the image (label, isContour)
 */
Matrix imgMatrix getImageMatrix(String imgName)

/**
 * fills the segment around the x and y coordinate with the given label
 */
Matrix imgMatrix fillSegment(String imgName, Matrix imgMatrix, int x, int y, int label) 

/**
 * fills all unlabeledSegments with the given label
 */
Matrix imgMatrix fillAllUnlabeledSegments(String imgName, Matrix imgMatrix, int label)
```
# development
This repo uses (at least is trying to) git flow, stick to the rules: http://nvie.com/posts/a-successful-git-branching-model/