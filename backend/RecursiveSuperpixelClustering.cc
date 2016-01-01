/**
 * $Id: RecursiveSuperpixelClustering.cc 223 2015-04-02 15:59:03Z hannes $
 *
 * Copyright (c) 2014, Johann Prankl
 * @author Johann Prankl (johann.prankl@josephinum.at)
 */


#include "RecursiveSuperpixelClustering.hh"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <set>


namespace jvis 
{

using namespace std;


/********************** RecursiveSuperpixelClustering ************************
 * Constructor/Destructor
 */
RecursiveSuperpixelClustering::RecursiveSuperpixelClustering(const Parameter &_param)
 : param(_param)
{
  sqr_thr = param.thr*param.thr;
}

RecursiveSuperpixelClustering::~RecursiveSuperpixelClustering()
{
}


/**
 * clusterPoints
 */
void RecursiveSuperpixelClustering::clusterSuperPixel(int seed, std::vector<int> &cluster)
{
  cluster.clear();
  if (mask[seed]) return;

  int idx=0;
  cluster.push_back(seed);
  mask[seed] = true;

  while (((int)cluster.size()) > idx)
  {
    const Cluster &cl = superpixel_means[cluster[idx]];

    for (unsigned i=0; i<cl.neighbours.size(); i++)
    {
      if (!mask[cl.neighbours[i]])
      {
        //if ( sqrDistance(cl.col, superpixel_means[cl.neighbours[i]].col) < sqr_thr )
        if (isSimilar3L1(cl.col, superpixel_means[cl.neighbours[i]].col) || (param.use_6L1 && isSimilar6L1(cl.col, superpixel_means[cl.neighbours[i]].col)))
        {
          mask[cl.neighbours[i]] = true;
          cluster.push_back(cl.neighbours[i]);
        }
      }
    }

    idx++;
  }
}

/**
 * setNeighbours
 */
void RecursiveSuperpixelClustering::setNeighbours()
{
  std::vector< std::set<int> > nbs(superpixel_means.size());
  std::set<int>::iterator it;
  unsigned z;

  // set neighbours
  for (int v=0; v<labels.rows-1; v++)
  {
    for (int u=0; u<labels.cols-1; u++)
    {
      const int &l = labels(v,u);
      if (l!=labels(v,u+1)) nbs[l].insert(labels(v,u+1));
      if (l!=labels(v+1,u)) nbs[l].insert(labels(v+1,u));
    }
  }
  
  // set reverse neighbours
  for (unsigned i=0; i<nbs.size(); i++)
  {
    for (it=nbs[i].begin(); it!=nbs[i].end(); it++)
      nbs[*it].insert(i);
  }

  // copy neighbours
  for (unsigned i=0; i<nbs.size(); i++)
  {
    std::vector<int> &neighbours = superpixel_means[i].neighbours;
    neighbours.resize(nbs[i].size());

    for (it=nbs[i].begin(),z=0; it!=nbs[i].end(); it++,z++)
    {
      neighbours[z] = *it;
    }
  }
}

/**
 * getClusterMean
 */
void RecursiveSuperpixelClustering::getClusterMean(Cluster &cluster)
{
  int nm;
  double inv_nm;
  cluster.col[0]=cluster.col[1]=cluster.col[2]=cluster.col[3]=cluster.col[4]=cluster.col[5]=0.;

  for (unsigned i=0; i<cluster.indices.size(); i++)
  {
    Cluster &cl = superpixel_means[cluster.indices[i]];
    nm = cluster.cnt+cl.cnt;
    inv_nm = 1./double(nm);

    //update sigma
    cluster.col[3] = sqrt(inv_nm*(cluster.cnt*sqr(cluster.col[3]) + cl.cnt*sqr(cl.col[3]) + cluster.cnt*cl.cnt*inv_nm*sqr(cluster.col[0]-cl.col[0])));
    cluster.col[4] = sqrt(inv_nm*(cluster.cnt*sqr(cluster.col[4]) + cl.cnt*sqr(cl.col[4]) + cluster.cnt*cl.cnt*inv_nm*sqr(cluster.col[1]-cl.col[1])));
    cluster.col[5] = sqrt(inv_nm*(cluster.cnt*sqr(cluster.col[5]) + cl.cnt*sqr(cl.col[5]) + cluster.cnt*cl.cnt*inv_nm*sqr(cluster.col[2]-cl.col[2])));
    //update mean
    cluster.col[0] = (cluster.col[0]*cluster.cnt + cl.col[0]*cl.cnt) * inv_nm;
    cluster.col[1] = (cluster.col[1]*cluster.cnt + cl.col[1]*cl.cnt) * inv_nm;
    cluster.col[2] = (cluster.col[2]*cluster.cnt + cl.col[2]*cl.cnt) * inv_nm;
    cluster.cnt = nm;
  }
}




/*************************** public *****************************************
 * Operate
 */
void RecursiveSuperpixelClustering::operate(std::vector<Cluster> &clusters)
{
  setNeighbours();

  mask.clear();
  mask.resize(superpixel_means.size(),false);
  clusters.clear();

  std::vector<int> inds;

  // cluster
  for (unsigned i=0; i<superpixel_means.size(); i++)
  {
    clusterSuperPixel(i, inds);

    if (inds.size()>0)
    {
      clusters.push_back(Cluster());
      clusters.back().indices = inds;
      getClusterMean(clusters.back());
    }
  }
}

/**
 * setSuperpixel
 */
void RecursiveSuperpixelClustering::setSuperpixel(const cv::Mat_<cv::Vec3d> &_im_lab, const cv::Mat_<int> &_labels, const int &_numlabels)
{
  numlabels = _numlabels;
  superpixel_means.clear();
  superpixel_means.resize(numlabels);
  double inv_cnt;

  im_lab = _im_lab;
  labels = _labels;
  numlabels = _numlabels;

  // compute mean
  for (int v=0; v<im_lab.rows; v++)
  {
    for (int u=0; u<im_lab.cols; u++)
    {
      const int &l = labels(v,u);
      const cv::Vec3d &lab = im_lab(v,u);
      Cluster &mean = superpixel_means[l];
      mean.col[0] += lab[0];
      mean.col[1] += lab[1];
      mean.col[2] += lab[2];
      mean.cnt++;
    }
  }
  for (unsigned i=0; i<superpixel_means.size(); i++)
  {
    Cluster &mean = superpixel_means[i];
    if (mean.cnt>0) {
      inv_cnt = 1./double(mean.cnt);
      mean.col[0] *= inv_cnt;
      mean.col[1] *= inv_cnt;
      mean.col[2] *= inv_cnt;
    }
  }

  // compute sigma
  for (int v=0; v<im_lab.rows; v++)
  {
    for (int u=0; u<im_lab.cols; u++)
    {
      const int &l = labels(v,u);
      const cv::Vec3d &lab = im_lab(v,u);
      Cluster &mean = superpixel_means[l];
      mean.col[3] += jvis::sqr(lab[0]-mean.col[0]);
      mean.col[4] += jvis::sqr(lab[1]-mean.col[1]);
      mean.col[5] += jvis::sqr(lab[2]-mean.col[2]);
    }
  }
  for (unsigned i=0; i<superpixel_means.size(); i++)
  {
    Cluster &mean = superpixel_means[i];
    if (mean.cnt>1) {
      inv_cnt = 1./double(mean.cnt-1);
      mean.col[3] = sqrt(mean.col[3]*inv_cnt);
      mean.col[4] = sqrt(mean.col[4]*inv_cnt);
      mean.col[5] = sqrt(mean.col[5]*inv_cnt);
    }
  }
}

/**
 * getLabelMap
 */
void RecursiveSuperpixelClustering::getLabelMap(const std::vector<Cluster> &clusters, cv::Mat_<int> &new_labels)
{
  new_labels = cv::Mat_<int>(labels.size());

  std::vector<int> new_ids(numlabels);
  for (unsigned i=0; i<clusters.size(); i++)
  {
    const std::vector<int> &inds = clusters[i].indices;
    for (unsigned j=0; j<inds.size(); j++)
      new_ids[inds[j]] = i;
  }

  for (int v=0; v<new_labels.rows; v++)
  {
    for (int u=0; u<new_labels.cols; u++)
    {
      new_labels(v,u) = new_ids[labels(v,u)];
    }
  }

}


}

