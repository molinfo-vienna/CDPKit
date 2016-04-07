/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondDonorFeatureGenerator.cpp 
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

#include "CDPL/Chem/HBondDonorFeatureGenerator.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/FeatureType.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"


using namespace CDPL; 


Chem::HBondDonorFeatureGenerator::HBondDonorFeatureGenerator()
{
    init();
}

Chem::HBondDonorFeatureGenerator::HBondDonorFeatureGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm) 
{
    init();
    generate(molgraph, pharm);
}

void Chem::HBondDonorFeatureGenerator::init()
{
    addIncludePattern(parseSMARTS("[O:3][#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[CX2,SX2:3][#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[*:4](=,:*)-,:[#7:11](-,:[*:4])[#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::VECTOR, 3.0);
    addIncludePattern(parseSMARTS("[#7:3][#1]"), FeatureType::H_BOND_DONOR, 1.5, FeatureGeometry::SPHERE);

    addExcludePattern(parseSMARTS("c1nnnn1"));
    addExcludePattern(parseSMARTS("N-[SX4](=O)(=O)[CX4](F)(F)F"));
    addExcludePattern(parseSMARTS("[C,P,S](=O)O"));
}
