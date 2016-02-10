# image_marker
Web application to mark objects on images.

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

### C++ image processor

Can be found at ./im_processor/src/lib/*

#### How to build the program
Install stuff ...

- C++ (apt-get install build-essential)
- CMake (sudo apt-get install cmake cmake-curses-gui)
- Pkg-config (sudo apt-get install pkg-config)

... and ... 

- Boost (sudo apt-get install libboost-all-dev)
- Eigen3 (sudo apt-get install libeigen3-dev)
- OpenCV 2.x (http://opencv.org/): Ich verwende die src-Version. Es sollte aber auch das Ubuntu-Package funktionieren.
(install instructions: http://docs.opencv.org/2.4/doc/tutorials/introduction/linux_install/linux_install.html)

... then ...

- cd ImageLabelling
- mkdir build
- cd build
- cmake ..
- make

#### How to start the program
./labelImageSoilCover --help
./labelImageSoilCover -d "path/to/input/directory/" -s 100 -c 10

### im_processor c++ native node module
#### How to build node module
- goto im_processor
- type npm install

## deployment
App can be deployed through ansible, run:
```
ansible-playbook deployment/playbook.yml --ask-pass --ask-sudo -u <your-user>
```
You can omit the -u parameter if your local user is equal to remote user at alagoda.at 
The script installs the app at alagoda.at, the frontend is reachable via im.alagoda.at