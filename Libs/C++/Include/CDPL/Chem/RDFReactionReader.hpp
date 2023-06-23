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
 * \brief Definition of the class CDPL::Chem::RDFReactionReader.
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
         * \brief A reader for reaction data in the <em>MDL RD-File</em> [\ref CTFILE] format.
         *
         * \c %RDFReactionReader supports the following control-parameters:
         *
         * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
         *   <td align="center">\c false</td>
         *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::MDL_IGNORE_PARITY</td>
         *   <td align="center">\c false</td>
         *   <td>Specifies whether the stereo parity of atoms shall be ignored</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::MDL_TRIM_STRINGS</td>
         *   <td align="center">\c true</td>
         *   <td>Specifies whether to remove leading and trailing whitespace from string values</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::MDL_TRIM_LINES</td>
         *   <td align="center">\c false</td>
         *   <td>Specifies whether to remove leading and trailing whitespace from data lines</td>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::MDL_IGNORE_LINE_LENGTH_LIMIT</td>
         *   <td align="center">\c true</td>
         *   <td>Specifies whether to check if data lines exceed the maximum allowed line length</td>
         *  </tr>
         * </table>
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

            /**
             * \brief Destructor.
             */
            ~RDFReactionReader();

        private:
            friend class Util::StreamDataReader<Reaction, RDFReactionReader>;

            RDFReactionReader(const RDFReactionReader&);

            RDFReactionReader& operator=(const RDFReactionReader&);

            bool readData(std::istream&, Reaction&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::auto_ptr<MDLDataReader> MDLDataReaderPtr;

            MDLDataReaderPtr reader;
        };
    }
}

#endif // CDPL_CHEM_RDFREACTIONREADER_HPP
