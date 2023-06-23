/* 
 * DataIOBaseTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Base/DataIOBase.hpp"


namespace
{

    class TestDataIOBase : public CDPL::Base::DataIOBase 
    {

    public:
        using CDPL::Base::DataIOBase::invokeIOCallbacks;
    };

    struct TestCallback
    {

        TestCallback(const CDPL::Base::DataIOBase& iob): ioBase(iob), calls(0) {}
 
        void operator()(const CDPL::Base::DataIOBase& iob, double) {
            if (&ioBase == &iob)
                calls++;
        }

        const CDPL::Base::DataIOBase& ioBase;
        std::size_t                   calls;
    };
}


BOOST_AUTO_TEST_CASE(DataIOBaseTest)
{
    using namespace CDPL;
    using namespace Base;

    TestDataIOBase test_iob;

    BOOST_CHECK(test_iob.registerIOCallback(TestCallback(test_iob)) == 0);
    BOOST_CHECK(test_iob.registerIOCallback(TestCallback(test_iob)) == 1);
    BOOST_CHECK(test_iob.registerIOCallback(TestCallback(test_iob)) == 2);

    test_iob.unregisterIOCallback(1);

    BOOST_CHECK(test_iob.registerIOCallback(TestCallback(test_iob)) == 1);

    TestCallback test_cb1(test_iob);
    TestCallback test_cb2(test_iob);

    test_iob.unregisterIOCallback(0);

    BOOST_CHECK(test_iob.registerIOCallback(std::ref(test_cb1)) == 0);

    test_iob.invokeIOCallbacks(1.0);

    BOOST_CHECK(test_cb1.calls == 1);
    BOOST_CHECK(test_cb2.calls == 0);

    test_iob.invokeIOCallbacks(1.0);

    BOOST_CHECK(test_cb1.calls == 2);
    BOOST_CHECK(test_cb2.calls == 0);

    BOOST_CHECK(test_iob.registerIOCallback(std::ref(test_cb2)) == 3);

    BOOST_CHECK(test_cb1.calls == 2);
    BOOST_CHECK(test_cb2.calls == 0);

    test_iob.invokeIOCallbacks(1.0);

    BOOST_CHECK(test_cb1.calls == 3);
    BOOST_CHECK(test_cb2.calls == 1);

    test_iob.invokeIOCallbacks(1.0);

    BOOST_CHECK(test_cb1.calls == 4);
    BOOST_CHECK(test_cb2.calls == 2);

    test_iob.unregisterIOCallback(0);    
    test_iob.invokeIOCallbacks(1.0);

    BOOST_CHECK(test_cb1.calls == 4);
    BOOST_CHECK(test_cb2.calls == 3);
}

