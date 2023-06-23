/* 
 * View2DExport.cpp 
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

#include "CDPL/Vis/View2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"

#include "ClassExports.hpp"


namespace
{

    struct View2DWrapper : CDPL::Vis::View2D, boost::python::wrapper<CDPL::Vis::View2D>
    {

        void render(CDPL::Vis::Renderer2D& renderer) {
            this->get_override("render")(boost::ref(renderer));
        }

        void setFontMetrics(CDPL::Vis::FontMetrics* font_metrics) {
            this->get_override("setFontMetrics")(boost::python::ptr(font_metrics));
        }

        void getModelBounds(CDPL::Vis::Rectangle2D& bounds) {
            this->get_override("getModelBounds")(boost::ref(bounds));
        }
    };
}


void CDPLPythonVis::exportView2D()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<View2DWrapper, python::bases<Base::ControlParameterContainer>, boost::noncopyable>("View2D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def("render", python::pure_virtual(&Vis::View2D::render), (python::arg("self"), python::arg("renderer")))
        .def("setFontMetrics", python::pure_virtual(&Vis::View2D::setFontMetrics), 
             (python::arg("self"), python::arg("font_metrics")),
             python::with_custodian_and_ward<1, 2>())
        .def("getModelBounds", python::pure_virtual(&Vis::View2D::getModelBounds), 
             (python::arg("self"), python::arg("bounds")));
}
