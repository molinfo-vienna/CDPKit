/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GraphicsPrimitive2DExport.cpp 
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

#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct GraphicsPrimitive2DWrapper : CDPL::Vis::GraphicsPrimitive2D, boost::python::wrapper<CDPL::Vis::GraphicsPrimitive2D>
	{

		void render(CDPL::Vis::Renderer2D& renderer) const {
			this->get_override("render")(boost::ref(renderer));
		}

		CDPL::Vis::GraphicsPrimitive2D::SharedPointer clone() const {
			return this->get_override("clone")();
		}

		void getBounds(CDPL::Vis::Rectangle2D& bbox, CDPL::Vis::FontMetrics* fm) const {
			this->get_override("getBounds")(boost::ref(bbox), fm);
		}
	};
}


void CDPLPythonVis::exportGraphicsPrimitive2D()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<GraphicsPrimitive2DWrapper, boost::noncopyable>("GraphicsPrimitive2D", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::GraphicsPrimitive2D>())	
		.def("render", python::pure_virtual(&Vis::GraphicsPrimitive2D::render), 
			 (python::arg("self"), python::arg("renderer")))
		.def("getBounds", python::pure_virtual(&Vis::GraphicsPrimitive2D::getBounds), 
			 (python::arg("self"), python::arg("bounds"), python::arg("font_metrics") = 0))
		.def("clone", python::pure_virtual(&Vis::GraphicsPrimitive2D::clone), python::arg("self"));
}
