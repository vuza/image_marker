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

## Development

### Frontend
- run npm install
- config your webserver to point to public/index.html or use ansible script for deployment (see "deployment")

### Backend
#### Git flow
This repo uses (at least is trying to) git flow, stick to the rules: http://nvie.com/posts/a-successful-git-branching-model/

#### Semver
The webapp (client and frontend) is using Semantic Versioning (http://semver.org/), be sure to update version in package.json correctly.

#### C++ image processor

Can be found at ./im_processor/src/lib/*

##### How to build the program
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

##### How to start the program
./labelImageSoilCover --help
./labelImageSoilCover -d "path/to/input/directory/" -s 100 -c 10

#### im_processor c++ native node module
##### How to build node module
- goto im_processor
- type npm install

## Deployment
### Dependencies
- Webservice for serving static files, nginx is recommended. It has to point to this repository's public folder
- Node.js 5.x
- cmake, boost, eigen3 and openCV, see ["C++ image processor/How to build the program"](#how-to-build-the-program)
- A user named "deploy" with write access to /var/node has to exist on webserver
- See config at deploy/vars/all.yml!
- Add webserver address to hosts file

### ansible
App can be deployed through ansible, run:
```
ansible-playbook deployment/playbook.yml -u <your-user> --extra-vars "target=<your.webserver.com>"
```
You can omit the -u parameter if your local user is equal to remote user at <your.webserver.com>, ansible will always ask you for sudo and ssh password.
The script installs the app at <your.webserver.com>, you will need to config a webserver to serve the static files by your self

### Nginx Setup
We use ngnix for serving static frontend files. Make sure html push-state URLs work properly. Example nginx setup:

```
server {
    listen 80;
    listen [::]:80;
    server_name im.localhost;
    location / {
        root /home/marlon/Documents/Bac/prototype/public/;
        index index.html;
        if (!-e $request_filename){
            rewrite ^(.*)$ /index.html break;
        }
    }
}
```

## Guidelines
### Exploited Errors
- 0: 'No unlocked image found'
- 2: 'Image [name] not found'
- 3: 'No images found at all'

### Add Images
Images have to have the following file format: image.[name].[jpg/png]
This is an implicit requirement, the programm does not check it (yet), but wont work, if file format is different.