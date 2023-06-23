/* 
 * XBondAcceptorFeatureGenerator.cpp 
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

#include "CDPL/Pharm/XBondAcceptorFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL; 


Pharm::XBondAcceptorFeatureGenerator::XBondAcceptorFeatureGenerator()
{
    init();
}

Pharm::XBondAcceptorFeatureGenerator::XBondAcceptorFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm) 

{
    init();
    generate(molgraph, pharm);
}

void Pharm::XBondAcceptorFeatureGenerator::init()
{
    using namespace Chem;

    addIncludePattern(parseSMARTS("[*:8]~[#8,S;X2:7]~[*:8]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[*:8]~[#7;X2:7]~[*:8]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR);
    addIncludePattern(parseSMARTS("[*:8]=[N;X2:7]-[#1]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[*:8]#[N;X1:7]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR);
    addIncludePattern(parseSMARTS("[*:8]-[N;X3:7](-[#1])-[#1]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[*:8]-[#7;X3:7](-[*:8])-[#1]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[*:8]-[N;X3:7](-[*:8])-[*:8]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::VECTOR);
    addIncludePattern(parseSMARTS("[*:8]-[O,S;X2:7]-[#1]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[*:8]-,=[O,S;X1:7]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[O,S;X2:3]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);
    addIncludePattern(parseSMARTS("[#7;X3:3]"), FeatureType::HALOGEN_BOND_ACCEPTOR, 1.5, FeatureGeometry::SPHERE);

    addExcludePattern(parseSMARTS("[+1:1]"));
}
