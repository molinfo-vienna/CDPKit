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

#include "CDPL/ForceField/BondFunctions.hpp"
#include "CDPL/ForceField/BondProperty.hpp"
#include "CDPL/Chem/Bond.hpp"


using namespace CDPL; 


#define MAKE_BOND_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
	void ForceField::set##FUNC_SUFFIX(Chem::Bond& bond, TYPE arg)		\
	{																	\
		bond.setProperty(BondProperty::PROP_NAME, arg);					\
	}																	\
																		\
	bool ForceField::has##FUNC_SUFFIX(const Chem::Bond& bond)			\
	{																	\
		return bond.isPropertySet(BondProperty::PROP_NAME);				\
	}																	\
																		\
	void ForceField::clear##FUNC_SUFFIX(Chem::Bond& bond)				\
	{																	\
		bond.removeProperty(BondProperty::PROP_NAME);					\
	}

#define MAKE_BOND_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)		\
	TYPE ForceField::get##FUNC_SUFFIX(const Chem::Bond& bond)			\
	{																	\
		return bond.getProperty<TYPE>(BondProperty::PROP_NAME);			\
	}																	\
																		\
	MAKE_BOND_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_BOND_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
	TYPE ForceField::get##FUNC_SUFFIX(const Chem::Bond& bond)			\
	{																	\
		return bond.getPropertyOrDefault<TYPE>(BondProperty::PROP_NAME,	\
											   BondPropertyDefault::PROP_NAME); \
	}																	\
																		\
	MAKE_BOND_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_BOND_PROPERTY_FUNCTIONS(MMFF94_TYPE_INDEX, unsigned int, MMFF94TypeIndex)
