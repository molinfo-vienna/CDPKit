/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsInteractionParameterizer.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::ForceField::MMFF94VanDerWaalsInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTIONPARAMETERIZER_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionData.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/TopologicalAtomDistanceFunction.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsParameterTable.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
	}

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94VanDerWaalsInteractionParameterizer
		{

		  public:
			typedef boost::shared_ptr<MMFF94VanDerWaalsInteractionParameterizer> SharedPointer;

			MMFF94VanDerWaalsInteractionParameterizer();

			MMFF94VanDerWaalsInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
													  MMFF94VanDerWaalsInteractionData& ia_data,
													  bool strict);

			void setFilterFunction(const InteractionFilterFunction2& func); 

			void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func); 

			void setTopologicalDistanceFunction(const TopologicalAtomDistanceFunction& func); 

			void setVanDerWaalsParameterTable(const MMFF94VanDerWaalsParameterTable::SharedPointer& table);

			void parameterize(const Chem::MolecularGraph& molgraph, MMFF94VanDerWaalsInteractionData& ia_data, bool strict);

		  private:
			InteractionFilterFunction2                     filterFunc;
			MMFF94NumericAtomTypeFunction                  typeFunc;
			TopologicalAtomDistanceFunction                distFunc;
			MMFF94VanDerWaalsParameterTable::SharedPointer paramTable;
		};			
    }
}

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTIONPARAMETERIZER_HPP
