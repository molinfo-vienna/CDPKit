/* 
 * RDFReactionWriter.hpp 
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
 * \brief Definition of class CDPL::Chem::RDFReactionWriter.
 */

#ifndef CDPL_CHEM_RDFREACTIONWRITER_HPP
#define CDPL_CHEM_RDFREACTIONWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MDLDataWriter;
        class Reaction;

        /**
         * \brief Writer for reaction data in the <em>MDL RD-File</em> [\ref CTFILE] format.
         */
        class CDPL_CHEM_API RDFReactionWriter : public Base::DataWriter<Reaction>
        {

          public:
            /**
             * \brief Constructs a \c %RDFReactionWriter instance that will write the reaction data to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            RDFReactionWriter(std::ostream& os);

            RDFReactionWriter(const RDFReactionWriter&) = delete;

            /**
             * \brief Destructor.
             */
            ~RDFReactionWriter();

            RDFReactionWriter& operator=(const RDFReactionWriter&) = delete;

            /**
             * \brief Writes the reaction \a rxn to the output stream specified in the constructor.
             * \param rxn The reaction to write.
             * \return A reference to itself.
             */
            Base::DataWriter<Reaction>& write(const Reaction& rxn);

            /**
             * \brief Returns a pointer that is non-null while the writer is in a good state and \c nullptr after a failed write.
             * \return A non-null pointer in a good state, \c nullptr otherwise.
             */
                 operator const void*() const;

            /**
             * \brief Tells whether a previous write operation has failed.
             * \return \c true if the writer is in a failed state, and \c false otherwise.
             */
            bool operator!() const;

          private:
            typedef std::unique_ptr<MDLDataWriter> MDLDataWriterPtr;

            std::ostream&    output;
            bool             state;
            MDLDataWriterPtr writer;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RDFREACTIONWRITER_HPP
