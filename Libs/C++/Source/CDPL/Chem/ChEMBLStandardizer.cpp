/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ChEMBLStandardizer.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <cstring>

#include "CDPL/Config.hpp"

#include <boost/thread.hpp>

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#else // defined(HAVE_BOOST_IOSTREAMS)

#include <sstream>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Chem/ChEMBLStandardizer.hpp"


using namespace CDPL;


namespace
{

	const char* CHEMBL_SALT_STRUCTURES =                 
    #include "ChEMBL-Salts.smi.str" 
	;

	const char* CHEMBL_SOLVENT_STRUCTURES =                 
    #include "ChEMBL-Solvents.smi.str" 
	;

	boost::once_flag initSaltAndSolventDataFlag = BOOST_ONCE_INIT;

	void initSaltAndSolventData()
	{
#if defined(HAVE_BOOST_IOSTREAMS)

		boost::iostreams::stream<boost::iostreams::array_source> salts_is(CHEMBL_SALT_STRUCTURES, std::strlen(CHEMBL_SALT_STRUCTURES));
		boost::iostreams::stream<boost::iostreams::array_source> solvents_is(CHEMBL_SOLVENT_STRUCTURES, std::strlen(CHEMBL_SOLVENT_STRUCTURES));

#else // defined(HAVE_BOOST_IOSTREAMS)

		std::istringstream salts_is(CHEMBL_SALT_STRUCTURES);
		std::istringstream solvents_is(CHEMBL_SOLVENT_STRUCTURES);

#endif // defined(HAVE_BOOST_IOSTREAMS)

		// TODO
	}
}


Chem::ChEMBLStandardizer::ChEMBLStandardizer() // TODO
{}

Chem::ChEMBLStandardizer::ChEMBLStandardizer(const ChEMBLStandardizer& standardizer)  // TODO
{}

Chem::ChEMBLStandardizer::Result Chem::ChEMBLStandardizer::standardize(Molecule& mol)
{
	// TODO

	return NO_CHANGES;
}

Chem::ChEMBLStandardizer::Result Chem::ChEMBLStandardizer::standardize(const Molecule& mol, Molecule& std_mol)
{
	// TODO
	
	return NO_CHANGES;
}

bool Chem::ChEMBLStandardizer::getParent(Molecule& mol)
{
	boost::call_once(&initSaltAndSolventData, initSaltAndSolventDataFlag);
	
	// TODO
	
	return false;
}

bool Chem::ChEMBLStandardizer::getParent(const Molecule& mol, Molecule& parent_mol)
{
	boost::call_once(&initSaltAndSolventData, initSaltAndSolventDataFlag);
	
// TODO
	
	return false;
}

Chem::ChEMBLStandardizer& Chem::ChEMBLStandardizer::operator=(const ChEMBLStandardizer& standardizer)
{
	if (&standardizer == this)
		return *this;

	// TODO
	
	return *this;
}
