/* 
 * SMILESMoleculeReader.hpp 
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
 * \brief Definition of the class CDPL::Chem::SMILESMoleculeReader.
 */

#ifndef CDPL_CHEM_SMILESMOLECULEREADER_HPP
#define CDPL_CHEM_SMILESMOLECULEREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Chem
    {

        class SMILESDataReader;
        class Molecule;

        /**
         * \brief A reader for molecule data in the <em>Daylight SMILES</em> [\ref SMILES] format.
         *
         * \c %SMILESMoleculeReader supports the following control-parameters:
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
        class CDPL_CHEM_API SMILESMoleculeReader : public Util::StreamDataReader<Molecule, SMILESMoleculeReader>
        {

          public:
            /**
             * \brief Constructs a \c %SMILESMoleculeReader instance that will read the molecule data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            SMILESMoleculeReader(std::istream& is);

            SMILESMoleculeReader(const SMILESMoleculeReader&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~SMILESMoleculeReader();

            SMILESMoleculeReader& operator=(const SMILESMoleculeReader&) = delete;

          private:
            friend class Util::StreamDataReader<Molecule, SMILESMoleculeReader>;

            bool readData(std::istream&, Molecule&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<SMILESDataReader> SMILESDataReaderPtr;

            SMILESDataReaderPtr reader;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SMILESMOLECULEREADER_HPP
