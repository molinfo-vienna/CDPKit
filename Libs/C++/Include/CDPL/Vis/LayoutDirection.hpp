/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LayoutDirection.hpp 
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
 * \brief Definition of constants in namespace CDPL::Vis::LayoutDirection.
 */

#ifndef CDPL_VIS_LAYOUTDIRECTION_HPP
#define CDPL_VIS_LAYOUTDIRECTION_HPP


namespace CDPL 
{

	namespace Vis
	{

		/**
		 * \addtogroup CDPL_VIS_CONSTANTS
		 * @{
		 */

		/**
		 * \brief Provides constants that are used to specify the main direction of object layouts.
		 */
		namespace LayoutDirection
		{

			/**
			 * \brief Specifies a horizontal layout (parallel to the x-axis).
			 */
			const unsigned int HORIZONTAL = 0;

			/**
			 * \brief Specifies a vertical layout (parallel to the y-axis).
			 */
			const unsigned int VERTICAL   = 1;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_VIS_LAYOUTDIRECTION_HPP
