/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalFeatureMappingExtractorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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

#include "CDPL/Chem/GeometricalFeatureMappingExtractor.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{
	
	static void setConstraintFunc1(CDPL::Chem::GeometricalFeatureMappingExtractor& xtor, 
								   const boost::python::object& callable) 
	{
		if (callable.ptr() == Py_None)
			xtor.setFeatureTypeMatchFunction(CDPL::Chem::GeometricalFeatureMappingExtractor::FeatureTypeMatchFunction());
		else
			xtor.setFeatureTypeMatchFunction(CDPLPythonBase::BinaryFunctionAdapter<bool, CDPL::Chem::Feature, 
											 CDPL::Chem::Feature>(callable)); 
	}

	static void setConstraintFunc2(CDPL::Chem::GeometricalFeatureMappingExtractor& xtor, 
								   const boost::python::object& callable) 
	{
		if (callable.ptr() == Py_None)
			xtor.setFeaturePositionMatchFunction(CDPL::Chem::GeometricalFeatureMappingExtractor::FeaturePositionMatchFunction());
		else
			xtor.setFeaturePositionMatchFunction(CDPLPythonBase::TernaryFunctionAdapter<bool, CDPL::Chem::Feature, 
												 CDPL::Chem::Feature, CDPL::Math::Matrix4D>(callable)); 
	}

	static void setConstraintFunc3(CDPL::Chem::GeometricalFeatureMappingExtractor& xtor, 
								   const boost::python::object& callable) 
	{
		if (callable.ptr() == Py_None)
			xtor.setFeatureGeometryMatchFunction(CDPL::Chem::GeometricalFeatureMappingExtractor::FeatureGeometryMatchFunction());
		else
			xtor.setFeatureGeometryMatchFunction(CDPLPythonBase::TernaryFunctionAdapter<bool, CDPL::Chem::Feature, 
												 CDPL::Chem::Feature, CDPL::Math::Matrix4D>(callable)); 
	}

	static bool constrFunc1Call(CDPL::Chem::GeometricalFeatureMappingExtractor::FeatureTypeMatchFunction& func, 
								CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2) 
	{
		return func(ftr1, ftr2);
	}

	static bool constrFunc2Call(CDPL::Chem::GeometricalFeatureMappingExtractor::FeaturePositionMatchFunction& func, 
								CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2, CDPL::Math::Matrix4D& xform) 
	{
		return func(ftr1, ftr2, xform);
	}

	static bool constrFunc3Call(CDPL::Chem::GeometricalFeatureMappingExtractor::FeatureGeometryMatchFunction& func, 
								CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2, CDPL::Math::Matrix4D& xform) 
	{
		return func(ftr1, ftr2, xform);
	}

	static bool constrFunc1NonZero(CDPL::Chem::GeometricalFeatureMappingExtractor::FeatureTypeMatchFunction& func) 
	{
		return !func.empty();
	}

	static bool constrFunc2NonZero(CDPL::Chem::GeometricalFeatureMappingExtractor::FeaturePositionMatchFunction& func) 
	{
		return !func.empty();
	}

	static bool constrFunc3NonZero(CDPL::Chem::GeometricalFeatureMappingExtractor::FeatureGeometryMatchFunction& func) 
	{
		return !func.empty();
	}
}


void CDPLPythonChem::exportGeometricalFeatureMappingExtractor()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<Chem::GeometricalFeatureMappingExtractor, boost::noncopyable>("GeometricalFeatureMappingExtractor", python::no_init)
		.def(python::init<const Chem::GeometricalFeatureMappingExtractor&>((python::arg("self"), python::arg("extor"))))
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode") = false)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::GeometricalFeatureMappingExtractor>())
		.def("assign", &Chem::GeometricalFeatureMappingExtractor::operator=, 
			 (python::arg("self"), python::arg("extor")), python::return_self<>())
		.def("getMapping", &Chem::GeometricalFeatureMappingExtractor::getMapping, 
			 (python::arg("self"), python::arg("mpd_pharm"), python::arg("ref_pharm"), python::arg("xform"), python::arg("mapping")))
		.def("setFeatureTypeMatchFunction", &setConstraintFunc1, 
			 (python::arg("self"), python::arg("func")))
		.def("getFeatureTypeMatchFunction", &Chem::GeometricalFeatureMappingExtractor::getFeatureTypeMatchFunction, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setFeaturePositionMatchFunction", &setConstraintFunc2, 
			 (python::arg("self"), python::arg("func")))
		.def("getFeaturePositionMatchFunction", &Chem::GeometricalFeatureMappingExtractor::getFeaturePositionMatchFunction, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("setFeatureGeometryMatchFunction", &setConstraintFunc3, 
			 (python::arg("self"), python::arg("func")))
		.def("getFeatureGeometryMatchFunction", &Chem::GeometricalFeatureMappingExtractor::getFeatureGeometryMatchFunction, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>());

	python::class_<typename Chem::GeometricalFeatureMappingExtractor::FeatureTypeMatchFunction>("FeatureTypeMatchFunction", python::no_init)
		.def("__call__", &constrFunc1Call, 
			 (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.def("__nonzero__", &constrFunc1NonZero, python::arg("self"));

	python::class_<typename Chem::GeometricalFeatureMappingExtractor::FeaturePositionMatchFunction>("FeaturePositionMatchFunction", python::no_init)
		.def("__call__", &constrFunc2Call, 
			 (python::arg("self"), python::arg("ftr1"), python::arg("ftr2"), python::arg("xform")))
		.def("__nonzero__", &constrFunc2NonZero, python::arg("self"));

	python::class_<typename Chem::GeometricalFeatureMappingExtractor::FeatureGeometryMatchFunction>("FeatureGeometryMatchFunction", python::no_init)
		.def("__call__", &constrFunc3Call, 
			 (python::arg("self"), python::arg("ftr1"), python::arg("ftr2"), python::arg("xform")))
		.def("__nonzero__", &constrFunc3NonZero, python::arg("self"));
}
