/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeAutoCorr3DDescriptorCalculator.cpp 
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

#include "CDPL/Chem/MoleculeAutoCorr3DDescriptorCalculator.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


namespace
{

	struct AtomPairWeightFunc
	{

		double operator()(const Chem::Atom& atom1, const Chem::Atom& atom2, unsigned int slot_atom_type) const {
			unsigned int atom_type1 = getType(atom1);
			unsigned int atom_type2 = getType(atom2);

			if (atom_type1 == slot_atom_type && atom_type2 == slot_atom_type)
				return 2;

			if (atom_type1 == slot_atom_type || atom_type2 == slot_atom_type)
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


CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::MoleculeAutoCorr3DDescriptorCalculator(): weightFunc()
{
    setAtom3DCoordinatesFunction(&Chem::get3DCoordinates);
} 

CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::MoleculeAutoCorr3DDescriptorCalculator(const AtomContainer& cntnr, Math::DVector& descr): weightFunc()
{
    setAtom3DCoordinatesFunction(&Chem::get3DCoordinates);
    calculate(cntnr, descr);
}

void CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::setStartRadius(double start_radius)
{
    autoCorrCalculator.setStartRadius(start_radius);
}

double CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::getStartRadius() const
{
    return autoCorrCalculator.getStartRadius();
}

void CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::setRadiusIncrement(double radius_inc)
{
    autoCorrCalculator.setRadiusIncrement(radius_inc);
}

double CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::getRadiusIncrement() const
{
    return autoCorrCalculator.getRadiusIncrement();
}

void CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::setNumSteps(std::size_t num_steps)
{
    autoCorrCalculator.setNumSteps(num_steps);
}

std::size_t CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::getNumSteps() const
{
    return autoCorrCalculator.getNumSteps();
}

void CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func)
{
    autoCorrCalculator.setEntity3DCoordinatesFunction(func);
}

void CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::setAtomPairWeightFunction(const AtomPairWeightFunction& func)
{
    weightFunc = func;
}

void CDPL::Chem::MoleculeAutoCorr3DDescriptorCalculator::calculate(const AtomContainer& cntnr, Math::DVector& descr)
{
	std::size_t sub_descr_size = autoCorrCalculator.getNumSteps() + 1;
	std::size_t num_atom_types = sizeof(ATOM_TYPES) / sizeof(unsigned int);

	descr.resize(sub_descr_size * num_atom_types, false);

	for (std::size_t i = 0; i < num_atom_types; i++) {
		if (weightFunc)
			autoCorrCalculator.setEntityPairWeightFunction(boost::bind<double>(weightFunc, _1, _2, ATOM_TYPES[i]));
		else
			autoCorrCalculator.setEntityPairWeightFunction(boost::bind<double>(AtomPairWeightFunc(), _1, _2, ATOM_TYPES[i]));

		Math::VectorRange<Math::DVector> sub_descr(descr, Math::range(i * sub_descr_size, (i + 1) * sub_descr_size));

		autoCorrCalculator.calculate(cntnr.getAtomsBegin(), cntnr.getAtomsEnd(), sub_descr);
	}
}
