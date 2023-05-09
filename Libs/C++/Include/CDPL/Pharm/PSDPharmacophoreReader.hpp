/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PSDPharmacophoreReader.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PSDPharmacophoreReader.
 */

#ifndef CDPL_PHARM_PSDPHARMACOPHOREREADER_HPP
#define CDPL_PHARM_PSDPHARMACOPHOREREADER_HPP

#include <string>
#include <iosfwd>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"
#include "CDPL/Base/DataReader.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Pharmacophore;

		/**
		 * \brief A reader for pharmacophore data in the PSD-format of the <em>CDPL</em>.
		 */
		class CDPL_PHARM_API PSDPharmacophoreReader : public Base::DataReader<Pharmacophore>
		{

		  public:
			/**
			 * \brief Constructs a \c %PSDPharmacophoreReader instance that will read the pharmacophore data from the input
			 *        stream \a is.
			 * \param is The input stream to read from.
			 */
			PSDPharmacophoreReader(std::istream& is);

			/**
			 * \brief Constructs a \c %PSDPharmacophoreReader instance that will read the pharmacophore data from the input
			 *        file \a file_name.
			 * \param file_name The input file to read from.
			 */
			PSDPharmacophoreReader(const std::string& file_name);

			~PSDPharmacophoreReader();

			PSDPharmacophoreReader& read(Pharmacophore& pharm, bool overwrite = true);

			PSDPharmacophoreReader& read(std::size_t idx, Pharmacophore& pharm, bool overwrite = true);

			PSDPharmacophoreReader& skip();

			bool hasMoreData();

			std::size_t getRecordIndex() const;
			void setRecordIndex(std::size_t idx);

			std::size_t getNumRecords();

			operator const void*() const;
			bool operator!() const;

		  private:
			PSDScreeningDBAccessor accessor;
			std::size_t            recordIndex;
			std::size_t            numRecords;
			bool                   state;
		};
    }
}

#endif // CDPL_PHARM_PSDPHARMACOPHOREREADER_HPP
