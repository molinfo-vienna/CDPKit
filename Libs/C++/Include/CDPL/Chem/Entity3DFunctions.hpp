/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Entity3DFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Entity3D instances.
 */

#ifndef CDPL_CHEM_ENTITY3DFUNCTIONS_HPP
#define CDPL_CHEM_ENTITY3DFUNCTIONS_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class Entity3D;
	
		/**
		 * \addtogroup CDPL_CHEM_ENTITY3D_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API const Math::Vector3D& get3DCoordinates(const Entity3D& entity);

		CDPL_CHEM_API void set3DCoordinates(Entity3D& entity, const Math::Vector3D& coords);

		CDPL_CHEM_API void clear3DCoordinates(Entity3D& entity);
	
		CDPL_CHEM_API bool has3DCoordinates(const Entity3D& entity);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ENTITY3DFUNCTIONS_HPP
 
