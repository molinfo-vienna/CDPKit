/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDRegularGridSetReader.hpp 
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
 * \brief Definition of the class CDPL::Grid::CDFDRegularGridSetReader.
 */

#ifndef CDPL_GRID_CDFDREGULARGRIDSETREADER_HPP
#define CDPL_GRID_CDFDREGULARGRIDSETREADER_HPP

#include <memory>

#include "CDPL/Grid/APIPrefix.hpp"
#include "CDPL/Grid/RegularGridSet.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL 
{

	namespace Grid
	{

		class CDFRegularGridSetDataReader;

		/**
		 * \addtogroup CDPL_GRID_CDF_IO
		 * @{
		 */

		/**
		 * \brief A reader for spatial regular grid set data in the native I/O format of the <em>CDPL</em>.
		 */
		class CDPL_GRID_API CDFDRegularGridSetReader : public Util::StreamDataReader<DRegularGridSet, CDFDRegularGridSetReader>
		{

		public:
			/**
			 * \brief Constructs a \c %CDFDRegularGridSetReader instance that will read the pharmacophore data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			CDFDRegularGridSetReader(std::istream& is);

			/**
			 * \brief Destructor.
			 */
			~CDFDRegularGridSetReader();

		private:
			friend class Util::StreamDataReader<DRegularGridSet, CDFDRegularGridSetReader>;

			CDFDRegularGridSetReader(const CDFDRegularGridSetReader&);

			CDFDRegularGridSetReader& operator=(const CDFDRegularGridSetReader&);

			bool readData(std::istream&, DRegularGridSet&, bool overwrite);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			typedef std::auto_ptr<CDFRegularGridSetDataReader> CDFDataReaderPtr;

			CDFDataReaderPtr reader;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_GRID_CDFDREGULARGRIDSETREADER_HPP
