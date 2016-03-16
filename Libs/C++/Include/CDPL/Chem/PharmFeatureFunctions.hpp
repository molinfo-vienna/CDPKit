/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmFeatureFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::PharmFeature instances.
 */

#ifndef CDPL_CHEM_PHARMFEATUREFUNCTIONS_HPP
#define CDPL_CHEM_PHARMFEATUREFUNCTIONS_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Chem 
    {

		class PharmFeature;
	
		/**
		 * \addtogroup CDPL_CHEM_PHARMFEATURE_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API unsigned int getType(const PharmFeature& feature);

		CDPL_CHEM_API void setType(PharmFeature& feature, unsigned int type);

		CDPL_CHEM_API void clearType(PharmFeature& feature);

		CDPL_CHEM_API bool hasType(const PharmFeature& feature);


		CDPL_CHEM_API unsigned int getGeometry(const PharmFeature& feature);

		CDPL_CHEM_API void setGeometry(PharmFeature& feature, unsigned int geom);

		CDPL_CHEM_API void clearGeometry(PharmFeature& feature);

		CDPL_CHEM_API bool hasGeometry(const PharmFeature& feature);

		
		CDPL_CHEM_API const Math::Vector3D& getOrientation(const PharmFeature& feature);

		CDPL_CHEM_API void setOrientation(PharmFeature& feature, const Math::Vector3D& orient);

		CDPL_CHEM_API void clearOrientation(PharmFeature& feature);
	
		CDPL_CHEM_API bool hasOrientation(const PharmFeature& feature);


		CDPL_CHEM_API double getLength(const PharmFeature& feature);

		CDPL_CHEM_API void setLength(PharmFeature& feature, double length);

		CDPL_CHEM_API void clearLength(PharmFeature& feature);

		CDPL_CHEM_API bool hasLength(const PharmFeature& feature);


		CDPL_CHEM_API double getTolerance(const PharmFeature& feature);

		CDPL_CHEM_API void setTolerance(PharmFeature& feature, double tol);

		CDPL_CHEM_API void clearTolerance(PharmFeature& feature);

		CDPL_CHEM_API bool hasTolerance(const PharmFeature& feature);


		CDPL_CHEM_API const Fragment::SharedPointer& getSubstructure(const PharmFeature& feature);

		CDPL_CHEM_API void setSubstructure(PharmFeature& feature, const Fragment::SharedPointer& substruct);

		CDPL_CHEM_API void clearSubstructure(PharmFeature& feature);

		CDPL_CHEM_API bool hasSubstructure(const PharmFeature& feature);


		CDPL_CHEM_API bool getDisabledFlag(const PharmFeature& feature);

		CDPL_CHEM_API void setDisabledFlag(PharmFeature& feature, bool flag);

		CDPL_CHEM_API void clearDisabledFlag(PharmFeature& feature);

		CDPL_CHEM_API bool hasDisabledFlag(const PharmFeature& feature);


		CDPL_CHEM_API bool getOptionalFlag(const PharmFeature& feature);

		CDPL_CHEM_API void setOptionalFlag(PharmFeature& feature, bool flag);

		CDPL_CHEM_API void clearOptionalFlag(PharmFeature& feature);

		CDPL_CHEM_API bool hasOptionalFlag(const PharmFeature& feature);

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_PHARMFEATUREFUNCTIONS_HPP
 
