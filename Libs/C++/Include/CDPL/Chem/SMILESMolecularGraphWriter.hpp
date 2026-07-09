/* 
 * SMILESMolecularGraphWriter.hpp 
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
 * \brief Definition of class CDPL::Chem::SMILESMolecularGraphWriter.
 */

#ifndef CDPL_CHEM_SMILESMOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_SMILESMOLECULARGRAPHWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class SMILESDataWriter;
        class MolecularGraph;

        /**
         * \brief Writer for molecular graph data in the <em>Daylight SMILES</em> [\ref SMILES] format.
         */
        class CDPL_CHEM_API SMILESMolecularGraphWriter : public Base::DataWriter<MolecularGraph>
        {

          public:
            /**
             * \brief Constructs a \c %SMILESMolecularGraphWriter instance that will write data of molecular graphs to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            SMILESMolecularGraphWriter(std::ostream& os);

            SMILESMolecularGraphWriter(const SMILESMolecularGraphWriter&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~SMILESMolecularGraphWriter();

            SMILESMolecularGraphWriter& operator=(const SMILESMolecularGraphWriter&) = delete;

            /**
             * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
             * \param molgraph The molecular graph to write.
             * \return A reference to itself.
             */
            Base::DataWriter<MolecularGraph>& write(const MolecularGraph& molgraph);

            /**
             * \brief Returns a pointer that is non-null while the writer is in a good state and \c nullptr after a failed write.
             * \return A non-null pointer in a good state, \c nullptr otherwise.
             */
                 operator const void*() const;

            /**
             * \brief Tells whether a previous write operation has failed.
             * \return \c true if the writer is in a failed state, and \c false otherwise.
             */
            bool operator!() const;

          private:
            typedef std::unique_ptr<SMILESDataWriter> SMILESDataWriterPtr;

            std::ostream&       output;
            bool                state;
            SMILESDataWriterPtr writer;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SMILESMOLECULARGRAPHWRITER_HPP
