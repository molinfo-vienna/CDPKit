/* 
 * VectorProxyTest.cpp 
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

#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    template <typename VR, typename V, typename R, typename T>
    void checkVectorRange(VR& vr, const V& v, const R& r, const T* values)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(vr.getSize(), r.getSize());
        BOOST_CHECK_EQUAL(vr.getStart(), r.getStart());
        BOOST_CHECK(vr.isEmpty() == r.isEmpty());

        typedef typename VR::SizeType SizeType;

        for (SizeType i = 0; i < vr.getSize() + 3; i++) {
            if (i >= vr.getSize()) {
                BOOST_CHECK_THROW(vr[i], Base::IndexError);
                BOOST_CHECK_THROW(vr(i), Base::IndexError);

                BOOST_CHECK_THROW(const_cast<const VR&>(vr)[i], Base::IndexError);
                BOOST_CHECK_THROW(const_cast<const VR&>(vr)(i), Base::IndexError);

            } else {
                BOOST_CHECK_EQUAL(vr[i], v[r(i)]);
                BOOST_CHECK_EQUAL(vr(i), v(r(i)));

                BOOST_CHECK_EQUAL(const_cast<const VR&>(vr)[i], v[r(i)]);
                BOOST_CHECK_EQUAL(const_cast<const VR&>(vr)(i), v(r(i)));
            }
        }

        if (values) {
            for (SizeType i = 0; i < v.getSize(); i++) {
                BOOST_CHECK_EQUAL(v(i), values[i]);
            }
        }
    }

    template <typename VS, typename V, typename S, typename T>
    void checkVectorSlice(VS& vs, const V& v, const S& s, const T* values)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(vs.getSize(), s.getSize());
        BOOST_CHECK_EQUAL(vs.getStart(), s.getStart());
        BOOST_CHECK_EQUAL(vs.getStride(), s.getStride());
        BOOST_CHECK(vs.isEmpty() == s.isEmpty());

        typedef typename VS::SizeType SizeType;

        for (SizeType i = 0; i < vs.getSize() + 3; i++) {
            if (i >= vs.getSize()) {
                BOOST_CHECK_THROW(vs[i], Base::IndexError);
                BOOST_CHECK_THROW(vs(i), Base::IndexError);

                BOOST_CHECK_THROW(const_cast<const VS&>(vs)[i], Base::IndexError);
                BOOST_CHECK_THROW(const_cast<const VS&>(vs)(i), Base::IndexError);

            } else {
                BOOST_CHECK_EQUAL(vs[i], v[s(i)]);
                BOOST_CHECK_EQUAL(vs(i), v(s(i)));

                BOOST_CHECK_EQUAL(const_cast<const VS&>(vs)[i], v[s(i)]);
                BOOST_CHECK_EQUAL(const_cast<const VS&>(vs)(i), v(s(i)));
            }
        }

        if (values) {
            for (SizeType i = 0; i < v.getSize(); i++) {
                BOOST_CHECK_EQUAL(v(i), values[i]);
            }
        }
    }
}


BOOST_AUTO_TEST_CASE(VectorRangeTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Vector<double>) == typeid(VectorRange<Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>::ValueType) == typeid(VectorRange<Vector<double> >::ValueType));
    BOOST_CHECK(typeid(Vector<double>::SizeType) == typeid(VectorRange<Vector<double> >::SizeType));
    BOOST_CHECK(typeid(Vector<double>::DifferenceType) == typeid(VectorRange<Vector<double> >::DifferenceType));
    BOOST_CHECK(typeid(Vector<double>::Reference) == typeid(VectorRange<Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorRange<Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorRange<const Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorRange<const Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(const Vector<double>) == typeid(VectorRange<const Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>) == typeid(VectorRange<Vector<double> >::VectorType));

    BOOST_CHECK(typeid(Range<Vector<double>::SizeType>) == typeid(VectorRange<Vector<double> >::RangeType));
    BOOST_CHECK(typeid(Range<Vector<double>::SizeType>) == typeid(VectorRange<const Vector<double> >::RangeType));

    // ---------

    typedef VectorRange<Vector<double> >::RangeType RangeType1;

    Vector<double> v1;
    RangeType1 rng1(1, 4);
    VectorRange<Vector<double> > v1_rng(v1, rng1);

    BOOST_CHECK(&v1_rng.getData().getData() == &v1);
    BOOST_CHECK(&const_cast<const VectorRange<Vector<double> >&>(v1_rng).getData().getData() == &v1);

    // ---------

    BOOST_CHECK_THROW(v1_rng(0), Base::IndexError);
    BOOST_CHECK_THROW(v1_rng[0], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)(0), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)[0], Base::IndexError);

    v1.resize(1, 1.1);

    BOOST_CHECK_THROW(v1_rng(0), Base::IndexError);
    BOOST_CHECK_THROW(v1_rng[0], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)(0), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)[0], Base::IndexError);

    v1.resize(3, 2.2);

    BOOST_CHECK_THROW(v1_rng(2), Base::IndexError);
    BOOST_CHECK_THROW(v1_rng[2], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)(2), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)[2], Base::IndexError);

    BOOST_CHECK_NO_THROW(v1_rng(0));
    BOOST_CHECK_NO_THROW(v1_rng[0]);
    BOOST_CHECK_NO_THROW(v1_rng(1));
    BOOST_CHECK_NO_THROW(v1_rng[1]);

    BOOST_CHECK_NO_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)(0));
    BOOST_CHECK_NO_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)[0]);
    BOOST_CHECK_NO_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)(1));
    BOOST_CHECK_NO_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)[1]);

    v1.resize(4, 4.4);

    checkVectorRange(v1_rng, v1, rng1, static_cast<double*>(0));

    v1.resize(1);

    BOOST_CHECK_THROW(v1_rng(0), Base::IndexError);
    BOOST_CHECK_THROW(v1_rng[0], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)(0), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorRange<Vector<double> >&>(v1_rng)[0], Base::IndexError);

    // ---------

    v1.resize(5, 5.5);

    v1_rng[0] = 2.0;
    v1_rng.getData()[2] = -1.0;
    v1_rng(2) = 3.0;

    double values1[] = { 1.1, 2.0, -1.0, 3.0, 5.5 };

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    Vector<double> v2(v1_rng);
    RangeType1 rng2(0, 3);
    VectorRange<Vector<double> > v2_rng(v2, rng2);

    checkVectorRange(v2_rng, v2, rng2, values1 + 1);

    // ---------

    Vector<double> v3(v1);
    RangeType1 rng3(0, 4);
    VectorRange<Vector<double> > v3_rng(v3, rng3);
    VectorRange<Vector<double> > v3_rng_tmp(v3_rng);

    checkVectorRange(v3_rng, v3, rng3, values1);
    checkVectorRange(v3_rng_tmp, v3, rng3, values1);

    // ---------

    Vector<double> v4(v1);
    RangeType1 rng4(2, 2);
    VectorRange<Vector<double> > v4_rng(v4, rng4);

    checkVectorRange(v4_rng, v4, rng4, values1);

    // ---------

    Vector<double> v5(v1);
    RangeType1 rng5(1, 5);
    VectorRange<const Vector<double> > v5_rng(v5, rng5);

    checkVectorRange(v5_rng, v5, rng5, values1);

    // ---------

    VectorRange<VectorRange<const Vector<double> > > v6_rng(v5_rng, rng3);

    checkVectorRange(v6_rng, v5_rng, rng3, values1 + 1);

    BOOST_CHECK(&v6_rng.getData().getData().getData() == &v5);
    BOOST_CHECK(&const_cast<const VectorRange<VectorRange<const Vector<double> > >&>(v6_rng).getData().getData().getData() == &v5);

    // ---------

    BOOST_CHECK(&(v1_rng *= -2.0) == &v1_rng);

    double values2[] = { 1.1, 2.0 * -2.0, -1.0 * -2.0, 3.0 * -2.0, 5.5 };

    checkVectorRange(v1_rng, v1, rng1, values2);

    // ---------

    BOOST_CHECK(&(v1_rng /= -2.0) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    BOOST_CHECK(&(v1_rng += v2) == &v1_rng);

    double values3[] = { 1.1, 2.0 + 2.0, -1.0 + -1.0, 3.0 + 3.0, 5.5 };

    checkVectorRange(v1_rng, v1, rng1, values3);

    BOOST_CHECK_THROW(v1_rng += v1, Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values3);

    BOOST_CHECK_THROW(v1_rng += Vector<float>(), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values3);

    // ---------
    
    BOOST_CHECK(&(v1_rng -= v2) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng -= v5_rng, Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng -= Vector<int>(2), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    BOOST_CHECK(&(v1_rng += v1_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);

    // ---------
    
    double values4[] = { 1.1, 0.0, 0.0, 0.0, 5.5 };

    BOOST_CHECK(&(v1_rng -= v1_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values4);

    // ---------

    BOOST_CHECK(&(v1_rng += v2_rng) == &v1_rng);
    BOOST_CHECK(&(v1_rng += v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);

    // ---------

    BOOST_CHECK(&(v1_rng -= v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    BOOST_CHECK(&v1_rng.plusAssign(v2) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);

    BOOST_CHECK_THROW(v1_rng.plusAssign(v1), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values3);

    BOOST_CHECK_THROW(v1_rng.plusAssign(Vector<float>()), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values3);

    // ---------
    
    BOOST_CHECK(&v1_rng.minusAssign(v2) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng.minusAssign(v5_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng.minusAssign(Vector<int>(2)), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    BOOST_CHECK(&v1_rng.plusAssign(v1_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);

    // ---------

    BOOST_CHECK(&v1_rng.minusAssign(v1_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values4);

    // ---------

    BOOST_CHECK(&v1_rng.plusAssign(v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    BOOST_CHECK(&v1_rng.minusAssign(v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values4);

    // ---------

    BOOST_CHECK(&(v1_rng = v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK(&(v1_rng = v1_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK(&(v1_rng = Vector<float>(3, 0.0f)) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values4);

    BOOST_CHECK(&(v1_rng = v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW((v1_rng = v3_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW((v1_rng = Vector<float>(2, 0.0f)), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW((v1_rng = Vector<int>(4, 0)), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------

    BOOST_CHECK(&(v1_rng += v2) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);

    BOOST_CHECK(&v1_rng.assign(v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK(&v1_rng.assign(v1_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK(&v1_rng.assign(Vector<float>(3, 0.0f)) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values4);

    BOOST_CHECK(&v1_rng.assign(v2_rng) == &v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng.assign(v3_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng.assign( Vector<float>(2, 0.0f)), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    BOOST_CHECK_THROW(v1_rng.assign(Vector<int>(4, 0)), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values1);

    // ---------
    
    v2_rng += v2;

    checkVectorRange(v1_rng, v1, rng1, values1);
    checkVectorRange(v2_rng, v2, rng2, values3 + 1);

    swap(v1_rng, v2_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);
    checkVectorRange(v2_rng, v2, rng2, values1 + 1);

    swap(v1_rng, v2_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);
    checkVectorRange(v2_rng, v2, rng2, values3 + 1);

    swap(v2_rng, v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);
    checkVectorRange(v2_rng, v2, rng2, values1 + 1);

    swap(v2_rng, v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);
    checkVectorRange(v2_rng, v2, rng2, values3 + 1);

    v1_rng.swap(v2_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);
    checkVectorRange(v2_rng, v2, rng2, values1 + 1);

    v1_rng.swap(v2_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);
    checkVectorRange(v2_rng, v2, rng2, values3 + 1);

    v2_rng.swap(v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values3);
    checkVectorRange(v2_rng, v2, rng2, values1 + 1);

    v2_rng.swap(v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values1);
    checkVectorRange(v2_rng, v2, rng2, values3 + 1);

    // ---------

    v1_rng -= v1_rng;

    checkVectorRange(v1_rng, v1, rng1, values4);

    BOOST_CHECK_THROW(v1_rng.swap(v3_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values4);
    checkVectorRange(v3_rng, v3, rng3, values1);

    BOOST_CHECK_THROW(swap(v1_rng, v3_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values4);
    checkVectorRange(v3_rng, v3, rng3, values1);

    BOOST_CHECK_THROW(v3_rng.swap(v1_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values4);
    checkVectorRange(v3_rng, v3, rng3, values1);

    BOOST_CHECK_THROW(swap(v3_rng, v1_rng), Base::SizeError);

    checkVectorRange(v1_rng, v1, rng1, values4);
    checkVectorRange(v3_rng, v3, rng3, values1);

    // ---------

    v1_rng.swap(v1_rng);

    checkVectorRange(v1_rng, v1, rng1, values4);
    
    swap(v2_rng, v2_rng);

    checkVectorRange(v2_rng, v2, rng2, values3 + 1);
}

BOOST_AUTO_TEST_CASE(VectorSliceTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Vector<double>) == typeid(VectorSlice<Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>::ValueType) == typeid(VectorSlice<Vector<double> >::ValueType));
    BOOST_CHECK(typeid(Vector<double>::SizeType) == typeid(VectorSlice<Vector<double> >::SizeType));
    BOOST_CHECK(typeid(Vector<double>::DifferenceType) == typeid(VectorSlice<Vector<double> >::DifferenceType));
    BOOST_CHECK(typeid(Vector<double>::Reference) == typeid(VectorSlice<Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorSlice<Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorSlice<const Vector<double> >::Reference));
    BOOST_CHECK(typeid(Vector<double>::ConstReference) == typeid(VectorSlice<const Vector<double> >::ConstReference));
    BOOST_CHECK(typeid(const Vector<double>) == typeid(VectorSlice<const Vector<double> >::VectorType));
    BOOST_CHECK(typeid(Vector<double>) == typeid(VectorSlice<Vector<double> >::VectorType));

    BOOST_CHECK(typeid(Slice<Vector<double>::SizeType, Vector<double>::DifferenceType>) == typeid(VectorSlice<Vector<double> >::SliceType));
    BOOST_CHECK(typeid(Slice<Vector<double>::SizeType, Vector<double>::DifferenceType>) == typeid(VectorSlice<const Vector<double> >::SliceType));

    // ---------

    typedef Vector<double>::SizeType SizeType1;
    typedef VectorSlice<Vector<double> >::SliceType SliceType1;

    Vector<double> v0;
    SliceType1 slc0(1, 2, 3);
    VectorSlice<Vector<double> > v0_slc(v0, slc0);

    BOOST_CHECK(&v0_slc.getData().getData() == &v0);
    BOOST_CHECK(&const_cast<const VectorSlice<Vector<double> >&>(v0_slc).getData().getData() == &v0);

    // ---------

    BOOST_CHECK_THROW(v0_slc(0), Base::IndexError);
    BOOST_CHECK_THROW(v0_slc[0], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)(0), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)[0], Base::IndexError);

    v0.resize(1, 1.1);

    BOOST_CHECK_THROW(v0_slc(0), Base::IndexError);
    BOOST_CHECK_THROW(v0_slc[0], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)(0), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)[0], Base::IndexError);

    v0.resize(5, 2.2);

    BOOST_CHECK_THROW(v0_slc(2), Base::IndexError);
    BOOST_CHECK_THROW(v0_slc[2], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)(2), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)[2], Base::IndexError);

    BOOST_CHECK_NO_THROW(v0_slc(0));
    BOOST_CHECK_NO_THROW(v0_slc[0]);
    BOOST_CHECK_NO_THROW(v0_slc(1));
    BOOST_CHECK_NO_THROW(v0_slc[1]);

    BOOST_CHECK_NO_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)(0));
    BOOST_CHECK_NO_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)[0]);
    BOOST_CHECK_NO_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)(1));
    BOOST_CHECK_NO_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)[1]);

    v0.resize(6, 4.4);

    checkVectorSlice(v0_slc, v0, slc0, static_cast<double*>(0));

    v0.resize(1);

    BOOST_CHECK_THROW(v0_slc(0), Base::IndexError);
    BOOST_CHECK_THROW(v0_slc[0], Base::IndexError);

    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)(0), Base::IndexError);
    BOOST_CHECK_THROW(const_cast<const VectorSlice<Vector<double> >&>(v0_slc)[0], Base::IndexError);

    // ---------

    Vector<double> v1(5, 5.5);
    SliceType1 slc1(1, 1, 3);
    VectorSlice<Vector<double> > v1_slc(v1, slc1);
    
    v1(0) = 1.1;
    v1_slc[0] = 2.0;
    v1_slc.getData()[2] = -1.0;
    v1_slc(2) = 3.0;

    double values1[] = { 1.1, 2.0, -1.0, 3.0, 5.5 };

    checkVectorSlice(v1_slc, v1, slc1, values1);

    // ---------

    Vector<double> v2(v1_slc);
    SliceType1 slc2(2, -1, 3);
    VectorSlice<Vector<double> > v2_slc(v2, slc2);

    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    // ---------

    Vector<double> v3(v1);
    SliceType1 slc3(0, 1, 4);
    VectorSlice<Vector<double> > v3_slc(v3, slc3);
    VectorSlice<Vector<double> > v3_slc_tmp(v3_slc);

    checkVectorSlice(v3_slc, v3, slc3, values1);
    checkVectorSlice(v3_slc_tmp, v3, slc3, values1);

    // ---------

    Vector<double> v4(v1);
    SliceType1 slc4(2, 1, 0);
    VectorSlice<Vector<double> > v4_slc(v4, slc4);

    checkVectorSlice(v4_slc, v4, slc4, values1);

    // ---------

    Vector<double> v5(v1);
    SliceType1 slc5(1, 1, 4);
    VectorSlice<const Vector<double> > v5_slc(v5, slc5);

    checkVectorSlice(v5_slc, v5, slc5, values1);

    // ---------

    VectorSlice<VectorSlice<const Vector<double> > > v6_slc(v5_slc, slc3);

    checkVectorSlice(v6_slc, v5_slc, slc3, values1 + 1);

    BOOST_CHECK(&v6_slc.getData().getData().getData() == &v5);
    BOOST_CHECK(&const_cast<const VectorSlice<VectorSlice<const Vector<double> > >&>(v6_slc).getData().getData().getData() == &v5);

    // ---------

    BOOST_CHECK(&(v1_slc *= -2.0) == &v1_slc);

    double values2[] = { 1.1, 2.0 * -2.0, -1.0 * -2.0, 3.0 * -2.0, 5.5 };

    checkVectorSlice(v1_slc, v1, slc1, values2);

    // ---------

    BOOST_CHECK(&(v1_slc /= -2.0) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    // ---------

    BOOST_CHECK(&(v1_slc += v2) == &v1_slc);

    double values3[] = { 1.1, 2.0 + 2.0, -1.0 + -1.0, 3.0 + 3.0, 5.5 };

    checkVectorSlice(v1_slc, v1, slc1, values3);

    BOOST_CHECK_THROW(v1_slc += v1, Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    BOOST_CHECK_THROW(v1_slc += Vector<float>(), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    // ---------
    
    BOOST_CHECK(&(v1_slc -= v2) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    BOOST_CHECK_THROW(v1_slc -= v5_slc, Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    BOOST_CHECK_THROW(v1_slc -= Vector<int>(2), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    // ---------

    BOOST_CHECK(&(v1_slc += v1_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    // ---------
    
    double values4[] = { 1.1, 0.0, 0.0, 0.0, 5.5 };

    BOOST_CHECK(&(v1_slc -= v1_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);

    // ---------

    double values5[] = { 1.1, 3.0, -1.0, 2.0, 5.5 };

    BOOST_CHECK(&(v1_slc += v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    // ---------

    BOOST_CHECK(&(v1_slc -= v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);

    // ---------

    BOOST_CHECK(&v1_slc.plusAssign(v2) == &v1_slc);
    BOOST_CHECK(&v1_slc.plusAssign(v2) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    BOOST_CHECK_THROW(v1_slc.plusAssign(v1), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    BOOST_CHECK_THROW(v1_slc.plusAssign(Vector<float>()), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    // ---------
    
    BOOST_CHECK(&v1_slc.minusAssign(v2) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    BOOST_CHECK_THROW(v1_slc.minusAssign(v5_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    BOOST_CHECK_THROW(v1_slc.minusAssign(Vector<int>(2)), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    // ---------

    BOOST_CHECK(&v1_slc.plusAssign(v1_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values3);

    // ---------

    BOOST_CHECK(&v1_slc.minusAssign(v1_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);

    // ---------

    BOOST_CHECK(&v1_slc.plusAssign(v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    // ---------

    BOOST_CHECK(&v1_slc.minusAssign(v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);

    // ---------

    BOOST_CHECK(&(v1_slc = v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK(&(v1_slc = v1_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK(&(v1_slc = Vector<float>(3, 0.0f)) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);

    BOOST_CHECK(&(v1_slc = v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK_THROW((v1_slc = v3_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK_THROW((v1_slc = Vector<float>(2, 0.0f)), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK_THROW((v1_slc = Vector<int>(4, 0)), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    // ---------
    
    BOOST_CHECK(&(v1_slc = v2) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);

    BOOST_CHECK(&v1_slc.assign(v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK(&v1_slc.assign(v1_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK(&v1_slc.assign(Vector<float>(3, 0.0f)) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);

    BOOST_CHECK(&v1_slc.assign(v2_slc) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK_THROW(v1_slc.assign(v3_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK_THROW(v1_slc.assign( Vector<float>(2, 0.0f)), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    BOOST_CHECK_THROW(v1_slc.assign(Vector<int>(4, 0)), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values5);

    // ---------
    
    BOOST_CHECK(&v1_slc.assign(v2) == &v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);
    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    swap(v1_slc, v2_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);
    checkVectorSlice(v2_slc, v2, slc2, values5 + 1);

    swap(v1_slc, v2_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);
    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    swap(v2_slc, v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);
    checkVectorSlice(v2_slc, v2, slc2, values5 + 1);

    swap(v2_slc, v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);
    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    v1_slc.swap(v2_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);
    checkVectorSlice(v2_slc, v2, slc2, values5 + 1);

    v1_slc.swap(v2_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);
    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    v2_slc.swap(v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values5);
    checkVectorSlice(v2_slc, v2, slc2, values5 + 1);

    v2_slc.swap(v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values1);
    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    // ---------

    v1_slc -= v1_slc;

    checkVectorSlice(v1_slc, v1, slc1, values4);

    BOOST_CHECK_THROW(v1_slc.swap(v3_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values4);
    checkVectorSlice(v3_slc, v3, slc3, values1);

    BOOST_CHECK_THROW(swap(v1_slc, v3_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values4);
    checkVectorSlice(v3_slc, v3, slc3, values1);

    BOOST_CHECK_THROW(v3_slc.swap(v1_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values4);
    checkVectorSlice(v3_slc, v3, slc3, values1);

    BOOST_CHECK_THROW(swap(v3_slc, v1_slc), Base::SizeError);

    checkVectorSlice(v1_slc, v1, slc1, values4);
    checkVectorSlice(v3_slc, v3, slc3, values1);

    // ---------

    v1_slc.swap(v1_slc);

    checkVectorSlice(v1_slc, v1, slc1, values4);
    
    swap(v2_slc, v2_slc);

    checkVectorSlice(v2_slc, v2, slc2, values1 + 1);

    // ---------

    Vector<double> v8(10, 1.0);
    SliceType1 slc81(0, 1, 10);
    VectorSlice<const Vector<double> > v8_slc1(v8, slc81);

    for (SizeType1 i = 0; i < v8.getSize(); i++)
        v8(i) = i + 1;

    checkVectorSlice(v8_slc1, v8, slc81, static_cast<const double*>(0));

    SliceType1 slc82(9, -1, 10);
    VectorSlice<const Vector<double> > v8_slc2(v8, slc82);

    checkVectorSlice(v8_slc2, v8, slc82, static_cast<const double*>(0));

    SliceType1 slc83(6, -2, 3);
    VectorSlice<const Vector<double> > v8_slc3(v8, slc83);

    checkVectorSlice(v8_slc3, v8, slc83, static_cast<const double*>(0));

    SliceType1 slc84(2, 2, 3);
    VectorSlice<const Vector<double> > v8_slc4(v8, slc84);

    checkVectorSlice(v8_slc4, v8, slc84, static_cast<const double*>(0));

    SliceType1 slc85(1, 0, 20);
    VectorSlice<const Vector<double> > v8_slc5(v8, slc85);

    checkVectorSlice(v8_slc5, v8, slc85, static_cast<const double*>(0));
}

BOOST_AUTO_TEST_CASE(VectorRangeFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<double> v(10, 1.0);
    const Vector<double>& const_v_ref = v;

    for (Vector<double>::SizeType i = 0; i < v.getSize(); i++)
        v(i) = i + 1;

    typedef const VectorRange<Vector<double> > CVR;
    typedef const VectorRange<const Vector<double> > CCVR;
    typedef VectorRange<Vector<double> >::RangeType RangeType;

    // ---------

    BOOST_CHECK(&range(v, RangeType(0, 10)).getData().getData() == &v);

    checkVectorRange<CVR>(range(v, RangeType(0, 10)), v, RangeType(0, 10), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, RangeType(0, 5)), v, RangeType(0, 5), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, RangeType(0, 0)), v, RangeType(0, 0), &v.getData()[0]);

    checkVectorRange<CVR>(range(v, RangeType(1, 10)), v, RangeType(1, 10), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, RangeType(2, 5)), v, RangeType(2, 5), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, RangeType(3, 3)), v, RangeType(3, 3), &v.getData()[0]);

    checkVectorRange<CVR>(range(v, RangeType(10, 10)), v, RangeType(10, 10), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, RangeType(11, 11)), v, RangeType(11, 11), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(range(v, RangeType(5, 8))(2));
    BOOST_CHECK_THROW(range(v, RangeType(5, 8))(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(range(v, RangeType(5, 12))(4));
    BOOST_CHECK_THROW(range(v, RangeType(5, 12))(5), Base::IndexError);

    BOOST_CHECK_EQUAL(v(3), 4.0);

    range(v, RangeType(2, 5))(1) = -5.0;

    BOOST_CHECK_EQUAL(v(3), -5.0);

    v(3) = 4.0;

    // ---------

    BOOST_CHECK(&range(v, 0, 10).getData().getData() == &v);

    checkVectorRange<CVR>(range(v, 0, 10), v, RangeType(0, 10), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, 0, 5), v, RangeType(0, 5), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, 0, 0), v, RangeType(0, 0), &v.getData()[0]);

    checkVectorRange<CVR>(range(v, 1, 10), v, RangeType(1, 10), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, 2, 5), v, RangeType(2, 5), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, 3, 3), v, RangeType(3, 3), &v.getData()[0]);

    checkVectorRange<CVR>(range(v, 10, 10), v, RangeType(10, 10), &v.getData()[0]);
    checkVectorRange<CVR>(range(v, 11, 11), v, RangeType(11, 11), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(range(v, 5, 8)(2));
    BOOST_CHECK_THROW(range(v, 5, 8)(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(range(v, 5, 12)(4));
    BOOST_CHECK_THROW(range(v, 5, 12)(5), Base::IndexError);

    BOOST_CHECK_EQUAL(v(3), 4.0);

    range(v, 2, 5)(1) = -5.0;

    BOOST_CHECK_EQUAL(v(3), -5.0);

    v(3) = 4.0;

    // ---------

    BOOST_CHECK(&range(const_v_ref, RangeType(0, 10)).getData().getData() == &v);

    checkVectorRange<CCVR>(range(const_v_ref, RangeType(0, 10)), v, RangeType(0, 10), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, RangeType(0, 5)), v, RangeType(0, 5), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, RangeType(0, 0)), v, RangeType(0, 0), &v.getData()[0]);

    checkVectorRange<CCVR>(range(const_v_ref, RangeType(1, 10)), v, RangeType(1, 10), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, RangeType(2, 5)), v, RangeType(2, 5), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, RangeType(3, 3)), v, RangeType(3, 3), &v.getData()[0]);

    checkVectorRange<CCVR>(range(const_v_ref, RangeType(10, 10)), v, RangeType(10, 10), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, RangeType(11, 11)), v, RangeType(11, 11), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(range(const_v_ref, RangeType(5, 8))(2));
    BOOST_CHECK_THROW(range(const_v_ref, RangeType(5, 8))(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(range(const_v_ref, RangeType(5, 12))(4));
    BOOST_CHECK_THROW(range(const_v_ref, RangeType(5, 12))(5), Base::IndexError);

    // ---------

    BOOST_CHECK(&range(const_v_ref, 0, 10).getData().getData() == &v);

    checkVectorRange<CCVR>(range(const_v_ref, 0, 10), v, RangeType(0, 10), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, 0, 5), v, RangeType(0, 5), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, 0, 0), v, RangeType(0, 0), &v.getData()[0]);

    checkVectorRange<CCVR>(range(const_v_ref, 1, 10), v, RangeType(1, 10), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, 2, 5), v, RangeType(2, 5), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, 3, 3), v, RangeType(3, 3), &v.getData()[0]);

    checkVectorRange<CCVR>(range(const_v_ref, 10, 10), v, RangeType(10, 10), &v.getData()[0]);
    checkVectorRange<CCVR>(range(const_v_ref, 11, 11), v, RangeType(11, 11), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(range(const_v_ref, 5, 8)(2));
    BOOST_CHECK_THROW(range(const_v_ref, 5, 8)(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(range(const_v_ref, 5, 12)(4));
    BOOST_CHECK_THROW(range(const_v_ref, 5, 12)(5), Base::IndexError);
}

BOOST_AUTO_TEST_CASE(VectorSliceFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    Vector<double> v(10, 1.0);
    const Vector<double>& const_v_ref = v;

    for (Vector<double>::SizeType i = 0; i < v.getSize(); i++)
        v(i) = i + 1;

    typedef const VectorSlice<Vector<double> > CVS;
    typedef const VectorSlice<const Vector<double> > CCVS;
    typedef VectorSlice<Vector<double> >::SliceType SliceType;

    // ---------

    BOOST_CHECK(&slice(v, SliceType(0, 1, 10)).getData().getData() == &v);

    checkVectorSlice<CVS>(slice(v, SliceType(0, 1, 10)), v, SliceType(0, 1, 10), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(0, 2, 5)), v, SliceType(0, 2, 5), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(9, -2, 5)), v, SliceType(9, -2, 5), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(0, 1, 5)), v, SliceType(0, 1, 5), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(0, 1, 0)), v, SliceType(0, 1, 0), &v.getData()[0]);

    checkVectorSlice<CVS>(slice(v, SliceType(1, 1, 9)), v, SliceType(1, 1, 9), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(9, -1, 9)), v, SliceType(9, -1, 9), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(2, 1, 3)), v, SliceType(2, 1, 3), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(3, 1, 0)), v, SliceType(3, 1, 0), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(3, 0, 20)), v, SliceType(3, 0, 20), &v.getData()[0]);

    checkVectorSlice<CVS>(slice(v, SliceType(10, 0, 0)), v, SliceType(10, 0, 0), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, SliceType(11, 1, 0)), v, SliceType(11, 1, 0), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(slice(v, SliceType(5, 2, 3))(2));
    BOOST_CHECK_THROW(slice(v, SliceType(5, 2, 3))(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(slice(v, SliceType(5, 1, 7))(4));
    BOOST_CHECK_THROW(slice(v, SliceType(5, 1, 7))(5), Base::IndexError);

    BOOST_CHECK_EQUAL(v(4), 5.0);

    slice(v, SliceType(2, 2, 3))(1) = -6.0;

    BOOST_CHECK_EQUAL(v(4), -6.0);

    v(4) = 5.0;

    // ---------

    BOOST_CHECK(&slice(v, 0, 1, 10).getData().getData() == &v);

    checkVectorSlice<CVS>(slice(v, 0, 1, 10), v, SliceType(0, 1, 10), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 0, 2, 5), v, SliceType(0, 2, 5), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 9, -2, 5), v, SliceType(9, -2, 5), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 0, 1, 5), v, SliceType(0, 1, 5), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 0, 1, 0), v, SliceType(0, 1, 0), &v.getData()[0]);

    checkVectorSlice<CVS>(slice(v, 1, 1, 9), v, SliceType(1, 1, 9), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 9, -1, 9), v, SliceType(9, -1, 9), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 2, 1, 3), v, SliceType(2, 1, 3), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 3, 1, 0), v, SliceType(3, 1, 0), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 3, 0, 20), v, SliceType(3, 0, 20), &v.getData()[0]);

    checkVectorSlice<CVS>(slice(v, 10, 0, 0), v, SliceType(10, 0, 0), &v.getData()[0]);
    checkVectorSlice<CVS>(slice(v, 11, 1, 0), v, SliceType(11, 1, 0), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(slice(v, 5, 2, 3)(2));
    BOOST_CHECK_THROW(slice(v, 5, 2, 3)(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(slice(v, 5, 1, 7)(4));
    BOOST_CHECK_THROW(slice(v, 5, 1, 7)(5), Base::IndexError);

    BOOST_CHECK_EQUAL(v(1), 2.0);

    slice(v, SliceType(2, -1, 3))(1) = -6.0;

    BOOST_CHECK_EQUAL(v(1), -6.0);

    v(1) = 2.0;

    // ---------

    BOOST_CHECK(&slice(const_v_ref, SliceType(0, 1, 10)).getData().getData() == &v);

    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(0, 1, 10)), v, SliceType(0, 1, 10), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(0, 2, 5)), v, SliceType(0, 2, 5), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(9, -2, 5)), v, SliceType(9, -2, 5), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(0, 1, 5)), v, SliceType(0, 1, 5), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(0, 1, 0)), v, SliceType(0, 1, 0), &v.getData()[0]);

    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(1, 1, 9)), v, SliceType(1, 1, 9), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(9, -1, 9)), v, SliceType(9, -1, 9), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(2, 1, 3)), v, SliceType(2, 1, 3), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(2, 1, 3)), v, SliceType(2, 1, 3), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(3, 1, 0)), v, SliceType(3, 1, 0), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(3, 0, 20)), v, SliceType(3, 0, 20), &v.getData()[0]);

    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(10, 0, 0)), v, SliceType(10, 0, 0), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, SliceType(11, 1, 0)), v, SliceType(11, 1, 0), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(slice(const_v_ref, SliceType(5, 2, 3))(2));
    BOOST_CHECK_THROW(slice(const_v_ref, SliceType(5, 2, 3))(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(slice(const_v_ref, SliceType(5, 1, 7))(4));
    BOOST_CHECK_THROW(slice(const_v_ref, SliceType(5, 1, 7))(5), Base::IndexError);

    // ---------

    BOOST_CHECK(&slice(const_v_ref, 0, 1, 10).getData().getData() == &v);

    checkVectorSlice<CCVS>(slice(const_v_ref, 0, 1, 10), v, SliceType(0, 1, 10), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 0, 2, 5), v, SliceType(0, 2, 5), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 9, -2, 5), v, SliceType(9, -2, 5), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 0, 1, 5), v, SliceType(0, 1, 5), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 0, 1, 0), v, SliceType(0, 1, 0), &v.getData()[0]);

    checkVectorSlice<CCVS>(slice(const_v_ref, 1, 1, 9), v, SliceType(1, 1, 9), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 9, -1, 9), v, SliceType(9, -1, 9), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 2, 1, 3), v, SliceType(2, 1, 3), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 3, 1, 0), v, SliceType(3, 1, 0), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 3, 0, 20), v, SliceType(3, 0, 20), &v.getData()[0]);

    checkVectorSlice<CCVS>(slice(const_v_ref, 10, 0, 0), v, SliceType(10, 0, 0), &v.getData()[0]);
    checkVectorSlice<CCVS>(slice(const_v_ref, 11, 1, 0), v, SliceType(11, 1, 0), &v.getData()[0]);

    BOOST_CHECK_NO_THROW(slice(const_v_ref, 5, 2, 3)(2));
    BOOST_CHECK_THROW(slice(const_v_ref, 5, 2, 3)(3), Base::IndexError);
    BOOST_CHECK_NO_THROW(slice(const_v_ref, 5, 1, 7)(4));
    BOOST_CHECK_THROW(slice(const_v_ref, 5, 1, 7)(5), Base::IndexError);
}
