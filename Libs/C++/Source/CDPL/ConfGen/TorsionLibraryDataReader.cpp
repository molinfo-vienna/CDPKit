/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionLibraryDataReader.cpp 
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

#include <sstream>
#include <cstring>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "TorsionLibraryDataReader.hpp"
#include "TorsionLibraryFormatData.hpp"


using namespace CDPL;


void ConfGen::TorsionLibraryDataReader::read(std::istream& is, TorsionLibrary& lib)
{
    is.seekg(0, std::ios::end);

	std::istream::pos_type data_len = is.tellg();

	if (data_len < 0)
		throw Base::IOError("TorsionLibraryDataReader: could not determine length of input data");

	charBuffer.resize(data_len + std::istream::pos_type(1));

    is.seekg(0, std::ios::beg);

	if (!is.read(&charBuffer[0], data_len) || is.gcount() != std::streamsize(data_len))
		throw Base::IOError("TorsionLibraryDataReader: reading torsion library data failed");
    
	charBuffer[data_len] = 0;

	processData(&charBuffer[0], lib);
}

void ConfGen::TorsionLibraryDataReader::read(const char* data, TorsionLibrary& lib)
{
	std::size_t data_len = std::strlen(data) + 1;

    charBuffer.resize(data_len);

	std::memcpy(&charBuffer[0], data, data_len);

	processData(&charBuffer[0], lib);
}

void ConfGen::TorsionLibraryDataReader::processData(char* data, TorsionLibrary& lib)
{
	using namespace TorsionLibraryFormatData;

	torLibDocument.parse<0>(data);

  	const XMLNode* lib_node = torLibDocument.first_node(LIBRARY_TAG.c_str());

	if (!lib_node)
		throw Base::IOError("TorsionLibraryDataReader: <" + LIBRARY_TAG + "> document root node not found");

	processCategory(lib_node, lib);
}

void ConfGen::TorsionLibraryDataReader::processCategory(const XMLNode* cat_node, TorsionCategory& cat) const
{
	using namespace TorsionLibraryFormatData;

	const XMLAttribute* attr = cat_node->first_attribute(CATEGORY_NAME_ATTR.c_str());
	std::string str;

	if (attr) 
		cat.setName(str = attr->value());
	
	attr = cat_node->first_attribute(CATEGORY_ATOM_TYPE1_ATTR.c_str());

	if (attr) 
		cat.setBondAtom1Type(Chem::AtomDictionary::getType(str = attr->value()));

	attr = cat_node->first_attribute(CATEGORY_ATOM_TYPE2_ATTR.c_str());

	if (attr) 
		cat.setBondAtom2Type(Chem::AtomDictionary::getType(str = attr->value()));
	
	attr = cat_node->first_attribute(CATEGORY_PATTERN_ATTR.c_str());

	if (attr)  {
		cat.setMatchPatternString(attr->value());
		cat.setMatchPattern(parseSMARTS(attr->value()));
	}

	for (const XMLNode* node = cat_node->first_node(); node; node = node->next_sibling()) {
		const char* node_name = node->name();

		if (node_name == CATEGORY_TAG) 
			processCategory(node, cat.addCategory());
		else if (node_name == RULE_TAG)
			processRule(node, cat.addRule());
		else if (node_name != NOTE_TAG)
			throw Base::IOError(std::string("TorsionLibraryDataReader: invalid tag <") + node_name + ">");
	}
}

void ConfGen::TorsionLibraryDataReader::processRule(const XMLNode* rule_node, TorsionRule& rule) const
{
	using namespace TorsionLibraryFormatData;

	const XMLAttribute* attr = rule_node->first_attribute(RULE_PATTERN_ATTR.c_str());

	if (attr) {
		rule.setMatchPattern(parseSMARTS(attr->value()));
		rule.setMatchPatternString(attr->value());

	} else
		throw Base::IOError("TorsionLibraryDataReader: missing rule '" + RULE_PATTERN_ATTR + "' attribute");

	if (!rule.getMatchPattern())
		throw Base::IOError("TorsionLibraryDataReader: empty or invalid rule '" + RULE_PATTERN_ATTR + "' attribute");

	for (const XMLNode* node = rule_node->first_node(); node; node = node->next_sibling()) {
		if (node->name() == ANGLE_LIST_TAG) 
			processAngleList(node, rule);
		else
			throw Base::IOError(std::string("TorsionLibraryDataReader: invalid tag <") + node->name() + ">");
	}
}

void ConfGen::TorsionLibraryDataReader::processAngleList(const XMLNode* ang_list_node, TorsionRule& rule) const
{
	using namespace TorsionLibraryFormatData;

	for (const XMLNode* node = ang_list_node->first_node(); node; node = node->next_sibling()) {
		const char* node_name = node->name();

		if (node_name != ANGLE_TAG)
			throw Base::IOError(std::string("TorsionLibraryDataReader: invalid tag <") + node_name + ">");

		const XMLAttribute* value_attr = node->first_attribute(ANGLE_VALUE_ATTR.c_str());

		if (!value_attr)
			throw Base::IOError("TorsionLibraryDataReader: missing angle entry '" + ANGLE_VALUE_ATTR + "' attribute");

		const XMLAttribute* tol1_attr = node->first_attribute(ANGLE_TOLERANCE1_ATTR.c_str());

		if (!tol1_attr)
			throw Base::IOError("TorsionLibraryDataReader: missing angle entry '" + ANGLE_TOLERANCE1_ATTR + "' attribute");

		const XMLAttribute* tol2_attr = node->first_attribute(ANGLE_TOLERANCE2_ATTR.c_str());

		if (!tol2_attr)
			throw Base::IOError("TorsionLibraryDataReader: missing angle entry '" + ANGLE_TOLERANCE2_ATTR + "' attribute");

		const XMLAttribute* score_attr = node->first_attribute(ANGLE_SCORE_ATTR.c_str());

		if (!score_attr)
			throw Base::IOError("TorsionLibraryDataReader: missing angle entry '" + ANGLE_SCORE_ATTR + "' attribute");

		rule.addAngle(Internal::parseNumber<double>(value_attr->value(), value_attr->value() + std::strlen(value_attr->value()), 
													"TorsionLibraryDataReader: error while parsing torsion angle value"),
					  Internal::parseNumber<double>(tol1_attr->value(), tol1_attr->value() + std::strlen(tol1_attr->value()), 
													"TorsionLibraryDataReader: error while parsing torsion angle tolerance 1"),
					  Internal::parseNumber<double>(tol2_attr->value(), tol2_attr->value() + std::strlen(tol2_attr->value()), 
													"TorsionLibraryDataReader: error while parsing torsion angle tolerance 1"),
					  Internal::parseNumber<double>(score_attr->value(), score_attr->value() + std::strlen(score_attr->value()), 
													"TorsionLibraryDataReader: error while parsing torsion angle score"));
	}
}

Chem::MolecularGraph::SharedPointer ConfGen::TorsionLibraryDataReader::parseSMARTS(const char* str) const
{
	using namespace Chem;

    boost::iostreams::stream<boost::iostreams::array_source> is(str, std::strlen(str));
	BasicMolecule::SharedPointer mol_ptr(new BasicMolecule());
	SMARTSMoleculeReader reader(is);

	if (!reader.read(*mol_ptr)) 
		return MolecularGraph::SharedPointer();

	initSubstructureSearchQuery(*mol_ptr, false);

	return mol_ptr;
}
