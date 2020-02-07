/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp 
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


#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"

#include "UtilityFunctions.hpp"


using namespace CDPL; 


std::string ConfGen::fragmentTypeToString(unsigned int frag_type, bool human)
{
    switch (frag_type) {

	case FragmentType::CHAIN:
	    return (human ? "chain" : "CHAIN");

	case FragmentType::FLEXIBLE_RING_SYSTEM:
	    return (human ? "flexible ring system" : "FLEXIBLE_RING_SYSTEM");

	case FragmentType::RIGID_RING_SYSTEM:
	    return (human ? "rigid ring system" : "RIGID_RING_SYSTEM");

	default:
	    break;
    }

    return (human ? "unknown" : "UNKNOWN");
}

std::string ConfGen::getSMILES(Chem::MolecularGraph& molgraph)
{
    perceiveSSSR(molgraph, false);
    perceiveComponents(molgraph, false);

    std::string smiles;

    if (generateSMILES(molgraph, smiles, false))
	return smiles;

    return "";
}

std::string ConfGen::getSMILES(const Chem::MolecularGraph& molgraph)
{
    std::string smiles;

    if (generateSMILES(molgraph, smiles, false))
	return smiles;

    return "";
}
