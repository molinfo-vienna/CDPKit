/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BuriednessGridCalculator.hpp 
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
 * \brief Definition of the class CDPL::GRAIL::BuriednessGridCalculator.
 */

#ifndef CDPL_GRAIL_BURIEDNESSGRIDCALCULATOR_HPP
#define CDPL_GRAIL_BURIEDNESSGRIDCALCULATOR_HPP

#include <vector>
#include <cstddef>
#include <memory>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/GRAIL/BuriednessScore.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Grid/SpatialGrid.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

 	namespace Internal 
	{

		template <typename PT, typename CT, typename ST> class Octree;
	}

	namespace GRAIL
    {

		/**
		 * \brief BuriednessGridCalculator.
		 */
		class CDPL_GRAIL_API BuriednessGridCalculator
		{

		  public:
			typedef std::shared_ptr<BuriednessGridCalculator> SharedPointer;

			BuriednessGridCalculator();

			BuriednessGridCalculator(const BuriednessGridCalculator& calc);

			void setProbeRadius(double radius);

			double getProbeRadius() const;

			void setMinVdWSurfaceDistance(double dist);

			double getMinVdWSurfaceDistance() const;

			void setNumTestRays(std::size_t num_rays);

			std::size_t getNumTestRays() const;

			/**
			 * \brief Specifies a function for the retrieval of atom 3D-coordinates for grid calculation.
			 * \param func The atom 3D-coordinates function.
			 */
			void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

			const Chem::Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

			void calculate(const Chem::AtomContainer& atoms, Grid::DSpatialGrid& grid);

			BuriednessGridCalculator& operator=(const BuriednessGridCalculator& calc);

		  private:
			typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
			typedef std::shared_ptr<Octree> OctreePtr;
			typedef std::vector<std::size_t> AtomIndexList;

			BuriednessScore      buriednessScore; 
			OctreePtr            octree;
			Math::Vector3DArray  atomCoords;
			AtomIndexList        atomIndices;
			Chem::Fragment       atomSubset;
		};
    }
}

#endif // CDPL_GRAIL_BURIEDNESSGRIDCALCULATOR_HPP
