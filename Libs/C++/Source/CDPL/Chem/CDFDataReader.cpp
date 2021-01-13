/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataReader.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "CDFDataReader.hpp"


using namespace CDPL;


Chem::CDFDataReader::AtomPropertyHandlerList      Chem::CDFDataReader::extAtomPropertyHandlers;
Chem::CDFDataReader::BondPropertyHandlerList      Chem::CDFDataReader::extBondPropertyHandlers;
Chem::CDFDataReader::MoleculePropertyHandlerList  Chem::CDFDataReader::extMoleculePropertyHandlers;


bool Chem::CDFDataReader::hasMoreMoleculeData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::MOLECULE_RECORD_ID, true, dataBuffer);
}

bool Chem::CDFDataReader::hasMoreReactionData(std::istream& is)
{
	init();

	CDF::Header header;

	return CDFDataReaderBase::skipToRecord(is, header, CDF::REACTION_RECORD_ID, true, dataBuffer);
}

bool Chem::CDFDataReader::readMolecule(std::istream& is, Molecule& mol)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::MOLECULE_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);
	readConnectionTable(mol, dataBuffer);

	return true;
}

bool Chem::CDFDataReader::readReaction(std::istream& is, Reaction& rxn)
{
	init();

	CDF::Header header;

	if (!skipToRecord(is, header, CDF::REACTION_RECORD_ID, false, dataBuffer))
		return false;

	readData(is, header.recordDataLength, dataBuffer);

	dataBuffer.setIOPointer(0);
	readReactionComponents(rxn, dataBuffer);

	return true;
}

bool Chem::CDFDataReader::skipMolecule(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::MOLECULE_RECORD_ID, dataBuffer);
}

bool Chem::CDFDataReader::skipReaction(std::istream& is)
{
	init();

	return skipNextRecord(is, CDF::REACTION_RECORD_ID, dataBuffer);
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

	readConnectionTable(mol, bbuf);

	return true;
}

bool Chem::CDFDataReader::readReaction(Reaction& rxn, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(0);

	CDF::Header header;

	if (!getHeader(header, bbuf))
		return false;

	if (header.recordTypeID != CDF::REACTION_RECORD_ID) {
		if (strictErrorChecking())
			throw Base::IOError("CDFDataReader: trying to read a non-reaction record");

		return false;
	}

	readReactionComponents(rxn, bbuf);

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

void Chem::CDFDataReader::readReactionComponents(Reaction& rxn, Internal::ByteBuffer& bbuf)
{
	unsigned int rxn_roles[] = { ReactionRole::REACTANT, ReactionRole::AGENT, ReactionRole::PRODUCT };

	for (std::size_t i = 0; i < 3; i++) {
		CDF::SizeType num_comps; bbuf.getInt(num_comps);

		for (std::size_t j = 0; j < num_comps; j++) {
			Molecule& mol = rxn.addComponent(rxn_roles[i]);

			readConnectionTable(mol, bbuf);
		}
	}

	readReactionProperties(rxn, bbuf);
}

void Chem::CDFDataReader::readConnectionTable(Molecule& mol, Internal::ByteBuffer& bbuf)
{
	atomStereoDescrs.clear();
	bondStereoDescrs.clear();

	startAtomIdx = mol.getNumAtoms();

	std::size_t num_atoms = readAtoms(mol, bbuf);

	readBonds(mol, bbuf, num_atoms);
	readMoleculeProperties(mol, bbuf);
	setStereoDescriptors(mol);
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

	bool multi_conf = getMultiConfImportParameter(ctrlParams);
	std::size_t num_coords_arrays = 0;

	bbuf.getInt(num_atoms);
	mol.reserveMemoryForAtoms(num_atoms);

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
					getCVectorProperty(prop_spec, coords_2d_val, bbuf);
					set2DCoordinates(atom, coords_2d_val);
					continue;

				case CDF::AtomProperty::COORDINATES_3D:
					getCVectorProperty(prop_spec, coords_3d_val, bbuf);
					set3DCoordinates(atom, coords_3d_val);
					continue;

				case CDF::AtomProperty::COORDINATES_3D_ARRAY: {
					Math::Vector3DArray::SharedPointer va_ptr(new Math::Vector3DArray());

					getCVectorArrayProperty(prop_spec, *va_ptr, bbuf);
					
					if (multi_conf) {
						set3DCoordinatesArray(atom, va_ptr);
						num_coords_arrays++;
					}

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

				case CDF::AtomProperty::ATOM_MAPPING_ID:
					getIntProperty(prop_spec, size_val, bbuf);
					setAtomMappingID(atom, size_val);
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

	if (multi_conf && num_coords_arrays < num_atoms) {
		for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
			Atom& atom = *it;

			if (has3DCoordinatesArray(atom))
				continue;

			Math::Vector3DArray::SharedPointer va_ptr(new Math::Vector3DArray());

			if (has3DCoordinates(atom))
				va_ptr->addElement(get3DCoordinates(atom));

			set3DCoordinatesArray(atom, va_ptr);
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
	mol.reserveMemoryForBonds(num_bonds);

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
	Base::uint64 uint64_val;
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

			case CDF::MolecularGraphProperty::CONFORMER_ENERGIES: {
				Util::DArray::SharedPointer array_ptr(new Util::DArray());

				getFloatArrayProperty(prop_spec, *array_ptr, bbuf);
				setConformerEnergies(mol, array_ptr);
				continue;
			}

			case CDF::MolecularGraphProperty::STRUCTURE_DATA:
				setStructureData(mol, readStringData(prop_spec, bbuf));
				continue;

			case CDF::MolecularGraphProperty::SSSR:
				setSSSR(mol, readFragmentList(mol, prop_spec, bbuf));
				continue;

			case CDF::MolecularGraphProperty::HASH_CODE:
				getIntProperty(prop_spec, uint64_val, bbuf);
				setHashCode(mol, uint64_val);
				continue;

			case CDF::MolecularGraphProperty::MATCH_CONSTRAINTS:

			default:
				throw Base::IOError("CDFDataReader: unsupported molecule property");
		}
	}
}

void Chem::CDFDataReader::readReactionProperties(Reaction& rxn, Internal::ByteBuffer& bbuf)
{
	CDF::PropertySpec prop_spec;
	std::string str_val;

	while (true) {
		unsigned int prop_id = getPropertySpec(prop_spec, bbuf);

		if (prop_id == CDF::PROP_LIST_END)
			break;

		switch (prop_id) {

			case CDF::ReactionProperty::NAME:
				getStringProperty(prop_spec, str_val, bbuf);
				setName(rxn, str_val);
				continue;
			
			case CDF::ReactionProperty::REACTION_DATA:
				setReactionData(rxn, readStringData(prop_spec, bbuf));
				continue;

			case CDF::ReactionProperty::MATCH_CONSTRAINTS:

			default:
				throw Base::IOError("CDFDataReader: unsupported reaction property");
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

Chem::FragmentList::SharedPointer Chem::CDFDataReader::readFragmentList(const Molecule& mol, CDF::PropertySpec prop_spec, Internal::ByteBuffer& bbuf) const
{
	FragmentList::SharedPointer frag_list(new FragmentList());
	CDF::SizeType num_entries;

	getIntProperty(prop_spec, num_entries, bbuf);

	for (CDF::SizeType i = 0; i < num_entries; i++) {
		Fragment::SharedPointer frag(new Fragment());
		CDF::SizeType num_atoms;

		bbuf.getInt(num_atoms);
		
		for (CDF::SizeType j = 0; j < num_atoms; j++) {
			CDF::SizeType atom_idx;

			bbuf.getInt(atom_idx);

			frag->addAtom(mol.getAtom(atom_idx));
		}

		CDF::SizeType num_bonds;

		bbuf.getInt(num_bonds);
		
		for (CDF::SizeType j = 0; j < num_bonds; j++) {
			CDF::SizeType bond_idx;

			bbuf.getInt(bond_idx);

			frag->addBond(mol.getBond(bond_idx));
		}

		frag_list->addElement(frag);
	}

	return frag_list;
}

Chem::StringDataBlock::SharedPointer Chem::CDFDataReader::readStringData(CDF::PropertySpec prop_spec, Internal::ByteBuffer& bbuf) const
{
	StringDataBlock::SharedPointer sdata(new StringDataBlock());
	CDF::SizeType num_entries;

	getIntProperty(prop_spec, num_entries, bbuf);

	std::string header, data;

	for (CDF::SizeType i = 0; i < num_entries; i++) {
		getString(header, bbuf);
		getString(data, bbuf);

		sdata->addEntry(header, data);
	}

	return sdata;
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
