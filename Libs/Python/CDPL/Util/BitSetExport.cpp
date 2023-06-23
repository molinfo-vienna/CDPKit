/* 
 * BitSetExport.cpp 
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

#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/BitSet.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{
 
    inline void checkIndex(const CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx)
    {
        if (idx < bs.size())
            return;

        throw CDPL::Base::IndexError("BitSet: bit index out of bounds");
    }

    inline void checkSizeEquality(const CDPL::Util::BitSet& bs1, const CDPL::Util::BitSet& bs2)
    {
        if (bs1.size() == bs2.size())
            return;

        throw CDPL::Base::ValueError("BitSet: bitset with different size");
    }

    CDPL::Util::BitSet& flipBit(CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx)
    {
        checkIndex(bs, idx);

        return bs.flip(idx);
    }

    CDPL::Util::BitSet& setBit(CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx, bool value = true)
    {
        checkIndex(bs, idx);

        return bs.set(idx, value);
    }
    
    void setItem(CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx, bool value)
    {
        checkIndex(bs, idx);

        setBit(bs, idx, value);
    }

    CDPL::Util::BitSet& resetBit(CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx)
    {
        checkIndex(bs, idx);

        return bs.reset(idx);
    }

    bool testBit(CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx)
    {
        checkIndex(bs, idx);

        return bs.test(idx);
    }

    CDPL::Util::BitSet::size_type findNext(CDPL::Util::BitSet& bs, CDPL::Util::BitSet::size_type idx)
    {
        checkIndex(bs, idx);

        return bs.find_next(idx);
    }

    bool isSubsetOf(const CDPL::Util::BitSet& bs1, const CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return bs1.is_subset_of(bs2);
    }

    bool isProperSubsetOf(const CDPL::Util::BitSet& bs1, const CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return bs1.is_proper_subset_of(bs2);
    }

    CDPL::Util::BitSet& iandOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 &= bs2);
    }

    CDPL::Util::BitSet& iorOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 |= bs2);
    }

    CDPL::Util::BitSet& ixorOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 ^= bs2);
    }

    CDPL::Util::BitSet& isubOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 -= bs2);
    }

    CDPL::Util::BitSet andOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 & bs2);
    }

    CDPL::Util::BitSet orOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 | bs2);
    }

    CDPL::Util::BitSet xorOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 ^ bs2);
    }

    CDPL::Util::BitSet subOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 - bs2);
    }

    bool ltOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 < bs2);
    }

    bool leOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 <= bs2);
    }

    bool gtOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 > bs2);
    }

    bool geOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        checkSizeEquality(bs1, bs2);

        return (bs1 >= bs2);
    }

    bool eqOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        return (bs1 == bs2);
    }

    bool neOperator(CDPL::Util::BitSet& bs1, CDPL::Util::BitSet& bs2)
    {
        return (bs1 != bs2);
    }

    std::string toString(CDPL::Util::BitSet& bs)
    {
        std::string str;

        to_string(bs, str);

        return str;
    }

    CDPL::Util::BitSet::size_type getNPos()
    {
        return CDPL::Util::BitSet::npos;
    }
}


void CDPLPythonUtil::exportBitSet()
{
    using namespace boost;
    using namespace CDPL;

    typedef Util::BitSet& (Util::BitSet::*NoArgMemFunc)();

    python::class_<Util::BitSet>("BitSet", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Util::BitSet&>((python::arg("self"), python::arg("bs"))))
        .def(python::init<Util::BitSet::size_type, unsigned long>((python::arg("self"), python::arg("num_bits"), python::arg("value") = 0)))
        .def(python::init<const std::string&>((python::arg("self"), python::arg("bit_str"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Util::BitSet>())
        .def("swap", &Util::BitSet::swap, (python::arg("self"), python::arg("bs")))
        .def("assign", CDPLPythonBase::copyAssOp(&Util::BitSet::operator=), (python::arg("self"), python::arg("bs")), python::return_self<>())
        .def("resize", &Util::BitSet::resize, (python::arg("self"), python::arg("num_bits"), python::arg("value") = false))
        .def("clear", &Util::BitSet::clear, python::arg("self"))
        .def("append", &Util::BitSet::push_back, (python::arg("self"), python::arg("value")))
        .def("flip", NoArgMemFunc(&Util::BitSet::flip), python::arg("self"), python::return_self<>())
        .def("flip", &flipBit, (python::arg("self"), python::arg("idx")), python::return_arg<1>())
        .def("set", NoArgMemFunc(&Util::BitSet::set), python::arg("self"), python::return_self<>())
        .def("set", &setBit, (python::arg("self"), python::arg("idx"), python::arg("value") = true), python::return_arg<1>())
        .def("reset", NoArgMemFunc(&Util::BitSet::reset), python::arg("self"), python::return_self<>())
        .def("reset", &resetBit, (python::arg("self"), python::arg("idx")), python::return_arg<1>())
        .def("test", &testBit, (python::arg("self"), python::arg("idx")))
        .def("findFirst", &Util::BitSet::find_first, python::arg("self"))
        .def("findNext", &findNext, (python::arg("self"), python::arg("idx")))
        .def("isSubsetOf", &isSubsetOf, (python::arg("self"), python::arg("bs")))
        .def("isProperSubsetOf", &isProperSubsetOf, (python::arg("self"), python::arg("bs")))
        .def("isEmpty", &Util::BitSet::empty, python::arg("self"))
        .def("getCount", &Util::BitSet::count, python::arg("self"))
        .def("getSize", &Util::BitSet::size, python::arg("self"))
        .def("getMaxSize", &Util::BitSet::max_size, python::arg("self"))
        .def("hasAny", &Util::BitSet::any, python::arg("self"))
        .def("hasNone", &Util::BitSet::none, python::arg("self"))
        .add_property("empty", &Util::BitSet::empty)
        .add_property("count", &Util::BitSet::count)
        .add_property("size", &Util::BitSet::size)
        .add_property("maxSize", &Util::BitSet::max_size)
        .add_property("any", &Util::BitSet::any)
        .add_property("none", &Util::BitSet::none)
        .def("__getitem__", &testBit, (python::arg("self"), python::arg("idx")))
        .def("__setitem__", &setItem, (python::arg("self"), python::arg("idx"), python::arg("value")))
        .def("__and__", &andOperator, (python::arg("self"), python::arg("bs")))
        .def("__or__", &orOperator, (python::arg("self"), python::arg("bs")))
        .def("__xor__", &xorOperator, (python::arg("self"), python::arg("bs")))
        .def("__sub__", &subOperator, (python::arg("self"), python::arg("bs")))
        .def("__iand__", &iandOperator, (python::arg("self"), python::arg("bs")), python::return_arg<1>())
        .def("__ior__", &iorOperator, (python::arg("self"), python::arg("bs")), python::return_arg<1>())
        .def("__ixor__", &ixorOperator, (python::arg("self"), python::arg("bs")), python::return_arg<1>())
        .def("__isub__", &isubOperator, (python::arg("self"), python::arg("bs")), python::return_arg<1>())
        .def("__long__", &Util::BitSet::to_ulong, python::arg("self"))
        .def("__ilshift__", &Util::BitSet::operator<<=, (python::arg("self"), python::arg("num_bits")), python::return_self<>())
        .def("__lshift__", &Util::BitSet::operator<<, (python::arg("self"), python::arg("num_bits")))
        .def("__irshift__", &Util::BitSet::operator>>=, (python::arg("self"), python::arg("num_bits")), python::return_self<>())
        .def("__rshift__", &Util::BitSet::operator>>, (python::arg("self"), python::arg("num_bits")))
        .def("__invert__", &Util::BitSet::operator~, python::arg("self"))
        .def("__eq__", &eqOperator, (python::arg("self"), python::arg("bs")))
        .def("__ne__", &neOperator, (python::arg("self"), python::arg("bs")))
        .def("__lt__", &ltOperator, (python::arg("self"), python::arg("bs")))
        .def("__le__", &leOperator, (python::arg("self"), python::arg("bs")))
        .def("__gt__", &gtOperator, (python::arg("self"), python::arg("bs")))
        .def("__ge__", &geOperator, (python::arg("self"), python::arg("bs")))
        .def("__len__", &Util::BitSet::size, python::arg("self"))
        .def("__nonzero__", &Util::BitSet::any, python::arg("self"))
        .def("__bool__", &Util::BitSet::any, python::arg("self"))
        .def("__str__", &toString, python::arg("self"))
        .add_static_property("npos", &getNPos);

    python::def("fold", &Util::fold, (python::arg("bs"), python::arg("num_times")));
}
