/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningDBAccessor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::ScreeningDBAccessor.
 */

#ifndef CDPL_PHARM_SCREENINGDBACCESSOR_HPP
#define CDPL_PHARM_SCREENINGDBACCESSOR_HPP

#include <string>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Molecule;
	}

    namespace Pharm
    {
	
		class Pharmacophore;

		/**
		 * \addtogroup CDPL_PHARM_SCREENING
		 * @{
		 */

		/**
		 * \brief A class for accessing the data stored in pharmacophore screening databases.
		 */
		class CDPL_PHARM_API ScreeningDBAccessor
		{

		  public:
			typedef boost::shared_ptr<ScreeningDBAccessor> SharedPointer;

			/**
			 * \brief Destructor.
			 */
			virtual ~ScreeningDBAccessor() {}

			virtual void open(const std::string& name) = 0;

			virtual void close() = 0;

			virtual const std::string& getDatabaseName() const = 0;

			virtual std::size_t getNumMolecules() const = 0;

			virtual std::size_t getNumPharmacophores() const = 0;

			virtual void getMolecule(std::size_t idx, Chem::Molecule& mol) const = 0; 

			virtual void getPharmacophore(std::size_t idx, Pharmacophore& pharm) const = 0; 

			virtual void getPharmacophore(std::size_t mol_idx, std::size_t conf_idx, Pharmacophore& pharm) const = 0; 

			virtual std::size_t findMatchingEntries(const Pharmacophore& pharm) = 0;

			virtual std::size_t getNumMatchingEntries() = 0;

			virtual std::size_t getMatchingEntryMolIndex(std::size_t idx) const = 0;

			virtual std::size_t getMatchingEntryConfIndex(std::size_t idx) const = 0;

		  protected:
			ScreeningDBAccessor& operator=(const ScreeningDBAccessor&) {
				return *this;
			}
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_SCREENINGDBACCESSOR_HPP
