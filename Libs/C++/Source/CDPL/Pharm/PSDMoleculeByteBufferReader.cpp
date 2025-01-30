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
#include "CDPL/Chem/StringDataBlock.hpp"
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

    byte_buf.getInt(tmp);

    if ((tmp & VERSION_MASK) != CURR_VERSION) // so far there is only one version
        throw PSDIOError("PSDMoleculeByteBufferReader: invalid molecule data format version");

    if (tmp & NAME_LENGTH_BYTE_COUNT_MASK) {
        std::uint32_t name_len = 0;

        byte_buf.getInt(name_len, (tmp & NAME_LENGTH_BYTE_COUNT_MASK) >> NAME_LENGTH_BYTE_COUNT_SHIFT);

        tmpString[0].resize(name_len);

        byte_buf.getBytes(tmpString[0].data(), name_len);

        setName(mol, tmpString[0]);
    }

    if (byte_buf.getIOPointer() == byte_buf.getSize())
        return;

    byte_buf.getInt(tmp);

    if (tmp > 0) {
        Chem::StringDataBlock::SharedPointer struct_data(new Chem::StringDataBlock());
        std::uint32_t num_sd_entries = 0;
  
        byte_buf.getInt(num_sd_entries, tmp);

        for (std::uint32_t i = 0; i < num_sd_entries; i++) {
            std::uint32_t header_len = 0;
            std::uint32_t data_len = 0;
            
            byte_buf.getInt(tmp);

            if (tmp & SD_HEADER_LENGTH_BYTE_COUNT_MASK)
                byte_buf.getInt(header_len, tmp & SD_HEADER_LENGTH_BYTE_COUNT_MASK);

            if (tmp & SD_DATA_LENGTH_BYTE_COUNT_MASK)
                byte_buf.getInt(data_len, (tmp & SD_DATA_LENGTH_BYTE_COUNT_MASK) >> SD_DATA_LENGTH_BYTE_COUNT_SHIFT);
 
            tmpString[0].resize(header_len);
            tmpString[1].resize(data_len);

            byte_buf.getBytes(tmpString[0].data(), header_len);
            byte_buf.getBytes(tmpString[1].data(), data_len);

            struct_data->addEntry(tmpString[0], tmpString[1]);
        }
        
        setStructureData(mol, struct_data);
    }
    
    // TODO
}
