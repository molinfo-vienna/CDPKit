/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorImpl.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::FragmentConformerGeneratorImpl.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORIMPL_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORIMPL_HPP

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/DGStructureGenerator.hpp"
#include "CDPL/ConfGen/CallbackFunction.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
#include "CDPL/Chem/AutomorphismGroupSearch.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/VectorArrayAlignmentCalculator.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class FragmentConformerGeneratorImpl
		{

		  public:
			typedef ConformerDataArray::const_iterator ConstConformerIterator;

			FragmentConformerGeneratorImpl();
	
			FragmentConformerGeneratorSettings& getSettings();

			const FragmentConformerGeneratorSettings& getSettings() const;

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			unsigned int generate(const Chem::MolecularGraph& molgraph, unsigned int frag_type);

			std::size_t getNumConformers() const;

			ConformerData& getConformer(std::size_t idx);

			ConstConformerIterator getConformersBegin() const;

			ConstConformerIterator getConformersEnd() const;

			bool generateConformerFromInputCoordinates(const Chem::MolecularGraph& molgraph);

		  private:
			typedef Util::ObjectPool<ConformerData> ConformerDataCache;
			typedef std::vector<const Chem::Atom*> AtomList;

			FragmentConformerGeneratorImpl(const FragmentConformerGeneratorImpl&);

			FragmentConformerGeneratorImpl& operator=(const FragmentConformerGeneratorImpl&);

			void init(const Chem::MolecularGraph& molgraph);

			bool generateConformerFromInputCoordinates(ConformerDataArray& conf_array);

			bool setupForceField();

			void setupRandomConformerGeneration();

			unsigned int generateSingleConformer();
			unsigned int generateFlexibleRingConformers();

			void addSymmetryMappingConformers(const ConformerData& conf_data, double rmsd, std::size_t max_num_out_confs);
			void addMirroredConformer(const ConformerData& conf_data, double rmsd, std::size_t max_num_out_confs);

			unsigned int generateRandomConformer(ConformerData& conf);

			bool checkRMSD(const Math::Vector3DArray& conf_coords, double min_rmsd);
			
			ConformerData::SharedPointer getRingAtomCoordinates(const Math::Vector3DArray& conf_coords);

			void getRingAtomIndices();
			void getSymmetryMappings();
			void getNeighborHydrogens(const Chem::Atom& atom, AtomList& nbr_list) const;

			std::size_t calcNumSmallRingSystemConfSamples() const;
			std::size_t calcNumMacrocyclicRingSystemConfSamples() const;

			std::size_t getNumRotatableRingBonds(const Chem::MolecularGraph& molgraph) const;

			ConformerData::SharedPointer allocConformerData();

			unsigned int invokeCallbacks() const;
			bool timedout(std::size_t timeout) const;

			bool has3DCoordinates(const Chem::Atom& atom) const;

			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef ForceField::MMFF94InteractionParameterizer MMFF94InteractionParameterizer;
			typedef ForceField::MMFF94InteractionData MMFF94InteractionData;
			typedef Math::BFGSMinimizer<Math::Vector3DArray::StorageType, double> BFGSMinimizer; 
			typedef Math::VectorArrayAlignmentCalculator<Math::Vector3DArray> AlignmentCalculator;
			typedef std::vector<std::size_t> IndexList;

			ConformerDataCache                       confDataCache;
			CallbackFunction                         abortCallback;
			CallbackFunction                         timeoutCallback;
			boost::timer::cpu_timer                  timer;
			const Chem::MolecularGraph*              molGraph;
			std::size_t                              numAtoms;
			MMFF94InteractionParameterizer           mmff94Parameterizer;
			MMFF94InteractionData                    mmff94Data;
			MMFF94EnergyCalculator                   mmff94EnergyCalc;
			MMFF94GradientCalculator                 mmff94GradientCalc;
			BFGSMinimizer                            energyMinimizer;
			DGStructureGenerator                     dgStructGen;
			Chem::Hydrogen3DCoordinatesGenerator     hCoordsGen;
			Chem::AutomorphismGroupSearch            symMappingSearch;
			AlignmentCalculator                      alignmentCalc;
			Math::Vector3DArray::StorageType         energyGradient;
			IndexList                                ringAtomIndices;
			IndexList                                symMappings;
			AtomList                                 nbrHydrogens1;
			AtomList                                 nbrHydrogens2;
			Chem::Fragment                           symMappingSearchMolGraph;
			Util::BitSet                             coreAtomMask;
			ConformerDataArray                       ringAtomCoords;
			ConformerDataArray                       outputConfs;
			ConformerDataArray                       workingConfs;
			FragmentConformerGeneratorSettings       settings;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORIMPL_HPP
