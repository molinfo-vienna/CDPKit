/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionLibraryDataWriter.cpp 
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
#include <iomanip>
#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/Chem/SMARTSMolecularGraphWriter.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "TorsionLibraryDataWriter.hpp"
#include "TorsionLibraryFormatData.hpp"


using namespace CDPL;


bool ConfGen::TorsionLibraryDataWriter::write(std::ostream& os, const TorsionLibrary& lib)
{
  	using namespace TorsionLibraryFormatData;

	os << std::fixed << std::boolalpha;

	writeStartTag(os, 0, LIBRARY_TAG, false);
	writeAttribute(os, CATEGORY_NAME_ATTR, lib.getName(), true, false);
	writeCategory(os, 0, lib, true);
	writeEndTag(os, 0, LIBRARY_TAG);

	return os.good();
}

void ConfGen::TorsionLibraryDataWriter::writeCategory(std::ostream& os, std::size_t ident, const TorsionCategory& cat, bool contents_only) const
{
  	using namespace TorsionLibraryFormatData;

	if (!contents_only) {
		writeStartTag(os, ident, CATEGORY_TAG, false);
		writeAttribute(os, CATEGORY_NAME_ATTR, cat.getName(), false, false);
	
		if (!cat.getMatchPatternString().empty())
			writeAttribute(os, CATEGORY_PATTERN_ATTR, cat.getMatchPatternString(), true, false);

		else if (cat.getMatchPattern())
			writeAttribute(os, CATEGORY_PATTERN_ATTR, getSMARTSPattern(*cat.getMatchPattern()), true, false);

		else if (cat.getBondAtom1Type() != Chem::AtomType::UNKNOWN && cat.getBondAtom2Type() != Chem::AtomType::UNKNOWN) {
			writeAttribute(os, CATEGORY_ATOM_TYPE1_ATTR, Chem::AtomDictionary::getSymbol(cat.getBondAtom1Type()), false, false);
			writeAttribute(os, CATEGORY_ATOM_TYPE2_ATTR, Chem::AtomDictionary::getSymbol(cat.getBondAtom2Type()), true, false);

		} else
			throw Base::IOError("TorsionLibraryDataWriter: missing category pattern or bond atom types");
	}

	std::for_each(cat.getCategoriesBegin(), cat.getCategoriesEnd(),
				  boost::bind(&TorsionLibraryDataWriter::writeCategory, this, boost::ref(os), ident + 1, _1, false));
	std::for_each(cat.getRulesBegin(), cat.getRulesEnd(),
				  boost::bind(&TorsionLibraryDataWriter::writeRule, this, boost::ref(os), ident + 1, _1));

	if (!contents_only)
		writeEndTag(os, ident, CATEGORY_TAG);
}

void ConfGen::TorsionLibraryDataWriter::writeRule(std::ostream& os, std::size_t ident, const TorsionRule& rule) const
{
  	using namespace TorsionLibraryFormatData;

	writeStartTag(os, ident, RULE_TAG, false);

	if (!rule.getMatchPatternString().empty())
		writeAttribute(os, RULE_PATTERN_ATTR, rule.getMatchPatternString(), true, false);

	else if (rule.getMatchPattern())
		writeAttribute(os, RULE_PATTERN_ATTR, getSMARTSPattern(*rule.getMatchPattern()), true, false);

	else
		throw Base::IOError("TorsionLibraryDataWriter: missing rule pattern");

	writeAngleList(os, ident + 1, rule);
	writeEndTag(os, ident, RULE_TAG);
}

void ConfGen::TorsionLibraryDataWriter::writeAngleList(std::ostream& os, std::size_t ident, const TorsionRule& rule) const
{
  	using namespace TorsionLibraryFormatData;

	writeStartTag(os, ident, ANGLE_LIST_TAG, true);
	
	std::for_each(rule.getAnglesBegin(), rule.getAnglesEnd(),
				  boost::bind(&TorsionLibraryDataWriter::writeAngleEntry, this, boost::ref(os), ident + 1, _1));

	writeEndTag(os, ident, ANGLE_LIST_TAG);
}

void ConfGen::TorsionLibraryDataWriter::writeAngleEntry(std::ostream& os, std::size_t ident, const TorsionRule::AngleEntry& angle_entry) const
{
  	using namespace TorsionLibraryFormatData;

	writeStartTag(os, ident, ANGLE_TAG, false);
	writeAttribute(os, ANGLE_VALUE_ATTR, angle_entry.getAngle(), false, true);
	writeAttribute(os, ANGLE_TOLERANCE1_ATTR, angle_entry.getTolerance1(), false, true);
	writeAttribute(os, ANGLE_TOLERANCE2_ATTR, angle_entry.getTolerance2(), false, true);
	writeAttribute(os, ANGLE_SCORE_ATTR, angle_entry.getScore(), true, true);
}

void ConfGen::TorsionLibraryDataWriter::writeStartTag(std::ostream& os, std::size_t ident, const std::string& tag, bool close) const
{
	if (ident > 0)
		Internal::writeWhitespace(os, ident);

	os << '<' << tag;

	if (close)
		closeTag(os);
}

void ConfGen::TorsionLibraryDataWriter::writeEndTag(std::ostream& os, std::size_t ident, const std::string& tag) const
{
	if (ident > 0)
		Internal::writeWhitespace(os, ident);

	os << "</" << tag; 

	closeTag(os);
}

template <typename T>
void ConfGen::TorsionLibraryDataWriter::writeAttribute(std::ostream& os, const std::string& name, const T& value, bool close, bool empty) const
{
	os << ' ' << name << "=\"" << value << "\"";

	if (close) 
		os << (empty ? " />\n" : ">\n");
}

void ConfGen::TorsionLibraryDataWriter::closeTag(std::ostream& os) const
{
	os << ">\n";
}

std::string ConfGen::TorsionLibraryDataWriter::getSMARTSPattern(const Chem::MolecularGraph& molgraph) const
{
	if (molgraph.getNumAtoms() < 2)
		throw Base::IOError("TorsionLibraryDataWriter: molecular graph of match pattern missing atoms");

	std::ostringstream oss;

	if (!Chem::SMARTSMolecularGraphWriter(oss).write(molgraph))
		throw Base::IOError("TorsionLibraryDataWriter: error while generating SMARTS pattern");

	return oss.str();
}
