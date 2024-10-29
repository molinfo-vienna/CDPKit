/* 
 * TorsionLibraryDataWriter.cpp 
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
#include <iomanip>
#include <algorithm>
#include <functional>

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
    using namespace Internal;
    
    os << std::fixed << std::setprecision(2) << std::boolalpha;

    writeStartTag(os, Element::LIBRARY, false);
    writeAttribute(os, Attribute::CATEGORY_NAME, lib.getName(), true, false);
    writeCategory(os, 0, lib, true);
    writeEndTag(os, Element::LIBRARY);

    return os.good();
}

void ConfGen::TorsionLibraryDataWriter::writeCategory(std::ostream& os, std::size_t indent, const TorsionCategory& cat, bool contents_only) const
{
    using namespace TorsionLibraryFormatData;
    using namespace Internal;
    using namespace std::placeholders;
    
    if (!contents_only) {
        writeStartTag(os, Element::CATEGORY, false, indent);
        writeAttribute(os, Attribute::CATEGORY_NAME, cat.getName(), false, false);
    
        if (!cat.getMatchPatternString().empty())
            writeAttribute(os, Attribute::CATEGORY_PATTERN, cat.getMatchPatternString(), true, false);

        else if (cat.getMatchPattern())
            writeAttribute(os, Attribute::CATEGORY_PATTERN, getSMARTSPattern(*cat.getMatchPattern()), true, false);

        else if (cat.getBondAtom1Type() != Chem::AtomType::UNKNOWN && cat.getBondAtom2Type() != Chem::AtomType::UNKNOWN) {
            writeAttribute(os, Attribute::CATEGORY_ATOM_TYPE1, Chem::AtomDictionary::getSymbol(cat.getBondAtom1Type()), false, false);
            writeAttribute(os, Attribute::CATEGORY_ATOM_TYPE2, Chem::AtomDictionary::getSymbol(cat.getBondAtom2Type()), true, false);

        } else
            throw Base::IOError("TorsionLibraryDataWriter: missing category pattern or bond atom types");
    }

    std::for_each(cat.getCategoriesBegin(), cat.getCategoriesEnd(),
                  std::bind(&TorsionLibraryDataWriter::writeCategory, this, std::ref(os), indent + 1, _1, false));
    std::for_each(cat.getRulesBegin(), cat.getRulesEnd(),
                  std::bind(&TorsionLibraryDataWriter::writeRule, this, std::ref(os), indent + 1, _1));

    if (!contents_only)
        writeEndTag(os, Element::CATEGORY, indent);
}

void ConfGen::TorsionLibraryDataWriter::writeRule(std::ostream& os, std::size_t indent, const TorsionRule& rule) const
{
    using namespace TorsionLibraryFormatData;
    using namespace Internal;
    
    writeStartTag(os, Element::RULE, false, indent);

    if (!rule.getMatchPatternString().empty())
        writeAttribute(os, Attribute::RULE_PATTERN, rule.getMatchPatternString(), true, false);

    else if (rule.getMatchPattern())
        writeAttribute(os, Attribute::RULE_PATTERN, getSMARTSPattern(*rule.getMatchPattern()), true, false);

    else
        throw Base::IOError("TorsionLibraryDataWriter: missing rule pattern");

    writeAngleList(os, indent + 1, rule);
    writeEndTag(os, Element::RULE, indent);
}

void ConfGen::TorsionLibraryDataWriter::writeAngleList(std::ostream& os, std::size_t indent, const TorsionRule& rule) const
{
    using namespace TorsionLibraryFormatData;
    using namespace Internal;
    
    writeStartTag(os, Element::ANGLE_LIST, true, indent);
    
    std::for_each(rule.getAnglesBegin(), rule.getAnglesEnd(),
                  std::bind(&TorsionLibraryDataWriter::writeAngleEntry, this,
                            std::ref(os), indent + 1, std::placeholders::_1));

    writeEndTag(os, Element::ANGLE_LIST, indent);
}

void ConfGen::TorsionLibraryDataWriter::writeAngleEntry(std::ostream& os, std::size_t indent, const TorsionRule::AngleEntry& angle_entry) const
{
    using namespace TorsionLibraryFormatData;
    using namespace Internal;
    
    writeStartTag(os, Element::ANGLE, false, indent);
    writeAttribute(os, Attribute::ANGLE_VALUE, angle_entry.getAngle(), false, true);
    writeAttribute(os, Attribute::ANGLE_TOLERANCE1, angle_entry.getTolerance1(), false, true);
    writeAttribute(os, Attribute::ANGLE_TOLERANCE2, angle_entry.getTolerance2(), false, true);
    writeAttribute(os, Attribute::ANGLE_SCORE, angle_entry.getScore(), true, true);
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
