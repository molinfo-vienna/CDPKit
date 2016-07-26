/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalEntityAlignmentExport.cpp 
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

#include "CDPL/Chem/GeometricalEntityAlignment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename T>
    struct GeometricalEntityAlignmentExport
    {

		GeometricalEntityAlignmentExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::scope scope = python::class_<Chem::GeometricalEntityAlignment<T>, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const Chem::GeometricalEntityAlignment<T>&>(
						 (python::arg("self"), python::arg("alignment"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::GeometricalEntityAlignment<T> >())	
				.def("setEntityMatchFunction", &setConstraintFunc1, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityMatchFunction", &Chem::GeometricalEntityAlignment<T>::getEntityMatchFunction, 
					 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.def("setEntityPairMatchFunction", &setConstraintFunc2, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityPairMatchFunction", &Chem::GeometricalEntityAlignment<T>::getEntityPairMatchFunction, 
					 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.def("setTopAlignmentConstraintFunction", &setConstraintFunc3, 
					 (python::arg("self"), python::arg("func")))
				.def("getTopAlignmentConstraintFunction", &Chem::GeometricalEntityAlignment<T>::getTopAlignmentConstraintFunction, 
					 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.def("setEntity3DCoordinatesFunction", &setCoordinatesFunc, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntity3DCoordinatesFunction", &Chem::GeometricalEntityAlignment<T>::getEntity3DCoordinatesFunction, 
					 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.def("addEntity", &addEntityFunc, (python::arg("self"), python::arg("entity"), python::arg("first_set")))
				.def("clearEntities", &Chem::GeometricalEntityAlignment<T>::clearEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getNumEntities", &Chem::GeometricalEntityAlignment<T>::getNumEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getEntities", &getEntitiesFunc, (python::arg("self"), python::arg("first_set")))
				.def("setMinTopologicalMappingSize", &Chem::GeometricalEntityAlignment<T>::setMinTopologicalMappingSize,
					 (python::arg("self"), python::arg("min_size")))
				.def("getMinTopologicalMappingSize", &Chem::GeometricalEntityAlignment<T>::getMinTopologicalMappingSize,
					 python::arg("self"))
				.def("init", &Chem::GeometricalEntityAlignment<T>::init, python::arg("self"))
				.def("nextAlignment", &Chem::GeometricalEntityAlignment<T>::nextAlignment, 
					 python::arg("self"))
				.def("getTransform", &Chem::GeometricalEntityAlignment<T>::getTransform,
					 python::arg("self"), python::return_internal_reference<>())
				.def("assign", &Chem::GeometricalEntityAlignment<T>::operator=, 
					 (python::arg("self"), python::arg("alignment")), python::return_self<>())
				.add_property("minTopologicalMappingSize", &Chem::GeometricalEntityAlignment<T>::getMinTopologicalMappingSize,
					  &Chem::GeometricalEntityAlignment<T>::setMinTopologicalMappingSize);

			python::class_<typename Chem::GeometricalEntityAlignment<T>::EntityMatchFunction>("EntityMatchFunction", python::no_init)
				.def("__call__", &constrFunc1Call, 
					 (python::arg("self"), python::arg("ent1"), python::arg("ent2")))
				.def("__nonzero__", &constrFunc1NonZero, python::arg("self"));

			python::class_<typename Chem::GeometricalEntityAlignment<T>::EntityPairMatchFunction>("EntityPairMatchFunction", python::no_init)
				.def("__call__", &constrFunc2Call, 
					 (python::arg("self"), python::arg("p1_ent1"), python::arg("p1_ent2"), python::arg("p2_ent1"), python::arg("p2_ent2")))
				.def("__nonzero__", &constrFunc2NonZero, python::arg("self"));

			python::class_<typename Chem::GeometricalEntityAlignment<T>::TopologicalAlignmentConstraintFunction>("TopologicalAlignmentConstraintFunction", python::no_init)
				.def("__call__", &constrFunc3Call, 
					 (python::arg("self"), python::arg("mapping")))
				.def("__nonzero__", &constrFunc3NonZero, python::arg("self"));

			python::class_<typename Chem::GeometricalEntityAlignment<T>::Entity3DCoordinatesFunction>("Entity3DCoordinatesFunction", python::no_init)
				.def("__call__", &coordsFuncCall, 
					 (python::arg("self"), python::arg("entity")), python::return_internal_reference<>())
				.def("__nonzero__", &coordsFuncNonZero, python::arg("self"));
		}

		static boost::python::object getEntitiesFunc(CDPL::Chem::GeometricalEntityAlignment<T>& alignment, bool first_set) {
			using namespace boost;
			
			python::list entities;

			for (typename CDPL::Chem::GeometricalEntityAlignment<T>::ConstEntityIterator it = alignment.getEntitiesBegin(first_set),
					 end = alignment.getEntitiesEnd(first_set); it != end; ++it)
				entities.append(boost::ref(*it));

			return entities;
		}

		static void addEntityFunc(CDPL::Chem::GeometricalEntityAlignment<T>& alignment, T& ent, bool first_set) {
			alignment.addEntity(ent, first_set);
		}

		static void setConstraintFunc1(CDPL::Chem::GeometricalEntityAlignment<T>& alignment, 
									   const boost::python::object& callable) {

			if (callable.ptr() == Py_None)
				alignment.setEntityMatchFunction(typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityMatchFunction());
			else
				alignment.setEntityMatchFunction(CDPLPythonBase::BinaryFunctionAdapter<bool, T, T>(callable)); 
		}
	
		static void setConstraintFunc2(CDPL::Chem::GeometricalEntityAlignment<T>& alignment, 
									   const boost::python::object& callable) {

			if (callable.ptr() == Py_None)
				alignment.setEntityPairMatchFunction(typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityPairMatchFunction());
			else
				alignment.setEntityPairMatchFunction(CDPLPythonBase::QuarternaryFunctionAdapter<bool, T, T, T, T>(callable)); 
		}

		static void setConstraintFunc3(CDPL::Chem::GeometricalEntityAlignment<T>& alignment, 
									   const boost::python::object& callable) {

			if (callable.ptr() == Py_None)
				alignment.setTopAlignmentConstraintFunction(typename CDPL::Chem::GeometricalEntityAlignment<T>::TopologicalAlignmentConstraintFunction());
			else
				alignment.setTopAlignmentConstraintFunction(CDPLPythonBase::UnaryFunctionAdapter<bool, 
															typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityMapping>(callable)); 
		}

		static void setCoordinatesFunc(CDPL::Chem::GeometricalEntityAlignment<T>& alignment, 
									   const boost::python::object& callable) {

			alignment.setEntity3DCoordinatesFunction(CDPLPythonBase::UnaryFunctionAdapter<const CDPL::Math::Vector3D&, T>(callable)); 
		}

		static bool constrFunc1Call(typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityMatchFunction& func, 
								   T& ent1, T& ent2) {
			return func(ent1, ent2);
		}

		static bool constrFunc2Call(typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityPairMatchFunction& func, 
									T& p1_ent1, T& p1_ent2, T& p2_ent1, T& p2_ent2) {
			return func(p1_ent1, p1_ent2, p1_ent1, p1_ent2);
		}

		static bool constrFunc3Call(typename CDPL::Chem::GeometricalEntityAlignment<T>::TopologicalAlignmentConstraintFunction& func, 
									const typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityMapping& mapping) {
			return func(mapping);
		}

		static const CDPL::Math::Vector3D& coordsFuncCall(typename CDPL::Chem::GeometricalEntityAlignment<T>::Entity3DCoordinatesFunction& func, 
														  T& ent) {
			return func(ent);
		}

		static bool constrFunc1NonZero(typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityMatchFunction& func) {
			return !func.empty();
		}

		static bool constrFunc2NonZero(typename CDPL::Chem::GeometricalEntityAlignment<T>::EntityPairMatchFunction& func) {
			return !func.empty();
		}

		static bool constrFunc3NonZero(typename CDPL::Chem::GeometricalEntityAlignment<T>::TopologicalAlignmentConstraintFunction& func) {
			return !func.empty();
		}

		static bool coordsFuncNonZero(typename CDPL::Chem::GeometricalEntityAlignment<T>::Entity3DCoordinatesFunction& func) {
			return !func.empty();
		}
    };
}


void CDPLPythonChem::exportGeometricalEntityAlignments()
{
    using namespace CDPL;
    using namespace Chem;

    GeometricalEntityAlignmentExport<GeometricalEntityAlignment<Entity3D> >("GeometricalEntity3DAlignment");
    GeometricalEntityAlignmentExport<GeometricalEntityAlignment<Atom> >("GeometricalAtomAlignment");
    GeometricalEntityAlignmentExport<GeometricalEntityAlignment<Feature> >("GeometricalFeatureAlignment");
}
