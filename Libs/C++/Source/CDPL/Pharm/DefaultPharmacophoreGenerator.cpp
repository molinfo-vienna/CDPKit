/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DefaultPharmacophoreGenerator.cpp 
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

#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/AromaticFeatureGenerator.hpp"
#include "CDPL/Pharm/HydrophobicFeatureGenerator.hpp"
#include "CDPL/Pharm/HBondAcceptorFeatureGenerator.hpp"
#include "CDPL/Pharm/HBondDonorFeatureGenerator.hpp"
#include "CDPL/Pharm/PosIonizableFeatureGenerator.hpp"
#include "CDPL/Pharm/NegIonizableFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"


using namespace CDPL; 


Pharm::DefaultPharmacophoreGenerator::DefaultPharmacophoreGenerator(bool fuzzy)
{
    init(fuzzy);
}

Pharm::DefaultPharmacophoreGenerator::DefaultPharmacophoreGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, bool fuzzy)
{
    init(fuzzy);
    generate(molgraph, pharm);
}

void Pharm::DefaultPharmacophoreGenerator::init(bool fuzzy)
{
    ftrGenerators.push_back(FeatureGenPtr(new HydrophobicFeatureGenerator()));
    ftrGenerators.push_back(FeatureGenPtr(new AromaticFeatureGenerator()));
    ftrGenerators.push_back(FeatureGenPtr(new NegIonizableFeatureGenerator(fuzzy)));
    ftrGenerators.push_back(FeatureGenPtr(new PosIonizableFeatureGenerator(fuzzy)));
    ftrGenerators.push_back(FeatureGenPtr(new HBondDonorFeatureGenerator(fuzzy)));
    ftrGenerators.push_back(FeatureGenPtr(new HBondAcceptorFeatureGenerator()));

    setFeatureGenerator(FeatureType::HYDROPHOBIC, *ftrGenerators[0]);
    setFeatureGenerator(FeatureType::AROMATIC, *ftrGenerators[1]);
    setFeatureGenerator(FeatureType::NEG_IONIZABLE, *ftrGenerators[2]);
    setFeatureGenerator(FeatureType::POS_IONIZABLE, *ftrGenerators[3]);
    setFeatureGenerator(FeatureType::H_BOND_DONOR, *ftrGenerators[4]);
    setFeatureGenerator(FeatureType::H_BOND_ACCEPTOR, *ftrGenerators[5]);

    enableFeature(FeatureType::HYDROPHOBIC, true);
    enableFeature(FeatureType::AROMATIC, true);
    enableFeature(FeatureType::NEG_IONIZABLE, true);
    enableFeature(FeatureType::POS_IONIZABLE, true);
    enableFeature(FeatureType::H_BOND_DONOR, true);
    enableFeature(FeatureType::H_BOND_ACCEPTOR, true);
}
