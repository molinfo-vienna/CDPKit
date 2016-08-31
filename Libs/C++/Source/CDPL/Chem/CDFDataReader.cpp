/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataReader.cpp 
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

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "CDFDataReader.hpp"


using namespace CDPL;


bool Chem::CDFDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::MOLECULE_RECORD_ID, true);
}

bool Chem::CDFDataReader::readMolecule(std::istream& is, Molecule& mol)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::MOLECULE_RECORD_ID, false))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);
	atomStereoDescrs.clear();
	bondStereoDescrs.clear();

	CDF::SizeType num_atoms, num_bonds;

	dataBuffer.getInt(num_atoms);
	dataBuffer.getInt(num_bonds);

	startAtomIdx = mol.getNumAtoms();

	readAtoms(mol, num_atoms);
	readBonds(mol, num_atoms, num_bonds);
	readMoleculeProperties(mol);
	setStereoDescriptors(mol);

	return true;
}

bool Chem::CDFDataReader::skipMolecule(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::MOLECULE_RECORD_ID);
}

void Chem::CDFDataReader::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ioBase)); 
}

void Chem::CDFDataReader::readAtoms(Molecule& mol, std::size_t num_atoms)
{
	CDF::PropertySpec prop_spec;
	CDF::UIntType uint_val;
	CDF::LongType long_val;
	CDF::SizeType size_val;
	CDF::BoolType bool_val;
	std::string str_val;
	Math::Vector2D coords_2d_val;
	Math::Vector3D coords_3d_val;

	for (std::size_t i = 0; i < num_atoms; i++) {
		Atom& atom = mol.addAtom();

		while (true) {
			dataBuffer.getInt(prop_spec);

			if (prop_spec == CDF::PROP_LIST_END)
				break;

			switch (extractPropertyID(prop_spec)) {

				case CDF::AtomProperty::TYPE:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setType(atom, uint_val);
					continue;
					
				case CDF::AtomProperty::FORMAL_CHARGE:
					getIntProperty(prop_spec, long_val, dataBuffer);
					setFormalCharge(atom, long_val);
					continue;

				case CDF::AtomProperty::SYMBOL:
					getStringProperty(prop_spec, str_val, dataBuffer);
					setSymbol(atom, str_val);
					continue;

				case CDF::AtomProperty::NAME:
					getStringProperty(prop_spec, str_val, dataBuffer);
					setName(atom, str_val);
					continue;

				case CDF::AtomProperty::ISOTOPE:
					getIntProperty(prop_spec, size_val, dataBuffer);
					setIsotope(atom, size_val);
					continue;

				case CDF::AtomProperty::RING_FLAG:
					getIntProperty(prop_spec, bool_val, dataBuffer);
					setRingFlag(atom, bool_val);
					continue;

				case CDF::AtomProperty::AROMATICITY_FLAG:
					getIntProperty(prop_spec, bool_val, dataBuffer);
					setAromaticityFlag(atom, bool_val);
					continue;

				case CDF::AtomProperty::RADICAL_TYPE:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setRadicalType(atom, uint_val);
					continue;

				case CDF::AtomProperty::HYBRIDIZATION:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setHybridizationState(atom, uint_val);
					continue;

				case CDF::AtomProperty::UNPAIRED_ELECTRON_COUNT:
					getIntProperty(prop_spec, size_val, dataBuffer);
					setUnpairedElectronCount(atom, size_val);
					continue;

				case CDF::AtomProperty::IMPLICIT_HYDROGEN_COUNT:
					getIntProperty(prop_spec, size_val, dataBuffer);
					setImplicitHydrogenCount(atom, size_val);
					continue;

				case CDF::AtomProperty::COORDINATES_2D:
					getVectorProperty(prop_spec, coords_2d_val, dataBuffer);
					set2DCoordinates(atom, coords_2d_val);
					continue;

				case CDF::AtomProperty::COORDINATES_3D:
					getVectorProperty(prop_spec, coords_3d_val, dataBuffer);
					set3DCoordinates(atom, coords_3d_val);
					continue;

				case CDF::AtomProperty::COORDINATES_3D_ARRAY: {
					Math::Vector3DArray::SharedPointer va_ptr(new Math::Vector3DArray());

					getVectorArrayProperty(prop_spec, *va_ptr, dataBuffer);
					set3DCoordinatesArray(atom, va_ptr);
					continue;
				}

				case CDF::AtomProperty::CIP_CONFIGURATION:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setCIPConfiguration(atom, uint_val);
					continue;

				case CDF::AtomProperty::STEREO_CENTER_FLAG:
					getIntProperty(prop_spec, bool_val, dataBuffer);
					setStereoCenterFlag(atom, bool_val);
					continue;

				case CDF::AtomProperty::COMPONENT_GROUP_ID:
					getIntProperty(prop_spec, size_val, dataBuffer);
					setComponentGroupID(atom, size_val);
					continue;

				case CDF::AtomProperty::REACTION_CENTER_STATUS:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setReactionCenterStatus(atom, uint_val);
					continue;

				case CDF::AtomProperty::REACTION_ATOM_MAPPING_ID:
					getIntProperty(prop_spec, size_val, dataBuffer);
					setReactionAtomMappingID(atom, size_val);
					continue;

				case CDF::AtomProperty::STEREO_DESCRIPTOR: {
					CDFStereoDescr descr(i);

					readStereoDescriptor(prop_spec, descr);
					atomStereoDescrs.push_back(descr);
					continue;
				}
					
				case CDF::AtomProperty::MATCH_CONSTRAINTS:

				default:
					handleUnknownProperty(prop_spec, atom, dataBuffer);
			}
		}
	}
}

void Chem::CDFDataReader::readBonds(Molecule& mol, std::size_t num_atoms, std::size_t num_bonds)
{
	CDF::PropertySpec prop_spec;
	CDF::SizeType size_val;
	CDF::UIntType uint_val;
	CDF::BoolType bool_val;
	CDF::SizeType atom1_idx, atom2_idx;
	CDF::BondAtomIndexLengthTuple idx_lengths;

	for (std::size_t i = 0; i < num_bonds; i++) {
		dataBuffer.getInt(idx_lengths);

		std::size_t idx1_length = (idx_lengths >> CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS);
		std::size_t idx2_length = (idx_lengths & CDF::BOND_ATOM_INDEX_LENGTH_MASK);

		if (idx1_length > sizeof(CDF::SizeType) || idx2_length > sizeof(CDF::SizeType))
			throw Base::IOError("CDFDataReader: invalid bond atom index byte size specification");

		dataBuffer.getInt(atom1_idx, idx1_length);
		dataBuffer.getInt(atom2_idx, idx2_length);

		if (atom1_idx >= num_atoms)
			throw Base::IOError("CDFDataReader: bond start atom index range error");

		if (atom2_idx >= num_atoms)
			throw Base::IOError("CDFDataReader: bond end atom index range error");

		Bond& bond = mol.addBond(atom1_idx + startAtomIdx, atom2_idx + startAtomIdx);

		while (true) {
			dataBuffer.getInt(prop_spec);

			if (prop_spec == CDF::PROP_LIST_END)
				break;

			switch (extractPropertyID(prop_spec)) {

				case CDF::BondProperty::ORDER:
					getIntProperty(prop_spec, size_val, dataBuffer);
					setOrder(bond, size_val);
					continue;

				case CDF::BondProperty::RING_FLAG:
					getIntProperty(prop_spec, bool_val, dataBuffer);
					setRingFlag(bond, bool_val);
					continue;

				case CDF::BondProperty::AROMATICITY_FLAG:
					getIntProperty(prop_spec, bool_val, dataBuffer);
					setAromaticityFlag(bond, bool_val);
					continue;

				case CDF::BondProperty::STEREO_CENTER_FLAG:
					getIntProperty(prop_spec, bool_val, dataBuffer);
					setStereoCenterFlag(bond, bool_val);
					continue;

				case CDF::BondProperty::STEREO_2D_FLAG:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					set2DStereoFlag(bond, uint_val);
					continue;

				case CDF::AtomProperty::CIP_CONFIGURATION:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setCIPConfiguration(bond, uint_val);
					continue;

				case CDF::BondProperty::DIRECTION:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setDirection(bond, uint_val);
					continue;

				case CDF::BondProperty::REACTION_CENTER_STATUS:
					getIntProperty(prop_spec, uint_val, dataBuffer);
					setReactionCenterStatus(bond, uint_val);
					continue;

				case CDF::BondProperty::STEREO_DESCRIPTOR: {
					CDFStereoDescr descr(i);

					readStereoDescriptor(prop_spec, descr);
					bondStereoDescrs.push_back(descr);
					continue;
				}

				case CDF::BondProperty::MATCH_CONSTRAINTS:
		
				default:
					handleUnknownProperty(prop_spec, bond, dataBuffer);
			}
		}
	}
}

void Chem::CDFDataReader::readMoleculeProperties(Molecule& mol)
{
	CDF::PropertySpec prop_spec;
	CDF::SizeType size_val;
	std::string str_val;
	double double_val;

	while (true) {
		dataBuffer.getInt(prop_spec);

		if (prop_spec == CDF::PROP_LIST_END)
			break;

		switch (extractPropertyID(prop_spec)) {

			case CDF::MolecularGraphProperty::NAME:
				getStringProperty(prop_spec, str_val, dataBuffer);
				setName(mol, str_val);
				continue;

			case CDF::MolecularGraphProperty::STOICHIOMETRIC_NUMBER:
				getFloatProperty(prop_spec, double_val, dataBuffer);
				setStoichiometricNumber(mol, double_val);
				continue;

			case CDF::MolecularGraphProperty::CONFORMATION_INDEX:
				getIntProperty(prop_spec, size_val, dataBuffer);
				setConformationIndex(mol, size_val);
				continue;

			case CDF::MolecularGraphProperty::MATCH_CONSTRAINTS:

			default:
				handleUnknownProperty(prop_spec, mol, dataBuffer);
		}
	}
}

void Chem::CDFDataReader::handleUnknownProperty(CDF::PropertySpec prop_spec, Atom& atom, Internal::ByteBuffer& data)
{
	throw Base::IOError("CDFDataReader: unsupported atom property");
}

void Chem::CDFDataReader::handleUnknownProperty(CDF::PropertySpec prop_spec, Bond& bond, Internal::ByteBuffer& data)
{
	throw Base::IOError("CDFDataReader: unsupported bond property");
}

void Chem::CDFDataReader::handleUnknownProperty(CDF::PropertySpec prop_spec, Molecule& mol, Internal::ByteBuffer& data)
{
	throw Base::IOError("CDFDataReader: unsupported molecule property");
}

void Chem::CDFDataReader::setStereoDescriptors(Molecule& mol) const
{
	for (StereoDescrList::const_iterator it = atomStereoDescrs.begin(), end = atomStereoDescrs.end(); it != end; ++it)
		setStereoDescriptor(mol.getAtom(it->objIndex), mol, *it);

	for (StereoDescrList::const_iterator it = bondStereoDescrs.begin(), end = bondStereoDescrs.end(); it != end; ++it)
		setStereoDescriptor(mol.getBond(it->objIndex), mol, *it);
}

template <typename T>
void Chem::CDFDataReader::setStereoDescriptor(T& obj, const Molecule& mol, const CDFStereoDescr& descr) const
{
	switch (descr.numRefAtoms) {

		case 0:
			Chem::setStereoDescriptor(obj, StereoDescriptor(descr.config));
			return;

		case 3:
			Chem::setStereoDescriptor(obj, StereoDescriptor(descr.config,
															mol.getAtom(descr.refAtomInds[0] + startAtomIdx),
															mol.getAtom(descr.refAtomInds[1] + startAtomIdx),
															mol.getAtom(descr.refAtomInds[2] + startAtomIdx)));
			return;

		case 4:
			Chem::setStereoDescriptor(obj, StereoDescriptor(descr.config,
															mol.getAtom(descr.refAtomInds[0] + startAtomIdx),
															mol.getAtom(descr.refAtomInds[1] + startAtomIdx),
															mol.getAtom(descr.refAtomInds[2] + startAtomIdx),
															mol.getAtom(descr.refAtomInds[3] + startAtomIdx)));
			return;

		default:
			throw Base::IOError("CDFDataReader: invalid number of stereo reference atoms");
	}
}

void Chem::CDFDataReader::readStereoDescriptor(CDF::PropertySpec prop_spec, CDFStereoDescr& descr)
{
	getIntProperty(prop_spec, descr.config, dataBuffer);
	dataBuffer.getInt(descr.numRefAtoms, 1);

	if (descr.numRefAtoms > 4)
		throw Base::IOError("CDFDataReader: more than four stereo reference atoms");

	for (std::size_t i = 0, len; i < descr.numRefAtoms; i++) {
		dataBuffer.getInt(len, 1);
		dataBuffer.getInt(descr.refAtomInds[i], len);
	}
}
