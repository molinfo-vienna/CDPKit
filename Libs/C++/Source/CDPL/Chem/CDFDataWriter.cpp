/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriter.cpp 
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

#include <ostream>
#include <cassert>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"

#include "CDFDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Chem::CDFDataWriter::writeMolGraph(std::ostream& os, const MolecularGraph& molgraph)
{
	writeMolGraph(molgraph, dataBuffer);

	return writeRecordData(os);
}

void Chem::CDFDataWriter::writeMolGraph(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf)
{
	init();

	bbuf.setIOPointer(CDF::HEADER_SIZE);

	outputAtoms(molgraph, bbuf);
	outputBonds(molgraph, bbuf);
	outputMolGraphProperties(molgraph, bbuf);

	bbuf.resize(bbuf.getIOPointer());

	outputMolGraphHeader(molgraph, bbuf);
}

void Chem::CDFDataWriter::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ctrlParams)); 
	singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(ctrlParams));
}

const Base::ControlParameterContainer& Chem::CDFDataWriter::getCtrlParameters() const
{
    return ctrlParams;
}

void Chem::CDFDataWriter::outputMolGraphHeader(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf) const
{
	CDF::Header cdf_header;

	cdf_header.recordDataLength = boost::numeric_cast<CDF::SizeType>(bbuf.getSize() - CDF::HEADER_SIZE);
	cdf_header.recordTypeID = CDF::MOLECULE_RECORD_ID;
	cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	bbuf.setIOPointer(0);

	putHeader(cdf_header, bbuf);
}

void Chem::CDFDataWriter::outputAtoms(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf)
{
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getNumAtoms()), false);

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); 
		 it != end; ++it) {

		const Atom& atom = *it;

		if (hasType(atom))
			putIntProperty(CDF::AtomProperty::TYPE, boost::numeric_cast<CDF::UIntType>(getType(atom)), bbuf);

		if (hasFormalCharge(atom))
			putIntProperty(CDF::AtomProperty::FORMAL_CHARGE, boost::numeric_cast<CDF::LongType>(getFormalCharge(atom)), bbuf);

		if (hasSymbol(atom))
			putStringProperty(CDF::AtomProperty::SYMBOL, getSymbol(atom), bbuf);

		if (hasName(atom))
			putStringProperty(CDF::AtomProperty::NAME, getName(atom), bbuf);
	
		if (hasIsotope(atom))
			putIntProperty(CDF::AtomProperty::ISOTOPE, boost::numeric_cast<CDF::SizeType>(getIsotope(atom)), bbuf);

		if (hasRingFlag(atom))
			putIntProperty(CDF::AtomProperty::RING_FLAG, CDF::BoolType(getRingFlag(atom)), bbuf);

		if (hasAromaticityFlag(atom))
			putIntProperty(CDF::AtomProperty::AROMATICITY_FLAG, CDF::BoolType(getAromaticityFlag(atom)), bbuf);

		if (hasRadicalType(atom))
			putIntProperty(CDF::AtomProperty::RADICAL_TYPE, boost::numeric_cast<CDF::UIntType>(getRadicalType(atom)), bbuf);

		if (hasHybridizationState(atom))
			putIntProperty(CDF::AtomProperty::HYBRIDIZATION, boost::numeric_cast<CDF::UIntType>(getHybridizationState(atom)), bbuf);

		if (hasUnpairedElectronCount(atom))
			putIntProperty(CDF::AtomProperty::UNPAIRED_ELECTRON_COUNT, boost::numeric_cast<CDF::SizeType>(getUnpairedElectronCount(atom)), bbuf);
	
		if (hasImplicitHydrogenCount(atom))
			putIntProperty(CDF::AtomProperty::IMPLICIT_HYDROGEN_COUNT, boost::numeric_cast<CDF::SizeType>(getImplicitHydrogenCount(atom)), bbuf);

		if (has2DCoordinates(atom))
			putVectorProperty(CDF::AtomProperty::COORDINATES_2D, get2DCoordinates(atom), bbuf);

		if (has3DCoordinates(atom))
			putVectorProperty(CDF::AtomProperty::COORDINATES_3D, get3DCoordinates(atom), bbuf);

		if (has3DCoordinatesArray(atom))
			putVectorArrayProperty(CDF::AtomProperty::COORDINATES_3D_ARRAY, *get3DCoordinatesArray(atom), bbuf);

		if (hasCIPConfiguration(atom))
			putIntProperty(CDF::AtomProperty::CIP_CONFIGURATION, boost::numeric_cast<CDF::UIntType>(getCIPConfiguration(atom)), bbuf);

		if (hasComponentGroupID(atom))
			putIntProperty(CDF::AtomProperty::COMPONENT_GROUP_ID, boost::numeric_cast<CDF::SizeType>(getComponentGroupID(atom)), bbuf);

		if (hasReactionCenterStatus(atom))
			putIntProperty(CDF::AtomProperty::REACTION_CENTER_STATUS, boost::numeric_cast<CDF::UIntType>(getReactionCenterStatus(atom)), bbuf);

		if (hasReactionAtomMappingID(atom))
			putIntProperty(CDF::AtomProperty::REACTION_ATOM_MAPPING_ID, boost::numeric_cast<CDF::SizeType>(getReactionAtomMappingID(atom)), bbuf);

		if (hasStereoDescriptor(atom))
			putStereoDescriptor(molgraph, CDF::AtomProperty::STEREO_DESCRIPTOR, getStereoDescriptor(atom), bbuf);

		// CDF::AtomProperty::MATCH_CONSTRAINTS // TODO

		outputExtendedProperties(atom, bbuf);

		putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
	}
}

void Chem::CDFDataWriter::outputBonds(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf)
{
	bbuf.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getNumBonds()), false);

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); 
		 it != end; ++it) {

		const Bond& bond = *it;
		std::size_t old_io_ptr = bbuf.getIOPointer();

		bbuf.setIOPointer(old_io_ptr + sizeof(CDF::BondAtomIndexLengthTuple));

		std::size_t num_idx1_bytes = bbuf.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getAtomIndex(bond.getBegin())), true);
		std::size_t num_idx2_bytes = bbuf.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getAtomIndex(bond.getEnd())), true);
		std::size_t new_io_ptr = bbuf.getIOPointer();

		assert(num_idx1_bytes < (1 << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS));
		assert(num_idx2_bytes < (1 << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS));

		CDF::BondAtomIndexLengthTuple idx_lengths = ((num_idx1_bytes << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS) + num_idx2_bytes);

		bbuf.setIOPointer(old_io_ptr);
		bbuf.putInt(idx_lengths, false);
		bbuf.setIOPointer(new_io_ptr);

		if (hasOrder(bond))
			putIntProperty(CDF::BondProperty::ORDER, boost::numeric_cast<CDF::SizeType>(getOrder(bond)), bbuf);

		if (hasRingFlag(bond))
			putIntProperty(CDF::BondProperty::RING_FLAG, CDF::BoolType(getRingFlag(bond)), bbuf);

		if (hasAromaticityFlag(bond))
			putIntProperty(CDF::BondProperty::AROMATICITY_FLAG, CDF::BoolType(getAromaticityFlag(bond)), bbuf);

		if (has2DStereoFlag(bond))
			putIntProperty(CDF::BondProperty::STEREO_2D_FLAG, boost::numeric_cast<CDF::UIntType>(get2DStereoFlag(bond)), bbuf);

		if (hasCIPConfiguration(bond))
			putIntProperty(CDF::BondProperty::CIP_CONFIGURATION, boost::numeric_cast<CDF::UIntType>(getCIPConfiguration(bond)), bbuf);

		if (hasDirection(bond))
			putIntProperty(CDF::BondProperty::DIRECTION, boost::numeric_cast<CDF::UIntType>(getDirection(bond)), bbuf);

		if (hasReactionCenterStatus(bond))
			putIntProperty(CDF::BondProperty::REACTION_CENTER_STATUS, boost::numeric_cast<CDF::UIntType>(getReactionCenterStatus(bond)), bbuf);

		if (hasStereoDescriptor(bond))
			putStereoDescriptor(molgraph, CDF::BondProperty::STEREO_DESCRIPTOR, getStereoDescriptor(bond), bbuf);

		// CDF::BondProperty::MATCH_CONSTRAINTS // TODO

		outputExtendedProperties(bond, bbuf);

		putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
	}
}

void Chem::CDFDataWriter::outputMolGraphProperties(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf)
{
	if (hasName(molgraph))
		putStringProperty(CDF::MolecularGraphProperty::NAME, getName(molgraph), bbuf);

	if (hasStoichiometricNumber(molgraph))
		putFloatProperty(CDF::MolecularGraphProperty::STOICHIOMETRIC_NUMBER, getStoichiometricNumber(molgraph), bbuf);

	if (hasConformationIndex(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::CONFORMATION_INDEX, boost::numeric_cast<CDF::SizeType>(getConformationIndex(molgraph)), bbuf);

	// CDF::MolecularGraphProperty::MATCH_CONSTRAINTS // TODO

	outputExtendedProperties(molgraph, bbuf);

	putPropertyListMarker(CDF::PROP_LIST_END, bbuf);
}

template <typename T>
void Chem::CDFDataWriter::outputExtendedProperties(const T& obj, Internal::ByteBuffer& bbuf)
{
	extDataBuffer.setIOPointer(0);

	outputExtendedProperties(obj, extDataBuffer);

	if (extDataBuffer.getIOPointer() == 0)
		return;

	putPropertyListMarker(CDF::PROP_LIST_END, extDataBuffer);

	std::size_t ext_data_len = extDataBuffer.getIOPointer();

	extDataBuffer.resize(ext_data_len);

	putIntProperty(CDF::EXTENDED_PROP_LIST, boost::numeric_cast<CDF::SizeType>(ext_data_len), bbuf);

	bbuf.putBytes(extDataBuffer);
}

void Chem::CDFDataWriter::outputExtendedProperties(const Atom& atom, Internal::ByteBuffer& bbuf) 
{}

void Chem::CDFDataWriter::outputExtendedProperties(const Bond& bond, Internal::ByteBuffer& bbuf) 
{}

void Chem::CDFDataWriter::outputExtendedProperties(const MolecularGraph& molgraph, Internal::ByteBuffer& bbuf) 
{}

void Chem::CDFDataWriter::putStereoDescriptor(const MolecularGraph& molgraph, unsigned int prop_id, 
											  const StereoDescriptor& descr, Internal::ByteBuffer& bbuf) const
{
	putIntProperty(prop_id, boost::numeric_cast<CDF::UIntType>(descr.getConfiguration()), bbuf);

	std::size_t num_ref_atoms = descr.getNumReferenceAtoms();

	bbuf.putInt(boost::numeric_cast<Base::uint8>(num_ref_atoms), false);

	for (std::size_t i = 0; i < num_ref_atoms; i++) {
		std::size_t old_io_pos = bbuf.getIOPointer();

		bbuf.setIOPointer(old_io_pos + 1);

		std::size_t num_bytes = bbuf.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getAtomIndex(*descr.getReferenceAtoms()[i])), true);
		std::size_t new_io_pos = bbuf.getIOPointer();

		bbuf.setIOPointer(old_io_pos);
		bbuf.putInt(boost::numeric_cast<Base::uint8>(num_bytes), false);
		bbuf.setIOPointer(new_io_pos);
	}
}

bool Chem::CDFDataWriter::writeRecordData(std::ostream& os)
{
	dataBuffer.writeBuffer(os);

	return os.good();
}
