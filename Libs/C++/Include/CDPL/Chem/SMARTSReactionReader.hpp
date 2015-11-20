/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMARTSReactionReader.hpp 
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
 * \brief Definition of the class CDPL::Chem::SMARTSReactionReader.
 */

#ifndef CDPL_CHEM_SMARTSREACTIONREADER_HPP
#define CDPL_CHEM_SMARTSREACTIONREADER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class SMARTSDataReader;
		class Reaction;

		/**
		 * \addtogroup CDPL_CHEM_SMARTS_IO
		 * @{
		 */

		/**
		 * \brief A reader for reaction data in the <em>Daylight SMARTS</em> [\ref SMARTS] format.
		 *
		 * \c %SMARTSReactionReader supports the following control-parameter:
		 *
		 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th>Control-Parameter</th> <th>Default Value (see Chem::ControlParameterDefault)</th> <th>Description</th>
		 *  </tr>
		 *  <tr>
		 *   <td>Chem::ControlParameter::STRICT_ERROR_CHECKING</td>
		 *   <td align="center">\c false</td>
		 *   <td>Specifies whether non-fatal recoverable errors should be ignored or cause a read operation to fail</td>
		 *  </tr>
		 * </table>
		 */
		class CDPL_CHEM_API SMARTSReactionReader : public Util::StreamDataReader<Reaction, SMARTSReactionReader>
		{

		public:
			/**
			 * \brief Constructs a \c %SMARTSReactionReader instance that will read the reaction data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			SMARTSReactionReader(std::istream& is);

			/**
			 * \brief Destructor.
			 */
			~SMARTSReactionReader();

		private:
			friend class Util::StreamDataReader<Reaction, SMARTSReactionReader>;

			SMARTSReactionReader(const SMARTSReactionReader&);

			SMARTSReactionReader& operator=(const SMARTSReactionReader&);

			bool readData(std::istream&, Reaction&);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			typedef std::auto_ptr<SMARTSDataReader> SMARTSDataReaderPtr;

			SMARTSDataReaderPtr reader;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SMARTSREACTIONREADER_HPP
