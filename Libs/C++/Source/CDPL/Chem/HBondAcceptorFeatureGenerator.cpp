/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondAcceptorFeatureGenerator.cpp 
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

#include "CDPL/Chem/HBondAcceptorFeatureGenerator.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/FeatureType.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"


using namespace CDPL; 


Chem::HBondAcceptorFeatureGenerator::HBondAcceptorFeatureGenerator()
{
    init();
}

Chem::HBondAcceptorFeatureGenerator::HBondAcceptorFeatureGenerator(const MolecularGraph& molgraph, Pharmacophore& pharm) 

{
    init();
    generate(molgraph, pharm);
}

void Chem::HBondAcceptorFeatureGenerator::init()
{
	addIncludePattern(parseSMARTS("[*:8]~[#7,#8,S;X2;!$(O(C)C(=O)):7]~[*:8]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR, 1.0);
	addIncludePattern(parseSMARTS("[*:8]~[#7,#8,S;X2;!$(O(C)C(=O)):7]-[#1]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR, 1.0);
	addIncludePattern(parseSMARTS("[*:8]~[N,O,S;X1:7]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR, 1.0);
	addIncludePattern(parseSMARTS("[#7,#8,S;X1,X2;!$(O(C)C(=O)):3]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE, 1.0);
	addIncludePattern(parseSMARTS("[*:8]-[F:7]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR, 1.0);
   
   addExcludePattern(parseSMARTS("[#8](c)c"));
}
