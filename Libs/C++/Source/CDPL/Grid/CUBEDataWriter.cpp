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
    writeGridOriginAndNumPoints(os, grid);
    writeGridAxesSpecs(os, grid);
    writeGridData(os, grid);
    
    return os.good();
}

void Grid::CUBEDataWriter::init(std::ostream& os)
{
    os.imbue(std::locale::classic());

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

void Grid::CUBEDataWriter::writeGridOriginAndNumPoints(std::ostream& os, const DRegularGrid& grid)
{
}

void Grid::CUBEDataWriter::writeGridAxesSpecs(std::ostream& os, const DRegularGrid& grid)
{
}

void Grid::CUBEDataWriter::writeGridData(std::ostream& os, const DRegularGrid& grid)
{
}
