//
// Created by andreas on 09.01.16.
//

#ifndef IMAGELABELLING_IM_PROCESSOR_API_H
#define IMAGELABELLING_IM_PROCESSOR_API_H

#endif //IMAGELABELLING_IM_PROCESSOR_API_H

#include <string>
#include <vector>

using namespace std;

class im_processor_api {
public:

    std::string getNextImgPath(std::string actualImgPath);

    /**
    * returns a Matrix including Meta information for each Pixel of the image (label, isContour)
    */
    //TODO pass args: superpixel compactness, superpixel size
    std::string getImageMatrix(std::string imgName);

    /**
     * fills the segment around the x and y coordinate with the given label
     */
    //TODO pass args: superpixel compactness, superpixel size
    std::string fillSegment(std::string imgName, Matrix imgMatrix, int x, int y, int label);

    /**
     * fills all unlabeledSegments with the given label
     */
    //TODO pass args: superpixel compactness, superpixel size
    std::string fillAllUnlabeledSegments(std::string imgName, Matrix imgMatrix, int label);

private:
    void init();
    void initLabelNames();

    vector<string> label_names;

    string image_directory = "./test_images/";
    string image_name = "image";
    string image_ext = "jpg";

    string label_name = "labels";
    string label_ext = "png";

    vector<std::string> label_files;
    vector<std::string> image_files;
};