/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SizeAdjustments.hpp 
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

/**
 * \file
 * \brief Provides the contents of namespace CDPL::Vis::SizeAdjustment.
 */

#ifndef CDPL_VIS_SIZEADJUSTMENTS_HPP
#define CDPL_VIS_SIZEADJUSTMENTS_HPP


namespace CDPL 
{

	namespace Vis
	{
		
		/**
		 * \brief Provides constants that are used to specify the size adjustment policy for graphical objects within
		 *        a bounded rectangular area.
		 */
		namespace SizeAdjustment
		{

			/**
			 * \brief Specifies that the size of a graphical object shall be left unchanged.
			 */
			const unsigned int NONE        = 0;

			/**
			 * \brief Specifies that a graphical object shall be resized to achieve a maximum coverage of the available area.
			 */
			const unsigned int BEST_FIT    = 1;

			/**
			 * \brief Specifies that a graphical object shall only be resized if its bounds exceed the available area.
			 */
			const unsigned int IF_REQUIRED = 2;
		}
	}
}

#endif // CDPL_VIS_SIZEADJUSTMENTS_HPP
