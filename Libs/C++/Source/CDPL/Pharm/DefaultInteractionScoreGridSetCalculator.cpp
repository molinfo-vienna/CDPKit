/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultInteractionScoreGridSetCalculator.cpp 
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

#include <algorithm>

#include "CDPL/Pharm/DefaultInteractionScoreGridSetCalculator.hpp"
#include "CDPL/Pharm/InteractionScoreCombiner.hpp"  
#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"  
#include "CDPL/Pharm/IonicInteractionScore.hpp"  
#include "CDPL/Pharm/HBondingInteractionScore.hpp"  
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/CationPiInteractionScore.hpp"  
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/AttributedGridFunctions.hpp"    


using namespace CDPL;


Pharm::DefaultInteractionScoreGridSetCalculator::DefaultInteractionScoreGridSetCalculator(): 
    xStepSize(0.0), yStepSize(0.0), zStepSize(0.0),
    gridXSize(0), gridYSize(0), gridZSize(0), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4))
{
    init();
}

Pharm::DefaultInteractionScoreGridSetCalculator::DefaultInteractionScoreGridSetCalculator(double step_size, std::size_t x_size, std::size_t y_size, std::size_t z_size): 
    xStepSize(step_size), yStepSize(step_size), zStepSize(step_size),
    gridXSize(x_size), gridYSize(y_size), gridZSize(z_size), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4))
{
    init();
}

Pharm::DefaultInteractionScoreGridSetCalculator::DefaultInteractionScoreGridSetCalculator(double x_step_size, double y_step_size, double z_step_size, 
																						  std::size_t x_size, std::size_t y_size, std::size_t z_size): 
    xStepSize(x_step_size), yStepSize(y_step_size), zStepSize(z_step_size),
    gridXSize(x_size), gridYSize(y_size), gridZSize(z_size), 
    coordsTransform(Math::IdentityMatrix<double>(4, 4))
{
    init();
}

const Math::Matrix4D& Pharm::DefaultInteractionScoreGridSetCalculator::getCoordinatesTransform() const
{
    return coordsTransform;
}

double Pharm::DefaultInteractionScoreGridSetCalculator::getXStepSize() const
{
    return xStepSize;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::setXStepSize(double size)
{
    xStepSize = size;
}

double Pharm::DefaultInteractionScoreGridSetCalculator::getYStepSize() const
{
    return yStepSize;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::setYStepSize(double size)
{
    yStepSize = size;
}

double Pharm::DefaultInteractionScoreGridSetCalculator::getZStepSize() const
{
    return zStepSize;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::setZStepSize(double size)
{
    zStepSize = size;
}

std::size_t Pharm::DefaultInteractionScoreGridSetCalculator::getGridXSize() const
{
    return gridXSize;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::setGridXSize(std::size_t size)
{
    gridXSize = size;
}

std::size_t Pharm::DefaultInteractionScoreGridSetCalculator::getGridYSize() const
{
    return gridYSize;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::setGridYSize(std::size_t size)
{
    gridYSize = size;
}

std::size_t Pharm::DefaultInteractionScoreGridSetCalculator::getGridZSize() const
{
    return gridZSize;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::setGridZSize(std::size_t size)
{
    gridZSize = size;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::calculate(const FeatureContainer& features, Grid::DRegularGridSet& grid_set)
{
	gridSet = &grid_set;

	InteractionScoreGridSetCalculator::calculate(features);
}

Grid::DSpatialGrid::SharedPointer Pharm::DefaultInteractionScoreGridSetCalculator::createGrid(unsigned int ftr_type, unsigned int tgt_ftr_type) const
{
	Grid::DRegularGrid::SharedPointer grid_ptr(new Grid::DRegularGrid(xStepSize, yStepSize, zStepSize));
	
	grid_ptr->resize(gridXSize, gridYSize, gridZSize, false);
	grid_ptr->setCoordinatesTransform(coordsTransform);
	
	setFeatureType(*grid_ptr, ftr_type);
	setTargetFeatureType(*grid_ptr, tgt_ftr_type);

	gridSet->addElement(grid_ptr);

	return grid_ptr;
}

void Pharm::DefaultInteractionScoreGridSetCalculator::init()
{
	setScoringFunction(FeatureType::POS_IONIZABLE, FeatureType::NEG_IONIZABLE, IonicInteractionScore());
	enableInteraction(FeatureType::POS_IONIZABLE, FeatureType::NEG_IONIZABLE, true);

	setScoringFunction(FeatureType::NEG_IONIZABLE, FeatureType::POS_IONIZABLE, IonicInteractionScore());
	enableInteraction(FeatureType::NEG_IONIZABLE, FeatureType::POS_IONIZABLE, true);

	setScoringFunction(FeatureType::POS_IONIZABLE, FeatureType::AROMATIC, CationPiInteractionScore(false));
	enableInteraction(FeatureType::POS_IONIZABLE, FeatureType::AROMATIC, true);

	setScoringFunction(FeatureType::AROMATIC, FeatureType::POS_IONIZABLE, CationPiInteractionScore(true));
	enableInteraction(FeatureType::AROMATIC, FeatureType::POS_IONIZABLE, true);

	setScoringFunction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, HydrophobicInteractionScore());
	enableInteraction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, true);

	setScoringFunction(FeatureType::AROMATIC, FeatureType::AROMATIC, 
								  InteractionScoreCombiner(OrthogonalPiPiInteractionScore(), ParallelPiPiInteractionScore()));
	enableInteraction(FeatureType::AROMATIC, FeatureType::AROMATIC, true);

	setScoringFunction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, HBondingInteractionScore(true));
	enableInteraction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, true);

	setScoringFunction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, HBondingInteractionScore(false));
	enableInteraction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, true);
}
