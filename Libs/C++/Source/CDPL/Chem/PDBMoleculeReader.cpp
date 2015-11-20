/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBMoleculeReader.cpp 
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

#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/PDBMoleculeReader.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "PDBDataReader.hpp"

#include <iostream>
using namespace CDPL;


Chem::PDBMoleculeReader::PDBMoleculeReader(std::istream& is): 
	Util::StreamDataReader<Molecule, PDBMoleculeReader>(is), reader(new PDBDataReader(*this)) {}

Chem::PDBMoleculeReader::~PDBMoleculeReader() {}

bool Chem::PDBMoleculeReader::readData(std::istream& is, Molecule& mol)
{
	try {
		return reader->readPDBFile(is, mol);

	} catch (Base::Exception& e) {
		std::cerr << e.what() << std::endl;
		throw Base::IOError("PDBMoleculeReader: while reading entry " + boost::lexical_cast<std::string>(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Chem::PDBMoleculeReader::skipData(std::istream& is)
{
	try {
		return reader->skipPDBFile(is);

	} catch (Base::Exception& e) {
		throw Base::IOError("PDBMoleculeReader: while skipping entry " + boost::lexical_cast<std::string>(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Chem::PDBMoleculeReader::moreData(std::istream& is)
{
	return reader->hasMoreData(is);
}
