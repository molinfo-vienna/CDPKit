/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultFeatureInteractionAnalyzer.cpp 
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

#include "CDPL/Chem/DefaultFeatureInteractionAnalyzer.hpp"
#include "CDPL/Chem/IonicInteractionConstraint.hpp"
#include "CDPL/Chem/HydrophobicInteractionConstraint.hpp"
#include "CDPL/Chem/HBondingInteractionConstraint.hpp"
#include "CDPL/Chem/CationPiInteractionConstraint.hpp"
#include "CDPL/Chem/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Chem/ParallelPiPiInteractionConstraint.hpp"
#include "CDPL/Chem/FeatureInteractionConstraintConnector.hpp"
#include "CDPL/Chem/FeatureType.hpp"


using namespace CDPL; 


Chem::DefaultFeatureInteractionAnalyzer::DefaultFeatureInteractionAnalyzer()
{
    init();
}

Chem::DefaultFeatureInteractionAnalyzer::DefaultFeatureInteractionAnalyzer(const Pharmacophore& pharm1, const Pharmacophore& pharm2, FeatureMapping& interactions)
{
    init();
    analyze(pharm1, pharm2, interactions);
}

void Chem::DefaultFeatureInteractionAnalyzer::init()
{
	setConstraintFunction(FeatureType::POS_IONIZABLE, FeatureType::NEG_IONIZABLE, IonicInteractionConstraint());
	setConstraintFunction(FeatureType::NEG_IONIZABLE, FeatureType::POS_IONIZABLE, IonicInteractionConstraint());

	setConstraintFunction(FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, HydrophobicInteractionConstraint());

	setConstraintFunction(FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, HBondingInteractionConstraint(true));
	setConstraintFunction(FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, HBondingInteractionConstraint(false));

	setConstraintFunction(FeatureType::AROMATIC, FeatureType::POS_IONIZABLE, CationPiInteractionConstraint(true));
	setConstraintFunction(FeatureType::POS_IONIZABLE, FeatureType::AROMATIC, CationPiInteractionConstraint(false));

	setConstraintFunction(FeatureType::AROMATIC, FeatureType::AROMATIC, 
						  FeatureInteractionConstraintConnector(false, 
																OrthogonalPiPiInteractionConstraint(), 
																ParallelPiPiInteractionConstraint()));
}
