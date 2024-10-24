/* 
 * CMLMolecularGraphWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::CMLMolecularGraphWriter.
 */

#ifndef CDPL_CHEM_CMLMOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_CMLMOLECULARGRAPHWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class CMLDataWriter;
        class MolecularGraph;

        /**
         * \brief A writer for molecular graph data in the <em>Chemical Markup Language</em> [\ref CML] format.
         *
         * \c %CMLMolecularGraphWriter supports the following control-parameters:
         *
         * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
         *  </tr>
         *  <tr>
         *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
         *   <td align="center">\c false</td>
         *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a write operation to fail</td>
         *  </tr>
         * </table>
         *
         * \since 1.2
         */
        class CDPL_CHEM_API CMLMolecularGraphWriter : public Base::DataWriter<MolecularGraph>
        {

          public:
            /**
             * \brief Constructs a \c %CMLMolecularGraphWriter instance that will write data of molecular graphs to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            CMLMolecularGraphWriter(std::ostream& os);

            CMLMolecularGraphWriter(const CMLMolecularGraphWriter&) = delete;
            
            /**
             * \brief Destructor.
             */
            ~CMLMolecularGraphWriter();

            CMLMolecularGraphWriter& operator=(const CMLMolecularGraphWriter&) = delete;

            /**
             * \brief Writes data of the molecular graph \a molgraph to the output stream specified in the constructor.
             * \param molgraph The molecular graph to write.
             * \return A reference to itself.
             */
            Base::DataWriter<MolecularGraph>& write(const MolecularGraph& molgraph);

            operator const void*() const;
            bool operator!() const;

          private:
            typedef std::unique_ptr<CMLDataWriter> CMLDataWriterPtr;

            std::ostream&    output;
            bool             state;
            CMLDataWriterPtr writer;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CMLMOLECULARGRAPHWRITER_HPP
