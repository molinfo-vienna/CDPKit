/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DMapping.hpp 
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
 * \brief Definition of the type CDPL::Chem::Entity3DMapping.
 */

#ifndef CDPL_CHEM_ENTITY3DMAPPING_HPP
#define CDPL_CHEM_ENTITY3DMAPPING_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/MultiMap.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class Entity3D;

		/**
		 * \addtogroup CDPL_CHEM_DATA_STRUCTURES
		 * @{
		 */

		/**
		 * \brief A data type for the storage and lookup of arbitrary entity to entity mappings.
		 *
		 * Entity3Ds mappings are stored as pairs of pointers to the mapped \c const Chem::Entity3D objects.
		 * Mappings do not have to be unique and multiple mappings of a given entity to other entities are possible.
		 * If a mapping entry for a particular entity does not exist, the methods Entity3DMapping::getValue()
		 * and Entity3DMapping::operator[]() return a \e null pointer to indicate that the lookup of the 
		 * mapped entity has failed.
		 */
		class CDPL_CHEM_API Entity3DMapping : public Util::MultiMap<const Entity3D*, const Entity3D*, true>
		{

		  public:
			typedef boost::shared_ptr<Entity3DMapping> SharedPointer;

			Entity3DMapping();
			
		  private:
			const char* getClassName() const {
				return "Entity3DMapping";
			}
		};
		
		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_ENTITY3DMAPPING_HPP
