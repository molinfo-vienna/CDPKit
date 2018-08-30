/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionView2DExport.cpp 
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

#include "CDPL/Vis/ReactionView2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Chem/Reaction.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportReactionView2D()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Vis::ReactionView2D, 
		python::bases<Vis::View2D>, boost::noncopyable>("ReactionView2D", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::Reaction*>((python::arg("self"), python::arg("rxn")))[python::with_custodian_and_ward<1, 2>()])
		.def("setReaction", &Vis::ReactionView2D::setReaction, (python::arg("self"), python::arg("rxn")),
			 python::with_custodian_and_ward<1, 2>())
		.def("getReaction", &Vis::ReactionView2D::getReaction, python::arg("self"), 
			 python::return_internal_reference<1>())
		.def("getFontMetrics", &Vis::ReactionView2D::getFontMetrics, python::arg("self"), 
			 python::return_internal_reference<1>())
		.add_property("reaction", python::make_function(&Vis::ReactionView2D::getReaction,
														python::return_internal_reference<1>()),
					 python::make_function(&Vis::ReactionView2D::setReaction, 
										   python::with_custodian_and_ward<1, 2>()))
		.add_property("fontMetrics", python::make_function(&Vis::ReactionView2D::getFontMetrics,
														   python::return_internal_reference<1>()),
					 python::make_function(&Vis::ReactionView2D::setFontMetrics,	 
										   python::with_custodian_and_ward<1, 2>()));
}
