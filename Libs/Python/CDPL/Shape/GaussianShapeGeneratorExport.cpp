/* 
 * GaussianShapeGeneratorExport.cpp 
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

#include "CDPL/Shape/GaussianShapeGenerator.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeGenerator()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (Shape::GaussianShapeGenerator::*SetBoolFunc)(bool);
	typedef bool (Shape::GaussianShapeGenerator::*GetBoolFunc)() const;

    python::class_<Shape::GaussianShapeGenerator, Shape::GaussianShapeGenerator::SharedPointer, boost::noncopyable>(
		"GaussianShapeGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShapeGenerator&>((python::arg("self"), python::arg("gen")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeGenerator>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::GaussianShapeGenerator::operator=), (python::arg("self"), python::arg("gen")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("setPharmacophoreGenerator", &Shape::GaussianShapeGenerator::setPharmacophoreGenerator,
			 (python::arg("self"), python::arg("gen")), python::with_custodian_and_ward<1, 2>())
		.def("getPharmacophoreGenerator", &Shape::GaussianShapeGenerator::getPharmacophoreGenerator,
			 python::arg("self"), python::return_internal_reference<>())
		.def("getDefaultPharmacophoreGenerator", static_cast<Pharm::DefaultPharmacophoreGenerator& (Shape::GaussianShapeGenerator::*)()>
			 (&Shape::GaussianShapeGenerator::getDefaultPharmacophoreGenerator),
			 python::arg("self"), python::return_internal_reference<>())
		.def("setAtomRadius", &Shape::GaussianShapeGenerator::setAtomRadius,
			 (python::arg("self"), python::arg("radius")))
		.def("getAtomRadius", &Shape::GaussianShapeGenerator::getAtomRadius,
			 python::arg("self"))
		.def("setAtomHardness", &Shape::GaussianShapeGenerator::setAtomHardness,
			 (python::arg("self"), python::arg("hardness")))
		.def("getAtomHardness", &Shape::GaussianShapeGenerator::getAtomHardness,
			 python::arg("self"))
		.def("setFeatureRadius", &Shape::GaussianShapeGenerator::setFeatureRadius,
			 (python::arg("self"), python::arg("radius")))
		.def("getFeatureRadius", &Shape::GaussianShapeGenerator::getFeatureRadius,
			 python::arg("self"))
		.def("setFeatureHardness", &Shape::GaussianShapeGenerator::setFeatureHardness,
			 (python::arg("self"), python::arg("hardness")))
		.def("getFeatureHardness", &Shape::GaussianShapeGenerator::getFeatureHardness,
			 python::arg("self"))
		.def("generatePharmacophoreShape", SetBoolFunc(&Shape::GaussianShapeGenerator::generatePharmacophoreShape), 
			 (python::arg("self"), python::arg("generate")))
		.def("generatePharmacophoreShape", GetBoolFunc(&Shape::GaussianShapeGenerator::generatePharmacophoreShape), 
			 python::arg("self"))
		.def("generateMoleculeShape", SetBoolFunc(&Shape::GaussianShapeGenerator::generateMoleculeShape), 
			 (python::arg("self"), python::arg("generate")))
		.def("generateMoleculeShape", GetBoolFunc(&Shape::GaussianShapeGenerator::generateMoleculeShape), 
			 python::arg("self"))
		.def("multiConformerMode", SetBoolFunc(&Shape::GaussianShapeGenerator::multiConformerMode), 
			 (python::arg("self"), python::arg("multi_conf")))
		.def("multiConformerMode", GetBoolFunc(&Shape::GaussianShapeGenerator::multiConformerMode), 
			 python::arg("self"))
		.def("includeHydrogens", SetBoolFunc(&Shape::GaussianShapeGenerator::includeHydrogens), 
			 (python::arg("self"), python::arg("include")))
		.def("includeHydrogens", GetBoolFunc(&Shape::GaussianShapeGenerator::includeHydrogens), 
			 python::arg("self"))
		.def("generate", &Shape::GaussianShapeGenerator::generate,
			 (python::arg("self"), python::arg("molgraph")), python::return_internal_reference<>())
		.def("getShapes", &Shape::GaussianShapeGenerator::getShapes,
			 python::arg("self"), python::return_internal_reference<>())
		.add_property("pharmacophoreGenerator",
					  python::make_function(&Shape::GaussianShapeGenerator::getPharmacophoreGenerator,
											python::return_internal_reference<>()),
					  python::make_function(&Shape::GaussianShapeGenerator::setPharmacophoreGenerator,
											python::with_custodian_and_ward<1, 2>()))
		.add_property("defPharmacophoreGenerator",
					  python::make_function(static_cast<Pharm::DefaultPharmacophoreGenerator& (Shape::GaussianShapeGenerator::*)()>
											(&Shape::GaussianShapeGenerator::getDefaultPharmacophoreGenerator),
											python::return_internal_reference<>()))
		.add_property("shapes", python::make_function(&Shape::GaussianShapeGenerator::getShapes,
													  python::return_internal_reference<>()))
		.add_property("genPharmacophoreShape", GetBoolFunc(&Shape::GaussianShapeGenerator::generatePharmacophoreShape),
					  SetBoolFunc(&Shape::GaussianShapeGenerator::generatePharmacophoreShape))
		.add_property("genMoleculeShape", GetBoolFunc(&Shape::GaussianShapeGenerator::generateMoleculeShape),
					  SetBoolFunc(&Shape::GaussianShapeGenerator::generateMoleculeShape))
		.add_property("multiConfMode", GetBoolFunc(&Shape::GaussianShapeGenerator::multiConformerMode),
					  SetBoolFunc(&Shape::GaussianShapeGenerator::multiConformerMode))
		.add_property("incHydrogens", GetBoolFunc(&Shape::GaussianShapeGenerator::includeHydrogens),
					  SetBoolFunc(&Shape::GaussianShapeGenerator::includeHydrogens))
		.add_property("atomRadius", &Shape::GaussianShapeGenerator::getAtomRadius,
					  &Shape::GaussianShapeGenerator::setAtomRadius)
		.add_property("atomHardness", &Shape::GaussianShapeGenerator::getAtomHardness,
					  &Shape::GaussianShapeGenerator::setAtomHardness)
		.add_property("featureRadius", &Shape::GaussianShapeGenerator::getFeatureRadius,
					  &Shape::GaussianShapeGenerator::setFeatureRadius)
		.add_property("featureHardness", &Shape::GaussianShapeGenerator::getFeatureHardness,
					  &Shape::GaussianShapeGenerator::setFeatureHardness);
}
