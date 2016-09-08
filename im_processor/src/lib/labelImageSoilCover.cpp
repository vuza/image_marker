/*
 */
 
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
#include <list>
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include "ColorMap.hpp"
#include "FilesystemUtils.hh"
#include "toString.hpp"
#include "Slic.h"
#include "RecursiveSuperpixelClustering.hh"

#include <string>


using namespace std;

namespace po = boost::program_options;

string label_name("labels");
string label_ext("png");
string image_name("image");
string image_ext("jpg");

boost::regex image_path_regex{image_name + "\\.*\\." + image_ext};
std::string directory;

std::vector<std::string> label_files;
std::vector<std::string> image_files;

//int k = 5000;    //Desired number of superpixels.
int superpixelsize = 100;
double compactness = 10;  //Compactness factor. use a value ranging from 10 to 40 depending on your needs. Default is 10
double thr_col = 2.5;
int last_label = 0;
int active_label = 1;
float alpha = 0.9;
bool draw_contours = true;
bool draw_segm = true;
unsigned MAX_UNDO_SIZE = 100;


bool parseArgs(int argc, char** argv);
void drawLabels(cv::Mat_<cv::Vec3b> &im, const cv::Mat_<unsigned char> &labels, float alpha);
bool setLabels(cv::Mat_<unsigned char> &im_labels, const cv::Mat_<int> &spc_labels, int active_label, int x, int y);
void setLabelsAllUndef(cv::Mat_<unsigned char> &im_labels, int active_label);
void undoLabels(cv::Mat_<unsigned char> &im_labels);
void redoLabels(cv::Mat_<unsigned char> &im_labels);
static void onMouse( int event, int x, int y, int flags, void* );
static void onTrackBarClusterThr(int, void*);
static void onTrackBarSuperpixelSize(int, void*);
static void onTrackBarLabel(int, void*);



cv::Mat_<unsigned char> im_labels;
cv::Mat_<cv::Vec3b> image, im_draw, im_tmp;
cv::Mat_<int> mask;
int mcnt = 0;

std::list< std::vector< std::pair<cv::Point2i,unsigned char> > > history_undo;
std::list< std::vector< std::pair<cv::Point2i,unsigned char> > > history_redo;

std::vector<cv::Point2i> queue;

std::vector<std::string> label_names;

int thr_col_val=25;
int numlabels(0);
cv::Mat_<int> labels, spc_labels;
std::vector<jvis::RecursiveSuperpixelClustering::Cluster> clusters;

jvis::Slic slic;
jvis::RecursiveSuperpixelClustering spc;

/**
 * @brief initLabelNames
 */
void initLabelNames()
{
  label_names.push_back("Erde");
  label_names.push_back("Kulturpflanze");
  label_names.push_back("Großer Ampfer");
  label_names.push_back("Sonstige lebende organische Masse");
  label_names.push_back("Tote organische Masse");
  label_names.push_back("Steine");
  label_names.push_back("Erde mit grünem Biofilm");
  label_names.push_back("Undefined");
  last_label = label_names.size()-1;
}

/**
 * main
 */
int main(int argc, char *argv[]) 
{
  initLabelNames();

  if(!parseArgs(argc, argv))
    return 0;

  jvis::initColorMapPlants();


  // load files...
  std::string so_far = "";
  std::string pattern =  image_name+std::string(".*.")+image_ext;
  std::vector<std::string> label_files;
  std::vector<std::string> image_files;

  jvis::utils::getFilesInDirectory(directory,image_files,so_far,pattern,false);

  label_files = image_files;

  for (unsigned i=0; i<image_files.size(); i++)
  {
    boost::replace_last (label_files[i], image_ext, label_ext);
    boost::replace_last (label_files[i], image_name, label_name);
  }


  // label images
  cv::namedWindow( "image", CV_GUI_NORMAL+CV_WINDOW_AUTOSIZE);//CV_WINDOW_AUTOSIZE ); //CV_WINDOW_KEEPRATIO);// CV_WINDOW_AUTOSIZE );
  cv::setMouseCallback( "image", onMouse, 0 );
  cv::createTrackbar("Threshold", "image",&thr_col_val,100, onTrackBarClusterThr);
  //cv::createTrackbar("Size   ", "image",&superpixelsize,1000, onTrackBarSuperpixelSize);
  cv::createTrackbar("Label  ", "image",&active_label, last_label, onTrackBarLabel);

  int key = (int)'n';

  cout<<"===================="<<endl;
  cout<<"Press ..."<<endl;
  cout<<" [Esc] quit program"<<endl;
  cout<<" [n] store the current image and load the next image"<<endl;
  cout<<" [p] store the current image and load the previous image"<<endl;
  cout<<" [d] toggle drawing mode"<<endl;
  cout<<" [c] toggle draw contours"<<endl;
  cout<<" [u] undo"<<endl;
  cout<<" [r] redo"<<endl;
  cout<<" [+] increase transparancy"<<endl;
  cout<<" [-] decrease trasparancy"<<endl;
  cout<<"===================="<<endl;

  cout<<"Mouse handling..."<<endl;
  cout<<" [Strg + left mouse button]  fill segment"<<endl;
  cout<<" [Strg + right mouse button] fill all unlabeled segments"<<endl;

  cout<<"===================="<<endl;
  cout<<"Labels..."<<endl;
  for (unsigned i=0; i<label_names.size(); i++)
    cout<<" "<<i<<": "<<label_names[i]<<endl;
  cout<<"===================="<<endl;

  for (unsigned i=0; i<image_files.size();)
  {
    if ( ((char)key)=='n' || ((char)key)=='p' )
    {
      image = cv::imread(directory+image_files[i], CV_LOAD_IMAGE_COLOR);
      im_labels = cv::imread(directory+label_files[i], CV_LOAD_IMAGE_GRAYSCALE);

      if (im_labels.empty() || image.size()!=im_labels.size()) im_labels = cv::Mat_<unsigned char>::ones(image.rows, image.cols)*255;
      mask = cv::Mat_<int>::zeros(image.rows, image.cols);

      cout<<(directory+image_files[i])<<endl;
      cout<<(directory+label_files[i])<<endl;

      thr_col = ((double)thr_col_val)/10.;
      spc.setColorThreshold(thr_col);

      //slic.segmentSuperpixelNumber(image,labels,numlabels, k, m);
      slic.segmentSuperpixelSize(image,labels,numlabels, superpixelsize, compactness);
      spc.setSuperpixel(slic.getImageLAB(), labels, numlabels);
      spc.operate(clusters);

      spc.getLabelMap(clusters, spc_labels);
      cout<<"number of labels: slic="<<numlabels<<", clusters="<<clusters.size()<<endl;
      cout<<"Active label: "<<label_names[active_label]<<endl;
      history_redo.clear();
      history_undo.clear();
    }

    image.copyTo(im_draw);
    if (draw_segm) drawLabels(im_draw, im_labels, alpha);
    if (draw_segm && draw_contours) slic.drawContours(im_draw, spc_labels, 255,0,0);

    cv::imshow("image",im_draw);

    key = cv::waitKey(0);

    if ( ((char)key)==27) //ESC
    {
      cv::imwrite(directory+label_files[i], im_labels);
      break;
    }
    else if (((char)key)=='n')
    {
      cv::imwrite(directory+label_files[i], im_labels);
      if (i<image_files.size()-1) i++;
    }
    else if (((char)key)=='p')
    {
      cv::imwrite(directory+label_files[i], im_labels);
      if (i>0) i--;
    }
    else if (((char)key)=='d') draw_segm = !draw_segm;
    else if (((char)key)=='c') draw_contours = !draw_contours;
    else if (((char)key)=='+' && alpha<1.) alpha+=0.1;
    else if (((char)key)=='-' && alpha>0.1) alpha-=0.1;
    else if (((char)key)=='u') { undoLabels(im_labels); }
    else if (((char)key)=='r') { redoLabels(im_labels); }
  }

//  //if (out_labels.size()>0)
//  //  cv::imwrite(out_labels, im_labels);


//  if (image.cols<3000) {
//    cv::imshow("image",im_draw);
//    cv::waitKey(0);
//  }else cout << "[ERROR] Can't show the image! It's too large!" <<endl;

}


bool parseArgs(int argc, char** argv)
{
    po::options_description general("General options");
    general.add_options()
            ("help", "show help message")
            ("directory,d", po::value<std::string>(&directory)->default_value(directory), "Input directory")
            ("superpixel-size,s", po::value<int>(&superpixelsize)->default_value(100), "Superpixel size")
            ("compactness,c", po::value<double>(&compactness)->default_value(10), "Superpixel compactness")
            ;


    po::options_description all("");
    all.add(general);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(all).run(), vm);
    po::notify(vm);
    std::string usage = "General usage: augmentTrainingImage [-d directory] [-s superpixel-size] [-c compactness]";

    if(vm.count("help"))
    {
        std::cout << usage << std::endl;
        std::cout << all;
        return false;
    }

    return true;
}

static void onMouse( int event, int x, int y, int flags, void* )
{
    if(x < 0 || x >= image.cols || y < 0 || y >= image.rows )
        return;

    if (event==CV_EVENT_RBUTTONDOWN && (flags & CV_EVENT_FLAG_CTRLKEY))
    {
      setLabelsAllUndef(im_labels, active_label);
      image.copyTo(im_draw);
      if (draw_segm) drawLabels(im_draw, im_labels, alpha);
      if (draw_segm && draw_contours) slic.drawContours(im_draw, spc_labels, 255,0,0);
      cv::imshow("image", im_draw);
    }
    else if( (event==CV_EVENT_LBUTTONDOWN || event==CV_EVENT_MOUSEMOVE) && (flags & CV_EVENT_FLAG_LBUTTON) && (flags & CV_EVENT_FLAG_CTRLKEY))
    {
      if (setLabels(im_labels, spc_labels, active_label, x, y))
      {
        image.copyTo(im_draw);
        if (draw_segm) drawLabels(im_draw, im_labels, alpha);
        if (draw_segm && draw_contours) slic.drawContours(im_draw, spc_labels, 255,0,0);
        cv::imshow("image", im_draw);
      }
    }
}

static void onTrackBarClusterThr(int, void*)
{
  thr_col = ((double)thr_col_val)/10.;

  spc.setColorThreshold(thr_col);
  spc.operate(clusters);
  spc.getLabelMap(clusters, spc_labels);

  image.copyTo(im_draw);
  if (draw_segm) drawLabels(im_draw, im_labels, alpha);
  if (draw_segm && draw_contours) slic.drawContours(im_draw, spc_labels, 255,0,0);

  cout<<"number of labels: slic="<<numlabels<<", clusters="<<clusters.size()<<endl;
  cv::imshow("image",im_draw);
}

static void onTrackBarSuperpixelSize(int, void*)
{
  thr_col = ((double)thr_col_val)/10.;
  spc.setColorThreshold(thr_col);

  slic.segmentSuperpixelSize(image,labels,numlabels, superpixelsize, compactness);

  spc.setSuperpixel(slic.getImageLAB(), labels, numlabels);
  spc.operate(clusters);
  spc.getLabelMap(clusters, spc_labels);

  image.copyTo(im_draw);
  if (draw_segm) drawLabels(im_draw, im_labels, alpha);
  if (draw_segm && draw_contours) slic.drawContours(im_draw, spc_labels, 255,0,0);

  cout<<"number of labels: slic="<<numlabels<<", clusters="<<clusters.size()<<endl;
  cv::imshow("image",im_draw);
}

static void onTrackBarLabel(int, void*)
{
  if (active_label>=0 && active_label<(int)label_names.size())
  {
    cout<<"Active label: "<<label_names[active_label]<<endl;
  }
  else
  {
    if (active_label<0) active_label = 0;
    else if (active_label>=(int)label_names.size()) active_label = (int)label_names.size()-1;
  }
}

/**
 * @brief redoLabels
 * @param im_labels
 */
void redoLabels(cv::Mat_<unsigned char> &im_labels)
{
  if (history_redo.size()==0)
    return;

  history_undo.push_back(std::vector< std::pair<cv::Point2i,unsigned char> >());
  std::vector< std::pair<cv::Point2i,unsigned char> > &hus = history_undo.back();
  std::vector< std::pair<cv::Point2i,unsigned char> > &hrs = history_redo.back();



  for (unsigned i=0; i<hrs.size(); i++)
  {
    std::pair<cv::Point2i,unsigned char> &hr = hrs[i];
    hus.push_back( std::make_pair(hr.first, im_labels(hr.first.y,hr.first.x)) );
    im_labels(hr.first.y,hr.first.x) = hr.second;
  }

  history_redo.pop_back();
}

/**
 * @brief undoLabels
 * @param im_labels
 */
void undoLabels(cv::Mat_<unsigned char> &im_labels)
{
  if (history_undo.size()==0)
    return;

  history_redo.push_back(std::vector< std::pair<cv::Point2i,unsigned char> >());
  std::vector< std::pair<cv::Point2i,unsigned char> > &hrs = history_redo.back();
  std::vector< std::pair<cv::Point2i,unsigned char> > &hus = history_undo.back();


  for (unsigned i=0; i<hus.size(); i++)
  {
    std::pair<cv::Point2i,unsigned char> &hu = hus[i];
    hrs.push_back( std::make_pair(hu.first, im_labels(hu.first.y,hu.first.x)) );
    im_labels(hu.first.y,hu.first.x) = hu.second;
  }

  history_undo.pop_back();
}


/**
 * @brief setLabels
 * @param im_labels
 * @param spc_labels
 * @param active_label
 * @param x
 * @param y
 */
bool setLabels(cv::Mat_<unsigned char> &im_labels, const cv::Mat_<int> &spc_labels, int active_label, int x, int y)
{
  if (active_label == last_label) active_label=255;

  if (im_labels(y,x)!=active_label)
  {
    mcnt++;

    int queue_idx = 0;
    int width = im_labels.cols;
    int height = im_labels.rows;

    history_undo.push_back(std::vector< std::pair<cv::Point2i,unsigned char> >());
    std::vector< std::pair<cv::Point2i,unsigned char> > &hu = history_undo.back();
    hu.push_back( std::make_pair(cv::Point2i(x,y), im_labels(y,x)) );
    if (history_undo.size()>MAX_UNDO_SIZE) history_undo.pop_front();
    history_redo.clear();

    mask(y,x) = mcnt;
    queue.resize(1);
    queue[0] = cv::Point2i(x,y);
    im_labels(y,x) = active_label;
    int la = spc_labels(y,x);    

    // start clustering
    while (((int)queue.size()) > queue_idx)
    {
      // extract current index
      cv::Point2i &pt = queue.at(queue_idx);
      queue_idx++;

      for(int v=pt.y-1; v<=pt.y+1; v++)
      {
        for (int u=pt.x-1; u<=pt.x+1; u++)
        {
           if ( (v < 0) || (u < 0) || (v >= height) || (u >= width) )
            continue;

          int idx = v*width + u;

          // not valid or not used point
          if (mask(idx)==mcnt)
            continue;

          // we can add this point to the plane
          if ( la==spc_labels(idx) )
          {
            hu.push_back( std::make_pair(cv::Point2i(u,v), im_labels(idx)) );
            queue.push_back(cv::Point2i(u,v));
            im_labels(idx) = active_label;
            mask(idx) = mcnt;
          }
        }
      }
    }
    return true;
  }

  return false;
}

/**
 * @brief setLabelsAllUndef
 * @param im_labels
 * @param active_label
 */
void setLabelsAllUndef(cv::Mat_<unsigned char> &im_labels, int active_label)
{
  history_undo.push_back(std::vector< std::pair<cv::Point2i,unsigned char> >());
  std::vector< std::pair<cv::Point2i,unsigned char> > &hu = history_undo.back();

  history_redo.clear();

  for (int v=0; v<im_labels.rows; v++)
  {
    for (int u=0; u<im_labels.cols; u++)
    {
      if (im_labels(v,u)==255)
      {
        hu.push_back( std::make_pair(cv::Point2i(u,v), im_labels(v,u)) );
        im_labels(v,u) = active_label;
      }
    }
  }

  if (hu.size()==0)
    history_undo.pop_back();

  if (history_undo.size()>MAX_UNDO_SIZE) history_undo.pop_front();
}

/**
 * drawLabels
 */
void drawLabels(cv::Mat_<cv::Vec3b> &im, const cv::Mat_<unsigned char> &labels, float alpha)
{
  cv::Vec3b la_col;

  if (im.rows!=labels.rows || im.cols!=labels.cols)
    im = cv::Mat_<cv::Vec3b>(labels.rows, labels.cols);

  float alpha_1 = 1.-alpha;

  for (int v=0; v<labels.rows; v++)
  {
    for (int u=0; u<labels.cols; u++)
    {
      unsigned char la = labels(v,u);
      if (la==255) continue;

      cv::Vec3b &im_col = im(v,u);
      la_col = jvis::getCol(la);

      im_col[0] = im_col[0]*alpha_1 + la_col[0]*alpha;
      im_col[1] = im_col[1]*alpha_1 + la_col[1]*alpha;
      im_col[2] = im_col[2]*alpha_1 + la_col[2]*alpha;
    }
  }
}








