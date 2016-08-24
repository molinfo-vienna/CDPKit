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
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Math/Vector.hpp"

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

	dataBuffer.setIOPointer(0);
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

/*
		CDF::AtomProperty::COORDINATES_3D_ARRAY
		CDF::AtomProperty::STEREO_DESCRIPTOR
		CDF::AtomProperty::STEREO_CENTER_FLAG
		CDF::AtomProperty::CIP_CONFIGURATION
		CDF::AtomProperty::REACTION_CENTER_STATUS
		CDF::AtomProperty::REACTION_ATOM_MAPPING_ID
		CDF::AtomProperty::MATCH_CONSTRAINTS
		CDF::AtomProperty::COMPONENT_GROUP_ID
*/

		dataBuffer.putInt(CDF::PROP_LIST_END, false);
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

		CDF::BondAtomIndexLengthTuple idx_lengths = (num_idx1_bytes << CDF::NUM_BOND_ATOM_INDEX_LENGTH_BITS) + num_idx2_bytes;

		dataBuffer.setIOPointer(old_io_ptr);
		dataBuffer.putInt(idx_lengths, false);
		dataBuffer.setIOPointer(new_io_ptr);

		if (hasOrder(bond))
			putIntProperty(CDF::BondProperty::ORDER, boost::numeric_cast<CDF::SizeType>(getOrder(bond)), dataBuffer);

		if (hasRingFlag(bond))
			putIntProperty(CDF::BondProperty::RING_FLAG, CDF::BoolType(getRingFlag(bond)), dataBuffer);

		if (hasAromaticityFlag(bond))
			putIntProperty(CDF::BondProperty::AROMATICITY_FLAG, CDF::BoolType(getAromaticityFlag(bond)), dataBuffer);

		if (hasStereoCenterFlag(bond))
			putIntProperty(CDF::BondProperty::STEREO_CENTER_FLAG, CDF::BoolType(getStereoCenterFlag(bond)), dataBuffer);

		if (has2DStereoFlag(bond))
			putIntProperty(CDF::BondProperty::STEREO_2D_FLAG, boost::numeric_cast<CDF::UIntType>(get2DStereoFlag(bond)), dataBuffer);

		/*
		  CDF::BondProperty::STEREO_DESCRIPTOR
		  CDF::BondProperty::CIP_CONFIGURATION
		  CDF::BondProperty::DIRECTION
		  CDF::BondProperty::REACTION_CENTER_STATUS
		  CDF::BondProperty::MATCH_CONSTRAINTS
		*/

		dataBuffer.putInt(CDF::PROP_LIST_END, false);
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

	/*
	CDF::MolecularGraphProperty::MATCH_CONSTRAINTS
	*/

	dataBuffer.putInt(CDF::PROP_LIST_END, false);
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
