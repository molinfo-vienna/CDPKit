/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RMSDConformerSelectorExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
		.def("setup", &ConfGen::RMSDConformerSelector::setup, 
			 (python::arg("self"), python::arg("molgraph"), python::arg("atom_mask"), python::arg("stable_config_atom_mask")),
			 python::with_custodian_and_ward<1, 2>())
		.def("process", &ConfGen::RMSDConformerSelector::process, 
			 (python::arg("self"), python::arg("conf_data")), python::with_custodian_and_ward<1, 2>())
		.def("clearConformers", &ConfGen::RMSDConformerSelector::clearConformers, python::arg("self"))
		.def("getNumConformers", &ConfGen::RMSDConformerSelector::getNumConformers, python::arg("self"))
		.def("getConformer", &ConfGen::RMSDConformerSelector::getConformer,
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.def("__getitem__", &ConfGen::RMSDConformerSelector::getConformer,
			 (python::arg("self"), python::arg("conf_idx")), python::return_internal_reference<>())
		.add_property("numConformers", &ConfGen::RMSDConformerSelector::getNumConformers)
		;
}
