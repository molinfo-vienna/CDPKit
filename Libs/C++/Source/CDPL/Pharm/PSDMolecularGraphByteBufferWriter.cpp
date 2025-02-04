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
#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "PSDMolecularGraphByteBufferWriter.hpp"
#include "PSDMoleculeDataFormat.hpp"
#include "PSDDataIOUtilities.hpp"


using namespace CDPL;


void Pharm::PSDMolecularGraphByteBufferWriter::writeMolecularGraph(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& bbuf)
{
    try {
        outputHeaderAndName(molgraph, bbuf);
        outputStructureData(molgraph, bbuf);

        if (molgraph.getNumAtoms() == 0)
            return;
    
        outputAtoms(molgraph, bbuf);
        outputConformers(molgraph, bbuf);
        outputBonds(molgraph, bbuf);

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDMolecularGraphByteBufferWriter: writing molecule data failed: ") + e.what());
    }
} 

void Pharm::PSDMolecularGraphByteBufferWriter::outputHeaderAndName(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& bbuf) const
{
    using namespace PSDMoleculeDataFormat;

    // header
    bbuf.resize(0);
    bbuf.setIOPointer(0);
    bbuf.putInt(FORMAT_ID, false);

    // name
    std::uint32_t name_len = 0; 
    std::uint8_t name_len_sto_size = 0;
    
    if (hasName(molgraph)) {
        auto& name = getName(molgraph);

        name_len = boost::numeric_cast<std::uint32_t>(name.size());
        bbuf.setIOPointer(2);

        name_len_sto_size = bbuf.putInt(name_len, true);

        bbuf.putBytes(name.data(), name_len);
        bbuf.setIOPointer(1);
    }
    
    bbuf.putInt(std::uint8_t(CURR_VERSION + (name_len_sto_size << NAME_LENGTH_BYTE_COUNT_SHIFT)), false);
    bbuf.setIOPointer(bbuf.getSize());
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputStructureData(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& bbuf) const
{
    using namespace PSDMoleculeDataFormat;

    if (!hasStructureData(molgraph)) {
        if (molgraph.getNumAtoms() > 0)
            bbuf.putInt(std::uint8_t(0), false);

        return;
    }
    
    auto& struct_data = getStructureData(molgraph);

    bbuf.putCompressedInt(boost::numeric_cast<std::uint32_t>(struct_data->getSize()));

    for (auto& sd_entry : *struct_data) {
        auto& header = sd_entry.getHeader();
        auto& data = sd_entry.getData();
        auto saved_io_ptr = bbuf.getIOPointer();

        bbuf.setIOPointer(saved_io_ptr + 1);

        std::uint8_t str_lens_stor_sizes =
            (header.empty() ? 0 : bbuf.putInt(boost::numeric_cast<std::uint32_t>(header.size()), true));

        str_lens_stor_sizes +=
            (data.empty() ? 0 : (bbuf.putInt(boost::numeric_cast<std::uint32_t>(data.size()), true) << SD_DATA_LENGTH_BYTE_COUNT_SHIFT));

        bbuf.setIOPointer(saved_io_ptr);
        bbuf.putInt(str_lens_stor_sizes, false);
        bbuf.setIOPointer(bbuf.getSize());

        bbuf.putBytes(header.data(), header.size());
        bbuf.putBytes(data.data(), data.size());
    }
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputAtoms(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& bbuf) const
{
    using namespace PSDMoleculeDataFormat;

    bbuf.putCompressedInt(boost::numeric_cast<std::uint32_t>(molgraph.getNumAtoms()));

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
         
        bbuf.putInt(prop_flags, false);

        if (prop_flags & Atom::TYPE_FLAG)
            bbuf.putInt(boost::numeric_cast<std::uint8_t>(getType(atom)), false);

        if (prop_flags & Atom::SYMBOL_FLAG) {
            auto& symbol = getSymbol(atom);

            bbuf.putInt(boost::numeric_cast<std::uint8_t>(symbol.length()), false);
            bbuf.putBytes(symbol.data(), symbol.length());
        }

        if (prop_flags & Atom::FORMAL_CHARGE_FLAG)
            bbuf.putInt(boost::numeric_cast<std::int8_t>(getFormalCharge(atom)), false);

        if (prop_flags & Atom::STEREO_DESCRIPTOR_FLAG)
            outputStereoDescriptor(getStereoDescriptor(atom), molgraph, bbuf);
    }
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputConformers(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& bbuf)
{
    using namespace PSDMoleculeDataFormat;

    std::uint32_t num_confs = boost::numeric_cast<std::uint32_t>(getNumConformations(molgraph));

    if (num_confs > 0) {
        bbuf.putCompressedInt(num_confs);

        for (std::size_t i = 0; i < num_confs; i++) {
            getConformation(molgraph, i, coordinates);
            outputCoordinates(bbuf);
        }
         
    } else if (hasCoordinates(molgraph, 3)) {
        bbuf.putInt(ATOM_3D_COORDS_MARKER, false);

        get3DCoordinates(molgraph, coordinates);
        outputCoordinates(bbuf);
         
    } else if (molgraph.getNumBonds() > 0)
        bbuf.putInt(std::int8_t(0), false);
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputBonds(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& bbuf) const
{
    using namespace PSDMoleculeDataFormat;
  
    std::uint32_t num_bonds = boost::numeric_cast<std::uint32_t>(getCompleteBondCount(molgraph));

    if (num_bonds == 0)
        return;

    bbuf.putCompressedInt(num_bonds);

    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        auto saved_io_ptr = bbuf.getIOPointer();

        bbuf.setIOPointer(saved_io_ptr + 1);
     
        std::uint8_t atom_inds_stor_sizes =
            bbuf.putInt(boost::numeric_cast<std::uint32_t>(molgraph.getAtomIndex(atom1)), true);

        atom_inds_stor_sizes +=
            (bbuf.putInt(boost::numeric_cast<std::uint32_t>(molgraph.getAtomIndex(atom2)), true) << Bond::ATOM2_INDEX_BYTE_COUNT_SHIFT);

        bbuf.setIOPointer(saved_io_ptr);
        bbuf.putInt(atom_inds_stor_sizes, false);
        bbuf.setIOPointer(bbuf.getSize());
         
        std::uint8_t prop_flags = 0;

        if (hasOrder(bond))
            prop_flags |= Bond::ORDER_FLAG;

        if (hasStereoDescriptor(bond))
            prop_flags |= Bond::STEREO_DESCRIPTOR_FLAG;
         
        bbuf.putInt(prop_flags, false);

        if (prop_flags & Bond::ORDER_FLAG)
            bbuf.putInt(boost::numeric_cast<std::uint8_t>(getOrder(bond)), false);

        if (prop_flags & Bond::STEREO_DESCRIPTOR_FLAG)
            outputStereoDescriptor(getStereoDescriptor(bond), molgraph, bbuf);
    }
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputStereoDescriptor(const Chem::StereoDescriptor& descr, const Chem::MolecularGraph& molgraph,
                                                                      Internal::ByteBuffer& bbuf) const
{
    bbuf.putInt(boost::numeric_cast<std::uint8_t>(descr.getConfiguration()), false);

    std::uint8_t num_ref_atoms = boost::numeric_cast<std::uint8_t>(descr.getNumReferenceAtoms());

    bbuf.putInt(num_ref_atoms, false);

    for (std::size_t i = 0; i < num_ref_atoms; i++)
        bbuf.putCompressedInt(boost::numeric_cast<std::uint32_t>(molgraph.getAtomIndex(*descr.getReferenceAtoms()[i])));
}

void Pharm::PSDMolecularGraphByteBufferWriter::outputCoordinates(Internal::ByteBuffer& bbuf) const
{
    using namespace PSDMoleculeDataFormat;

    double trans_vec[3] = { 0.0 };
    double scaling_fact = 1.0;
    std::uint8_t trans_flags = 0;
   
    calcCoordsTransform(coordinates, trans_vec, scaling_fact, COORDS_PRECISION);

    auto saved_io_ptr = bbuf.getSize();
    
    bbuf.setIOPointer(saved_io_ptr + 1);
    
    if (trans_vec[0] != 0.0) {
        trans_flags |= X_COORD_TRANSLATION_FLAG;
        bbuf.putFloat(float(trans_vec[0]));
    }
    
    if (trans_vec[1] != 0.0) {
        trans_flags |= Y_COORD_TRANSLATION_FLAG;
        bbuf.putFloat(float(trans_vec[1]));
    }
    
    if (trans_vec[2] != 0.0) {
        trans_flags |= Z_COORD_TRANSLATION_FLAG;
        bbuf.putFloat(float(trans_vec[2]));
    }
    
    if (scaling_fact != 1.0) {
        trans_flags |= COORDS_SCALING_FACTOR_FLAG;
        bbuf.putFloat(float(scaling_fact));
    }

    bbuf.setIOPointer(saved_io_ptr);
    bbuf.putInt(trans_flags, false);
    bbuf.setIOPointer(bbuf.getSize());

    for (auto& xyz : coordinates)
          for (std::size_t i = 0; i < 3; i++)
              bbuf.putInt(floatingToInt16FixedPoint(trans_vec[i] + xyz(i) * scaling_fact, COORDS_PRECISION), false);
}
