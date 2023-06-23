/* 
 * MMFF94OutOfPlaneBendingInteractionParameterizer.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94OutOfPlaneBendingInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTIONPARAMETERIZER_HPP

#include <vector>
#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"


namespace CDPL 
{
	
	namespace Chem
	{

		class MolecularGraph;
		class Atom;
	}

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94OutOfPlaneBendingInteractionParameterizer
		{

		  public:
			typedef std::shared_ptr<MMFF94OutOfPlaneBendingInteractionParameterizer> SharedPointer;

			MMFF94OutOfPlaneBendingInteractionParameterizer();

			MMFF94OutOfPlaneBendingInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
															MMFF94OutOfPlaneBendingInteractionData& ia_data,
															bool strict);

			void setFilterFunction(const InteractionFilterFunction4& func); 

			void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func); 

			void setOutOfPlaneBendingParameterTable(const MMFF94OutOfPlaneBendingParameterTable::SharedPointer& table);

			void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

			void setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

			void parameterize(const Chem::MolecularGraph& molgraph, MMFF94OutOfPlaneBendingInteractionData& ia_data, bool strict);

		  private:
			typedef std::vector<const Chem::Atom*> AtomList;
			
			double getForceConstant(const Chem::MolecularGraph& molgraph, unsigned int ctr_atom_type, 
									std::size_t ctr_atom_idx, const AtomList& nbr_atoms, bool strict) const;

			double getForceConstant(const Chem::MolecularGraph& molgraph, unsigned int ctr_atom_type, 
									std::size_t ctr_atom_idx, unsigned int nbr_atom_types[3], const AtomList& nbr_atoms) const;

			InteractionFilterFunction4                            filterFunc;
			MMFF94NumericAtomTypeFunction                         atomTypeFunc;	
			MMFF94OutOfPlaneBendingParameterTable::SharedPointer  paramTable;
			MMFF94AtomTypePropertyTable::SharedPointer            typePropTable;
			MMFF94PrimaryToParameterAtomTypeMap::SharedPointer    paramTypeMap;
			AtomList                                              nbrAtoms;
		};			
    }
}

#endif // CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTIONPARAMETERIZER_HPP
