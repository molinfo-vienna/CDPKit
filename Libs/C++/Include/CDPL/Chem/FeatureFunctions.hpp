/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Feature instances.
 */

#ifndef CDPL_CHEM_FEATUREFUNCTIONS_HPP
#define CDPL_CHEM_FEATUREFUNCTIONS_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

    namespace Chem 
    {

		class Feature;
	
		/**
		 * \addtogroup CDPL_CHEM_FEATURE_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API unsigned int getType(const Feature& feature);

		CDPL_CHEM_API void setType(Feature& feature, unsigned int type);

		CDPL_CHEM_API void clearType(Feature& feature);

		CDPL_CHEM_API bool hasType(const Feature& feature);


		CDPL_CHEM_API unsigned int getGeometry(const Feature& feature);

		CDPL_CHEM_API void setGeometry(Feature& feature, unsigned int geom);

		CDPL_CHEM_API void clearGeometry(Feature& feature);

		CDPL_CHEM_API bool hasGeometry(const Feature& feature);

		
		CDPL_CHEM_API const Math::Vector3D& getOrientation(const Feature& feature);

		CDPL_CHEM_API void setOrientation(Feature& feature, const Math::Vector3D& orient);

		CDPL_CHEM_API void clearOrientation(Feature& feature);
	
		CDPL_CHEM_API bool hasOrientation(const Feature& feature);


		CDPL_CHEM_API double getLength(const Feature& feature);

		CDPL_CHEM_API void setLength(Feature& feature, double length);

		CDPL_CHEM_API void clearLength(Feature& feature);

		CDPL_CHEM_API bool hasLength(const Feature& feature);


		CDPL_CHEM_API double getTolerance(const Feature& feature);

		CDPL_CHEM_API void setTolerance(Feature& feature, double tol);

		CDPL_CHEM_API void clearTolerance(Feature& feature);

		CDPL_CHEM_API bool hasTolerance(const Feature& feature);


		CDPL_CHEM_API const Fragment::SharedPointer& getSubstructure(const Feature& feature);

		CDPL_CHEM_API void setSubstructure(Feature& feature, const Fragment::SharedPointer& substruct);

		CDPL_CHEM_API void clearSubstructure(Feature& feature);

		CDPL_CHEM_API bool hasSubstructure(const Feature& feature);


		CDPL_CHEM_API bool getDisabledFlag(const Feature& feature);

		CDPL_CHEM_API void setDisabledFlag(Feature& feature, bool flag);

		CDPL_CHEM_API void clearDisabledFlag(Feature& feature);

		CDPL_CHEM_API bool hasDisabledFlag(const Feature& feature);


		CDPL_CHEM_API bool getOptionalFlag(const Feature& feature);

		CDPL_CHEM_API void setOptionalFlag(Feature& feature, bool flag);

		CDPL_CHEM_API void clearOptionalFlag(Feature& feature);

		CDPL_CHEM_API bool hasOptionalFlag(const Feature& feature);

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_FEATUREFUNCTIONS_HPP
 
