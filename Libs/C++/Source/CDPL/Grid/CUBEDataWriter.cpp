/* 
 * CUBEDataWriter.cpp 
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

#include <ostream>
#include <iomanip>
#include <locale>
#include <algorithm>

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"
#include "CDPL/Grid/AttributedGridFunctions.hpp"

#include "CUBEDataWriter.hpp"
#include "CUBEFormatData.hpp"


using namespace CDPL;


namespace
{

    void writeCUBELines(std::ostream& os, std::size_t count, const std::string& lines)
    {
        using namespace Grid;
        
        std::size_t lines_written = 0;

        for (auto it = lines.begin(); (it < lines.end()) && (lines_written < count); lines_written++) {
            auto eol = std::find(it, lines.end(), CUBE::END_OF_LINE);

            os.write(&*it, eol - it);
            os.put(CUBE::END_OF_LINE);

            it = ++eol;
        }

        for (std::size_t i = lines_written; i < count; i++)
            os.put(CUBE::END_OF_LINE);
    }
}


bool Grid::CUBEDataWriter::writeGrid(std::ostream& os, const DRegularGrid& grid)
{
    os.imbue(std::locale::classic());

    // comment lines

    if (getCUBECommentIsNameParameter(ctrlParams)) {
        writeCUBELines(os, 1, getName(grid));
        writeCUBELines(os, 1, getComment(grid));

    } else
        writeCUBELines(os, 2, getComment(grid));
    
    // grid origin

    auto dist_factor = getCUBEOutputDistanceScalingFactorParameter(ctrlParams);
    double grid_origin[3];

    grid.getCoordinates(0, 0, 0, grid_origin);

    os << std::fixed << std::setprecision(6);
    
    os << std::setw(5) << 0 // num. atoms
       << std::setw(12) << (grid_origin[0] * dist_factor)
       << std::setw(12) << (grid_origin[1] * dist_factor)
       << std::setw(12) << (grid_origin[2] * dist_factor)
       << std::setw(3) << 1 // num. values per voxel
       << CUBE::END_OF_LINE;

    // grid axes dimensions and directions
    
    auto& grid_xform = grid.getCoordinatesTransform();

    for (std::size_t i = 0; i < 3; i++) {
        double tot_factor;
        std::size_t dim;

        switch (i) {

            case 0:
                dim = grid.getSize1();
                tot_factor = grid.getXStepSize() * dist_factor;
                break;

            case 1:
                dim = grid.getSize2();
                tot_factor = grid.getYStepSize() * dist_factor;
                break;

            default:
                dim = grid.getSize3();
                tot_factor = grid.getZStepSize() * dist_factor;
        }
        
        os << std::setw(5) << dim
           << std::setw(12) << (grid_xform(0, i) * tot_factor)
           << std::setw(12) << (grid_xform(1, i) * tot_factor)
           << std::setw(12) << (grid_xform(2, i) * tot_factor)
           << CUBE::END_OF_LINE;
    }

    // voxel values

    os << std::scientific;
    
    auto at_nl = true;

    for (std::size_t i = 0, size1 = grid.getSize1(), size2 = grid.getSize2(), size3 = grid.getSize3(); i < size1; i++) {
        for (std::size_t j = 0; j < size2; j++) {
            for (std::size_t k = 0; k < size3; k++) {
                os << std::setw(14) << grid(i, j, k);
                at_nl = false;
                
                if ((k % 6) == 5) {
                    os << CUBE::END_OF_LINE;
                    at_nl = true;
                } 
            }

            if (!at_nl) {
                os << CUBE::END_OF_LINE;
                at_nl = true;
            }
        }
    }
    
    return os.good();
}
