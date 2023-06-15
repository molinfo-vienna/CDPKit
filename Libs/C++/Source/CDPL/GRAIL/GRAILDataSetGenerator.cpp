/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GRAILDataSetGenerator.cpp 
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

#include <algorithm>
#include <functional>
#include <cmath>

#include "CDPL/GRAIL/GRAILDataSetGenerator.hpp"
#include "CDPL/GRAIL/AttributedGridFunctions.hpp"
#include "CDPL/Pharm/FeatureInteractionScoreCombiner.hpp"  
#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"  
#include "CDPL/Pharm/IonicInteractionScore.hpp"  
#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/XBondingInteractionScore.hpp"  
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/CationPiInteractionScore.hpp"  
#include "CDPL/Pharm/FeatureFunctions.hpp"  
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Grid/AttributedGridFunctions.hpp"
#include "CDPL/Math/AffineTransform.hpp"


using namespace CDPL;


namespace
{

    const GRAIL::FeatureInteractionScoreGridCalculator::ScoringFunction NO_SCORING_FUNC;
	const std::string                                                   NO_GRID_NAME;
}


constexpr double GRAIL::GRAILDataSetGenerator::DEF_GRID_STEP_SIZE;

GRAIL::GRAILDataSetGenerator::GRAILDataSetGenerator(): 
	pharmGenerator(Pharm::DefaultPharmacophoreGenerator::STATIC_H_DONORS),
    gridStepSize(DEF_GRID_STEP_SIZE), gridXSize(0), gridYSize(0), gridZSize(0), 
    gridTransform(Math::IdentityMatrix<double>(4, 4)), diminishByAtomDensity(true),
	storeEnvAtomDensityGrid(true), envAtomDensityGridName("ENV")
{
    init();
}

const Math::Matrix4D& GRAIL::GRAILDataSetGenerator::getGridTransform() const
{
    return gridTransform;
}

double GRAIL::GRAILDataSetGenerator::getGridStepSize() const
{
    return gridStepSize;
}

void GRAIL::GRAILDataSetGenerator::setGridStepSize(double size)
{
    gridStepSize = size;
}

std::size_t GRAIL::GRAILDataSetGenerator::getGridXSize() const
{
    return gridXSize;
}

void GRAIL::GRAILDataSetGenerator::setGridXSize(std::size_t size)
{
    gridXSize = size;
}

std::size_t GRAIL::GRAILDataSetGenerator::getGridYSize() const
{
    return gridYSize;
}

void GRAIL::GRAILDataSetGenerator::setGridYSize(std::size_t size)
{
    gridYSize = size;
}

std::size_t GRAIL::GRAILDataSetGenerator::getGridZSize() const
{
    return gridZSize;
}

void GRAIL::GRAILDataSetGenerator::setGridZSize(std::size_t size)
{
    gridZSize = size;
}

void GRAIL::GRAILDataSetGenerator::setGridParamsForBoundingBox(const Math::Vector3D& bbox_min, const Math::Vector3D& bbox_max, double step_size)
{
	Math::Vector3D grid_ctr = (bbox_min + bbox_max) * 0.5;

	gridTransform = Math::TranslationMatrix<double>(4, grid_ctr[0], grid_ctr[1], grid_ctr[2]);
	gridStepSize = step_size;
	
	double grid_w = bbox_max[0] - bbox_min[0];
    double grid_h = bbox_max[1] - bbox_min[1];
    double grid_d = bbox_max[2] - bbox_min[2];

	gridXSize = std::floor(grid_w / step_size);
	gridYSize = std::floor(grid_h / step_size);
	gridZSize = std::floor(grid_d / step_size);
}

void GRAIL::GRAILDataSetGenerator::enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable)
{
    if (enable)
		enabledFtrInteractions.insert(FeatureTypePair(ftr_type, tgt_ftr_type));
    else
		enabledFtrInteractions.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}

bool GRAIL::GRAILDataSetGenerator::isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
    return (enabledFtrInteractions.find(FeatureTypePair(ftr_type, tgt_ftr_type)) != enabledFtrInteractions.end());
}

void GRAIL::GRAILDataSetGenerator::clearEnabledInteractions()
{
    enabledFtrInteractions.clear();
}

void GRAIL::GRAILDataSetGenerator::setScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const ScoringFunction& func)
{
    ftrInteractionScoringFuncMap[FeatureTypePair(ftr_type, tgt_ftr_type)] = func;
}

const GRAIL::GRAILDataSetGenerator::ScoringFunction& 
GRAIL::GRAILDataSetGenerator::getScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
    ScoringFuncMap::const_iterator it = ftrInteractionScoringFuncMap.find(FeatureTypePair(ftr_type, tgt_ftr_type));

    return (it == ftrInteractionScoringFuncMap.end() ? NO_SCORING_FUNC : it->second);
}

void GRAIL::GRAILDataSetGenerator::removeScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type)
{
    ftrInteractionScoringFuncMap.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}

void GRAIL::GRAILDataSetGenerator::setGridName(unsigned int ftr_type, unsigned int tgt_ftr_type, const std::string& name)
{
	gridNameMap[FeatureTypePair(ftr_type, tgt_ftr_type)] = name;
}

const std::string& GRAIL::GRAILDataSetGenerator::getGridName(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
	GridNameMap::const_iterator it = gridNameMap.find(FeatureTypePair(ftr_type, tgt_ftr_type));

    return (it == gridNameMap.end() ? NO_GRID_NAME : it->second);
}

void GRAIL::GRAILDataSetGenerator::removeGridName(unsigned int ftr_type, unsigned int tgt_ftr_type)
{
	gridNameMap.erase(FeatureTypePair(ftr_type, tgt_ftr_type));
}
		
void GRAIL::GRAILDataSetGenerator::setScoreCombinationFunction(const ScoreCombinationFunction& func)
{
    ftrInteractionGridCalc.setScoreCombinationFunction(func);
}

const GRAIL::GRAILDataSetGenerator::ScoreCombinationFunction& GRAIL::GRAILDataSetGenerator::getScoreCombinationFunction() const
{
    return ftrInteractionGridCalc.getScoreCombinationFunction();
}

void GRAIL::GRAILDataSetGenerator::normalizeScores(bool normalize)
{
    ftrInteractionGridCalc.normalizeScores(normalize);
}

bool GRAIL::GRAILDataSetGenerator::scoresNormalized() const
{
    return ftrInteractionGridCalc.scoresNormalized();
}

void GRAIL::GRAILDataSetGenerator::diminishScoresByAtomDensity(bool diminish)
{
	diminishByAtomDensity = diminish;
}

bool GRAIL::GRAILDataSetGenerator::scoresDiminishedByAtomDensity() const
{
	return diminishByAtomDensity;
}

void GRAIL::GRAILDataSetGenerator::storeEnvironmentAtomDensityGrid(bool store)
{
	storeEnvAtomDensityGrid = store;
}

bool GRAIL::GRAILDataSetGenerator::environmentAtomDensityGridStored() const
{
	return storeEnvAtomDensityGrid;
}

void GRAIL::GRAILDataSetGenerator::setEnvironmentAtomDensityGridName(const std::string& name)
{
	envAtomDensityGridName = name;
}

const std::string& GRAIL::GRAILDataSetGenerator::getEnvironmentAtomDensityGridName() const
{
	return envAtomDensityGridName;
}

const Pharm::DefaultPharmacophoreGenerator& GRAIL::GRAILDataSetGenerator::getPharmacophoreGenerator() const
{
	return pharmGenerator;
}

Pharm::DefaultPharmacophoreGenerator& GRAIL::GRAILDataSetGenerator::getPharmacophoreGenerator()
{
	return pharmGenerator;
}

void GRAIL::GRAILDataSetGenerator::setPharmacophoreProcessingFunction(const PharmacophoreProcessingFunction& func)
{
	pharmProcessingFunc = func;
}

const GRAIL::GRAILDataSetGenerator::PharmacophoreProcessingFunction&
GRAIL::GRAILDataSetGenerator::getPharmacophoreProcessingFunction() const
{
	return pharmProcessingFunc;
}
			
void GRAIL::GRAILDataSetGenerator::calcInteractionGrids(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
														Grid::DRegularGridSet& grid_set, bool append)
{
	using namespace std::placeholders;

	if (!append)
		grid_set.clear();
	
	Grid::DRegularGrid::SharedPointer env_atom_grid_ptr;

	if (diminishByAtomDensity || storeEnvAtomDensityGrid)
		env_atom_grid_ptr = calcAtomDensityGrid(tgt_env, coords_func, envAtomDensityGridName);

	pharmGenerator.setAtom3DCoordinatesFunction(coords_func);
	pharmGenerator.generate(tgt_env, pharmacophore);

	if (pharmProcessingFunc)
		pharmProcessingFunc(pharmacophore);
	
	std::size_t num_grid_pts = (diminishByAtomDensity ? env_atom_grid_ptr->getNumElements() : 0);
	
    for (ScoringFuncMap::const_iterator it = ftrInteractionScoringFuncMap.begin(), end = ftrInteractionScoringFuncMap.end(); it != end; ++it) {
		if (!it->second)
			continue;

		if (enabledFtrInteractions.find(it->first) == enabledFtrInteractions.end())
			continue;

		unsigned int ftr_type = it->first.first;
		unsigned int tgt_ftr_type = it->first.second;

		Grid::DRegularGrid::SharedPointer grid_ptr = createGrid();
	
		setFeatureType(*grid_ptr, ftr_type);
		setTargetFeatureType(*grid_ptr, tgt_ftr_type);

		const std::string& grid_name = getGridName(ftr_type, tgt_ftr_type);

		if (&grid_name != &NO_GRID_NAME)
			setName(*grid_ptr, grid_name);
		
		ftrInteractionGridCalc.setScoringFunction(it->second);
		ftrInteractionGridCalc.setFeatureSelectionPredicate(std::bind(std::equal_to<unsigned int>(), std::bind(&Pharm::getType, _1), tgt_ftr_type));
		ftrInteractionGridCalc.calculate(pharmacophore, *grid_ptr);

		for (std::size_t i = 0; i < num_grid_pts; i++)
			(*grid_ptr)(i) *= (1.0 - (*env_atom_grid_ptr)(i));

		grid_set.addElement(grid_ptr);
    }

	if (storeEnvAtomDensityGrid)
		grid_set.addElement(env_atom_grid_ptr);
}

Grid::DRegularGrid::SharedPointer
GRAIL::GRAILDataSetGenerator::calcAtomDensityGrid(const Chem::AtomContainer& atoms, const Chem::Atom3DCoordinatesFunction& coords_func,
												  const std::string& grid_name)
{
	Grid::DRegularGrid::SharedPointer grid_ptr = createGrid();

	if (!grid_name.empty())
		setName(*grid_ptr, grid_name);

	atomDensityGridCalc.setAtom3DCoordinatesFunction(coords_func);
	atomDensityGridCalc.calculate(atoms, *grid_ptr);
	
	return grid_ptr;
}

Grid::DRegularGrid::SharedPointer GRAIL::GRAILDataSetGenerator::createGrid() const
{
    Grid::DRegularGrid::SharedPointer grid_ptr(new Grid::DRegularGrid(gridStepSize));
	
    grid_ptr->resize(gridXSize, gridYSize, gridZSize, false);
    grid_ptr->setCoordinatesTransform(gridTransform);

    return grid_ptr;
}

void GRAIL::GRAILDataSetGenerator::init()
{
    using namespace Pharm;
	
    setScoringFunction(FeatureType::POSITIVE_IONIZABLE, FeatureType::NEGATIVE_IONIZABLE, IonicInteractionScore());
    enableInteraction(FeatureType::POSITIVE_IONIZABLE, FeatureType::NEGATIVE_IONIZABLE, true);
    setGridName(FeatureType::POSITIVE_IONIZABLE, FeatureType::NEGATIVE_IONIZABLE, "PI-NI");
	
    setScoringFunction(FeatureType::NEGATIVE_IONIZABLE, FeatureType::POSITIVE_IONIZABLE, IonicInteractionScore());
    enableInteraction(FeatureType::NEGATIVE_IONIZABLE, FeatureType::POSITIVE_IONIZABLE, true);
	setGridName(FeatureType::NEGATIVE_IONIZABLE, FeatureType::POSITIVE_IONIZABLE, "NI-PI");

    setScoringFunction(FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, CationPiInteractionScore(false));
    enableInteraction(FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, true);
	setGridName(FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, "PI-AR");

    setScoringFunction(FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, CationPiInteractionScore(true));
    enableInteraction(FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, true);
	setGridName(FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, "AR-PI");

    setScoringFunction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, HydrophobicInteractionScore());
    enableInteraction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, true);
	setGridName(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, "H-H");

    setScoringFunction(FeatureType::AROMATIC, FeatureType::AROMATIC, 
					   FeatureInteractionScoreCombiner(FeatureInteractionScore::SharedPointer(new OrthogonalPiPiInteractionScore()),
													   FeatureInteractionScore::SharedPointer(new ParallelPiPiInteractionScore())));
    enableInteraction(FeatureType::AROMATIC, FeatureType::AROMATIC, true);
	setGridName(FeatureType::AROMATIC, FeatureType::AROMATIC, "AR-AR");

    setScoringFunction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, HBondingInteractionScore(true));
    enableInteraction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, true);
	setGridName(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, "HBD-HBA");

    setScoringFunction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, HBondingInteractionScore(false));
    enableInteraction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, true);
	setGridName(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, "HBA-HBD");

    setScoringFunction(FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, XBondingInteractionScore(true));
    enableInteraction(FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, true);
	setGridName(FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, "XBD-XBA");

	pharmGenerator.enableFeature(Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR, true);
}
