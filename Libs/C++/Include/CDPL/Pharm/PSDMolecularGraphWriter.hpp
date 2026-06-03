/* 
 * PSDMolecularGraphWriter.hpp 
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
 * \brief Definition of class CDPL::Pharm::PSDMolecularGraphWriter.
 */

#ifndef CDPL_PHARM_PSDMOLECULARGRAPHWRITER_HPP
#define CDPL_PHARM_PSDMOLECULARGRAPHWRITER_HPP

#include <string>
#include <iosfwd>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Pharm
    {

        /**
         * \brief Writer for molecular graph data in the PSD-format of the <em>CDPL</em>.
         */
        class CDPL_PHARM_API PSDMolecularGraphWriter : public Base::DataWriter<Chem::MolecularGraph>
        {

          public:
            /**
             * \brief Constructs a \c %PSDMolecularGraphWriter instance that will write the molecular graph data to the 
             *        output stream \a os.
             * \param os The output stream to write to.
             */
            PSDMolecularGraphWriter(std::ostream& os);

            /**
             * \brief Constructs a \c %PSDMolecularGraphWriter instance that will write the molecular graph data to the output
             *        file \a file_name.
             * \param file_name The output file to write to.
             */
            PSDMolecularGraphWriter(const std::string& file_name);

            /**
             * \brief Destructor.
             */
            ~PSDMolecularGraphWriter();

            /**
             * \brief Writes \a molgraph as the next record to the underlying PSD database.
             * \param molgraph The molecular graph to write.
             * \return A reference to itself.
             */
            PSDMolecularGraphWriter& write(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Closes the underlying PSD database and finalizes the output stream/file.
             */
            void close();

            /**
             * \brief Tells whether the writer is in a good (writable) state.
             * \return A non-\c nullptr pointer if the writer is in a good state, and \c nullptr otherwise.
             */
            operator const void*() const;

            /**
             * \brief Tells whether the writer is in a bad (non-writable) state.
             * \return \c true if the writer is in a bad state, and \c false otherwise.
             */
            bool operator!() const;

          private:
            PSDScreeningDBCreator creator;
            std::ostream*         output;
            std::streampos        outputPos;
            bool                  state;
            bool                  closed;
        };
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PSDMOLECULARGRAPHWRITER_HPP
