/* 
 * PSDMoleculeInputHandler.hpp 
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
 * \brief Definition of class CDPL::Pharm::PSDMoleculeInputHandler.
 */

#ifndef CDPL_PHARM_PSDMOLECULEINPUTHANDLER_HPP
#define CDPL_PHARM_PSDMOLECULEINPUTHANDLER_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Base/DataInputHandler.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;
    }

    namespace Pharm
    {

        /**
         * \brief Handler for the input of molecule data in the PSD-format of the <em>CDPL</em>.
         */
        class CDPL_PHARM_API PSDMoleculeInputHandler : public Base::DataInputHandler<Chem::Molecule>
        {

          public:
            /**
             * \brief Returns the data format advertised by this handler (Pharm::DataFormat::PSD).
             * \return A \c const reference to the PSD Base::DataFormat instance.
             */
            const Base::DataFormat& getDataFormat() const;

            /**
             * \brief Creates a Pharm::PSDMoleculeReader that reads from the input stream \a is.
             * \param is The input stream to read from.
             * \return A shared pointer to the constructed reader.
             */
            ReaderType::SharedPointer createReader(std::istream& is) const;

            /**
             * \brief Creates a Pharm::PSDMoleculeReader that reads from the file \a file_name.
             * \param file_name The input file to read from.
             * \param mode The open mode of the underlying file stream.
             * \return A shared pointer to the constructed reader.
             */
            ReaderType::SharedPointer createReader(const std::string& file_name, std::ios_base::openmode mode) const;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDMOLECULEINPUTHANDLER_HPP
