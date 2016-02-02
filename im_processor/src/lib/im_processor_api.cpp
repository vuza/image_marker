//
// Created by andreas on 09.01.16.
//

#include <opencv2/highgui/highgui_c.h>
#include "im_processor_api.h"
#include "FilesystemUtils.hh"
#include "ColorMap.hpp"

/**
 * empty constructor
 */
Im_processor_api::Im_processor_api() { }

/**
 * inits the program
 */
void Im_processor_api::init()
{
    initLabelNames();
    jvis::initColorMapPlants();
}

/**
 * @brief initLabelNames
 */
void Im_processor_api::initLabelNames()
{
    label_names.push_back("Erde");
    label_names.push_back("Kulturpflanze");
    label_names.push_back("Großer Ampfer");
    label_names.push_back("Sonstige lebende organische Masse");
    label_names.push_back("Tote organische Masse");
    label_names.push_back("Steine");
    label_names.push_back("Erde mit grünem Biofilm");
    label_names.push_back("Undefined");
    //last_label = label_names.size()-1;
}

void Im_processor_api::loadImage(string imgName)
{
    string pathToImage = image_directory + imgName;
    image = cv::imread(image_directory + imgName, CV_LOAD_IMAGE_COLOR);

    string labelName = "label_" + imgName.substr(0, imgName.length() - image_ext.length()) + label_ext;
    string pathToLabel = label_directory + labelName;
    image_labels = cv::imread(label_directory + labelName, CV_LOAD_IMAGE_GRAYSCALE);

    if(image_labels.empty() || image.size() != image_labels.size())
        image_labels = cv::Mat_<unsigned char>::ones(image.rows, image.cols)*255;

    image_mask = cv::Mat_<int>::zeros(image.rows, image.cols);

    thr_col = ((double)thr_col_val)/10.;
    spc.setColorThreshold(thr_col);

    slic.segmentSuperpixelSize(image,labels,numlabels, superpixelsize, compactness);
    spc.setSuperpixel(slic.getImageLAB(), labels, numlabels);
    spc.operate(clusters);

    spc.getLabelMap(clusters, spc_labels);
}

std::string Im_processor_api::getImageMatrix(std::string imgName)
{

    init();
    loadImage(imgName);

    string result = "";
    string label_test = "";

    result += string("{\"imgName\":\"") + string(imgName) + string("\",");
        result += string("\"width\":") + to_string(image.rows) + string(",");
        result += string("\"height\":") + to_string(image.cols) + string(",");

        result += "\"data\":{";
            for(int x = 0; x < image.rows; x++)
            {
                for(int y = 0; y < image.cols; y++)
                {
                    result+= string("x:") + to_string(x) + string(",");
                    result+= string("y:") + to_string(y) + string(",");

                    //calculate label from greyColor
                    int label = jvis::getLabel(image_labels(y,x));
                    label_test += to_string(label) + string(",");
                    result+= string("label:") + to_string(label) + string(",");

                    result+= string("isContour: false") + string(","); //TODO check if true or false
                }
            }
            result = result.substr(0, result.length()-1); //remove last ","
        result += string("}");
    result += string("}");
    //std::cout << label_test << std::endl;

    return result;
}

std::string Im_processor_api::fillSegment(std::string imgName, std::string imgMatrix, int x, int y, int label)
{
    return "not implemented";
}

std::string Im_processor_api::fillAllUnlabeledSegments(std::string imgName, std::string imgMatrix, int label)
{
    return "not implemented";
}