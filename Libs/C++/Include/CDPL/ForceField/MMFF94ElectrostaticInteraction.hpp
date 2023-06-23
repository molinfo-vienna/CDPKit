/* 
 * MMFF94ElectrostaticInteraction.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94ElectrostaticInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTION_HPP

#include <cstddef>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94ElectrostaticInteraction
		{

		  public:
			MMFF94ElectrostaticInteraction(std::size_t atom1_idx, std::size_t atom2_idx, double atom1_chg, 
										   double atom2_chg, double scale_fact, double de_const, double dist_expo):
				atom1Idx(atom1_idx), atom2Idx(atom2_idx), atom1Chg(atom1_chg), atom2Chg(atom2_chg),
				scaleFact(scale_fact), deConst(de_const), distExpo(dist_expo) {}

			std::size_t getAtom1Index() const {
				return atom1Idx;
			}

			std::size_t getAtom2Index() const {
				return atom2Idx;
			}

			double getAtom1Charge() const {
				return atom1Chg;
			}

			double getAtom2Charge() const {
				return atom2Chg;
			}

			double getScalingFactor() const {
				return scaleFact;
			}

			double getDielectricConstant() const {
				return deConst;
			}

			double getDistanceExponent() const {
				return distExpo;
			}

		  private:
			std::size_t atom1Idx;
			std::size_t atom2Idx;
			double      atom1Chg;
			double      atom2Chg;
			double      scaleFact;
			double      deConst;
			double      distExpo;
		};			
    }
}

#endif // CDPL_FORCEFIELD_MMFF94ELECTROSTATICINTERACTION_HPP
