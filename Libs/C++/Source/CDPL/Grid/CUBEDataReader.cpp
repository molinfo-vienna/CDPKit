/* 
 * CUBEDataReader.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "StaticInit.hpp"

#include <istream>
#include <sstream>
#include <locale>
#include <cstddef>

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "CUBEDataReader.hpp"
#include "CUBEFormatData.hpp"


using namespace CDPL;


namespace
{

    void skipCUBELines(std::istream& is, std::size_t count, const char* err_msg = "Error")
    {
        Internal::skipLines(is, count, err_msg, Grid::CUBE::END_OF_LINE);
    }
    
    void readCUBELine(std::istream& is, std::string& line, const char* err_msg = "Error")
    {
        Internal::readLine(is, line, err_msg, false, false, 80, Grid::CUBE::END_OF_LINE);
    }
}


bool Grid::CUBEDataReader::hasMoreData(std::istream& is)
{
    return !std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof());
}

bool Grid::CUBEDataReader::readGrid(std::istream& is, DRegularGrid& grid)
{
    if (!hasMoreData(is))
        return false;

    init(is);
  
    return false;
}

bool Grid::CUBEDataReader::skipGrid(std::istream& is)
{
    if (!hasMoreData(is))
        return false;

    init(is);

    skipCUBELines(is, 2, "CUBEDataReader: error while skipping comment lines");
    readCUBELine(is, line, "CUBEDataReader: error while reading number of atoms and number of values");

    Internal::trimString(line, false, true);
    
    std::istringstream iss(line);
    long num_atoms;
    long num_values = 1;
    double tmp;

    if (!(iss >> num_atoms))
        throw Base::IOError("CUBEDataReader: error while reading number of atoms");

    for (std::size_t i = 0; i < 3; i++)
        if (!(iss >> tmp))
            throw Base::IOError("CUBEDataReader: error while reading grid origin coordinates");
   
    if ((num_atoms >= 0) && hasMoreData(iss) && !(iss >> num_values))
        throw Base::IOError("CUBEDataReader: error while reading number of values per voxel");

    if (num_values < 0)
        num_values = -num_values;
    
    long grid_dims[3];
    
    for (std::size_t i = 0; i < 3; i++) {
        if (!(is >> grid_dims[i]))
            throw Base::IOError("CUBEDataReader: error while reading axis voxel count");

        if (grid_dims[i] < 0)
            grid_dims[i] = -grid_dims[i];
        
        skipCUBELines(is, 1, "CUBEDataReader: error while skipping axis direction data");
    }

    skipCUBELines(is, num_atoms < 0 ? -num_atoms : num_atoms, "CUBEDataReader: error while skipping atom lines");

    if (num_atoms < 0) {
        if (!(iss >> num_values))
            throw Base::IOError("CUBEDataReader: error while reading number of values per voxel from DSET_IDS block");

        for (long i = 0; num_values; i++)
            if (!(is >> line))
                throw Base::IOError("CUBEDataReader: error while skipping voxel value identifier in DSET_IDS block");

        skipCUBELines(is, 1, "CUBEDataReader: error while skipping DSET_IDS block");
    }

    for (std::size_t i = 0, skip_cnt = grid_dims[0] * grid_dims[1] * grid_dims[2] * num_values; i < skip_cnt; i++)
        if (!(is >> line))
            throw Base::IOError("CUBEDataReader: error while skipping voxel value");

    skipCUBELines(is, 1, "CUBEDataReader: error while skipping voxel values");
    
    return true;
}

void Grid::CUBEDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ctrlParams);
    distScalingFactor = getCUBEInputDistanceScalingFactorParameter(ctrlParams);

    is.imbue(std::locale::classic());
}
