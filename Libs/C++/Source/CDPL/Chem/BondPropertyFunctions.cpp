/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondPropertyFunctions.cpp 
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

#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/BondProperty.hpp"
#include "CDPL/Chem/BondPropertyDefault.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


using namespace CDPL; 


#define MAKE_BOND_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
	void Chem::set##FUNC_SUFFIX(Chem::Bond& bond, TYPE arg)				\
	{																	\
		bond.setProperty(BondProperty::PROP_NAME, arg);					\
	}																	\
																		\
	bool Chem::has##FUNC_SUFFIX(const Chem::Bond& bond)					\
	{																	\
		return bond.isPropertySet(BondProperty::PROP_NAME);				\
	}																	\
																		\
	void Chem::clear##FUNC_SUFFIX(Chem::Bond& bond)						\
	{																	\
		bond.removeProperty(BondProperty::PROP_NAME);					\
	}

#define MAKE_BOND_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)		\
	TYPE Chem::get##FUNC_SUFFIX(const Chem::Bond& bond)					\
	{																	\
		return bond.getProperty<TYPE>(BondProperty::PROP_NAME);			\
	}																	\
																		\
	MAKE_BOND_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
	TYPE Chem::get##FUNC_SUFFIX(const Chem::Bond& bond)					\
	{																	\
		return bond.getPropertyOrDefault<TYPE>(BondProperty::PROP_NAME,	\
											   BondPropertyDefault::PROP_NAME); \
	}																	\
																		\
	MAKE_BOND_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


typedef const Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer& MatchExpressionPtr;


MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(ORDER, std::size_t, Order)
MAKE_BOND_PROPERTY_FUNCTIONS(RING_FLAG, bool, RingFlag)
MAKE_BOND_PROPERTY_FUNCTIONS(AROMATICITY_FLAG, bool, AromaticityFlag)
MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(STEREO_DESCRIPTOR, const Chem::StereoDescriptor&, StereoDescriptor)
MAKE_BOND_PROPERTY_FUNCTIONS(STEREO_CENTER_FLAG, bool, StereoCenterFlag)
MAKE_BOND_PROPERTY_FUNCTIONS(CIP_CONFIGURATION, unsigned int, CIPConfiguration)
MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(DIRECTION, unsigned int, Direction)
MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(SYBYL_TYPE, unsigned int, SybylType)
MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(STEREO_2D_FLAG, unsigned int, 2DStereoFlag)
MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(REACTION_CENTER_STATUS, unsigned int, ReactionCenterStatus)
MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(MATCH_CONSTRAINTS, const Chem::MatchConstraintList::SharedPointer&, MatchConstraints)
MAKE_BOND_PROPERTY_FUNCTIONS(MATCH_EXPRESSION, MatchExpressionPtr, MatchExpression)
MAKE_BOND_PROPERTY_FUNCTIONS(MATCH_EXPRESSION_STRING, const std::string&, MatchExpressionString)
