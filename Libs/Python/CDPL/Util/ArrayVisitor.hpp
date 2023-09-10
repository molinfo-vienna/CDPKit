/* 
 * ArrayVisitor.hpp 
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


#ifndef CDPL_PYTHON_UTIL_ARRAYVISITOR_HPP
#define CDPL_PYTHON_UTIL_ARRAYVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"


#if (CDPL_UTIL_ARRAY_CHECKS_DISABLE == 0)
# define CHECK_ARRAY_INDEX(a, i, end_ok)
#else
# define CHECK_ARRAY_INDEX(a, i, end_ok)                                \
  if (end_ok) {                                                         \
   if (i > a.getSize())                                                 \
    throw CDPL::Base::IndexError("Array: element index out of bounds"); \
  } else if (i >= a.getSize())                                          \
   throw CDPL::Base::IndexError("Array: element index out of bounds");
#endif


namespace CDPLPythonUtil
{

    template <typename ArrayType, typename ElementReturnPolicy,
              typename ElementAdditionPolicy1, typename ElementAdditionPolicy2, typename ElementAdditionPolicy3>
    class ArrayVisitor : public boost::python::def_visitor<ArrayVisitor<ArrayType, ElementReturnPolicy,
                                                                        ElementAdditionPolicy1, ElementAdditionPolicy2, ElementAdditionPolicy3> >
    {
        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;

            void (ArrayType::*assignFunc)(std::size_t, const typename ArrayType::BaseType::ElementType&) = &ArrayType::assign;
            void (ArrayType::*removeElementFunc)(std::size_t)                                            = &ArrayType::removeElement;
            void (ArrayType::*insertElementFunc)(std::size_t, const typename ArrayType::BaseType::ElementType&) =
                &ArrayType::insertElement;
            void (ArrayType::*insertElementsFunc)(std::size_t, std::size_t, const typename ArrayType::BaseType::ElementType&) =
                &ArrayType::insertElements;

            typename ArrayType::BaseType::ElementType& (ArrayType::*getFirstElementFunc)()       = &ArrayType::BaseType::getFirstElement;
            typename ArrayType::BaseType::ElementType& (ArrayType::*getLastElementFunc)()        = &ArrayType::BaseType::getLastElement;
            typename ArrayType::BaseType::ElementType& (ArrayType::*getElementFunc)(std::size_t) = &ArrayType::BaseType::getElement;

            void (ArrayType::*addElementFunc)(const typename ArrayType::BaseType::ElementType&) = &ArrayType::addElement;

            cl
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ArrayType>())
                .def("getSize", &ArrayType::getSize, python::arg("self"))
                .def("isEmpty", &ArrayType::isEmpty, python::arg("self"))
                .def("resize", &ArrayType::resize, (python::arg("self"), python::arg("num_elem"), python::arg("value")),
                     ElementAdditionPolicy2())
                .def("reserve", &ArrayType::reserve, (python::arg("self"), python::arg("num_elem")))
                .def("getCapacity", &ArrayType::getCapacity, python::arg("self"))
                .def("clear", &ArrayType::clear, python::arg("self"))
                .def("assign", CDPLPythonBase::copyAssOp<ArrayType>(), (python::arg("self"), python::arg("array")),
                     python::return_self<ElementAdditionPolicy1>())
                .def("assign", assignFunc, (python::arg("self"), python::arg("num_elem"), python::arg("value")),
                     ElementAdditionPolicy2())
                .def("addElement", addElementFunc, (python::arg("self"), python::arg("value")),
                     ElementAdditionPolicy1())
                .def("addElements", &addElements, (python::arg("self"), python::arg("values")),
                     ElementAdditionPolicy1())
                .def("insertElement", insertElementFunc, (python::arg("self"), python::arg("idx"), python::arg("value")),
                     ElementAdditionPolicy2())
                .def("insertElements", insertElementsFunc, (python::arg("self"), python::arg("idx"), python::arg("num_elem"), python::arg("value")),
                     ElementAdditionPolicy3())
                .def("insertElements", &insertElements, (python::arg("self"), python::arg("index"), python::arg("values")),
                     ElementAdditionPolicy2())
                .def("popLastElement", &ArrayType::popLastElement, python::arg("self"))
                .def("removeElement", removeElementFunc, (python::arg("self"), python::arg("idx")))
                .def("removeElements", &removeElements, (python::arg("self"), python::arg("begin_idx"), python::arg("end_idx")))
                .def("getFirstElement", getFirstElementFunc, python::arg("self"), ElementReturnPolicy())
                .def("getLastElement", getLastElementFunc, python::arg("self"), ElementReturnPolicy())
                .def("getElement", getElementFunc, (python::arg("self"), python::arg("idx")),
                     ElementReturnPolicy())
                .def("setElement", &setItem, (python::arg("self"), python::arg("idx"), python::arg("value")),
                     ElementAdditionPolicy2())
                .def("__delitem__", &delItem, (python::arg("self"), python::arg("idx")))
                .def("__getitem__", &getItem, (python::arg("self"), python::arg("idx")), ElementReturnPolicy())
                .def("__len__", &ArrayType::getSize, python::arg("self"))
                .def("__setitem__", &setItem, (python::arg("self"), python::arg("index"), python::arg("value")),
                     ElementAdditionPolicy2())
                .add_property("size", &ArrayType::getSize);
        }

        static void popElement(ArrayType& array)
        {
#if (CDPL_UTIL_ARRAY_CHECKS_DISABLE == 0)
#else
            if (array.isEmpty())
                throw CDPL::Base::OperationFailed("Array: operation requires non-empty array");
#endif
            array.popLastElement();
        }

        static void insertElements(ArrayType& array, std::size_t index, const ArrayType& values)
        {
            CHECK_ARRAY_INDEX(array, index, true);

            array.insertElements(index, values.getBase().getElementsBegin(), values.getBase().getElementsEnd());
        }

        static void addElements(ArrayType& array, const ArrayType& values)
        {
            array.insertElements(array.getElementsEnd(), values.getBase().getElementsBegin(), values.getBase().getElementsEnd());
        }

        static void removeElements(ArrayType& array, std::size_t begin, std::size_t end)
        {
            CHECK_ARRAY_INDEX(array, begin, true);
            CHECK_ARRAY_INDEX(array, end, true);

            array.removeElements(array.getElementsBegin() + begin, array.getElementsBegin() + end);
        }

        static typename ArrayType::BaseType::ElementType& getItem(ArrayType& array, std::size_t idx)
        {
            CHECK_ARRAY_INDEX(array, idx, false);

            return array.ArrayType::BaseType::getElement(idx);
        }

        static void delItem(ArrayType& array, std::size_t idx)
        {
            CHECK_ARRAY_INDEX(array, idx, false);

            array.removeElement(idx);
        }

        static void setItem(ArrayType& array, std::size_t idx, const typename ArrayType::BaseType::ElementType& value)
        {
            CHECK_ARRAY_INDEX(array, idx, false);

            array.setElement(idx, value);
        }
    };
} // namespace CDPLPythonUtil

#endif // CDPL_PYTHON_UTIL_ARRAYVISITOR_HPP
