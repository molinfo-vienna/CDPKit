/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMARTSMoleculeWriter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::SMARTSMoleculeWriter.
 */

#ifndef CDPL_CHEM_SMARTSMOLECULARGRAPHWRITER_HPP
#define CDPL_CHEM_SMARTSMOLECULARGRAPHWRITER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/DataWriter.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class SMARTSDataWriter;
		class Molecule;

		/**
		 * \addtogroup CDPL_CHEM_SMARTS_IO
		 * @{
		 */

		/**
		 * \brief A writer for molecule data in the <em>Daylight SMARTS</em> [\ref SMARTS] format.
		 *
		 * \c %SMARTSMoleculeWriter supports the following control-parameters:
		 *
		 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value</th> <th>Description</th>
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
		class CDPL_CHEM_API SMARTSMoleculeWriter : public Base::DataWriter<Molecule>
		{

		public:
			/**
			 * \brief Constructs a \c %SMARTSMoleculeWriter instance that will write data of molecules to the output
			 *        stream \a os.
			 * \param os The output stream to write to.
			 */
			SMARTSMoleculeWriter(std::ostream& os);

			/**
			 * \brief Destructor.
			 */
			~SMARTSMoleculeWriter();

			/**
			 * \brief Writes data of the molecule \a mol to the output stream specified in the constructor.
			 * \param mol The molecule to write.
			 * \return A reference to itself.
			 */
			Base::DataWriter<Molecule>& write(const Molecule& mol);

			operator const void*() const;
			bool operator!() const;

		private:
			SMARTSMoleculeWriter(const SMARTSMoleculeWriter&);

			typedef std::auto_ptr<SMARTSDataWriter> SMARTSDataWriterPtr;

			std::ostream&       output;
			bool                state;
			SMARTSDataWriterPtr writer;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SMARTSMOLECULARGRAPHWRITER_HPP
