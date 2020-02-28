/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AttributedGridPropertyFunctions.cpp 
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

#include "CDPL/Grid/AttributedGridFunctions.hpp"
#include "CDPL/Grid/AttributedGridProperty.hpp"
#include "CDPL/Grid/AttributedGridPropertyDefault.hpp"
#include "CDPL/Grid/AttributedGrid.hpp"


using namespace CDPL; 


#define MAKE_ATTRGRID_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
	void Grid::set##FUNC_SUFFIX(Grid::AttributedGrid& grid, TYPE arg)	\
	{																	\
		grid.setProperty(AttributedGridProperty::PROP_NAME, arg);		\
	}																	\
																		\
	bool Grid::has##FUNC_SUFFIX(const Grid::AttributedGrid& grid)		\
	{																	\
		return grid.isPropertySet(AttributedGridProperty::PROP_NAME);	\
	}																	\
																		\
	void Grid::clear##FUNC_SUFFIX(Grid::AttributedGrid& grid)			\
	{																	\
		grid.removeProperty(AttributedGridProperty::PROP_NAME);			\
	}

#define MAKE_ATTRGRID_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)	\
	TYPE Grid::get##FUNC_SUFFIX(const Grid::AttributedGrid& grid)		\
	{																	\
		return grid.getProperty<TYPE>(AttributedGridProperty::PROP_NAME); \
	}																	\
																		\
	MAKE_ATTRGRID_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_ATTRGRID_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX) \
	TYPE Grid::get##FUNC_SUFFIX(const Grid::AttributedGrid& grid)		\
	{																	\
		return grid.getPropertyOrDefault<TYPE>(AttributedGridProperty::PROP_NAME, \
											   AttributedGridPropertyDefault::PROP_NAME); \
	}																	\
																		\
	MAKE_ATTRGRID_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_ATTRGRID_PROPERTY_FUNCTIONS_WITH_DEF(NAME, const std::string&, Name)
