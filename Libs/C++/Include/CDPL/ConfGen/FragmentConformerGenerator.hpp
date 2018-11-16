/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::FragmentConformerGenerator.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/Raw3DCoordinatesGenerator.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
#include "CDPL/Chem/AutomorphismGroupSearch.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/VectorArrayAlignmentCalculator.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		class CDPL_CONFGEN_API FragmentConformerGenerator
		{

		  public:
			static const std::size_t  DEF_MAX_NUM_STRUCTURE_GEN_TRIALS    = 10;
			static const std::size_t  DEF_MAX_NUM_MINIMIZATION_STEPS      = 0;
			static const std::size_t  DEF_MAX_NUM_OUTPUT_CONFORMERS       = 1000;
			static const std::size_t  DEF_MIN_NUM_RING_CONFORMER_TRIALS   = 30;
			static const std::size_t  DEF_MAX_NUM_RING_CONFORMER_TRIALS   = 2000;
			static const std::size_t  DEF_RING_CONFORMER_TRIAL_FACTOR     = 20;
			static const std::size_t  DEF_TIMEOUT                         = 10 * 60 * 1000;
			static const double       DEF_MINIMIZATION_STOP_GRADIENT_NORM;
			static const double       DEF_MINIMIZATION_STOP_ENERGY_DELTA;
			static const double       DEF_ENERGY_WINDOW;
			static const double       DEF_MIN_RMSD;

			FragmentConformerGenerator();
	
			void setMaxNumStructureGenerationTrials(std::size_t max_num);

			std::size_t getMaxNumStructureGenerationTrials() const;

			void setMaxNumMinimizationSteps(std::size_t max_num);

			std::size_t getMaxNumMinimizationSteps() const;

			void setMinimizationStopGradientNorm(double grad_norm);

			double getMinimizationStopGradientNorm() const;

			void setMinimizationStopEnergyDelta(double e_delta);

			double getMinimizationStopEnergyDelta() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

			void reuseExistingCoordinates(bool reuse);

			bool existingCoordinatesReused() const;

			void setEnergyWindow(double win_size);

			double getEnergyWindow() const;

			void setRingConformerTrialFactor(std::size_t factor);

			std::size_t getRingConformerTrialFactor() const;

			void setMinNumRingConformerTrials(std::size_t min_num);

			std::size_t getMinNumRingConformerTrials() const;

			void setMaxNumRingConformerTrials(std::size_t max_num);

			std::size_t getMaxNumRingConformerTrials() const;
			
			void setMinRMSD(double min_rmsd);

			double getMinRMSD() const;

			void setMaxNumOutputConformers(std::size_t max_num);

			std::size_t getMaxNumOutputConformers() const;

			std::size_t generate(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data, 
								 unsigned int frag_type);

			std::size_t getNumConformers() const;

			const Math::Vector3DArray& getCoordinates(std::size_t conf_idx) const;

			Math::Vector3DArray& getCoordinates(std::size_t conf_idx);

			double getEnergy(std::size_t conf_idx) const;

		  private:
			typedef std::pair<double, Math::Vector3DArray::SharedPointer> ConfData;
			typedef std::vector<const Chem::Atom*> AtomList;

			FragmentConformerGenerator(const FragmentConformerGenerator&);

			FragmentConformerGenerator& operator=(const FragmentConformerGenerator&);

			void generateSingleConformer();
			void generateFlexibleRingConformers();

			bool extractExistingCoordinates(ConfData& conf);
			bool generateRandomConformer(ConfData& conf, bool best_opt);

			void init(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);
			void initRandomConformerGeneration();

			bool checkRMSD(const ConfData& conf);
			
			Math::Vector3DArray::SharedPointer getRingAtomCoordinates(const ConfData& conf);

			void getRingAtomIndices();
			void getAtomSymmetryMappings();
			void getNeighborHydrogens(const Chem::Atom& atom, AtomList& nbr_list) const;

			bool isMacrocyclicRingSystem() const;

			std::size_t calcStandardRingSystemConformerTrials() const;
			std::size_t calcMacrocyclicRingSystemConformerTrials() const;

			std::size_t getNumRotatableRingBonds(const Chem::MolecularGraph& molgraph) const;

			double calcMacrocyclicRingSystemEnergyWindow() const;

			void freeCoordinates(const Math::Vector3DArray::SharedPointer& coords_ptr);
			void freeCoordinates(const ConfData& conf);

			Math::Vector3DArray::SharedPointer allocCoordinates();
			void allocCoordinates(ConfData& conf);

			bool timeoutExceeded() const;
			bool has3DCoordinates(const Chem::Atom& atom) const;

			class CoordsDeallocator
			{

			public:
				CoordsDeallocator(FragmentConformerGenerator* owner, const ConfData& conf): 
					owner(owner), coordsPtr(conf.second), released(false) {}

				CoordsDeallocator(FragmentConformerGenerator* owner, const Math::Vector3DArray::SharedPointer& coords_ptr): 
					owner(owner), coordsPtr(coords_ptr), released(false) {}

				~CoordsDeallocator() {
					if (!released)
						owner->freeCoordinates(coordsPtr);
				}

				void release() {
					released = true;
				}

			private:
				FragmentConformerGenerator*               owner;
				const Math::Vector3DArray::SharedPointer& coordsPtr;
				bool                                      released;
			};

			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef Math::BFGSMinimizer<Math::Vector3DArray::StorageType, double> BFGSMinimizer; 
			typedef Math::VectorArrayAlignmentCalculator<Math::Vector3DArray> AlignmentCalculator;
			typedef std::vector<ConfData> ConfDataArray;
			typedef std::vector<Math::Vector3DArray::SharedPointer> CoordsDataArray;
			typedef std::vector<std::size_t> IndexList;

			std::size_t                              maxNumStructGenTrials;
			std::size_t                              maxNumMinSteps;
			std::size_t                              maxNumOutputConfs;
			double                                   minStopGradNorm;
			double                                   minStopEnergyDelta;
			std::size_t                              timeout;
			bool                                     reuseExistingCoords;
			double                                   eWindow;
			std::size_t                              ringConfTrialFactor;
			std::size_t                              minNumRingConfTrials;
			std::size_t                              maxNumRingConfTrials;
			double                                   minRMSD;
			boost::timer::cpu_timer                  timer;
			const Chem::MolecularGraph*              molGraph;
			std::size_t                              numAtoms;
			const ForceField::MMFF94InteractionData* mmff94Interactions;   
			MMFF94EnergyCalculator                   mmff94EnergyCalc;
			MMFF94GradientCalculator                 mmff94GradientCalc;
			BFGSMinimizer                            energyMinimizer;
			Raw3DCoordinatesGenerator                rawCoordsGenerator;
			Chem::Hydrogen3DCoordinatesGenerator     hCoordsGenerator;
			Chem::AutomorphismGroupSearch            automorphGroupSearch;
			AlignmentCalculator                      alignmentCalc;
			Math::Vector3DArray::StorageType         gradient;
			IndexList                                ringAtomIndices;
			IndexList                                atomSymmetryMappings;
			AtomList                                 nbrHydrogens1;
			AtomList                                 nbrHydrogens2;
			Chem::Fragment                           ordHDepleteMolGraph;
			Util::BitSet                             ordHDepleteAtomMask;
			CoordsDataArray                          ringAtomCoords;
			ConfDataArray                            outputConfs;
			ConfDataArray                            workingConfs;
			CoordsDataArray                          coordsCache;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP
