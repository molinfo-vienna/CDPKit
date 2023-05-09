/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomMapping.hpp 
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
 * \brief Definition of the type CDPL::Chem::AtomMapping.
 */

#ifndef CDPL_CHEM_ATOMMAPPING_HPP
#define CDPL_CHEM_ATOMMAPPING_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/MultiMap.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;

		/**
		 * \brief A data type for the storage and lookup of arbitrary atom to atom mappings.
		 *
		 * Atoms mappings are stored as pairs of pointers to the mapped \c const Chem::Atom objects.
		 * Mappings do not have to be unique and multiple mappings of a given atom to other atoms are possible.
		 * If a mapping entry for a particular atom does not exist, the methods AtomMapping::getValue()
		 * and AtomMapping::operator[]() return a \e null pointer to indicate that the lookup of the 
		 * mapped atom has failed.
		 */
		class CDPL_CHEM_API AtomMapping : public Util::MultiMap<const Atom*, const Atom*, true>
		{

		  public:
			typedef boost::shared_ptr<AtomMapping> SharedPointer;

		  private:
			const char* getClassName() const {
				return "AtomMapping";
			}
		};
	}
}

#endif // CDPL_CHEM_ATOMMAPPING_HPP
