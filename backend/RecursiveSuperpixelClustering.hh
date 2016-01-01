/**
 * $Id: RecursiveSuperpixelClustering.hh 226 2015-04-08 20:05:48Z hannes $
 *
 * Copyright (c) 2014, Johann Prankl
 * @author Johann Prankl (johann.prankl@josephinum.at)
 */


#ifndef JVIS_RECURSIVE_SUPERPIXEL_CLUSTERING_HH
#define JVIS_RECURSIVE_SUPERPIXEL_CLUSTERING_HH

#include <opencv2/core/core.hpp>
#include <stdexcept>
#include <float.h>
#include <iostream>
#include <set>
#include <map>
#include "Vector.hpp"

namespace jvis
{


class RecursiveSuperpixelClustering
{
public:
  class Parameter
  {
  public:
    double thr;                 // similarity threshold
    double thr_sigma;
    double brightness_weight;
    bool use_6L1;               // use an L1 threshold for sigma
    Parameter(const double &_thr=5., const double &_thr_sigma=1., 
              const double &_brightness_weight=.5, bool _use_6L1=false) 
    : thr(_thr), thr_sigma(_thr_sigma),
      brightness_weight(_brightness_weight), use_6L1(_use_6L1) {}
  };
  class Cluster
  {
  public:
    int cnt;
    cv::Vec6d col;
    std::vector<int> neighbours;
    std::vector<int> indices;
    Cluster() : cnt(0), col(cv::Vec6d(0.,0.,0.,0.,0.,0.)) {}
  };

private:
  Parameter param;

  double sqr_thr;
  int numlabels;
  cv::Mat_<cv::Vec3d> im_lab;
  cv::Mat_<int> labels;

  std::vector<bool> mask;
  std::vector<Cluster> superpixel_means;   //superpixel means and neighbour indices

  void setNeighbours();
  void clusterSuperPixel(int seed, std::vector<int> &cluster);
  void getClusterMean(Cluster &cluster);

  inline double sqrDistance(const cv::Vec6d &val1, const cv::Vec6d &val2);
  inline bool isSimilar3L1(const cv::Vec6d &val1, const cv::Vec6d &val2);
  inline bool isSimilar6L1(const cv::Vec6d &val1, const cv::Vec6d &val2);


public:


  RecursiveSuperpixelClustering(const Parameter &_param=Parameter());
  ~RecursiveSuperpixelClustering();

  void setSuperpixel(const cv::Mat_<cv::Vec3d> &_im_lab, const cv::Mat_<int> &_labels, const int &_numlabels);
  void operate(std::vector<Cluster> &clusters);
  void getLabelMap(const std::vector<Cluster> &clusters, cv::Mat_<int> &new_labels);
  void setColorThreshold(double thr) { param.thr = thr; sqr_thr = thr*thr; }
};




/*********************** INLINE METHODES **************************/

/**
 * sqrDistance
 */
inline double RecursiveSuperpixelClustering::sqrDistance(const cv::Vec6d &val1, const cv::Vec6d &val2)
{
  return sqr(val1[0]-val2[0]) + sqr(val1[1]-val2[1]) + sqr(val1[2]-val2[2]);
}

/**
 * isSimilar3L1
 */
inline bool RecursiveSuperpixelClustering::isSimilar3L1(const cv::Vec6d &val1, const cv::Vec6d &val2)
{
  if ( fabs(val1[0]-val2[0])*param.brightness_weight < param.thr && fabs(val1[1]-val2[1]) < param.thr && fabs(val1[2]-val2[2]) < param.thr){
    return true;
  }
  return false;
}

/**
 * isSimilar6L1
 */
inline bool RecursiveSuperpixelClustering::isSimilar6L1(const cv::Vec6d &val1, const cv::Vec6d &val2)
{
  if ( fabs(val1[0]-val2[0])*param.brightness_weight < param.thr && 
       fabs(val1[1]-val2[1]) < param.thr && fabs(val1[2]-val2[2]) < param.thr &&
       fabs(val1[3]-val2[3]) < param.thr_sigma && 
       fabs(val1[4]-val2[4]) < param.thr_sigma && fabs(val1[5]-val2[5]) < param.thr_sigma)
    return true;
  return false;
}



}

#endif

