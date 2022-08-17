/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreFunctions.hpp 
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
 * \brief Declaration of functions that operate on Pharm::Pharmacophore instances.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP
#define CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class AtomContainer;
	}

    namespace Pharm 
    {
	
		class Pharmacophore;
		class FeatureMapping;
		class FeatureContainer;
	
		CDPL_PHARM_API void buildInteractionPharmacophore(Pharmacophore& pharm, const FeatureMapping& iactions, bool append = false);
			
		CDPL_PHARM_API void createExclusionVolumes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr, 
												   const Chem::Atom3DCoordinatesFunction& coords_func, 
												   double tol = 0.0, double min_dist = 0.0, bool rel_dist = true, bool append = true);

		CDPL_PHARM_API void createExclusionVolumes(Pharmacophore& pharm, const FeatureContainer& cntnr, 
												   double tol = 0.0, double min_dist = 0.0, bool rel_dist = true, bool append = true);

		CDPL_PHARM_API bool removeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr, 
															  const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact = 1.0);

		CDPL_PHARM_API bool resizeExclusionVolumesWithClashes(Pharmacophore& pharm, const Chem::AtomContainer& cntnr, 
															  const Chem::Atom3DCoordinatesFunction& coords_func, double vdw_scaling_fact = 1.0);

    }
}

#endif // CDPL_PHARM_PHARMACOPHOREFUNCTIONS_HPP
