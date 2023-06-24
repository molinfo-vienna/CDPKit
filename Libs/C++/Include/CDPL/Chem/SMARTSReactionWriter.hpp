/* 
 * SMARTSReactionWriter.hpp 
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
 * \brief Definition of the class CDPL::Chem::SMARTSReactionWriter.
 */

#ifndef CDPL_CHEM_SMARTSREACTIONWRITER_HPP
#define CDPL_CHEM_SMARTSREACTIONWRITER_HPP

#include <memory>
#include <iosfwd>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL
{

    namespace Chem
    {

        class SMARTSDataWriter;
        class Reaction;

        /**
         * \brief A writer for reaction data in the <em>Daylight SMARTS</em> [\ref SMARTS] format.
         *
         * \c %SMARTSReactionWriter supports the following control-parameters:
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
         *  <tr>
         *   <td>Chem::ControlParameter::RECORD_SEPARATOR</td>
         *   <td align="center">\c "\\n"</td>
         *   <td>Specifies the data record separator</td>
         *  </tr>
         * </table>
         */
        class CDPL_CHEM_API SMARTSReactionWriter : public Base::DataWriter<Reaction>
        {

          public:
            /**
             * \brief Constructs a \c %SMARTSReactionWriter instance that will write the reaction data to the output
             *        stream \a os.
             * \param os The output stream to write to.
             */
            SMARTSReactionWriter(std::ostream& os);

            /**
             * \brief Destructor.
             */
            ~SMARTSReactionWriter();

            /**
             * \brief Writes the reaction \a rxn to the output stream specified in the constructor.
             * \param rxn The reaction to write.
             * \return A reference to itself.
             */
            Base::DataWriter<Reaction>& write(const Reaction& rxn);

                 operator const void*() const;
            bool operator!() const;

          private:
            typedef std::auto_ptr<SMARTSDataWriter> SMARTSDataWriterPtr;

            SMARTSReactionWriter(const SMARTSReactionWriter&);

            SMARTSReactionWriter& operator=(const SMARTSReactionWriter&);

            std::ostream&       output;
            bool                state;
            SMARTSDataWriterPtr writer;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SMARTSREACTIONWRITER_HPP
