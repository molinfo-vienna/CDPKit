/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeAutoCorr2DDescriptorCalculator.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/MoleculeAutoCorr2DDescriptorCalculator.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Math/VectorProxy.hpp"


using namespace CDPL;


namespace
{

	struct AtomPairWeightFunc
	{

		double operator()(const Chem::Atom& atom1, const Chem::Atom& atom2, unsigned int slot_type1, unsigned int slot_type2) const {
			unsigned int atom_type1 = getType(atom1);
			unsigned int atom_type2 = getType(atom2);

			if ((atom_type1 == slot_type1 && atom_type2 == slot_type2) ||
				(atom_type2 == slot_type1 && atom_type1 == slot_type2))
				return 1;

			return 0;
		}
	};

    unsigned int ATOM_TYPES[] = {
	    Chem::AtomType::H,
		Chem::AtomType::C,
		Chem::AtomType::N,
		Chem::AtomType::O,
		Chem::AtomType::S,
		Chem::AtomType::P,
		Chem::AtomType::F,
		Chem::AtomType::Cl,
		Chem::AtomType::Br,
		Chem::AtomType::I
    };
}


CDPL::Chem::MoleculeAutoCorr2DDescriptorCalculator::MoleculeAutoCorr2DDescriptorCalculator(): weightFunc()
{
	setMaxDistance(15);
} 

CDPL::Chem::MoleculeAutoCorr2DDescriptorCalculator::MoleculeAutoCorr2DDescriptorCalculator(const MolecularGraph& molgraph, Math::DVector& descr): weightFunc()
{
	setMaxDistance(15);
    calculate(molgraph, descr);
}

void CDPL::Chem::MoleculeAutoCorr2DDescriptorCalculator::setMaxDistance(std::size_t max_dist)
{
    autoCorrCalculator.setMaxDistance(max_dist);
}

std::size_t CDPL::Chem::MoleculeAutoCorr2DDescriptorCalculator::getMaxDistance() const
{
    return autoCorrCalculator.getMaxDistance();
}

void CDPL::Chem::MoleculeAutoCorr2DDescriptorCalculator::setAtomPairWeightFunction(const AtomPairWeightFunction& func)
{
    weightFunc = func;
}

void CDPL::Chem::MoleculeAutoCorr2DDescriptorCalculator::calculate(const MolecularGraph& molgraph, Math::DVector& descr)
{
	std::size_t sub_descr_size = autoCorrCalculator.getMaxDistance() + 1;
	std::size_t num_atom_types = sizeof(ATOM_TYPES) / sizeof(unsigned int);

	descr.resize((sub_descr_size * (num_atom_types + 1) * num_atom_types) / 2, false);

	Math::DVector sub_descr(sub_descr_size);

	for (std::size_t i = 0, offs = 0; i < num_atom_types; i++) {
		for (std::size_t j = i; j < num_atom_types; j++, offs += sub_descr_size) {
			if (weightFunc)
				autoCorrCalculator.setAtomPairWeightFunction(boost::bind<double>(weightFunc, _1, _2, ATOM_TYPES[i], ATOM_TYPES[j]));
			else
				autoCorrCalculator.setAtomPairWeightFunction(boost::bind<double>(AtomPairWeightFunc(), _1, _2, ATOM_TYPES[i], ATOM_TYPES[j]));

			autoCorrCalculator.calculate(molgraph, sub_descr);
		
			Math::VectorRange<Math::DVector>(descr, Math::range(offs, offs + sub_descr_size)).assign(sub_descr);
		}
	}
}
