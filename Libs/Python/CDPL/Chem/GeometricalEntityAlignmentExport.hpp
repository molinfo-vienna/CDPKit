/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalEntityAlignmentExport.hpp 
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


#ifndef CDPL_PYTHON_CHEM_GEOMETRICALENTITYALIGNMENTEXPORT_HPP
#define CDPL_PYTHON_CHEM_GEOMETRICALENTITYALIGNMENTEXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Chem/GeometricalEntityAlignment.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"


namespace CDPLPythonChem
{

    template <typename T>
    struct GeometricalEntityAlignmentExport
    {

		typedef CDPL::Chem::GeometricalEntityAlignment<T> AlignmentType;

		GeometricalEntityAlignmentExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::class_<AlignmentType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const AlignmentType&>(
						 (python::arg("self"), python::arg("alignment"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<AlignmentType >())	
				.def("setEntityMatchFunction", &setConstraintFunc1, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityMatchFunction", &AlignmentType::getEntityMatchFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("setEntityPairMatchFunction", &setConstraintFunc2, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityPairMatchFunction", &AlignmentType::getEntityPairMatchFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("setTopAlignmentConstraintFunction", &setConstraintFunc3, 
					 (python::arg("self"), python::arg("func")))
				.def("getTopAlignmentConstraintFunction", &AlignmentType::getTopAlignmentConstraintFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("setEntity3DCoordinatesFunction", &setCoordinatesFunc, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntity3DCoordinatesFunction", &AlignmentType::getEntity3DCoordinatesFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("addEntity", &addEntityFunc, (python::arg("self"), python::arg("entity"), python::arg("first_set")))
				.def("clearEntities", &AlignmentType::clearEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getNumEntities", &AlignmentType::getNumEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getEntities", &getEntitiesFunc, (python::arg("self"), python::arg("first_set")))
				.def("setMinTopologicalMappingSize", &AlignmentType::setMinTopologicalMappingSize,
					 (python::arg("self"), python::arg("min_size")))
				.def("getMinTopologicalMappingSize", &AlignmentType::getMinTopologicalMappingSize,
					 python::arg("self"))
				.def("init", &AlignmentType::init, python::arg("self"))
				.def("nextAlignment", &AlignmentType::nextAlignment, 
					 python::arg("self"))
				.def("getTransform", &AlignmentType::getTransform,
					 python::arg("self"), python::return_internal_reference<>())
				.def("assign", &AlignmentType::operator=, 
					 (python::arg("self"), python::arg("alignment")), python::return_self<>())
				.add_property("minTopologicalMappingSize", &AlignmentType::getMinTopologicalMappingSize,
					  &AlignmentType::setMinTopologicalMappingSize);
		}

		static boost::python::object getEntitiesFunc(AlignmentType& alignment, bool first_set) {
			using namespace boost;
			
			python::list entities;

			for (typename AlignmentType::ConstEntityIterator it = alignment.getEntitiesBegin(first_set),
					 end = alignment.getEntitiesEnd(first_set); it != end; ++it)
				entities.append(boost::ref(*it));

			return entities;
		}

		static void addEntityFunc(AlignmentType& alignment, T& ent, bool first_set) {
			alignment.addEntity(ent, first_set);
		}

		static void setConstraintFunc1(AlignmentType& alignment, const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				alignment.setEntityMatchFunction(typename AlignmentType::EntityMatchFunction());
			else
				alignment.setEntityMatchFunction(CDPLPythonBase::BinaryFunctionAdapter<bool, T, T>(callable)); 
		}
	
		static void setConstraintFunc2(AlignmentType& alignment, const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				alignment.setEntityPairMatchFunction(typename AlignmentType::EntityPairMatchFunction());
			else
				alignment.setEntityPairMatchFunction(CDPLPythonBase::QuarternaryFunctionAdapter<bool, T, T, T, T>(callable)); 
		}

		static void setConstraintFunc3(AlignmentType& alignment, const boost::python::object& callable) {
			if (callable.ptr() == Py_None)
				alignment.setTopAlignmentConstraintFunction(typename AlignmentType::TopologicalAlignmentConstraintFunction());
			else
				alignment.setTopAlignmentConstraintFunction(CDPLPythonBase::UnaryFunctionAdapter<bool, 
															typename AlignmentType::EntityMapping>(callable)); 
		}

		static void setCoordinatesFunc(AlignmentType& alignment, const boost::python::object& callable) {
			alignment.setEntity3DCoordinatesFunction(CDPLPythonBase::UnaryFunctionAdapter<const CDPL::Math::Vector3D&, T>(callable)); 
		}
    };
}

#endif // CDPL_PYTHON_CHEM_GEOMETRICALENTITYALIGNMENTEXPORT_HPP
