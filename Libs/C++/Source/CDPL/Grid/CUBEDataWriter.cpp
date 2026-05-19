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
#include <locale>
#include <algorithm>

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"
#include "CDPL/Grid/AttributedGridFunctions.hpp"

#include "CUBEDataWriter.hpp"


using namespace CDPL;


namespace
{

    constexpr char END_OF_LINE = '\n';
}


bool Grid::CUBEDataWriter::writeGrid(std::ostream& os, const DRegularGrid& grid)
{
    init(os);

    writeCommentLines(os, commentIsName ? getName(grid) : getComment(grid));
    writeGridOriginSpec(os, grid);
    writeGridAxesSpecs(os, grid);
    writeGridData(os, grid);
    
    return os.good();
}

void Grid::CUBEDataWriter::init(std::ostream& os)
{
    os.imbue(std::locale::classic());

    os << std::scientific;
    
    commentIsName = getCUBECommentIsNameParameter(ctrlParams);
    distScalingFactor = getCUBEOutputDistanceScalingFactorParameter(ctrlParams);
}

void Grid::CUBEDataWriter::writeCommentLines(std::ostream& os, const std::string& comment) const
{
    std::size_t lines_written = 0;

    for (auto it = comment.begin(); (it < comment.end()) && (lines_written < 2); lines_written++) {
        auto eol = std::find(it, comment.end(), END_OF_LINE);

        os.write(&*it, eol - it);
        os.put(END_OF_LINE);
        
        it = ++eol;
    }

    for (std::size_t i = lines_written; i < 2; i++)
        os.put(END_OF_LINE);
}

void Grid::CUBEDataWriter::writeGridOriginSpec(std::ostream& os, const DRegularGrid& grid)
{
    double origin[3];

    grid.getCoordinates(0, 0, 0, origin);

    os << 0 // num. atoms
       << (origin[0] * distScalingFactor)
       << (origin[1] * distScalingFactor)
       << (origin[2] * distScalingFactor)
       << 1
       << END_OF_LINE;
}

void Grid::CUBEDataWriter::writeGridAxesSpecs(std::ostream& os, const DRegularGrid& grid)
{
    auto& xform = grid.getCoordinatesTransform();
    auto sclg_factor = grid.getXStepSize() * distScalingFactor;
    
    os << grid.getSize1()
       << (xform(0, 0) * sclg_factor)
       << (xform(1, 0) * sclg_factor)
       << (xform(2, 0) * sclg_factor)
       << END_OF_LINE;

    sclg_factor = grid.getYStepSize() * distScalingFactor;

    os << grid.getSize2()
       << (xform(0, 1) * sclg_factor)
       << (xform(1, 1) * sclg_factor)
       << (xform(2, 1) * sclg_factor)
       << END_OF_LINE;

    sclg_factor = grid.getZStepSize() * distScalingFactor;

    os << grid.getSize3()
       << (xform(0, 2) * sclg_factor)
       << (xform(1, 2) * sclg_factor)
       << (xform(2, 2) * sclg_factor)
       << END_OF_LINE;
}

void Grid::CUBEDataWriter::writeGridData(std::ostream& os, const DRegularGrid& grid)
{
    auto at_nl = true;

    for (std::size_t i = 0, size1 = grid.getSize1(), size2 = grid.getSize2(), size3 = grid.getSize3(); i < size1; i++) {
        for (std::size_t j = 0; j < size2; j++) {
            for (std::size_t k = 0; k < size3; k++) {
                os << grid(i, j, k);
                at_nl = false;
                
                if ((k % 6) == 5) {
                    os << END_OF_LINE;
                    at_nl = true;
                }
            }

            if (!at_nl) {
                os << END_OF_LINE;
                at_nl = true;
            }
        }
    }
}
