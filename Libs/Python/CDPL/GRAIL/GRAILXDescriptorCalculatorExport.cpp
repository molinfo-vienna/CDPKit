/* 
 * GRAILXDescriptorCalculatorExport.cpp 
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

#include "CDPL/GRAIL/GRAILXDescriptorCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonGRAIL::exportGRAILXDescriptorCalculator()
{
    using namespace boost;
    using namespace CDPL;
  
    python::class_<GRAIL::GRAILXDescriptorCalculator, GRAIL::GRAILXDescriptorCalculator::SharedPointer,
               boost::noncopyable> cls("GRAILXDescriptorCalculator", python::no_init);

    python::scope scope = cls;

    python::enum_<GRAIL::GRAILXDescriptorCalculator::ElementIndex>("ElementIndex")
        .value("PI_COUNT", GRAIL::GRAILXDescriptorCalculator::PI_COUNT)
        .value("NI_COUNT", GRAIL::GRAILXDescriptorCalculator::NI_COUNT)
        .value("AR_COUNT", GRAIL::GRAILXDescriptorCalculator::AR_COUNT)
        .value("H_COUNT", GRAIL::GRAILXDescriptorCalculator::H_COUNT)
        .value("HBD_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_COUNT)
        .value("HBA_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_COUNT)
        .value("XBD_COUNT", GRAIL::GRAILXDescriptorCalculator::XBD_COUNT)
        .value("XBA_COUNT", GRAIL::GRAILXDescriptorCalculator::XBA_COUNT)
        .value("HBD_N3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_N3_COUNT)
        .value("HBD_N2_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_N2_COUNT)
        .value("HBD_Nar_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_COUNT)
        .value("HBD_Nam_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_COUNT)
        .value("HBD_Npl3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_COUNT)
        .value("HBD_N4_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_N4_COUNT)
        .value("HBD_O3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_O3_COUNT)
        .value("HBD_S3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBD_S3_COUNT)
        .value("HBA_N3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_N3_COUNT)
        .value("HBA_N2_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_N2_COUNT)
        .value("HBA_N1_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_N1_COUNT)
        .value("HBA_Nar_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_COUNT)
        .value("HBA_Npl3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_COUNT)
        .value("HBA_O3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_O3_COUNT)
        .value("HBA_O2_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_O2_COUNT)
        .value("HBA_Oco2_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_COUNT)
        .value("HBA_S3_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_S3_COUNT)
        .value("HBA_S2_COUNT", GRAIL::GRAILXDescriptorCalculator::HBA_S2_COUNT)
        .value("HVY_ATOM_COUNT", GRAIL::GRAILXDescriptorCalculator::HVY_ATOM_COUNT)
        .value("ROT_BOND_COUNT", GRAIL::GRAILXDescriptorCalculator::ROT_BOND_COUNT)
        .value("TOTAL_HYD", GRAIL::GRAILXDescriptorCalculator::TOTAL_HYD)
        .value("LOGP", GRAIL::GRAILXDescriptorCalculator::LOGP)
        .value("TPSA", GRAIL::GRAILXDescriptorCalculator::TPSA)
        .value("ENV_HBA_N_OCC_SUM", GRAIL::GRAILXDescriptorCalculator::ENV_HBA_N_OCC_SUM)
        .value("ENV_HBA_N_OCC_MAX", GRAIL::GRAILXDescriptorCalculator::ENV_HBA_N_OCC_MAX)
        .value("ENV_HBA_O_OCC_SUM", GRAIL::GRAILXDescriptorCalculator::ENV_HBA_O_OCC_SUM)
        .value("ENV_HBA_O_OCC_MAX", GRAIL::GRAILXDescriptorCalculator::ENV_HBA_O_OCC_MAX)
        .value("ENV_HBA_S_OCC_SUM", GRAIL::GRAILXDescriptorCalculator::ENV_HBA_S_OCC_SUM)
        .value("ENV_HBA_S_OCC_MAX", GRAIL::GRAILXDescriptorCalculator::ENV_HBA_S_OCC_MAX)
        .value("ENV_HBD_N_OCC_SUM", GRAIL::GRAILXDescriptorCalculator::ENV_HBD_N_OCC_SUM)
        .value("ENV_HBD_N_OCC_MAX", GRAIL::GRAILXDescriptorCalculator::ENV_HBD_N_OCC_MAX)
        .value("ENV_HBD_O_OCC_SUM", GRAIL::GRAILXDescriptorCalculator::ENV_HBD_O_OCC_SUM)
        .value("ENV_HBD_O_OCC_MAX", GRAIL::GRAILXDescriptorCalculator::ENV_HBD_O_OCC_MAX)
        .value("ENV_HBD_S_OCC_SUM", GRAIL::GRAILXDescriptorCalculator::ENV_HBD_S_OCC_SUM)
        .value("ENV_HBD_S_OCC_MAX", GRAIL::GRAILXDescriptorCalculator::ENV_HBD_S_OCC_MAX)
        .value("PI_AR_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::PI_AR_SCORE_SUM)
        .value("PI_AR_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::PI_AR_SCORE_MAX)
        .value("AR_PI_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::AR_PI_SCORE_SUM)
        .value("AR_PI_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::AR_PI_SCORE_MAX)
        .value("H_H_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::H_H_SCORE_SUM)
        .value("H_H_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::H_H_SCORE_MAX)
        .value("AR_AR_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::AR_AR_SCORE_SUM)
        .value("AR_AR_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::AR_AR_SCORE_MAX)
        .value("HBD_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_HBA_N_SCORE_SUM)
        .value("HBD_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_HBA_N_SCORE_MAX)
        .value("HBD_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_HBA_O_SCORE_SUM)
        .value("HBD_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_HBA_O_SCORE_MAX)
        .value("HBD_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_HBA_S_SCORE_SUM)
        .value("HBD_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_HBA_S_SCORE_MAX)
        .value("HBD_N3_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N3_HBA_N_SCORE_SUM)
        .value("HBD_N3_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N3_HBA_N_SCORE_MAX)
        .value("HBD_N3_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N3_HBA_O_SCORE_SUM)
        .value("HBD_N3_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N3_HBA_O_SCORE_MAX)
        .value("HBD_N3_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N3_HBA_S_SCORE_SUM)
        .value("HBD_N3_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N3_HBA_S_SCORE_MAX)
        .value("HBD_N2_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N2_HBA_N_SCORE_SUM)
        .value("HBD_N2_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N2_HBA_N_SCORE_MAX)
        .value("HBD_N2_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N2_HBA_O_SCORE_SUM)
        .value("HBD_N2_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N2_HBA_O_SCORE_MAX)
        .value("HBD_N2_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N2_HBA_S_SCORE_SUM)
        .value("HBD_N2_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N2_HBA_S_SCORE_MAX)
        .value("HBD_Nar_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_HBA_N_SCORE_SUM)
        .value("HBD_Nar_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_HBA_N_SCORE_MAX)
        .value("HBD_Nar_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_HBA_O_SCORE_SUM)
        .value("HBD_Nar_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_HBA_O_SCORE_MAX)
        .value("HBD_Nar_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_HBA_S_SCORE_SUM)
        .value("HBD_Nar_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Nar_HBA_S_SCORE_MAX)
        .value("HBD_Nam_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_HBA_N_SCORE_SUM)
        .value("HBD_Nam_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_HBA_N_SCORE_MAX)
        .value("HBD_Nam_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_HBA_O_SCORE_SUM)
        .value("HBD_Nam_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_HBA_O_SCORE_MAX)
        .value("HBD_Nam_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_HBA_S_SCORE_SUM)
        .value("HBD_Nam_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Nam_HBA_S_SCORE_MAX)
        .value("HBD_Npl3_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_HBA_N_SCORE_SUM)
        .value("HBD_Npl3_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_HBA_N_SCORE_MAX)
        .value("HBD_Npl3_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_HBA_O_SCORE_SUM)
        .value("HBD_Npl3_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_HBA_O_SCORE_MAX)
        .value("HBD_Npl3_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_HBA_S_SCORE_SUM)
        .value("HBD_Npl3_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_Npl3_HBA_S_SCORE_MAX)
        .value("HBD_N4_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N4_HBA_N_SCORE_SUM)
        .value("HBD_N4_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N4_HBA_N_SCORE_MAX)
        .value("HBD_N4_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N4_HBA_O_SCORE_SUM)
        .value("HBD_N4_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N4_HBA_O_SCORE_MAX)
        .value("HBD_N4_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_N4_HBA_S_SCORE_SUM)
        .value("HBD_N4_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_N4_HBA_S_SCORE_MAX)
        .value("HBD_O3_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_O3_HBA_N_SCORE_SUM)
        .value("HBD_O3_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_O3_HBA_N_SCORE_MAX)
        .value("HBD_O3_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_O3_HBA_O_SCORE_SUM)
        .value("HBD_O3_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_O3_HBA_O_SCORE_MAX)
        .value("HBD_O3_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_O3_HBA_S_SCORE_SUM)
        .value("HBD_O3_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_O3_HBA_S_SCORE_MAX)
        .value("HBD_S3_HBA_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_S3_HBA_N_SCORE_SUM)
        .value("HBD_S3_HBA_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_S3_HBA_N_SCORE_MAX)
        .value("HBD_S3_HBA_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_S3_HBA_O_SCORE_SUM)
        .value("HBD_S3_HBA_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_S3_HBA_O_SCORE_MAX)
        .value("HBD_S3_HBA_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBD_S3_HBA_S_SCORE_SUM)
        .value("HBD_S3_HBA_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBD_S3_HBA_S_SCORE_MAX)
        .value("HBA_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_HBD_N_SCORE_SUM)
        .value("HBA_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_HBD_N_SCORE_MAX)
        .value("HBA_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_HBD_O_SCORE_SUM)
        .value("HBA_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_HBD_O_SCORE_MAX)
        .value("HBA_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_HBD_S_SCORE_SUM)
        .value("HBA_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_HBD_S_SCORE_MAX)
        .value("HBA_N3_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N3_HBD_N_SCORE_SUM)
        .value("HBA_N3_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N3_HBD_N_SCORE_MAX)
        .value("HBA_N3_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N3_HBD_O_SCORE_SUM)
        .value("HBA_N3_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N3_HBD_O_SCORE_MAX)
        .value("HBA_N3_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N3_HBD_S_SCORE_SUM)
        .value("HBA_N3_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N3_HBD_S_SCORE_MAX)
        .value("HBA_N2_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N2_HBD_N_SCORE_SUM)
        .value("HBA_N2_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N2_HBD_N_SCORE_MAX)
        .value("HBA_N2_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N2_HBD_O_SCORE_SUM)
        .value("HBA_N2_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N2_HBD_O_SCORE_MAX)
        .value("HBA_N2_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N2_HBD_S_SCORE_SUM)
        .value("HBA_N2_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N2_HBD_S_SCORE_MAX)
        .value("HBA_N1_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N1_HBD_N_SCORE_SUM)
        .value("HBA_N1_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N1_HBD_N_SCORE_MAX)
        .value("HBA_N1_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N1_HBD_O_SCORE_SUM)
        .value("HBA_N1_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N1_HBD_O_SCORE_MAX)
        .value("HBA_N1_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_N1_HBD_S_SCORE_SUM)
        .value("HBA_N1_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_N1_HBD_S_SCORE_MAX)
        .value("HBA_Nar_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_HBD_N_SCORE_SUM)
        .value("HBA_Nar_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_HBD_N_SCORE_MAX)
        .value("HBA_Nar_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_HBD_O_SCORE_SUM)
        .value("HBA_Nar_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_HBD_O_SCORE_MAX)
        .value("HBA_Nar_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_HBD_S_SCORE_SUM)
        .value("HBA_Nar_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Nar_HBD_S_SCORE_MAX)
        .value("HBA_Npl3_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_HBD_N_SCORE_SUM)
        .value("HBA_Npl3_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_HBD_N_SCORE_MAX)
        .value("HBA_Npl3_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_HBD_O_SCORE_SUM)
        .value("HBA_Npl3_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_HBD_O_SCORE_MAX)
        .value("HBA_Npl3_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_HBD_S_SCORE_SUM)
        .value("HBA_Npl3_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Npl3_HBD_S_SCORE_MAX)
        .value("HBA_O3_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_O3_HBD_N_SCORE_SUM)
        .value("HBA_O3_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_O3_HBD_N_SCORE_MAX)
        .value("HBA_O3_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_O3_HBD_O_SCORE_SUM)
        .value("HBA_O3_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_O3_HBD_O_SCORE_MAX)
        .value("HBA_O3_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_O3_HBD_S_SCORE_SUM)
        .value("HBA_O3_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_O3_HBD_S_SCORE_MAX)
        .value("HBA_O2_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_O2_HBD_N_SCORE_SUM)
        .value("HBA_O2_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_O2_HBD_N_SCORE_MAX)
        .value("HBA_O2_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_O2_HBD_O_SCORE_SUM)
        .value("HBA_O2_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_O2_HBD_O_SCORE_MAX)
        .value("HBA_O2_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_O2_HBD_S_SCORE_SUM)
        .value("HBA_O2_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_O2_HBD_S_SCORE_MAX)
        .value("HBA_Oco2_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_HBD_N_SCORE_SUM)
        .value("HBA_Oco2_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_HBD_N_SCORE_MAX)
        .value("HBA_Oco2_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_HBD_O_SCORE_SUM)
        .value("HBA_Oco2_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_HBD_O_SCORE_MAX)
        .value("HBA_Oco2_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_HBD_S_SCORE_SUM)
        .value("HBA_Oco2_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_Oco2_HBD_S_SCORE_MAX)
        .value("HBA_S3_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_S3_HBD_N_SCORE_SUM)
        .value("HBA_S3_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_S3_HBD_N_SCORE_MAX)
        .value("HBA_S3_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_S3_HBD_O_SCORE_SUM)
        .value("HBA_S3_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_S3_HBD_O_SCORE_MAX)
        .value("HBA_S3_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_S3_HBD_S_SCORE_SUM)
        .value("HBA_S3_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_S3_HBD_S_SCORE_MAX)
        .value("HBA_S2_HBD_N_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_S2_HBD_N_SCORE_SUM)
        .value("HBA_S2_HBD_N_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_S2_HBD_N_SCORE_MAX)
        .value("HBA_S2_HBD_O_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_S2_HBD_O_SCORE_SUM)
        .value("HBA_S2_HBD_O_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_S2_HBD_O_SCORE_MAX)
        .value("HBA_S2_HBD_S_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::HBA_S2_HBD_S_SCORE_SUM)
        .value("HBA_S2_HBD_S_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::HBA_S2_HBD_S_SCORE_MAX)
        .value("XBD_XBA_SCORE_SUM", GRAIL::GRAILXDescriptorCalculator::XBD_XBA_SCORE_SUM)
        .value("XBD_XBA_SCORE_MAX", GRAIL::GRAILXDescriptorCalculator::XBD_XBA_SCORE_MAX)
        .value("ES_ENERGY", GRAIL::GRAILXDescriptorCalculator::ES_ENERGY)
        .value("ES_ENERGY_SQRD_DIST", GRAIL::GRAILXDescriptorCalculator::ES_ENERGY_SQRD_DIST)
        .value("VDW_ENERGY_ATT", GRAIL::GRAILXDescriptorCalculator::VDW_ENERGY_ATT)
        .value("VDW_ENERGY_REP", GRAIL::GRAILXDescriptorCalculator::VDW_ENERGY_REP)
        .export_values();

    cls
        .def(python::init<>(python::arg("self")))
        .def(python::init<const GRAIL::GRAILXDescriptorCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::GRAILXDescriptorCalculator>())
        .def("assign", CDPLPythonBase::copyAssOp<GRAIL::GRAILXDescriptorCalculator>(),
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("initTargetData", &GRAIL::GRAILXDescriptorCalculator::initTargetData,
             (python::arg("self"), python::arg("tgt_env"), python::arg("coords_func"), python::arg("tgt_env_changed") = true))
        .def("initLigandData", &GRAIL::GRAILXDescriptorCalculator::initLigandData, (python::arg("self"), python::arg("ligand")))
        .def("calculate", &GRAIL::GRAILXDescriptorCalculator::calculate,
             (python::arg("self"), python::arg("atom_coords"), python::arg("descr"), python::arg("update_lig_part") = true))
        .def_readonly("TOTAL_DESCRIPTOR_SIZE", GRAIL::GRAILXDescriptorCalculator::TOTAL_DESCRIPTOR_SIZE)
        .def_readonly("LIGAND_DESCRIPTOR_SIZE", GRAIL::GRAILXDescriptorCalculator::LIGAND_DESCRIPTOR_SIZE);
}
