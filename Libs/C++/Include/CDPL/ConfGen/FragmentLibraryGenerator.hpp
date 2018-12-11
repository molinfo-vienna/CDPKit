/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentLibraryGenerator.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::ConfGen::FragmentLibraryGenerator.
 */

#ifndef CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP
#define CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP

#include <boost/function.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentLibrary.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/ConfGen/FragmentList.hpp"
#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Chem/Molecule.hpp"


namespace CDPL 
{

    namespace ConfGen
    {

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		/**
		 * \brief FragmentLibraryGenerator.
		 */
		class CDPL_CONFGEN_API FragmentLibraryGenerator
		{

		  public:
			static const unsigned int DEF_FORCE_FIELD_TYPE = ForceFieldType::MMFF94S_NO_ESTAT;

			typedef boost::function4<void, Base::uint64, const Chem::MolecularGraph&, bool, std::size_t> ProcessingResultCallbackFunction;
			typedef boost::function2<bool, const Chem::MolecularGraph&, const std::string&> ProcessingErrorCallbackFunction;
			typedef FragmentConformerGenerator::ProgressCallbackFunction ProgressCallbackFunction;

			FragmentLibraryGenerator();

			FragmentLibraryGenerator(const FragmentLibrary::SharedPointer& lib);

			void setFragmentLibrary(const FragmentLibrary::SharedPointer& lib);

			const FragmentLibrary::SharedPointer& getFragmentLibrary() const;

			void setForceFieldType(unsigned int type);
	    
			unsigned int getForceFieldType() const;

			void performStrictAtomTyping(bool strict);

			bool strictAtomTypingPerformed() const;

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

			void setProcessingResultCallback(const ProcessingResultCallbackFunction& func);

			const ProcessingResultCallbackFunction& getProcessingResultCallback();
	
			void setProcessingErrorCallback(const ProcessingErrorCallbackFunction& func);

			const ProcessingErrorCallbackFunction& getProcessingErrorCallback();

			void setProgressCallback(const ProgressCallbackFunction& func);

			const ProgressCallbackFunction& getProgressCallback() const;

			void process(const Chem::MolecularGraph& molgraph);
	
		  private:
			FragmentLibraryGenerator(const FragmentLibraryGenerator&);

			FragmentLibraryGenerator& operator=(const FragmentLibraryGenerator&);

			void processFragment(const Chem::MolecularGraph& frag);

			Chem::Molecule::SharedPointer addNewLibraryEntry(const Chem::MolecularGraph& frag);

			void removeNewLibraryEntry() const;

			FragmentLibrary::SharedPointer                  fragLib;
			unsigned int                                    forceFieldType;
			ProcessingResultCallbackFunction                resultCallback;
			ProcessingErrorCallbackFunction                 errorCallback;
			FragmentLibraryEntry                            fragLibEntry;
			FragmentList                                    fragList;
			FragmentConformerGenerator                      fragConfGen;
			ForceField::MMFF94InteractionParameterizer      mmff94Parameterizer;
			ForceField::MMFF94InteractionData               mmff94ParamData;
			Chem::SmallestSetOfSmallestRings::SharedPointer fragSSSR;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTLIBRARYGENERATOR_HPP
