/* 
 * TopologicalEntityAlignmentExport.hpp 
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


#ifndef CDPL_PYTHON_CHEM_TOPOLOGICALENTITYALIGNMENTEXPORT_HPP
#define CDPL_PYTHON_CHEM_TOPOLOGICALENTITYALIGNMENTEXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Chem/TopologicalEntityAlignment.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"


namespace CDPLPythonChem
{

	template <typename T>
    struct TopologicalEntityAlignmentExport
    {

		typedef CDPL::Chem::TopologicalEntityAlignment<T> AlignmentType;

		TopologicalEntityAlignmentExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::class_<AlignmentType, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const AlignmentType&>(
						 (python::arg("self"), python::arg("alignment")))[python::with_custodian_and_ward<1, 2>()])
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<AlignmentType >())	
				.def("setEntityMatchFunction", &AlignmentType::setEntityMatchFunction, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityMatchFunction", &AlignmentType::getEntityMatchFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("setEntityPairMatchFunction", &AlignmentType::setEntityPairMatchFunction, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityPairMatchFunction", &AlignmentType::getEntityPairMatchFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("addEntity", &addEntityFunc, (python::arg("self"), python::arg("entity"), python::arg("first_set")),
					 python::with_custodian_and_ward<1, 2>())
				.def("clearEntities", &AlignmentType::clearEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getNumEntities", &AlignmentType::getNumEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getEntities", &getEntitiesFunc, (python::arg("self"), python::arg("first_set")))
				.def("getEntity", &AlignmentType::getEntity, (python::arg("self"), python::arg("idx"), python::arg("first_set")),
					 python::return_internal_reference<>())
				.def("reset", &AlignmentType::reset, python::arg("self"))
				.def("nextAlignment", &AlignmentType::nextAlignment, 
					 (python::arg("self"), python::arg("mapping")))
				.def("assign", &AlignmentType::operator=, 
					 (python::arg("self"), python::arg("alignment")), python::return_self<python::with_custodian_and_ward<1, 2> >())
				.add_property("entityMatchFunction", 
							  python::make_function(&AlignmentType::getEntityMatchFunction, python::return_internal_reference<>()),
							  &AlignmentType::setEntityMatchFunction)
				.add_property("entityPairMatchFunction", 
							  python::make_function(&AlignmentType::getEntityPairMatchFunction, python::return_internal_reference<>()),
							  &AlignmentType::setEntityPairMatchFunction);

		}

		static boost::python::object getEntitiesFunc(AlignmentType& alignment, bool first_set) {
			using namespace boost;
			
			python::list entities;

			for (typename AlignmentType::ConstEntityIterator it = alignment.getEntitiesBegin(first_set),
					 end = alignment.getEntitiesEnd(first_set); it != end; ++it)
				entities.append(boost::ref(*it));

			return std::move(entities);
		}

		static void addEntityFunc(AlignmentType& alignment, T& ent, bool first_set) {
			alignment.addEntity(ent, first_set);
		}
    };
}

#endif // CDPL_PYTHON_CHEM_TOPOLOGICALENTITYALIGNMENTEXPORT_HPP
