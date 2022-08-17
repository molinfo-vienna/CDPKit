/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94VanDerWaalsInteraction.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94VanDerWaalsInteraction.
 */

#ifndef CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTION_HPP
#define CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTION_HPP

#include <cstddef>
#include <cmath>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94VanDerWaalsInteraction
		{

		  public:
			enum HDonorAcceptorType 
			{
			
			    NONE,
				DONOR,
				ACCEPTOR
			};	

			MMFF94VanDerWaalsInteraction(std::size_t atom1_idx, std::size_t atom2_idx, 
										 double atom_pol1, double eff_el_num1, double fact_a1, double fact_g1, 
										 HDonorAcceptorType don_acc_type1, double atom_pol2, double eff_el_num2,
										 double fact_a2, double fact_g2, HDonorAcceptorType don_acc_type2,
										 double expo, double fact_b, double beta, double fact_darad, double fact_daeps):
				atom1Idx(atom1_idx), atom2Idx(atom2_idx) {
				
				bool have_don = false;
				bool have_don_acc = false;
    
				switch (don_acc_type1) {
      
					case DONOR:
						have_don = true;
						have_don_acc = (don_acc_type2 == ACCEPTOR);
						break;
     
					case ACCEPTOR:
						have_don_acc = (don_acc_type2 == DONOR);
						have_don = have_don_acc;
						break;
        
					default:
						have_don = (don_acc_type2 == DONOR);
						break;
				}
  
				double rII = fact_a1 * std::pow(atom_pol1, expo);
				double rJJ = fact_a2 * std::pow(atom_pol2, expo);
				double gIJ = (rII - rJJ) / (rII + rJJ);
    	
				rIJ = 0.5 * (rII + rJJ);
    
				if (!have_don)
					rIJ += rIJ * fact_b * (1.0 - std::exp(-beta * gIJ * gIJ));

				eIJ = 181.16 * fact_g1 * fact_g2 * atom_pol1 * atom_pol2 / (std::pow(atom_pol1 / eff_el_num1, 0.5) + std::pow(atom_pol2 / eff_el_num2, 0.5)) * std::pow(rIJ, -6.0);
    
				if (have_don_acc) {
					rIJ *= fact_darad;
					eIJ *= fact_daeps;
				}
  
				rIJPow7 = std::pow(rIJ, 7.0);
			}

			std::size_t getAtom1Index() const {
				return atom1Idx;
			}

			std::size_t getAtom2Index() const {
				return atom2Idx;
			}

			double getEIJ() const {
				return eIJ;
			}
	
			double getRIJ() const {
				return rIJ;
			}

			double getRIJPow7() const {
				return rIJPow7;
			}

		  private:
			std::size_t atom1Idx;
			std::size_t atom2Idx;
			double      eIJ;
			double      rIJ;
			double      rIJPow7;
		};			
    }
}

#endif // CDPL_FORCEFIELD_MMFF94VANDERWAALSINTERACTION_HPP
