/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyFunctions.cpp 
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

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Chem/AtomPropertyDefault.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL; 


#define MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
void Chem::set##FUNC_SUFFIX(Chem::Atom& atom, TYPE arg)		          \
{									  \
    atom.setProperty(AtomProperty::PROP_NAME, arg);			  \
}									  \
									  \
bool Chem::has##FUNC_SUFFIX(const Chem::Atom& atom)			  \
{									  \
    return atom.isPropertySet(AtomProperty::PROP_NAME);			  \
}									  \
									  \
void Chem::clear##FUNC_SUFFIX(Chem::Atom& atom)				  \
{									  \
    atom.removeProperty(AtomProperty::PROP_NAME);			  \
}

#define MAKE_ATOM_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)	\
TYPE Chem::get##FUNC_SUFFIX(const Chem::Atom& atom)			\
{									\
    return atom.getProperty<TYPE>(AtomProperty::PROP_NAME);             \
}									\
									\
MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
TYPE Chem::get##FUNC_SUFFIX(const Chem::Atom& atom)	                    \
{									    \
    return atom.getPropertyOrDefault<TYPE>(AtomProperty::PROP_NAME,	    \
					   AtomPropertyDefault::PROP_NAME); \
}									    \
									    \
MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


typedef const Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer& MatchExpressionPtr;


MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(NAME, const std::string&, Name)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(SYMBOL, const std::string&, Symbol)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(TYPE, unsigned int, Type)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(FORMAL_CHARGE, long, FormalCharge)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(ISOTOPE, std::size_t, Isotope)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(RADICAL_TYPE, unsigned int, RadicalType)
MAKE_ATOM_PROPERTY_FUNCTIONS(HYBRIDIZATION, unsigned int, HybridizationState) 
MAKE_ATOM_PROPERTY_FUNCTIONS(RING_FLAG, bool, RingFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS(AROMATICITY_FLAG, bool, AromaticityFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(UNPAIRED_ELECTRON_COUNT, std::size_t, UnpairedElectronCount)
MAKE_ATOM_PROPERTY_FUNCTIONS(IMPLICIT_HYDROGEN_COUNT, std::size_t, ImplicitHydrogenCount)
MAKE_ATOM_PROPERTY_FUNCTIONS(COORDINATES_2D, const Math::Vector2D&, 2DCoordinates)
MAKE_ATOM_PROPERTY_FUNCTIONS(COORDINATES_3D_ARRAY, const Math::Vector3DArray::SharedPointer&, 3DCoordinatesArray)
MAKE_ATOM_PROPERTY_FUNCTIONS(MORGAN_NUMBER, std::size_t, MorganNumber)
MAKE_ATOM_PROPERTY_FUNCTIONS(CANONICAL_NUMBER, std::size_t, CanonicalNumber)
MAKE_ATOM_PROPERTY_FUNCTIONS(CIP_PRIORITY, std::size_t, CIPPriority)
MAKE_ATOM_PROPERTY_FUNCTIONS(SYMMETRY_CLASS, std::size_t, SymmetryClass)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(STEREO_DESCRIPTOR, const Chem::StereoDescriptor&, StereoDescriptor)
MAKE_ATOM_PROPERTY_FUNCTIONS(STEREO_CENTER_FLAG, bool, StereoCenterFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS(CIP_CONFIGURATION, unsigned int, CIPConfiguration)
MAKE_ATOM_PROPERTY_FUNCTIONS(MDL_PARITY, unsigned int, MDLParity)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(MDL_DB_STEREO_CARE_FLAG, bool, MDLStereoCareFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(SYBYL_TYPE, unsigned int, SybylType)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(MOL2_CHARGE, double, MOL2Charge)
MAKE_ATOM_PROPERTY_FUNCTIONS(PEOE_CHARGE, double, PEOECharge)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(REACTION_CENTER_STATUS, unsigned int, ReactionCenterStatus)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(REACTION_ATOM_MAPPING_ID, std::size_t, ReactionAtomMappingID)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(MATCH_CONSTRAINTS, const Chem::MatchConstraintList::SharedPointer&, MatchConstraints)
MAKE_ATOM_PROPERTY_FUNCTIONS(MATCH_EXPRESSION, MatchExpressionPtr, MatchExpression)
MAKE_ATOM_PROPERTY_FUNCTIONS(MATCH_EXPRESSION_STRING, const std::string&, MatchExpressionString)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(COMPONENT_GROUP_ID, std::size_t, ComponentGroupID)
