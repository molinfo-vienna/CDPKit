/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentConformerGeneratorSettings.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::FragmentConformerGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		class CDPL_CONFGEN_API FragmentConformerGeneratorSettings
		{

		  public:
			static const FragmentConformerGeneratorSettings DEFAULT;

			FragmentConformerGeneratorSettings();
	
			virtual ~FragmentConformerGeneratorSettings() {}

			void setMaxNumStructureGenerationTrials(std::size_t max_num);

			std::size_t getMaxNumStructureGenerationTrials() const;

			void setForceFieldType(unsigned int type);
	    
			unsigned int getForceFieldType() const;

			void strictParameterization(bool strict);

			bool strictParameterization() const;

			void setMaxNumRefinementIterations(std::size_t max_num);

			std::size_t getMaxNumRefinementIterations() const;

			void setRefinementStopGradient(double grad_norm);

			double getRefinementStopGradient() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

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

		  private:
			std::size_t  maxNumStructGenTrials;
			std::size_t  maxNumMinIters;
			std::size_t  maxNumOutputConfs;
			double       minStopGrad;
			std::size_t  timeout;
			double       eWindow;
			std::size_t  ringConfTrialFactor;
			std::size_t  maxNumRingConfTrials;
			double       minRMSD;
			unsigned int forceFieldType;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATORSETTINGS_HPP
