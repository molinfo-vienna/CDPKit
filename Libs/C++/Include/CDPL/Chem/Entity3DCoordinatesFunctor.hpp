/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DCoordinatesFunctor.hpp 
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
 * \brief Definition of the class CDPL::Chem::Entity3DCoordinatesFunctor.
 */

#ifndef CDPL_CHEM_ENTITY3DCOORDINATESFUNCTOR_HPP
#define CDPL_CHEM_ENTITY3DCOORDINATESFUNCTOR_HPP

#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Entity3D;

		/**
		 * \addtogroup CDPL_CHEM_FUNCTORS
		 * @{
		 */

		/**
		 * \brief Entity3DCoordinatesFunctor.
		 */
		class CDPL_CHEM_API Entity3DCoordinatesFunctor : public std::unary_function<Entity3D, const Math::Vector3D&>
		{

		  public:
			/**
			 * \brief Returns the 3D-coordinates of the argument entity object.
			 * \param entity The entity object.
			 * \return The 3D-coordinates of the entity object.
			 * \see Chem::get3DCoordinates(const Entity3D&)
			 */
			const Math::Vector3D& operator()(const Entity3D& entity) const;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ENTITY3DCOORDINATESFUNCTOR_HPP
