/* 
 * AtomBondMapping.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomBondMapping.
 */

#ifndef CDPL_CHEM_ATOMBONDMAPPING_HPP
#define CDPL_CHEM_ATOMBONDMAPPING_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomMapping.hpp"
#include "CDPL/Chem/BondMapping.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief A data structure for the common storage of related atom to atom and bond to bond mappings.
		 *
		 * \c %AtomBondMapping is used to represent arbitrary mappings between the atoms and bonds of
		 * two (or more) molecular graphs (e.g. results of a substructure search).
		 * The atom and bond mappings are stored in respective data members of type Chem::AtomMapping
		 * and Chem::BondMapping. They can be accessed by the provided getAtomMapping() and getBondMapping()
		 * family of overloaded methods.
		 */
		class CDPL_CHEM_API AtomBondMapping
		{

		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %AtomBondMapping instances.
			 */
			typedef std::shared_ptr<AtomBondMapping> SharedPointer;

			/**
			 * \brief Returns a \c const reference to the Chem::AtomMapping data member storing the atom
			 *        to atom mappings. 
			 * \return A \c const reference to the Chem::AtomMapping data member.
			 */
			const AtomMapping& getAtomMapping() const;

			/**
			 * \brief Returns a \c const reference to the Chem::BondMapping data member storing the bond
			 *        to bond mappings. 
			 * \return A \c const reference to the  Chem::BondMapping data member.
			 */
			const BondMapping& getBondMapping() const;

			/**
			 * \brief Returns a non-\c const reference to the Chem::AtomMapping data member storing the atom
			 *        to atom mappings. 
			 * \return A non-\c const reference to the Chem::AtomMapping data member.
			 */
			AtomMapping& getAtomMapping();

			/**
			 * \brief Returns a non-\c const reference to the Chem::BondMapping data member storing the bond
			 *        to bond mappings. 
			 * \return A non-\c const reference to the Chem::BondMapping data member.
			 */
			BondMapping& getBondMapping();

			/**
			 * \brief Removes all atom to atom and bond to bond mappings.
			 */
			void clear();

			/**
			 * \brief Equality comparison operator.
			 * \param mapping The other \c %AtomBondMapping instance to be compared with.
			 * \return \c true if the atom to atom and bond to bond mappings compare equal, and
			 *         \c false otherwise.
			 */
			bool operator==(const AtomBondMapping& mapping) const;

			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == mapping)</tt>.
			 *
			 * \param mapping The other \c %AtomBondMapping instance to be compared with.
			 * \return \c true if the atom to atom and/or bond to bond mappings compare non-equal, and
			 *         \c false otherwise.
			 * \see operator==()
			 */
			bool operator!=(const AtomBondMapping& mapping) const;

		private:
			AtomMapping atomMapping;
			BondMapping bondMapping;
		};
	}
}

#endif // CDPL_CHEM_ATOMBONDMAPPING_HPP
