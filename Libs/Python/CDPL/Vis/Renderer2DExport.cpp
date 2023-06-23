/* 
 * Renderer2DExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct Renderer2DWrapper : CDPL::Vis::Renderer2D, boost::python::wrapper<CDPL::Vis::Renderer2D>
	{

		void saveState() {
			this->get_override("saveState")();
		}

		void restoreState() {
			this->get_override("restoreState")();
		}

		void setTransform(const CDPL::Math::Matrix3D& xform) {
			this->get_override("setTransform")(boost::ref(xform));
		}

		void transform(const CDPL::Math::Matrix3D& xform) {
			this->get_override("transform")(boost::ref(xform));
		}

		void setPen(const CDPL::Vis::Pen& pen) {
			this->get_override("setPen")(boost::ref(pen));
		}

		void setBrush(const CDPL::Vis::Brush& brush) {
			this->get_override("setBrush")(boost::ref(brush));
		}

		void setFont(const CDPL::Vis::Font& font) {
			this->get_override("setFont")(boost::ref(font));
		}

		void drawRectangle(double x, double y, double w, double h) {
			this->get_override("drawRectangle")(x, y, w, h);
		}

		void drawPolygon(const CDPL::Math::Vector2DArray& points) {
			this->get_override("drawPolygon")(boost::ref(points));
		}

		void drawLine(double x1, double y1, double x2, double y2) {
			this->get_override("drawLine")(x1, y1 ,x2, y2);
		}

		void drawPolyline(const CDPL::Math::Vector2DArray& points) {
			this->get_override("drawPolyline")(boost::ref(points));
		}

		void drawLineSegments(const CDPL::Math::Vector2DArray& points) {
			this->get_override("drawLineSegments")(boost::ref(points));
		}

		void drawPoint(double x, double y) {
			this->get_override("drawPoint")(x, y);
		}

		void drawText(double x, double y, const std::string& txt) {
			this->get_override("drawText")(x, y, txt);
		}

		void drawEllipse(double x, double y, double w, double h) {
			this->get_override("drawEllipse")(x, y, w, h);
		}
	};
}


void CDPLPythonVis::exportRenderer2D()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Renderer2DWrapper, boost::noncopyable>("Renderer2D", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Renderer2D>())	
		.def("saveState", python::pure_virtual(&CDPL::Vis::Renderer2D::saveState), python::arg("self"))
		.def("restoreState", python::pure_virtual(&CDPL::Vis::Renderer2D::restoreState), python::arg("self"))
		.def("setTransform", python::pure_virtual(&CDPL::Vis::Renderer2D::setTransform), 
			 (python::arg("self"), python::arg("xform")))
		.def("transform", python::pure_virtual(&CDPL::Vis::Renderer2D::transform), 
			 (python::arg("self"), python::arg("xform")))
		.def("setPen", python::pure_virtual(&CDPL::Vis::Renderer2D::setPen), 
			 (python::arg("self"), python::arg("pen")))
		.def("setBrush", python::pure_virtual(&CDPL::Vis::Renderer2D::setBrush), 
			 (python::arg("self"), python::arg("brush")))
		.def("setFont", python::pure_virtual(&CDPL::Vis::Renderer2D::setFont), 
			 (python::arg("self"), python::arg("font")))
		.def("drawRectangle", python::pure_virtual(&CDPL::Vis::Renderer2D::drawRectangle), 
			 (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("width"), python::arg("height")))
		.def("drawEllipse", python::pure_virtual(&CDPL::Vis::Renderer2D::drawEllipse), 
			 (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("width"), python::arg("height")))
		.def("drawPolygon", python::pure_virtual(&CDPL::Vis::Renderer2D::drawPolygon), 
			 (python::arg("self"), python::arg("points")))
		.def("drawLine", python::pure_virtual(&CDPL::Vis::Renderer2D::drawLine), 
			 (python::arg("self"), python::arg("x1"), python::arg("y1"), python::arg("x2"), python::arg("y2")))
		.def("drawPolyline", python::pure_virtual(&CDPL::Vis::Renderer2D::drawPolyline), 
			 (python::arg("self"), python::arg("points")))
		.def("drawLineSegments", python::pure_virtual(&CDPL::Vis::Renderer2D::drawLineSegments), 
			 (python::arg("self"), python::arg("points")))
		.def("drawPoint", python::pure_virtual(&CDPL::Vis::Renderer2D::drawPoint), 
			 (python::arg("self"), python::arg("x"), python::arg("y")))
		.def("drawText", python::pure_virtual(&CDPL::Vis::Renderer2D::drawText), 
			 (python::arg("self"), python::arg("x"), python::arg("y"), python::arg("txt")));
}
