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
    //string json = api->getImageMatrix("/mnt/Data/git/image_marker/test_images/image.4.jpg", 100, 10, 25);
    //api->fillSegment("/mnt/Data/git/image_marker/test_images/image.4.jpg", 59, 82, 2, 100, 10, 25);
    //std::cout << "fillSegment finished" << std::endl;
    //api->fillSegment("/mnt/Data/git/image_marker/test_images/image.2.jpg", 10, 11, 1, 100, 10, 25);
    //std::cout << "fillSegment finished" << std::endl;
    api->fillAllUnlabeledSegments("/mnt/Data/git/image_marker/test_images/image.4.jpg", 4, 100, 10, 25);
    std::cout << "fillAllUnlabeledSegments finished" << std::endl;

    std::cout << "Application finished." << std::endl;
}
