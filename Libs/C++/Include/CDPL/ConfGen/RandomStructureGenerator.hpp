/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RandomStructureGenerator.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::RandomStructureGenerator.
 */

#ifndef CDPL_CONFGEN_RANDOMSTRUCTUREGENERATOR_HPP
#define CDPL_CONFGEN_RANDOMSTRUCTUREGENERATOR_HPP

#include <cstddef>

#include <boost/timer/timer.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/DGStructureGenerator.hpp"
#include "CDPL/ConfGen/RandomStructureGeneratorSettings.hpp"
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

		class CDPL_CONFGEN_API RandomStructureGenerator
		{

		public:
	
			RandomStructureGenerator();
	
			RandomStructureGeneratorSettings& getSettings();

			const RandomStructureGeneratorSettings& getSettings() const;

			unsigned int setup(const Chem::MolecularGraph& molgraph);

			unsigned int generate(Math::Vector3DArray& coords);

			double getEnergy() const;

		private:
			RandomStructureGenerator(const RandomStructureGenerator&);

			RandomStructureGenerator& operator=(const RandomStructureGenerator&);

			bool timeoutExceeded() const;
			bool has3DCoordinates(const Chem::Atom& atom) const;

			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;
			typedef ForceField::MMFF94GradientCalculator<double> MMFF94GradientCalculator;
			typedef Math::BFGSMinimizer<Math::Vector3DArray::StorageType, double> BFGSMinimizer; 
		
			const Chem::MolecularGraph*                molGraph;
			boost::timer::cpu_timer                    timer;
			double                                     energy;
			ForceField::MMFF94InteractionParameterizer mmff94Parameterizer;
			ForceField::MMFF94InteractionData          mmff94Data;
			MMFF94EnergyCalculator                     mmff94EnergyCalc;
			MMFF94GradientCalculator                   mmff94GradientCalc;
			BFGSMinimizer                              energyMinimizer;
			DGStructureGenerator                       dgStructGen;
			Chem::Hydrogen3DCoordinatesGenerator       hCoordsGen;
			Math::Vector3DArray::StorageType           gradient;
			RandomStructureGeneratorSettings           settings;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_RANDOMSTRUCTUREGENERATOR_HPP
