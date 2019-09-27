/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomStructureGeneratorSettings.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::RandomStructureGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_RANDOMSTRUCTUREGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_RANDOMSTRUCTUREGENERATORSETTINGS_HPP

#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_DATA_STRUCTURES
		 * @{
		 */

		class CDPL_CONFGEN_API RandomStructureGeneratorSettings
		{

		public:
			static const RandomStructureGeneratorSettings DEFAULT;

			RandomStructureGeneratorSettings();

			void regardAtomConfiguration(bool regard);

			bool regardAtomConfiguration() const;

			void regardBondConfiguration(bool regard);

			bool regardBondConfiguration() const;

			void setMaxNumStructureGenerationTrials(std::size_t max_num);

			std::size_t getMaxNumStructureGenerationTrials() const;

			void setMaxNumRefinementIterations(std::size_t max_iter);

			std::size_t getMaxNumRefinementIterations() const;

			void setRefinementStopGradient(double grad_norm);

			double getRefinementStopGradient() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

			void strictForceFieldParameterization(bool strict);

			bool strictForceFieldParameterization() const;
	
			void setForceFieldType(unsigned int type);
	
			unsigned int getForceFieldType() const;

		  private:
			bool         atomConfig;
			bool         bondConfig;
			std::size_t  maxNumStructGenTrials;
			std::size_t  maxNumRefIters;
			double       refStopGrad;
			std::size_t  timeout;
			bool         strictParam;
			unsigned int forceFieldType;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_RANDOMSTRUCTUREGENERATORSETTINGS_HPP
