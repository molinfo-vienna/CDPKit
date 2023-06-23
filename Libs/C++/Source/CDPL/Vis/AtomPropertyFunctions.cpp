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

#include "CDPL/Vis/AtomFunctions.hpp"
#include "CDPL/Vis/AtomProperty.hpp"
#include "CDPL/Vis/AtomPropertyDefault.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


#define MAKE_ATOM_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)		\
	TYPE Vis::get##FUNC_SUFFIX(const Chem::Atom& atom)					\
	{																	\
		return atom.getPropertyOrDefault<TYPE>(AtomProperty::PROP_NAME,	\
											   AtomPropertyDefault::PROP_NAME);	\
	}																	\
																		\
	void Vis::set##FUNC_SUFFIX(Chem::Atom& atom, TYPE arg)				\
	{																	\
		atom.setProperty(AtomProperty::PROP_NAME, arg);					\
	}																	\
																		\
	bool Vis::has##FUNC_SUFFIX(const Chem::Atom& atom)					\
	{																	\
		return atom.isPropertySet(AtomProperty::PROP_NAME);				\
	}																	\
																		\
	void Vis::clear##FUNC_SUFFIX(Chem::Atom& atom)						\
	{																	\
		atom.removeProperty(AtomProperty::PROP_NAME);					\
	}


MAKE_ATOM_PROPERTY_FUNCTIONS(COLOR, const Vis::Color&, Color)
MAKE_ATOM_PROPERTY_FUNCTIONS(LABEL_FONT, const Vis::Font&, LabelFont)
MAKE_ATOM_PROPERTY_FUNCTIONS(LABEL_SIZE, const Vis::SizeSpecification&, LabelSize)
MAKE_ATOM_PROPERTY_FUNCTIONS(SECONDARY_LABEL_FONT, const Vis::Font&, SecondaryLabelFont)
MAKE_ATOM_PROPERTY_FUNCTIONS(SECONDARY_LABEL_SIZE, const Vis::SizeSpecification&, SecondaryLabelSize)
MAKE_ATOM_PROPERTY_FUNCTIONS(LABEL_MARGIN, const Vis::SizeSpecification&, LabelMargin)
MAKE_ATOM_PROPERTY_FUNCTIONS(RADICAL_ELECTRON_DOT_SIZE, const Vis::SizeSpecification&, RadicalElectronDotSize)
