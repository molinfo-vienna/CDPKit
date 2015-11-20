/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphINCHIFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <sstream>

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/INCHIMolecularGraphWriter.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/INCHIReturnCode.hpp"

#include "LibInChI/inchi_api.h"


using namespace CDPL; 


int Chem::generateINCHI(const MolecularGraph& molgraph, std::string& inchi, const std::string& options, std::size_t dim)
{
	std::ostringstream oss;
	INCHIMolecularGraphWriter inchi_writer(oss);

	setINCHIOutputOptionsParameter(inchi_writer, options);
	setCoordinatesDimensionParameter(inchi_writer, dim);
	setRecordSeparatorParameter(inchi_writer, "");

	if (!inchi_writer.write(molgraph))
		return inchi_writer.getReturnCode();

	inchi.append(oss.str());

	return inchi_writer.getReturnCode();
}

int Chem::generateINCHIKey(const MolecularGraph& molgraph, std::string& inchi_key)
{
	std::ostringstream oss;
	INCHIMolecularGraphWriter inchi_writer(oss);

	setCoordinatesDimensionParameter(inchi_writer, 0);
	setRecordSeparatorParameter(inchi_writer, "");

	if (!inchi_writer.write(molgraph))
		return inchi_writer.getReturnCode();

	char inchi_key_cstr[29];
	int ret_code = GetINCHIKeyFromINCHI(oss.str().c_str(), 0, 0, inchi_key_cstr, 0, 0);

	if (ret_code != INCHIKEY_OK)
		return INCHIReturnCode::ERROR;

	inchi_key.append(inchi_key_cstr);

	return INCHIReturnCode::OKAY;
}
