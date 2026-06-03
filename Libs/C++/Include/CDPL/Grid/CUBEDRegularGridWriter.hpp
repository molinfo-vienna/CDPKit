/* 
 * CUBEDRegularGridWriter.hpp 
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
 * \brief Definition of class CDPL::Grid::CUBEDRegularGridWriter.
 */

#ifndef CDPL_GRID_CUBEDREGULARGRIDWRITER_HPP
#define CDPL_GRID_CUBEDREGULARGRIDWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Grid/APIPrefix.hpp"
#include "CDPL/Grid/RegularGrid.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Grid
    {

        class CUBEDataWriter;

        /**
         * \brief Writer for regular spatial grid data in the <em>Gaussian CUBE</em> [\ref CUBE] format.
         * \since 1.4
         */
        class CDPL_GRID_API CUBEDRegularGridWriter : public Base::DataWriter<DRegularGrid>
        {

          public:
            /**
             * \brief Constructs a \c %CUBEDRegularGridWriter instance that will write data of regular spatial grids to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            CUBEDRegularGridWriter(std::ostream& os);

            CUBEDRegularGridWriter(const CUBEDRegularGridWriter&) = delete;

            /**
             * \brief Destructor.
             */
            ~CUBEDRegularGridWriter();

            CUBEDRegularGridWriter& operator=(const CUBEDRegularGridWriter&) = delete;

            /**
             * \brief Writes data of the regular spatial grid \a grid to the output stream specified in the constructor.
             * \param grid The regular spatial grid to write.
             * \return A reference to itself.
             */
            Base::DataWriter<DRegularGrid>& write(const DRegularGrid& grid);

            /**
             * \brief Tells whether the writer is in a good (writable) state.
             * \return A non-\c nullptr pointer if the writer is in a good state, and \c nullptr otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether the writer is in a bad (non-writable) state.
             * \return \c true if the writer is in a bad state, and \c false otherwise.
             */
            bool operator!() const;

          private:
            typedef std::unique_ptr<CUBEDataWriter> CUBEDataWriterPtr;

            std::ostream&     output;
            bool              state;
            CUBEDataWriterPtr writer;
        };
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_CUBEDREGULARGRIDWRITER_HPP
