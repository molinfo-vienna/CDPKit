/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerAtomCountFunctions.cpp 
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

#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


std::size_t Chem::getExplicitAtomCount(const AtomContainer& cntnr)
{
	return cntnr.getNumAtoms();
}

std::size_t Chem::getExplicitAtomCount(const AtomContainer& cntnr, unsigned int type)
{
	std::size_t count = 0;

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		if (getType(*it) == type)
			count++;

	return count;
}

std::size_t Chem::getExplicitChainAtomCount(const AtomContainer& cntnr)
{
	std::size_t count = 0;

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		if (!getRingFlag(*it))
			count++;

	return count;
}

std::size_t Chem::getRingAtomCount(const AtomContainer& cntnr)
{
	std::size_t count = 0;

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		if (getRingFlag(*it))
			count++;

	return count;
}

std::size_t Chem::getAromaticAtomCount(const AtomContainer& cntnr)
{
	std::size_t count = 0;

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		if (getAromaticityFlag(*it))
			count++;

	return count;
}

std::size_t Chem::getHeavyAtomCount(const AtomContainer& cntnr)
{
	std::size_t count = 0;

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		if (getType(*it) != AtomType::H)
			count++;

	return count;
}
