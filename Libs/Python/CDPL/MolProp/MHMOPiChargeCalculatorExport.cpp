/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MHMOPiChargeCalculatorExport.cpp 
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

#include "CDPL/MolProp/MHMOPiChargeCalculator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonMolProp::exportMHMOPiChargeCalculator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<MolProp::MHMOPiChargeCalculator, boost::noncopyable>("MHMOPiChargeCalculator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::MolecularGraph&>((python::arg("self"), python::arg("molgraph"))))
		.def(python::init<const Chem::ElectronSystemList&, const Chem::MolecularGraph&>((python::arg("self"), python::arg("pi_sys_list"), python::arg("molgraph"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MolProp::MHMOPiChargeCalculator>())
		.def("localizedPiBonds", static_cast<void (MolProp::MHMOPiChargeCalculator::*)(bool)>(&MolProp::MHMOPiChargeCalculator::localizedPiBonds),
			 (python::arg("self"), python::arg("localized")))
		.def("localizedPiBonds", static_cast<bool (MolProp::MHMOPiChargeCalculator::*)() const>(&MolProp::MHMOPiChargeCalculator::localizedPiBonds),
			 python::arg("localized"))
		.def("calculate", static_cast<void (MolProp::MHMOPiChargeCalculator::*)(
				 const Chem::MolecularGraph&)>(&MolProp::MHMOPiChargeCalculator::calculate),
			 (python::arg("self"), python::arg("molgraph")))
		.def("calculate", static_cast<void (MolProp::MHMOPiChargeCalculator::*)(
				 const Chem::ElectronSystemList&, const Chem::MolecularGraph&)>(&MolProp::MHMOPiChargeCalculator::calculate),
			 (python::arg("self"), python::arg("pi_sys_list"), python::arg("molgraph")))
		.def("getElectronDensity", &MolProp::MHMOPiChargeCalculator::getElectronDensity, (python::arg("self"), python::arg("atom_idx")))
		.def("getCharge", &MolProp::MHMOPiChargeCalculator::getCharge, (python::arg("self"), python::arg("atom_idx")))
		.def("getBondOrder", &MolProp::MHMOPiChargeCalculator::getBondOrder, (python::arg("self"), python::arg("bond_idx")))
		.def("getEnergy", &MolProp::MHMOPiChargeCalculator::getEnergy, python::arg("self"))
		.add_property("locPiBonds", static_cast<bool (MolProp::MHMOPiChargeCalculator::*)() const>(&MolProp::MHMOPiChargeCalculator::localizedPiBonds),
					  static_cast<void (MolProp::MHMOPiChargeCalculator::*)(bool)>(&MolProp::MHMOPiChargeCalculator::localizedPiBonds))
		.add_property("energy", &MolProp::MHMOPiChargeCalculator::getEnergy);
}
