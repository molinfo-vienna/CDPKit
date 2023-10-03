/* 
 * GRAILDescriptorCalculatorExport.cpp 
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

#include "CDPL/GRAIL/GRAILDescriptorCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAIL::exportGRAILDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;
  
    python::class_<GRAIL::GRAILDescriptorCalculator, GRAIL::GRAILDescriptorCalculator::SharedPointer,
               boost::noncopyable> cls("GRAILDescriptorCalculator", python::no_init);

    python::scope scope = cls;

    python::enum_<GRAIL::GRAILDescriptorCalculator::ElementIndex>("ElementIndex")
        .value("PI_COUNT", GRAIL::GRAILDescriptorCalculator::PI_COUNT)
        .value("NI_COUNT", GRAIL::GRAILDescriptorCalculator::NI_COUNT)
        .value("AR_COUNT", GRAIL::GRAILDescriptorCalculator::AR_COUNT)
        .value("H_COUNT", GRAIL::GRAILDescriptorCalculator::H_COUNT)
        .value("HBD_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_COUNT)
        .value("HBA_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_COUNT)
        .value("XBD_COUNT", GRAIL::GRAILDescriptorCalculator::XBD_COUNT)
        .value("XBA_COUNT", GRAIL::GRAILDescriptorCalculator::XBA_COUNT)
        .value("HVY_ATOM_COUNT", GRAIL::GRAILDescriptorCalculator::HVY_ATOM_COUNT)
        .value("ROT_BOND_COUNT", GRAIL::GRAILDescriptorCalculator::ROT_BOND_COUNT)
        .value("TOTAL_HYD", GRAIL::GRAILDescriptorCalculator::TOTAL_HYD)
        .value("LOGP", GRAIL::GRAILDescriptorCalculator::LOGP)
        .value("TPSA", GRAIL::GRAILDescriptorCalculator::TPSA)
        .value("ENV_HBA_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBA_OCC_SUM)
        .value("ENV_HBA_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBA_OCC_MAX)
        .value("ENV_HBD_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBD_OCC_SUM)
        .value("ENV_HBD_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBD_OCC_MAX)
        .value("PI_AR_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::PI_AR_SCORE_SUM)
        .value("PI_AR_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::PI_AR_SCORE_MAX)
        .value("AR_PI_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::AR_PI_SCORE_SUM)
        .value("AR_PI_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::AR_PI_SCORE_MAX)
        .value("H_H_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::H_H_SCORE_SUM)
        .value("H_H_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::H_H_SCORE_MAX)
        .value("AR_AR_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::AR_AR_SCORE_SUM)
        .value("AR_AR_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::AR_AR_SCORE_MAX)
        .value("HBD_HBA_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_HBA_SCORE_SUM)
        .value("HBD_HBA_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_HBA_SCORE_MAX)
        .value("HBA_HBD_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_HBD_SCORE_SUM)
        .value("HBA_HBD_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_HBD_SCORE_MAX)
        .value("XBD_XBA_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::XBD_XBA_SCORE_SUM)
        .value("XBD_XBA_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::XBD_XBA_SCORE_MAX)
        .value("ES_ENERGY", GRAIL::GRAILDescriptorCalculator::ES_ENERGY)
        .value("ES_ENERGY_SQRD_DIST", GRAIL::GRAILDescriptorCalculator::ES_ENERGY_SQRD_DIST)
        .value("VDW_ENERGY_ATT", GRAIL::GRAILDescriptorCalculator::VDW_ENERGY_ATT)
        .value("VDW_ENERGY_REP", GRAIL::GRAILDescriptorCalculator::VDW_ENERGY_REP)
        .export_values();

    cls
        .def(python::init<>(python::arg("self")))
        .def(python::init<const GRAIL::GRAILDescriptorCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::GRAILDescriptorCalculator>())
        .def("assign", CDPLPythonBase::copyAssOp<GRAIL::GRAILDescriptorCalculator>(),
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("initTargetData", &GRAIL::GRAILDescriptorCalculator::initTargetData,
             (python::arg("self"), python::arg("tgt_env"), python::arg("coords_func"), python::arg("tgt_env_changed") = true))
        .def("initLigandData", &GRAIL::GRAILDescriptorCalculator::initLigandData, (python::arg("self"), python::arg("ligand")))
        .def("calculate", &GRAIL::GRAILDescriptorCalculator::calculate,
             (python::arg("self"), python::arg("atom_coords"), python::arg("descr"), python::arg("update_lig_part") = true))
        .def_readonly("TOTAL_DESCRIPTOR_SIZE", GRAIL::GRAILDescriptorCalculator::TOTAL_DESCRIPTOR_SIZE)
        .def_readonly("LIGAND_DESCRIPTOR_SIZE", GRAIL::GRAILDescriptorCalculator::LIGAND_DESCRIPTOR_SIZE);
}
