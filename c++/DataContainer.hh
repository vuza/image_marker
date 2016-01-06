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
 * $Id: DataContainer.hh 264 2015-07-17 14:17:45Z hannes $
 */

#ifndef JVIS_DATACONTAINER_HH
#define JVIS_DATACONTAINER_HH

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string.h>
#include "SmartPtr.hpp"

namespace jvis 
{

/**
 * DataContainer
 */
class DataContainer
{
public:
  enum Type
  {
    FLOAT_2D,
    FLOAT3_2D,
    FLOAT4_2D,
    UCHAR_2D,
    INT_2D,
    UINT_2D,
    DOUBLE_2D,
    MAX_TYPE,
    UNDEF = MAX_TYPE
  };

public:
  Type type;

  DataContainer(const Type &_type=UNDEF) {type=_type;};
  virtual ~DataContainer(){};

  virtual int getRows() {return -1;}
  virtual int getCols() {return -1;}

  typedef SmartPtr< ::jvis::DataContainer > Ptr;
  typedef SmartPtr< ::jvis::DataContainer const> ConstPtr;
};


} //--END--

#endif

