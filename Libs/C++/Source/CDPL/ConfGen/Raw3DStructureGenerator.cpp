/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Raw3DStructureGenerator.cpp 
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

#include "CDPL/ConfGen/Raw3DStructureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"


using namespace CDPL;


ConfGen::Raw3DStructureGenerator::Raw3DStructureGenerator(): molGraph(0), currCoords(0)
{
	hCoordsGen.undefinedOnly(true);
}

void ConfGen::Raw3DStructureGenerator::regardAtomConfiguration(bool regard)
{
    dgConstraintsGen.regardAtomConfiguration(regard);
}

bool ConfGen::Raw3DStructureGenerator::atomConfigurationRegarded() const
{
    return dgConstraintsGen.atomConfigurationRegarded();
}

void ConfGen::Raw3DStructureGenerator::regardBondConfiguration(bool regard)
{
    dgConstraintsGen.regardBondConfiguration(regard);
}

bool ConfGen::Raw3DStructureGenerator::bondConfigurationRegarded() const
{
    return dgConstraintsGen.bondConfigurationRegarded();
}

void ConfGen::Raw3DStructureGenerator::calculateHydrogenPositions(bool calc)
{
    dgConstraintsGen.excludeHydrogens(calc);
}

bool ConfGen::Raw3DStructureGenerator::hydrogenPositionsCalculated() const
{
    return dgConstraintsGen.hydrogensExcluded();
}

void ConfGen::Raw3DStructureGenerator::setup(const Chem::MolecularGraph& molgraph, 
											 const ForceField::MMFF94InteractionData& ia_data)
{
    setup(molgraph, &ia_data);
}

void ConfGen::Raw3DStructureGenerator::setup(const Chem::MolecularGraph& molgraph) 
{
    setup(molgraph, 0);
}

bool ConfGen::Raw3DStructureGenerator::generate(Math::Vector3DArray& coords)
{
    if (!molGraph)
		return false;

    phase1CoordsGen.generate(molGraph->getNumAtoms(), coords, true);
    phase2CoordsGen.generate(molGraph->getNumAtoms(), coords, false);

	if (dgConstraintsGen.hydrogensExcluded())
		calcHydrogenCoordinates(coords);

	if (dgConstraintsGen.atomConfigurationRegarded() && !checkAtomConfigurations(coords))
		return false;

	if (dgConstraintsGen.bondConfigurationRegarded() && !checkBondConfigurations(coords))
		return false;

    return true;
}

void ConfGen::Raw3DStructureGenerator::setup(const Chem::MolecularGraph& molgraph, 
											 const ForceField::MMFF94InteractionData* ia_data)
{
    molGraph = &molgraph;

    if (ia_data)
		dgConstraintsGen.setup(molgraph, *ia_data);
    else
		dgConstraintsGen.setup(molgraph);

	double box_size = molGraph->getNumBonds() * 2;

    phase1CoordsGen.clearDistanceConstraints();
    phase1CoordsGen.clearVolumeConstraints();
	phase1CoordsGen.setBoxSize(box_size);

    dgConstraintsGen.addBondLengthConstraints(phase1CoordsGen);
    dgConstraintsGen.addBondAngleConstraints(phase1CoordsGen);
    dgConstraintsGen.addBondConfigurationConstraints(phase1CoordsGen);
    dgConstraintsGen.add14DistanceConstraints(phase1CoordsGen);
    dgConstraintsGen.addDefaultDistanceConstraints(phase1CoordsGen);
    dgConstraintsGen.addAtomConfigurationConstraints(phase1CoordsGen);

    phase2CoordsGen = phase1CoordsGen;

    dgConstraintsGen.addAtomPlanarityConstraints(phase2CoordsGen);	 
    dgConstraintsGen.addBondPlanarityConstraints(phase2CoordsGen);
}

void ConfGen::Raw3DStructureGenerator::calcHydrogenCoordinates(Math::Vector3DArray& coords)
{
	currCoords = &coords;

	hCoordsGen.setAtom3DCoordinatesFunction(boost::bind(&ConfGen::Raw3DStructureGenerator::get3DCoordinates, this, _1));
	hCoordsGen.setAtom3DCoordinatesCheckFunction(boost::bind(&ConfGen::Raw3DStructureGenerator::has3DCoordinates, this, _1));

	hCoordsGen.generate(*molGraph, coords, false);
}

bool ConfGen::Raw3DStructureGenerator::checkAtomConfigurations(Math::Vector3DArray& coords) const
{

	for (DGConstraintGenerator::ConstStereoCenterDataIterator it = dgConstraintsGen.getAtomStereoCenterDataBegin(),
			 end = dgConstraintsGen.getAtomStereoCenterDataEnd(); it != end; ++it) {

		const DGConstraintGenerator::StereoCenterData& sc_data = *it;

		if (!checkAtomConfiguration(molGraph->getAtom(sc_data.first), *molGraph, sc_data.second, coords))
			return false;
	}

	return true;
}

bool ConfGen::Raw3DStructureGenerator::checkBondConfigurations(Math::Vector3DArray& coords) const
{
	for (DGConstraintGenerator::ConstStereoCenterDataIterator it = dgConstraintsGen.getBondStereoCenterDataBegin(),
			 end = dgConstraintsGen.getBondStereoCenterDataEnd(); it != end; ++it) {

		const DGConstraintGenerator::StereoCenterData& sc_data = *it;

		if (!checkBondConfiguration(molGraph->getBond(sc_data.first), *molGraph, sc_data.second, coords))
			return false;
	}

	return true;
}

const Math::Vector3D& ConfGen::Raw3DStructureGenerator::get3DCoordinates(const Chem::Atom& atom) const
{
	return (*currCoords)[molGraph->getAtomIndex(atom)];
}

bool ConfGen::Raw3DStructureGenerator::has3DCoordinates(const Chem::Atom& atom) const
{
	return !dgConstraintsGen.getExcludedHydrogenMask().test(molGraph->getAtomIndex(atom));
}
