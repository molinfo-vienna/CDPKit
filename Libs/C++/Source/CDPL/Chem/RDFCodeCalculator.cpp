/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RDFCodeCalculator.cpp 
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

#include <cmath>
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Chem/RDFCodeCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL;


Chem::RDFCodeCalculator::RDFCodeCalculator(): 
	 smoothingFactor(1.0), scalingFactor(100.0), startRadius(0.0), radiusIncrement(0.1), numSteps(99), 
	 weightFunc(boost::bind(std::multiplies<unsigned int>(),
							boost::bind(&getType, _1), boost::bind(&getType, _1))) {}

Chem::RDFCodeCalculator::RDFCodeCalculator(const MolecularGraph& molgraph, Math::DVector& rdf_code): 
	 smoothingFactor(1.0), scalingFactor(100.0), startRadius(0.0), radiusIncrement(0.1), numSteps(99), 
	 weightFunc(boost::bind(std::multiplies<unsigned int>(),
							boost::bind(&getType, _1), boost::bind(&getType, _1)))
{
	calculate(molgraph, rdf_code);
}

void CDPL::Chem::RDFCodeCalculator::setSmoothingFactor(double factor)
{
	smoothingFactor = factor;
}

void CDPL::Chem::RDFCodeCalculator::setScalingFactor(double factor)
{
	scalingFactor = factor;
}

void CDPL::Chem::RDFCodeCalculator::setStartRadius(double start_radius)
{
	startRadius = start_radius;
}

void CDPL::Chem::RDFCodeCalculator::setRadiusIncrement(double radius_inc)
{
	radiusIncrement = radius_inc;
}

void CDPL::Chem::RDFCodeCalculator::setNumSteps(std::size_t num_steps)
{
	numSteps = num_steps;
}

double CDPL::Chem::RDFCodeCalculator::getSmoothingFactor() const
{
	return smoothingFactor;
}

double CDPL::Chem::RDFCodeCalculator::getScalingFactor() const
{
	return scalingFactor;
}

double CDPL::Chem::RDFCodeCalculator::getStartRadius() const
{
	return startRadius;
}

double CDPL::Chem::RDFCodeCalculator::getRadiusIncrement() const
{
	return radiusIncrement;
}

std::size_t CDPL::Chem::RDFCodeCalculator::getNumSteps() const
{
	return numSteps;
}

void Chem::RDFCodeCalculator::calculate(const MolecularGraph& molgraph, Math::DVector& rdf_code)
{
	init(molgraph);

	rdf_code.resize(numSteps + 1, false);

	const Math::DMatrix& dist_mtx = *getGeometricalDistanceMatrix(molgraph);

	double r = startRadius;

	MolecularGraph::ConstAtomIterator atoms_beg = molgraph.getAtomsBegin();
	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (std::size_t i = 0; i <= numSteps; i++, r += radiusIncrement) {
		double sum = 0.0;

		for (MolecularGraph::ConstAtomIterator it1 = atoms_beg; it1 != atoms_end; ) {
			std::size_t atom1_idx = molgraph.getAtomIndex(*it1);

			for (MolecularGraph::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
				std::size_t atom2_idx = molgraph.getAtomIndex(*it2);

				double t = r - dist_mtx(atom1_idx, atom2_idx);

				sum += weightMatrix(atom1_idx, atom2_idx) * std::exp(-smoothingFactor * t * t);
			}
		}

		rdf_code(i) = scalingFactor * sum;
	}
}

void Chem::RDFCodeCalculator::setAtomPairWeightFunction(const AtomPairWeightFunction& func)
{
	weightFunc = func;
}

void Chem::RDFCodeCalculator::init(const MolecularGraph& molgraph)
{
	std::size_t num_atoms = molgraph.getNumAtoms();

	if (weightMatrix.getSize1() < num_atoms)
		weightMatrix.resize(num_atoms, num_atoms, false);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it1 = molgraph.getAtomsBegin(); it1 != atoms_end; ) {
		const Atom& atom1 = *it1;
		std::size_t atom1_idx = molgraph.getAtomIndex(atom1);

		for (MolecularGraph::ConstAtomIterator it2 = ++it1; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;
			std::size_t atom2_idx = molgraph.getAtomIndex(atom2);

			weightMatrix(atom1_idx, atom2_idx) = weightFunc(atom1, atom2);
		}
	}
}
