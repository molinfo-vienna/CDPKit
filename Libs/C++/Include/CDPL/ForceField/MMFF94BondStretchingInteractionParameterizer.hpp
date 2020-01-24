/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94BondStretchingInteractionParameterizer.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94BondStretchingInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTIONPARAMETERIZER_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Bond;
	}
    
	namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_INTERACTION_PARAMETERIZATION
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94BondStretchingInteractionParameterizer
		{

		  public:
			typedef boost::shared_ptr<MMFF94BondStretchingInteractionParameterizer> SharedPointer;

			 MMFF94BondStretchingInteractionParameterizer();

			 MMFF94BondStretchingInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
														  MMFF94BondStretchingInteractionData& ia_data, 
														  bool strict);

			 void setFilterFunction(const InteractionFilterFunction2& func); 

			 void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func); 

			 void setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func); 

			 void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

			 void setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table);

			 void setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table);

			 void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

			 void parameterize(const Chem::MolecularGraph& molgraph, MMFF94BondStretchingInteractionData& ia_data, bool strict);

			 void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
								unsigned int& bond_type_idx, double& force_const, double& ref_length, bool strict) const;

		  private:
			 typedef MMFF94AtomTypePropertyTable::Entry AtomTypePropEntry;

			 void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
								unsigned int bond_type_idx, unsigned int atom1_type, unsigned int atom2_type, 
								double& force_const, double& ref_length) const;

			 double calcReferenceBondLength(const Chem::MolecularGraph& molgraph, const Chem::Bond& bond, 
											const AtomTypePropEntry& type1_prop_entry,
											const AtomTypePropEntry& type2_prop_entry) const;

			 InteractionFilterFunction2                            filterFunc;
			 MMFF94NumericAtomTypeFunction                         atomTypeFunc;	
			 MMFF94BondTypeIndexFunction                           bondTypeIdxFunc;	
			 MMFF94RingSetFunction                                 aromRingSetFunc;
			 MMFF94BondStretchingParameterTable::SharedPointer     paramTable;
			 MMFF94BondStretchingRuleParameterTable::SharedPointer ruleParamTable;
			 MMFF94AtomTypePropertyTable::SharedPointer            typePropTable;
		};			
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94BONDSTRETCHINGINTERACTIONPARAMETERIZER_HPP
