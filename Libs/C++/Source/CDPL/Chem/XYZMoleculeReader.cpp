/* 
 * XYZMoleculeReader.cpp 
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

#include "CDPL/Chem/XYZMoleculeReader.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "XYZDataReader.hpp"


using namespace CDPL;


Chem::XYZMoleculeReader::XYZMoleculeReader(std::istream& is): 
    Util::StreamDataReader<Molecule, XYZMoleculeReader>(is), reader(new XYZDataReader(*this)) {}

Chem::XYZMoleculeReader::~XYZMoleculeReader() {}

bool Chem::XYZMoleculeReader::readData(std::istream& is, Molecule& mol, bool overwrite)
{
    try {
        if (overwrite)
            mol.clear();

        return reader->readMolecule(is, mol);

    } catch (const std::exception& e) {
        throw Base::IOError("XYZMoleculeReader: while reading record " + std::to_string(getRecordIndex()) + 
                            ": " + e.what());
    }
}

bool Chem::XYZMoleculeReader::skipData(std::istream& is)
{
    try {
        return reader->skipMolecule(is);

    } catch (const std::exception& e) {
        throw Base::IOError("XYZMoleculeReader: while skipping record " + std::to_string(getRecordIndex()) + 
                            ": " + e.what());
    }
}

bool Chem::XYZMoleculeReader::moreData(std::istream& is)
{
    return reader->hasMoreData(is);
}
