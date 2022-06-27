/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondAcceptorFeatureGenerator.cpp 
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

#include "CDPL/Pharm/HBondAcceptorFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL; 


Pharm::HBondAcceptorFeatureGenerator::HBondAcceptorFeatureGenerator()
{
    init();
}

Pharm::HBondAcceptorFeatureGenerator::HBondAcceptorFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm) 

{
    init();
    generate(molgraph, pharm);
}

void Pharm::HBondAcceptorFeatureGenerator::init()
{
    using namespace Chem;

	addIncludePattern(parseSMARTS("[*:8]~[#8,#7,S;X2:7]~[*:8]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]=[N;X2:7]-[#1]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]#[N;X1:7]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]-[N;X3:7](-[#1])-[#1]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]-[#7;X3:7](-[*:8])-[#1]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]-[N;X3:7](-[*:8])-[*:8]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]-[O,S;X2:7]-[#1]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]-,=[O,S;X1:7]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[O,S;X2:3]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[#7;X3:3]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
	addIncludePattern(parseSMARTS("[*:8]-[F:7]"), FeatureType::H_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);

	addExcludePattern(parseSMARTS("[+1:1]"));
	addExcludePattern(parseSMARTS("[N:1]-[a]"));
	addExcludePattern(parseSMARTS("[O,S:1](-[a])-[a]"));
	addExcludePattern(parseSMARTS("[O,S:1](-[*])-[P,S,C]=O"));
	addExcludePattern(parseSMARTS("[N:1]-[P,S,C]=O"));
	addExcludePattern(parseSMARTS("[N:1]=[P,S,C]-O"));
}
