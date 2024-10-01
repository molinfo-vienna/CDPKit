/* 
 * ResidueTypeExport.cpp 
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

#include "CDPL/Biomol/ResidueType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ResidueType {};
}


void CDPLPythonBiomol::exportResidueTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ResidueType, boost::noncopyable>("ResidueType", python::no_init)
        .def_readonly("UNKNOWN", Biomol::ResidueType::UNKNOWN)
        .def_readonly("OTHER", Biomol::ResidueType::OTHER)
        .def_readonly("NON_POLYMER", Biomol::ResidueType::NON_POLYMER)
        .def_readonly("L_PEPTIDE_CARBOXY_TERMINUS", Biomol::ResidueType::L_PEPTIDE_CARBOXY_TERMINUS)
        .def_readonly("L_PEPTIDE_AMINO_TERMINUS", Biomol::ResidueType::L_PEPTIDE_AMINO_TERMINUS)
        .def_readonly("D_PEPTIDE_AMINO_TERMINUS", Biomol::ResidueType::D_PEPTIDE_AMINO_TERMINUS)
        .def_readonly("PEPTIDE_LINKING", Biomol::ResidueType::PEPTIDE_LINKING)
        .def_readonly("L_PEPTIDE_LINKING", Biomol::ResidueType::L_PEPTIDE_LINKING)
        .def_readonly("D_PEPTIDE_LINKING", Biomol::ResidueType::D_PEPTIDE_LINKING)
        .def_readonly("L_BETA_PEPTIDE_LINKING", Biomol::ResidueType::L_BETA_PEPTIDE_LINKING)
        .def_readonly("D_BETA_PEPTIDE_LINKING", Biomol::ResidueType::D_BETA_PEPTIDE_LINKING)
        .def_readonly("L_GAMMA_PEPTIDE_LINKING", Biomol::ResidueType::L_GAMMA_PEPTIDE_LINKING)
        .def_readonly("D_GAMMA_PEPTIDE_LINKING", Biomol::ResidueType::D_GAMMA_PEPTIDE_LINKING)
        .def_readonly("PEPTIDE_LIKE", Biomol::ResidueType::PEPTIDE_LIKE)
        .def_readonly("RNA_3_HYDROXY_TERMINUS", Biomol::ResidueType::RNA_3_HYDROXY_TERMINUS)
        .def_readonly("RNA_5_HYDROXY_TERMINUS", Biomol::ResidueType::RNA_5_HYDROXY_TERMINUS)
        .def_readonly("DNA_3_HYDROXY_TERMINUS", Biomol::ResidueType::DNA_3_HYDROXY_TERMINUS)
        .def_readonly("DNA_5_HYDROXY_TERMINUS", Biomol::ResidueType::DNA_5_HYDROXY_TERMINUS)
        .def_readonly("RNA_LINKING", Biomol::ResidueType::RNA_LINKING)
        .def_readonly("DNA_LINKING", Biomol::ResidueType::DNA_LINKING)
        .def_readonly("L_RNA_LINKING", Biomol::ResidueType::L_RNA_LINKING)
        .def_readonly("L_DNA_LINKING", Biomol::ResidueType::L_DNA_LINKING)
        .def_readonly("L_SACCHARIDE_1_4_LINKING", Biomol::ResidueType::L_SACCHARIDE_1_4_LINKING)
        .def_readonly("D_SACCHARIDE_1_4_LINKING", Biomol::ResidueType::D_SACCHARIDE_1_4_LINKING)
        .def_readonly("L_SACCHARIDE_ALPHA_LINKING", Biomol::ResidueType::L_SACCHARIDE_ALPHA_LINKING)
        .def_readonly("D_SACCHARIDE_ALPHA_LINKING", Biomol::ResidueType::D_SACCHARIDE_ALPHA_LINKING)
        .def_readonly("L_SACCHARIDE_BETA_LINKING", Biomol::ResidueType::L_SACCHARIDE_BETA_LINKING)
        .def_readonly("D_SACCHARIDE_BETA_LINKING", Biomol::ResidueType::D_SACCHARIDE_BETA_LINKING)
        .def_readonly("L_SACCHARIDE", Biomol::ResidueType::L_SACCHARIDE)
        .def_readonly("D_SACCHARIDE", Biomol::ResidueType::D_SACCHARIDE)
        .def_readonly("SACCHARIDE", Biomol::ResidueType::SACCHARIDE)
        ;
}
