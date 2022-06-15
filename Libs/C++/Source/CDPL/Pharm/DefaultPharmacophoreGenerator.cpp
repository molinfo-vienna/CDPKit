/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultPharmacophoreGenerator.cpp 
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

#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/AromaticFeatureGenerator.hpp"
#include "CDPL/Pharm/HydrophobicFeatureGenerator.hpp"
#include "CDPL/Pharm/HBondAcceptorFeatureGenerator.hpp"
#include "CDPL/Pharm/HBondDonorFeatureGenerator.hpp"
#include "CDPL/Pharm/XBondAcceptorFeatureGenerator.hpp"
#include "CDPL/Pharm/XBondDonorFeatureGenerator.hpp"
#include "CDPL/Pharm/PosIonizableFeatureGenerator.hpp"
#include "CDPL/Pharm/NegIonizableFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"


using namespace CDPL; 


Pharm::DefaultPharmacophoreGenerator::DefaultPharmacophoreGenerator(Configuration config)
{
    init(config);
}

Pharm::DefaultPharmacophoreGenerator::DefaultPharmacophoreGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, Configuration config)
{
    init(config);
    generate(molgraph, pharm);
}

void Pharm::DefaultPharmacophoreGenerator::init(Configuration config)
{
	setFeatureGenerator(FeatureType::HYDROPHOBIC, FeatureGenerator::SharedPointer(new HydrophobicFeatureGenerator()));
	setFeatureGenerator(FeatureType::AROMATIC, FeatureGenerator::SharedPointer(new AromaticFeatureGenerator()));
    setFeatureGenerator(FeatureType::H_BOND_ACCEPTOR, FeatureGenerator::SharedPointer(new HBondAcceptorFeatureGenerator()));
	setFeatureGenerator(FeatureType::HALOGEN_BOND_DONOR, FeatureGenerator::SharedPointer(new XBondDonorFeatureGenerator()));
    setFeatureGenerator(FeatureType::HALOGEN_BOND_ACCEPTOR, FeatureGenerator::SharedPointer(new XBondAcceptorFeatureGenerator()));

	applyConfiguration(config);
	
    enableFeature(FeatureType::HYDROPHOBIC, true);
    enableFeature(FeatureType::AROMATIC, true);
    enableFeature(FeatureType::NEGATIVE_IONIZABLE, true);
    enableFeature(FeatureType::POSITIVE_IONIZABLE, true);
    enableFeature(FeatureType::H_BOND_DONOR, true);
    enableFeature(FeatureType::H_BOND_ACCEPTOR, true);
    enableFeature(FeatureType::HALOGEN_BOND_DONOR, true);
}

void Pharm::DefaultPharmacophoreGenerator::applyConfiguration(Configuration config)
{
	setFeatureGenerator(FeatureType::NEGATIVE_IONIZABLE, FeatureGenerator::SharedPointer(new NegIonizableFeatureGenerator(config & PI_NI_ON_CHARGED_GROUPS_ONLY)));
	setFeatureGenerator(FeatureType::POSITIVE_IONIZABLE, FeatureGenerator::SharedPointer(new PosIonizableFeatureGenerator(config & PI_NI_ON_CHARGED_GROUPS_ONLY)));
	setFeatureGenerator(FeatureType::H_BOND_DONOR, FeatureGenerator::SharedPointer(new HBondDonorFeatureGenerator(config & STATIC_H_DONORS)));
}
