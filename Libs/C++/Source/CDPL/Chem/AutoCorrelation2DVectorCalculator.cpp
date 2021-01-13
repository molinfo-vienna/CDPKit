/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AutoCorrelation2DVectorCalculator.cpp 
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

#include <functional>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/bind.hpp>

#include "CDPL/Chem/AutoCorrelation2DVectorCalculator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Math/VectorIterator.hpp"


using namespace CDPL;

Chem::AutoCorrelation2DVectorCalculator::AutoCorrelation2DVectorCalculator():
	weightFunc(boost::bind(std::multiplies<unsigned int>(),
						   boost::bind(&getType, _1), boost::bind(&getType, _1))) {}

Chem::AutoCorrelation2DVectorCalculator::AutoCorrelation2DVectorCalculator(const MolecularGraph& molgraph, Math::DVector& corr_vec):
	weightFunc(boost::bind(std::multiplies<unsigned int>(),
						   boost::bind(&getType, _1), boost::bind(&getType, _1)))
{
	calculate(molgraph, corr_vec);
}

void Chem::AutoCorrelation2DVectorCalculator::calculate(const MolecularGraph& molgraph, Math::DVector& corr_vec)
{
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

void Chem::AutoCorrelation2DVectorCalculator::setAtomPairWeightFunction(const AtomPairWeightFunction& func)
{
	weightFunc = func;
}

void Chem::AutoCorrelation2DVectorCalculator::setMaxDistance(std::size_t max_dist)
{
	maxDist = max_dist;
}

std::size_t Chem::AutoCorrelation2DVectorCalculator::getMaxDistance() const
{
	return maxDist;
}
