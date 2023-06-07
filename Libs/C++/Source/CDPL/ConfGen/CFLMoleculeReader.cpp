/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CFLMoleculeReader.cpp 
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

#include "CDPL/ConfGen/CFLMoleculeReader.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CFLDataReader.hpp"


using namespace CDPL;


ConfGen::CFLMoleculeReader::CFLMoleculeReader(std::istream& is): 
	Util::StreamDataReader<Chem::Molecule, CFLMoleculeReader>(is), reader(new CFLDataReader(*this))
{}

ConfGen::CFLMoleculeReader::~CFLMoleculeReader() {}

bool ConfGen::CFLMoleculeReader::readData(std::istream& is, Chem::Molecule& mol, bool overwrite)
{
	try {
		if (overwrite)
			mol.clear();

		return reader->readMolecule(is, mol);

	} catch (const std::exception& e) {
		throw Base::IOError("CFLMoleculeReader: while reading record " + std::to_string(getRecordIndex()) + 
							": " + e.what());
	}
}

bool ConfGen::CFLMoleculeReader::skipData(std::istream& is)
{
	try {
		return reader->skipMolecule(is);

	} catch (const std::exception& e) {
		throw Base::IOError("CFLMoleculeReader: while skipping record " + std::to_string(getRecordIndex()) + 
							": " + e.what());
	}
}

bool ConfGen::CFLMoleculeReader::moreData(std::istream& is)
{
	return reader->hasMoreData(is);
}
