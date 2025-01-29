/* 
 * PSDMoleculeByteBufferReader.cpp 
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

#include <cstdint>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/CDFDataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "PSDMoleculeByteBufferReader.hpp"
#include "PSDMoleculeDataFormat.hpp"
#include "PSDDataIOUtilities.hpp"


using namespace CDPL;


Pharm::PSDMoleculeByteBufferReader::PSDMoleculeByteBufferReader()
{
    Chem::setStrictErrorCheckingParameter(*this, true);
}

Pharm::PSDMoleculeByteBufferReader::~PSDMoleculeByteBufferReader()
{}

void Pharm::PSDMoleculeByteBufferReader::readMolecule(Internal::ByteBuffer& byte_buf, Chem::Molecule& mol)
{
    try {
        doReadMolecule(byte_buf, mol);

    } catch (const PSDIOError& e) {
        throw e;

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDMoleculeByteBufferReader: reading molecule data failed: ") + e.what());
    }  
} 

void Pharm::PSDMoleculeByteBufferReader::doReadMolecule(Internal::ByteBuffer& byte_buf, Chem::Molecule& mol)
{
    if (containsCDFData(byte_buf)) {
        if (!cdfReader)
            cdfReader.reset(new Chem::CDFDataReader(*this));

        if (!cdfReader->readMolecule(mol, byte_buf))
            throw PSDIOError("PSDMoleculeByteBufferReader: reading molecule data failed");

        return;
    }

    using namespace PSDMoleculeDataFormat;

    std::uint8_t tmp = 0;

    byte_buf.setIOPointer(0);
    byte_buf.getInt(tmp);
    
    if (tmp != FORMAT_ID)
        throw PSDIOError("PSDMoleculeByteBufferReader: invalid molecule data format");

    // TODO
}
