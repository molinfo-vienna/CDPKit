/* 
 * CDFDataReader.cpp 
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

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/CDFDataReader.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CDFDataReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


void Biomol::CDFDataReader::registerExternalPropertyHandlers()
{
	Chem::CDFDataReader::registerExternalAtomPropertyHandler(&readAtomProperties);
	Chem::CDFDataReader::registerExternalMoleculePropertyHandler(&readMoleculeProperties);
}

bool Biomol::CDFDataReader::readAtomProperties(unsigned int handler_id, const Chem::CDFDataReader& reader, 
											   Chem::Atom& atom, Internal::ByteBuffer& data)
{
	if (handler_id != CDF::AtomProperty::PROPERTY_HANDLER_ID)
		return false;

	CDF::PropertySpec prop_spec;
	CDF::CharType char_val;
	CDF::SizeType size_val;
	CDF::LongType long_val;
	CDF::BoolType bool_val;
	std::string string_val;

	while (true) {
		unsigned int prop_id = reader.getPropertySpec(prop_spec, data);

		if (prop_id == CDF::PROP_LIST_END)
			return true;

		switch (prop_id) {

			case CDF::AtomProperty::RESIDUE_ATOM_NAME:
				reader.getStringProperty(prop_spec, string_val, data);
				setResidueAtomName(atom, string_val);
				continue;

			case CDF::AtomProperty::RESIDUE_ALT_ATOM_NAME:
				reader.getStringProperty(prop_spec, string_val, data);
				setResidueAltAtomName(atom, string_val);
				continue;

			case CDF::AtomProperty::RESIDUE_LEAVING_ATOM_FLAG:
				reader.getIntProperty(prop_spec, bool_val, data);
				setResidueLeavingAtomFlag(atom, bool_val);
				continue;

			case CDF::AtomProperty::RESIDUE_LINKING_ATOM_FLAG:
				reader.getIntProperty(prop_spec, bool_val, data);
				setResidueLinkingAtomFlag(atom, bool_val);
				continue;

			case CDF::AtomProperty::RESIDUE_CODE:
				reader.getStringProperty(prop_spec, string_val, data);
				setResidueCode(atom, string_val);
				continue;

			case CDF::AtomProperty::RESIDUE_SEQUENCE_NUMBER:
				reader.getIntProperty(prop_spec, long_val, data);
				setResidueSequenceNumber(atom, long_val);
				continue;

			case CDF::AtomProperty::RESIDUE_INSERTION_CODE:
				reader.getIntProperty(prop_spec, char_val, data);
				setResidueInsertionCode(atom, char_val);
				continue;

			case CDF::AtomProperty::HETERO_ATOM_FLAG:
				reader.getIntProperty(prop_spec, bool_val, data);
				setHeteroAtomFlag(atom, bool_val);
				continue;

			case CDF::AtomProperty::CHAIN_ID:
				reader.getStringProperty(prop_spec, string_val, data);
				setChainID(atom, string_val);
				continue;

			case CDF::AtomProperty::MODEL_NUMBER:
				reader.getIntProperty(prop_spec, size_val, data);
				setModelNumber(atom, size_val);
				continue;

			case CDF::AtomProperty::SERIAL_NUMBER:
				reader.getIntProperty(prop_spec, long_val, data);
				setSerialNumber(atom, long_val);
				continue;

			default:
				throw Base::IOError("CDFDataReader: unsupported atom property");
		}
	}
}

bool Biomol::CDFDataReader::readMoleculeProperties(unsigned int handler_id, const Chem::CDFDataReader& reader, 
												   Chem::Molecule& mol, Internal::ByteBuffer& data)
{
	if (handler_id != CDF::MolecularGraphProperty::PROPERTY_HANDLER_ID)
		return false;

	CDF::PropertySpec prop_spec;
	CDF::CharType char_val;
	CDF::SizeType size_val;
	CDF::LongType long_val;
	std::string string_val;

	while (true) {
		unsigned int prop_id = reader.getPropertySpec(prop_spec, data);

		if (prop_id == CDF::PROP_LIST_END)
			return true;

		switch (prop_id) {

			case CDF::MolecularGraphProperty::RESIDUE_CODE:
				reader.getStringProperty(prop_spec, string_val, data);
				setResidueCode(mol, string_val);
				continue;

			case CDF::MolecularGraphProperty::RESIDUE_SEQUENCE_NUMBER:
				reader.getIntProperty(prop_spec, long_val, data);
				setResidueSequenceNumber(mol, long_val);
				continue;

			case CDF::MolecularGraphProperty::RESIDUE_INSERTION_CODE:
				reader.getIntProperty(prop_spec, char_val, data);
				setResidueInsertionCode(mol, char_val);
				continue;

			case CDF::MolecularGraphProperty::CHAIN_ID:
				reader.getStringProperty(prop_spec, string_val, data);
				setChainID(mol, string_val);
				continue;

			case CDF::MolecularGraphProperty::MODEL_NUMBER:
				reader.getIntProperty(prop_spec, size_val, data);
				setModelNumber(mol, size_val);
				continue;

			default:
				throw Base::IOError("CDFDataReader: unsupported molecule property");
		}
	}
}
