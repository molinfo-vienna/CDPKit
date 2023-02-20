/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondAcceptorAtomTypeExport.cpp 
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

#include "CDPL/MolProp/HBondAcceptorAtomType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct HBondAcceptorAtomType {};
}


void CDPLPythonMolProp::exportHBondAcceptorAtomTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<HBondAcceptorAtomType, boost::noncopyable>("HBondAcceptorAtomType", python::no_init)
		.def_readonly("UNDEF", &MolProp::HBondAcceptorAtomType::UNDEF)
		.def_readonly("NONE", &MolProp::HBondAcceptorAtomType::NONE)
		.def_readonly("O_H2O", &MolProp::HBondAcceptorAtomType::O_H2O)
		.def_readonly("O_UREA", &MolProp::HBondAcceptorAtomType::O_UREA)
		.def_readonly("O_BARBITURIC_ACID", &MolProp::HBondAcceptorAtomType::O_BARBITURIC_ACID)
		.def_readonly("O_URIC_ACID", &MolProp::HBondAcceptorAtomType::O_URIC_ACID)
		.def_readonly("O_ETHER", &MolProp::HBondAcceptorAtomType::O_ETHER)
		.def_readonly("O_AMIDE", &MolProp::HBondAcceptorAtomType::O_AMIDE)
		.def_readonly("O_N_OXIDE", &MolProp::HBondAcceptorAtomType::O_N_OXIDE)
		.def_readonly("O_ACID", &MolProp::HBondAcceptorAtomType::O_ACID)
		.def_readonly("O_ESTER", &MolProp::HBondAcceptorAtomType::O_ESTER)
		.def_readonly("O_SULFOXIDE", &MolProp::HBondAcceptorAtomType::O_SULFOXIDE)
		.def_readonly("O_NITRO", &MolProp::HBondAcceptorAtomType::O_NITRO)
		.def_readonly("O_SELEN_OXIDE", &MolProp::HBondAcceptorAtomType::O_SELEN_OXIDE)
		.def_readonly("O_ALDEHYD", &MolProp::HBondAcceptorAtomType::O_ALDEHYD)
		.def_readonly("O_KETONE", &MolProp::HBondAcceptorAtomType::O_KETONE)
		.def_readonly("O_ALCOHOL", &MolProp::HBondAcceptorAtomType::O_ALCOHOL)
		.def_readonly("N_NH3", &MolProp::HBondAcceptorAtomType::N_NH3)
		.def_readonly("N_DIAMINE", &MolProp::HBondAcceptorAtomType::N_DIAMINE)
		.def_readonly("N_MONO_DI_NITRO_ANILINE", &MolProp::HBondAcceptorAtomType::N_MONO_DI_NITRO_ANILINE)
		.def_readonly("N_TRI_NITRO_ANILINE", &MolProp::HBondAcceptorAtomType::N_TRI_NITRO_ANILINE)
		.def_readonly("N_HALOGENO_ANILINE", &MolProp::HBondAcceptorAtomType::N_HALOGENO_ANILINE)
		.def_readonly("N_ANILINE", &MolProp::HBondAcceptorAtomType::N_ANILINE)
		.def_readonly("N_NITRILE", &MolProp::HBondAcceptorAtomType::N_NITRILE)
		.def_readonly("N_AZOLE", &MolProp::HBondAcceptorAtomType::N_AZOLE)
		.def_readonly("N_AMINE", &MolProp::HBondAcceptorAtomType::N_AMINE)
		.def_readonly("N_AMIDINE", &MolProp::HBondAcceptorAtomType::N_AMIDINE)
		.def_readonly("N_AZO", &MolProp::HBondAcceptorAtomType::N_AZO)
		.def_readonly("N_AZINE", &MolProp::HBondAcceptorAtomType::N_AZINE)
		.def_readonly("N_DIAZINE", &MolProp::HBondAcceptorAtomType::N_DIAZINE)
		.def_readonly("S_SULFIDE", &MolProp::HBondAcceptorAtomType::S_SULFIDE)
		.def_readonly("S_THIOUREA", &MolProp::HBondAcceptorAtomType::S_THIOUREA)
		.def_readonly("P_MONO_DI_PHOSPHINE", &MolProp::HBondAcceptorAtomType::P_MONO_DI_PHOSPHINE)
		.def_readonly("P_TRI_PHOSPHINE", &MolProp::HBondAcceptorAtomType::P_TRI_PHOSPHINE)
		.def_readonly("MAX_TYPE", &MolProp::HBondAcceptorAtomType::MAX_TYPE);
}
