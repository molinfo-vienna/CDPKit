/* 
 * MolecularGraphPrepareFor2DVisualizationFunction.cpp 
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

#include "CDPL/Vis/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"


using namespace CDPL;


void Vis::prepareFor2DVisualization(Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
    
    perceiveComponents(molgraph, false);
    perceiveComponentGroups(molgraph, false);
    perceiveSSSR(molgraph, false);
    setRingFlags(molgraph, false);
    calcTopologicalDistanceMatrix(molgraph, false);

    calcImplicitHydrogenCounts(molgraph, false);
    perceiveHybridizationStates(molgraph, false);
    setAromaticityFlags(molgraph, false);

    perceiveAtomStereoCenters(molgraph, false, false);
    perceiveBondStereoCenters(molgraph, false, false);
    calcAtomStereoDescriptors(molgraph, false);
    calcBondStereoDescriptors(molgraph, false);

    setAtomSymbolsFromTypes(molgraph, false);
    generateMatchExpressionStrings(molgraph, false);
}
