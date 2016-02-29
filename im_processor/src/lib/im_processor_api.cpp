//
// Created by andreas on 09.01.16.
//

#include <opencv2/highgui/highgui_c.h>
#include "im_processor_api.h"
#include "FilesystemUtils.hh"
#include "ColorMap.hpp"
#include <boost/algorithm/string.hpp>

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

void Im_processor_api::loadImage(string imgPath)
{
    vector<string> imgPathSplitted;
    boost::split(imgPathSplitted, imgPath, boost::is_any_of("/"));
    string imgNameWithFileFormat = imgPathSplitted.back();

    vector<string> imgNameSplitted;
    boost::split(imgNameSplitted, imgNameWithFileFormat, boost::is_any_of("."));
    assert(imgNameSplitted.size() == 3); //ex. image.1.jpg

    image_name = imgNameSplitted[0] + "." + imgNameSplitted[1];

    string labelImgPath = "";
    for(int i = 1; i < imgPathSplitted.size() - 1; i++)
    {
        labelImgPath += "/" + imgPathSplitted.at(i);
    }

    labelImgPath += "/" + image_name + "." + label_ext;
    std::cout << labelImgPath << std::endl;

    image = cv::imread(imgPath, CV_LOAD_IMAGE_COLOR);
    image_labels = cv::imread(labelImgPath, CV_LOAD_IMAGE_GRAYSCALE);

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

std::string Im_processor_api::getImageMatrix(std::string imgPath)
{

    init();
    loadImage(imgPath);

    string result = "";
    string label_test = "";

    result += "{\"imgPath\":\"" + imgPath + "\",";
        result += "\"width\":" + to_string(image.rows) + ",";
        result += "\"height\":" + to_string(image.cols) + ",";

        result += "\"data\":[";
            for(int x = 0; x < image.rows; x++)
            {
                for(int y = 0; y < image.cols; y++)
                {
                    result += "{";
                    result+= "\"x\":" + to_string(x) + ",";
                    result+= "\"y\":" + to_string(y) + ",";

                    //calculate label from greyColor
                    int label = jvis::getLabel(image_labels(y,x));
                    label_test += to_string(label) + ",";
                    result+= "\"label\":" + to_string(label) + ",";

                    result+= "\"isContour\": false" + string("},"); //TODO check if true or false
                }
            }
            result = result.substr(0, result.length()-1); //remove last ","
        result += string("]");
    result += string("}");

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