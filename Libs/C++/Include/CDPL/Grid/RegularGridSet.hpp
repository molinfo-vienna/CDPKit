/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RegularGridSet.hpp 
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
 * \brief Definition of the class CDPL::Grid::RegularGridSet.
 */

#ifndef CDPL_GRID_REGULARGRIDSET_HPP
#define CDPL_GRID_REGULARGRIDSET_HPP

#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Util/IndirectArray.hpp"


namespace CDPL 
{

    namespace Grid
    {

		/**
		 * \brief RegularGridSet.
		 */
		template <typename T, typename CVT = T>
		class RegularGridSet : public Util::IndirectArray<RegularGrid<T, CVT> >
		{

		  public:
			typedef boost::shared_ptr<RegularGridSet> SharedPointer;

		  private:
			const char* getClassName() const {
				return "RegularGridSet";
			}
		};

		typedef RegularGridSet<double> DRegularGridSet;
		typedef RegularGridSet<float> FRegularGridSet;
    }
}

#endif // CDPL_GRID_REGULARGRIDSET_HPP
