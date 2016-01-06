# image_marker
Web application to mark objects on images.

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
The script installs the app at alagoda.at, the frontend is reachable via im.alagoda.at# image_marker backend

## How to build the program
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