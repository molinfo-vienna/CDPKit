/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondContainerBondCountFunctions.cpp 
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

#include "CDPL/Chem/BondContainerFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


std::size_t Chem::getExplicitBondCount(const BondContainer& cntnr)
{
	return cntnr.getNumBonds();
}

std::size_t Chem::getExplicitBondCount(const BondContainer& cntnr, std::size_t order)
{
	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (getOrder(*it) == order)
			count++;

	return count;
}

std::size_t Chem::getExplicitHydrogenBondCount(const BondContainer& cntnr)
{
	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (isHydrogenBond(*it))
			count++;

	return count;
}

std::size_t Chem::getExplicitChainBondCount(const BondContainer& cntnr)
{
	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (!getRingFlag(*it))
			count++;

	return count;
}

std::size_t Chem::getRingBondCount(const BondContainer& cntnr)
{
	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (getRingFlag(*it))
			count++;

	return count;
}

std::size_t Chem::getAromaticBondCount(const BondContainer& cntnr)
{
	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (getAromaticityFlag(*it))
			count++;

	return count;
}

std::size_t Chem::getHeavyBondCount(const BondContainer& cntnr)
{
	std::size_t count = 0;

	for (BondContainer::ConstBondIterator it = cntnr.getBondsBegin(), end = cntnr.getBondsEnd(); it != end; ++it)
		if (!isHydrogenBond(*it))
			count++;

	return count;
}
