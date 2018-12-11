/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionLibraryDataReader.cpp 
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

#include <sstream>
#include <cstring>

#include "CDPL/Config.hpp"

#if defined(HAVE_BOOST_IOSTREAMS)

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#endif // defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "TorsionLibraryDataReader.hpp"


using namespace CDPL;


namespace
{

	const char* LIBRARY_TAG               = "library";
	const char* CATEGORY_TAG              = "category";
	const char* RULE_TAG                  = "rule";
	const char* ANGLE_LIST_TAG            = "torsions";
	const char* ANGLE_TAG                 = "angle";
	const char* NOTE_TAG                  = "note";

	const char* CATEGORY_NAME_ATTR        = "name";
	const char* CATEGORY_PATTERN_ATTR     = "pattern";
	const char* CATEGORY_ATOM_TYPE1_ATTR  = "atomType1";
	const char* CATEGORY_ATOM_TYPE2_ATTR  = "atomType2";

	const char* RULE_PATTERN_ATTR         = "pattern";

	const char* ANGLE_VALUE_ATTR          = "value";
	const char* ANGLE_TOLERANCE1_ATTR     = "tolerance1";
	const char* ANGLE_TOLERANCE2_ATTR     = "tolerance2";
	const char* ANGLE_SCORE_ATTR          = "score";
}


void ConfGen::TorsionLibraryDataReader::read(std::istream& is, TorsionLibrary& lib)
{
    is.seekg(0, std::ios::end);

	std::istream::pos_type data_len = is.tellg();

	if (data_len < 0)
		throw Base::IOError("TorsionLibraryDataReader: reading torsion library data failed");

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
	torLibDocument.parse<0>(data);

  	const XMLNode* lib_node = torLibDocument.first_node(LIBRARY_TAG);

	if (!lib_node)
		throw Base::IOError(std::string("TorsionLibraryDataReader: <") + LIBRARY_TAG + "> document root node not found");

	processCategory(lib_node, lib);
}

void ConfGen::TorsionLibraryDataReader::processCategory(const XMLNode* cat_node, TorsionCategory& cat) const
{
	const XMLAttribute* attr = cat_node->first_attribute(CATEGORY_NAME_ATTR);
	std::string str;

	if (attr) 
		cat.setName(str = attr->value());
	
	attr = cat_node->first_attribute(CATEGORY_ATOM_TYPE1_ATTR);

	if (attr) 
		cat.setBondAtom1Type(Chem::AtomDictionary::getType(str = attr->value()));

	attr = cat_node->first_attribute(CATEGORY_ATOM_TYPE2_ATTR);

	if (attr) 
		cat.setBondAtom2Type(Chem::AtomDictionary::getType(str = attr->value()));
	
	attr = cat_node->first_attribute(CATEGORY_PATTERN_ATTR);

	if (attr) 
		cat.setMatchPattern(parseSMARTS(attr->value()));
	
	for (const XMLNode* node = cat_node->first_node(); node; node = node->next_sibling()) {
		const char* node_name = node->name();

		if (std::strcmp(node_name, CATEGORY_TAG) == 0) 
			processCategory(node, cat.addCategory());
		else if (std::strcmp(node_name, RULE_TAG) == 0)
			processRule(node, cat.addRule());
		else if (std::strcmp(node_name, NOTE_TAG) != 0)
			throw Base::IOError(std::string("TorsionLibraryDataReader: invalid tag <") + node_name + ">");
	}
}

void ConfGen::TorsionLibraryDataReader::processRule(const XMLNode* rule_node, TorsionRule& rule) const
{
	const XMLAttribute* attr = rule_node->first_attribute(RULE_PATTERN_ATTR);

	if (attr) 
		rule.setMatchPattern(parseSMARTS(attr->value()));
	else
		throw Base::IOError(std::string("TorsionLibraryDataReader: missing rule '") + RULE_PATTERN_ATTR + "' attribute");

	if (!rule.getMatchPattern())
		throw Base::IOError(std::string("TorsionLibraryDataReader: empty or invalid rule '") + RULE_PATTERN_ATTR + "' attribute");

	for (const XMLNode* node = rule_node->first_node(); node; node = node->next_sibling()) {
		if (std::strcmp(node->name(), ANGLE_LIST_TAG) == 0) 
			processAngleList(node, rule);
		else
			throw Base::IOError(std::string("TorsionLibraryDataReader: invalid tag <") + node->name() + ">");
	}
}

void ConfGen::TorsionLibraryDataReader::processAngleList(const XMLNode* ang_list_node, TorsionRule& rule) const
{
	for (const XMLNode* node = ang_list_node->first_node(); node; node = node->next_sibling()) {
		const char* node_name = node->name();

		if (std::strcmp(node_name, ANGLE_TAG) != 0)
			throw Base::IOError(std::string("TorsionLibraryDataReader: invalid tag <") + node_name + ">");

		const XMLAttribute* value_attr = node->first_attribute(ANGLE_VALUE_ATTR);

		if (!value_attr)
			throw Base::IOError(std::string("TorsionLibraryDataReader: missing angle entry '") + ANGLE_VALUE_ATTR + "' attribute");

		const XMLAttribute* tol1_attr = node->first_attribute(ANGLE_TOLERANCE1_ATTR);

		if (!tol1_attr)
			throw Base::IOError(std::string("TorsionLibraryDataReader: missing angle entry '") + ANGLE_TOLERANCE1_ATTR + "' attribute");

		const XMLAttribute* tol2_attr = node->first_attribute(ANGLE_TOLERANCE2_ATTR);

		if (!tol2_attr)
			throw Base::IOError(std::string("TorsionLibraryDataReader: missing angle entry '") + ANGLE_TOLERANCE2_ATTR + "' attribute");

		const XMLAttribute* score_attr = node->first_attribute(ANGLE_SCORE_ATTR);

		if (!score_attr)
			throw Base::IOError(std::string("TorsionLibraryDataReader: missing angle entry '") + ANGLE_SCORE_ATTR + "' attribute");

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

#if defined(HAVE_BOOST_IOSTREAMS)

    boost::iostreams::stream<boost::iostreams::array_source> is(str, std::strlen(str));

#else // defined(HAVE_BOOST_IOSTREAMS)

	std::istringstream is(str);

#endif // defined(HAVE_BOOST_IOSTREAMS)

	BasicMolecule::SharedPointer mol_ptr(new BasicMolecule());
	SMARTSMoleculeReader reader(is);

	if (!reader.read(*mol_ptr)) 
		return MolecularGraph::SharedPointer();

	initSubstructureSearchQuery(*mol_ptr, false);

	return mol_ptr;
}
