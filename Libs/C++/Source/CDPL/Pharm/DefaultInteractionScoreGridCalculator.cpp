/* -*- mode: c++; c-basic-offcalculator: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultInteractionScoreGridCalculator.cpp 
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

#include "CDPL/Pharm/DefaultInteractionScoreGridCalculator.hpp"
#include "CDPL/Pharm/StericAtomClashFactorCalculator.hpp"
#include "CDPL/Pharm/InteractionScoreCombiner.hpp"  
#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"  
#include "CDPL/Pharm/IonicInteractionScore.hpp"  
#include "CDPL/Pharm/HBondingInteractionScore.hpp"  
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/CationPiInteractionScore.hpp"  
#include "CDPL/Pharm/FeatureType.hpp"  


using namespace CDPL;


Pharm::DefaultInteractionScoreGridCalculator::DefaultInteractionScoreGridCalculator(): InteractionScoreGridCalculator()
{
    init();
}

Pharm::DefaultInteractionScoreGridCalculator::DefaultInteractionScoreGridCalculator(double step_size, std::size_t x_size, std::size_t y_size, std::size_t z_size): 
	InteractionScoreGridCalculator(step_size, x_size, y_size, z_size)
{
    init();
}

Pharm::DefaultInteractionScoreGridCalculator::DefaultInteractionScoreGridCalculator(double x_step_size, double y_step_size, double z_step_size, 
																					std::size_t x_size, std::size_t y_size, std::size_t z_size): 
  	InteractionScoreGridCalculator(x_step_size, y_step_size, z_step_size, x_size, y_size, z_size)
{
    init();
}

void Pharm::DefaultInteractionScoreGridCalculator::init()
{
	setInteractionScoringFunction(FeatureType::POS_IONIZABLE, FeatureType::NEG_IONIZABLE, IonicInteractionScore());
	enableInteraction(FeatureType::POS_IONIZABLE, FeatureType::NEG_IONIZABLE, true);

	setInteractionScoringFunction(FeatureType::NEG_IONIZABLE, FeatureType::POS_IONIZABLE, IonicInteractionScore());
	enableInteraction(FeatureType::NEG_IONIZABLE, FeatureType::POS_IONIZABLE, true);

	setInteractionScoringFunction(FeatureType::POS_IONIZABLE, FeatureType::AROMATIC, CationPiInteractionScore(false));
	enableInteraction(FeatureType::POS_IONIZABLE, FeatureType::AROMATIC, true);

	setInteractionScoringFunction(FeatureType::AROMATIC, FeatureType::POS_IONIZABLE, CationPiInteractionScore(true));
	enableInteraction(FeatureType::AROMATIC, FeatureType::POS_IONIZABLE, true);

	setInteractionScoringFunction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, HydrophobicInteractionScore());
	enableInteraction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, true);

	setInteractionScoringFunction(FeatureType::AROMATIC, FeatureType::AROMATIC, 
								  InteractionScoreCombiner(OrthogonalPiPiInteractionScore(), ParallelPiPiInteractionScore(), &std::max<double>));
	enableInteraction(FeatureType::AROMATIC, FeatureType::AROMATIC, true);

	setInteractionScoringFunction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, HBondingInteractionScore(true));
	enableInteraction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, true);

	setInteractionScoringFunction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, HBondingInteractionScore(false));
	enableInteraction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, true);

	setStericClashFactorFunction(StericAtomClashFactorCalculator());
}
