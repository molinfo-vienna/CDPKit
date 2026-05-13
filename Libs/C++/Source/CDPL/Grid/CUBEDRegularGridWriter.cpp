/* 
 * CUBEDRegularGridWriter.cpp 
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

#include "CDPL/Grid/CUBEDRegularGridWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CUBEDataWriter.hpp"


using namespace CDPL;


Grid::CUBEDRegularGridWriter::CUBEDRegularGridWriter(std::ostream& os): 
    output(os), state(os.good()), writer(new CUBEDataWriter(*this)) {}

Grid::CUBEDRegularGridWriter::~CUBEDRegularGridWriter() {}

Base::DataWriter<Grid::DRegularGrid>& Grid::CUBEDRegularGridWriter::write(const DRegularGrid& grid)
{
    state = false;

    try {
        state = writer->writeGrid(output, grid);

    } catch (const std::exception& e) {
        throw Base::IOError("CUBEDRegularGridWriter: " + std::string(e.what()));
    }

    invokeIOCallbacks(1.0);

    return *this;
}

Grid::CUBEDRegularGridWriter::operator const void*() const
{
    return (state ? this : 0);
}

bool Grid::CUBEDRegularGridWriter::operator!() const
{
    return !state;
}
