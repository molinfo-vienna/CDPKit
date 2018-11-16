/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Bond instances.
 */

#ifndef CDPL_CHEM_BONDFUNCTIONS_HPP
#define CDPL_CHEM_BONDFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/AtomPriorityFunctionWrapper.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class StereoDescriptor;

		/**
		 * \addtogroup CDPL_CHEM_BOND_FUNCTIONS
		 * @{
		 */

		CDPL_CHEM_API std::size_t getOrder(const Bond& bond);

		CDPL_CHEM_API void setOrder(Bond& bond, std::size_t order);

		CDPL_CHEM_API void clearOrder(Bond& bond);
	
		CDPL_CHEM_API bool hasOrder(const Bond& bond);


		CDPL_CHEM_API bool getRingFlag(const Bond& bond);
	
		CDPL_CHEM_API void setRingFlag(Bond& bond, bool in_ring);

		CDPL_CHEM_API void clearRingFlag(Bond& bond);
	
		CDPL_CHEM_API bool hasRingFlag(const Bond& bond);


		CDPL_CHEM_API bool isInRing(const Bond& Bond, const MolecularGraph& molgraph);

		CDPL_CHEM_API bool isInRingOfSize(const Bond& bond, const MolecularGraph& molgraph, std::size_t size);

		CDPL_CHEM_API std::size_t getNumContainingSSSRRings(const Bond& bond, const MolecularGraph& molgraph);


		CDPL_CHEM_API bool isInFragmentOfSize(const Bond& bond, const FragmentList& frag_list, std::size_t size);

		CDPL_CHEM_API std::size_t getSizeOfSmallestContainingFragment(const Bond& bond, const FragmentList& frag_list);

		CDPL_CHEM_API std::size_t getSizeOfLargestContainingFragment(const Bond& bond, const FragmentList& frag_list);

		CDPL_CHEM_API std::size_t getNumContainingFragments(const Bond& bond, const FragmentList& frag_list);

		CDPL_CHEM_API void getContainingFragments(const Bond& bond, const FragmentList& frag_list, FragmentList& cont_frag_list);


		CDPL_CHEM_API bool getAromaticityFlag(const Bond& bond);

		CDPL_CHEM_API void setAromaticityFlag(Bond& bond, bool aromatic);

		CDPL_CHEM_API void clearAromaticityFlag(Bond& bond);
	
		CDPL_CHEM_API bool hasAromaticityFlag(const Bond& bond);


		CDPL_CHEM_API unsigned int get2DStereoFlag(const Bond& bond);

		CDPL_CHEM_API void set2DStereoFlag(Bond& bond, unsigned int flag);

		CDPL_CHEM_API void clear2DStereoFlag(Bond& bond);
	
		CDPL_CHEM_API bool has2DStereoFlag(const Bond& bond);


		CDPL_CHEM_API unsigned int getCIPConfiguration(const Bond& bond);
	
		CDPL_CHEM_API void setCIPConfiguration(Bond& bond, unsigned int config);

		CDPL_CHEM_API void clearCIPConfiguration(Bond& bond);
	
		CDPL_CHEM_API bool hasCIPConfiguration(const Bond& bond);

		CDPL_CHEM_API unsigned int calcCIPConfiguration(const Bond& bond, const MolecularGraph& molgraph);

		CDPL_CHEM_API unsigned int calcCIPConfiguration(const Bond& bond, const MolecularGraph& molgraph, const AtomPriorityFunction& cip_pri_func);


		CDPL_CHEM_API const StereoDescriptor& getStereoDescriptor(const Bond& bond);

		CDPL_CHEM_API void setStereoDescriptor(Bond& bond, const StereoDescriptor& descr);

		CDPL_CHEM_API void clearStereoDescriptor(Bond& bond);
	
		CDPL_CHEM_API bool hasStereoDescriptor(const Bond& bond);

		CDPL_CHEM_API StereoDescriptor calcStereoDescriptor(const Bond& bond, const MolecularGraph& molgraph, std::size_t dim = 1, 
															std::size_t min_ring_size = 8, bool check_order = true);

		CDPL_CHEM_API unsigned int calcBondConfiguration(const Bond& bond, const MolecularGraph& molgraph, const StereoDescriptor& descr,
														 const Math::Vector3DArray& coords);


		CDPL_CHEM_API bool getStereoCenterFlag(const Bond& bond);

		CDPL_CHEM_API void setStereoCenterFlag(Bond& bond, bool is_center);

		CDPL_CHEM_API void clearStereoCenterFlag(Bond& bond);
	
		CDPL_CHEM_API bool hasStereoCenterFlag(const Bond& bond);

		CDPL_CHEM_API bool isStereoCenter(const Bond& bond, const MolecularGraph& molgraph, bool check_cip_sym = true, std::size_t min_ring_size = 8);
		

		CDPL_CHEM_API unsigned int getDirection(const Bond& bond);

		CDPL_CHEM_API void setDirection(Bond& bond, unsigned int dir);

		CDPL_CHEM_API void clearDirection(Bond& bond);
	
		CDPL_CHEM_API bool hasDirection(const Bond& bond);

	
		CDPL_CHEM_API unsigned int getReactionCenterStatus(const Bond& bond);

		CDPL_CHEM_API void setReactionCenterStatus(Bond& bond, unsigned int status);

		CDPL_CHEM_API void clearReactionCenterStatus(Bond& bond);
	
		CDPL_CHEM_API bool hasReactionCenterStatus(const Bond& bond);


		CDPL_CHEM_API const MatchConstraintList::SharedPointer& getMatchConstraints(const Bond& bond);
	
		CDPL_CHEM_API void setMatchConstraints(Bond& bond, const MatchConstraintList::SharedPointer& constr);

		CDPL_CHEM_API void clearMatchConstraints(Bond& bond);

		CDPL_CHEM_API bool hasMatchConstraints(const Bond& bond);


		CDPL_CHEM_API const MatchExpression<Bond, MolecularGraph>::SharedPointer& getMatchExpression(const Bond& bond);

		CDPL_CHEM_API void setMatchExpression(Bond& bond, const MatchExpression<Bond, MolecularGraph>::SharedPointer& expr);

		CDPL_CHEM_API void clearMatchExpression(Bond& bond);

		CDPL_CHEM_API bool hasMatchExpression(const Bond& bond);

		CDPL_CHEM_API MatchExpression<Bond, MolecularGraph>::SharedPointer buildMatchExpression(const Bond& bond, const MolecularGraph& molgraph);


		CDPL_CHEM_API const std::string& getMatchExpressionString(const Bond& bond);

		CDPL_CHEM_API void setMatchExpressionString(Bond& bond, const std::string& expr_str);

		CDPL_CHEM_API void clearMatchExpressionString(Bond& bond);

		CDPL_CHEM_API bool hasMatchExpressionString(const Bond& bond);

		CDPL_CHEM_API void buildMatchExpressionString(const Bond& bond, const MolecularGraph& molgraph, std::string& str);


		CDPL_CHEM_API double calcPolarizability(const Bond& bond, const MolecularGraph& molgraph, double damping = 0.75);


		CDPL_CHEM_API bool isRotatable(const Bond& bond, const MolecularGraph& molgraph, bool h_rotors = false, bool ring_bonds = false, bool amide_bonds = false);

		CDPL_CHEM_API bool isHydrogenBond(const Bond& bond);

		CDPL_CHEM_API bool isAmideBond(const Bond& bond, const MolecularGraph& molgraph, bool c_only = false, bool db_o_only = false);


		CDPL_CHEM_API unsigned int getSybylType(const Bond& bond);

		CDPL_CHEM_API void setSybylType(Bond& bond, unsigned int type);

		CDPL_CHEM_API void clearSybylType(Bond& bond);
	
		CDPL_CHEM_API bool hasSybylType(const Bond& bond);

		CDPL_CHEM_API unsigned int perceiveSybylType(const Bond& bond, const MolecularGraph& molgraph);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_BONDFUNCTIONS_HPP
 
