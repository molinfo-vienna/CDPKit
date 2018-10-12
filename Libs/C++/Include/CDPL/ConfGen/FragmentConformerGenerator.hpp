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
#include <utility>
#include <vector>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/Raw3DCoordinatesGenerator.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/ForceField/MMFF94GradientCalculator.hpp"
#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/VectorArray.hpp"


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
			static const std::size_t  DEF_TIMEOUT                         = 30 * 1000;
			static const std::size_t  DEF_RING_CONF_RETRIAL_FACTOR        = 20;
			static const double       DEF_MINIMIZATION_STOP_GRADIENT_NORM;
			static const double       DEF_ENERGY_WINDOW;
			static const double       DEF_MIN_RMSD;

			FragmentConformerGenerator();
	
			void setMaxNumStructureGenerationTrials(std::size_t max_num);

			std::size_t getMaxNumStructureGenerationTrials() const;

			void setMaxNumMinimizationSteps(std::size_t max_num);

			std::size_t getMaxNumMinimizationSteps() const;

			void setMinimizationStopGradientNorm(double grad_norm);

			double getMinimizationStopGradientNorm() const;

			void setTimeout(std::size_t mil_secs);

			std::size_t getTimeout() const;

			void reuseExistingCoordinates(bool reuse);

			bool existingCoordinatesReused() const;

			void setEnergyWindow(double win_size);

			double getEnergyWindow() const;

			void setRingConformerRetrialFactor(std::size_t factor);

			std::size_t getRingConformerRetrialFactor() const;

			void setMinRMSD(double min_rmsd);

			double getMinRMSD() const;

			void generate(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data, unsigned int frag_type);

			std::size_t getNumConformations() const;

			const Math::Vector3DArray& getConformation(std::size_t idx) const;

			Math::Vector3DArray& getConformation(std::size_t idx);

			double getConformerEnergy(std::size_t idx) const;

		  private:
			void generateSingleConformer(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

			void generateMultipleConformers(const Chem::MolecularGraph& molgraph, const ForceField::MMFF94InteractionData& ia_data);

			bool timeoutExceeded() const;

			void init();

			Math::Vector3DArray::SharedPointer allocCoordinatesArray(std::size_t num_atoms);

			void freeCoordinatesArray(const Math::Vector3DArray::SharedPointer& coords_ptr);

			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef Math::BFGSMinimizer<Math::Vector3DArray, double> BFGSMinimizer; 
			typedef std::pair<double, Math::Vector3DArray::SharedPointer> Conformation;
			typedef std::vector<Conformation> ConformerArray;
			typedef std::vector<Math::Vector3DArray::SharedPointer> CoordinatesArrayCache;

			std::size_t                    maxNumStructGenTrials;
			std::size_t                    maxNumMinSteps;
			double                         minStopGradNorm;
			std::size_t                    timeout;
			bool                           reuseExistingCoords;
			double                         eWindow;
			std::size_t                    ringConfRetrialFact;
			double                         minRMSD;
			boost::timer::cpu_timer        timer;
			MMFF94EnergyCalculator         mmff94EnergyCalc;
			MMFF94GradientCalculator       mmff94GradientCalc;
			BFGSMinimizer                  energyMinimizer;
			Raw3DCoordinatesGenerator      rawCoordsGenerator;
			Math::Vector3DArray            gradient;
			ConformerArray                 conformers;
			CoordinatesArrayCache          coordsArrayCache;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_FRAGMENTCONFORMERGENERATOR_HPP
