/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultInteractionScoreGridSetCalculator.cpp 
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

#include "CDPL/GRAIL/DefaultInteractionScoreGridSetCalculator.hpp"
#include "CDPL/GRAIL/AttributedGridFunctions.hpp"
#include "CDPL/Pharm/FeatureInteractionScoreCombiner.hpp"  
#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"  
#include "CDPL/Pharm/IonicInteractionScore.hpp"  
#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/XBondingInteractionScore.hpp"  
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/CationPiInteractionScore.hpp"  
#include "CDPL/Pharm/FeatureType.hpp"


using namespace CDPL;


GRAIL::DefaultInteractionScoreGridSetCalculator::DefaultInteractionScoreGridSetCalculator(): 
    xStepSize(0.0), yStepSize(0.0), zStepSize(0.0),
    gridXSize(0), gridYSize(0), gridZSize(0), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4))
{
    init();
}

GRAIL::DefaultInteractionScoreGridSetCalculator::DefaultInteractionScoreGridSetCalculator(double step_size, std::size_t x_size, std::size_t y_size, std::size_t z_size): 
    xStepSize(step_size), yStepSize(step_size), zStepSize(step_size),
    gridXSize(x_size), gridYSize(y_size), gridZSize(z_size), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4))
{
    init();
}

GRAIL::DefaultInteractionScoreGridSetCalculator::DefaultInteractionScoreGridSetCalculator(double x_step_size, double y_step_size, double z_step_size, 
																						  std::size_t x_size, std::size_t y_size, std::size_t z_size): 
    xStepSize(x_step_size), yStepSize(y_step_size), zStepSize(z_step_size),
    gridXSize(x_size), gridYSize(y_size), gridZSize(z_size), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4))
{
    init();
}

const Math::Matrix4D& GRAIL::DefaultInteractionScoreGridSetCalculator::getCoordinatesTransform() const
{
    return coordsTransform;
}

double GRAIL::DefaultInteractionScoreGridSetCalculator::getXStepSize() const
{
    return xStepSize;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::setXStepSize(double size)
{
    xStepSize = size;
}

double GRAIL::DefaultInteractionScoreGridSetCalculator::getYStepSize() const
{
    return yStepSize;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::setYStepSize(double size)
{
    yStepSize = size;
}

double GRAIL::DefaultInteractionScoreGridSetCalculator::getZStepSize() const
{
    return zStepSize;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::setZStepSize(double size)
{
    zStepSize = size;
}

std::size_t GRAIL::DefaultInteractionScoreGridSetCalculator::getGridXSize() const
{
    return gridXSize;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::setGridXSize(std::size_t size)
{
    gridXSize = size;
}

std::size_t GRAIL::DefaultInteractionScoreGridSetCalculator::getGridYSize() const
{
    return gridYSize;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::setGridYSize(std::size_t size)
{
    gridYSize = size;
}

std::size_t GRAIL::DefaultInteractionScoreGridSetCalculator::getGridZSize() const
{
    return gridZSize;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::setGridZSize(std::size_t size)
{
    gridZSize = size;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::calculate(const Pharm::FeatureContainer& tgt_ftrs, Grid::DRegularGridSet& grid_set)
{
	gridSet = &grid_set;

	InteractionScoreGridSetCalculator::calculate(tgt_ftrs);
}

Grid::DSpatialGrid::SharedPointer GRAIL::DefaultInteractionScoreGridSetCalculator::createGrid(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
	Grid::DRegularGrid::SharedPointer grid_ptr(new Grid::DRegularGrid(xStepSize, yStepSize, zStepSize));
	
	grid_ptr->resize(gridXSize, gridYSize, gridZSize, false);
	grid_ptr->setCoordinatesTransform(coordsTransform);
	
	setFeatureType(*grid_ptr, ftr_type);
	setTargetFeatureType(*grid_ptr, tgt_ftr_type);

	gridSet->addElement(grid_ptr);

	return grid_ptr;
}

void GRAIL::DefaultInteractionScoreGridSetCalculator::init()
{
	using namespace Pharm;
	
	setScoringFunction(FeatureType::POSITIVE_IONIZABLE, FeatureType::NEGATIVE_IONIZABLE, IonicInteractionScore());
	enableInteraction(FeatureType::POSITIVE_IONIZABLE, FeatureType::NEGATIVE_IONIZABLE, true);

	setScoringFunction(FeatureType::NEGATIVE_IONIZABLE, FeatureType::POSITIVE_IONIZABLE, IonicInteractionScore());
	enableInteraction(FeatureType::NEGATIVE_IONIZABLE, FeatureType::POSITIVE_IONIZABLE, true);

	setScoringFunction(FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, CationPiInteractionScore(false));
	enableInteraction(FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, true);

	setScoringFunction(FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, CationPiInteractionScore(true));
	enableInteraction(FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, true);

	setScoringFunction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, HydrophobicInteractionScore());
	enableInteraction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, true);

	setScoringFunction(FeatureType::AROMATIC, FeatureType::AROMATIC, 
					   FeatureInteractionScoreCombiner(FeatureInteractionScore::SharedPointer(new OrthogonalPiPiInteractionScore()),
													   FeatureInteractionScore::SharedPointer(new ParallelPiPiInteractionScore())));
	enableInteraction(FeatureType::AROMATIC, FeatureType::AROMATIC, true);

	setScoringFunction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, HBondingInteractionScore(true));
	enableInteraction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, true);

	setScoringFunction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, HBondingInteractionScore(false));
	enableInteraction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, true);

	setScoringFunction(FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, XBondingInteractionScore(true));
	enableInteraction(FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, true);

}
