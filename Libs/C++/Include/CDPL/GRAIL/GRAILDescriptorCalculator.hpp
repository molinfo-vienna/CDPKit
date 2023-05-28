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

			enum ElementIndex
		    {

			  PI_COUNT,
			  NI_COUNT,
			  AR_COUNT,
			  H_COUNT,
			  HBD_COUNT,
			  HBA_COUNT,
			  XBD_COUNT,
			  XBA_COUNT,
			  HBD_N3_COUNT,
			  HBD_N2_COUNT,
			  HBD_Nar_COUNT,
			  HBD_Nam_COUNT,
			  HBD_Npl3_COUNT,
			  HBD_N4_COUNT,
			  HBD_O3_COUNT,
			  HBD_S3_COUNT,
			  HBA_N3_COUNT,
			  HBA_N2_COUNT,
			  HBA_N1_COUNT,
			  HBA_Nar_COUNT,
			  HBA_Npl3_COUNT,
			  HBA_O3_COUNT,
			  HBA_O2_COUNT,
			  HBA_Oco2_COUNT,
			  HBA_S3_COUNT,
			  HBA_S2_COUNT,
			  TOTAL_HYD,
			  LOGP,
			  ENV_HBA_N_OCC,
			  ENV_HBA_O_OCC,
			  ENV_HBA_S_OCC,
			  ENV_HBD_N_OCC,
			  ENV_HBD_O_OCC,
			  ENV_HBD_S_OCC,
			  PI_AR_SCORE,
			  AR_PI_SCORE,
			  H_H_SCORE,
			  AR_AR_SCORE,
			  HBD_HBA_N_SCORE,
			  HBD_HBA_O_SCORE,
			  HBD_HBA_S_SCORE,
			  HBD_N3_HBA_N_SCORE,
			  HBD_N3_HBA_O_SCORE,
			  HBD_N3_HBA_S_SCORE,
			  HBD_N2_HBA_N_SCORE,
			  HBD_N2_HBA_O_SCORE,
			  HBD_N2_HBA_S_SCORE,
			  HBD_Nar_HBA_N_SCORE,
			  HBD_Nar_HBA_O_SCORE,
			  HBD_Nar_HBA_S_SCORE,
			  HBD_Nam_HBA_N_SCORE,
			  HBD_Nam_HBA_O_SCORE,
			  HBD_Nam_HBA_S_SCORE,
			  HBD_Npl3_HBA_N_SCORE,
			  HBD_Npl3_HBA_O_SCORE,
			  HBD_Npl3_HBA_S_SCORE,
			  HBD_N4_HBA_N_SCORE,
			  HBD_N4_HBA_O_SCORE,
			  HBD_N4_HBA_S_SCORE,
			  HBD_O3_HBA_N_SCORE,
			  HBD_O3_HBA_O_SCORE,
			  HBD_O3_HBA_S_SCORE,
			  HBD_S3_HBA_N_SCORE,
			  HBD_S3_HBA_O_SCORE,
			  HBD_S3_HBA_S_SCORE,
			  HBA_HBD_N_SCORE,
			  HBA_HBD_O_SCORE,
			  HBA_HBD_S_SCORE,
			  HBA_N3_HBD_N_SCORE,
			  HBA_N3_HBD_O_SCORE,
			  HBA_N3_HBD_S_SCORE,
			  HBA_N2_HBD_N_SCORE,
			  HBA_N2_HBD_O_SCORE,
			  HBA_N2_HBD_S_SCORE,
			  HBA_N1_HBD_N_SCORE,
			  HBA_N1_HBD_O_SCORE,
			  HBA_N1_HBD_S_SCORE,
			  HBA_Nar_HBD_N_SCORE,
			  HBA_Nar_HBD_O_SCORE,
			  HBA_Nar_HBD_S_SCORE,
			  HBA_Npl3_HBD_N_SCORE,
			  HBA_Npl3_HBD_O_SCORE,
			  HBA_Npl3_HBD_S_SCORE,
			  HBA_O3_HBD_N_SCORE,
			  HBA_O3_HBD_O_SCORE,
			  HBA_O3_HBD_S_SCORE,
			  HBA_O2_HBD_N_SCORE,
			  HBA_O2_HBD_O_SCORE,
			  HBA_O2_HBD_S_SCORE,
			  HBA_Oco2_HBD_N_SCORE,
			  HBA_Oco2_HBD_O_SCORE,
			  HBA_Oco2_HBD_S_SCORE,
			  HBA_S3_HBD_N_SCORE,
			  HBA_S3_HBD_O_SCORE,
			  HBA_S3_HBD_S_SCORE,
			  HBA_S2_HBD_N_SCORE,
			  HBA_S2_HBD_O_SCORE,
			  HBA_S2_HBD_S_SCORE,
			  XBD_XBA_SCORE,
			  ES_ENERGY,
			  VDW_ENERGY
		    };
			
			GRAILDescriptorCalculator();

			GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc);

			GRAILDescriptorCalculator& operator=(const GRAILDescriptorCalculator& calc);

			void initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
								bool tgt_env_changed = true);

			void initLigandData(const Chem::MolecularGraph& ligand);

			void calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part = true);
			
		  private:
			void calcLigFtrCoordinates(const Math::Vector3DArray::StorageType& atom_coords);
			
			void calcTgtEnvHBAHBDOccupations(const Math::Vector3DArray::StorageType& atom_coords,
											 Math::DVector& descr, std::size_t& idx);
			double calcTgtEnvHBAHBDOccupation(const Math::Vector3DArray::StorageType& atom_coords,
											  unsigned int tgt_ftr_type, bool is_hba_type);
			
			void calcFeatureInteractionScores(Math::DVector& descr, std::size_t& idx);

			void calcElectrostaticInteractionEnergy(const Math::Vector3DArray::StorageType& atom_coords,
													Math::DVector& descr, std::size_t& idx);

			void calcVdWInteractionEnergy(const Math::Vector3DArray::StorageType& atom_coords,
										  Math::DVector& descr, std::size_t idx);
			
			typedef std::vector<std::size_t> IndexList;
			typedef std::vector<const Pharm::Feature*> FeatureList;
			typedef std::vector<double> DoubleArray;
			typedef std::vector<IndexList> IndexListArray;
			typedef std::vector<Math::Vector3D> FastVector3DArray;
			typedef Internal::Octree<Math::Vector3D, FastVector3DArray, double> Octree;
			typedef boost::shared_ptr<Octree> OctreePtr;

			struct FeatureSubset
			{

				FeatureList       features;
				OctreePtr         octree;
				FastVector3DArray ftrCoords;
			};

			struct TargetAtomCoordsFunc
		    {

				TargetAtomCoordsFunc(const Chem::MolecularGraph& tgt_env, const FastVector3DArray& coords):
					tgtEnv(&tgt_env), coords(&coords) {}

				const Math::Vector3D& operator()(const Chem::Atom& atom) const;
				
				const Chem::MolecularGraph* tgtEnv;
				const FastVector3DArray*    coords;
			};
			
			typedef std::vector<FeatureSubset> FeatureSubsetList;
			typedef std::pair<double, double> DoublePair;
			typedef std::vector<DoublePair> DoublePairArray;

			void getVdWParameters(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, DoublePair& params) const;
			bool isPolarHydrogen(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const;
			
			void initPharmGenerators();

			void copyTgtFtrSubsets(const FeatureSubsetList& ftr_ss_list);

			Pharm::DefaultPharmacophoreGenerator  tgtPharmGenerator;
			Pharm::BasicPharmacophore             tgtPharmacophore;
			DoubleArray                           tgtAtomCharges;
			DoublePairArray                       tgtAtomVdWParams;
			FastVector3DArray                     tgtAtomCoords;
			OctreePtr                             tgtAtomOctree;
			FeatureSubsetList                     tgtFtrSubsets;
			Pharm::DefaultPharmacophoreGenerator  ligPharmGenerator;
			Pharm::BasicPharmacophore             ligPharmacophore;
			DoubleArray                           ligAtomCharges;
			DoublePairArray                       ligAtomVdWParams;
			IndexList                             ligHeavyAtoms;
			IndexListArray                        ligFtrSubsets;
			IndexListArray                        ligFtrAtoms;
			DoubleArray                           ligFtrWeights;
			FastVector3DArray                     ligFtrCoords;
			double                                ligDescriptor[LIGAND_DESCRIPTOR_SIZE];
			std::size_t                           numLigAtoms;
			IndexList                             tmpIndexList;
		};
	}
}

#endif // CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
