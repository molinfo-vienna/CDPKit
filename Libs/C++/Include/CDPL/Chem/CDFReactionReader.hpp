/* 
 * CDFReactionReader.hpp 
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
 * \brief Definition of the class CDPL::Chem::CDFReactionReader.
 */

#ifndef CDPL_CHEM_CDFREACTIONREADER_HPP
#define CDPL_CHEM_CDFREACTIONREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Chem
    {

        class CDFDataReader;
        class Reaction;

        /**
         * \brief A reader for reaction data in the native I/O format of the <em>CDPL</em>.
         */
        class CDPL_CHEM_API CDFReactionReader : public Util::StreamDataReader<Reaction, CDFReactionReader>
        {

          public:
            /**
             * \brief Constructs a \c %CDFReactionReader instance that will read the reaction data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            CDFReactionReader(std::istream& is);

            /**
             * \brief Destructor.
             */
            ~CDFReactionReader();

          private:
            friend class Util::StreamDataReader<Reaction, CDFReactionReader>;

            CDFReactionReader(const CDFReactionReader&);

            CDFReactionReader& operator=(const CDFReactionReader&);

            bool readData(std::istream&, Reaction&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<CDFDataReader> CDFDataReaderPtr;

            CDFDataReaderPtr reader;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CDFREACTIONREADER_HPP
