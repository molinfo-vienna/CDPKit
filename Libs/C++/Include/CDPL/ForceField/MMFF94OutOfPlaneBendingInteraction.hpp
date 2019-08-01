/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94OutOfPlaneBendingInteraction.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94OutOfPlaneBendingInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTION_HPP

#include <cstddef>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_INTERACTION_DATA
		 * @{
		 */

		class CDPL_FORCEFIELD_API MMFF94OutOfPlaneBendingInteraction
		{

		  public:
			MMFF94OutOfPlaneBendingInteraction(std::size_t term_atom1_idx, std::size_t ctr_atom_idx, std::size_t term_atom2_idx, 
											   std::size_t oop_atom_idx, double force_const):
				termAtom1Idx(term_atom1_idx), ctrAtomIdx(ctr_atom_idx), termAtom2Idx(term_atom2_idx), 
				oopAtomIdx(oop_atom_idx), forceConst(force_const) {}

			std::size_t getTerminalAtom1Index() const {
				return termAtom1Idx;
			}

			std::size_t getCenterAtomIndex() const {
				return ctrAtomIdx;
			}

			std::size_t getTerminalAtom2Index() const {
				return termAtom2Idx;
			}

			std::size_t getOutOfPlaneAtomIndex() const {
				return oopAtomIdx;
			}
	
			std::size_t getAtom1Index() const {
				return termAtom1Idx;
			}

			std::size_t getAtom2Index() const {
				return ctrAtomIdx;
			}

			std::size_t getAtom3Index() const {
				return termAtom2Idx;
			}

			std::size_t getAtom4Index() const {
				return oopAtomIdx;
			}

			double getForceConstant() const {
				return forceConst;
			}

		  private:
			std::size_t termAtom1Idx;
			std::size_t ctrAtomIdx;
			std::size_t termAtom2Idx;
			std::size_t oopAtomIdx;
			double      forceConst;
		};			
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_MMFF94OUTOFPLANEBENDINGINTERACTION_HPP
