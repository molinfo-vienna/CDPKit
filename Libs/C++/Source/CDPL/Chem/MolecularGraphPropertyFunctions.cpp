/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyFunctions.cpp 
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

#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraphProperty.hpp"
#include "CDPL/Chem/MolecularGraphPropertyDefault.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL; 


#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)        \
void Chem::set##FUNC_SUFFIX(Chem::MolecularGraph& molgraph, TYPE arg)		     \
{									             \
    molgraph.setProperty(MolecularGraphProperty::PROP_NAME, arg);		     \
}									             \
									             \
bool Chem::has##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)	  	     \
{									             \
    return molgraph.isPropertySet(MolecularGraphProperty::PROP_NAME);		     \
}									             \
									             \
void Chem::clear##FUNC_SUFFIX(Chem::MolecularGraph& molgraph)			     \
{									             \
    molgraph.removeProperty(MolecularGraphProperty::PROP_NAME);			     \
}

#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)	             \
TYPE Chem::get##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)		     \
{									             \
    return molgraph.getProperty<TYPE>(MolecularGraphProperty::PROP_NAME);            \
}									             \
									             \
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX)            \
TYPE Chem::get##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)	                   \
{									                   \
    return molgraph.getPropertyOrDefault<TYPE>(MolecularGraphProperty::PROP_NAME,	   \
					       MolecularGraphPropertyDefault::PROP_NAME);  \
}									                   \
									                   \
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


typedef const Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer& MatchExpressionPtr;


MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(NAME, const std::string&, Name)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MATCH_CONSTRAINTS, const Chem::MatchConstraintList::SharedPointer&, MatchConstraints)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(MATCH_EXPRESSION, MatchExpressionPtr, MatchExpression)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(COMPONENTS, const Chem::FragmentList::SharedPointer&, Components)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(RINGS, const Chem::FragmentList::SharedPointer&, Rings)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(SSSR, const Chem::FragmentList::SharedPointer&, SSSR)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(CYCLIC_SUBSTRUCTURE, const Chem::Fragment::SharedPointer&, CyclicSubstructure)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(AROMATIC_SUBSTRUCTURE, const Chem::Fragment::SharedPointer&, AromaticSubstructure)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(COMPONENT_GROUPS, const Chem::FragmentList::SharedPointer&, ComponentGroups)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(TOPOLOGICAL_DISTANCE_MATRIX, const Math::ULMatrix::SharedPointer&, TopologicalDistanceMatrix)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(GEOMETRICAL_DISTANCE_MATRIX, const Math::DMatrix::SharedPointer&, GeometricalDistanceMatrix)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(STOICHIOMETRIC_NUMBER, double, StoichiometricNumber)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(CONFORMATION_INDEX, std::size_t, ConformationIndex)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(STRUCTURE_DATA, const Chem::StringDataBlock::SharedPointer&, StructureData)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_USER_INITIALS, const std::string&, MDLUserInitials)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_PROGRAM_NAME, const std::string&, MDLProgramName)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(MDL_TIMESTAMP, std::time_t, MDLTimestamp)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(MDL_REGISTRY_NUMBER, std::size_t, MDLRegistryNumber)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_COMMENT, const std::string&, MDLComment)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_CTAB_VERSION, unsigned int, MDLCTABVersion)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_DIMENSIONALITY, std::size_t, MDLDimensionality) 
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_SCALING_FACTOR1, long, MDLScalingFactor1)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_SCALING_FACTOR2, double, MDLScalingFactor2)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_ENERGY, double, MDLEnergy)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MDL_CHIRAL_FLAG, bool, MDLChiralFlag)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MOL2_CHARGE_TYPE, unsigned int,MOL2ChargeType )
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MOL2_MOLECULE_TYPE, unsigned int, MOL2MoleculeType)

