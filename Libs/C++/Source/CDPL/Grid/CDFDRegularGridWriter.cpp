/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDRegularGridWriter.cpp 
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

#include "CDPL/Grid/CDFDRegularGridWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFRegularGridDataWriter.hpp"


using namespace CDPL;


Grid::CDFDRegularGridWriter::CDFDRegularGridWriter(std::ostream& os): 
	output(os), state(os.good()), writer(new CDFRegularGridDataWriter(*this)) {}

Grid::CDFDRegularGridWriter::~CDFDRegularGridWriter() {}

Base::DataWriter<Grid::DRegularGrid>& Grid::CDFDRegularGridWriter::write(const DRegularGrid& grid)
{
	state = false;

	try {
		state = writer->writeGrid(output, grid);

	} catch (const std::exception& e) {
		throw Base::IOError("CDFDRegularGridWriter: " + std::string(e.what()));
	}

	invokeIOCallbacks(1.0);

	return *this;
}

Grid::CDFDRegularGridWriter::operator const void*() const
{
	return (state ? this : 0);
}

bool Grid::CDFDRegularGridWriter::operator!() const
{
	return !state;
}
