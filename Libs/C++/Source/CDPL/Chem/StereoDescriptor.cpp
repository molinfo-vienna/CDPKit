/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StereoDescriptor.cpp 
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

#include <algorithm>

#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Internal/Permutation.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"


using namespace CDPL;


namespace
{

	unsigned int getParity(const Chem::Atom* const* ref_atoms, const Chem::Atom** perm_atoms, 
						   std::size_t num_perm_atoms, std::size_t cmp_seq_len)
	{
		std::size_t num_perms = 0;
		std::size_t num_swaps = 0;
		std::size_t max_num_perms = CDPL::Math::factorial<std::size_t>(num_perm_atoms);

		while (!std::equal(ref_atoms, ref_atoms + cmp_seq_len, perm_atoms) &&
			   (++num_perms < max_num_perms))
			num_swaps += Internal::nextPermutation(perm_atoms, perm_atoms + num_perm_atoms);

		if (num_perms >= max_num_perms)  //	a matching permutation should have been found
			return 0;
		
		if ((num_swaps % 2) != 0) 
			return 1;

		return 2;
	}
}


Chem::StereoDescriptor::StereoDescriptor(unsigned int config): numRefAtoms(0), config(config) {}

Chem::StereoDescriptor::StereoDescriptor(const StereoDescriptor& descr): 
	numRefAtoms(descr.numRefAtoms), config(descr.config) 
{
	std::copy(descr.refAtoms, descr.refAtoms + descr.numRefAtoms, refAtoms);
}

Chem::StereoDescriptor::StereoDescriptor(unsigned int config, const Atom& atom1, 
										 const Atom& atom2, const Atom& atom3): numRefAtoms(3), config(config)
{
	refAtoms[0] = &atom1;
	refAtoms[1] = &atom2;
	refAtoms[2] = &atom3;
	refAtoms[3] = 0;
}

Chem::StereoDescriptor::StereoDescriptor(unsigned int config, const Atom& atom1, const Atom& atom2, 
										 const Atom& atom3, const Atom& atom4): numRefAtoms(4), config(config)
{
	refAtoms[0] = &atom1;
	refAtoms[1] = &atom2;
	refAtoms[2] = &atom3;
	refAtoms[3] = &atom4;
}

std::size_t Chem::StereoDescriptor::getNumReferenceAtoms() const
{
	return numRefAtoms;
}

unsigned int Chem::StereoDescriptor::getConfiguration() const
{
	return config;
}

void Chem::StereoDescriptor::setConfiguration(unsigned int config)
{
	this->config = config;
}

const Chem::Atom* const* Chem::StereoDescriptor::getReferenceAtoms() const
{
	return refAtoms;
}

Chem::StereoDescriptor& Chem::StereoDescriptor::operator=(const StereoDescriptor& descr)
{
	if (this == &descr)
		return *this;

	numRefAtoms = descr.numRefAtoms;
	config = descr.config;
	
	std::copy(descr.refAtoms, descr.refAtoms + descr.numRefAtoms, refAtoms);

	return *this;
}

bool Chem::StereoDescriptor::isValid(const Atom& atom) const
{
	if (numRefAtoms < 3)
		return false;

	for (std::size_t i = 0; i < numRefAtoms; i++) {
		for (std::size_t j = i + 1; j < numRefAtoms; j++)
			if (refAtoms[i] == refAtoms[j])
				return false;

		if (!atom.findBondToAtom(*refAtoms[i]))
			return false;
	}

	return true;
}

bool Chem::StereoDescriptor::isValid(const Bond& bond) const
{
	if (numRefAtoms < 4)
		return false;

	if (refAtoms[1]->findBondToAtom(*refAtoms[2]) != &bond) 
		return false;

	if (refAtoms[0] == refAtoms[2])
		return false;

	if (refAtoms[3] == refAtoms[1])
		return false;

	if (!refAtoms[1]->findBondToAtom(*refAtoms[0]))
		return false;

	if (!refAtoms[2]->findBondToAtom(*refAtoms[3]))
		return false;

	return true;
}

unsigned int Chem::StereoDescriptor::getPermutationParity(const Atom& atom1, const Atom& atom2, 
														  const Atom& atom3) const
{
	if (numRefAtoms < 3)
		return 0;

	const Atom* atoms[3];

	atoms[0] = &atom1;
	atoms[1] = &atom2;
	atoms[2] = &atom3;

	if (numRefAtoms == 4) {
		const Atom* tmp_ref_atoms[4];

		std::copy(refAtoms, refAtoms + 4, tmp_ref_atoms);

		return getParity(atoms, tmp_ref_atoms, 4, 3);
	}

	return getParity(refAtoms, atoms, 3, 3);
}

unsigned int Chem::StereoDescriptor::getPermutationParity(const Atom& atom1, const Atom& atom2, 
														  const Atom& atom3, const Atom& atom4) const
{
	if (numRefAtoms < 3)
		return 0;

	const Atom* atoms[4];

	atoms[0] = &atom1;
	atoms[1] = &atom2;
	atoms[2] = &atom3;
	atoms[3] = &atom4;

	return getParity(refAtoms, atoms, 4, numRefAtoms);
}
