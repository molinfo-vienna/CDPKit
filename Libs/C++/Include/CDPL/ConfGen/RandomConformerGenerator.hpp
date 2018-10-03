/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomConformerGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::RandomConformerGenerator.
 */

#ifndef CDPL_CONFGEN_RANDOMCONFORMERGENERATOR_HPP
#define CDPL_CONFGEN_RANDOMCONFORMERGENERATOR_HPP

#include <cstddef>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/Raw3DStructureGenerator.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		/**
		 * \addtogroup CDPL_CONFGEN_GENERATORS
		 * @{
		 */

		class CDPL_CONFGEN_API RandomConformerGenerator
		{

		public:
			static const std::size_t DEF_MAX_NUM_TRIALS                  = 10;
			static const std::size_t DEF_MAX_NUM_NINIMIZATION_STEPS      = 0;
			static const std::size_t DEF_TIMEOUT                         = 600 * 1000;
			static const double      DEF_MINIMIZATION_STOP_GRADIENT_NORM;

			enum Status
			{

			    SUCCESS,
			    UNINITIALIZED,
				MAX_NUM_TRIALS_EXCEEDED,
				MINIMIZATION_ERROR,
				TIMEOUT_EXCEEDED
			};

			RandomConformerGenerator();

			void regardAtomConfiguration(bool regard);

			bool atomConfigurationRegarded() const;

			void regardBondConfiguration(bool regard);

			bool bondConfigurationRegarded() const;

			void setMaxNumTrials(std::size_t max_num);

			std::size_t getMaxNumTrials() const;

			void setMaxNumMinimizationSteps(std::size_t max_num);

			std::size_t getMaxNumMinimizationSteps() const;

			void setMinimizationStopGradientNorm(double grad_norm);

			double getMinimizationStopGradientNorm() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

			void performStrictMMFF94AtomTyping(bool strict);

			bool strictMMFF94AtomTypingPerformed() const;

			void useDynamicMMFF94Parameters();

			void useStaticMMFF94Parameters();
				
			void enableElectrostaticMMFF94Terms(bool enable);
	
			bool electrostaticMMFF94TermsEnabled() const;
		
			void setup(const Chem::MolecularGraph& molgraph);

			Status generate(Math::Vector3DArray& coords);

			double getEnergy() const;

		private:
			bool timeoutExceeded() const;

			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef Math::BFGSMinimizer<Math::Vector3DArray, double> BFGSMinimizer; 

			const Chem::MolecularGraph*                molGraph;
			std::size_t                                maxNumTrials;
			std::size_t                                maxNumMinSteps;
			double                                     minStopGradNorm;
			std::size_t                                timeout;
			bool                                       elstaticMMFF94Terms;
			boost::timer::cpu_timer                    timer;
			double                                     energy;
			ForceField::MMFF94InteractionParameterizer mmff94Parameterizer;
			ForceField::MMFF94InteractionData          mmff94ParamData;
			MMFF94EnergyCalculator                     mmff94EnergyCalc;
			MMFF94GradientCalculator                   mmff94GradientCalc;
			BFGSMinimizer                              energyMinimizer;
			Raw3DStructureGenerator                    raw3DStructureGen;
			Math::Vector3DArray                        gradient;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_RANDOMCONFORMERGENERATOR_HPP
