/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondDonorAtomTypeExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/MolProp/HBondDonorAtomType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct HBondDonorAtomType {};
}


void CDPLPythonMolProp::exportHBondDonorAtomTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<HBondDonorAtomType, boost::noncopyable>("HBondDonorAtomType", python::no_init)
		.def_readonly("UNDEF", &MolProp::HBondDonorAtomType::UNDEF)
		.def_readonly("NONE", &MolProp::HBondDonorAtomType::NONE)
		.def_readonly("I_HI", &MolProp::HBondDonorAtomType::I_HI)
		.def_readonly("BR_HBR", &MolProp::HBondDonorAtomType::BR_HBR)
		.def_readonly("CL_HCL", &MolProp::HBondDonorAtomType::CL_HCL)
		.def_readonly("S_HSCN", &MolProp::HBondDonorAtomType::S_HSCN)
		.def_readonly("F_HF", &MolProp::HBondDonorAtomType::F_HF)
		.def_readonly("H_H2", &MolProp::HBondDonorAtomType::H_H2)
		.def_readonly("C_HCN", &MolProp::HBondDonorAtomType::C_HCN)
		.def_readonly("C_ETHINE", &MolProp::HBondDonorAtomType::C_ETHINE)
		.def_readonly("N_HN3", &MolProp::HBondDonorAtomType::N_HN3)
		.def_readonly("N_NH3", &MolProp::HBondDonorAtomType::N_NH3)
		.def_readonly("N_NH4", &MolProp::HBondDonorAtomType::N_NH4)
		.def_readonly("N_AMINE", &MolProp::HBondDonorAtomType::N_AMINE)
		.def_readonly("N_AMINIUM", &MolProp::HBondDonorAtomType::N_AMINIUM)
		.def_readonly("N_ANILINE", &MolProp::HBondDonorAtomType::N_ANILINE)
		.def_readonly("N_MONO_DI_NITRO_ANILINE", &MolProp::HBondDonorAtomType::N_MONO_DI_NITRO_ANILINE)
		.def_readonly("N_TRI_NITRO_ANILINE", &MolProp::HBondDonorAtomType::N_TRI_NITRO_ANILINE)
		.def_readonly("N_PYRROLE", &MolProp::HBondDonorAtomType::N_PYRROLE)
		.def_readonly("N_AMIDE", &MolProp::HBondDonorAtomType::N_AMIDE)
		.def_readonly("N_IMINE", &MolProp::HBondDonorAtomType::N_IMINE)
		.def_readonly("N_IMINIUM", &MolProp::HBondDonorAtomType::N_IMINIUM)
		.def_readonly("S_H2S", &MolProp::HBondDonorAtomType::S_H2S)
		.def_readonly("S_HS", &MolProp::HBondDonorAtomType::S_HS)
		.def_readonly("S_THIOL", &MolProp::HBondDonorAtomType::S_THIOL)
		.def_readonly("O_H3PO4", &MolProp::HBondDonorAtomType::O_H3PO4)
		.def_readonly("O_H2CO3", &MolProp::HBondDonorAtomType::O_H2CO3)
		.def_readonly("O_HCO3", &MolProp::HBondDonorAtomType::O_HCO3)
		.def_readonly("O_H2O2", &MolProp::HBondDonorAtomType::O_H2O2)
		.def_readonly("O_H2O", &MolProp::HBondDonorAtomType::O_H2O)
		.def_readonly("O_CF3SO3H", &MolProp::HBondDonorAtomType::O_CF3SO3H)
		.def_readonly("O_HCLO4", &MolProp::HBondDonorAtomType::O_HCLO4)
		.def_readonly("O_H2SO4", &MolProp::HBondDonorAtomType::O_H2SO4)
		.def_readonly("O_HNO3", &MolProp::HBondDonorAtomType::O_HNO3)
		.def_readonly("O_HSO4", &MolProp::HBondDonorAtomType::O_HSO4)
		.def_readonly("O_HNO2", &MolProp::HBondDonorAtomType::O_HNO2)
		.def_readonly("O_NH2OH", &MolProp::HBondDonorAtomType::O_NH2OH)
		.def_readonly("O_H2PO4", &MolProp::HBondDonorAtomType::O_H2PO4)
		.def_readonly("O_H3BO3", &MolProp::HBondDonorAtomType::O_H3BO3)
		.def_readonly("O_H4SIO4", &MolProp::HBondDonorAtomType::O_H4SIO4)
		.def_readonly("O_HPO4", &MolProp::HBondDonorAtomType::O_HPO4)
		.def_readonly("O_H2BO3", &MolProp::HBondDonorAtomType::O_H2BO3)
		.def_readonly("O_HO", &MolProp::HBondDonorAtomType::O_HO)
		.def_readonly("O_SULFONIC_ACID", &MolProp::HBondDonorAtomType::O_SULFONIC_ACID)
		.def_readonly("O_MONO_DI_NITRO_PHENOL", &MolProp::HBondDonorAtomType::O_MONO_DI_NITRO_PHENOL)
		.def_readonly("O_HALOGENO_ALCOHOL", &MolProp::HBondDonorAtomType::O_HALOGENO_ALCOHOL)
		.def_readonly("O_ALCOHOL", &MolProp::HBondDonorAtomType::O_ALCOHOL)
		.def_readonly("O_TRI_NITRO_PHENOL", &MolProp::HBondDonorAtomType::O_TRI_NITRO_PHENOL)
		.def_readonly("O_HALOGENO_PHENOL", &MolProp::HBondDonorAtomType::O_HALOGENO_PHENOL)
		.def_readonly("O_PHENOL", &MolProp::HBondDonorAtomType::O_PHENOL)
		.def_readonly("O_CARBOXYLIC_ACID", &MolProp::HBondDonorAtomType::O_CARBOXYLIC_ACID)
		.def_readonly("O_HALOGENO_CARBOXYCLIC_ACID", &MolProp::HBondDonorAtomType::O_HALOGENO_CARBOXYCLIC_ACID)
		.def_readonly("O_ENOL", &MolProp::HBondDonorAtomType::O_ENOL)
		.def_readonly("O_OXIME", &MolProp::HBondDonorAtomType::O_OXIME)
		.def_readonly("O_CL5_PHENOL", &MolProp::HBondDonorAtomType::O_CL5_PHENOL)
		.def_readonly("MAX_TYPE", &MolProp::HBondDonorAtomType::MAX_TYPE);
}
