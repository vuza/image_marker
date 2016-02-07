#include "ColorMap.hpp"

namespace jvis
{

std::map<int, cv::Vec3b> col_map;

void initColorMap()
{
  col_map[-1] = cv::Vec3b(180,180,180);
  col_map[0] = cv::Vec3b(255, 0, 0);
  col_map[1] = cv::Vec3b(0, 255, 0);
  col_map[2] = cv::Vec3b(0, 0, 255);
  col_map[3] = cv::Vec3b(255, 255, 0);
  col_map[4] = cv::Vec3b(0, 255, 255);
  col_map[5] = cv::Vec3b(255, 0, 255);
  col_map[6] = cv::Vec3b(125, 0, 0);
  col_map[7] = cv::Vec3b(0, 125, 0);
  col_map[8] = cv::Vec3b(0, 0, 125);
}

void initColorMapDark()
{
  col_map[-1] = cv::Vec3b(128,128,128);
  col_map[0] = cv::Vec3b(166,206,227);
  col_map[1] = cv::Vec3b(31,120,180);
  col_map[2] = cv::Vec3b(178,223,138);
  col_map[3] = cv::Vec3b(51,160,44);
  col_map[4] = cv::Vec3b(251,154,153);
  col_map[5] = cv::Vec3b(227,26,28);
  col_map[6] = cv::Vec3b(253,191,111);
  col_map[7] = cv::Vec3b(255,127,0);
  col_map[8] = cv::Vec3b(202,178,214);
  col_map[9] = cv::Vec3b(106,61,154);
  col_map[10] = cv::Vec3b(255,255,153);
  col_map[11] = cv::Vec3b(177,89,40);
  col_map[12] = cv::Vec3b(141,211,199);
  col_map[13] = cv::Vec3b(255,255,179);
  col_map[14] = cv::Vec3b(190,186,218);
  col_map[15] = cv::Vec3b(251,128,114);
  col_map[16] = cv::Vec3b(128,177,211);
  col_map[17] = cv::Vec3b(253,180,98);
  col_map[18] = cv::Vec3b(179,222,105);
  col_map[19] = cv::Vec3b(252,205,229);
  col_map[20] = cv::Vec3b(217,217,217);
  col_map[21] = cv::Vec3b(188,128,189);
  col_map[22] = cv::Vec3b(204,235,197);
  col_map[23] = cv::Vec3b(255,237,111);
}

void initColorMapPlants()
{
  col_map[-1] = cv::Vec3b(128,128,128);
  col_map[0] = cv::Vec3b(166,206,227);
  col_map[1] = cv::Vec3b(51,160,44);
  col_map[2] = cv::Vec3b(251,154,153);
  col_map[3] = cv::Vec3b(130,250,120);
  col_map[4] = cv::Vec3b(31,120,180);
  col_map[5] = cv::Vec3b(227,26,28);
  col_map[6] = cv::Vec3b(253,191,111);
  col_map[7] = cv::Vec3b(255,127,0);
  col_map[8] = cv::Vec3b(202,178,214);
  col_map[9] = cv::Vec3b(106,61,154);
  col_map[10] = cv::Vec3b(255,255,153);
  col_map[11] = cv::Vec3b(177,89,40);
  col_map[12] = cv::Vec3b(141,211,199);
  col_map[13] = cv::Vec3b(255,255,179);
  col_map[14] = cv::Vec3b(190,186,218);
  col_map[15] = cv::Vec3b(251,128,114);
  col_map[16] = cv::Vec3b(128,177,211);
  col_map[17] = cv::Vec3b(253,180,98);
  col_map[18] = cv::Vec3b(179,222,105);
  col_map[19] = cv::Vec3b(252,205,229);
  col_map[20] = cv::Vec3b(217,217,217);
  col_map[21] = cv::Vec3b(188,128,189);
  col_map[22] = cv::Vec3b(204,235,197);
  col_map[23] = cv::Vec3b(255,237,111);

}



/**
 * getCol
 */
const cv::Vec3b &getCol(int idx)
{
  std::map<int, cv::Vec3b>::iterator it;

  if (col_map.size()==0) initColorMapDark();

  it = col_map.find(idx);

  if (it==col_map.end())
  {
    std::pair< std::map<int,cv::Vec3b>::iterator, bool > it2;
    it2 = col_map.insert(std::make_pair(idx,cv::Vec3b(rand()%255,rand()%255,rand()%255)) );
    it = it2.first;
  }

  return it->second;
}

const int getLabel(int greyColor)
{
  if(0 <= greyColor  && greyColor <= 31)
    return 0;

  if(32 <= greyColor && greyColor <= 63)
    return 1;

  if(64 <= greyColor && greyColor <= 95)
    return 2;

  if(96 <= greyColor && greyColor <= 127)
    return 3;

  if(128 <= greyColor && greyColor <= 159)
    return 4;

  if(160 <= greyColor && greyColor <= 191)
    return 5;

  if(192 <= greyColor && greyColor <= 223)
    return 6;

  if(224 <= greyColor && greyColor <= 255)
    return 7;
}

}