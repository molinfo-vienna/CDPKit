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

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Grid/ControlParameterFunctions.hpp"

#include "CUBEDataWriter.hpp"


using namespace CDPL;


bool Grid::CUBEDataWriter::writeGrid(std::ostream& os, const DRegularGrid& grid)
{
    init(os);

    writeHeader(os, grid);
    
    return true;
}

void Grid::CUBEDataWriter::init(std::ostream& os)
{
    os.imbue(std::locale::classic());

    commentIsName = getCUBECommentIsNameParameter(ctrlParams);
}

void Grid::CUBEDataWriter::writeHeader(std::ostream& os, const DRegularGrid& grid)
{
}
