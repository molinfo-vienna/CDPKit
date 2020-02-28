/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureGeneratorSettings.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::StructureGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_STRUCTUREGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_STRUCTUREGENERATORSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/FragmentConformerGeneratorSettings.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_DATA_STRUCTURES
		 * @{
		 */

		class CDPL_CONFGEN_API StructureGeneratorSettings
		{

		  public:
			static const StructureGeneratorSettings DEFAULT;

			StructureGeneratorSettings();

			void setGenerationMode(unsigned int mode);

			unsigned int getGenerationMode() const;

			void generateCoordinatesFromScratch(bool generate);
	
			bool generateCoordinatesFromScratch() const;
		
			void sampleAngleToleranceRanges(bool sample);
				
			bool sampleAngleToleranceRanges() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

			void setForceFieldType(unsigned int type);
	    
			unsigned int getForceFieldType() const;
			
			void strictForceFieldParameterization(bool strict);

			bool strictForceFieldParameterization() const;

			void setDielectricConstant(double de_const);

			double getDielectricConstant() const;

			void setDistanceExponent(double exponent);

			double getDistanceExponent() const;

			void setMaxNumRefinementIterations(std::size_t max_iter);

			std::size_t getMaxNumRefinementIterations() const;

			void setRefinementStopGradient(double grad_norm);

			double getRefinementStopGradient() const;

			void setMaxNumSampledConformers(std::size_t max_num);

			std::size_t getMaxNumSampledConformers() const;

			void setConvergenceIterationCount(std::size_t count);

			std::size_t getConvergenceIterationCount() const;

			void setMacrocycleRotorBondCountThreshold(std::size_t min_count);

			std::size_t getMacrocycleRotorBondCountThreshold() const;
		
			FragmentConformerGeneratorSettings& getFragmentBuildSettings();

			const FragmentConformerGeneratorSettings& getFragmentBuildSettings() const;

		  private:
			unsigned int                       generationMode;
			bool                               fromScratch;
			bool                               sampleTolRanges;
			std::size_t                        timeout;
			unsigned int                       forceFieldType;
			bool                               strictParam;
			double                             dielectricConst;
			double                             distExponent;
			std::size_t                        maxNumRefIters;
			double                             refStopGrad;
			std::size_t                        maxNumSampledConfs;
			std::size_t                        convIterCount;
			std::size_t                        mcRotorBondCountThresh;
			FragmentConformerGeneratorSettings fragBuildSettings;
		};
	};

	/**
	 * @}
	 */
}

#endif // CDPL_CONFGEN_STRUCTUREGENERATORSETTINGS_HPP
