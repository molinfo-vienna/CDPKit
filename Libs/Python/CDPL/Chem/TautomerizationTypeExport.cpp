/* 
 * TautomerizationTypeExport.cpp 
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

#include "CDPL/Chem/TautomerizationType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct TautomerizationType {};
}


void CDPLPythonChem::exportTautomerizationTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<TautomerizationType, boost::noncopyable>("TautomerizationType", python::no_init)
        .def_readonly("KETO_ENOL", &Chem::TautomerizationType::KETO_ENOL)
        .def_readonly("IMINE_ENAMINE", &Chem::TautomerizationType::IMINE_ENAMINE)
        .def_readonly("NITROSO_OXIME", &Chem::TautomerizationType::NITROSO_OXIME)
        .def_readonly("AMIDE_IMIDIC_ACID", &Chem::TautomerizationType::AMIDE_IMIDIC_ACID)
        .def_readonly("LACTAM_LACTIM", &Chem::TautomerizationType::LACTAM_LACTIM)
        .def_readonly("KETENE_YNOL", &Chem::TautomerizationType::KETENE_YNOL)
        .def_readonly("NITRO_ACI", &Chem::TautomerizationType::NITRO_ACI)
        .def_readonly("PHOSPHINIC_ACID", &Chem::TautomerizationType::PHOSPHINIC_ACID)
        .def_readonly("SULFENIC_ACID", &Chem::TautomerizationType::SULFENIC_ACID)
        .def_readonly("GENERIC_H_13_SHIFT", &Chem::TautomerizationType::GENERIC_H_13_SHIFT)
        .def_readonly("GENERIC_H_15_SHIFT", &Chem::TautomerizationType::GENERIC_H_15_SHIFT)
        .def_readonly("CONJ_RING_BOND_SWITCH", &Chem::TautomerizationType::CONJ_RING_BOND_SWITCH);
}
