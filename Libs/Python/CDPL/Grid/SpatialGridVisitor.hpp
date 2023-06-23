/* 
 * SpatialGridVisitor.hpp 
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


#ifndef CDPL_PYTHON_GRID_SPATIALGRIDVISITOR_HPP
#define CDPL_PYTHON_GRID_SPATIALGRIDVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define SPATIALGRID_IMPL()												\
    const ValueType& operator()(std::size_t idx) const {				\
	    return this->get_override("__call__")(idx);						\
    }																	\
																		\
    ValueType& operator()(std::size_t idx) {							\
	    return this->get_override("__call__")(idx);						\
    }																	\
																		\
    void getCoordinates(std::size_t i, CoordinatesType& coords) const { \
	    this->get_override("getCoordinates")(i, boost::ref(coords));	\
    }


namespace CDPLPythonGrid
{

	class SpatialGridVisitorBase
	{

	protected:
		template <typename GridType>
		static void setItem(GridType& grid, std::size_t i, const typename GridType::ValueType& v) {
			grid(i) = v;
		}
	};

	template <typename GridType>
    class SpatialGridVirtualFunctionsVisitor : private SpatialGridVisitorBase, public boost::python::def_visitor<SpatialGridVirtualFunctionsVisitor<GridType> >
    {

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;
			
			typedef typename GridType::ValueType ValueType;

			cl	
				.def("__call__", python::pure_virtual(static_cast<const ValueType& (GridType::*)(std::size_t) const>(&GridType::operator())), 
					 (python::arg("self"), python::arg("i")), python::return_value_policy<python::copy_const_reference>())
				.def("getElement", python::pure_virtual(static_cast<const ValueType& (GridType::*)(std::size_t) const>(&GridType::operator())), 
					 (python::arg("self"), python::arg("i")), python::return_value_policy<python::copy_const_reference>())
				.def("setElement", &setItem<GridType>, (python::arg("self"), python::arg("i"), python::arg("value")))
				.def("getCoordinates", python::pure_virtual(&GridType::getCoordinates), (python::arg("self"), python::arg("i"), python::arg("coords")));
		}
    };

	template <typename GridType>
    class SpatialGridSpecialFunctionsVisitor : private SpatialGridVisitorBase, public boost::python::def_visitor<SpatialGridSpecialFunctionsVisitor<GridType> >
    {

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			typedef typename GridType::ValueType ValueType;

			cl
				.def("__getitem__", static_cast<const ValueType& (GridType::*)(std::size_t) const>(&GridType::operator()),
					 (python::arg("self"), python::arg("i")),
					 python::return_value_policy<python::copy_const_reference>())
				.def("__setitem__", &setItem<GridType>, (python::arg("self"), python::arg("i"), python::arg("value")));
		}
    };
}

#endif // CDPL_PYTHON_GRID_SPATIALGRIDVISITOR_HPP
