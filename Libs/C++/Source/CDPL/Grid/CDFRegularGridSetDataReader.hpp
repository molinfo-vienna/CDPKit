/* 
 * CDFRegularGridSetDataReader.hpp 
 *
 * This file is part of the Gridical Data Processing Toolkit
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


#ifndef CDPL_GRID_CDFREGULARGRIDSETDATAREADER_HPP
#define CDPL_GRID_CDFREGULARGRIDSETDATAREADER_HPP

#include "CDPL/Grid/RegularGridSet.hpp"

#include "CDFRegularGridDataReader.hpp"


namespace CDPL 
{

	namespace Grid
	{

		class CDFRegularGridSetDataReader : private CDFRegularGridDataReader
		{

		public:
			CDFRegularGridSetDataReader(const Base::ControlParameterContainer& ctrl_params): 
				CDFRegularGridDataReader(ctrl_params) {}

			bool readGridSet(std::istream& is, DRegularGridSet& grid_set);

			bool readGridSet(DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf);

			bool skipGridSet(std::istream& is);

			bool hasMoreData(std::istream& is);

		private:
			bool doReadGridSet(DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf) const;
		};
	}
}

#endif // CDPL_GRID_CDFREGULARGRIDSETDATAREADER_HPP
