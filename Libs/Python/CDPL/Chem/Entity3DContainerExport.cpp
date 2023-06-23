/* 
 * Entity3DContainerExport.cpp 
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

#include "CDPL/Chem/Entity3DContainer.hpp"
#include "CDPL/Chem/Entity3D.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "Entity3DContainerVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

    struct Entity3DContainerWrapper : CDPL::Chem::Entity3DContainer, boost::python::wrapper<CDPL::Chem::Entity3DContainer> 
    {

        ENTITY3DCONTAINER_IMPL()
    };
}


void CDPLPythonChem::exportEntity3DContainer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Entity3DContainerWrapper, boost::noncopyable>("Entity3DContainer", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(Entity3DContainerVirtualFunctionsVisitor())
        .def(Entity3DContainerSpecialFunctionsVisitor())
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::Entity3DContainer>())
        .add_property("numEntities", &Chem::Entity3DContainer::getNumEntities);
}
