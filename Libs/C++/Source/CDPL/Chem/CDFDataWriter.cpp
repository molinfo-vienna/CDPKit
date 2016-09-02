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
#include "CDPL/Base/DataIOBase.hpp"

#include "CDFDataWriter.hpp"


using namespace CDPL;


bool Chem::CDFDataWriter::writeMolGraph(std::ostream& os, const MolecularGraph& molgraph)
{
	init();

	outputMolGraphHeader(molgraph);
	outputAtoms(molgraph);
	outputBonds(molgraph);
	outputMolGraphProperties(molgraph);

	return writeRecordData(os);
}

void Chem::CDFDataWriter::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ioBase)); 
	singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(ioBase));

	dataBuffer.setIOPointer(0);
}

const Base::DataIOBase& Chem::CDFDataWriter::getIOBase() const
{
    return ioBase;
}

void Chem::CDFDataWriter::outputMolGraphHeader(const MolecularGraph& molgraph)
{
	cdfHeader.recordTypeID = CDF::MOLECULE_RECORD_ID;
	cdfHeader.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	dataBuffer.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getNumAtoms()), false);
	dataBuffer.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getNumBonds()), false);
}

void Chem::CDFDataWriter::outputAtoms(const MolecularGraph& molgraph)
{
	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); 
		 it != end; ++it) {

		const Atom& atom = *it;

		if (hasType(atom))
			putIntProperty(CDF::AtomProperty::TYPE, boost::numeric_cast<CDF::UIntType>(getType(atom)), dataBuffer);

		if (hasFormalCharge(atom))
			putIntProperty(CDF::AtomProperty::FORMAL_CHARGE, boost::numeric_cast<CDF::LongType>(getFormalCharge(atom)), dataBuffer);

		if (hasSymbol(atom))
			putStringProperty(CDF::AtomProperty::SYMBOL, getSymbol(atom), dataBuffer);

		if (hasName(atom))
			putStringProperty(CDF::AtomProperty::NAME, getName(atom), dataBuffer);
	
		if (hasIsotope(atom))
			putIntProperty(CDF::AtomProperty::ISOTOPE, boost::numeric_cast<CDF::SizeType>(getIsotope(atom)), dataBuffer);

		if (hasRingFlag(atom))
			putIntProperty(CDF::AtomProperty::RING_FLAG, CDF::BoolType(getRingFlag(atom)), dataBuffer);

		if (hasAromaticityFlag(atom))
			putIntProperty(CDF::AtomProperty::AROMATICITY_FLAG, CDF::BoolType(getAromaticityFlag(atom)), dataBuffer);

		if (hasRadicalType(atom))
			putIntProperty(CDF::AtomProperty::RADICAL_TYPE, boost::numeric_cast<CDF::UIntType>(getRadicalType(atom)), dataBuffer);

		if (hasHybridizationState(atom))
			putIntProperty(CDF::AtomProperty::HYBRIDIZATION, boost::numeric_cast<CDF::UIntType>(getHybridizationState(atom)), dataBuffer);

		if (hasUnpairedElectronCount(atom))
			putIntProperty(CDF::AtomProperty::UNPAIRED_ELECTRON_COUNT, boost::numeric_cast<CDF::SizeType>(getUnpairedElectronCount(atom)), dataBuffer);
	
		if (hasImplicitHydrogenCount(atom))
			putIntProperty(CDF::AtomProperty::IMPLICIT_HYDROGEN_COUNT, boost::numeric_cast<CDF::SizeType>(getImplicitHydrogenCount(atom)), dataBuffer);

		if (has2DCoordinates(atom))
			putVectorProperty(CDF::AtomProperty::COORDINATES_2D, get2DCoordinates(atom), dataBuffer);

		if (has3DCoordinates(atom))
			putVectorProperty(CDF::AtomProperty::COORDINATES_3D, get3DCoordinates(atom), dataBuffer);

		if (has3DCoordinatesArray(atom))
			putVectorArrayProperty(CDF::AtomProperty::COORDINATES_3D_ARRAY, *get3DCoordinatesArray(atom), dataBuffer);

		if (hasCIPConfiguration(atom))
			putIntProperty(CDF::AtomProperty::CIP_CONFIGURATION, boost::numeric_cast<CDF::UIntType>(getCIPConfiguration(atom)), dataBuffer);

		if (hasComponentGroupID(atom))
			putIntProperty(CDF::AtomProperty::COMPONENT_GROUP_ID, boost::numeric_cast<CDF::SizeType>(getComponentGroupID(atom)), dataBuffer);

		if (hasReactionCenterStatus(atom))
			putIntProperty(CDF::AtomProperty::REACTION_CENTER_STATUS, boost::numeric_cast<CDF::UIntType>(getReactionCenterStatus(atom)), dataBuffer);

		if (hasReactionAtomMappingID(atom))
			putIntProperty(CDF::AtomProperty::REACTION_ATOM_MAPPING_ID, boost::numeric_cast<CDF::SizeType>(getReactionAtomMappingID(atom)), dataBuffer);

		if (hasStereoDescriptor(atom))
			putStereoDescriptor(molgraph, CDF::AtomProperty::STEREO_DESCRIPTOR, getStereoDescriptor(atom));

		// CDF::AtomProperty::MATCH_CONSTRAINTS // TODO

		outputExternalProperties(atom, dataBuffer);

		putPropertyListMarker(CDF::PROP_LIST_END, dataBuffer);
	}
}

void Chem::CDFDataWriter::outputBonds(const MolecularGraph& molgraph)
{
	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); 
		 it != end; ++it) {

		const Bond& bond = *it;
		std::size_t old_io_ptr = dataBuffer.getIOPointer();

		dataBuffer.setIOPointer(old_io_ptr + sizeof(CDF::BondAtomIndexLengthTuple));

		std::size_t num_idx1_bytes = dataBuffer.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getAtomIndex(bond.getBegin())), true);
		std::size_t num_idx2_bytes = dataBuffer.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getAtomIndex(bond.getEnd())), true);
		std::size_t new_io_ptr = dataBuffer.getIOPointer();

		assert(num_idx1_bytes < (1 << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS));
		assert(num_idx2_bytes < (1 << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS));

		CDF::BondAtomIndexLengthTuple idx_lengths = ((num_idx1_bytes << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS) + num_idx2_bytes);

		dataBuffer.setIOPointer(old_io_ptr);
		dataBuffer.putInt(idx_lengths, false);
		dataBuffer.setIOPointer(new_io_ptr);

		if (hasOrder(bond))
			putIntProperty(CDF::BondProperty::ORDER, boost::numeric_cast<CDF::SizeType>(getOrder(bond)), dataBuffer);

		if (hasRingFlag(bond))
			putIntProperty(CDF::BondProperty::RING_FLAG, CDF::BoolType(getRingFlag(bond)), dataBuffer);

		if (hasAromaticityFlag(bond))
			putIntProperty(CDF::BondProperty::AROMATICITY_FLAG, CDF::BoolType(getAromaticityFlag(bond)), dataBuffer);

		if (has2DStereoFlag(bond))
			putIntProperty(CDF::BondProperty::STEREO_2D_FLAG, boost::numeric_cast<CDF::UIntType>(get2DStereoFlag(bond)), dataBuffer);

		if (hasCIPConfiguration(bond))
			putIntProperty(CDF::BondProperty::CIP_CONFIGURATION, boost::numeric_cast<CDF::UIntType>(getCIPConfiguration(bond)), dataBuffer);

		if (hasDirection(bond))
			putIntProperty(CDF::BondProperty::DIRECTION, boost::numeric_cast<CDF::UIntType>(getDirection(bond)), dataBuffer);

		if (hasReactionCenterStatus(bond))
			putIntProperty(CDF::BondProperty::REACTION_CENTER_STATUS, boost::numeric_cast<CDF::UIntType>(getReactionCenterStatus(bond)), dataBuffer);

		if (hasStereoDescriptor(bond))
			putStereoDescriptor(molgraph, CDF::BondProperty::STEREO_DESCRIPTOR, getStereoDescriptor(bond));

		// CDF::BondProperty::MATCH_CONSTRAINTS // TODO

		outputExternalProperties(bond, dataBuffer);

		putPropertyListMarker(CDF::PROP_LIST_END, dataBuffer);
	}
}

void Chem::CDFDataWriter::outputMolGraphProperties(const MolecularGraph& molgraph)
{
	if (hasName(molgraph))
		putStringProperty(CDF::MolecularGraphProperty::NAME, getName(molgraph), dataBuffer);

	if (hasStoichiometricNumber(molgraph))
		putFloatProperty(CDF::MolecularGraphProperty::STOICHIOMETRIC_NUMBER, getStoichiometricNumber(molgraph), dataBuffer);

	if (hasConformationIndex(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::CONFORMATION_INDEX, boost::numeric_cast<CDF::SizeType>(getConformationIndex(molgraph)), dataBuffer);

	// CDF::MolecularGraphProperty::MATCH_CONSTRAINTS // TODO

	outputExternalProperties(molgraph, dataBuffer);

	putPropertyListMarker(CDF::PROP_LIST_END, dataBuffer);
}

void Chem::CDFDataWriter::outputExternalProperties(const Atom& atom, Internal::ByteBuffer& data) 
{}

void Chem::CDFDataWriter::outputExternalProperties(const Bond& bond, Internal::ByteBuffer& data) 
{}

void Chem::CDFDataWriter::outputExternalProperties(const MolecularGraph& molgraph, Internal::ByteBuffer& data) 
{}

void Chem::CDFDataWriter::putStereoDescriptor(const MolecularGraph& molgraph, unsigned int prop_id, const StereoDescriptor& descr)
{
	putIntProperty(prop_id, boost::numeric_cast<CDF::UIntType>(descr.getConfiguration()), dataBuffer);

	std::size_t num_ref_atoms = descr.getNumReferenceAtoms();

	dataBuffer.putInt(boost::numeric_cast<Base::uint8>(num_ref_atoms), false);

	for (std::size_t i = 0; i < num_ref_atoms; i++) {
		std::size_t old_io_pos = dataBuffer.getIOPointer();

		dataBuffer.setIOPointer(old_io_pos + 1);

		std::size_t num_bytes = dataBuffer.putInt(boost::numeric_cast<CDF::SizeType>(molgraph.getAtomIndex(*descr.getReferenceAtoms()[i])), true);
		std::size_t new_io_pos = dataBuffer.getIOPointer();

		dataBuffer.setIOPointer(old_io_pos);
		dataBuffer.putInt(boost::numeric_cast<Base::uint8>(num_bytes), false);
		dataBuffer.setIOPointer(new_io_pos);
	}
}

bool Chem::CDFDataWriter::writeRecordData(std::ostream& os)
{
	dataBuffer.resize(dataBuffer.getIOPointer());

	cdfHeader.recordDataLength = boost::numeric_cast<CDF::SizeType>(dataBuffer.getSize());

	if (!writeHeader(os, cdfHeader))
		return false;

	dataBuffer.writeBuffer(os);

	return os.good();
}
