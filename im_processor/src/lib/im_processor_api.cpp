//
// Created by andreas on 09.01.16.
//

#include "im_processor_api.h"
#include "FilesystemUtils.hh"
#include "ColorMap.hpp"

/**
 * inits the program
 */
void im_processor_api::init()
{
    initLabelNames();
    jvis::initColorMapPlants();

    /* i don't need to load all images
    // load files...
    std::string so_far = "";
    std::string pattern = image_name+ std::string(".*.") + image_ext;

    jvis::utils::getFilesInDirectory(image_directory,image_files,so_far,pattern,false);

    //init label files
    label_files = image_files;
    for (unsigned i=0; i<image_files.size(); i++)
    {
        boost::replace_last (label_files[i], image_ext, label_ext);
        boost::replace_last (label_files[i], image_name, label_name);
    }
    */
}

/**
 * returns the path of the next image
 */
string im_processor_api::getNextImgPath(string actualImgPath)
{

    if(!boost::regex_match(actualImgPath, image_path_regex)) {
        //TODO
        return null;
    }else{
        string imgNumberStr = actualImgPath.substr(image_name.size()+1, (actualImgPath.size() - image_ext.size()+1));
        int imgNumber = std::stoi(imgNumberStr); //TODO HIER WEITERMACHEN
        if(image_files.size() > imgNumber) {
            return image_name + "." + imgNumber+1 + "." + image_ext;
        }
    }

}

/**
 * @brief initLabelNames
 */
void im_processor_api::initLabelNames()
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