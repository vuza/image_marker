//
// Created by Andreas Wittmann on 09.01.16.
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
    * returns a Matrix including Meta information for each Pixel of the image
    * @param imgPath path to image
    * @param superpixelsize - size of a superpixel
    * @param compactness of superpixel (more compact - less neighbours)
    * @param thr_col_val - similarity threshold
    * @return imgMatrix in JSON format
    */
    std::string getImageMatrix(std::string imgPath, int superpixelsize, double compactness, int thr_col_val);

    /**
    * returns a Matrix including Meta information for each Pixel of the image
    * @param imgPath path to image
    * @param superpixelsize - size of a superpixel
    * @param compactness of superpixel (more compact - less neighbours)
    * @param thr_col_val - similarity threshold
    * @return imgMatrix in JSON format
    */
    std::string getImageMatrixCompressed(std::string imgPath, int superpixelsize, double compactness, int thr_col_val);

    /**
     * fills the segment around the x and y coordinate with the given label
     * @param imgPath path to image
     * @param label the label to fill the segment with
     * @param superpixelsize - size of a superpixel
     * @param compactness of superpixel (more compact - less neighbours)
     * @param thr_col_val - similarity threshold
     * @return imgMatrix in JSON format
     */
    std::string fillSegment(std::string imgPath, int x, int y, int label, int superpixelsize, double compactness,
                            int thr_col_val);

    /**
     * fills all unlabeledSegments with the given label
     * @param imgPath path to image
     * @param label the label to fill the segments with
     * @param superpixelsize - size of a superpixel
     * @param compactness of superpixel (more compact - less neighbours)
     * @param thr_col_val - similarity threshold
     * @return imgMatrix in JSON format
     */
    std::string fillAllUnlabeledSegments(std::string imgPath, int label, int superpixelsize, double compactness,
                                         int thr_col_val);

    /**
     * prepares the image
     * creates its label image file its colored label image file if they do not exist and the contours file
     * @param imgPath path to image
     * @param superpixelsize - size of a superpixel
     * @param compactness of superpixel (more compact - less neighbours)
     * @param thr_col_val - similarity threshold
     */
    std::string prepareImg(std::string imgPath, int superpixelsize, double compactness, int thr_col_val);

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
     * loads the given image, its label image and contour image into image and image_labels
     * and calculates the superpixels of the image
     * saves the imgPath into image_path
     * @param imgPath path to image
     * @param superpixelsize - size of a superpixel
     * @param compactness of superpixel (more compact - less neighbours)
     * @param thr_col_val - similarity threshold
     */
    void loadImage(std::string imgPath, int superpixelsize, double compactness, int thr_col_val);

    /**
     * creates the image matrix in JSON format
     * Precondition: init() and loadImage() methods executed before
     * @return imgMatrix in JSON format
     */
    std::string createImgMatrix();

    /**
     * creates the image matrix in own format
     * Precondition: init() and loadImage() methods executed before
     * @return imgMatrix in JSON format
     */
    std::string createImgMatrixCompressed();

    /**
     * saves the loaded image, its label file and the colored label file to directory
     * @return true if successfully saved
     */
    bool saveImg();

    /**
     * create and saves the colored label image to directory
     * @return true if successfully created and saved.
     */
    bool createColoredLabelImg();

    /**
     * create and saves the contours image to directory
     * calcSuperpixels(..) must run before
     * @return true if successfully created and saved.
     */
    bool createContoursImg();

    /**
     * calculates the superpixels of the image
     * image must be loaded before
     * @param superpixelsize - size of a superpixel
     * @param compactness of superpixel (more compact - less neighbours)
     * @param thr_col_val - similarity threshold
     */
    void calcSuperpixels(int superpixelsize, double compactness, int thr_col_val);

    vector<string> label_names;

    string image_path;
    string image_name;
    string image_ext = "jpg";

    string image_labels_path;
    string image_labels_colored_path;
    string image_labels_contours_path;
    string image_labels_colored_contour_path;
    string image_labels_ext = "png";
    string image_labels_colored_ext = "png";
    string image_labels_contours_ext = "png";

    cv::Mat_<cv::Vec3b> image;
    cv::Mat_<unsigned char> image_labels;
    cv::Mat_<cv::Vec4b> image_labels_colored;
    cv::Mat_<int> image_mask;

    //variables for superpixel clustering
    //int superpixelsize = 100;
    //double compactness = 10;  //Compactness factor. use a value ranging from 10 to 40 depending on your needs. Default is 10
    //int thr_col_val=25;

    int numlabels = 0;
    cv::Mat_<int> labels, spc_labels;
    std::vector<jvis::RecursiveSuperpixelClustering::Cluster> clusters;

    //superpixel clustering
    jvis::Slic slic;
    jvis::RecursiveSuperpixelClustering spc;
};