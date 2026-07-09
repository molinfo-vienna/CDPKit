/* 
 * RDFReactionReader.hpp 
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
 * \brief Definition of class CDPL::Chem::RDFReactionReader.
 */

#ifndef CDPL_CHEM_RDFREACTIONREADER_HPP
#define CDPL_CHEM_RDFREACTIONREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MDLDataReader;
        class Reaction;

        /**
         * \brief Reader for reaction data in the <em>MDL RD-File</em> [\ref CTFILE] format.
         */
        class CDPL_CHEM_API RDFReactionReader : public Util::StreamDataReader<Reaction, RDFReactionReader>
        {

          public:
            /**
             * \brief Constructs a \c %RDFReactionReader instance that will read the reaction data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            RDFReactionReader(std::istream& is);

            RDFReactionReader(const RDFReactionReader&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~RDFReactionReader();

            RDFReactionReader& operator=(const RDFReactionReader&) = delete;

          private:
            friend class Util::StreamDataReader<Reaction, RDFReactionReader>;

            bool readData(std::istream&, Reaction&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<MDLDataReader> MDLDataReaderPtr;

            MDLDataReaderPtr reader;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RDFREACTIONREADER_HPP
