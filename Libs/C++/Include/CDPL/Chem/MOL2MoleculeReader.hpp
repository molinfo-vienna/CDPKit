/* 
 * MOL2MoleculeReader.hpp 
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
 * \brief Definition of the class CDPL::Chem::MOL2MoleculeReader.
 */

#ifndef CDPL_CHEM_MOL2MOLECULEREADER_HPP
#define CDPL_CHEM_MOL2MOLECULEREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MOL2DataReader;
        class Molecule;

        class CDPL_CHEM_API MOL2MoleculeReader : public Util::StreamDataReader<Molecule, MOL2MoleculeReader>
        {

          public:
            /**
             * \brief Constructs a \c %MOL2MoleculeReader instance that will read the molecule data from the input
             *        stream \a is.
             * \param is The input stream to read from.
             */
            MOL2MoleculeReader(std::istream& is);

            MOL2MoleculeReader(const MOL2MoleculeReader&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~MOL2MoleculeReader();

            MOL2MoleculeReader& operator=(const MOL2MoleculeReader&) = delete;

          private:
            friend class Util::StreamDataReader<Molecule, MOL2MoleculeReader>;

            bool readData(std::istream&, Molecule&, bool overwrite);
            bool skipData(std::istream&);
            bool moreData(std::istream&);

            typedef std::unique_ptr<MOL2DataReader> MOL2DataReaderPtr;

            MOL2DataReaderPtr reader;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOL2MOLECULEREADER_HPP
