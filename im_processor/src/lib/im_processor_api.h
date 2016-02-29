//
// Created by andreas on 09.01.16.
//

#ifndef IMAGELABELLING_IM_PROCESSOR_API_H
#define IMAGELABELLING_IM_PROCESSOR_API_H

#endif //IMAGELABELLING_IM_PROCESSOR_API_H

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "RecursiveSuperpixelClustering.hh"
#include "Slic.h"

#include <string>
#include <vector>

using namespace std;

class Im_processor_api {
public:

    Im_processor_api();

    /**
    * returns a Matrix including Meta information for each Pixel of the image (label, isContour)
    */
    //TODO pass args: superpixel compactness, superpixel size
    std::string getImageMatrix(std::string imgPath);

    /**
     * fills the segment around the x and y coordinate with the given label
     */
    //TODO pass args: superpixel compactness, superpixel size
    std::string fillSegment(std::string imgPath, std::string imgMatrix, int x, int y, int label);

    /**
     * fills all unlabeledSegments with the given label
     */
    //TODO pass args: superpixel compactness, superpixel size
    std::string fillAllUnlabeledSegments(std::string imgPath, std::string imgMatrix, int label);

private:
    void init();
    void initLabelNames();
    void loadImage(std::string imgName);

    vector<string> label_names;

    string image_name;
    string image_ext = "jpg";

    string label_name;
    string label_ext = "png";

    cv::Mat_<cv::Vec3b> image;
    cv::Mat_<unsigned char> image_labels;
    cv::Mat_<int> image_mask;

    //variables for superpixel clustering
    int superpixelsize = 100;
    double compactness = 10;  //Compactness factor. use a value ranging from 10 to 40 depending on your needs. Default is 10
    double thr_col = 2.5;

    int thr_col_val=25;
    int numlabels = 0;
    cv::Mat_<int> labels, spc_labels;
    std::vector<jvis::RecursiveSuperpixelClustering::Cluster> clusters;

    //superpixel clustering
    jvis::Slic slic;
    jvis::RecursiveSuperpixelClustering spc;
};