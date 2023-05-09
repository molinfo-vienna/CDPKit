/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionRuleMatch.cpp 
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

#include "CDPL/ConfGen/TorsionRuleMatch.hpp"


using namespace CDPL;


ConfGen::TorsionRuleMatch::TorsionRuleMatch(const TorsionRule& rule, const Chem::Bond& bond, 
											const Chem::Atom* atom1, const Chem::Atom* atom2, 
											const Chem::Atom* atom3, const Chem::Atom* atom4): 
	rule(&rule), bond(&bond)
{
    atoms[0] = atom1;
    atoms[1] = atom2;
    atoms[2] = atom3;
    atoms[3] = atom4;
}

const Chem::Atom* const* ConfGen::TorsionRuleMatch::getAtoms() const
{
    return atoms;
}

const ConfGen::TorsionRule& ConfGen::TorsionRuleMatch::getRule() const
{
    return *rule;
}

const Chem::Bond& ConfGen::TorsionRuleMatch::getBond() const
{
    return *bond;
}
