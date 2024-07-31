/* 
 * MMCIFMoleculeReader.hpp 
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
 * \brief Definition of the class CDPL::Biomol::MMCIFMoleculeReader.
 */

#ifndef CDPL_BIOMOL_MMCIFMOLECULEREADER_HPP
#define CDPL_BIOMOL_MMCIFMOLECULEREADER_HPP

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

        class MMCIFDataReader;

        /**
         * \since 1.2
         */
        class CDPL_BIOMOL_API MMCIFMoleculeReader : public Util::StreamDataReader<Chem::Molecule, MMCIFMoleculeReader>
        {

          public:
            /**
             * \brief Constructs a \c %MMCIFMoleculeReader instance that will read the molecule data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            MMCIFMoleculeReader(std::istream& is);

            /**
             * \brief Destructor.
             */
            ~MMCIFMoleculeReader();

          private:
            friend class Util::StreamDataReader<Chem::Molecule, MMCIFMoleculeReader>;

            MMCIFMoleculeReader(const MMCIFMoleculeReader&);

            MMCIFMoleculeReader& operator=(const MMCIFMoleculeReader&);

            bool readData(std::istream&, Chem::Molecule&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<MMCIFDataReader> MMCIFDataReaderPtr;

            MMCIFDataReaderPtr reader;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFMOLECULEREADER_HPP
