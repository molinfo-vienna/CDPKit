/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DContainer.hpp 
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
 * \brief Definition of the class CDPL::Chem::Entity3DContainer.
 */

#ifndef CDPL_CHEM_ENTITYCONTAINER_HPP
#define CDPL_CHEM_ENTITYCONTAINER_HPP

#include <cstddef>

#include <boost/ref.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Entity3D;

		/**
		 * \addtogroup CDPL_CHEM_STRUCTURE_INTERFACES
		 * @{
		 */

		/**
		 * \brief A common interface for data-structures that support a random access to stored immutable Chem::Entity3D instances.
		 *
		 * Implementations have to guarantee that a given Chem::Entity3D object is stored only once and its index is unique amongst
		 * all contained Chem::Entity3D instances. Otherwise algorithms that rely on this behaviour may not work correctly!
		 */
		class CDPL_CHEM_API Entity3DContainer
		{

		public:
			/**
			 * \brief Returns the number of stored Chem::Entity3D objects.
			 * \return The number of stored Chem::Entity3D objects.
			 */
			virtual std::size_t getNumEntities() const = 0;

			/**
			 * \brief Returns a \c const reference to the Chem::Entity3D instance at index \a idx.
			 * \param idx The zero-based index of the Chem::Entity3D instance to return.
			 * \return A \c const reference to the Chem::Entity3D instance at the specified index.
			 * \throw Base::IndexError if the container is empty or \a idx is not in the range [0, getNumEntities() - 1].
			 */
			virtual const Entity3D& getEntity(std::size_t idx) const = 0;

			/**
			 * \brief Returns a non-\c const reference to the entity at index \a idx.
			 * \param idx The zero-based index of the Chem::Entity3D instance to return.
			 * \return A non-\c const reference to the entity at the specified index.
			 * \throw Base::IndexError if the number of entitys is zero or \a idx is not in the range [0, getNumEntities() - 1].
			 */
			virtual Entity3D& getEntity(std::size_t idx) = 0;
	
		protected:
			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Entity3DContainer() {}
		
			/**
			 * \brief Assignment operator.
			 * \param cntnr The other container to copy.
			 * \return A reference to itself.
			 */
			Entity3DContainer& operator=(const Entity3DContainer& cntnr) { return *this; }
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ENTITYCONTAINER_HPP
