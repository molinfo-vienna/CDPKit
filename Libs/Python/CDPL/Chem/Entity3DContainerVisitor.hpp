/* 
 * Entity3DContainerVisitor.hpp 
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


#ifndef CDPL_PYTHON_BASE_ENTITY3DCONTAINERVISITOR_HPP
#define CDPL_PYTHON_BASE_ENTITY3DCONTAINERVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define ENTITY3DCONTAINER_IMPL()                                                                       \
    std::size_t getNumEntities() const                                                                 \
    {                                                                                                  \
        return this->get_override("getNumEntities")();                                                 \
    }                                                                                                  \
                                                                                                       \
    const CDPL::Chem::Entity3D& getEntity(std::size_t idx) const                                       \
    {                                                                                                  \
        return boost::python::call<CDPL::Chem::Entity3D&>(this->get_override("getEntity").ptr(), idx); \
    }                                                                                                  \
                                                                                                       \
    CDPL::Chem::Entity3D& getEntity(std::size_t idx)                                                   \
    {                                                                                                  \
        return boost::python::call<CDPL::Chem::Entity3D&>(this->get_override("getEntity").ptr(), idx); \
    }


namespace CDPLPythonChem
{

    class Entity3DContainerVirtualFunctionsVisitor : public boost::python::def_visitor<Entity3DContainerVirtualFunctionsVisitor>
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;
            using namespace CDPL;

            cl
                .def("getEntity", python::pure_virtual(static_cast<Chem::Entity3D& (Chem::Entity3DContainer::*)(std::size_t)>(&Chem::Entity3DContainer::getEntity)),
                     (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
                .def("getNumEntities", python::pure_virtual(&Chem::Entity3DContainer::getNumEntities), python::arg("self"));
        }
    };

    class Entity3DContainerSpecialFunctionsVisitor : public boost::python::def_visitor<Entity3DContainerSpecialFunctionsVisitor>
    {

        friend class boost::python::def_visitor_access;

      private:
        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;
            using namespace CDPL;

            cl
                .def("__getitem__", static_cast<Chem::Entity3D& (Chem::Entity3DContainer::*)(std::size_t)>(&Chem::Entity3DContainer::getEntity),
                     (python::arg("self"), python::arg("idx")),
                     python::return_internal_reference<1>())
                .def("__len__", &Chem::Entity3DContainer::getNumEntities, python::arg("self"));
        }
    };
} // namespace CDPLPythonChem

#endif // CDPL_PYTHON_BASE_ENTITY3DCONTAINERVISITOR_HPP
