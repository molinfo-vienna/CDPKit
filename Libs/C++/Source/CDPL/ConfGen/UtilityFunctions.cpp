/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp 
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


#include <algorithm>
#include <cmath>

#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"

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

std::string ConfGen::returnCodeToString(unsigned int ret_code)
{
	switch (ret_code) {

	    case ReturnCode::SUCCESS:
			return "SUCCESS";

	    case ReturnCode::UNINITIALIZED:
			return "UNINITIALIZED";

	    case ReturnCode::TIMEOUT:
			return "TIMEOUT";

	    case ReturnCode::ABORTED:
			return "ABORTED";

	    case ReturnCode::FORCEFIELD_SETUP_FAILED:
			return "FORCEFIELD_SETUP_FAILED";

	    case ReturnCode::FORCEFIELD_MINIMIZATION_FAILED:
			return "FORCEFIELD_MINIMIZATION_FAILED";

	    case ReturnCode::FRAGMENT_LIBRARY_NOT_SET:
			return "FRAGMENT_LIBRARY_NOT_SET";
 	
	    case ReturnCode::FRAGMENT_CONF_GEN_FAILED:
			return "FRAGMENT_CONF_GEN_FAILED";

	    case ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT:
			return "FRAGMENT_CONF_GEN_TIMEOUT";

	    case ReturnCode::FRAGMENT_ALREADY_PROCESSED:
			return "FRAGMENT_ALREADY_PROCESSED";

	    case ReturnCode::TORSION_DRIVING_FAILED:
			return "TORSION_DRIVING_FAILED";

	    case ReturnCode::CONF_GEN_FAILED:
			return "CONF_GEN_FAILED";

	    case ReturnCode::TOO_MUCH_SYMMETRY:
			return "TOO_MUCH_SYMMETRY";

		default:
			break;
	}

    return "UNKNOWN";
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

std::size_t ConfGen::getNonAromaticSingleBondCount(const Chem::BondContainer& cntnr)
{
	using namespace Chem;

	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (getOrder(*it) == 1 && !getAromaticityFlag(*it))
			count++;

	return count;
}

std::size_t ConfGen::getMaxNonAromaticSingleBondCount(const Chem::FragmentList& frags)
{
	using namespace Chem;

	std::size_t max_count = 0;

	for (FragmentList::ConstElementIterator it =  frags.getElementsBegin(), end = frags.getElementsEnd(); it != end; ++it)
		max_count = std::max(max_count, getNonAromaticSingleBondCount(*it));

	return max_count;
}

double ConfGen::normalizeAngle(double angle)
{
	// normalize angle to range [0, 360)
	
	if (angle < 0.0)
		return std::fmod(angle, 360.0) + 360.0;

	return std::fmod(angle, 360.0);
}

double ConfGen::getAbsoluteAngleDistance(double angle1, double angle2)
{
	angle1 = normalizeAngle(angle1);
	angle2 = normalizeAngle(angle2);

	if (angle1 < angle2) 
		return std::min(angle2 - angle1, angle1 + 360.0 - angle2);

	return std::min(angle1 - angle2, angle2 + 360.0 - angle1);
}
