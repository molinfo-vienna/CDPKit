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

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"

#include "CDFDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


void Biomol::CDFDataWriter::outputExternalProperties(const Chem::Atom& atom, Internal::ByteBuffer& data) 
{
	dataBuffer.setIOPointer(0);

	if (hasResidueAtomName(atom))
		putStringProperty(CDF::AtomProperty::RESIDUE_ATOM_NAME, getResidueAtomName(atom), dataBuffer);

	if (hasResidueAltAtomName(atom))
		putStringProperty(CDF::AtomProperty::RESIDUE_ALT_ATOM_NAME, getResidueAtomName(atom), dataBuffer);

	if (hasResidueLeavingAtomFlag(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG, CDF::BoolType(getResidueLeavingAtomFlag(atom)), dataBuffer);

	if (hasResidueLinkingAtomFlag(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_LINKING_ATOM_FLAG, CDF::BoolType(getResidueLinkingAtomFlag(atom)), dataBuffer);

	if (hasResidueCode(atom))
		putStringProperty(CDF::AtomProperty::RESIDUE_CODE, getResidueCode(atom), dataBuffer);

	if (hasResidueSequenceNumber(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_SEQUENCE_NUMBER, boost::numeric_cast<CDF::SizeType>(getResidueSequenceNumber(atom)), dataBuffer);

	if (hasResidueInsertionCode(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_INSERTION_CODE, boost::numeric_cast<CDF::CharType>(getResidueInsertionCode(atom)), dataBuffer);

	if (hasChainID(atom))
		putIntProperty(CDF::AtomProperty::CHAIN_ID, boost::numeric_cast<CDF::CharType>(getChainID(atom)), dataBuffer);

	if (hasModelNumber(atom))
		putIntProperty(CDF::AtomProperty::MODEL_NUMBER, boost::numeric_cast<CDF::SizeType>(getModelNumber(atom)), dataBuffer);

	if (hasSerialNumber(atom))
		putIntProperty(CDF::AtomProperty::SERIAL_NUMBER, boost::numeric_cast<CDF::SizeType>(getSerialNumber(atom)), dataBuffer);

	if (hasHeteroAtomFlag(atom))
		putIntProperty(CDF::AtomProperty::HETERO_ATOM_FLAG, CDF::BoolType(getHeteroAtomFlag(atom)), dataBuffer);

	if (dataBuffer.getIOPointer() == 0)
		return;

	dataBuffer.resize(dataBuffer.getIOPointer());

	putPropertyListMarker(CDF::AtomProperty::BIOMOL_PROP_LIST, data);

	data.putBytes(dataBuffer);

	putPropertyListMarker(CDF::PROP_LIST_END, data);
}

void Biomol::CDFDataWriter::outputExternalProperties(const Chem::Bond& bond, Internal::ByteBuffer& data) 
{}

void Biomol::CDFDataWriter::outputExternalProperties(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& data) 
{
	dataBuffer.setIOPointer(0);

	if (hasResidueCode(molgraph))
		putStringProperty(CDF::MolecularGraphProperty::RESIDUE_CODE, getResidueCode(molgraph), dataBuffer);

	if (hasResidueSequenceNumber(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER, boost::numeric_cast<CDF::SizeType>(getResidueSequenceNumber(molgraph)), dataBuffer);

	if (hasResidueInsertionCode(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::RESIDUE_INSERTION_CODE, boost::numeric_cast<CDF::CharType>(getResidueInsertionCode(molgraph)), dataBuffer);

	if (hasChainID(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::CHAIN_ID, boost::numeric_cast<CDF::CharType>(getChainID(molgraph)), dataBuffer);

	if (hasModelNumber(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::MODEL_NUMBER, boost::numeric_cast<CDF::SizeType>(getModelNumber(molgraph)), dataBuffer);

	if (dataBuffer.getIOPointer() == 0)
		return;

	dataBuffer.resize(dataBuffer.getIOPointer());

	putPropertyListMarker(CDF::MolecularGraphProperty::BIOMOL_PROP_LIST, data);

	data.putBytes(dataBuffer);

	putPropertyListMarker(CDF::PROP_LIST_END, data);
}

void Biomol::CDFDataWriter::init()
{
    Chem::CDFDataWriter::init();

    strictErrorChecking(getStrictErrorCheckingParameter(getIOBase())); 
    singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(getIOBase()));
}
