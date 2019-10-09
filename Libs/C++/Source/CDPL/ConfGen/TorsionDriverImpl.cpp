/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriverImpl.cpp 
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

#include "TorsionDriverImpl.hpp"
#include "TorsionLibraryDataReader.hpp"


using namespace CDPL;


namespace
{

	const char* FALLBACK_TORSION_RULES = 
		"<library name=\"FallbackRules\">"
		" <category name=\"GG\" atomType1=\"*\" atomType2=\"*\">"
		" </category>"
		"</library>";

	ConfGen::TorsionLibrary::SharedPointer fallbackTorLib(new ConfGen::TorsionLibrary());

	struct Init
    {

		Init() {
			ConfGen::TorsionLibraryDataReader().read(FALLBACK_TORSION_RULES, *fallbackTorLib);
		}

    } init;

	const std::size_t MAX_CONFORMER_DATA_CACHE_SIZE = 5000;
}


ConfGen::TorsionDriverImpl::TorsionDriverImpl(): 
	fragTree(MAX_CONFORMER_DATA_CACHE_SIZE)
{} 

ConfGen::TorsionDriverImpl::~TorsionDriverImpl() {}

ConfGen::TorsionDriverSettings& ConfGen::TorsionDriverImpl::getSettings()
{
	return settings;
}

void ConfGen::TorsionDriverImpl::setupTorsions(FragmentTreeNode& node)
{
	using namespace Chem;

}

const ConfGen::TorsionRuleMatch* ConfGen::TorsionDriverImpl::getMatchingTorsionRule(const Chem::Bond& bond)
{
	torRuleMatcher.setTorsionLibrary(settings.getTorsionLibrary());

	if (torRuleMatcher.findMatches(bond, *rootMolGraph, false)) 
		return &torRuleMatcher.getMatch(0); 

	torRuleMatcher.setTorsionLibrary(fallbackTorLib);

	if (torRuleMatcher.findMatches(bond, *rootMolGraph, false)) 
		return &torRuleMatcher.getMatch(0); 

	return 0;
}
