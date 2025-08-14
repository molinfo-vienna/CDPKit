/* 
 * FeatureContainerObject3DFactoryExport.cpp 
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


#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Vis/FeatureContainerObject3DFactory.hpp"

#include "Object3DFactoryExport.hpp"
#include "ClassExports.hpp"


void CDPLPythonVis::exportFeatureContainerObject3DFactory()
{
    using namespace boost;
    using namespace CDPL;

    Object3DFactoryExport<Pharm::FeatureContainer>("FeatureContainerObject3DFactoryBase");

    python::class_<Vis::FeatureContainerObject3DFactory, Vis::FeatureContainerObject3DFactory::SharedPointer,
                   python::bases<Vis::Object3DFactory<Pharm::FeatureContainer> >, boost::noncopyable>("FeatureContainerObject3DFactory", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Vis::FeatureContainerObject3DFactory&>((python::arg("self"), python::arg("factory"))));
}
