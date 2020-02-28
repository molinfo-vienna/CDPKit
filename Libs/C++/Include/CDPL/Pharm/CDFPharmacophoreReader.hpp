/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFPharmacophoreReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Pharm::CDFPharmacophoreReader.
 */

#ifndef CDPL_PHARM_CDFPHARMACOPHOREREADER_HPP
#define CDPL_PHARM_CDFPHARMACOPHOREREADER_HPP

#include <memory>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Util/StreamDataReader.hpp"


namespace CDPL 
{

	namespace Pharm
	{

		class CDFPharmacophoreDataReader;
		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_CDF_IO
		 * @{
		 */

		/**
		 * \brief A reader for pharmacophore data in the native I/O format of the <em>CDPL</em>.
		 */
		class CDPL_PHARM_API CDFPharmacophoreReader : public Util::StreamDataReader<Pharmacophore, CDFPharmacophoreReader>
		{

		public:
			/**
			 * \brief Constructs a \c %CDFPharmacophoreReader instance that will read the pharmacophore data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			CDFPharmacophoreReader(std::istream& is);

			/**
			 * \brief Destructor.
			 */
			~CDFPharmacophoreReader();

		private:
			friend class Util::StreamDataReader<Pharmacophore, CDFPharmacophoreReader>;

			CDFPharmacophoreReader(const CDFPharmacophoreReader&);

			CDFPharmacophoreReader& operator=(const CDFPharmacophoreReader&);

			bool readData(std::istream&, Pharmacophore&, bool overwrite);
			bool skipData(std::istream&);
			bool moreData(std::istream&);

			typedef std::auto_ptr<CDFPharmacophoreDataReader> CDFDataReaderPtr;

			CDFDataReaderPtr reader;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_PHARM_CDFPHARMACOPHOREREADER_HPP
