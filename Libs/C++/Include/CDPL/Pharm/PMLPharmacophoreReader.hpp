/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PMLPharmacophoreReader.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PMLPharmacophoreReader.
 */

#ifndef CDPL_PHARM_PMLPHARMACOPHOREREADER_HPP
#define CDPL_PHARM_PMLPHARMACOPHOREREADER_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class PMLDataReader;
		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_PML_IO
		 * @{
		 */

		/**
		 * \brief A reader for pharmacophore data in the native I/O format of <em>LigandScout</em>.
		 */
		class CDPL_PHARM_API PMLPharmacophoreReader : public Util::StreamDataReader<Pharmacophore, PMLPharmacophoreReader>
		{

		public:
			/**
			 * \brief Constructs a \c %PMLPharmacophoreReader instance that will read the pharmacophore data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			PMLPharmacophoreReader(std::istream& is);

			/**
			 * \brief Destructor.
			 */
			~PMLPharmacophoreReader();

		private:
			friend class Util::StreamDataReader<Pharmacophore, PMLPharmacophoreReader>;

			PMLPharmacophoreReader(const PMLPharmacophoreReader&);

			PMLPharmacophoreReader& operator=(const PMLPharmacophoreReader&);

			bool readData(std::istream&, Pharmacophore&, bool overwrite);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			typedef std::auto_ptr<PMLDataReader> PMLDataReaderPtr;

			PMLDataReaderPtr reader;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_PMLPHARMACOPHOREREADER_HPP
