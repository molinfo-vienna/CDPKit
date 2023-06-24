/* 
 * MMTFMolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Biomol::MMTFMolecularGraphWriter.
 */

#ifndef CDPL_BIOMOL_MMTFMOLECULARGRAPHWRITER_HPP
#define CDPL_BIOMOL_MMTFMOLECULARGRAPHWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Biomol/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }

    namespace Biomol
    {

        class MMTFDataWriter;

        /**
         * \brief A writer for molecular graph data in the <em>Macromolecular Transmission Format (MMTF)</em> [\ref MMTF].
         */
        class CDPL_BIOMOL_API MMTFMolecularGraphWriter : public Base::DataWriter<Chem::MolecularGraph>
        {

          public:
            /**
             * \brief Constructs a \c %MMTFMolecularGraphWriter instance that will write data of molecular graphs to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            MMTFMolecularGraphWriter(std::ostream& os);

            /**
             * \brief Destructor.
             */
            ~MMTFMolecularGraphWriter();

            /**
             * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
             * \param molgraph The molecular graph to write.
             * \return A reference to itself.
             */
            Base::DataWriter<Chem::MolecularGraph>& write(const Chem::MolecularGraph& molgraph);

                 operator const void*() const;
            bool operator!() const;

          private:
            typedef std::auto_ptr<MMTFDataWriter> MMTFDataWriterPtr;

            MMTFMolecularGraphWriter(const MMTFMolecularGraphWriter&);

            MMTFMolecularGraphWriter& operator=(const MMTFMolecularGraphWriter&);

            std::ostream&     output;
            bool              state;
            MMTFDataWriterPtr writer;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMTFMOLECULARGRAPHWRITER_HPP
