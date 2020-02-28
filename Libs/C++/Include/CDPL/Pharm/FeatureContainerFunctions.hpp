/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Pharm::FeatureContainer instances.
 */

#ifndef CDPL_PHARM_FEATURECONTAINERFUNCTIONS_HPP
#define CDPL_PHARM_FEATURECONTAINERFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class AtomContainer;
		class Fragment;
    }

    namespace Pharm 
    {
	
		class FeatureContainer;
		class FeatureTypeHistogram;
	
		/**
		 * \addtogroup CDPL_PHARM_FEATURE_CONTAINER_FUNCTIONS
		 * @{
		 */

		CDPL_PHARM_API const std::string& getName(const FeatureContainer& cntnr);

		CDPL_PHARM_API void setName(FeatureContainer& cntnr, const std::string& name);

		CDPL_PHARM_API void clearName(FeatureContainer& cntnr);

		CDPL_PHARM_API bool hasName(const FeatureContainer& cntnr);

	
		CDPL_PHARM_API std::size_t getFeatureCount(const FeatureContainer& cntnr);

		CDPL_PHARM_API std::size_t getFeatureCount(const FeatureContainer& cntnr, unsigned int type);

		CDPL_PHARM_API void buildFeatureTypeHistogram(const FeatureContainer& cntnr, FeatureTypeHistogram& hist, bool append = false);

		CDPL_PHARM_API void transform3DCoordinates(FeatureContainer& cntnr, const Math::Matrix4D& mtx);

		CDPL_PHARM_API bool checkExclusionVolumeClash(const FeatureContainer& ftr_cntnr, const Chem::AtomContainer& atom_cntnr, 
													  const Chem::Atom3DCoordinatesFunction& coords_func,
													  const Math::Matrix4D& xform, double vdw_factor = 1.0);

		CDPL_PHARM_API void getFeatureAtoms(const FeatureContainer& cntnr, Chem::Fragment& atoms, bool append = false);

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_FEATURECONTAINERFUNCTIONS_HPP
