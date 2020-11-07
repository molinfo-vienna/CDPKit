/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConformerGeneratorImpl.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::ConformerGeneratorImpl.
 */

#ifndef CDPL_CONFGEN_CONFORMERGENERATORIMPL_HPP
#define CDPL_CONFGEN_CONFORMERGENERATORIMPL_HPP

#include <vector>
#include <cstddef>
#include <utility>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/ConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ConfGen/RMSDConformerSelector.hpp"
#include "CDPL/ConfGen/DGStructureGenerator.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Util/ObjectPool.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Util/BitSet.hpp"

#include "TorsionDriverImpl.hpp"
#include "FragmentAssemblerImpl.hpp"
#include "ForceFieldInteractionMask.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class ConformerGeneratorImpl 
		{

		public:
			typedef ConformerDataArray::const_iterator ConstConformerIterator;

			ConformerGeneratorImpl();

			~ConformerGeneratorImpl();

			ConformerGeneratorSettings& getSettings();

			void clearFragmentLibraries();

			void addFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

			void clearTorsionLibraries();

			void addTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			void setLogMessageCallback(const LogMessageCallbackFunction& func);

			const LogMessageCallbackFunction& getLogMessageCallback() const;

			unsigned int generate(const Chem::MolecularGraph& molgraph, bool struct_gen_only);

			void setConformers(Chem::MolecularGraph& molgraph) const;

			std::size_t getNumConformers() const;

			ConformerData& getConformer(std::size_t idx);

			ConstConformerIterator getConformersBegin() const;

			ConstConformerIterator getConformersEnd() const;

		private:
			struct FragmentConfData;
			struct ConfCombinationData;

			typedef Util::ObjectPool<FragmentConfData> FragmentConfDataCache;
			typedef FragmentConfDataCache::SharedObjectPointer FragmentConfDataPtr;
		
			ConformerGeneratorImpl(const ConformerGeneratorImpl&);

			ConformerGeneratorImpl& operator=(const ConformerGeneratorImpl&);

			unsigned int generateConformers(const Chem::MolecularGraph& molgraph, const Chem::FragmentList& comps, bool struct_gen_only);
	
			void combineComponentConformers(const Chem::MolecularGraph& molgraph, bool have_full_ipt_coords);

			void calcConformerBounds(double min[3], double max[3], const Math::Vector3DArray& coords) const;

			unsigned int generateConformers(const Chem::MolecularGraph& molgraph, bool struct_gen_only, bool start_timer);

			unsigned int generateConformersSystematic(bool struct_gen_only);

			unsigned int generateConformersStochastic(bool struct_gen_only);

			void removeWorkingConfDuplicates();
			
			bool determineSamplingMode();

			void init(const Chem::MolecularGraph& molgraph, bool start_timer);

			bool generateHydrogenCoordsAndMinimize(ConformerData& conf_data);

			ConformerData::SharedPointer getInputCoordinates();

			void splitIntoTorsionFragments();
			
			bool setupMMFF94Parameters(unsigned int ff_type);
			
			unsigned int generateFragmentConformers(bool struct_gen_only);
			
			unsigned int generateFragmentConformerCombinations();
		
			void generateFragmentConformerCombinations(std::size_t frag_idx, double comb_energy);

			unsigned int generateOutputConformers(bool struct_gen_only);

			unsigned int selectOutputConformers(bool struct_gen_only, bool& );

			double getMMFF94BondLength(std::size_t atom1_idx, std::size_t atom2_idx) const;

			bool has3DCoordinates(const Chem::Atom& atom) const;

			static bool compareConfCombinationEnergy(const ConfCombinationData* comb1, 
													 const ConfCombinationData* comb2);
			static bool compareFragmentConfCount(const FragmentConfDataPtr& conf_data1, 
												 const FragmentConfDataPtr& conf_data2);

			void orderConformersByEnergy(ConformerDataArray& confs) const;

			unsigned int invokeCallbacks() const;
			bool timedout() const;

			bool rmsdConfSelectorAbortCallback() const;
			
			typedef std::vector<std::size_t> UIntArray;

			struct FragmentConfData
			{

				Chem::Fragment::SharedPointer fragment;
				ConformerDataArray            conformers;
				std::size_t                   lastConfIdx;
				bool                          haveInputCoords;

				void clear() {
					conformers.clear();
					fragment.reset();
				}
			};

			struct ConfCombinationData
			{

				UIntArray   confIndices;
				double      energy;
			};

			typedef Util::ObjectStack<ConfCombinationData> ConfCombinationDataCache;
			typedef Util::ObjectPool<ConformerData> ConformerDataCache;
			typedef std::vector<FragmentConfDataPtr> FragmentConfDataList;
			typedef ForceField::MMFF94InteractionData MMFF94InteractionData;
			typedef ForceField::MMFF94InteractionParameterizer MMFF94Parameterizer;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef std::vector<const Chem::Bond*> BondList;
			typedef std::vector<ConfCombinationData*> ConfCombinationDataList;
			typedef Math::BFGSMinimizer<Math::Vector3DArray::StorageType, double> BFGSMinimizer; 

			ConformerDataCache                   confDataCache;
			FragmentConfDataCache                fragConfDataCache;
			ConfCombinationDataCache             confCombDataCache;
			ConformerGeneratorSettings           settings;
			const Chem::MolecularGraph*          molGraph;
			ConformerDataArray                   workingConfs;
			ConformerDataArray                   tmpWorkingConfs;
			ConformerDataArray                   outputConfs;
			CallbackFunction                     abortCallback;
			CallbackFunction                     timeoutCallback;
			LogMessageCallbackFunction           logCallback;
			boost::timer::cpu_timer              timer;
			RMSDConformerSelector                confSelector;
			TorsionDriverImpl                    torDriver;
			FragmentAssemblerImpl                fragAssembler;
			DGStructureGenerator                 dgStructureGen;
			MMFF94Parameterizer                  mmff94Parameterizer;
			MMFF94InteractionData                mmff94Data;
			ForceFieldInteractionMask            mmff94InteractionMask;
			MMFF94GradientCalculator             mmff94GradientCalc;
			BFGSMinimizer                        energyMinimizer;
			Chem::Hydrogen3DCoordinatesGenerator hCoordsGen;
			BondList                             torDriveBonds;
			BondList                             fragSplitBonds;
			Chem::FragmentList                   fragments;
			Util::BitSet                         tmpBitSet;
			Util::BitSet                         coreAtomMask;
			Util::BitSet                         invertibleNMask;
			Util::BitSet                         fixedAtomConfigMask;
			FragmentConfDataList                 compConfData;
			FragmentConfDataList                 torFragConfData;
			ConfCombinationDataList              torFragConfCombData;
			UIntArray                            currConfComb;
			UIntArray                            parentAtomInds; 
			Math::Vector3DArray::StorageType     energyGradient;
			bool                                 inStochasticMode;
		};
    }
}

#endif // CDPL_CONFGEN_CONFORMERGENERATORIMPL_HPP
