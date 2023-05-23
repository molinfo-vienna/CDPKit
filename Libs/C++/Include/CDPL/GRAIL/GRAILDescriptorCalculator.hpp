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
#include <utility>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Vector.hpp"


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
			static const std::size_t TOTAL_DESCRIPTOR_SIZE  = 101;
			static const std::size_t LIGAND_DESCRIPTOR_SIZE = 28;
			
			typedef boost::shared_ptr<GRAILDescriptorCalculator> SharedPointer;
			
			GRAILDescriptorCalculator();

			GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc);

			GRAILDescriptorCalculator& operator=(const GRAILDescriptorCalculator& calc);

			void initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func, bool tgt_env_changed = true);

			void initLigandData(const Chem::MolecularGraph& ligand);

			void calculate(const Math::Vector3DArray& atom_coords, Math::DVector& res);
			
		  private:
			void calcLigDescriptor(const Chem::MolecularGraph& ligand);
			
			void calcLigFtrCoordinates(const Math::Vector3DArray& atom_coords);
			
			void calcTgtEnvHBAHBDOccupations(const Math::Vector3DArray& atom_coords, Math::DVector& res, std::size_t& idx);
			double calcTgtEnvHBAHBDOccupation(const Math::Vector3DArray& atom_coords, unsigned int tgt_ftr_type, bool is_hba_type);
			
			void calcFeatureInteractionScores(Math::DVector& res, std::size_t& idx);

			void calcElectrostaticInteractionEnergy(const Math::Vector3DArray& atom_coords, Math::DVector& res, std::size_t& idx);

			void calcVdWInteractionEnergy(const Math::Vector3DArray& atom_coords, Math::DVector& res, std::size_t idx);
			
			typedef Internal::Octree<Math::Vector3D, Math::Vector3DArray, double> Octree;
			typedef boost::shared_ptr<Octree> OctreePtr;
			typedef std::vector<std::size_t> IndexList;
			typedef std::vector<const Pharm::Feature*> FeatureList;
			typedef std::vector<double> DoubleArray;
			typedef std::vector<IndexList> IndexListArray;
			
			struct FeatureSubset
			{

				FeatureList features;
				OctreePtr   octree;
			};

			typedef std::vector<FeatureSubset> FeatureSubsetList;
			typedef std::pair<double, double> DoublePair;
			typedef std::vector<DoublePair> DoublePairArray;
			
			void initPharmGenerators();
			void copyTgtFtrSubsets(const FeatureSubsetList& ftr_ss_list);

			Pharm::DefaultPharmacophoreGenerator  tgtPharmGenerator;
			Pharm::BasicPharmacophore             tgtPharmacophore;
			DoubleArray                           tgtAtomCharges;
			DoublePairArray                       tgtAtomVdWParams;
			Math::Vector3DArray                   tgtAtomCoords;
			OctreePtr                             tgtAtomOctree;
			FeatureSubsetList                     tgtFtrSubsets;
			Math::Vector3DArray                   tgtFtrCoords;
			Pharm::DefaultPharmacophoreGenerator  ligPharmGenerator;
			Pharm::BasicPharmacophore             ligPharmacophore;
			DoubleArray                           ligAtomCharges;
			DoublePairArray                       ligAtomVdWParams;
			IndexList                             ligHeavyAtoms;
			IndexListArray                        ligFtrSubsets;
			IndexListArray                        ligFtrAtoms;
			DoubleArray                           ligFtrWeights;
			Math::Vector3DArray                   ligFtrCoords;
			double                                ligDescriptor[LIGAND_DESCRIPTOR_SIZE];
			IndexList                             tmpIndexList;
		};
	}
}

#endif // CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
