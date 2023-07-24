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
        .value("HBD_N3_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_N3_COUNT)
        .value("HBD_N2_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_N2_COUNT)
        .value("HBD_Nar_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_Nar_COUNT)
        .value("HBD_Nam_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_Nam_COUNT)
        .value("HBD_Npl3_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_COUNT)
        .value("HBD_N4_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_N4_COUNT)
        .value("HBD_O3_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_O3_COUNT)
        .value("HBD_S3_COUNT", GRAIL::GRAILDescriptorCalculator::HBD_S3_COUNT)
        .value("HBA_N3_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_N3_COUNT)
        .value("HBA_N2_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_N2_COUNT)
        .value("HBA_N1_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_N1_COUNT)
        .value("HBA_Nar_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_Nar_COUNT)
        .value("HBA_Npl3_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_COUNT)
        .value("HBA_O3_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_O3_COUNT)
        .value("HBA_O2_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_O2_COUNT)
        .value("HBA_Oco2_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_COUNT)
        .value("HBA_S3_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_S3_COUNT)
        .value("HBA_S2_COUNT", GRAIL::GRAILDescriptorCalculator::HBA_S2_COUNT)
        .value("TOTAL_HYD", GRAIL::GRAILDescriptorCalculator::TOTAL_HYD)
        .value("LOGP", GRAIL::GRAILDescriptorCalculator::LOGP)
        .value("TPSA", GRAIL::GRAILDescriptorCalculator::TPSA)
        .value("ENV_HBA_N_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBA_N_OCC_SUM)
        .value("ENV_HBA_N_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBA_N_OCC_MAX)
        .value("ENV_HBA_O_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBA_O_OCC_SUM)
        .value("ENV_HBA_O_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBA_O_OCC_MAX)
        .value("ENV_HBA_S_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBA_S_OCC_SUM)
        .value("ENV_HBA_S_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBA_S_OCC_MAX)
        .value("ENV_HBD_N_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBD_N_OCC_SUM)
        .value("ENV_HBD_N_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBD_N_OCC_MAX)
        .value("ENV_HBD_O_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBD_O_OCC_SUM)
        .value("ENV_HBD_O_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBD_O_OCC_MAX)
        .value("ENV_HBD_S_OCC_SUM", GRAIL::GRAILDescriptorCalculator::ENV_HBD_S_OCC_SUM)
        .value("ENV_HBD_S_OCC_MAX", GRAIL::GRAILDescriptorCalculator::ENV_HBD_S_OCC_MAX)
        .value("PI_AR_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::PI_AR_SCORE_SUM)
        .value("PI_AR_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::PI_AR_SCORE_MAX)
        .value("AR_PI_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::AR_PI_SCORE_SUM)
        .value("AR_PI_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::AR_PI_SCORE_MAX)
        .value("H_H_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::H_H_SCORE_SUM)
        .value("H_H_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::H_H_SCORE_MAX)
        .value("AR_AR_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::AR_AR_SCORE_SUM)
        .value("AR_AR_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::AR_AR_SCORE_MAX)
        .value("HBD_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_HBA_N_SCORE_SUM)
        .value("HBD_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_HBA_N_SCORE_MAX)
        .value("HBD_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_HBA_O_SCORE_SUM)
        .value("HBD_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_HBA_O_SCORE_MAX)
        .value("HBD_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_HBA_S_SCORE_SUM)
        .value("HBD_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_HBA_S_SCORE_MAX)
        .value("HBD_N3_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N3_HBA_N_SCORE_SUM)
        .value("HBD_N3_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N3_HBA_N_SCORE_MAX)
        .value("HBD_N3_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N3_HBA_O_SCORE_SUM)
        .value("HBD_N3_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N3_HBA_O_SCORE_MAX)
        .value("HBD_N3_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N3_HBA_S_SCORE_SUM)
        .value("HBD_N3_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N3_HBA_S_SCORE_MAX)
        .value("HBD_N2_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N2_HBA_N_SCORE_SUM)
        .value("HBD_N2_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N2_HBA_N_SCORE_MAX)
        .value("HBD_N2_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N2_HBA_O_SCORE_SUM)
        .value("HBD_N2_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N2_HBA_O_SCORE_MAX)
        .value("HBD_N2_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N2_HBA_S_SCORE_SUM)
        .value("HBD_N2_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N2_HBA_S_SCORE_MAX)
        .value("HBD_Nar_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Nar_HBA_N_SCORE_SUM)
        .value("HBD_Nar_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Nar_HBA_N_SCORE_MAX)
        .value("HBD_Nar_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Nar_HBA_O_SCORE_SUM)
        .value("HBD_Nar_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Nar_HBA_O_SCORE_MAX)
        .value("HBD_Nar_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Nar_HBA_S_SCORE_SUM)
        .value("HBD_Nar_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Nar_HBA_S_SCORE_MAX)
        .value("HBD_Nam_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Nam_HBA_N_SCORE_SUM)
        .value("HBD_Nam_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Nam_HBA_N_SCORE_MAX)
        .value("HBD_Nam_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Nam_HBA_O_SCORE_SUM)
        .value("HBD_Nam_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Nam_HBA_O_SCORE_MAX)
        .value("HBD_Nam_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Nam_HBA_S_SCORE_SUM)
        .value("HBD_Nam_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Nam_HBA_S_SCORE_MAX)
        .value("HBD_Npl3_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_HBA_N_SCORE_SUM)
        .value("HBD_Npl3_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_HBA_N_SCORE_MAX)
        .value("HBD_Npl3_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_HBA_O_SCORE_SUM)
        .value("HBD_Npl3_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_HBA_O_SCORE_MAX)
        .value("HBD_Npl3_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_HBA_S_SCORE_SUM)
        .value("HBD_Npl3_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_Npl3_HBA_S_SCORE_MAX)
        .value("HBD_N4_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N4_HBA_N_SCORE_SUM)
        .value("HBD_N4_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N4_HBA_N_SCORE_MAX)
        .value("HBD_N4_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N4_HBA_O_SCORE_SUM)
        .value("HBD_N4_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N4_HBA_O_SCORE_MAX)
        .value("HBD_N4_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_N4_HBA_S_SCORE_SUM)
        .value("HBD_N4_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_N4_HBA_S_SCORE_MAX)
        .value("HBD_O3_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_O3_HBA_N_SCORE_SUM)
        .value("HBD_O3_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_O3_HBA_N_SCORE_MAX)
        .value("HBD_O3_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_O3_HBA_O_SCORE_SUM)
        .value("HBD_O3_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_O3_HBA_O_SCORE_MAX)
        .value("HBD_O3_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_O3_HBA_S_SCORE_SUM)
        .value("HBD_O3_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_O3_HBA_S_SCORE_MAX)
        .value("HBD_S3_HBA_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_S3_HBA_N_SCORE_SUM)
        .value("HBD_S3_HBA_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_S3_HBA_N_SCORE_MAX)
        .value("HBD_S3_HBA_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_S3_HBA_O_SCORE_SUM)
        .value("HBD_S3_HBA_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_S3_HBA_O_SCORE_MAX)
        .value("HBD_S3_HBA_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBD_S3_HBA_S_SCORE_SUM)
        .value("HBD_S3_HBA_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBD_S3_HBA_S_SCORE_MAX)
        .value("HBA_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_HBD_N_SCORE_SUM)
        .value("HBA_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_HBD_N_SCORE_MAX)
        .value("HBA_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_HBD_O_SCORE_SUM)
        .value("HBA_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_HBD_O_SCORE_MAX)
        .value("HBA_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_HBD_S_SCORE_SUM)
        .value("HBA_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_HBD_S_SCORE_MAX)
        .value("HBA_N3_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N3_HBD_N_SCORE_SUM)
        .value("HBA_N3_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N3_HBD_N_SCORE_MAX)
        .value("HBA_N3_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N3_HBD_O_SCORE_SUM)
        .value("HBA_N3_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N3_HBD_O_SCORE_MAX)
        .value("HBA_N3_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N3_HBD_S_SCORE_SUM)
        .value("HBA_N3_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N3_HBD_S_SCORE_MAX)
        .value("HBA_N2_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N2_HBD_N_SCORE_SUM)
        .value("HBA_N2_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N2_HBD_N_SCORE_MAX)
        .value("HBA_N2_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N2_HBD_O_SCORE_SUM)
        .value("HBA_N2_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N2_HBD_O_SCORE_MAX)
        .value("HBA_N2_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N2_HBD_S_SCORE_SUM)
        .value("HBA_N2_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N2_HBD_S_SCORE_MAX)
        .value("HBA_N1_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N1_HBD_N_SCORE_SUM)
        .value("HBA_N1_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N1_HBD_N_SCORE_MAX)
        .value("HBA_N1_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N1_HBD_O_SCORE_SUM)
        .value("HBA_N1_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N1_HBD_O_SCORE_MAX)
        .value("HBA_N1_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_N1_HBD_S_SCORE_SUM)
        .value("HBA_N1_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_N1_HBD_S_SCORE_MAX)
        .value("HBA_Nar_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Nar_HBD_N_SCORE_SUM)
        .value("HBA_Nar_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Nar_HBD_N_SCORE_MAX)
        .value("HBA_Nar_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Nar_HBD_O_SCORE_SUM)
        .value("HBA_Nar_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Nar_HBD_O_SCORE_MAX)
        .value("HBA_Nar_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Nar_HBD_S_SCORE_SUM)
        .value("HBA_Nar_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Nar_HBD_S_SCORE_MAX)
        .value("HBA_Npl3_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_HBD_N_SCORE_SUM)
        .value("HBA_Npl3_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_HBD_N_SCORE_MAX)
        .value("HBA_Npl3_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_HBD_O_SCORE_SUM)
        .value("HBA_Npl3_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_HBD_O_SCORE_MAX)
        .value("HBA_Npl3_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_HBD_S_SCORE_SUM)
        .value("HBA_Npl3_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Npl3_HBD_S_SCORE_MAX)
        .value("HBA_O3_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_O3_HBD_N_SCORE_SUM)
        .value("HBA_O3_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_O3_HBD_N_SCORE_MAX)
        .value("HBA_O3_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_O3_HBD_O_SCORE_SUM)
        .value("HBA_O3_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_O3_HBD_O_SCORE_MAX)
        .value("HBA_O3_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_O3_HBD_S_SCORE_SUM)
        .value("HBA_O3_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_O3_HBD_S_SCORE_MAX)
        .value("HBA_O2_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_O2_HBD_N_SCORE_SUM)
        .value("HBA_O2_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_O2_HBD_N_SCORE_MAX)
        .value("HBA_O2_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_O2_HBD_O_SCORE_SUM)
        .value("HBA_O2_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_O2_HBD_O_SCORE_MAX)
        .value("HBA_O2_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_O2_HBD_S_SCORE_SUM)
        .value("HBA_O2_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_O2_HBD_S_SCORE_MAX)
        .value("HBA_Oco2_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_HBD_N_SCORE_SUM)
        .value("HBA_Oco2_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_HBD_N_SCORE_MAX)
        .value("HBA_Oco2_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_HBD_O_SCORE_SUM)
        .value("HBA_Oco2_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_HBD_O_SCORE_MAX)
        .value("HBA_Oco2_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_HBD_S_SCORE_SUM)
        .value("HBA_Oco2_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_Oco2_HBD_S_SCORE_MAX)
        .value("HBA_S3_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_S3_HBD_N_SCORE_SUM)
        .value("HBA_S3_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_S3_HBD_N_SCORE_MAX)
        .value("HBA_S3_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_S3_HBD_O_SCORE_SUM)
        .value("HBA_S3_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_S3_HBD_O_SCORE_MAX)
        .value("HBA_S3_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_S3_HBD_S_SCORE_SUM)
        .value("HBA_S3_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_S3_HBD_S_SCORE_MAX)
        .value("HBA_S2_HBD_N_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_S2_HBD_N_SCORE_SUM)
        .value("HBA_S2_HBD_N_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_S2_HBD_N_SCORE_MAX)
        .value("HBA_S2_HBD_O_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_S2_HBD_O_SCORE_SUM)
        .value("HBA_S2_HBD_O_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_S2_HBD_O_SCORE_MAX)
        .value("HBA_S2_HBD_S_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::HBA_S2_HBD_S_SCORE_SUM)
        .value("HBA_S2_HBD_S_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::HBA_S2_HBD_S_SCORE_MAX)
        .value("XBD_XBA_SCORE_SUM", GRAIL::GRAILDescriptorCalculator::XBD_XBA_SCORE_SUM)
        .value("XBD_XBA_SCORE_MAX", GRAIL::GRAILDescriptorCalculator::XBD_XBA_SCORE_MAX)
        .value("ES_ENERGY", GRAIL::GRAILDescriptorCalculator::ES_ENERGY)
        .value("ES_ENERGY_SQRD_DIST", GRAIL::GRAILDescriptorCalculator::ES_ENERGY_SQRD_DIST)
        .value("VDW_ENERGY", GRAIL::GRAILDescriptorCalculator::VDW_ENERGY)
        .export_values();

    cls
        .def(python::init<>(python::arg("self")))
        .def(python::init<const GRAIL::GRAILDescriptorCalculator&>((python::arg("self"), python::arg("calc"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::GRAILDescriptorCalculator>())
        .def("assign", CDPLPythonBase::copyAssOp(&GRAIL::GRAILDescriptorCalculator::operator=),
             (python::arg("self"), python::arg("calc")), python::return_self<>())
        .def("initTargetData", &GRAIL::GRAILDescriptorCalculator::initTargetData,
             (python::arg("self"), python::arg("tgt_env"), python::arg("coords_func"), python::arg("tgt_env_changed") = true))
        .def("initLigandData", &GRAIL::GRAILDescriptorCalculator::initLigandData, (python::arg("self"), python::arg("ligand")))
        .def("calculate", &GRAIL::GRAILDescriptorCalculator::calculate,
             (python::arg("self"), python::arg("atom_coords"), python::arg("descr"), python::arg("update_lig_part") = true))
        .def_readonly("TOTAL_DESCRIPTOR_SIZE", GRAIL::GRAILDescriptorCalculator::TOTAL_DESCRIPTOR_SIZE)
        .def_readonly("LIGAND_DESCRIPTOR_SIZE", GRAIL::GRAILDescriptorCalculator::LIGAND_DESCRIPTOR_SIZE);
}
