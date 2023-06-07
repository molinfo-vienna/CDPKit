/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBMoleculeReader.cpp 
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

#include "CDPL/Biomol/PDBMoleculeReader.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "PDBDataReader.hpp"


using namespace CDPL;


Biomol::PDBMoleculeReader::PDBMoleculeReader(std::istream& is): 
	Util::StreamDataReader<Chem::Molecule, PDBMoleculeReader>(is), reader(new PDBDataReader(*this)) {}

Biomol::PDBMoleculeReader::~PDBMoleculeReader() {}

bool Biomol::PDBMoleculeReader::readData(std::istream& is, Chem::Molecule& mol, bool overwrite)
{
	try {
		if (overwrite)
			mol.clear();

		return reader->readPDBFile(is, mol);

	} catch (const std::exception& e) {
		throw Base::IOError("PDBMoleculeReader: while reading entry " + std::to_string(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Biomol::PDBMoleculeReader::skipData(std::istream& is)
{
	try {
		return reader->skipPDBFile(is);

	} catch (const std::exception& e) {
		throw Base::IOError("PDBMoleculeReader: while skipping entry " + std::to_string(getRecordIndex()) + 
							": " + e.what());
	}
}

bool Biomol::PDBMoleculeReader::moreData(std::istream& is)
{
	return reader->hasMoreData(is);
}
