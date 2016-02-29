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
    * @param imgPath path to image
    * @return imgMatrix in JSON format
    */
    //TODO pass args: superpixel compactness, superpixel size
    std::string getImageMatrix(std::string imgPath);

    /**
     * fills the segment around the x and y coordinate with the given label
     * @param imgPath path to image
     * @param label the label to fill the segment with
     * @return imgMatrix in JSON format
     */
    //TODO pass args: superpixel compactness, superpixel size
    std::string fillSegment(std::string imgPath, int x, int y, int label);

    /**
     * fills all unlabeledSegments with the given label
     * @param imgPath path to image
     * @param label the label to fill the segments with
     * @return imgMatrix in JSON format
     */
    //TODO pass args: superpixel compactness, superpixel size
    std::string fillAllUnlabeledSegments(std::string imgPath, int label);

private:

    void init();

    void initLabelNames(); //TODO do we need label names in api?
    /**
     * loads the given image and its label image into image and image_labels
     * saves the imgPath into image_path
     * @param imgPath path to image
     */
    void loadImage(std::string imgPath);

    /**
     * creates the image matrix in JSON format
     * Precondition: execute init() and loadImage() methods before
     * @param imgPath path to image
     * @return imgMatrix in JSON format
     */
    std::string createImgMatrix();
    /**
     * saves the loaded image and its label file to directory
     * @return true if successfully saved
     */
    bool saveImg();

    vector<string> label_names;

    string image_path;
    string image_name;
    //string image_ext = "jpg";

    string image_labels_path;
    string image_labels_ext = "png";

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