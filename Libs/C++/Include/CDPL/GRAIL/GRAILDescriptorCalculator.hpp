/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GRAILDescriptorCalculator.hpp 
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
 * \brief Definition of the class CDPL::GRAIL::GRAILDescriptorCalculator.
 */

#ifndef CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
#define CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP

#include <vector>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
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
		 * \brief GRAILDescriptorCalculator.
		 * \see [\ref GRAIL]
		 */
		class CDPL_GRAIL_API GRAILDescriptorCalculator
		{

		  public:
			typedef boost::shared_ptr<GRAILDescriptorCalculator> SharedPointer;
			
			GRAILDescriptorCalculator();

			GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc);

			GRAILDescriptorCalculator& operator=(const GRAILDescriptorCalculator& calc);

			void initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func, bool tgt_env_changed = true);
			
		  private:
			typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
			typedef boost::shared_ptr<Octree> OctreePtr;
			typedef std::vector<std::size_t> IndexList;
			typedef std::vector<const Pharm::Feature*> FeatureList;
			
			struct FeatureSubset
			{

				FeatureList features;
				OctreePtr   octree;
			};

			typedef std::vector<FeatureSubset> FeatureSubsetList;

			void copyTargetFtrSubsetList(const FeatureSubsetList& ftr_ss_list);

			Pharm::DefaultPharmacophoreGenerator  tgtPharmGenerator;
			Pharm::BasicPharmacophore             tgtPharmacophore;
			Math::Vector3DArray                   tgtAtomCoords;
			OctreePtr                             tgtAtomOctree;
			FeatureSubsetList                     tgtFtrSubsets;
			Math::Vector3DArray                   tgtFtrCoords;
			IndexList                             indexList;
		};
	}
}

#endif // CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
