/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeAlignmentStartGeneratorExport.cpp 
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

#include "CDPL/Shape/GaussianShapeAlignmentStartGenerator.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct GaussianShapeAlignmentStartGeneratorWrapper :
		CDPL::Shape::GaussianShapeAlignmentStartGenerator, boost::python::wrapper<CDPL::Shape::GaussianShapeAlignmentStartGenerator> 
	{

		void setReference(const CDPL::Shape::GaussianShapeFunction& ref_shape_func, unsigned int sym_class) {
			this->get_override("setReference")(boost::ref(ref_shape_func), sym_class);
		}

		bool generate(const CDPL::Shape::GaussianShapeFunction& aligned_shape_func, unsigned int sym_class) {
			return this->get_override("generate")(boost::ref(aligned_shape_func), sym_class);
		}
			
		std::size_t getNumStartTransforms() const {
			return this->get_override("getNumStartTransforms")();
		}

		const CDPL::Shape::QuaternionTransformation& getStartTransform(std::size_t idx) const {
			return this->get_override("getStartTransform")(idx);
		}
	};
}


void CDPLPythonShape::exportGaussianShapeAlignmentStartGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GaussianShapeAlignmentStartGeneratorWrapper, boost::noncopyable>("GaussianShapeAlignmentStartGenerator", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeAlignmentStartGenerator>())
		.def("setReference", python::pure_virtual(&Shape::GaussianShapeAlignmentStartGenerator::setReference),
			 (python::arg("self"), python::arg("ref_shape_func"), python::arg("sym_class")))
		.def("generate", python::pure_virtual(&Shape::GaussianShapeAlignmentStartGenerator::generate),
			 (python::arg("self"), python::arg("aligned_shape_func"), python::arg("sym_class")))
		.def("getNumStartTransforms", python::pure_virtual(&Shape::GaussianShapeAlignmentStartGenerator::getNumStartTransforms),
			 python::arg("self"))
		.def("getStartTransform", python::pure_virtual(&Shape::GaussianShapeAlignmentStartGenerator::getStartTransform),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__len__", &Shape::GaussianShapeAlignmentStartGenerator::getNumStartTransforms,  python::arg("self"))
		.def("__getitem__", &Shape::GaussianShapeAlignmentStartGenerator::getStartTransform,
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>());
}
