/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94ElectrostaticInteractionParameterizer.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94ElectrostaticInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONPARAMETERIZER_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionData.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/TopologicalAtomDistanceFunction.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_INTERACTION_PARAMETERIZATION
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94ElectrostaticInteractionParameterizer
		{

		  public:
			static const double DEF_DISTANCE_EXPONENT;
			static const double DEF_DIELECTRIC_CONSTANT;
			static const double DIELECTRIC_CONSTANT_WATER;

			typedef boost::shared_ptr<MMFF94ElectrostaticInteractionParameterizer> SharedPointer;

			MMFF94ElectrostaticInteractionParameterizer();

			MMFF94ElectrostaticInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
														MMFF94ElectrostaticInteractionData& ia_data,
														bool strict);

			void setFilterFunction(const InteractionFilterFunction2& func); 

			void setAtomChargeFunction(const MMFF94AtomChargeFunction& func); 

			void setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func); 

			void setDielectricConstant(double de_const);

			void setDistanceExponent(double dist_expo);

			void parameterize(const Chem::MolecularGraph& molgraph, MMFF94ElectrostaticInteractionData& ia_data, bool strict);

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

#endif // CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTIONPARAMETERIZER_HPP
