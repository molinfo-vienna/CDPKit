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


void Biomol::CDFDataWriter::outputExtendedProperties(const Chem::Atom& atom, Internal::ByteBuffer& data) 
{
	if (hasResidueAtomName(atom))
		putStringProperty(CDF::AtomProperty::RESIDUE_ATOM_NAME, getResidueAtomName(atom), data);

	if (hasResidueAltAtomName(atom))
		putStringProperty(CDF::AtomProperty::RESIDUE_ALT_ATOM_NAME, getResidueAtomName(atom), data);

	if (hasResidueLeavingAtomFlag(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG, CDF::BoolType(getResidueLeavingAtomFlag(atom)), data);

	if (hasResidueLinkingAtomFlag(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_LINKING_ATOM_FLAG, CDF::BoolType(getResidueLinkingAtomFlag(atom)), data);

	if (hasResidueCode(atom))
		putStringProperty(CDF::AtomProperty::RESIDUE_CODE, getResidueCode(atom), data);

	if (hasResidueSequenceNumber(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_SEQUENCE_NUMBER, boost::numeric_cast<CDF::SizeType>(getResidueSequenceNumber(atom)), data);

	if (hasResidueInsertionCode(atom))
		putIntProperty(CDF::AtomProperty::RESIDUE_INSERTION_CODE, boost::numeric_cast<CDF::CharType>(getResidueInsertionCode(atom)), data);

	if (hasChainID(atom))
		putIntProperty(CDF::AtomProperty::CHAIN_ID, boost::numeric_cast<CDF::CharType>(getChainID(atom)), data);

	if (hasModelNumber(atom))
		putIntProperty(CDF::AtomProperty::MODEL_NUMBER, boost::numeric_cast<CDF::SizeType>(getModelNumber(atom)), data);

	if (hasSerialNumber(atom))
		putIntProperty(CDF::AtomProperty::SERIAL_NUMBER, boost::numeric_cast<CDF::SizeType>(getSerialNumber(atom)), data);

	if (hasHeteroAtomFlag(atom))
		putIntProperty(CDF::AtomProperty::HETERO_ATOM_FLAG, CDF::BoolType(getHeteroAtomFlag(atom)), data);
}

void Biomol::CDFDataWriter::outputExtendedProperties(const Chem::MolecularGraph& molgraph, Internal::ByteBuffer& data) 
{
	if (hasResidueCode(molgraph))
		putStringProperty(CDF::MolecularGraphProperty::RESIDUE_CODE, getResidueCode(molgraph), data);

	if (hasResidueSequenceNumber(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER, boost::numeric_cast<CDF::SizeType>(getResidueSequenceNumber(molgraph)), data);

	if (hasResidueInsertionCode(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::RESIDUE_INSERTION_CODE, boost::numeric_cast<CDF::CharType>(getResidueInsertionCode(molgraph)), data);

	if (hasChainID(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::CHAIN_ID, boost::numeric_cast<CDF::CharType>(getChainID(molgraph)), data);

	if (hasModelNumber(molgraph))
		putIntProperty(CDF::MolecularGraphProperty::MODEL_NUMBER, boost::numeric_cast<CDF::SizeType>(getModelNumber(molgraph)), data);
}

void Biomol::CDFDataWriter::init()
{
    Chem::CDFDataWriter::init();

    strictErrorChecking(getStrictErrorCheckingParameter(getIOBase())); 
    singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(getIOBase()));
}
