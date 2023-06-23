/* 
 * SpatialEntityAlignmentExport.hpp 
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


#ifndef CDPL_PYTHON_CHEM_SPATIALENTITYALIGNMENTEXPORT_HPP
#define CDPL_PYTHON_CHEM_SPATIALENTITYALIGNMENTEXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Chem/SpatialEntityAlignment.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"


namespace CDPLPythonChem
{

    template <typename T>
    struct SpatialEntityAlignmentExport
    {
		
		typedef CDPL::Chem::SpatialEntityAlignment<T> AlignmentType;

		SpatialEntityAlignmentExport(const char* name) {
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
				.def("setTopAlignmentConstraintFunction", &AlignmentType::setTopAlignmentConstraintFunction, 
					 (python::arg("self"), python::arg("func")))
				.def("getTopAlignmentConstraintFunction", &AlignmentType::getTopAlignmentConstraintFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("setEntity3DCoordinatesFunction", &AlignmentType::setEntity3DCoordinatesFunction, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntity3DCoordinatesFunction", &AlignmentType::getEntity3DCoordinatesFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("setEntityWeightFunction", &AlignmentType::setEntityWeightFunction, 
					 (python::arg("self"), python::arg("func")))
				.def("getEntityWeightFunction", &AlignmentType::getEntityWeightFunction, 
					 python::arg("self"), python::return_internal_reference<>())
				.def("performExhaustiveSearch", &AlignmentType::performExhaustiveSearch,
					 (python::arg("self"), python::arg("exhaustive")))
				.def("exhaustiveSearchPerformed", &AlignmentType::exhaustiveSearchPerformed,
					 python::arg("self"))
				.def("addEntity", &addEntityFunc, (python::arg("self"), python::arg("entity"), python::arg("first_set")),
					 python::with_custodian_and_ward<1, 2>())
				.def("clearEntities", &AlignmentType::clearEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getNumEntities", &AlignmentType::getNumEntities, 
					 (python::arg("self"), python::arg("first_set")))
				.def("getEntities", &getEntitiesFunc, (python::arg("self"), python::arg("first_set")))
				.def("getEntity", &AlignmentType::getEntity, (python::arg("self"), python::arg("idx"), python::arg("first_set")),
					 python::return_internal_reference<>())
				.def("setMinTopologicalMappingSize", &AlignmentType::setMinTopologicalMappingSize,
					 (python::arg("self"), python::arg("min_size")))
				.def("getMinTopologicalMappingSize", &AlignmentType::getMinTopologicalMappingSize,
					 python::arg("self"))
				.def("reset", &AlignmentType::reset, python::arg("reset"))
				.def("nextAlignment", &AlignmentType::nextAlignment, 
					 python::arg("self"))
				.def("getTransform", &AlignmentType::getTransform,
					 python::arg("self"), python::return_internal_reference<>())
				.def("assign", &AlignmentType::operator=, 
					 (python::arg("self"), python::arg("alignment")), python::return_self<python::with_custodian_and_ward<1, 2> >())
				.def("getTopologicalMapping", &AlignmentType::getTopologicalMapping,
					 python::arg("self"), python::return_internal_reference<>())
				.add_property("topMapping", 
							  python::make_function(&AlignmentType::getTopologicalMapping, python::return_internal_reference<>()))
				.add_property("minTopologicalMappingSize", &AlignmentType::getMinTopologicalMappingSize,
							  &AlignmentType::setMinTopologicalMappingSize)
				.add_property("exhaustiveSearch", &AlignmentType::exhaustiveSearchPerformed,
							  &AlignmentType::performExhaustiveSearch)
				.add_property("transform", 
							  python::make_function(&AlignmentType::getTransform, python::return_internal_reference<>()))
				.add_property("entityMatchFunction", 
							  python::make_function(&AlignmentType::getEntityMatchFunction, python::return_internal_reference<>()),
							  &AlignmentType::setEntityMatchFunction)
				.add_property("entityPairMatchFunction", 
							  python::make_function(&AlignmentType::getEntityPairMatchFunction, python::return_internal_reference<>()),
							  &AlignmentType::setEntityPairMatchFunction)
				.add_property("topAlignmentConstraintFunction", 
							  python::make_function(&AlignmentType::getTopAlignmentConstraintFunction, python::return_internal_reference<>()),
							  &AlignmentType::setTopAlignmentConstraintFunction)
				.add_property("entity3DCoordinatesFunction", 
							  python::make_function(&AlignmentType::setEntity3DCoordinatesFunction, python::return_internal_reference<>()),
							  &AlignmentType::setEntity3DCoordinatesFunction)
				.add_property("entityWeightFunction", 
							  python::make_function(&AlignmentType::setEntityWeightFunction, python::return_internal_reference<>()),
							  &AlignmentType::setEntityWeightFunction);
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

#endif // CDPL_PYTHON_CHEM_SPATIALENTITYALIGNMENTEXPORT_HPP
