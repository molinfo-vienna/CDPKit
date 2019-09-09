/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Random3DCoordinatesGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::Random3DCoordinatesGenerator.
 */

#ifndef CDPL_CONFGEN_RANDOM3DCOORDINATESGENERATOR_HPP
#define CDPL_CONFGEN_RANDOM3DCOORDINATESGENERATOR_HPP

#include <cstddef>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/Raw3DCoordinatesGenerator.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/Chem/Hydrogen3DCoordinatesGenerator.hpp"
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

		class CDPL_CONFGEN_API Random3DCoordinatesGenerator
		{

		public:
			static const unsigned int DEF_FORCE_FIELD_TYPE                = ForceFieldType::MMFF94S_NO_ESTAT;
			static const std::size_t  DEF_MAX_NUM_STRUCTURE_GEN_TRIALS    = 10;
			static const std::size_t  DEF_MAX_NUM_MINIMIZATION_STEPS      = 0;
			static const std::size_t  DEF_TIMEOUT                         = 600 * 1000;
			static const double       DEF_MINIMIZATION_STOP_GRADIENT_NORM;

			Random3DCoordinatesGenerator();
	
			void regardAtomConfiguration(bool regard);

			bool atomConfigurationRegarded() const;

			void regardBondConfiguration(bool regard);

			bool bondConfigurationRegarded() const;

			void setMaxNumStructureGenerationTrials(std::size_t max_num);

			std::size_t getMaxNumStructureGenerationTrials() const;

			void setMaxNumMinimizationSteps(std::size_t max_num);

			std::size_t getMaxNumMinimizationSteps() const;

			void setMinimizationStopGradientNorm(double grad_norm);

			double getMinimizationStopGradientNorm() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

			void performStrictAtomTyping(bool strict);

			bool strictAtomTypingPerformed() const;
	
			void setForceFieldType(unsigned int type);
	
			unsigned int getForceFieldType() const;

			unsigned int setup(const Chem::MolecularGraph& molgraph);

			unsigned int generate(Math::Vector3DArray& coords);

			double getEnergy() const;

		private:
			Random3DCoordinatesGenerator(const Random3DCoordinatesGenerator&);

			Random3DCoordinatesGenerator& operator=(const Random3DCoordinatesGenerator&);

			bool timeoutExceeded() const;
			bool has3DCoordinates(const Chem::Atom& atom) const;

			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef Math::BFGSMinimizer<Math::Vector3DArray::StorageType, double> BFGSMinimizer; 
		
			const Chem::MolecularGraph*                molGraph;
			std::size_t                                maxNumStructGenTrials;
			std::size_t                                maxNumMinSteps;
			double                                     minStopGradNorm;
			std::size_t                                timeout;
			unsigned int                               forceFieldType;
			boost::timer::cpu_timer                    timer;
			double                                     energy;
			ForceField::MMFF94InteractionParameterizer mmff94Parameterizer;
			ForceField::MMFF94InteractionData          mmff94Data;
			MMFF94EnergyCalculator                     mmff94EnergyCalc;
			MMFF94GradientCalculator                   mmff94GradientCalc;
			BFGSMinimizer                              energyMinimizer;
			Raw3DCoordinatesGenerator                  rawCoordsGenerator;
			Chem::Hydrogen3DCoordinatesGenerator       hCoordsGenerator;
			Math::Vector3DArray::StorageType           gradient;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_RANDOM3DCOORDINATESGENERATOR_HPP
