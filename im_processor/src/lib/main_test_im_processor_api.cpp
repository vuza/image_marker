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
    api->prepareImg("/mnt/Data/git/image_marker/public/images/image.2.jpg");
    //api->fillSegment("/mnt/Data/git/image_marker/public/images/image.2.jpg", 100, 10, 3, 100, 10, 25);
    //api->fillAllUnlabeledSegments("/mnt/Data/git/image_marker/public/images/image.2.jpg", 3, 100, 10, 25);

    std::cout << "Application finished." << std::endl;
}
