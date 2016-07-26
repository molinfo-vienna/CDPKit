/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TopologicalEntityAlignmentExport.cpp 
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

#include "CDPL/Chem/TopologicalEntityAlignment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename T>
    struct TopologicalEntityAlignmentExport
    {

		TopologicalEntityAlignmentExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::scope scope = python::class_<Chem::TopologicalEntityAlignment<T>, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const Chem::TopologicalEntityAlignment<T>&>(
						 (python::arg("self"), python::arg("alignment"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::TopologicalEntityAlignment<T> >())	
				.def("setEntityMatchFunction", &setConstraintFunc1, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityMatchFunction", &Chem::TopologicalEntityAlignment<T>::getEntityMatchFunction, 
					 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.def("setEntityPairMatchFunction", &setConstraintFunc2, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityPairMatchFunction", &Chem::TopologicalEntityAlignment<T>::getEntityPairMatchFunction, 
					 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.def("addEntity", &addEntityFunc, (python::arg("self"), python::arg("entity"), python::arg("first_set")))
				.def("clearEntities", &Chem::TopologicalEntityAlignment<T>::clearEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getNumEntities", &Chem::TopologicalEntityAlignment<T>::getNumEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getEntities", &getEntitiesFunc, (python::arg("self"), python::arg("first_set")))
				.def("init", &Chem::TopologicalEntityAlignment<T>::init, python::arg("self"))
				.def("nextAlignment", &Chem::TopologicalEntityAlignment<T>::nextAlignment, 
					 (python::arg("self"), python::arg("mapping")))
				.def("assign", &Chem::TopologicalEntityAlignment<T>::operator=, 
					 (python::arg("self"), python::arg("alignment")), python::return_self<>());

			python::class_<typename Chem::TopologicalEntityAlignment<T>::EntityMatchFunction>("EntityMatchFunction", python::no_init)
				.def("__call__", &constrFunc1Call, 
					 (python::arg("self"), python::arg("ent1"), python::arg("ent2")))
				.def("__nonzero__", &constrFunc1NonZero, python::arg("self"));

			python::class_<typename Chem::TopologicalEntityAlignment<T>::EntityPairMatchFunction>("EntityPairMatchFunction", python::no_init)
				.def("__call__", &constrFunc2Call, 
					 (python::arg("self"), python::arg("p1_ent1"), python::arg("p1_ent2"), python::arg("p2_ent1"), python::arg("p2_ent2")))
				.def("__nonzero__", &constrFunc2NonZero, python::arg("self"));
		}

		static boost::python::object getEntitiesFunc(CDPL::Chem::TopologicalEntityAlignment<T>& alignment, bool first_set) {
			using namespace boost;
			
			python::list entities;

			for (typename CDPL::Chem::TopologicalEntityAlignment<T>::ConstEntityIterator it = alignment.getEntitiesBegin(first_set),
					 end = alignment.getEntitiesEnd(first_set); it != end; ++it)
				entities.append(boost::ref(*it));

			return entities;
		}

		static void addEntityFunc(CDPL::Chem::TopologicalEntityAlignment<T>& alignment, T& ent, bool first_set) {
			alignment.addEntity(ent, first_set);
		}

		static void setConstraintFunc1(CDPL::Chem::TopologicalEntityAlignment<T>& alignment, 
									   const boost::python::object& callable) {

			if (callable.ptr() == Py_None)
				alignment.setEntityMatchFunction(typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityMatchFunction());
			else
				alignment.setEntityMatchFunction(CDPLPythonBase::BinaryFunctionAdapter<bool, T, T>(callable)); 
		}
	
		static void setConstraintFunc2(CDPL::Chem::TopologicalEntityAlignment<T>& alignment, 
									   const boost::python::object& callable) {

			if (callable.ptr() == Py_None)
				alignment.setEntityPairMatchFunction(typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityPairMatchFunction());
			else
				alignment.setEntityPairMatchFunction(CDPLPythonBase::QuarternaryFunctionAdapter<bool, T, T, T, T>(callable)); 
		}

		static bool constrFunc1Call(typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityMatchFunction& func, 
								   T& ent1, T& ent2) {
			return func(ent1, ent2);
		}

		static bool constrFunc2Call(typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityPairMatchFunction& func, 
									T& p1_ent1, T& p1_ent2, T& p2_ent1, T& p2_ent2) {
			return func(p1_ent1, p1_ent2, p1_ent1, p1_ent2);
		}

		static bool constrFunc1NonZero(typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityMatchFunction& func) {
			return !func.empty();
		}

		static bool constrFunc2NonZero(typename CDPL::Chem::TopologicalEntityAlignment<T>::EntityPairMatchFunction& func) {
			return !func.empty();
		}
    };
}


void CDPLPythonChem::exportTopologicalEntityAlignments()
{
    using namespace CDPL;
    using namespace Chem;

    TopologicalEntityAlignmentExport<TopologicalEntityAlignment<Entity3D> >("TopologicalEntity3DAlignment");
    TopologicalEntityAlignmentExport<TopologicalEntityAlignment<Atom> >("TopologicalAtomAlignment");
    TopologicalEntityAlignmentExport<TopologicalEntityAlignment<Feature> >("TopologicalFeatureAlignment");
}
