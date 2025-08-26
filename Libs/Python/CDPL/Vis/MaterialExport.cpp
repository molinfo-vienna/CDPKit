/* 
 * MaterialExport.cpp 
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

#include "CDPL/Vis/Material.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonVis::exportMaterial()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Vis::Material>("Material", python::no_init)
        .def(python::init<const Vis::Material&>((python::arg("self"), python::arg("material"))))
        .def(python::init<const Vis::Color&, const Vis::Color&, const Vis::Color&, double, double>(
                 (python::arg("self"), python::arg("amb_color"), python::arg("diff_color"), python::arg("spec_color"),
                  python::arg("shininess"), python::arg("transp") = 1.0)))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::Material>())
        .def("assign", CDPLPythonBase::copyAssOp<Vis::Material>(),
             (python::arg("self"), python::arg("material")), python::return_self<>())
        .def("getAmbientColor", &Vis::Material::getAmbientColor, python::arg("self"), python::return_internal_reference<1>())
        .def("setAmbientColor", &Vis::Material::setAmbientColor, (python::arg("self"), python::arg("color")))
        .def("getDiffuseColor", &Vis::Material::getDiffuseColor, python::arg("self"), python::return_internal_reference<1>())
        .def("setDiffuseColor", &Vis::Material::setDiffuseColor, (python::arg("self"), python::arg("color")))
        .def("getSpecularColor", &Vis::Material::getSpecularColor, python::arg("self"), python::return_internal_reference<1>())
        .def("setSpecularColor", &Vis::Material::setSpecularColor, (python::arg("self"), python::arg("color")))
        .def("getTransparency", &Vis::Material::getTransparency, python::arg("self"))
        .def("setTransparency", &Vis::Material::setTransparency, (python::arg("self"), python::arg("transp")))
        .def("getShininess", &Vis::Material::getShininess, python::arg("self"))
        .def("setShininess", &Vis::Material::setShininess, (python::arg("self"), python::arg("shininess")))
        .def("__eq__", &Vis::Material::operator==, (python::arg("self"), python::arg("material")))
        .def("__ne__", &Vis::Material::operator!=, (python::arg("self"), python::arg("material")))
        .add_property("ambient", python::make_function(&Vis::Material::getAmbientColor, python::return_internal_reference<1>()),
                      &Vis::Material::setAmbientColor)
        .add_property("diffuse", python::make_function(&Vis::Material::getDiffuseColor, python::return_internal_reference<1>()),
                      &Vis::Material::setDiffuseColor)
        .add_property("specular", python::make_function(&Vis::Material::getSpecularColor, python::return_internal_reference<1>()),
                      &Vis::Material::setSpecularColor)
        .add_property("shininess", &Vis::Material::getShininess, &Vis::Material::setShininess)
        .add_property("transparency", &Vis::Material::getTransparency, &Vis::Material::setTransparency);
}
