/*
 * Software License Agreement (GNU General Public License)
 *
 *  Copyright (c) 2014, Johann Prankl, prankl@acin.tuwien.ac.at
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Johann Prankl
 *
 */

/**
 * $Id$
 */

#ifndef JVIS_COLOR_MAP_HPP
#define JVIS_COLOR_MAP_HPP

#include <map>
#include <opencv2/core/core.hpp>

namespace jvis
{

void initColorMap();

void initColorMapDark();

void initColorMapPlants();

/**
 * getCol
 */
const cv::Vec3b &getCol(int idx);

const int getLabel(int greyColor);

}

#endif
