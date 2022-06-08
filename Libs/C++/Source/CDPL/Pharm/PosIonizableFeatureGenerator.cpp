/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PosIonizableFeatureGenerator.cpp 
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

#include "CDPL/Pharm/PosIonizableFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL; 


Pharm::PosIonizableFeatureGenerator::PosIonizableFeatureGenerator(bool chgd_groups_only)
{
    init(chgd_groups_only);
}

Pharm::PosIonizableFeatureGenerator::PosIonizableFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, bool chgd_groups_only)
{
    init(chgd_groups_only);
    generate(molgraph, pharm);
}

void Pharm::PosIonizableFeatureGenerator::init(bool chgd_groups_only)
{
    using namespace Chem;

	if (!chgd_groups_only) {
		addIncludePattern(parseSMARTS("[NX3:3]([CX4])([CX4,#1])[CX4,#1]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[NX4:3]([CX4])([CX4,#1])([CX4,#1])[CX4,#1]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N:3])[!N]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N:3])[N:3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);

	} else {
		addIncludePattern(parseSMARTS("[N+1:3]=[CX3:3]([N:3])[!N]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N+1:3])[!N]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N+1:3]=[CX3:3]([N:3])[N:3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N+1:3])[N:3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N:3]=[CX3:3]([N:3])[N+1:3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
	}

    addIncludePattern(parseSMARTS("[+,+2,+3,+4,+5,+6,+7;!$(*~[-,-2,-3,-4,-5,-6,-7]):3]"), FeatureType::POS_IONIZABLE, 1.5, FeatureGeometry::SPHERE);

    addExcludePattern(parseSMARTS("[N:1]-[C,S,P]=O"));
}
