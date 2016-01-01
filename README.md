# image_marker frontend
Web application to mark objects on images.

# image_marker backend
##How to build the program
Ihr benötigt auf jeden Fall die üblichen Develop-Sachen:

- C++ (apt-get install build-essential)
- CMake (sudo apt-get install cmake cmake-curses-gui)
- Pkg-config (sudo apt-get install pkg-config)

und 

- Boost (sudo apt-get install libboost-all-dev)
- Eigen3 (sudo apt-get install libeigen3-dev)
- OpenCV 2.x (http://opencv.org/): Ich verwende die src-Version. Es sollte aber auch das Ubuntu-Package funktionieren.

Dann:

cd ImageLabelling
mkdir build
cd build
cmake ..
make


## How to start the program
./labelImageSoilCover --help
./labelImageSoilCover -d "path/to/input/directory/" -s 100 -c 10


# development
This repo uses (at least is trying to) git flow, stick to the rules: http://nvie.com/posts/a-successful-git-branching-model/
