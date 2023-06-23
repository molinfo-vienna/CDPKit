/* 
 * VectorAdapterTest.cpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    template <typename Q, typename V, typename T>
    void checkVectorQuaternionAdapter(Q& quat, const V& v, typename V::SizeType n, const T& c1, const T& c2 = T(), const T& c3 = T(), const T& c4 = T(), const T& c5 = T())
    {
        BOOST_CHECK_EQUAL(quat.getC1(), c1);
        BOOST_CHECK_EQUAL(quat.getC2(), c2);
        BOOST_CHECK_EQUAL(quat.getC3(), c3);
        BOOST_CHECK_EQUAL(quat.getC4(), c4);

        BOOST_CHECK(&quat.getData().getData() == &v);
        BOOST_CHECK(&const_cast<const Q&>(quat).getData().getData() == &v);

        BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC1(), c1);
        BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC2(), c2);
        BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC3(), c3);
        BOOST_CHECK_EQUAL(const_cast<const Q&>(quat).getC4(), c4);

        BOOST_CHECK_EQUAL(v(0), c1);
        BOOST_CHECK_EQUAL(v(1), c2);
        BOOST_CHECK_EQUAL(v(2), c3);
        BOOST_CHECK_EQUAL(v(3), c4);

        if (v.getSize() > 4)
            BOOST_CHECK_EQUAL(v(4), c5);

        BOOST_CHECK_EQUAL(v.getSize(), n);
    }

    template <typename VA, typename V, typename T>
    void checkHomogenousCoordsAdapter(VA& va, const V& v, const T last_val, const T* values = 0)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(va.getSize(), v.getSize() + 1);
        BOOST_CHECK(!va.isEmpty());

        typedef typename VA::SizeType SizeType;

        for (SizeType i = 0; i < va.getSize() + 3; i++) {
            if (i >= va.getSize()) {
                BOOST_CHECK_THROW(va[i], Base::IndexError);
                BOOST_CHECK_THROW(va(i), Base::IndexError);

                BOOST_CHECK_THROW(const_cast<const VA&>(va)[i], Base::IndexError);
                BOOST_CHECK_THROW(const_cast<const VA&>(va)(i), Base::IndexError);

            } else if (i < v.getSize()) {
                BOOST_CHECK_EQUAL(va[i], v[i]);
                BOOST_CHECK_EQUAL(va(i), v(i));

                BOOST_CHECK_EQUAL(const_cast<const VA&>(va)[i], v[i]);
                BOOST_CHECK_EQUAL(const_cast<const VA&>(va)(i), v(i));
    
            } else if (i == v.getSize()) {
                BOOST_CHECK_EQUAL(va[i], last_val);
                BOOST_CHECK_EQUAL(va(i), last_val);

                BOOST_CHECK_EQUAL(const_cast<const VA&>(va)[i], last_val);
                BOOST_CHECK_EQUAL(const_cast<const VA&>(va)(i), last_val);
            }
        }

        if (values) {
            for (SizeType i = 0; i < v.getSize(); i++)
                BOOST_CHECK_EQUAL(va(i), values[i]);
        }
    }
}


BOOST_AUTO_TEST_CASE(VectorQuaternionAdapterTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Vector<double>) == typeid(VectorQuaternionAdapter<Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>::ValueType) == typeid(VectorQuaternionAdapter<Vector<double> >::ValueType));
    BOOST_CHECK(typeid(Vector<double>::Reference) == typeid(VectorQuaternionAdapter<Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorQuaternionAdapter<Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorQuaternionAdapter<const Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorQuaternionAdapter<const Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(const Vector<double>) == typeid(VectorQuaternionAdapter<const Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>) == typeid(VectorQuaternionAdapter<Vector<double> >::VectorType));

    // ---------

    Vector<double> v1;
    VectorQuaternionAdapter<Vector<double> > v1_ad(v1);

    BOOST_CHECK_THROW(v1_ad.getC1(), Base::IndexError);
    BOOST_CHECK_THROW(v1_ad.getC2(), Base::IndexError);
    BOOST_CHECK_THROW(v1_ad.getC3(), Base::IndexError);
    BOOST_CHECK_THROW(v1_ad.getC4(), Base::IndexError);

    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC1(), Base::IndexError);
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC2(), Base::IndexError);
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC3(), Base::IndexError);
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC4(), Base::IndexError);

    v1.resize(1, -1.1);

    BOOST_CHECK_NO_THROW(v1_ad.getC1());
    BOOST_CHECK_THROW(v1_ad.getC2(), Base::IndexError);
    BOOST_CHECK_THROW(v1_ad.getC3(), Base::IndexError);
    BOOST_CHECK_THROW(v1_ad.getC4(), Base::IndexError);

    BOOST_CHECK_NO_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC1());
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC2(), Base::IndexError);
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC3(), Base::IndexError);
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC4(), Base::IndexError);

    v1.resize(2, 2.2);

    BOOST_CHECK_NO_THROW(v1_ad.getC1());
    BOOST_CHECK_NO_THROW(v1_ad.getC2());
    BOOST_CHECK_THROW(v1_ad.getC3(), Base::IndexError);
    BOOST_CHECK_THROW(v1_ad.getC4(), Base::IndexError);

    BOOST_CHECK_NO_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC1());
    BOOST_CHECK_NO_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC2());
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC3(), Base::IndexError);
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC4(), Base::IndexError);

    v1.resize(3, -3.33);

    BOOST_CHECK_NO_THROW(v1_ad.getC1());
    BOOST_CHECK_NO_THROW(v1_ad.getC2());
    BOOST_CHECK_NO_THROW(v1_ad.getC3());
    BOOST_CHECK_THROW(v1_ad.getC4(), Base::IndexError);

    BOOST_CHECK_NO_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC1());
    BOOST_CHECK_NO_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC2());
    BOOST_CHECK_NO_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC3());
    BOOST_CHECK_THROW(static_cast<const VectorQuaternionAdapter<Vector<double> >&>(v1_ad).getC4(), Base::IndexError);

    v1.resize(4, 4.4);

    checkVectorQuaternionAdapter(v1_ad, v1, 4, -1.1, 2.2, -3.33, 4.4);
 
    v1.resize(5, 5.55);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.1, 2.2, -3.33, 4.4, 5.55);
 
    // ---------

    Vector<double> v2 = vec(-1.47, 0.0, 0.0, 0);
    VectorQuaternionAdapter<Vector<double> > v2_ad(v2);

    checkVectorQuaternionAdapter(v2_ad, v2, 4, -1.47);

    Vector<double> v3 = vec(1.47, 2.1, 0.0, 0);
    VectorQuaternionAdapter<const Vector<double> > v3_ad(v3);

    checkVectorQuaternionAdapter(v3_ad, v3, 4, 1.47, 2.1);
    
    CVector<double, 4> v4 = vec(1.1, -2.1, 3.2, 0);
    VectorQuaternionAdapter<const CVector<double, 4> > v4_ad(v4);

    checkVectorQuaternionAdapter(v4_ad, v4, 4, 1.1, -2.1, 3.2);

    CVector<double, 4> v5 = vec(-1.02, 2.21, -3.0, 4.4);
    VectorQuaternionAdapter<CVector<double, 4> > v5_ad(v5);

    checkVectorQuaternionAdapter(v5_ad, v5, 4, -1.02, 2.21, -3.0, 4.4);

    VectorQuaternionAdapter< CVector<double, 4> > v6_ad(v5_ad);
    
    checkVectorQuaternionAdapter(v6_ad, v5, 4, -1.02, 2.21, -3.0, 4.4);

    // ---------

    v1_ad.set();

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.0, 0.0, 0.0, 0.0, 5.55);

    v1_ad.set(-1.0);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.0, 0.0, 0.0, 0.0, 5.55);

    v1_ad.set(1.1, 2.1);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.1, 2.1, 0.0, 0.0, 5.55);

    v1_ad.set(0.0, -1.1, 0.05);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.0, -1.1, 0.05, 0.0, 5.55);

    v1(0) = 20.12;
    v1(1) = 1.13;
    v1(2) = 1.15;
    v1(3) = -4.44;

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 20.12, 1.13, 1.15, -4.44, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad = quat(11.02, 12.21, -13.0, 14.4)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 11.02, 12.21, -13.0, 14.4, 5.55);

    BOOST_CHECK(&(v1_ad = v5_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.02, 2.21, -3.0, 4.4, 5.55);

    BOOST_CHECK(&(v1_ad = 2.3) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 2.3, 0.0, 0.0, 0.0, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad -= v1_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.0, 0.0, 0.0, 0.0, 5.55);

    BOOST_CHECK(&(v1_ad -= v5_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.02, -2.21, 3.0, -4.4, 5.55);

    BOOST_CHECK(&(v1_ad -= quat(1.1, -2.1, 3.2)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.02 - 1.1, -2.21 - -2.1, 3.0 - 3.2, -4.4 - 0.0, 5.55);

    BOOST_CHECK(&(v1_ad -= -4.13f) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.02 - 1.1 - -4.13f, -2.21 - -2.1, 3.0 - 3.2, -4.4 - 0.0, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad = v5_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.02, 2.21, -3.0, 4.4, 5.55);

    BOOST_CHECK(&(v1_ad += v1_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.02 + -1.02, 2.21 + 2.21, -3.0 + -3.0, 4.4 + 4.4, 5.55);

    BOOST_CHECK(&(v1_ad += v4_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.02 + -1.02 + 1.1, 2.21 + 2.21 + -2.1, -3.0 + -3.0 + 3.2, 4.4 + 4.4 + 0.0, 5.55);

    BOOST_CHECK(&(v1_ad += quat(1.47, 2.1)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.02 + -1.02 + 1.1 + 1.47, 2.21 + 2.21 + -2.1 + 2.1, -3.0 + -3.0 + 3.2 + 0.0, 4.4 + 4.4 + 0.0 + 0.0, 5.55);

    BOOST_CHECK(&(v1_ad += 5.67f) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.02 + -1.02 + 1.1 + 1.47 + 5.67f, 2.21 + 2.21 + -2.1 + 2.1, -3.0 + -3.0 + 3.2 + 0.0, 4.4 + 4.4 + 0.0 + 0.0, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad.assign(quat(-1.47))) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.47, 0.0, 0.0, 0.0, 5.55);

    BOOST_CHECK(&(v1_ad.assign(v1_ad)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.47, 0.0, 0.0, 0.0, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad.minusAssign(v1_ad)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.0, 0.0, 0.0, 0.0, 5.55);

    BOOST_CHECK(&(v1_ad.minusAssign(quat(-1.02, 2.21, -3.0, 4.4))) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.02, -2.21, 3.0, -4.4, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad.plusAssign(v1_ad)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.02 + 1.02, -2.21 + -2.21, 3.0 + 3.0, -4.4 + -4.4, 5.55);

    BOOST_CHECK(&(v1_ad.plusAssign(quat(1.47, 2.1, -1.1, 0.35))) == &v1_ad);
    
    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.02 + 1.02 + 1.47, -2.21 + -2.21 + 2.1, 3.0 + 3.0 + -1.1, -4.4 + -4.4 + 0.35, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad *= 0) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.0, 0.0, 0.0, 0.0, 5.55);

    v1_ad.set(5.27, 1.1, 1.2, -1.3);

    BOOST_CHECK(&(v1_ad *= 2) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 5.27 * 2, 1.1 * 2, 1.2 * 2, -1.3 * 2, 5.55);

    BOOST_CHECK(&(v1_ad *= -1.0) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 5.27 * 2 * -1.0, 1.1 * 2 * -1.0, 1.2 * 2 * -1.0, -1.3 * 2 * -1.0, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad /= 2) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 5.27 * 2 * -1.0 / 2, 1.1 * 2 * -1.0 / 2, 1.2 * 2 * -1.0 / 2, -1.3 * 2 * -1.0 / 2, 5.55);

    BOOST_CHECK(&(v1_ad /= -1) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 5.27 * 2 * -1.0 / 2 / -1, 1.1 * 2 * -1.0 / 2 / -1, 1.2 * 2 * -1.0 / 2 / -1, -1.3 * 2 * -1.0 / 2 / -1, 5.55);

    // ---------

    BOOST_CHECK(&(v1_ad *= Quaternion<float>(0)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.0, 0.0, 0.0, 0.0, 5.55);

    v1_ad.set(-1.0, 1.1, -1.2, 1.3);

    BOOST_CHECK(&(v1_ad *= quat(1.0)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -1.0, 1.1, -1.2, 1.3, 5.55);

    v1_ad.set(2, 0.0, -6, 3);

    BOOST_CHECK(&(v1_ad *= quat(1, 3, -2, 2)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -16.0, 0.0, -1.0, 25.0, 5.55);

    v1_ad.set(1, 3, -2, 2);
    
    BOOST_CHECK(&(v1_ad *= Quaternion<float>(2, 0.0, -6, 3)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -16.0, 12.0, -19.0, -11.0, 5.55);

    v1_ad.set(1.0);

    BOOST_CHECK(&(v1_ad *= v1_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.0, 0.0, 0.0, 0.0, 5.55);

    // ---------

    v1_ad.set(2.0, -1.0, 2.0, 3.0);
    
    BOOST_CHECK(&(v1_ad /= Quaternion<double>(1.0)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 2.0, -1.0, 2.0, 3.0, 5.55);

    BOOST_CHECK(&(v1_ad /= Quaternion<double>(-1.0)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, -2.0, 1.0, -2.0, -3.0, 5.55);

    BOOST_CHECK(&(v1_ad /= v1_ad) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 1.0, 0.0, 0.0, 0.0, 5.55);

    v1_ad.set(2.0, 3.0, 4.0, 5.0);

    BOOST_CHECK(&(v1_ad /= quat(3.0, 4.0, 5.0, 6.0)) == &v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5.0, 0.79069767441860461, 0.023255813953488372, 0.0, 0.046511627906976744, 5.55);

    // ---------

    Vector<double> v7(0);
    VectorQuaternionAdapter<Vector<double> > v7_ad(v7);
    
    BOOST_CHECK_NO_THROW(v7_ad.swap(v7_ad));

    BOOST_CHECK_THROW(v1_ad.swap(v7_ad), Base::IndexError);

    v7.resize(1);

    BOOST_CHECK_THROW(v7_ad.swap(v1_ad), Base::IndexError);

    v7.resize(2);

    BOOST_CHECK_THROW(v1_ad.swap(v7_ad), Base::IndexError);

    v7.resize(3);

    BOOST_CHECK_THROW(v7_ad.swap(v1_ad), Base::IndexError);

    v7.resize(7);

    BOOST_CHECK_NO_THROW(v1_ad.swap(v7_ad));

    // ---------

    v1_ad.set(0.1, 0.2, -0.3, -0.4);

    v2(0) = 3.0;
    v2(1) = 4.0;
    v2(2) = 5.0;
    v2(3) = 6.0;

    v1_ad.swap(v2_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 3.0, 4.0, 5.0, 6.0, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 0.1, 0.2, -0.3, -0.4);

    v1_ad.swap(v2_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.1, 0.2, -0.3, -0.4, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 3.0, 4.0, 5.0, 6.0);

    v2_ad.swap(v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 3.0, 4.0, 5.0, 6.0, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 0.1, 0.2, -0.3, -0.4);

    v2_ad.swap(v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.1, 0.2, -0.3, -0.4, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 3.0, 4.0, 5.0, 6.0);

    swap(v1_ad, v2_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 3.0, 4.0, 5.0, 6.0, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 0.1, 0.2, -0.3, -0.4);

    swap(v1_ad, v2_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.1, 0.2, -0.3, -0.4, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 3.0, 4.0, 5.0, 6.0);

    swap(v2_ad, v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 3.0, 4.0, 5.0, 6.0, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 0.1, 0.2, -0.3, -0.4);

    swap(v2_ad, v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.1, 0.2, -0.3, -0.4, 5.55);
    checkVectorQuaternionAdapter(v2_ad, v2, 4, 3.0, 4.0, 5.0, 6.0);

    v1_ad.swap(v1_ad);

    checkVectorQuaternionAdapter(v1_ad, v1, 5, 0.1, 0.2, -0.3, -0.4, 5.55);

    swap(v2_ad, v2_ad);

    checkVectorQuaternionAdapter(v2_ad, v2, 4, 3.0, 4.0, 5.0, 6.0);
}

BOOST_AUTO_TEST_CASE(QuatFunction1Test)
{
    using namespace CDPL;
    using namespace Math;

    typedef const VectorQuaternionAdapter<Vector<double> > CVQA;
    typedef const VectorQuaternionAdapter<const Vector<double> > CCVQA;

    Vector<double> v1 = vec(1.0, 2.0, 3.0, 4.0);
    v1.resize(5, -5.55);

    checkVectorQuaternionAdapter<CVQA>(quat(v1), v1, 5, 1.0, 2.0, 3.0, 4.0, -5.55);

    const Vector<double>& v1_cref = v1;

    checkVectorQuaternionAdapter<CCVQA>(quat(v1_cref), v1_cref, 5, 1.0, 2.0, 3.0, 4.0, -5.55);

    // ---------

    checkVectorQuaternionAdapter<CVQA>((quat(v1) += quat(0.1, 0.2, 0.3, 0.4)), v1, 5, 1.0 + 0.1, 2.0 + 0.2, 3.0 + 0.3, 4.0 + 0.4, -5.55);
}

BOOST_AUTO_TEST_CASE(HomogenousCoordsAdapterTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Vector<double>::ValueType) == typeid(HomogenousCoordsAdapter<Vector<double> >::ValueType));
    BOOST_CHECK(typeid(Vector<double>::SizeType) == typeid(HomogenousCoordsAdapter<Vector<double> >::SizeType));
    BOOST_CHECK(typeid(Vector<double>::DifferenceType) == typeid(HomogenousCoordsAdapter<Vector<double> >::DifferenceType));
    BOOST_CHECK(typeid(Vector<double>::Reference) == typeid(HomogenousCoordsAdapter<Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(HomogenousCoordsAdapter<Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(HomogenousCoordsAdapter<const Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(HomogenousCoordsAdapter<const Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(const Vector<double>) == typeid(HomogenousCoordsAdapter<const Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>) == typeid(HomogenousCoordsAdapter<Vector<double> >::VectorType));

    // ---------

    Vector<double> v1;
    HomogenousCoordsAdapter<Vector<double> > v1_hca(v1);

    // ---------

    BOOST_CHECK(&v1_hca.getData().getData() == &v1);
    BOOST_CHECK(&const_cast<const HomogenousCoordsAdapter<Vector<double> >&>(v1_hca).getData().getData() == &v1);

    // ---------

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    v1_hca.getData().getData().resize(4, 2.2);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    v1[0] = 2.0;
    v1_hca(3) = 3.0;
    v1_hca.getData().getData()[2] = -1.0;

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    Vector<double> v2(v1_hca);
    HomogenousCoordsAdapter<Vector<double> > v2_hca(v2);

    checkHomogenousCoordsAdapter(v2_hca, v2, 1.0);

    // ---------

    Vector<double> v3(v1.getData());
    HomogenousCoordsAdapter<Vector<double> > v3_hca(v3);

    checkHomogenousCoordsAdapter(v3_hca, v3, 1.0);

    // ---------

    Vector<double> v4(4);
    HomogenousCoordsAdapter<Vector<double> > v4_hca(v4);

    checkHomogenousCoordsAdapter(v4_hca, v4, 1.0);

    // ---------

    Vector<double> v5(4, 2.2);
    HomogenousCoordsAdapter<const Vector<double> > v5_hca(v5);

    checkHomogenousCoordsAdapter(v5_hca, v5, 1.0);

    // --------

    Vector<double> v6(static_cast<const VectorExpression<Vector<double> >&>(v1));
    HomogenousCoordsAdapter<const Vector<double> > v6_hca(v6);

    checkHomogenousCoordsAdapter(v6_hca, v6, 1.0);

    // ---------

    Vector<double> v7;
    HomogenousCoordsAdapter<Vector<double> > v7_hca(v7);

    v7.resize(1, 2.0);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);

    v7.resize(2, -1.2);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);

    v7_hca.getData().getData().resize(3, 5.0);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);

    v7.resize(0);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);

    v7.resize(6, 1.0);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);

    // ---------

    v7_hca.getData().getData().clear();

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);

    // ---------

    BOOST_CHECK(&(v1_hca *= -2.0) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, -2.0);

    // ---------

    BOOST_CHECK(&(v1_hca /= -2.0) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    BOOST_CHECK(&(v1_hca += v1_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 2.0);

    BOOST_CHECK_THROW(v1_hca += v7, Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 2.0);

    BOOST_CHECK_THROW(v1_hca += Vector<float>(), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 2.0);

    // ---------

    BOOST_CHECK(&(v1_hca -= v2) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca -= v7, Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca -= Vector<float>(), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    v1.resize(v1.getSize() + 1, 0.2);

    BOOST_CHECK(&(v1_hca += v2_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 2.0);

    // ---------

    BOOST_CHECK(&(v1_hca -= v1_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    // ---------

    BOOST_CHECK(&(v1_hca += v2_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    v7.clear(0.0);

    BOOST_CHECK(&(v1_hca += v7) == &v1_hca);

    v7.resize(10.0, 0.0);

    BOOST_CHECK_THROW(v1_hca += v7, Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca += Vector<int>(), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    v6 = v1;
    v6.resize(v1.getSize() + 1, 1.0);

    BOOST_CHECK(&(v1_hca += v6) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 2.0);

    // ---------

    BOOST_CHECK(&(v1_hca -= v2_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca -= v7, Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca -= Vector<float>(), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    BOOST_CHECK(&(v1_hca -= v1_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    // ---------

    BOOST_CHECK(&v1_hca.plusAssign(v2_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca.plusAssign(v7_hca), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca.plusAssign(Vector<float>()), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    BOOST_CHECK(&v1_hca.plusAssign(v1_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 2.0);

    // ---------

    BOOST_CHECK(&v1_hca.minusAssign(v2_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca.minusAssign(v7), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    BOOST_CHECK_THROW(v1_hca.minusAssign(Vector<int>()), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    // ---------

    v6 = v1_hca;

    BOOST_CHECK(&v1_hca.minusAssign(v6) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    // ---------

    v1.resize(2);

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    v1.resize(v2.getSize());

    BOOST_CHECK(&(v1_hca = v2_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v2, 1.0);
    
    v1.resize(v5.getSize() - 1);
    
    BOOST_CHECK(&(v1_hca = v5) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, v5[v5.getSize() - 1]);

    v1.resize(v7.getSize() - 1);

    BOOST_CHECK(&(v1_hca = v7) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, v7[v7.getSize() - 1]);

    BOOST_CHECK(&(v1_hca = v1_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, v7[v7.getSize() - 1]);

    BOOST_CHECK(&(v1 = v7) == &v1);

    checkHomogenousCoordsAdapter(v1_hca, v1, v7[v7.getSize() - 1]);

    // ---------

    v1.resize(v3.getSize() - 1);

    BOOST_CHECK(&v1_hca.assign(v3) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, v3[v3.getSize() - 1]);

    v1.resize(v5.getSize());

    BOOST_CHECK(&v1_hca.assign(v5_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v5, v5_hca[v5_hca.getSize() - 1]);

    v1.resize(v6.getSize() - 1);

    BOOST_CHECK(&v1_hca.assign(v6) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, v6[v6.getSize() - 1]);

    BOOST_CHECK(&v1_hca.assign(v1_hca) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, v6[v6.getSize() - 1]);

    BOOST_CHECK(&v1_hca.assign(Vector<float>(v1.getSize() + 1)) == &v1_hca);

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    // ---------
    
    BOOST_CHECK_THROW(swap(v1_hca, v7_hca), Base::SizeError);

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    v1.resize(v7.getSize());
    v7.clear(2.1);

    swap(v1_hca, v7_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 0.0);
    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    swap(v1_hca, v7_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);
    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    swap(v7_hca, v1_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 0.0);
    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    swap(v7_hca, v1_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);
    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    v1_hca.swap(v7_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 0.0);
    checkHomogenousCoordsAdapter(v1_hca, v1, 1.0);

    v1_hca.swap(v7_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);
    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0);

    swap(v7_hca, v7_hca);

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0);


    // ---------

    const double v1_vals[] = { 0,0,0,0,0,0,0,0,0,0,0 };

    checkHomogenousCoordsAdapter(v1_hca, v1, 0.0, v1_vals);

    const double v2_vals[] = { 2,2.2,-1,3,1,1 };

    checkHomogenousCoordsAdapter(v2_hca, v2, 1.0, v2_vals);

    const double v3_vals[] = { 2,2.2,-1,3,1 };

    checkHomogenousCoordsAdapter(v3_hca, v3, 1.0, v3_vals);

    const double v4_vals[] = { 0,0,0,0,1 };

    checkHomogenousCoordsAdapter(v4_hca, v4, 1.0, v4_vals);

    const double v5_vals[] = { 2.2,2.2,2.2,2.2,1 };

    checkHomogenousCoordsAdapter(v5_hca, v5, 1.0, v5_vals);

    const double v6_vals[] = { 2,2.2,-1,3,1,1,1 };

    checkHomogenousCoordsAdapter(v6_hca, v6, 1.0, v6_vals);

    const double v7_vals[] = { 2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,2.1,1 };

    checkHomogenousCoordsAdapter(v7_hca, v7, 1.0, v7_vals);
}

BOOST_AUTO_TEST_CASE(HomogFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef const HomogenousCoordsAdapter<Vector<double> > HCA;
    typedef const HomogenousCoordsAdapter<const Vector<double> > CHCA;

    Vector<double> v1 = vec(1.0, 2.0, 3.0, 4.0);
    v1.resize(5, -5.55);

    const double values[] = { 1.0, 2.0, 3.0, 4.0, -5.55 };

    checkHomogenousCoordsAdapter<HCA>(homog(v1), v1, 1.0, values);

    const Vector<double>& v1_cref = v1;

    checkHomogenousCoordsAdapter<CHCA>(homog(v1_cref), v1_cref, 1.0, values);
}
