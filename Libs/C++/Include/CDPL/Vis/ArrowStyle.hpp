/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ArrowStyle.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::ArrowStyle.
 */

#ifndef CDPL_VIS_ARROWSTYLE_HPP
#define CDPL_VIS_ARROWSTYLE_HPP


namespace CDPL 
{

	namespace Vis
	{
	
		/**
		 * \brief Provides constants for the specification of reaction arrow styles in 2D depictions of
		 *        chemical reactions.
		 */
		namespace ArrowStyle
		{

			/**
			 * \brief Specifies that no reaction arrow shall be drawn.
			 */
			const unsigned int NONE            = 0;

			/**
			 * \brief Specifies a solid reaction arrow (interior will be filled).
			 */
			const unsigned int REACTION_SOLID  = 1;
			
			/**
			 * \brief Specifies a hollow reaction arrow (interior will be not filled).
			 */
			const unsigned int REACTION_HOLLOW = 2;
		}
	}
}

#endif // CDPL_VIS_ARROWSTYLE_HPP
