//
// Created by andreas on 02.02.16.
//
#include <iostream>

#include "im_processor_api.h"

using namespace std;


int main(int argc, char *argv[])
{
    std::cout << "Application started." << std::endl;

    Im_processor_api* api = new Im_processor_api();
    string json = api->getImageMatrix("/mnt/Data/git/image_marker/test_images/image.1.jpg");

    std::cout << json << std::endl;

    std::cout << "Application finished." << std::endl;
}
