/* 
 * SMILESReactionReader.hpp 
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
 * \brief Definition of class CDPL::Chem::SMILESReactionReader.
 */

#ifndef CDPL_CHEM_SMILESREACTIONREADER_HPP
#define CDPL_CHEM_SMILESREACTIONREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Chem
    {

        class SMILESDataReader;
        class Reaction;

        /**
         * \brief A reader for reaction data in the <em>Daylight SMILES</em> [\ref SMILES] format.
         *
         * \c %SMILESReactionReader supports the following control-parameters:
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
         *   <td>Chem::ControlParameter::SMILES_RECORD_FORMAT</td>
         *   <td align="center">\c "S"</td>
         *   <td>Specifies the data record format</td>
         *  </tr>
         * </table>
         */
        class CDPL_CHEM_API SMILESReactionReader : public Util::StreamDataReader<Reaction, SMILESReactionReader>
        {

          public:
            /**
             * \brief Constructs a \c %SMILESReactionReader instance that will read the reaction data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            SMILESReactionReader(std::istream& is);

            SMILESReactionReader(const SMILESReactionReader&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~SMILESReactionReader();

            SMILESReactionReader& operator=(const SMILESReactionReader&) = delete;

          private:
            friend class Util::StreamDataReader<Reaction, SMILESReactionReader>;

            bool readData(std::istream&, Reaction&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<SMILESDataReader> SMILESDataReaderPtr;

            SMILESDataReaderPtr reader;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SMILESREACTIONREADER_HPP
