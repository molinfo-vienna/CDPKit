/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultInteractionAnalyzer.cpp 
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

#include "CDPL/Pharm/DefaultInteractionAnalyzer.hpp"
#include "CDPL/Pharm/IonicInteractionConstraint.hpp"
#include "CDPL/Pharm/HydrophobicInteractionConstraint.hpp"
#include "CDPL/Pharm/HBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/XBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/CationPiInteractionConstraint.hpp"
#include "CDPL/Pharm/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/ParallelPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/InteractionConstraintConnector.hpp"
#include "CDPL/Pharm/FeatureType.hpp"


using namespace CDPL; 


Pharm::DefaultInteractionAnalyzer::DefaultInteractionAnalyzer()
{
    init();
}

Pharm::DefaultInteractionAnalyzer::DefaultInteractionAnalyzer(const FeatureContainer& cntnr1, const FeatureContainer& cntnr2, FeatureMapping& interactions)
{
    init();
    analyze(cntnr1, cntnr2, interactions);
}

void Pharm::DefaultInteractionAnalyzer::init()
{
	setConstraintFunction(FeatureType::POSITIVE_IONIZABLE, FeatureType::NEGATIVE_IONIZABLE, IonicInteractionConstraint());
	setConstraintFunction(FeatureType::NEGATIVE_IONIZABLE, FeatureType::POSITIVE_IONIZABLE, IonicInteractionConstraint());

	setConstraintFunction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, HydrophobicInteractionConstraint());

	setConstraintFunction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, HBondingInteractionConstraint(true));
	setConstraintFunction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, HBondingInteractionConstraint(false));

	setConstraintFunction(FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, XBondingInteractionConstraint(true));
	setConstraintFunction(FeatureType::HALOGEN_BOND_ACCEPTOR, FeatureType::HALOGEN_BOND_DONOR, XBondingInteractionConstraint(false));

	setConstraintFunction(FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, CationPiInteractionConstraint(true));
	setConstraintFunction(FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, CationPiInteractionConstraint(false));

	setConstraintFunction(FeatureType::AROMATIC, FeatureType::AROMATIC, 
						  InteractionConstraintConnector(false, 
														 OrthogonalPiPiInteractionConstraint(), 
														 ParallelPiPiInteractionConstraint()));
}
