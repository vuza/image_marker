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

std::string Im_processor_api::getImageMatrix(std::string imgPath, int superpixelsize, double compactness, int thr_col_val)
{
    init();
    loadImage(imgPath, superpixelsize, compactness, thr_col_val);
    return createImgMatrix();
}

std::string Im_processor_api::fillSegment(std::string imgPath, int x, int y, int label, int superpixelsize, double compactness, int thr_col_val)
{
    init();
    loadImage(imgPath, superpixelsize, compactness, thr_col_val);

    if (label == label_names.size()-1) label=255;

    if (image_labels(y,x)!=label)
    {
        int mcnt = image_mask(y,x) + 1;

        int width = image_labels.cols;
        int height = image_labels.rows;

        image_mask(y,x) = mcnt;

        int queue_idx = 0;
        std::vector<cv::Point2i> queue;
        queue.resize(1);
        queue[0] = cv::Point2i(x,y);

        image_labels(y,x) = label;
        int la = spc_labels(y,x);

        // start clustering
        while (queue_idx < ((int)queue.size()))
        {
            // extract current index
            cv::Point2i &point = queue.at(queue_idx);
            queue_idx++;

            for(int v=point.y-1; v<=point.y+1; v++)
            {
                for (int u=point.x-1; u<=point.x+1; u++)
                {
                    if ( (v < 0) || (u < 0) || (v >= height) || (u >= width) )
                        continue;

                    int idx = v*width + u;

                    // not valid or not used point
                    if (image_mask(idx)==mcnt)
                        continue;

                    // we can add this point to the plane
                    if ( la==spc_labels(idx) )
                    {
                        queue.push_back(cv::Point2i(u,v));
                        image_labels(idx) = label;
                        image_mask(idx) = mcnt;
                    }
                }
            }
        }
        saveImg();
    }

    return createImgMatrix();
}

std::string Im_processor_api::fillAllUnlabeledSegments(std::string imgPath, int label, int superpixelsize, double compactness, int thr_col_val)
{
    init();
    loadImage(imgPath, superpixelsize, compactness, thr_col_val);

    for (int v=0; v<image_labels.rows; v++)
    {
        for (int u=0; u<image_labels.cols; u++)
        {
            if (image_labels(v,u)==255)
            {
                image_labels(v,u) = label;
            }
        }
    }
    saveImg();
    return createImgMatrix();
}

std::string Im_processor_api::prepareImg(std::string imgPath, int superpixelsize, double compactness, int thr_col_val)
{
    init();
    loadImage(imgPath, superpixelsize, compactness, thr_col_val);

    return "";
}

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
}

void Im_processor_api::loadImage(string imgPath)
{
    image_path = imgPath;

    vector<string> imgPathSplitted;
    boost::split(imgPathSplitted, imgPath, boost::is_any_of("/"));
    string imgNameWithFileFormat = imgPathSplitted.back();

    vector<string> imgNameSplitted;
    boost::split(imgNameSplitted, imgNameWithFileFormat, boost::is_any_of("."));
    assert(imgNameSplitted.size() == 3); //ex. image.1.jpg

    string imgNumber = imgNameSplitted[1];
    image_name = imgNameSplitted[0] + "." + imgNameSplitted[1];

    string labelImgPath = "";
    for(int i = 1; i < imgPathSplitted.size() - 1; i++)
    {
        labelImgPath += "/" + imgPathSplitted.at(i);
    }
    labelImgPath += "/labels/";
    image_labels_colored_path = labelImgPath;
    image_labels_contours_path = labelImgPath;

    labelImgPath += "label." + imgNumber + "." + image_labels_ext;
    image_labels_path = labelImgPath;

    image_labels_colored_path += "label_colored." + imgNumber + "." + image_labels_colored_ext;
    image_labels_contours_path += "label_contours." + imgNumber + "." + image_labels_contours_ext;

    image = cv::imread(imgPath, CV_LOAD_IMAGE_COLOR);
    image_labels = cv::imread(image_labels_path, CV_LOAD_IMAGE_GRAYSCALE);
    image_labels_colored = cv::imread(image_labels_colored_path, CV_LOAD_IMAGE_UNCHANGED); //load with alpha channel

    if(image_labels.empty() || image.size() != image_labels.size())
    {
        image_labels = cv::Mat_<unsigned char>::ones(image.rows, image.cols)*255;
        createColoredLabelImg();
    }

    if(image_labels_colored.empty() && !image_labels.empty())
        createColoredLabelImg();

    image_mask = cv::Mat_<int>::zeros(image.rows, image.cols);
}

void Im_processor_api::loadImage(string imgPath, int superpixelsize, double compactness, int thr_col_val)
{
    loadImage(imgPath);
    calcSuperpixels(superpixelsize, compactness, thr_col_val);
    createContoursImg();
}

std::string Im_processor_api::createImgMatrix()
{
    string result = "";

    result += "{\"imgPath\":\"" + image_path + "\",";
    result += "\"width\":" + std::to_string(image.rows) + ",";
    result += "\"height\":" + std::to_string(image.cols) + ",";

    result += "\"data\":[";
    for(int x = 0; x < image.rows; x++)
    {
        for(int y = 0; y < image.cols; y++)
        {
            result += "{";
            result+= "\"x\":" + std::to_string(x) + ",";
            result+= "\"y\":" + std::to_string(y) + ",";

            //calculate label from greyColor
            int label = jvis::getLabel(image_labels(y,x));
            result+= "\"label\":" + std::to_string(label) + "},";

            //result+= "\"isContour\": false" + string("},"); //TODO check if true or false
        }
    }
    result = result.substr(0, result.length()-1); //remove last ","
    result += string("]");
    result += string("}");

    return result;
}

bool Im_processor_api::saveImg()
{
    cv::imwrite(image_labels_path, image_labels);
    createColoredLabelImg();
    return true; //TODO check if imwrite was succesful.
}

bool Im_processor_api::createColoredLabelImg()
{
    image_labels_colored = cv::Mat_<cv::Vec4b>::zeros(image.rows, image.cols);

    for (int v=0; v<image_labels.rows; v++)
    {
        for (int u=0; u<image_labels.cols; u++)
        {
            unsigned char label = image_labels(v,u);
            if (label==255) continue;

            cv::Vec3b color = jvis::getCol(label);
            image_labels_colored.at<cv::Vec4b>(v,u) = cv::Vec4b(color.val[0], color.val[1], color.val[2], 255);
        }
    }

    cv::imwrite(image_labels_colored_path, image_labels_colored);
}

bool Im_processor_api::createContoursImg()
{
    cv::Mat_<cv::Vec4b> image_labels_contours = cv::Mat_<cv::Vec4b>::zeros(image.rows, image.cols);
    slic.drawContours(image_labels_contours, spc_labels, 255, 0, 0);
    cv::imwrite(image_labels_contours_path, image_labels_contours);
}

void Im_processor_api::calcSuperpixels(int superpixelsize, double compactness, int thr_col_val)
{
    double thr_col = ((double)thr_col_val)/10.;
    spc.setColorThreshold(thr_col);

    slic.segmentSuperpixelSize(image,labels,numlabels, superpixelsize, compactness);
    spc.setSuperpixel(slic.getImageLAB(), labels, numlabels);
    spc.operate(clusters);

    spc.getLabelMap(clusters, spc_labels);
}