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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "CDFDataReader.hpp"


using namespace CDPL;


Chem::CDFDataReader::AtomPropertyHandlerList      Chem::CDFDataReader::extAtomPropertyHandlers;
Chem::CDFDataReader::BondPropertyHandlerList      Chem::CDFDataReader::extBondPropertyHandlers;
Chem::CDFDataReader::MoleculePropertyHandlerList  Chem::CDFDataReader::extMoleculePropertyHandlers;


bool Chem::CDFDataReader::hasMoreData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::MOLECULE_RECORD_ID, true, dataBuffer);
}

bool Chem::CDFDataReader::readMolecule(std::istream& is, Molecule& mol)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::MOLECULE_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);
	atomStereoDescrs.clear();
	bondStereoDescrs.clear();

	startAtomIdx = mol.getNumAtoms();

	std::size_t num_atoms = readAtoms(mol, dataBuffer);

	readBonds(mol, dataBuffer, num_atoms);
	readMoleculeProperties(mol, dataBuffer);
	setStereoDescriptors(mol);

	return true;
}

bool Chem::CDFDataReader::skipMolecule(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::MOLECULE_RECORD_ID, dataBuffer);
}

bool Chem::CDFDataReader::readMolecule(Molecule& mol, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::MOLECULE_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFDataReader: trying to read a non-molecule record");

		return false;
	}

	atomStereoDescrs.clear();
	bondStereoDescrs.clear();

	startAtomIdx = mol.getNumAtoms();

	std::size_t num_atoms = readAtoms(mol, bbuf);

	readBonds(mol, bbuf, num_atoms);
	readMoleculeProperties(mol, bbuf);
	setStereoDescriptors(mol);

	return true;
}

void Chem::CDFDataReader::registerExternalAtomPropertyHandler(const AtomPropertyHandler& handler)
{
	extAtomPropertyHandlers.push_back(handler);
}

void Chem::CDFDataReader::registerExternalBondPropertyHandler(const BondPropertyHandler& handler)
{
	extBondPropertyHandlers.push_back(handler);
}

void Chem::CDFDataReader::registerExternalMoleculePropertyHandler(const MoleculePropertyHandler& handler)
{
	extMoleculePropertyHandlers.push_back(handler);
}

void Chem::CDFDataReader::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
}

const Base::ControlParameterContainer& Chem::CDFDataReader::getCtrlParameters() const
{
    return ctrlParams;
}

std::size_t Chem::CDFDataReader::readAtoms(Molecule& mol, Internal::ByteBuffer& bbuf)
{
	CDF::PropertySpec prop_spec;
	CDF::UIntType uint_val;
	CDF::LongType long_val;
	CDF::SizeType size_val;
	CDF::BoolType bool_val;
	std::string str_val;
	Math::Vector2D coords_2d_val;
	Math::Vector3D coords_3d_val;
	CDF::SizeType num_atoms;

	bbuf.getInt(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++) {
		Atom& atom = mol.addAtom();

		while (true) {
			unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

			if (prop_id == CDF::PROP_LIST_END)
				break;

			switch (prop_id) {

				case CDF::EXTENDED_PROP_LIST:
					readExternalProperties(prop_spec, atom, bbuf);
					continue;

				case CDF::AtomProperty::TYPE:
					getIntProperty(prop_spec, uint_val, bbuf);
					setType(atom, uint_val);
					continue;
					
				case CDF::AtomProperty::FORMAL_CHARGE:
					getIntProperty(prop_spec, long_val, bbuf);
					setFormalCharge(atom, long_val);
					continue;

				case CDF::AtomProperty::SYMBOL:
					getStringProperty(prop_spec, str_val, bbuf);
					setSymbol(atom, str_val);
					continue;

				case CDF::AtomProperty::NAME:
					getStringProperty(prop_spec, str_val, bbuf);
					setName(atom, str_val);
					continue;

				case CDF::AtomProperty::ISOTOPE:
					getIntProperty(prop_spec, size_val, bbuf);
					setIsotope(atom, size_val);
					continue;

				case CDF::AtomProperty::RING_FLAG:
					getIntProperty(prop_spec, bool_val, bbuf);
					setRingFlag(atom, bool_val);
					continue;

				case CDF::AtomProperty::AROMATICITY_FLAG:
					getIntProperty(prop_spec, bool_val, bbuf);
					setAromaticityFlag(atom, bool_val);
					continue;

				case CDF::AtomProperty::RADICAL_TYPE:
					getIntProperty(prop_spec, uint_val, bbuf);
					setRadicalType(atom, uint_val);
					continue;

				case CDF::AtomProperty::HYBRIDIZATION:
					getIntProperty(prop_spec, uint_val, bbuf);
					setHybridizationState(atom, uint_val);
					continue;

				case CDF::AtomProperty::UNPAIRED_ELECTRON_COUNT:
					getIntProperty(prop_spec, size_val, bbuf);
					setUnpairedElectronCount(atom, size_val);
					continue;

				case CDF::AtomProperty::IMPLICIT_HYDROGEN_COUNT:
					getIntProperty(prop_spec, size_val, bbuf);
					setImplicitHydrogenCount(atom, size_val);
					continue;

				case CDF::AtomProperty::COORDINATES_2D:
					getVectorProperty(prop_spec, coords_2d_val, bbuf);
					set2DCoordinates(atom, coords_2d_val);
					continue;

				case CDF::AtomProperty::COORDINATES_3D:
					getVectorProperty(prop_spec, coords_3d_val, bbuf);
					set3DCoordinates(atom, coords_3d_val);
					continue;

				case CDF::AtomProperty::COORDINATES_3D_ARRAY: {
					Math::Vector3DArray::SharedPointer va_ptr(new Math::Vector3DArray());

					getVectorArrayProperty(prop_spec, *va_ptr, bbuf);
					set3DCoordinatesArray(atom, va_ptr);
					continue;
				}

				case CDF::AtomProperty::CIP_CONFIGURATION:
					getIntProperty(prop_spec, uint_val, bbuf);
					setCIPConfiguration(atom, uint_val);
					continue;

				case CDF::AtomProperty::COMPONENT_GROUP_ID:
					getIntProperty(prop_spec, size_val, bbuf);
					setComponentGroupID(atom, size_val);
					continue;

				case CDF::AtomProperty::REACTION_CENTER_STATUS:
					getIntProperty(prop_spec, uint_val, bbuf);
					setReactionCenterStatus(atom, uint_val);
					continue;

				case CDF::AtomProperty::REACTION_ATOM_MAPPING_ID:
					getIntProperty(prop_spec, size_val, bbuf);
					setReactionAtomMappingID(atom, size_val);
					continue;

				case CDF::AtomProperty::STEREO_DESCRIPTOR: {
					CDFStereoDescr descr(i);

					readStereoDescriptor(prop_spec, descr, bbuf);
					atomStereoDescrs.push_back(descr);
					continue;
				}
					
				case CDF::AtomProperty::MATCH_CONSTRAINTS:

				default:
					throw Base::IOError("CDFDataReader: unsupported atom property");
			}
		}
	}

	return num_atoms;
}

void Chem::CDFDataReader::readBonds(Molecule& mol, Internal::ByteBuffer& bbuf, std::size_t num_atoms)
{
	CDF::PropertySpec prop_spec;
	CDF::SizeType size_val;
	CDF::UIntType uint_val;
	CDF::BoolType bool_val;
	CDF::SizeType atom1_idx, atom2_idx;
	CDF::BondAtomIndexLengthTuple idx_lengths;
	CDF::SizeType num_bonds;

	bbuf.getInt(num_bonds);

	for (std::size_t i = 0; i < num_bonds; i++) {
		bbuf.getInt(idx_lengths);

		std::size_t idx1_length = (idx_lengths >> CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS);
		std::size_t idx2_length = (idx_lengths & CDF::BOND_ATOM_INDEX_LENGTH_MASK);

		if (idx1_length > sizeof(CDF::SizeType) || idx2_length > sizeof(CDF::SizeType))
			throw Base::IOError("CDFDataReader: invalid bond atom index byte size specification");

		bbuf.getInt(atom1_idx, idx1_length);
		bbuf.getInt(atom2_idx, idx2_length);

		if (atom1_idx >= num_atoms)
			throw Base::IOError("CDFDataReader: bond start atom index range error");

		if (atom2_idx >= num_atoms)
			throw Base::IOError("CDFDataReader: bond end atom index range error");

		Bond& bond = mol.addBond(atom1_idx + startAtomIdx, atom2_idx + startAtomIdx);

		while (true) {
			unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

			if (prop_id == CDF::PROP_LIST_END)
				break;

			switch (prop_id) {

				case CDF::EXTENDED_PROP_LIST:
					readExternalProperties(prop_spec, bond, bbuf);
					continue;

				case CDF::BondProperty::ORDER:
					getIntProperty(prop_spec, size_val, bbuf);
					setOrder(bond, size_val);
					continue;

				case CDF::BondProperty::RING_FLAG:
					getIntProperty(prop_spec, bool_val, bbuf);
					setRingFlag(bond, bool_val);
					continue;

				case CDF::BondProperty::AROMATICITY_FLAG:
					getIntProperty(prop_spec, bool_val, bbuf);
					setAromaticityFlag(bond, bool_val);
					continue;

				case CDF::BondProperty::STEREO_2D_FLAG:
					getIntProperty(prop_spec, uint_val, bbuf);
					set2DStereoFlag(bond, uint_val);
					continue;

				case CDF::BondProperty::CIP_CONFIGURATION:
					getIntProperty(prop_spec, uint_val, bbuf);
					setCIPConfiguration(bond, uint_val);
					continue;

				case CDF::BondProperty::DIRECTION:
					getIntProperty(prop_spec, uint_val, bbuf);
					setDirection(bond, uint_val);
					continue;

				case CDF::BondProperty::REACTION_CENTER_STATUS:
					getIntProperty(prop_spec, uint_val, bbuf);
					setReactionCenterStatus(bond, uint_val);
					continue;

				case CDF::BondProperty::STEREO_DESCRIPTOR: {
					CDFStereoDescr descr(i);

					readStereoDescriptor(prop_spec, descr, bbuf);
					bondStereoDescrs.push_back(descr);
					continue;
				}

				case CDF::BondProperty::MATCH_CONSTRAINTS:
		
				default:
					throw Base::IOError("CDFDataReader: unsupported bond property");
			}
		}
	}
}

void Chem::CDFDataReader::readMoleculeProperties(Molecule& mol, Internal::ByteBuffer& bbuf)
{
	CDF::PropertySpec prop_spec;
	CDF::SizeType size_val;
	std::string str_val;
	double double_val;

	while (true) {
		unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

		if (prop_id == CDF::PROP_LIST_END)
			break;

		switch (prop_id) {

			case CDF::EXTENDED_PROP_LIST:
				readExternalProperties(prop_spec, mol, bbuf);
				continue;

			case CDF::MolecularGraphProperty::NAME:
				getStringProperty(prop_spec, str_val, bbuf);
				setName(mol, str_val);
				continue;

			case CDF::MolecularGraphProperty::STOICHIOMETRIC_NUMBER:
				getFloatProperty(prop_spec, double_val, bbuf);
				setStoichiometricNumber(mol, double_val);
				continue;

			case CDF::MolecularGraphProperty::CONFORMATION_INDEX:
				getIntProperty(prop_spec, size_val, bbuf);
				setConformationIndex(mol, size_val);
				continue;

			case CDF::MolecularGraphProperty::MATCH_CONSTRAINTS:

			default:
				throw Base::IOError("CDFDataReader: unsupported molecule property");
		}
	}
}

template <typename T>
void Chem::CDFDataReader::readExternalProperties(CDF::PropertySpec prop_spec, T& obj, Internal::ByteBuffer& bbuf)
{
	CDF::SizeType size_val;

	getIntProperty(prop_spec, size_val, bbuf);
	
	unsigned int handler_id = getPropertySpec(prop_spec, bbuf);

	if (!readExternalProperties(handler_id, obj, bbuf))
		bbuf.setIOPointer(bbuf.getIOPointer() + size_val);
}

bool Chem::CDFDataReader::readExternalProperties(unsigned int handler_id, Atom& atom, Internal::ByteBuffer& bbuf)
{
	return (std::find_if(extAtomPropertyHandlers.begin(), extAtomPropertyHandlers.end(),
						 boost::bind(&AtomPropertyHandler::operator(), _1, handler_id, boost::ref(*this), boost::ref(atom), boost::ref(bbuf)))
			!= extAtomPropertyHandlers.end());
}

bool Chem::CDFDataReader::readExternalProperties(unsigned int handler_id, Bond& bond, Internal::ByteBuffer& bbuf)
{
	return (std::find_if(extBondPropertyHandlers.begin(), extBondPropertyHandlers.end(),
						 boost::bind(&BondPropertyHandler::operator(), _1, handler_id, boost::ref(*this), boost::ref(bond), boost::ref(bbuf)))
			!= extBondPropertyHandlers.end());
}

bool Chem::CDFDataReader::readExternalProperties(unsigned int handler_id, Molecule& mol, Internal::ByteBuffer& bbuf)
{
	return (std::find_if(extMoleculePropertyHandlers.begin(), extMoleculePropertyHandlers.end(),
						 boost::bind(&MoleculePropertyHandler::operator(), _1, handler_id, boost::ref(*this), boost::ref(mol), boost::ref(bbuf)))
			!= extMoleculePropertyHandlers.end());
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

void Chem::CDFDataReader::readStereoDescriptor(CDF::PropertySpec prop_spec, CDFStereoDescr& descr, Internal::ByteBuffer& bbuf) const
{
	getIntProperty(prop_spec, descr.config, bbuf);
	bbuf.getInt(descr.numRefAtoms, 1);

	if (descr.numRefAtoms > 4)
		throw Base::IOError("CDFDataReader: more than four stereo reference atoms");

	for (std::size_t i = 0, len; i < descr.numRefAtoms; i++) {
		bbuf.getInt(len, 1);
		bbuf.getInt(descr.refAtomInds[i], len);
	}
}
