/* 
 * AutoCorrelation2DVectorCalculator.cpp 
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


#include "StaticInit.hpp"

#include <functional>

#include "CDPL/Descr/AutoCorrelation2DVectorCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Math/VectorIterator.hpp"


using namespace CDPL;

Descr::AutoCorrelation2DVectorCalculator::AutoCorrelation2DVectorCalculator():
	weightFunc(std::bind(std::multiplies<unsigned int>(),
						 std::bind(&Chem::getType, std::placeholders::_1),
						 std::bind(&Chem::getType, std::placeholders::_1))) {}

Descr::AutoCorrelation2DVectorCalculator::AutoCorrelation2DVectorCalculator(const Chem::MolecularGraph& molgraph, Math::DVector& corr_vec):
	weightFunc(std::bind(std::multiplies<unsigned int>(),
						 std::bind(&Chem::getType, std::placeholders::_1),
						 std::bind(&Chem::getType, std::placeholders::_1)))
{
	calculate(molgraph, corr_vec);
}

void Descr::AutoCorrelation2DVectorCalculator::calculate(const Chem::MolecularGraph& molgraph, Math::DVector& corr_vec)
{
	using namespace Chem;

	if (maxDist > 0) {
		corr_vec.resize(maxDist + 1, false);
		corr_vec.clear(0.0);
	} else
		corr_vec.resize(0, false);

	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);

	MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

	for (MolecularGraph::ConstAtomIterator it1 = molgraph.getAtomsBegin(); it1 != atoms_end; ++it1) {
		const Atom& atom1 = *it1;
		std::size_t atom1_idx = molgraph.getAtomIndex(atom1);

		for (MolecularGraph::ConstAtomIterator it2 = it1; it2 != atoms_end; ++it2) {
			const Atom& atom2 = *it2;
			std::size_t atom2_idx = molgraph.getAtomIndex(atom2);
			std::size_t dist = dist_mtx(atom1_idx, atom2_idx);

			if (dist == 0 && atom1_idx != atom2_idx)
				continue;

			if (maxDist > 0) {
				if (dist > maxDist)
					continue;

			} else if (dist >= corr_vec.getSize())
				corr_vec.resize(dist + 1, 0.0);

			double weight = (weightFunc ? weightFunc(atom1, atom2) : 1.0);
		
			corr_vec(dist) += weight;
		}
	}
}

void Descr::AutoCorrelation2DVectorCalculator::setAtomPairWeightFunction(const AtomPairWeightFunction& func)
{
	weightFunc = func;
}

void Descr::AutoCorrelation2DVectorCalculator::setMaxDistance(std::size_t max_dist)
{
	maxDist = max_dist;
}

std::size_t Descr::AutoCorrelation2DVectorCalculator::getMaxDistance() const
{
	return maxDist;
}
