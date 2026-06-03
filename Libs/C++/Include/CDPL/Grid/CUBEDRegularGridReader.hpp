/* 
 * CUBEDRegularGridReader.hpp 
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
 * \brief Definition of class CDPL::Grid::CUBEDRegularGridReader.
 */

#ifndef CDPL_GRID_CUBEDREGULARGRIDREADER_HPP
#define CDPL_GRID_CUBEDREGULARGRIDREADER_HPP

#include <memory>

#include "CDPL/Grid/APIPrefix.hpp"
#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Grid
    {

        class CUBEDataReader;

        /**
         * \brief Reader for regular spatial grid data in the <em>Gaussian CUBE</em> [\ref CUBE] format.
         * \since 1.4
         */
        class CDPL_GRID_API CUBEDRegularGridReader : public Util::StreamDataReader<DRegularGrid, CUBEDRegularGridReader>
        {

          public:
            /**
             * \brief Constructs a \c %CUBEDRegularGridReader instance that will read the regular spatial grid data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            CUBEDRegularGridReader(std::istream& is);

            CUBEDRegularGridReader(const CUBEDRegularGridReader&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~CUBEDRegularGridReader();

            CUBEDRegularGridReader& operator=(const CUBEDRegularGridReader&) = delete;

          private:
            friend class Util::StreamDataReader<DRegularGrid, CUBEDRegularGridReader>;

            bool readData(std::istream&, DRegularGrid&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<CUBEDataReader> CUBEDataReaderPtr;

            CUBEDataReaderPtr reader;
        };
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_CUBEDREGULARGRIDREADER_HPP
