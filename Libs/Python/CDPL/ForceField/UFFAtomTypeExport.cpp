/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UFFAtomTypeExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/ForceField/UFFAtomType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct UFFAtomType {};
}


void CDPLPythonForceField::exportUFFAtomTypes()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<UFFAtomType, boost::noncopyable>("UFFAtomType", python::no_init)
		.def_readonly("NONE", &ForceField::UFFAtomType::NONE)
		.def_readonly("H  ", &ForceField::UFFAtomType::H)
		.def_readonly("H_b", &ForceField::UFFAtomType::H_b)
		.def_readonly("He_4_4", &ForceField::UFFAtomType::He_4_4)
		.def_readonly("Li", &ForceField::UFFAtomType::Li)
		.def_readonly("Be_3_2", &ForceField::UFFAtomType::Be_3_2)
		.def_readonly("B_3", &ForceField::UFFAtomType::B_3)
		.def_readonly("B_2", &ForceField::UFFAtomType::B_2)
		.def_readonly("C_3", &ForceField::UFFAtomType::C_3)
		.def_readonly("C_R", &ForceField::UFFAtomType::C_R)
		.def_readonly("C_2", &ForceField::UFFAtomType::C_2)
		.def_readonly("C_1", &ForceField::UFFAtomType::C_1)
		.def_readonly("N_3", &ForceField::UFFAtomType::N_3)
		.def_readonly("N_R", &ForceField::UFFAtomType::N_R)
		.def_readonly("N_2", &ForceField::UFFAtomType::N_2)
		.def_readonly("N_1", &ForceField::UFFAtomType::N_1)
		.def_readonly("O_3", &ForceField::UFFAtomType::O_3)
		.def_readonly("O_3_z", &ForceField::UFFAtomType::O_3_z)
		.def_readonly("O_R", &ForceField::UFFAtomType::O_R)
		.def_readonly("O_2", &ForceField::UFFAtomType::O_2)
		.def_readonly("O_1", &ForceField::UFFAtomType::O_1)
		.def_readonly("F", &ForceField::UFFAtomType::F)
		.def_readonly("Ne_4_4", &ForceField::UFFAtomType::Ne_4_4)
		.def_readonly("Na", &ForceField::UFFAtomType::Na)
		.def_readonly("Mg_3_2", &ForceField::UFFAtomType::Mg_3_2)
		.def_readonly("Al_3", &ForceField::UFFAtomType::Al_3)
		.def_readonly("Si_3", &ForceField::UFFAtomType::Si_3)
		.def_readonly("P_3_3", &ForceField::UFFAtomType::P_3_3)
		.def_readonly("P_3_5", &ForceField::UFFAtomType::P_3_5)
		.def_readonly("P_3_q", &ForceField::UFFAtomType::P_3_q)
		.def_readonly("S_3_2", &ForceField::UFFAtomType::S_3_2)
		.def_readonly("S_3_4", &ForceField::UFFAtomType::S_3_4)
		.def_readonly("S_3_6", &ForceField::UFFAtomType::S_3_6)
		.def_readonly("S_R", &ForceField::UFFAtomType::S_R)
		.def_readonly("S_2", &ForceField::UFFAtomType::S_2)
		.def_readonly("Cl", &ForceField::UFFAtomType::Cl)
		.def_readonly("Ar_4_4", &ForceField::UFFAtomType::Ar_4_4)
		.def_readonly("K", &ForceField::UFFAtomType::K)
		.def_readonly("Ca_6_2", &ForceField::UFFAtomType::Ca_6_2)
		.def_readonly("Sc_3_3", &ForceField::UFFAtomType::Sc_3_3)
		.def_readonly("Ti_3_4", &ForceField::UFFAtomType::Ti_3_4)
		.def_readonly("Ti_6_4", &ForceField::UFFAtomType::Ti_6_4)
		.def_readonly("V_3_5", &ForceField::UFFAtomType::V_3_5)
		.def_readonly("Cr_6_3", &ForceField::UFFAtomType::Cr_6_3)
		.def_readonly("Mn_6_2", &ForceField::UFFAtomType::Mn_6_2)
		.def_readonly("Fe_3_2", &ForceField::UFFAtomType::Fe_3_2)
		.def_readonly("Fe_6_2", &ForceField::UFFAtomType::Fe_6_2)
		.def_readonly("Co_6_3", &ForceField::UFFAtomType::Co_6_3)
		.def_readonly("Ni_4_2", &ForceField::UFFAtomType::Ni_4_2)
		.def_readonly("Cu_3_1", &ForceField::UFFAtomType::Cu_3_1)
		.def_readonly("Zn_3_2", &ForceField::UFFAtomType::Zn_3_2)
		.def_readonly("Ga_3_3", &ForceField::UFFAtomType::Ga_3_3)
		.def_readonly("Ge_3", &ForceField::UFFAtomType::Ge_3)
		.def_readonly("As_3_3", &ForceField::UFFAtomType::As_3_3)
		.def_readonly("Se_3_2", &ForceField::UFFAtomType::Se_3_2)
		.def_readonly("Br", &ForceField::UFFAtomType::Br)
		.def_readonly("Kr_4_4", &ForceField::UFFAtomType::Kr_4_4)
		.def_readonly("Rb", &ForceField::UFFAtomType::Rb)
		.def_readonly("Sr_6_2", &ForceField::UFFAtomType::Sr_6_2)
		.def_readonly("Y_3_3", &ForceField::UFFAtomType::Y_3_3)
		.def_readonly("Zr_3_4", &ForceField::UFFAtomType::Zr_3_4)
		.def_readonly("Nb_3_5", &ForceField::UFFAtomType::Nb_3_5)
		.def_readonly("Mo_6_6", &ForceField::UFFAtomType::Mo_6_6)
		.def_readonly("Mo_3_6", &ForceField::UFFAtomType::Mo_3_6)
		.def_readonly("Tc_6_5", &ForceField::UFFAtomType::Tc_6_5)
		.def_readonly("Ru_6_2", &ForceField::UFFAtomType::Ru_6_2)
		.def_readonly("Rh_6_3", &ForceField::UFFAtomType::Rh_6_3)
		.def_readonly("Pd_4_2", &ForceField::UFFAtomType::Pd_4_2)
		.def_readonly("Ag_1_1", &ForceField::UFFAtomType::Ag_1_1)
		.def_readonly("Cd_3_2", &ForceField::UFFAtomType::Cd_3_2)
		.def_readonly("In_3_3", &ForceField::UFFAtomType::In_3_3)
		.def_readonly("Sn_3", &ForceField::UFFAtomType::Sn_3)
		.def_readonly("Sb_3_3", &ForceField::UFFAtomType::Sb_3_3)
		.def_readonly("Te_3_2", &ForceField::UFFAtomType::Te_3_2)
		.def_readonly("I", &ForceField::UFFAtomType::I)
		.def_readonly("Xe_4_4", &ForceField::UFFAtomType::Xe_4_4)
		.def_readonly("Cs", &ForceField::UFFAtomType::Cs)
		.def_readonly("Ba_6_2", &ForceField::UFFAtomType::Ba_6_2)
		.def_readonly("La_3_3", &ForceField::UFFAtomType::La_3_3)
		.def_readonly("Ce_6_3", &ForceField::UFFAtomType::Ce_6_3)
		.def_readonly("Pr_6_3", &ForceField::UFFAtomType::Pr_6_3)
		.def_readonly("Nd_6_3", &ForceField::UFFAtomType::Nd_6_3)
		.def_readonly("Pm_6_3", &ForceField::UFFAtomType::Pm_6_3)
		.def_readonly("Sm_6_3", &ForceField::UFFAtomType::Sm_6_3)
		.def_readonly("Eu_6_3", &ForceField::UFFAtomType::Eu_6_3)
		.def_readonly("Gd_6_3", &ForceField::UFFAtomType::Gd_6_3)
		.def_readonly("Tb_6_3", &ForceField::UFFAtomType::Tb_6_3)
		.def_readonly("Dy_6_3", &ForceField::UFFAtomType::Dy_6_3)
		.def_readonly("Ho_6_3", &ForceField::UFFAtomType::Ho_6_3)
		.def_readonly("Er_6_3", &ForceField::UFFAtomType::Er_6_3)
		.def_readonly("Tm_6_3", &ForceField::UFFAtomType::Tm_6_3)
		.def_readonly("Yb_6_3", &ForceField::UFFAtomType::Yb_6_3)
		.def_readonly("Lu_6_3", &ForceField::UFFAtomType::Lu_6_3)
		.def_readonly("Hf_3_4", &ForceField::UFFAtomType::Hf_3_4)
		.def_readonly("Ta_3_5", &ForceField::UFFAtomType::Ta_3_5)
		.def_readonly("W_6_6", &ForceField::UFFAtomType::W_6_6)
		.def_readonly("W_3_4", &ForceField::UFFAtomType::W_3_4)
		.def_readonly("W_3_6", &ForceField::UFFAtomType::W_3_6)
		.def_readonly("Re_6_5", &ForceField::UFFAtomType::Re_6_5)
		.def_readonly("Re_3_7", &ForceField::UFFAtomType::Re_3_7)
		.def_readonly("Os_6_6", &ForceField::UFFAtomType::Os_6_6)
		.def_readonly("Ir_6_3", &ForceField::UFFAtomType::Ir_6_3)
		.def_readonly("Pt_4_2", &ForceField::UFFAtomType::Pt_4_2)
		.def_readonly("Au_4_3", &ForceField::UFFAtomType::Au_4_3)
		.def_readonly("Hg_1_2", &ForceField::UFFAtomType::Hg_1_2)
		.def_readonly("Tl_3_3", &ForceField::UFFAtomType::Tl_3_3)
		.def_readonly("Pb_3", &ForceField::UFFAtomType::Pb_3)
		.def_readonly("Bi_3_3", &ForceField::UFFAtomType::Bi_3_3)
		.def_readonly("Po_3_2", &ForceField::UFFAtomType::Po_3_2)
		.def_readonly("At", &ForceField::UFFAtomType::At)
		.def_readonly("Rn_4_4", &ForceField::UFFAtomType::Rn_4_4)
		.def_readonly("Fr", &ForceField::UFFAtomType::Fr)
		.def_readonly("Ra_6_2", &ForceField::UFFAtomType::Ra_6_2)
		.def_readonly("Ac_6_3", &ForceField::UFFAtomType::Ac_6_3)
		.def_readonly("Th_6_4", &ForceField::UFFAtomType::Th_6_4)
		.def_readonly("Pa_6_4", &ForceField::UFFAtomType::Pa_6_4)
		.def_readonly("U_6_4", &ForceField::UFFAtomType::U_6_4)
		.def_readonly("Np_6_4", &ForceField::UFFAtomType::Np_6_4)
		.def_readonly("Pu_6_4", &ForceField::UFFAtomType::Pu_6_4)
		.def_readonly("Am_6_4", &ForceField::UFFAtomType::Am_6_4)
		.def_readonly("Cm_6_3", &ForceField::UFFAtomType::Cm_6_3)
		.def_readonly("Bk_6_3", &ForceField::UFFAtomType::Bk_6_3)
		.def_readonly("Cf_6_3", &ForceField::UFFAtomType::Cf_6_3)
		.def_readonly("Es_6_3", &ForceField::UFFAtomType::Es_6_3)
		.def_readonly("Fm_6_3", &ForceField::UFFAtomType::Fm_6_3)
		.def_readonly("Md_6_3", &ForceField::UFFAtomType::Md_6_3)
		.def_readonly("No_6_3", &ForceField::UFFAtomType::No_6_3)
		.def_readonly("Lr_6_3", &ForceField::UFFAtomType::Lr_6_3)
		.def_readonly("MAX_TYPE", &ForceField::UFFAtomType::MAX_TYPE);
}
