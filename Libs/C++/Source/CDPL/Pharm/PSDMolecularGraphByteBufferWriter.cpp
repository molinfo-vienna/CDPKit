/* 
 * PSDMolecularGraphByteBufferWriter.cpp 
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

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/CDFDataWriter.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "PSDMolecularGraphByteBufferWriter.hpp"
#include "PSDMoleculeDataFormat.hpp"
#include "PSDDataIOUtilities.hpp"


using namespace CDPL;


Pharm::PSDMolecularGraphByteBufferWriter::PSDMolecularGraphByteBufferWriter()
{
    Chem::setStrictErrorCheckingParameter(*this, true);
    Chem::setCDFOutputSinglePrecisionFloatsParameter(*this, true);
}

Pharm::PSDMolecularGraphByteBufferWriter::~PSDMolecularGraphByteBufferWriter()
{}

void Pharm::PSDMolecularGraphByteBufferWriter::writeMolecularGraph(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& byte_buf)
{
    try {
        if (!cdfWriter)
            cdfWriter.reset(new Chem::CDFDataWriter(*this));

        cdfWriter->writeMolGraph(molgraph, byte_buf);

        //doWriteMolecularGraph(molgraph, byte_buf);

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDMolecularGraphByteBufferWriter: writing molecule data failed: ") + e.what());
    }
} 

void Pharm::PSDMolecularGraphByteBufferWriter::doWriteMolecularGraph(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& byte_buf)
{
    using namespace PSDMoleculeDataFormat;

    byte_buf.resize(0);
    byte_buf.setIOPointer(0);
    byte_buf.putInt(FORMAT_ID, false);

    std::uint32_t name_len = 0; 
    std::uint8_t name_len_sto_size = 0;
    
    if (hasName(molgraph)) {
        auto& name = getName(molgraph);

        if (!name.empty()) {
            name_len = boost::numeric_cast<std::uint32_t>(name.size());
            byte_buf.setIOPointer(2);

            name_len_sto_size = byte_buf.putInt(name_len, true);

            byte_buf.putBytes(name.data(), name_len);
            byte_buf.setIOPointer(1);
        }
    }

    std::uint32_t num_atoms = boost::numeric_cast<std::uint32_t>(molgraph.getNumAtoms());
    
    byte_buf.putInt(std::uint8_t(CURR_VERSION + (name_len_sto_size << NAME_LENGTH_BYTE_COUNT_SHIFT)), false);
    byte_buf.setIOPointer(byte_buf.getSize());
    
    if (hasStructureData(molgraph)) {
        auto& struct_data = getStructureData(molgraph);
        std::uint32_t num_sd_entries = boost::numeric_cast<std::uint32_t>(struct_data->getSize());
        auto saved_io_ptr = byte_buf.getIOPointer();
        
        byte_buf.setIOPointer(saved_io_ptr + 1);
        
        std::uint8_t num_sd_entries_stor_size = byte_buf.putInt(num_sd_entries, true);

        byte_buf.setIOPointer(saved_io_ptr);
        byte_buf.putInt(num_sd_entries_stor_size, false);
        byte_buf.setIOPointer(byte_buf.getSize());

        for (auto& sd_entry : *struct_data) {
            auto& header = sd_entry.getHeader();
            auto& data = sd_entry.getData();
            
            saved_io_ptr = byte_buf.getIOPointer();

            byte_buf.setIOPointer(saved_io_ptr + 1);

            std::uint8_t str_lens_stor_sizes =
                (header.empty() ? 0 : byte_buf.putInt(boost::numeric_cast<std::uint32_t>(header.size()), true));

            str_lens_stor_sizes +=
                (data.empty() ? 0 : (byte_buf.putInt(boost::numeric_cast<std::uint32_t>(data.size()), true) << SD_DATA_LENGTH_BYTE_COUNT_SHIFT));

            byte_buf.setIOPointer(saved_io_ptr);
            byte_buf.putInt(str_lens_stor_sizes, false);
            byte_buf.setIOPointer(byte_buf.getSize());

            byte_buf.putBytes(header.data(), header.size());
            byte_buf.putBytes(data.data(), data.size());
        }
        
    } else if (num_atoms > 0)
        byte_buf.putInt(std::uint8_t(0), false);

     if (num_atoms == 0)
         return;

     auto saved_io_ptr = byte_buf.getIOPointer();

     byte_buf.setIOPointer(saved_io_ptr + 1);

     std::uint8_t num_atoms_stor_size = byte_buf.putInt(num_atoms, true);

     byte_buf.setIOPointer(saved_io_ptr);
     byte_buf.putInt(num_atoms_stor_size, false);
     byte_buf.setIOPointer(byte_buf.getSize());

     for (auto& atom : molgraph.getAtoms()) {
         std::uint8_t prop_flags = 0;

         if (hasType(atom))
             prop_flags |= Atom::TYPE_FLAG;

         if (hasSymbol(atom))
             prop_flags |= Atom::SYMBOL_FLAG;

         if (hasFormalCharge(atom))
             prop_flags |= Atom::FORMAL_CHARGE_FLAG;

         if (hasStereoDescriptor(atom))
             prop_flags |= Atom::STEREO_DESCRIPTOR_FLAG;
         
         byte_buf.putInt(prop_flags, false);

         if (prop_flags & Atom::TYPE_FLAG)
             byte_buf.putInt(boost::numeric_cast<std::uint8_t>(getType(atom)), false);

         if (prop_flags & Atom::SYMBOL_FLAG) {
             auto& symbol = getSymbol(atom);

             byte_buf.putInt(boost::numeric_cast<std::uint8_t>(symbol.length()), false);
             byte_buf.putBytes(symbol.data(), symbol.length());
         }

         if (prop_flags & Atom::FORMAL_CHARGE_FLAG)
             byte_buf.putInt(boost::numeric_cast<std::int8_t>(getFormalCharge(atom)), false);

         if (prop_flags & Atom::STEREO_DESCRIPTOR_FLAG)
             outputStereoDescriptor(getStereoDescriptor(atom), molgraph, byte_buf);
     }

     std::uint32_t num_bonds = boost::numeric_cast<std::uint32_t>(getCompleteBondCount(molgraph));

     if (num_bonds == 0)
         return;

     saved_io_ptr = byte_buf.getIOPointer();

     byte_buf.setIOPointer(saved_io_ptr + 1);
     
     std::uint8_t num_bonds_stor_size = byte_buf.putInt(num_bonds, true);

     byte_buf.setIOPointer(saved_io_ptr);
     byte_buf.putInt(num_bonds_stor_size, false);
     byte_buf.setIOPointer(byte_buf.getSize());

     for (auto& bond : molgraph.getBonds()) {
         auto& atom1 = bond.getBegin();

         if (!molgraph.containsAtom(atom1))
             continue;

         auto& atom2 = bond.getEnd();

         if (!molgraph.containsAtom(atom2))
             continue;

         saved_io_ptr = byte_buf.getIOPointer();

         byte_buf.setIOPointer(saved_io_ptr + 1);
     
         std::uint8_t atom_inds_stor_sizes =
             byte_buf.putInt(boost::numeric_cast<std::uint32_t>(molgraph.getAtomIndex(atom1)), true);

         atom_inds_stor_sizes +=
             (byte_buf.putInt(boost::numeric_cast<std::uint32_t>(molgraph.getAtomIndex(atom2)), true) << Bond::ATOM2_INDEX_BYTE_COUNT_SHIFT);

         byte_buf.setIOPointer(saved_io_ptr);
         byte_buf.putInt(atom_inds_stor_sizes, false);
         byte_buf.setIOPointer(byte_buf.getSize());
         
         std::uint8_t prop_flags = 0;

         if (hasOrder(bond))
             prop_flags |= Bond::ORDER_FLAG;

         if (hasStereoDescriptor(bond))
             prop_flags |= Bond::STEREO_DESCRIPTOR_FLAG;
         
         byte_buf.putInt(prop_flags, false);

         if (prop_flags & Bond::ORDER_FLAG)
             byte_buf.putInt(boost::numeric_cast<std::uint8_t>(getOrder(bond)), false);

         if (prop_flags & Bond::STEREO_DESCRIPTOR_FLAG)
             outputStereoDescriptor(getStereoDescriptor(bond), molgraph, byte_buf);
     }
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputStereoDescriptor(const Chem::StereoDescriptor& descr, const Chem::MolecularGraph& molgraph,
                                                                      Internal::ByteBuffer& byte_buf) const
{
    // TODO
}
