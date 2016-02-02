# image_marker

Web application to mark objects on images. This repo includes C++ Code for image processing, Node.js server and Marionette.js web client.

```
image_processor
|   README.md
|   ...
|   package.json // holds all information to install, test and run Node.js server
|
├---deployment // ansible deployment scripts are stored here
|   |   playbook.yml
|
├---im_processor // Node.js/C++ image processing module
|   ├---build
|   └---src
|       └----lib // stores original C++ image processing program!
|
└---public // Marionette.js frontend is stored here
    ├---css
    ├---images
    ├---scripts
    |   index.html
```

## development

### Git flow
This repo uses (at least is trying to) git flow, stick to the rules: http://nvie.com/posts/a-successful-git-branching-model/

### Semver
The webapp (client and frontend) is using Semantic Versioning (http://semver.org/), be sure to update version in package.json correctly.

## deployment
App can be deployed through ansible, run:
```
ansible-playbook deployment/playbook.yml --ask-pass --ask-sudo -u <your-user>
```
You can omit the -u parameter if your local user is equal to remote user at alagoda.at 
The script installs the app at alagoda.at, the frontend is reachable via im.alagoda.at

# development
This repo uses (at least is trying to) git flow, stick to the rules: http://nvie.com/posts/a-successful-git-branching-model/

## C++ image processor

Can be found at ./im_processor/src/lib/*

### How to build the program
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


### How to start the program
./labelImageSoilCover --help
./labelImageSoilCover -d "path/to/input/directory/" -s 100 -c 10

### api (not implemented)
```c++
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
