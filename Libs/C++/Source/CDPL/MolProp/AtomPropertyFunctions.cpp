/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyFunctions.cpp 
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

#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/MolProp/AtomProperty.hpp"
#include "CDPL/MolProp/AtomPropertyDefault.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


#define MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
	void MolProp::set##FUNC_SUFFIX(Chem::Atom& atom, TYPE arg)			\
	{																	\
		atom.setProperty(AtomProperty::PROP_NAME, arg);					\
	}																	\
																		\
	bool MolProp::has##FUNC_SUFFIX(const Chem::Atom& atom)				\
	{																	\
		return atom.isPropertySet(AtomProperty::PROP_NAME);				\
	}																	\
																		\
	void MolProp::clear##FUNC_SUFFIX(Chem::Atom& atom)					\
	{																	\
		atom.removeProperty(AtomProperty::PROP_NAME);					\
	}

#define MAKE_ATOM_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)		\
	TYPE MolProp::get##FUNC_SUFFIX(const Chem::Atom& atom)				\
	{																	\
		return atom.getProperty<TYPE>(AtomProperty::PROP_NAME);			\
	}																	\
																		\
	MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
	TYPE MolProp::get##FUNC_SUFFIX(const Chem::Atom& atom)				\
	{																	\
		return atom.getPropertyOrDefault<TYPE>(AtomProperty::PROP_NAME,	\
											   AtomPropertyDefault::PROP_NAME); \
	}																	\
																		\
	MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_ATOM_PROPERTY_FUNCTIONS(HYDROPHOBICITY, double, Hydrophobicity) 
MAKE_ATOM_PROPERTY_FUNCTIONS(PEOE_SIGMA_CHARGE, double, PEOESigmaCharge)
MAKE_ATOM_PROPERTY_FUNCTIONS(PEOE_SIGMA_ELECTRONEGATIVITY, double, PEOESigmaElectronegativity)
MAKE_ATOM_PROPERTY_FUNCTIONS(MHMO_PI_CHARGE, double, MHMOPiCharge)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(H_BOND_DONOR_TYPE, unsigned int, HBondDonorType)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(H_BOND_ACCEPTOR_TYPE, unsigned int, HBondAcceptorType)
