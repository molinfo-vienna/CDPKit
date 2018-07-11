/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94ElectrostaticInteractionAnalyzer.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94ElectrostaticInteractionAnalyzer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONANALYZER_HPP
#define CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONANALYZER_HPP

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionList.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctionWrappers.hpp"
#include "CDPL/ForceField/InteractionFilterFunctionWrappers.hpp"
#include "CDPL/ForceField/TopologicalAtomDistanceFunctionWrapper.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_INTERACTION_ANALYSIS
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94ElectrostaticInteractionAnalyzer
		{

		  public:
			static const double DEF_DISTANCE_EXPONENT;
			static const double DEF_DIELECTRIC_CONSTANT;

			MMFF94ElectrostaticInteractionAnalyzer();

			MMFF94ElectrostaticInteractionAnalyzer(const Chem::MolecularGraph& molgraph, 
												   MMFF94ElectrostaticInteractionList& iactions);

			void setFilterFunction(const InteractionFilterFunction2& func); 

			void setChargeFunction(const MMFF94AtomChargeFunction& func); 

			void setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func); 

			void setDielectricConstant(double de_const);

			void setDistanceExponent(double dist_expo);

			void analyze(const Chem::MolecularGraph& molgraph, MMFF94ElectrostaticInteractionList& iactions);

		  private:
			InteractionFilterFunction2      filterFunc;
			MMFF94AtomChargeFunction        chargeFunc;
			TopologicalAtomDistanceFunction distFunc;
			double                          deConst;
			double                          distExpo;
		};			
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONANALYZER_HPP
