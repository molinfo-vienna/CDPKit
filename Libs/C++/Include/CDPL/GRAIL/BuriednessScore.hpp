/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BuriednessScore.hpp 
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
 * \brief Definition of the class CDPL::GRAIL::BuriednessScore.
 */

#ifndef CDPL_GRAIL_BURIEDNESSSCORE_HPP
#define CDPL_GRAIL_BURIEDNESSSCORE_HPP

#include <cstddef>
#include <vector>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
    {

		class AtomContainer;
	}
	
    namespace GRAIL
    {

		/**
		 * \brief BuriednessScore.
		 */
		class CDPL_GRAIL_API BuriednessScore
		{

		  public:
			static const double DEF_PROBE_RADIUS;
			static const double DEF_MIN_VDW_SURFACE_DISTANCE;
			static const std::size_t DEF_NUM_TEST_RAYS;

			BuriednessScore(double probe_radius = DEF_PROBE_RADIUS, double min_vdw_surf_dist = DEF_MIN_VDW_SURFACE_DISTANCE,
							std::size_t num_test_rays = DEF_NUM_TEST_RAYS);

			void setProbeRadius(double radius);

			double getProbeRadius() const;

			void setMinVdWSurfaceDistance(double dist);

			double getMinVdWSurfaceDistance() const;

			void setNumTestRays(std::size_t num_rays);

			std::size_t getNumTestRays() const;

			/**
			 * \brief Specifies a function for the retrieval of atom 3D-coordinates for buriedness calculation.
			 * \param func The atom 3D-coordinates function.
			 */
			void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

			const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;
	
			double operator()(const Math::Vector3D& pos, const Chem::AtomContainer& atoms);

		  private:
			void genSphereSurfacePoints();

			typedef std::vector<Math::Vector3D> PointList;

			double                          probeRadius;
			double                          minVdWSurfaceDist;
			std::size_t                     numTestRays;
			Chem::Atom3DCoordinatesFunction coordsFunc;
			PointList                       probeSurfPoints;
			Util::BitSet                    rayHitsMask;
		};
    }
}

#endif // CDPL_GRAIL_BURIEDNESSSCORE_HPP
