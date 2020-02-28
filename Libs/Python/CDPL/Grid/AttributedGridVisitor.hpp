/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AttributedGridVisitor.hpp 
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


#ifndef CDPL_PYTHON_GRID_ATTRIBUTEDGRIDVISITOR_HPP
#define CDPL_PYTHON_GRID_ATTRIBUTEDGRIDVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define ATTRIBUTEDGRID_IMPL()											\
    std::size_t getNumElements() const {                                \
		return this->get_override("getNumElements")();                  \
    }																	\
																		\
    bool isEmpty() const {												\
	    return this->get_override("isEmpty")();							\
    }


namespace CDPLPythonGrid
{

    class AttributedGridVirtualFunctionsVisitor : public boost::python::def_visitor<AttributedGridVirtualFunctionsVisitor>
    {

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl	
				.def("isEmpty", python::pure_virtual(&Grid::AttributedGrid::isEmpty), python::arg("self"))
				.def("getNumElements", python::pure_virtual(&Grid::AttributedGrid::getNumElements), python::arg("self"));
		}
    };

    class AttributedGridSpecialFunctionsVisitor : public boost::python::def_visitor<AttributedGridSpecialFunctionsVisitor>
    {

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl
				.def("__len__", &Grid::AttributedGrid::getNumElements, python::arg("self"));
		}
    };
}

#endif // CDPL_PYTHON_GRID_ATTRIBUTEDGRIDVISITOR_HPP
