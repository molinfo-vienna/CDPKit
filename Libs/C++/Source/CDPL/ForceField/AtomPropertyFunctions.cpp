/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyFunctions.cpp 
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

#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/AtomProperty.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


#define MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
	void ForceField::set##FUNC_SUFFIX(Chem::Atom& atom, TYPE arg)		\
	{																	\
		atom.setProperty(AtomProperty::PROP_NAME, arg);					\
	}																	\
																		\
	bool ForceField::has##FUNC_SUFFIX(const Chem::Atom& atom)			\
	{																	\
		return atom.isPropertySet(AtomProperty::PROP_NAME);				\
	}																	\
																		\
	void ForceField::clear##FUNC_SUFFIX(Chem::Atom& atom)				\
	{																	\
		atom.removeProperty(AtomProperty::PROP_NAME);					\
	}

#define MAKE_ATOM_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)		\
	TYPE ForceField::get##FUNC_SUFFIX(const Chem::Atom& atom)			\
	{																	\
		return atom.getProperty<TYPE>(AtomProperty::PROP_NAME);			\
	}																	\
																		\
	MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
	TYPE ForceField::get##FUNC_SUFFIX(const Chem::Atom& atom)			\
	{																	\
		return atom.getPropertyOrDefault<TYPE>(AtomProperty::PROP_NAME,	\
											   AtomPropertyDefault::PROP_NAME); \
	}																	\
																		\
	MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_ATOM_PROPERTY_FUNCTIONS(MMFF94_SYMBOLIC_TYPE, const std::string&, MMFF94SymbolicType)
MAKE_ATOM_PROPERTY_FUNCTIONS(MMFF94_NUMERIC_TYPE, unsigned int, MMFF94NumericType)
MAKE_ATOM_PROPERTY_FUNCTIONS(MMFF94_CHARGE, double, MMFF94Charge)
