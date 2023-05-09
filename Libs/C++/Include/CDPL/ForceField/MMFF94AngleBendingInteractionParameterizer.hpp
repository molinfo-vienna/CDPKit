/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94AngleBendingInteractionParameterizer.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94AngleBendingInteractionParameterizer.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTIONPARAMETERIZER_HPP
#define CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTIONPARAMETERIZER_HPP

#include <vector>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94PropertyFunctions.hpp"
#include "CDPL/ForceField/InteractionFilterFunctions.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingRuleParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingParameterTable.hpp"
#include "CDPL/ForceField/MMFF94AtomTypePropertyTable.hpp"
#include "CDPL/ForceField/MMFF94PrimaryToParameterAtomTypeMap.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;
	}

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94AngleBendingInteractionParameterizer
		{

		  public:
			typedef boost::shared_ptr<MMFF94AngleBendingInteractionParameterizer> SharedPointer;

			MMFF94AngleBendingInteractionParameterizer();

			MMFF94AngleBendingInteractionParameterizer(const Chem::MolecularGraph& molgraph, 
													   MMFF94AngleBendingInteractionData& ia_data,
													   bool strict);

			void setFilterFunction(const InteractionFilterFunction3& func); 

			void setAtomTypeFunction(const MMFF94NumericAtomTypeFunction& func); 

			void setBondTypeIndexFunction(const MMFF94BondTypeIndexFunction& func); 

			void setAromaticRingSetFunction(const MMFF94RingSetFunction& func);

			void setBondStretchingParameterTable(const MMFF94BondStretchingParameterTable::SharedPointer& table);

			void setBondStretchingRuleParameterTable(const MMFF94BondStretchingRuleParameterTable::SharedPointer& table);

			void setAngleBendingParameterTable(const MMFF94AngleBendingParameterTable::SharedPointer& table);

			void setAtomTypePropertyTable(const MMFF94AtomTypePropertyTable::SharedPointer& table);

			void setParameterAtomTypeMap(const MMFF94PrimaryToParameterAtomTypeMap::SharedPointer& map);

			void parameterize(const Chem::MolecularGraph& molgraph, MMFF94AngleBendingInteractionData& ia_data, bool strict);

		  private:
			void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, const Chem::Atom& ctr_atom, 
							   const Chem::Atom& term_atom2, const Chem::Bond& term_atom1_bnd, const Chem::Bond& term_atom2_bnd,
							   unsigned int& angle_type_idx, bool& linear, double& force_const, double& ref_angle, bool strict) const;

			void getParameters(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, unsigned int term_atom1_type, const Chem::Atom& ctr_atom, 
							   unsigned int ctr_atom_type, const Chem::Atom& term_atom2, unsigned int term_atom2_type, const Chem::Bond& term_atom1_bnd,
							   const Chem::Bond& term_atom2_bnd, unsigned int& angle_type_idx, bool& linear, double& force_const, double& ref_angle, bool strict) const;

			std::size_t getSizeOfContaining3Or4Ring(const Chem::MolecularGraph& molgraph, const Chem::Atom& term_atom1, 
													const Chem::Atom& ctr_atom, const Chem::Atom& term_atom2) const;

			/**
			 * \brief Returns the angle type index. 
			 *
			 * The angle-bending parameters employ angle type indices ATIJK ranging between 0 and 8. 
			 * Their meanings are as defined below:
			 * 
			 * ATIJK Structural significance
			 * ---------------------------------------------------------------------------
			 * 0 The angle i-j-k is a "normal" bond angle
			 * 1 Either bond i-j or bond j-k has a bond type of 1
			 * 2 Both i-j and j-k have bond types of 1; the sum is 2
			 * 3 The angle occurs in a three-membered ring
			 * 4 The angle occurs in a four-membered ring 
			 * 5 Is in a three-membered ring and the sum of the bond types is 1
			 * 6 Is in a three-membered ring and the sum of the bond types is 2
			 * 7 Is in a four-membered ring and the sum of the bond types is 1
			 * 8 Is in a four-membered ring and the sum of the bond types is 2
			 * 
			 * \param bond1 The first bond defining the angle.
			 * \param bond2 The second bond defining the angle.
			 * \param r_size The size of the ring the two bonds are a member of.
			 * \return The angle type index.
			 */
			unsigned int getAngleTypeIndex(const Chem::Bond& bond1, const Chem::Bond& bond2, std::size_t r_size) const;

			typedef std::vector<const Chem::Atom*> AtomList;
			typedef std::vector<const Chem::Bond*> BondList;

			InteractionFilterFunction3                            filterFunc;
			MMFF94NumericAtomTypeFunction                         atomTypeFunc;	
			MMFF94BondTypeIndexFunction                           bondTypeIdxFunc;	
			MMFF94AngleBendingParameterTable::SharedPointer       paramTable;
			MMFF94AtomTypePropertyTable::SharedPointer            typePropTable;
			MMFF94PrimaryToParameterAtomTypeMap::SharedPointer    paramTypeMap;
			MMFF94BondStretchingInteractionParameterizer          bsParameterizer;
			AtomList                                              nbrAtoms;
			BondList                                              nbrBonds;
		};			
    }
}

#endif // CDPL_FORCEFIELD_MMFF94ANGLEBENDINGINTERACTIONPARAMETERIZER_HPP
