/* 
 * CDFReactionWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::CDFReactionWriter.
 */

#ifndef CDPL_CHEM_CDFREACTIONWRITER_HPP
#define CDPL_CHEM_CDFREACTIONWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

    namespace Chem
    {

        class CDFDataWriter;
        class Reaction;

        /**
         * \brief A writer for molecular graph data in the native I/O format of the <em>CDPL</em>.
         */
        class CDPL_CHEM_API CDFReactionWriter : public Base::DataWriter<Reaction>
        {

        public:
            /**
             * \brief Constructs a \c %CDFReactionWriter instance that will write reaction data  to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            CDFReactionWriter(std::ostream& os);

            /**
             * \brief Destructor.
             */
            ~CDFReactionWriter();

            /**
             * \brief Writes the reaction \a rxn to the output stream specified in the constructor.
             * \param rxn The reaction data to write.
             * \return A reference to itself.
             */
            Base::DataWriter<Reaction>& write(const Reaction& rxn);

            operator const void*() const;
            bool operator!() const;

        private:
            typedef std::auto_ptr<CDFDataWriter> CDFDataWriterPtr;

            CDFReactionWriter(const CDFReactionWriter&);

            CDFReactionWriter& operator=(const CDFReactionWriter&);

            std::ostream&    output;
            bool             state;
            CDFDataWriterPtr writer;
        };
    }
}

#endif // CDPL_CHEM_CDFREACTIONWRITER_HPP
