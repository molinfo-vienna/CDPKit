/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomColorTable.hpp 
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

/**
 * \file
 * \brief Provides the contents of namespace CDPL::Vis::AtomColorTable.
 */

#ifndef CDPL_VIS_ATOMCOLORTABLE_HPP
#define CDPL_VIS_ATOMCOLORTABLE_HPP

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/ColorTable.hpp"


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \brief Provides preinitialized color tables for the visualization of atomic properties.
		 */
		namespace AtomColorTable
		{

			/**
			 * \brief Provides colors for frequently occurring chemical elements.
			 *
			 * The table is used for the element dependent coloring of atom labels in 2D depictions 
			 * of chemical structures. Currently, colors for the following elements are provided:
			 * <em>C, H, N, O, S, P, F, Cl, Br, I, Li, Na, B, Fe, Ba, Mg, Zn, Cu, Ni, Ca, Mn, Al, Ti,
			 * Cr, Ag, Si, Au</em> and <em>He</em>.
			 */
			extern CDPL_VIS_API const ColorTable ELEMENT_COLORS_2D;
		}
	}
}

#endif // CDPL_VIS_ATOMCOLORTABLE_HPP
