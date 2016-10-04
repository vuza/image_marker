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

    api->prepareImg("/mnt/Data/git/image_marker/public/images/image.1.jpg", 100, 10, 25);
    string jsonMatrix1 = api->getImageMatrix("/mnt/Data/git/image_marker/public/images/image.1.jpg", 100, 10, 25);
    string compressedMatrix1 = api->getImageMatrixCompressed("/mnt/Data/git/image_marker/public/images/image.1.jpg", 100, 10, 25);

    //api->prepareImg("/mnt/Data/git/image_marker/public/images/image.2.jpg", 100, 10, 25);
    //string jsonMatrix2 = api->getImageMatrix("/mnt/Data/git/image_marker/public/images/image.2.jpg", 100, 10, 25);
    //string compressedMatrix2 = api->getImageMatrixCompressed("/mnt/Data/git/image_marker/public/images/image.2.jpg", 100, 10, 25);

    //api->prepareImg("/mnt/Data/git/image_marker/public/images/image.3.jpg", 100, 10, 25);
    //string jsonMatrix3 = api->getImageMatrix("/mnt/Data/git/image_marker/public/images/image.3.jpg", 100, 10, 25);
    //string compressedMatrix3 = api->getImageMatrixCompressed("/mnt/Data/git/image_marker/public/images/image.3.jpg", 100, 10, 25);

    std::cout << "jsonMatrix1 Length: " << jsonMatrix1.length() << std::endl;
    std::cout << "compressedMatrix1 Length: " << compressedMatrix1.length() << std::endl;
    /*
    std::cout << "jsonMatrix2 Length: " << jsonMatrix2.length() << std::endl;
    std::cout << "compressedMatrix2 Length: " << compressedMatrix2.length() << std::endl;

    std::cout << "jsonMatrix3 Length: " << jsonMatrix3.length() << std::endl;
    std::cout << "compressedMatrix3 Length: " << compressedMatrix3.length() << std::endl;
    */
    //api->fillAllUnlabeledSegments("/mnt/Data/git/image_marker/public/images/image.1.jpg", 3, 100, 10, 25);
    //api->fillSegment("/mnt/Data/git/image_marker/public/images/image.1.jpg", 500, 10, 5, 100, 10, 25);


    std::cout << "Application finished." << std::endl;
}
