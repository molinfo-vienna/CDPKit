/* 
 * MMTFMoleculeReader.hpp 
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
 * \brief Definition of the class CDPL::Biomol::MMTFMoleculeReader.
 */

#ifndef CDPL_BIOMOL_MMTFMOLECULEREADER_HPP
#define CDPL_BIOMOL_MMTFMOLECULEREADER_HPP

#include <memory>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }

    namespace Biomol
    {

        class MMTFDataReader;

        /**
         * \brief A reader for molecule data in the <em>Macromolecular Transmission Format (MMTF)</em>
         *        [\ref MMTF].
         */
        class CDPL_BIOMOL_API MMTFMoleculeReader : public Util::StreamDataReader<Chem::Molecule, MMTFMoleculeReader>
        {

          public:
            /**
             * \brief Constructs a \c %MMTFMoleculeReader instance that will read molecule data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            MMTFMoleculeReader(std::istream& is);

            /**
             * \brief Destructor.
             */
            ~MMTFMoleculeReader();

          private:
            friend class Util::StreamDataReader<Chem::Molecule, MMTFMoleculeReader>;

            MMTFMoleculeReader(const MMTFMoleculeReader&);

            MMTFMoleculeReader& operator=(const MMTFMoleculeReader&);

            bool readData(std::istream&, Chem::Molecule&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::auto_ptr<MMTFDataReader> MMTFDataReaderPtr;

            MMTFDataReaderPtr reader;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMTFMOLECULEREADER_HPP
