/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HBondDonorFeatureGeneratorExport.cpp 
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

#include "CDPL/Pharm/HBondDonorFeatureGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"

#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportHBondDonorFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::HBondDonorFeatureGenerator, python::bases<Pharm::PatternBasedFeatureGenerator>,
				   boost::noncopyable>("HBondDonorFeatureGenerator", python::no_init)
		.def(python::init<bool>((python::arg("self"), python::arg("static_h_bonds"))))
		.def(python::init<const Pharm::HBondDonorFeatureGenerator&>(
				 (python::arg("self"), python::arg("gen"))))
		.def(python::init<const Chem::MolecularGraph&, Pharm::Pharmacophore&, bool>(
				 (python::arg("self"), python::arg("molgraph"), python::arg("pharm"), python::arg("static_h_bonds"))))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::HBondDonorFeatureGenerator::operator=), 
			 (python::arg("self"), python::arg("gen")), python::return_self<>());
}
