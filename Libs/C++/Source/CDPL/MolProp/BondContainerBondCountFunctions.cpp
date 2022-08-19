/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondContainerBondCountFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/MolProp/BondContainerFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


std::size_t MolProp::getExplicitBondCount(const Chem::BondContainer& cntnr)
{
	return cntnr.getNumBonds();
}

std::size_t MolProp::getExplicitBondCount(const Chem::BondContainer& cntnr, std::size_t order, bool inc_aro)
{
    std::size_t count = 0;

    for (Chem::BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it) {
		const Chem::Bond& bond = *it;
		
		if (!inc_aro && getAromaticityFlag(bond))
			continue;
		
		if (getOrder(bond) == order)
			count++;
	}
	
    return count;
}

std::size_t MolProp::getExplicitHydrogenBondCount(const Chem::BondContainer& cntnr)
{
	std::size_t count = 0;

	for (Chem::BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (isHydrogenBond(*it))
			count++;

	return count;
}

std::size_t MolProp::getExplicitChainBondCount(const Chem::BondContainer& cntnr)
{
	std::size_t count = 0;

	for (Chem::BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (!getRingFlag(*it))
			count++;

	return count;
}

std::size_t MolProp::getRingBondCount(const Chem::BondContainer& cntnr)
{
	std::size_t count = 0;

	for (Chem::BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (getRingFlag(*it))
			count++;

	return count;
}

std::size_t MolProp::getAromaticBondCount(const Chem::BondContainer& cntnr)
{
	std::size_t count = 0;

	for (Chem::BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (getAromaticityFlag(*it))
			count++;

	return count;
}

std::size_t MolProp::getHeavyBondCount(const Chem::BondContainer& cntnr)
{
	std::size_t count = 0;

	for (Chem::BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (!isHydrogenBond(*it))
			count++;

	return count;
}
