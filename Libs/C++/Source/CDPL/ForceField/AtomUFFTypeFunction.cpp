/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomUFFTypeFunctions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/ForceField/AtomFunctions.hpp"
#include "CDPL/ForceField/UFFAtomType.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"


using namespace CDPL; 


unsigned int ForceField::perceiveUFFType(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph)
{
    using namespace Chem;
	using namespace MolProp;
    
    switch (getType(atom)) {

		case AtomType::H:
			if (getBondCount(atom, molgraph) == 2 && getBondCount(atom, molgraph, 1, AtomType::B, true) == 2)
				return UFFAtomType::H_b;
			
			return UFFAtomType::H;
	    
		case AtomType::He:
			return UFFAtomType::He_4_4;
	    
		case AtomType::Li:
			return UFFAtomType::Li;
	    
		case AtomType::Be:
			return UFFAtomType::Be_3_2;
	    
		case AtomType::B:
			if (getHybridizationState(atom) == HybridizationState::SP3)
				return UFFAtomType::B_3;

			return UFFAtomType::B_2;
	    
		case AtomType::C:
			if (getAromaticityFlag(atom))
				return UFFAtomType::C_R;
			
			switch (getHybridizationState(atom)) {

				case HybridizationState::SP:
					return UFFAtomType::C_1;
					
				case HybridizationState::SP2:
					return UFFAtomType::C_2;
			}

			return UFFAtomType::C_3;
	    
		case AtomType::N:
			if (getAromaticityFlag(atom))
				return UFFAtomType::N_R;
			
			switch (getHybridizationState(atom)) {

				case HybridizationState::SP:
					return UFFAtomType::N_1;
					
				case HybridizationState::SP2:
					return UFFAtomType::N_2;
			}

			return UFFAtomType::N_3;

		case AtomType::O:
			if (getAromaticityFlag(atom))
				return UFFAtomType::O_R;
			
			switch (getHybridizationState(atom)) {

				case HybridizationState::SP:
					return UFFAtomType::O_1;
					
				case HybridizationState::SP2:
					return UFFAtomType::O_2;
			}

			return UFFAtomType::O_3;
	    
		case AtomType::F:
			return UFFAtomType::F;
	    
		case AtomType::Ne:
			return UFFAtomType::Ne_4_4;
	    
		case AtomType::Na:
			return UFFAtomType::Na;
	    
		case AtomType::Mg:
			return UFFAtomType::Mg_3_2;
	    
		case AtomType::Al:
			return UFFAtomType::Al_3;

		case AtomType::Si:
			return UFFAtomType::Si_3;
	    
		case AtomType::P:
			if (calcValence(atom, molgraph) == 5)
				return UFFAtomType::P_3_5;

			return UFFAtomType::P_3_3;
	    
		case AtomType::S:
			if (getAromaticityFlag(atom))
				return UFFAtomType::S_R;
			
			if (getHybridizationState(atom) == HybridizationState::SP2)
				return UFFAtomType::S_2;

			switch (calcValence(atom, molgraph)) {

				case 2:
					return UFFAtomType::S_3_2;

				case 4:
					return UFFAtomType::S_3_4;

				case 6:
					return UFFAtomType::S_3_6;
			}

			return UFFAtomType::S_3_2;

		case AtomType::Cl:
			return UFFAtomType::Cl;
	    
		case AtomType::Ar:
			return UFFAtomType::Ar_4_4;
		
		case AtomType::K:
			return UFFAtomType::K;

		case AtomType::Ca:
			return UFFAtomType::Ca_6_2;

		case AtomType::Sc:
			return UFFAtomType::Sc_3_3;

		case AtomType::Ti:
			if (getBondCount(atom, molgraph) == 6)
				return UFFAtomType::Ti_6_4;

			return UFFAtomType::Ti_3_4;
	    
		case AtomType::V:
			return UFFAtomType::V_3_5;

		case AtomType::Cr:
			return UFFAtomType::Cr_6_3;

		case AtomType::Mn:
			return UFFAtomType::Mn_6_2;

		case AtomType::Fe:
			if (getBondCount(atom, molgraph) == 6)
				return UFFAtomType::Fe_6_2;

			return UFFAtomType::Fe_3_2;

		case AtomType::Co:
			return UFFAtomType::Co_6_3;
		
		case AtomType::Ni:
			return UFFAtomType::Ni_4_2;
		
		case AtomType::Cu:
			return UFFAtomType::Cu_3_1;
		
		case AtomType::Zn:
			return UFFAtomType::Zn_3_2;
		
		case AtomType::Ga:
			return UFFAtomType::Ga_3_3;
		
		case AtomType::Ge:
			return UFFAtomType::Ge_3;
		
		case AtomType::As:
			return UFFAtomType::As_3_3;
		
		case AtomType::Se:
			return UFFAtomType::Se_3_2;
		
		case AtomType::Br:
			return UFFAtomType::Br;
		
		case AtomType::Kr:
			return UFFAtomType::Kr_4_4;
		
		case AtomType::Rb:
			return UFFAtomType::Rb;
		
		case AtomType::Sr:
			return UFFAtomType::Sr_6_2;
		
		case AtomType::Y:
			return UFFAtomType::Y_3_3;
		
		case AtomType::Zr:
			return UFFAtomType::Zr_3_4;
		
		case AtomType::Nb:
			return UFFAtomType::Nb_3_5;
		
		case AtomType::Mo:
			if (getBondCount(atom, molgraph) == 6)
				return UFFAtomType::Mo_6_6;

			return UFFAtomType::Mo_3_6;
		
		case AtomType::Tc:
			return UFFAtomType::Tc_6_5;
		
		case AtomType::Ru:
			return UFFAtomType::Ru_6_2;
		
		case AtomType::Rh:
			return UFFAtomType::Rh_6_3;
		
		case AtomType::Pd:
			return UFFAtomType::Pd_4_2;
		
		case AtomType::Ag:
			return UFFAtomType::Ag_1_1;
		
		case AtomType::Cd:
			return UFFAtomType::Cd_3_2;
		
		case AtomType::In:
			return UFFAtomType::In_3_3;
		
		case AtomType::Sn:
			return UFFAtomType::Sn_3;
		
		case AtomType::Sb:
			return UFFAtomType::Sb_3_3;
		
		case AtomType::Te:
			return UFFAtomType::Te_3_2;
		
		case AtomType::I:
			return UFFAtomType::I;
		
		case AtomType::Xe:
			return UFFAtomType::Xe_4_4;
		
		case AtomType::Cs:
			return UFFAtomType::Cs;
		
		case AtomType::Ba:
			return UFFAtomType::Ba_6_2;
		
		case AtomType::La:
			return UFFAtomType::La_3_3;
		
		case AtomType::Ce:
			return UFFAtomType::Ce_6_3;
		
		case AtomType::Pr:
			return UFFAtomType::Pr_6_3;
		
		case AtomType::Nd:
			return UFFAtomType::Nd_6_3;
		
		case AtomType::Pm:
			return UFFAtomType::Pm_6_3;
		
		case AtomType::Sm:
			return UFFAtomType::Sm_6_3;
		
		case AtomType::Eu:
			return UFFAtomType::Eu_6_3;
		
		case AtomType::Gd:
			return UFFAtomType::Gd_6_3;
		
		case AtomType::Tb:
			return UFFAtomType::Tb_6_3;
		
		case AtomType::Dy:
			return UFFAtomType::Dy_6_3;
		
		case AtomType::Ho:
			return UFFAtomType::Ho_6_3;
		
		case AtomType::Er:
			return UFFAtomType::Er_6_3;
		
		case AtomType::Tm:
			return UFFAtomType::Tm_6_3;
		
		case AtomType::Yb:
			return UFFAtomType::Yb_6_3;
		
		case AtomType::Lu:
			return UFFAtomType::Lu_6_3;
		
		case AtomType::Hf:
			return UFFAtomType::Hf_3_4;
		
		case AtomType::Ta:
			return UFFAtomType::Ta_3_5;
		
		case AtomType::W:
			if (getBondCount(atom, molgraph) == 6)
				return UFFAtomType::W_6_6;

			if (calcValence(atom, molgraph) == 6)
				return UFFAtomType::W_3_6;

			return UFFAtomType::W_3_4;

		case AtomType::Re:
			if (getBondCount(atom, molgraph) == 6)
				return UFFAtomType::Re_6_5;

			return UFFAtomType::Re_3_7;
		
		case AtomType::Os:
			return UFFAtomType::Os_6_6;
		
		case AtomType::Ir:
			return UFFAtomType::Ir_6_3;
		
		case AtomType::Pt:
			return UFFAtomType::Pt_4_2;
		
		case AtomType::Au:
			return UFFAtomType::Au_4_3;
		
		case AtomType::Hg:
			return UFFAtomType::Hg_1_2;
		
		case AtomType::Tl:
			return UFFAtomType::Tl_3_3;
		
		case AtomType::Pb:
			return UFFAtomType::Pb_3;
		
		case AtomType::Bi:
			return UFFAtomType::Bi_3_3;
		
		case AtomType::Po:
			return UFFAtomType::Po_3_2;
		
		case AtomType::At:
			return UFFAtomType::At;
	    
		case AtomType::Rn:
			return UFFAtomType::Rn_4_4;
		
		case AtomType::Fr:
			return UFFAtomType::Fr;
		
		case AtomType::Ra:
			return UFFAtomType::Ra_6_2;
		
		case AtomType::Ac:
			return UFFAtomType::Ac_6_3;
		
		case AtomType::Th:
			return UFFAtomType::Th_6_4;
		
		case AtomType::Pa:
			return UFFAtomType::Pa_6_4;
		
		case AtomType::U:
			return UFFAtomType::U_6_4;
		
		case AtomType::Np:
			return UFFAtomType::Np_6_4;
		
		case AtomType::Pu:
			return UFFAtomType::Pu_6_4;
		
		case AtomType::Am:
			return UFFAtomType::Am_6_4;
		
		case AtomType::Cm:
			return UFFAtomType::Cm_6_3;
		
		case AtomType::Bk:
			return UFFAtomType::Bk_6_3;
		
		case AtomType::Cf:
			return UFFAtomType::Cf_6_3;
		
		case AtomType::Es:
			return UFFAtomType::Es_6_3;
		
		case AtomType::Fm:
			return UFFAtomType::Fm_6_3;
		
		case AtomType::Md:
			return UFFAtomType::Md_6_3;
		
		case AtomType::No:
			return UFFAtomType::No_6_3;
		
		case AtomType::Lr:
			return UFFAtomType::Lr_6_3;
    }

    return UFFAtomType::NONE;
}
