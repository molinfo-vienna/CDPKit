/* 
 * BondContainerVisitor.hpp 
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


#ifndef CDPL_PYTHON_CHEM_BONDCONTAINERVISITOR_HPP
#define CDPL_PYTHON_CHEM_BONDCONTAINERVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define BONDCONTAINER_IMPL()                                   \
 void orderBonds(const CDPL::Chem::BondCompareFunction& func)  \
 {                                                             \
  this->get_override("orderBonds")(boost::ref(func));          \
 }                                                             \
                                                               \
 std::size_t getNumBonds() const                               \
 {                                                             \
  return this->get_override("getNumBonds")();                  \
 }                                                             \
                                                               \
 const CDPL::Chem::Bond& getBond(std::size_t idx) const        \
 {                                                             \
  return this->get_override("getBond")(idx);                   \
 }                                                             \
                                                               \
 bool containsBond(const CDPL::Chem::Bond& bond) const         \
 {                                                             \
  return this->get_override("containsBond")(boost::ref(bond)); \
 }                                                             \
                                                               \
 std::size_t getBondIndex(const CDPL::Chem::Bond& bond) const  \
 {                                                             \
  return this->get_override("getBondIndex")(boost::ref(bond)); \
 }                                                             \
                                                               \
 CDPL::Chem::Bond& getBond(std::size_t idx)                    \
 {                                                             \
  return this->get_override("getBond")(idx);                   \
 }


namespace CDPLPythonChem
{

    class BondContainerVisitorBase
    {

      protected:
        static bool containsBond(CDPL::Chem::BondContainer& cntnr, CDPL::Chem::Bond& bond)
        {
            return cntnr.containsBond(bond);
        }
    };

    class BondContainerVirtualFunctionsVisitor : private BondContainerVisitorBase,
                                                 public boost::python::def_visitor<BondContainerVirtualFunctionsVisitor>
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;
            using namespace CDPL;

            cl
                .def("getBond", python::pure_virtual(static_cast<Chem::Bond& (Chem::BondContainer::*)(std::size_t)>(&Chem::BondContainer::getBond)),
                     (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
                .def("containsBond", python::pure_virtual(&this->containsBond), (python::arg("self"), python::arg("bond")))
                .def("orderBonds", python::pure_virtual(&Chem::BondContainer::orderBonds), (python::arg("self"), python::arg("func")))
                .def("getBondIndex", python::pure_virtual(&getBondIndex), (python::arg("self"), python::arg("bond")))
                .def("getNumBonds", python::pure_virtual(&Chem::BondContainer::getNumBonds), python::arg("self"));
        }

        static std::size_t getBondIndex(CDPL::Chem::BondContainer& cntnr, CDPL::Chem::Bond& bond)
        {
            return cntnr.getBondIndex(bond);
        }
    };

    class BondContainerSpecialFunctionsVisitor : private BondContainerVisitorBase,
                                                 public boost::python::def_visitor<BondContainerSpecialFunctionsVisitor>
    {

        friend class boost::python::def_visitor_access;

      public:
        BondContainerSpecialFunctionsVisitor(bool contains_only):
            containsOnly(contains_only) {}

      private:
        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;
            using namespace CDPL;

            cl.def("__contains__", &this->containsBond, (python::arg("self"), python::arg("bond")));

            if (containsOnly)
                return;

            cl
                .def("__getitem__", static_cast<Chem::Bond& (Chem::BondContainer::*)(std::size_t)>(&Chem::BondContainer::getBond), (python::arg("self"), python::arg("idx")),
                     python::return_internal_reference<1>())
                .def("__len__", &Chem::BondContainer::getNumBonds, python::arg("self"));
        }

        bool containsOnly;
    };
} // namespace CDPLPythonChem

#endif // CDPL_PYTHON_CHEM_BONDCONTAINERVISITOR_HPP
