/* 
 * CDFDRegularGridSetWriter.hpp 
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
 * \brief Definition of class CDPL::Grid::CDFDRegularGridSetWriter.
 */

#ifndef CDPL_GRID_CDFDREGULARGRIDSETWRITER_HPP
#define CDPL_GRID_CDFDREGULARGRIDSETWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Grid/APIPrefix.hpp"
#include "CDPL/Grid/RegularGridSet.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Grid
    {

        class CDFRegularGridSetDataWriter;

        /**
         * \brief A writer for spatial regular grid set data in the native I/O format of the <em>CDPL</em>.
         */
        class CDPL_GRID_API CDFDRegularGridSetWriter : public Base::DataWriter<DRegularGridSet>
        {

          public:
            /**
             * \brief Constructs a \c %CDFDRegularGridSetWriter instance that will write data of spatial regular grids to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            CDFDRegularGridSetWriter(std::ostream& os);

            CDFDRegularGridSetWriter(const CDFDRegularGridSetWriter&) = delete;

            /**
             * \brief Destructor.
             */
            ~CDFDRegularGridSetWriter();

            CDFDRegularGridSetWriter& operator=(const CDFDRegularGridSetWriter&) = delete;

            /**
             * \brief Writes data of the spatial regular grid set \a grid_set to the output stream specified in the constructor.
             * \param grid_set The spatial regular grid set to write.
             * \return A reference to itself.
             */
            Base::DataWriter<DRegularGridSet>& write(const DRegularGridSet& grid_set);

            operator const void*() const;
            bool operator!() const;

          private:
            typedef std::unique_ptr<CDFRegularGridSetDataWriter> CDFDataWriterPtr;

            std::ostream&    output;
            bool             state;
            CDFDataWriterPtr writer;
        };
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_CDFDREGULARGRIDSETWRITER_HPP
