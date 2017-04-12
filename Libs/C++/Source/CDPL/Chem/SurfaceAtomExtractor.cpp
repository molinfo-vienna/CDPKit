/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SurfaceAtomExtractor.cpp 
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

#include <limits>
#include <algorithm>
#include <cmath>

#include "CDPL/Chem/SurfaceAtomExtractor.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Math/SVDecomposition.hpp"


using namespace CDPL; 


const double       Chem::SurfaceAtomExtractor::DEF_PROBE_RADIUS    = 1.2;
const double       Chem::SurfaceAtomExtractor::DEF_GRID_OVERSIZE   = 5.0;
const double       Chem::SurfaceAtomExtractor::DEF_GRID_STEP_SIZE  = 0.75;
const double       Chem::SurfaceAtomExtractor::DEF_MIN_SURFACE_ACC = 0.01;
const std::size_t  Chem::SurfaceAtomExtractor::DEF_NUM_TEST_POINTS = 250;


Chem::SurfaceAtomExtractor::SurfaceAtomExtractor(): 
    probeRadius(DEF_PROBE_RADIUS), gridOversize(DEF_GRID_OVERSIZE), 
	gridStepSize(DEF_GRID_STEP_SIZE), minSurfAcc(DEF_MIN_SURFACE_ACC),
	numTestPoints(DEF_NUM_TEST_POINTS), coordsFunc(Chem::get3DCoordinates)
{}

Chem::SurfaceAtomExtractor::SurfaceAtomExtractor(
	const AtomContainer& cntnr, const MolecularGraph& parent_molgraph, Fragment& frag):
    probeRadius(DEF_PROBE_RADIUS), gridOversize(DEF_GRID_OVERSIZE), 
	gridStepSize(DEF_GRID_STEP_SIZE), minSurfAcc(DEF_MIN_SURFACE_ACC),
	numTestPoints(DEF_NUM_TEST_POINTS), coordsFunc(Chem::get3DCoordinates)
{
    extract(cntnr, parent_molgraph, frag);
}

void Chem::SurfaceAtomExtractor::setProbeRadius(double radius)
{
	probeRadius = radius;
}

double Chem::SurfaceAtomExtractor::getProbeRadius() const
{
	return probeRadius;
}

void Chem::SurfaceAtomExtractor::setGridStepSize(double size)
{
	gridStepSize = size;
}

double Chem::SurfaceAtomExtractor::getGridStepSize() const
{
	return gridStepSize;
}

void Chem::SurfaceAtomExtractor::setGridOversize(double size)
{
	gridOversize = size;
}

double Chem::SurfaceAtomExtractor::getGridOversize() const
{
	return gridOversize;
}

void Chem::SurfaceAtomExtractor::setMinSurfaceAccessibility(double min_acc)
{
	minSurfAcc = min_acc;
}

double Chem::SurfaceAtomExtractor::getMinSurfaceAccessibility() const
{
	return minSurfAcc;
}

void Chem::SurfaceAtomExtractor::setNumTestPoints(std::size_t num_points)
{
	numTestPoints = num_points;
}

std::size_t Chem::SurfaceAtomExtractor::getNumTestPoints() const
{
	return numTestPoints;
}

void Chem::SurfaceAtomExtractor::setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func)
{
	coordsFunc = func;
}

const Chem::Atom3DCoordinatesFunction& Chem::SurfaceAtomExtractor::getAtom3DCoordinatesFunction() const
{
	return coordsFunc;
}

void Chem::SurfaceAtomExtractor::extract(const AtomContainer& cntnr, const MolecularGraph& parent_molgraph, Fragment& frag)
{
	if (!init(cntnr, parent_molgraph))
		return;

	transformCoordinates();
	calcBoundingBox();
    initGridAtomLookupTable();
	extractSurfaceAtoms(frag);
}

bool Chem::SurfaceAtomExtractor::init(const AtomContainer& cntnr, const MolecularGraph& parent_molgraph)
{
	std::size_t num_prnt_atoms = parent_molgraph.getNumAtoms();
	std::size_t num_atoms = cntnr.getNumAtoms();

	if (num_atoms == 0 || num_prnt_atoms == 0)
		return false;

	atomContainer = &cntnr;
	parentMolGraph = &parent_molgraph;

	atomRadii.clear();
	atomRadii.reserve(num_prnt_atoms);

	atomCoords.clear();	
	atomCoords.reserve(num_prnt_atoms);	

	for (MolecularGraph::ConstAtomIterator it = parent_molgraph.getAtomsBegin(), end = parent_molgraph.getAtomsEnd(); it != end; ++it) {
		atomRadii.push_back(getVdWRadius(*it) + probeRadius);
		atomCoords.push_back(coordsFunc(*it));
	}

	atomIndices.clear();
	atomIndices.reserve(num_atoms);

	for (MolecularGraph::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it)
		atomIndices.push_back(parent_molgraph.getAtomIndex(*it));

	return true;
}

void Chem::SurfaceAtomExtractor::transformCoordinates()
{
	Math::Vector3D ctr;
	std::size_t num_atoms = atomContainer->getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++)
		ctr.plusAssign(atomCoords[atomIndices[i]]);
	
	ctr /= num_atoms; 

	svdU.resize(num_atoms, 3, false);

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Math::Vector3D& pos = atomCoords[atomIndices[i]];

		svdU(i, 0) = pos(0) - ctr(0);
		svdU(i, 1) = pos(1) - ctr(1);
		svdU(i, 2) = pos(2) - ctr(2);
	}

	Math::Matrix3D svd_v;
	Math::Vector3D svd_w;
	Math::Matrix3D xform;

	Math::svDecompose(svdU, svd_w, svd_v);

	row(xform, 0) = column(svd_v, 0) / length(column(svd_v, 0));
	row(xform, 1) = column(svd_v, 1) / length(column(svd_v, 1));
	row(xform, 2) = column(svd_v, 2) / length(column(svd_v, 2));

	std::size_t num_prnt_atoms = parentMolGraph->getNumAtoms();
	Math::Vector3D tmp;

	for (std::size_t i = 0; i < num_prnt_atoms; i++) {
		tmp.assign(atomCoords[i] - ctr);
		prod(xform, tmp, atomCoords[i]);
	}
}

void Chem::SurfaceAtomExtractor::calcBoundingBox()
{
	bBoxMin.clear(std::numeric_limits<double>::max());
	bBoxMax.clear(-std::numeric_limits<double>::max());

	for (AtomIndexList::const_iterator it = atomIndices.begin(), end = atomIndices.end(); it != end; ++it) {
		std::size_t atom_idx = *it;
		double radius = atomRadii[atom_idx];
		const Math::Vector3D& coords = atomCoords[atom_idx];

		bBoxMin(0) = std::min(bBoxMin(0), coords(0) - radius);
		bBoxMin(1) = std::min(bBoxMin(1), coords(1) - radius);
		bBoxMin(2) = std::min(bBoxMin(2), coords(2) - radius);

		bBoxMax(0) = std::max(bBoxMax(0), coords(0) + radius);
		bBoxMax(1) = std::max(bBoxMax(1), coords(1) + radius);
		bBoxMax(2) = std::max(bBoxMax(2), coords(2) + radius);
	}

	gridXSize = std::ceil((bBoxMax(0) - bBoxMin(0) + 2.0 * gridOversize) / gridStepSize);
	gridYSize = std::ceil((bBoxMax(1) - bBoxMin(1) + 2.0 * gridOversize) / gridStepSize);
	gridZSize = std::ceil((bBoxMax(2) - bBoxMin(2) + 2.0 * gridOversize) / gridStepSize);

	bBoxMin(0) = 0.5 * (bBoxMax(0) + bBoxMin(0) - gridXSize * gridStepSize);
	bBoxMin(1) = 0.5 * (bBoxMax(1) + bBoxMin(1) - gridYSize * gridStepSize);
	bBoxMin(2) = 0.5 * (bBoxMax(2) + bBoxMin(2) - gridZSize * gridStepSize);

	bBoxMax(0) = bBoxMin(0) + gridXSize * gridStepSize;
	bBoxMax(1) = bBoxMin(1) + gridYSize * gridStepSize;
	bBoxMax(2) = bBoxMin(2) + gridZSize * gridStepSize;

}

void Chem::SurfaceAtomExtractor::initGridAtomLookupTable()
{
	gridAtomLookup.assign(gridXSize * gridYSize * gridZSize, AtomIndexListPtr());

	std::size_t num_prnt_atoms = parentMolGraph->getNumAtoms();

	for (std::size_t i = 0; i < num_prnt_atoms; i++) {
		double radius = atomRadii[i];
		const Math::Vector3D& coords = atomCoords[i];

		if ((coords(0) + radius) < bBoxMin(0))
			continue;

		if ((coords(1) + radius) < bBoxMin(1))
			continue;
	
		if ((coords(2) + radius) < bBoxMin(2))
			continue;

		if ((coords(0) - radius) > bBoxMax(0))
			continue;

		if ((coords(1) - radius) > bBoxMax(1))
			continue;
	
		if ((coords(2) - radius) > bBoxMax(2))
			continue;

		std::size_t grid_span = std::ceil(2 * radius / gridStepSize);
		double x = coords(0) - 0.5 * grid_span * gridStepSize - bBoxMin(0);

		for (std::size_t j = 0; j <= grid_span; j++, x += gridStepSize) {
			if (x < 0.0)
				continue;

			std::size_t x_idx = x / gridStepSize;

			if (x_idx > gridXSize - 1)
				continue;

			double y = coords(1) - 0.5 * grid_span * gridStepSize - bBoxMin(1);

			for (std::size_t k = 0; k <= grid_span; k++, y += gridStepSize) {
				if (y < 0.0)
					continue;

				std::size_t y_idx = y / gridStepSize;

				if (y_idx > gridYSize - 1)
					continue;

				double z = coords(2) - 0.5 * grid_span * gridStepSize - bBoxMin(2);

				for (std::size_t l = 0; l <= grid_span; l++, z += gridStepSize) {
					if (z < 0.0)
						continue;

					std::size_t z_idx = z / gridStepSize;

					if (z_idx > gridZSize - 1)
						continue;

					AtomIndexListPtr& alist_ptr = gridAtomLookup[z_idx * gridXSize * gridYSize + y_idx * gridXSize + x_idx];

					if (!alist_ptr)
						alist_ptr.reset(new AtomIndexList());

					alist_ptr->push_back(i);
				}
			}
		}
	}
}

void Chem::SurfaceAtomExtractor::extractSurfaceAtoms(Fragment& frag)
{
	initTestPoints();

	Math::Vector3D test_pos;
	Math::Vector3D tmp;

	for (AtomIndexList::const_iterator it = atomIndices.begin(), end = atomIndices.end(); it != end; ++it) {
		std::size_t atom_idx = *it;
		double radius = atomRadii[atom_idx];
		const Math::Vector3D& coords = atomCoords[atom_idx];

		std::size_t num_acc_pts = 0; //

		for (std::size_t i = 0; i < numTestPoints; i++) {
			test_pos.assign(coords + testPoints[i] * radius);

			std::size_t x_idx = (test_pos(0) - bBoxMin(0)) / gridStepSize;
			std::size_t y_idx = (test_pos(1) - bBoxMin(1)) / gridStepSize;
			std::size_t z_idx = (test_pos(2) - bBoxMin(2)) / gridStepSize;

			AtomIndexListPtr& alist_ptr = gridAtomLookup[z_idx * gridXSize * gridYSize + y_idx * gridXSize + x_idx];

			if (!alist_ptr) {
				num_acc_pts++;
				continue;
			}

			bool found_coll = false;

			for (AtomIndexList::const_iterator al_it = alist_ptr->begin(), al_end = alist_ptr->end(); al_it != al_end; ++al_it) {
				std::size_t nbr_atom_idx = *al_it;

				if (nbr_atom_idx == atom_idx)
					continue;

				tmp.assign(atomCoords[nbr_atom_idx] - test_pos);

				if (length(tmp) <= atomRadii[nbr_atom_idx]) {
					found_coll = true;
					break;
				}
			} 

			if (!found_coll) 
				num_acc_pts++;
		}

		if ((double(num_acc_pts) / numTestPoints) >= minSurfAcc)
			frag.addAtom(parentMolGraph->getAtom(atom_idx));
	}
}

void Chem::SurfaceAtomExtractor::initTestPoints()
{
	if (testPoints.size() == numTestPoints)
		return;

	testPoints.resize(numTestPoints);

	double inc = M_PI * (3.0 - std::sqrt(5.0));
	double off = 2.0 / numTestPoints;

	for (std::size_t i = 0; i < numTestPoints; i++) {
		double y = i * off - 1.0 + off * 0.5;
		double r = std::sqrt(1.0 - y * y);
		double phi = i * inc;
		
		Math::Vector3D& pt = testPoints[i];

		pt(0) = std::cos(phi) * r;
		pt(1) = y;
		pt(2) = std::sin(phi) * r;
	}
}
