/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * NegIonizableFeatureGenerator.cpp 
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

#include "CDPL/Pharm/NegIonizableFeatureGenerator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL; 


Pharm::NegIonizableFeatureGenerator::NegIonizableFeatureGenerator(bool fuzzy)
{
    init(fuzzy);
}

Pharm::NegIonizableFeatureGenerator::NegIonizableFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, bool fuzzy)
{
    init(fuzzy);
    generate(molgraph, pharm);
}

void Pharm::NegIonizableFeatureGenerator::init(bool fuzzy)
{
	using namespace Chem;

	if (fuzzy) {
		addIncludePattern(parseSMARTS("[c;!$(c[#7][#6]);!$(c[#7][#7][#6]):3]1[n:3][n:3][n:3][n:3]1"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[P,S:3](~[O:3])(~[O:3])(~[O:3])[OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[P,S:3](~[O:3])(~[O:3])[OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[NR;H1,-1:3](-C(=O))-[SX4](=O)(=O)"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[C:3](=[O:3])[N:3][OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[C:3]([O:3])[N:3][OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[C:3][O:3](=[N:3][OH1,O-:3])"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[S,C,P:3](~[O:3])[OH1,O-:3]"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N:3]-[SX4](=O)(=O)[CX4](F)(F)F"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);

	} else {
		addIncludePattern(parseSMARTS("[P,S:3](~[O:3])(~[O:3])(~[O:3])[OH0-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[P,S:3](~[O:3])(~[O:3])[OH0-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[NR;H0-:3](-C(=O))-[SX4](=O)(=O)"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[C:3](=[O:3])[N:3][OH0-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[C:3]([O:3])[N:3][OH0-:3]"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[C:3][O:3](=[N:3][OH0-:3])"), FeatureType::NEG_IONIZABLE, 2.0, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[S,C,P:3](~[O:3])[OH0-:3]"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
		addIncludePattern(parseSMARTS("[N-:3]-[SX4](=O)(=O)[CX4](F)(F)F"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);
	}

    addIncludePattern(parseSMARTS("[-,-2,-3,-4,-5,-6,-7;!$(*~[+,+2,+3,+4,+5,+6,+7]):3]"), FeatureType::NEG_IONIZABLE, 1.5, FeatureGeometry::SPHERE);

    addExcludePattern(parseSMARTS("C(=O)[OH0+0]"));
    addExcludePattern(parseSMARTS("C(O)O"));
    addExcludePattern(parseSMARTS("[P,S](~O)(~O)(~O)N"));
}
