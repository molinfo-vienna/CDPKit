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

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Grid/AttributedGridFunctions.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
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

    is.imbue(std::locale::classic());

    auto dist_factor = getCUBEInputDistanceScalingFactorParameter(ctrlParams);

    // comment lines
    
    readCUBELine(is, tmpString[0], "CUBEDataReader: error while reading first comment line");
    readCUBELine(is, tmpString[1], "CUBEDataReader: error while reading second comment line");

    if (getCUBECommentIsNameParameter(ctrlParams)) {
        setName(grid, tmpString[0]);
        setComment(grid, tmpString[1]);

    } else {
        tmpString[0].push_back('\n');
        tmpString[0].append(tmpString[1]);

        setComment(grid, tmpString[0]);
    }

    // num. atoms, origin coordinates and number of values per voxel
    
    readCUBELine(is, tmpString[0], "CUBEDataReader: error while reading number of atoms, origin coordinates and number of values per voxel");

    Internal::trimString(tmpString[0], false, true);

    std::istringstream iss(tmpString[0]);
    long num_atoms;
    long num_values = 1;
    double grid_origin[3];

    if (!(iss >> num_atoms))
        throw Base::IOError("CUBEDataReader: error while reading number of atoms");

    for (std::size_t i = 0; i < 3; i++) {
        if (!(iss >> grid_origin[i]))
            throw Base::IOError("CUBEDataReader: error while reading origin coordinates");

        grid_origin[i] *= dist_factor;
    }
    
    if ((num_atoms >= 0) && hasMoreData(iss) && !(iss >> num_values))
        throw Base::IOError("CUBEDataReader: error while reading number of values per voxel");

    // grid axes dimensions and directions
    
    long grid_dims[3];
    Math::Vector3D grid_axes[3];
    double cell_sizes[3];
    
    for (std::size_t i = 0; i < 3; i++) {
        if (!(is >> grid_dims[i]))
            throw Base::IOError("CUBEDataReader: error while reading axis voxel count");

        if (grid_dims[i] < 0)
            grid_dims[i] = -grid_dims[i];
        
        for (std::size_t j = 0; j < 3; j++) {
            if (!(is >> grid_axes[i][j]))
                throw Base::IOError("CUBEDataReader: error while reading axis vector coordinate");

            grid_axes[i][j] *= dist_factor;
        }

        cell_sizes[i] = length(grid_axes[i]);
        grid_axes[i] /= cell_sizes[i];

        skipCUBELines(is, 1, "CUBEDataReader: error while reading axis specification line");
    }

    // target grid setup
    
    grid.resize(grid_dims[0], grid_dims[1], grid_dims[2], false);
    grid.setXStepSize(cell_sizes[0]);
    grid.setYStepSize(cell_sizes[1]);
    grid.setZStepSize(cell_sizes[2]);

    DRegularGrid::CoordinatesTransformType grid_xform;

    grid_xform(3, 3) = 1;

    for (std::size_t i = 0; i < 3; i++)
        column(grid_xform, i) = grid_axes[i];

    grid.setCoordinatesTransform(grid_xform); // only rotation for now

    double curr_grid_origin[3];

    grid.getCoordinates(0, 0, 0, curr_grid_origin);

    for (std::size_t i = 0; i < 3; i++)
        grid_xform(i, 3) = grid_origin[i] - curr_grid_origin[i];

    grid.setCoordinatesTransform(grid_xform); // now rotation + translation

    // atom block
    
    skipCUBELines(is, num_atoms < 0 ? -num_atoms : num_atoms, "CUBEDataReader: error while skipping atom lines");

    // DSET_IDS block
    
    if (num_atoms < 0) {
        if (!(is >> num_values))
            throw Base::IOError("CUBEDataReader: error while reading number of value identifiers in DSET_IDS block");
        
        for (long i = 0; i < num_values; i++)
            if (!(is >> tmpString[0]))
                throw Base::IOError("CUBEDataReader: error while skipping voxel value identifier in DSET_IDS block");

        skipCUBELines(is, 1, "CUBEDataReader: error while skipping DSET_IDS block");
    }

    // voxel values

    for (long i = 0; i < grid_dims[0]; i++)
        for (long j = 0; j < grid_dims[1]; j++)
            for (long k = 0; k < grid_dims[2]; k++)
                for (long l = 0; l < num_values; l++) {
                    if (l == 0) { // save only the first cell value
                        if (!(is >> grid(i, j, k)))
                            throw Base::IOError("CUBEDataReader: error while reading voxel value");
                         
                    } else {
                        if (!(is >> tmpString[0]))
                            throw Base::IOError("CUBEDataReader: error while reading voxel value");
                    }
                }

    // skip remainer of last line
    
    skipCUBELines(is, 1, "CUBEDataReader: error while reading voxel values");
    
    return false;
}

bool Grid::CUBEDataReader::skipGrid(std::istream& is)
{
    if (!hasMoreData(is))
        return false;

    is.imbue(std::locale::classic());
    
    skipCUBELines(is, 2, "CUBEDataReader: error while skipping comment lines");
    readCUBELine(is, tmpString[0], "CUBEDataReader: error while reading number of atoms and number of values per voxel");

    Internal::trimString(tmpString[0], false, true);
    
    std::istringstream iss(tmpString[0]);
    long num_atoms;
    long num_values = 1;
    double tmp;

    if (!(iss >> num_atoms))
        throw Base::IOError("CUBEDataReader: error while reading number of atoms");

    for (std::size_t i = 0; i < 3; i++)
        if (!(iss >> tmp))
            throw Base::IOError("CUBEDataReader: error while skipping origin coordinates");
   
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
        if (!(is >> num_values))
            throw Base::IOError("CUBEDataReader: error while reading number of value identifiers in DSET_IDS block");

        for (long i = 0; i < num_values; i++)
            if (!(is >> tmpString[0]))
                throw Base::IOError("CUBEDataReader: error while skipping voxel value identifier in DSET_IDS block");

        skipCUBELines(is, 1, "CUBEDataReader: error while skipping DSET_IDS block");
    }

    for (std::size_t i = 0, skip_cnt = grid_dims[0] * grid_dims[1] * grid_dims[2] * num_values; i < skip_cnt; i++)
        if (!(is >> tmpString[0]))
            throw Base::IOError("CUBEDataReader: error while skipping voxel value");

    skipCUBELines(is, 1, "CUBEDataReader: error while skipping voxel values");
    
    return true;
}
