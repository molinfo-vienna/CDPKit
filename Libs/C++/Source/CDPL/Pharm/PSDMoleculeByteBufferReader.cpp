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
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
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

void Pharm::PSDMoleculeByteBufferReader::readMolecule(Internal::ByteBuffer& bbuf, Chem::Molecule& mol)
{
    try {
        if (containsCDFData(bbuf)) {
            if (!cdfReader)
                cdfReader.reset(new Chem::CDFDataReader(*this));

            if (!cdfReader->readMolecule(mol, bbuf))
                throw PSDIOError("PSDMoleculeByteBufferReader: reading molecule data failed");

            return;
        }
     
        readHeaderAndName(bbuf, mol);
    
        if (bbuf.getIOPointer() < bbuf.getSize()) {
            readStructureData(bbuf, mol);

            if (bbuf.getIOPointer() < bbuf.getSize()) {
                startAtomIdx = mol.getNumAtoms();
                atomStereoDescrs.clear();
                bondStereoDescrs.clear();
    
                readAtoms(bbuf, mol);
      
                if (bbuf.getIOPointer() < bbuf.getSize()) {
                    readConformers(bbuf, mol);

                    if (bbuf.getIOPointer() < bbuf.getSize())
                        readBonds(bbuf, mol);
                }

                setStereoDescriptors(mol);
            }
        }

    } catch (const PSDIOError& e) {
        throw e;

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDMoleculeByteBufferReader: reading molecule data failed: ") + e.what());
    }  
} 

void Pharm::PSDMoleculeByteBufferReader::readHeaderAndName(Internal::ByteBuffer& bbuf, Chem::Molecule& mol)
{
    using namespace PSDMoleculeDataFormat;

    std::uint8_t tmp = 0;

    // header
    bbuf.setIOPointer(0);
    bbuf.getInt(tmp);

    if (tmp != FORMAT_ID)
        throw PSDIOError("PSDMoleculeByteBufferReader: invalid molecule data format");

    bbuf.getInt(tmp);

    if ((tmp & VERSION_MASK) != CURR_VERSION) // so far there is only one version
        throw PSDIOError("PSDMoleculeByteBufferReader: invalid molecule data format version");

    // name
    if (tmp & NAME_LENGTH_BYTE_COUNT_MASK) {
        std::uint32_t name_len = 0;

        bbuf.getInt(name_len, (tmp & NAME_LENGTH_BYTE_COUNT_MASK) >> NAME_LENGTH_BYTE_COUNT_SHIFT);

        tmpString[0].resize(name_len);

        bbuf.getBytes(tmpString[0].data(), name_len);

        setName(mol, tmpString[0]);
    }
}

void Pharm::PSDMoleculeByteBufferReader::readStructureData(Internal::ByteBuffer& bbuf, Chem::Molecule& mol)
{
    using namespace PSDMoleculeDataFormat;

    std::uint8_t tmp = 0;

    bbuf.getInt(tmp);

    if (tmp == 0)
        return;
    
    std::uint32_t num_sd_entries = 0;
  
    bbuf.getInt(num_sd_entries, tmp);

    Chem::StringDataBlock::SharedPointer struct_data(new Chem::StringDataBlock());
    
    for (std::size_t i = 0; i < num_sd_entries; i++) {
        std::uint32_t header_len = 0;
        std::uint32_t data_len = 0;
            
        bbuf.getInt(tmp);

        if (tmp & SD_HEADER_LENGTH_BYTE_COUNT_MASK)
            bbuf.getInt(header_len, tmp & SD_HEADER_LENGTH_BYTE_COUNT_MASK);

        if (tmp & SD_DATA_LENGTH_BYTE_COUNT_MASK)
            bbuf.getInt(data_len, (tmp & SD_DATA_LENGTH_BYTE_COUNT_MASK) >> SD_DATA_LENGTH_BYTE_COUNT_SHIFT);
 
        tmpString[0].resize(header_len);
        tmpString[1].resize(data_len);

        bbuf.getBytes(tmpString[0].data(), header_len);
        bbuf.getBytes(tmpString[1].data(), data_len);

        struct_data->addEntry(tmpString[0], tmpString[1]);
    }
        
    setStructureData(mol, struct_data);
}

void Pharm::PSDMoleculeByteBufferReader::readAtoms(Internal::ByteBuffer& bbuf, Chem::Molecule& mol)
{
    using namespace PSDMoleculeDataFormat;
    
    std::uint32_t num_atoms = 0;

    bbuf.getCompressedInt(num_atoms);

    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = mol.addAtom();
        std::uint8_t prop_flags = 0;

        bbuf.getInt(prop_flags);
     
        if (prop_flags & Atom::TYPE_FLAG) {
            std::uint8_t type = 0;

            bbuf.getInt(type);

            setType(atom, type);
        }

        if (prop_flags & Atom::SYMBOL_FLAG) {
            std::uint8_t sym_len = 0;

            bbuf.getInt(sym_len);
            tmpString[0].resize(sym_len);
            bbuf.getBytes(tmpString[0].data(), sym_len);

            setSymbol(atom, tmpString[0]);
        }

        if (prop_flags & Atom::FORMAL_CHARGE_FLAG) {
            std::int8_t charge = 0;

            bbuf.getInt(charge);

            setFormalCharge(atom, charge);
        }
          
        if (prop_flags & Atom::UNPAIRED_ELEC_COUNT_FLAG) {
            std::uint8_t count = 0;

            bbuf.getInt(count);

            setUnpairedElectronCount(atom, count);
        }

        if (prop_flags & Atom::STEREO_DESCRIPTOR_FLAG) {
            atomStereoDescrs.emplace_back(mol.getNumAtoms() - 1);
            
            readStereoDescriptor(atomStereoDescrs.back(), bbuf);
        }
    }
}

void Pharm::PSDMoleculeByteBufferReader::readConformers(Internal::ByteBuffer& bbuf, Chem::Molecule& mol)
{
    using namespace PSDMoleculeDataFormat;

    std::uint8_t tmp = 0;

    bbuf.getInt(tmp);

    if (tmp == 0)
        return;

    auto num_atoms = mol.getNumAtoms() - startAtomIdx;
    
    if (tmp == ATOM_3D_COORDS_MARKER) {
        readCoordinates(num_atoms, bbuf);

        for (std::size_t i = 0; i < num_atoms; i++)
            set3DCoordinates(mol.getAtom(i + startAtomIdx), coordinates[i]);

        return;
    }
    
    std::uint32_t num_confs = 0;
  
    bbuf.getInt(num_confs, tmp);

    atomCoordsArrays.clear();

    for (auto it = mol.getAtomsBegin() + startAtomIdx, end = mol.getAtomsEnd(); it != end; ++it) {
        atomCoordsArrays.emplace_back(new Math::Vector3DArray());

        set3DCoordinatesArray(*it, atomCoordsArrays.back());
    }
    
    for (std::size_t i = 0; i < num_confs; i++) {
        readCoordinates(num_atoms, bbuf);

        for (std::size_t j = 0; j < num_atoms; j++)
            atomCoordsArrays[j]->addElement(coordinates[j]);
    }
}

void Pharm::PSDMoleculeByteBufferReader::readBonds(Internal::ByteBuffer& bbuf, Chem::Molecule& mol)
{
    using namespace PSDMoleculeDataFormat;
    
    std::uint32_t num_bonds = 0;

    bbuf.getCompressedInt(num_bonds);

    for (std::size_t i = 0; i < num_bonds; i++) {
        std::uint8_t atom_inds_stor_sizes = 0;

        bbuf.getInt(atom_inds_stor_sizes);

        std::uint32_t atom1_idx = 0;
        std::uint32_t atom2_idx = 0;

        bbuf.getInt(atom1_idx, atom_inds_stor_sizes & Bond::ATOM1_INDEX_BYTE_COUNT_MASK);
        bbuf.getInt(atom2_idx, (atom_inds_stor_sizes & Bond::ATOM2_INDEX_BYTE_COUNT_MASK)
                    >> Bond::ATOM2_INDEX_BYTE_COUNT_SHIFT);
        
        auto& bond = mol.addBond(atom1_idx + startAtomIdx, atom2_idx + startAtomIdx);

        std::uint8_t prop_flags = 0;

        bbuf.getInt(prop_flags);
     
        if (prop_flags & Bond::ORDER_FLAG) {
            std::uint8_t order = 0;

            bbuf.getInt(order);

            setOrder(bond, order);
        }

        if (prop_flags & Bond::STEREO_DESCRIPTOR_FLAG) {
            bondStereoDescrs.emplace_back(mol.getNumBonds() - 1);
            
            readStereoDescriptor(bondStereoDescrs.back(), bbuf);
        }
    }
}

void Pharm::PSDMoleculeByteBufferReader::readStereoDescriptor(StereoDescr& descr, Internal::ByteBuffer& bbuf) const
{
    bbuf.getInt(descr.config, 1);
    bbuf.getInt(descr.numRefAtoms, 1);

    if (descr.numRefAtoms > 4)
        throw PSDIOError("PSDMoleculeByteBufferReader: stereo descriptor with more than four reference atoms");

    for (std::size_t i = 0; i < descr.numRefAtoms; i++)
        bbuf.getCompressedInt(descr.refAtomInds[i]);
}

void Pharm::PSDMoleculeByteBufferReader::readCoordinates(std::size_t num_atoms, Internal::ByteBuffer& bbuf)
{
    using namespace PSDMoleculeDataFormat;

    std::uint8_t trans_flags;

    bbuf.getInt(trans_flags);
    
    float trans_vec[3] = { 0.0f };
    float scaling_fact = 1.0f;

    if (trans_flags & X_COORD_TRANSLATION_FLAG)
        bbuf.getFloat(trans_vec[0]);

    if (trans_flags & Y_COORD_TRANSLATION_FLAG)
        bbuf.getFloat(trans_vec[1]);
    
    if (trans_flags & Z_COORD_TRANSLATION_FLAG)
        bbuf.getFloat(trans_vec[2]);

    if (trans_flags & COORDS_SCALING_FACTOR_FLAG)
        bbuf.getFloat(scaling_fact);

    coordinates.clear();

    Math::Vector3D xyz;
    std::int16_t tmp;
        
    for (std::size_t i = 0; i < num_atoms; i++) {
        for (std::size_t j = 0; j < 3; j++) {
            bbuf.getInt(tmp);

            xyz(j) = (int16FixedToFloatingPoint<double>(tmp, COORDS_PRECISION) - trans_vec[j]) / scaling_fact;
        }

        coordinates.addElement(xyz);
    }
}

void Pharm::PSDMoleculeByteBufferReader::setStereoDescriptors(Chem::Molecule& mol) const
{
    for (auto& descr : atomStereoDescrs)
        setStereoDescriptor(mol.getAtom(descr.objIndex), mol, descr);

    for (auto& descr : bondStereoDescrs)
        setStereoDescriptor(mol.getBond(descr.objIndex), mol, descr);
}

template <typename T>
void Pharm::PSDMoleculeByteBufferReader::setStereoDescriptor(T& obj, const Chem::Molecule& mol, const StereoDescr& descr) const
{
    switch (descr.numRefAtoms) {

        case 0:
            Chem::setStereoDescriptor(obj, Chem::StereoDescriptor(descr.config));
            return;

        case 3:
            Chem::setStereoDescriptor(obj,
                                      Chem::StereoDescriptor(descr.config,
                                                             mol.getAtom(descr.refAtomInds[0] + startAtomIdx),
                                                             mol.getAtom(descr.refAtomInds[1] + startAtomIdx),
                                                             mol.getAtom(descr.refAtomInds[2] + startAtomIdx)));
            return;

        case 4:
            Chem::setStereoDescriptor(obj,
                                      Chem::StereoDescriptor(descr.config,
                                                             mol.getAtom(descr.refAtomInds[0] + startAtomIdx),
                                                             mol.getAtom(descr.refAtomInds[1] + startAtomIdx),
                                                             mol.getAtom(descr.refAtomInds[2] + startAtomIdx),
                                                             mol.getAtom(descr.refAtomInds[3] + startAtomIdx)));
            return;

        default:
            throw PSDIOError("PSDMoleculeByteBufferReader: invalid number of stereo descriptor reference atoms");
    }
}
