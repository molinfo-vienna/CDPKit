/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RMSDConformerSelectorExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/ConfGen/RMSDConformerSelector.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportRMSDConformerSelector()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<ConfGen::RMSDConformerSelector, boost::noncopyable>("RMSDConformerSelector", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::RMSDConformerSelector>())
		.def("setMinRMSD", &ConfGen::RMSDConformerSelector::setMinRMSD, (python::arg("self"), python::arg("min_rmsd")))
		.def("getMinRMSD", &ConfGen::RMSDConformerSelector::getMinRMSD, python::arg("self"))
		.def("setAbortCallback", &ConfGen::RMSDConformerSelector::setAbortCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getAbortCallback", &ConfGen::RMSDConformerSelector::getAbortCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("getNumSymmetryMappings", &ConfGen::RMSDConformerSelector::getNumSymmetryMappings, python::arg("self"))
		.def("setMaxNumSymmetryMappings", &ConfGen::RMSDConformerSelector::setMaxNumSymmetryMappings, (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumSymmetryMappings", &ConfGen::RMSDConformerSelector::getMaxNumSymmetryMappings, python::arg("self"))
		.def("setup", 
			 static_cast<void (ConfGen::RMSDConformerSelector::*)(const Chem::MolecularGraph&, const Util::BitSet&, const Util::BitSet&, const Math::Vector3DArray&)>
			 (&ConfGen::RMSDConformerSelector::setup), 
			 (python::arg("self"), python::arg("molgraph"), python::arg("atom_mask"), python::arg("stable_config_atom_mask"),
			  python::arg("coords")), python::with_custodian_and_ward<1, 2>())
		.def("setup", 
			 static_cast<void (ConfGen::RMSDConformerSelector::*)(const Chem::MolecularGraph&, const Util::BitSet&)>
			 (&ConfGen::RMSDConformerSelector::setup), 
			 (python::arg("self"), python::arg("molgraph"), python::arg("atom_mask")), python::with_custodian_and_ward<1, 2>())
		.def("selected", &ConfGen::RMSDConformerSelector::selected, 
			 (python::arg("self"), python::arg("conf_coords")), python::with_custodian_and_ward<1, 2>())
		.def_readonly("DEF_MAX_NUM_SYMMETRY_MAPPINGS", ConfGen::RMSDConformerSelector::DEF_MAX_NUM_SYMMETRY_MAPPINGS)
		.add_property("abortCallback", 
					  python::make_function(&ConfGen::RMSDConformerSelector::getAbortCallback,
											python::return_internal_reference<>()),
					  &ConfGen::RMSDConformerSelector::setAbortCallback)
		.add_property("numSymmetryMappings", &ConfGen::RMSDConformerSelector::getNumSymmetryMappings)
		.add_property("maxNumSymmetryMappings", &ConfGen::RMSDConformerSelector::getMaxNumSymmetryMappings,
					  &ConfGen::RMSDConformerSelector::setMaxNumSymmetryMappings)
		.add_property("minRMSD", &ConfGen::RMSDConformerSelector::getMinRMSD, &ConfGen::RMSDConformerSelector::setMinRMSD);
}
