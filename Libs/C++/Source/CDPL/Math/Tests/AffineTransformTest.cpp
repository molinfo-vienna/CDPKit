/* 
 * AffineTransformTest.cpp 
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


#include <cmath>

#include <boost/test/auto_unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    template <typename M,typename T, std::size_t N>
    void checkRotationMatrix(typename M::SizeType size, M& mtx, T values[N][N])
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(mtx.getSize1(), size);
        BOOST_CHECK_EQUAL(mtx.getSize2(), size);
        BOOST_CHECK(!mtx.isEmpty());

        typedef typename M::ValueType ValueType;

        const ValueType near_zero = ValueType(0.0000000000001);

        for (typename M::SizeType i = 0; i < size; i++) {
            for (typename M::SizeType j = 0; j < size; j++) {
                ValueType v;

                if (i >= N || j >= N)
                    v = (i == j ? ValueType(1) : ValueType());
                else 
                    v = values[i][j];
                
                if (v >= ValueType() && v <= near_zero)
                    BOOST_CHECK_SMALL(mtx(i, j), near_zero);
                else
                    BOOST_CHECK_CLOSE(mtx(i, j), v, 0.000001);
            }
        }

        BOOST_CHECK_THROW(mtx(size, 0), Base::IndexError);
        BOOST_CHECK_THROW(mtx(0, size), Base::IndexError);
        BOOST_CHECK_THROW(mtx(size, size), Base::IndexError);
    }

    template <typename M>
    void checkScalingMatrix(typename M::SizeType size, M& mtx, 
                            const typename M::ValueType& sx, const typename M::ValueType& sy, 
                            const typename M::ValueType& sz)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(mtx.getSize1(), size);
        BOOST_CHECK_EQUAL(mtx.getSize2(), size);
        BOOST_CHECK(!mtx.isEmpty());

        typedef typename M::ValueType ValueType;

        for (typename M::SizeType i = 0; i < size; i++) {
            for (typename M::SizeType j = 0; j < size; j++) {
                if (i == j) {
                    ValueType v(1);

                    if (i < size && i < 3) {
                        switch (i) {
                    
                        case 0:
                            v = sx;
                            break;

                        case 1:
                            v = sy;
                            break;

                        case 2:
                            v = sz;

                        default:
                            break;
                        }
                    }

                    BOOST_CHECK_EQUAL(mtx(i, j), v);
                
                } else {
                    BOOST_CHECK_EQUAL(mtx(i, j), ValueType());
                }
            }
        }

        BOOST_CHECK_THROW(mtx(size, 0), Base::IndexError);
        BOOST_CHECK_THROW(mtx(0, size), Base::IndexError);
        BOOST_CHECK_THROW(mtx(size, size), Base::IndexError);
    }

    template <typename M>
    void checkTranslationMatrix(typename M::SizeType size, M& mtx, 
                                const typename M::ValueType& tx, const typename M::ValueType& ty, 
                                const typename M::ValueType& tz)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(mtx.getSize1(), size);
        BOOST_CHECK_EQUAL(mtx.getSize2(), size);
        BOOST_CHECK(!mtx.isEmpty());

        typedef typename M::ValueType ValueType;

        for (typename M::SizeType i = 0; i < size; i++) {
            for (typename M::SizeType j = 0; j < size; j++) {
                if (i == j) {
                    BOOST_CHECK_EQUAL(mtx(i, j), ValueType(1));

                } else if (j == size - 1 && i < size && i < 3) {
                    ValueType v = ValueType();

                    switch (i) {
                    
                    case 0:
                        v = tx;
                        break;

                    case 1:
                        v = ty;
                        break;

                    case 2:
                        v = tz;

                    default:
                        break;
                    }

                    BOOST_CHECK_EQUAL(mtx(i, j), v);
                
                }  else {
                    BOOST_CHECK_EQUAL(mtx(i, j), ValueType());
                }
            }
        }

        BOOST_CHECK_THROW(mtx(size, 0), Base::IndexError);
        BOOST_CHECK_THROW(mtx(0, size), Base::IndexError);
        BOOST_CHECK_THROW(mtx(size, size), Base::IndexError);
    }

    template <typename M>
    void checkEmpty(M& mtx)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(mtx.getSize1(), 0);
        BOOST_CHECK_EQUAL(mtx.getSize2(), 0);
        BOOST_CHECK(mtx.isEmpty());

        BOOST_CHECK_THROW(mtx(0, 0), Base::IndexError);
        BOOST_CHECK_THROW(mtx(1, 0), Base::IndexError);
        BOOST_CHECK_THROW(mtx(0, 2), Base::IndexError);
        BOOST_CHECK_THROW(mtx(3, 3), Base::IndexError);
    }
}


BOOST_AUTO_TEST_CASE(RotationMatrixTest)
{
    using namespace CDPL;
    using namespace Math;

    RotationMatrix<double> m1(0, 0, 0, 0, 0);

    checkEmpty(m1);

    BOOST_CHECK_EQUAL(m1.getMaxSize1(), std::numeric_limits<RotationMatrix<double>::SizeType>::max());
    BOOST_CHECK_EQUAL(m1.getMaxSize2(), std::numeric_limits<RotationMatrix<double>::SizeType>::max());

    // ---------

    const double deg_97 = 97.0 * M_PI / 180.0;

    double rot_x_97_data[3][3] = { 
        { 1.0, 0.0, 0.0 },
        { 0.0, std::cos(deg_97), -std::sin(deg_97) },
        { 0.0, std::sin(deg_97), std::cos(deg_97) }
    };

    RotationMatrix<double> m2(3, deg_97, 1.0, 0.0, 0.0);

    checkRotationMatrix(3, m2, rot_x_97_data);

    // ---------

    const double deg_295 = 295.0 * M_PI / 180.0;

    double rot_y_295_data[3][3] = { 
        { std::cos(deg_295), 0.0, std::sin(deg_295) },
        { 0.0, 1.0, 0.0 },
        { -std::sin(deg_295), 0.0, std::cos(deg_295) }
    };

    RotationMatrix<double> m3(4, deg_295 - 2.0 * M_PI, 0.0, 1.0, 0.0);

    checkRotationMatrix(4, m3, rot_y_295_data);

    // ---------

    const double deg_m130 = -130.0 * M_PI / 180.0;

    double rot_z_m130_data[3][3] = { 
        { std::cos(deg_m130), -std::sin(deg_m130), 0.0 },
        { std::sin(deg_m130), std::cos(deg_m130), 0.0 },
        { 0.0, 0.0, 1.0 }
    };

    RotationMatrix<double> m4(5, deg_m130 + 2.0 * M_PI, 0.0, 0.0, 1.0);

    checkRotationMatrix(5, m4, rot_z_m130_data);

    // ---------

    RotationMatrix<double> m5(m2);

    checkRotationMatrix(3, m5, rot_x_97_data);
    checkRotationMatrix(3, m2, rot_x_97_data);

    // ---------

    RotationMatrix<double> m6(8, Quaternion<double>(std::cos(deg_97 * 0.5), std::sin(deg_97 * 0.5), 0.0, 0.0));

    checkRotationMatrix(8, m6, rot_x_97_data);

    // ---------

    RotationMatrix<double> m7(3, Quaternion<double>(std::cos(deg_295 * 0.5), 0.0, std::sin(deg_295 * 0.5), 0.0));

    checkRotationMatrix(3, m7, rot_y_295_data);

    // ---------

    RotationMatrix<double> m8(2, Quaternion<double>(std::cos(deg_m130 * 0.5), 0.0, 0.0, std::sin(deg_m130 * 0.5)));

    checkRotationMatrix(2, m8, rot_z_m130_data);

    // ---------

    m1 = m1;

    checkEmpty(m1);

    m1 = m5;

    checkRotationMatrix(3, m1, rot_x_97_data);
    checkRotationMatrix(3, m5, rot_x_97_data);

    m1 = m1;

    checkRotationMatrix(3, m1, rot_x_97_data);

    // ---------

    m1.resize(0);

    checkEmpty(m1);

    m1.resize(1);

    checkRotationMatrix(1, m1, rot_x_97_data);

    m1.resize(2);

    checkRotationMatrix(2, m1, rot_x_97_data);

    m1.resize(3);

    checkRotationMatrix(3, m1, rot_x_97_data);

    m1.resize(4);

    checkRotationMatrix(4, m1, rot_x_97_data);

    m1.resize(5);

    checkRotationMatrix(5, m1, rot_x_97_data);

    m8.resize(4);

    checkRotationMatrix(4, m8, rot_z_m130_data);

    // ---------

    double identity_data[1][1] = { { 1.0 } };

    m1.set(deg_295, 0.0, 1.0, 0.0);

    checkRotationMatrix(5, m1, rot_y_295_data);

    m1.resize(0);

    checkEmpty(m1);

    m1.set(0.0, 1.0, 0.0, 0.0);

    checkEmpty(m1);

    m1.resize(12);

    checkRotationMatrix(12, m1, identity_data);

    m1.set(deg_97, 1.0, 0.0, 0.0);

    checkRotationMatrix(12, m1, rot_x_97_data);

    m1.set(Quaternion<double>(std::cos(deg_m130 * 0.5), 0.0, 0.0, std::sin(deg_m130 * 0.5)));

    checkRotationMatrix(12, m1, rot_z_m130_data);

    m1.resize(0);

    checkEmpty(m1);

    m1.resize(1);

    checkRotationMatrix(1, m1, rot_z_m130_data);

    // ---------

    m5.resize(0);
    m1.resize(4);

    checkEmpty(m5);

    m1.swap(m5);

    checkRotationMatrix(4, m5, rot_z_m130_data);
    checkEmpty(m1);

    m1.swap(m5);

    checkRotationMatrix(4, m1, rot_z_m130_data);
    checkEmpty(m5);

    m5.swap(m1);

    checkRotationMatrix(4, m5, rot_z_m130_data);
    checkEmpty(m1);

    m5.swap(m1);

    checkRotationMatrix(4, m1, rot_z_m130_data);
    checkEmpty(m5);

    swap(m1, m5);

    checkRotationMatrix(4, m5, rot_z_m130_data);
    checkEmpty(m1);

    swap(m1, m5);

    checkRotationMatrix(4, m1, rot_z_m130_data);
    checkEmpty(m5);

    swap(m5, m1);

    checkRotationMatrix(4, m5, rot_z_m130_data);
    checkEmpty(m1);

    swap(m5, m1);

    checkRotationMatrix(4, m1, rot_z_m130_data);
    checkEmpty(m5);

    // --

    m5.resize(6);

    m1.swap(m5);

    checkRotationMatrix(6, m1, rot_x_97_data);
    checkRotationMatrix(4, m5, rot_z_m130_data);

    m1.swap(m5);

    checkRotationMatrix(6, m5, rot_x_97_data);
    checkRotationMatrix(4, m1, rot_z_m130_data);

    m5.swap(m1);

    checkRotationMatrix(6, m1, rot_x_97_data);
    checkRotationMatrix(4, m5, rot_z_m130_data);

    m5.swap(m1);

    checkRotationMatrix(6, m5, rot_x_97_data);
    checkRotationMatrix(4, m1, rot_z_m130_data);

    swap(m1, m5);

    checkRotationMatrix(6, m1, rot_x_97_data);
    checkRotationMatrix(4, m5, rot_z_m130_data);

    swap(m1, m5);

    checkRotationMatrix(6, m5, rot_x_97_data);
    checkRotationMatrix(4, m1, rot_z_m130_data);

    swap(m5, m1);

    checkRotationMatrix(6, m1, rot_x_97_data);
    checkRotationMatrix(4, m5, rot_z_m130_data);

    swap(m5, m1);

    checkRotationMatrix(6, m5, rot_x_97_data);
    checkRotationMatrix(4, m1, rot_z_m130_data);

    // --

    m1.swap(m1);

    checkRotationMatrix(4, m1, rot_z_m130_data);

    swap(m1, m1);

    checkRotationMatrix(4, m1, rot_z_m130_data);
}

BOOST_AUTO_TEST_CASE(ScalingMatrixTest)
{
    using namespace CDPL;
    using namespace Math;

    ScalingMatrix<double> m1(0);

    checkEmpty(m1);

    BOOST_CHECK_EQUAL(m1.getMaxSize1(), std::numeric_limits<ScalingMatrix<double>::SizeType>::max());
    BOOST_CHECK_EQUAL(m1.getMaxSize2(), std::numeric_limits<ScalingMatrix<double>::SizeType>::max());

    // ---------

    ScalingMatrix<double> m2(3);

    checkScalingMatrix(3, m2, 1.0, 1.0, 1.0);

    // ---------

    ScalingMatrix<double> m3(4, 1.3);

    checkScalingMatrix(4, m3, 1.3, 1.0, 1.0);

    // ---------

    ScalingMatrix<double> m4(5, 1.3, -2.3);

    checkScalingMatrix(5, m4, 1.3, -2.3, 1.0);

    // ---------

    ScalingMatrix<double> m5(5, 1.3, -2.3, 7.7);

    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    // ---------

    ScalingMatrix<double> m6(m5);

    checkScalingMatrix(5, m6, 1.3, -2.3, 7.7);
    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    // ---------

    ScalingMatrix<double> m7(2, 1.3, 0.0, 7.7);

    checkScalingMatrix(2, m7, 1.3, 0.0, 7.7);

    // ---------

    ScalingMatrix<double> m8(m1);

    checkEmpty(m8);
    checkEmpty(m1);

    // ---------

    m1 = m1;

    checkEmpty(m1);

    m1 = m5;

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);
    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    m1 = m1;

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    // ---------

    m1.resize(0);

    checkEmpty(m1);

    m1.resize(1);

    checkScalingMatrix(1, m1, 1.3, -2.3, 7.7);

    m1.resize(2);

    checkScalingMatrix(2, m1, 1.3, -2.3, 7.7);

    m1.resize(3);

    checkScalingMatrix(3, m1, 1.3, -2.3, 7.7);

    m1.resize(4);

    checkScalingMatrix(4, m1, 1.3, -2.3, 7.7);

    m1.resize(5);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    m8.resize(4);

    checkScalingMatrix(4, m8, 1.0, 1.0, 1.0);

    // ---------

    m1.set();

    checkScalingMatrix(5, m1, 1.0, 1.0, 1.0);

    m1.set(-2.11);

    checkScalingMatrix(5, m1, -2.11, 1.0, 1.0);

    m1.set(-2.10, 1.001);

    checkScalingMatrix(5, m1, -2.10, 1.001, 1.0);

    m1.set(2.11, -1.1, 0.3);

    checkScalingMatrix(5, m1, 2.11, -1.1, 0.3);

    m1.resize(0);
    m1.set(-2.11, -1.1, -0.3);
    m1.resize(3);

    checkScalingMatrix(3, m1, -2.11, -1.1, -0.3);
    
    m1.resize(2);
    m1.set(1.3, -2.3, 7.7);

    checkScalingMatrix(2, m1, 1.3, -2.3, 0.0);

    m1.resize(5);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    // ---------

    m5.resize(0);

    checkEmpty(m5);

    m1.swap(m5);

    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    m1.swap(m5);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    m5.swap(m1);

    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    m5.swap(m1);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    swap(m1, m5);

    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    swap(m1, m5);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    swap(m5, m1);

    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    swap(m5, m1);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    // --

    m5.set(1.1, 2.2, 3.3);
    m5.resize(6);

    checkScalingMatrix(6, m5, 1.1, 2.2, 3.3);

    m1.swap(m5);

    checkScalingMatrix(6, m1, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    m1.swap(m5);

    checkScalingMatrix(6, m5, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    m5.swap(m1);

    checkScalingMatrix(6, m1, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    m5.swap(m1);

    checkScalingMatrix(6, m5, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    swap(m1, m5);

    checkScalingMatrix(6, m1, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    swap(m1, m5);

    checkScalingMatrix(6, m5, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    swap(m5, m1);

    checkScalingMatrix(6, m1, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m5, 1.3, -2.3, 7.7);

    swap(m5, m1);

    checkScalingMatrix(6, m5, 1.1, 2.2, 3.3);
    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    // --

    m1.swap(m1);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);

    swap(m1, m1);

    checkScalingMatrix(5, m1, 1.3, -2.3, 7.7);
}

BOOST_AUTO_TEST_CASE(TranslationMatrixTest)
{
    using namespace CDPL;
    using namespace Math;

    TranslationMatrix<double> m1(0);

    checkEmpty(m1);

    BOOST_CHECK_EQUAL(m1.getMaxSize1(), std::numeric_limits<TranslationMatrix<double>::SizeType>::max());
    BOOST_CHECK_EQUAL(m1.getMaxSize2(), std::numeric_limits<TranslationMatrix<double>::SizeType>::max());

    // ---------

    TranslationMatrix<double> m2(3);

    checkTranslationMatrix(3, m2, 0.0, 0.0, 0.0);

    // ---------

    TranslationMatrix<double> m3(4, 1.3);

    checkTranslationMatrix(4, m3, 1.3, 0.0, 0.0);

    // ---------

    TranslationMatrix<double> m4(5, 1.3, -2.3);

    checkTranslationMatrix(5, m4, 1.3, -2.3, 0.0);

    // ---------

    TranslationMatrix<double> m5(5, 1.3, -2.3, 7.7);

    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    // ---------

    TranslationMatrix<double> m6(m5);

    checkTranslationMatrix(5, m6, 1.3, -2.3, 7.7);
    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    // ---------

    TranslationMatrix<double> m7(2, 1.3, 0.0, 7.7);

    checkTranslationMatrix(2, m7, 1.3, 0.0, 7.7);

    // ---------

    TranslationMatrix<double> m8(m1);

    checkEmpty(m8);
    checkEmpty(m1);

    // ---------

    m1 = m1;

    checkEmpty(m1);

    m1 = m5;

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);
    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    m1 = m1;

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    // ---------

    m1.resize(0);

    checkEmpty(m1);

    m1.resize(1);

    checkTranslationMatrix(1, m1, 1.3, -2.3, 7.7);

    m1.resize(2);

    checkTranslationMatrix(2, m1, 1.3, -2.3, 7.7);

    m1.resize(3);

    checkTranslationMatrix(3, m1, 1.3, -2.3, 7.7);

    m1.resize(4);

    checkTranslationMatrix(4, m1, 1.3, -2.3, 7.7);

    m1.resize(5);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    m8.resize(4);

    checkTranslationMatrix(4, m8, 0.0, 0.0, 0.0);

    // ---------

    m1.set();

    checkTranslationMatrix(5, m1, 0.0, 0.0, 0.0);

    m1.set(-2.11);

    checkTranslationMatrix(5, m1, -2.11, 0.0, 0.0);

    m1.set(-2.10, 1.001);

    checkTranslationMatrix(5, m1, -2.10, 1.001, 0.0);

    m1.set(2.11, -1.1, 0.3);

    checkTranslationMatrix(5, m1, 2.11, -1.1, 0.3);

    m1.resize(0);
    m1.set(-2.11, -1.1, -0.3);
    m1.resize(3);

    checkTranslationMatrix(3, m1, -2.11, -1.1, -0.3);
    
    m1.resize(2);
    m1.set(1.3, -2.3, 7.7);

    checkTranslationMatrix(2, m1, 1.3, -2.3, 0.0);

    m1.resize(5);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    // ---------

    m5.resize(0);

    checkEmpty(m5);

    m1.swap(m5);

    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    m1.swap(m5);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    m5.swap(m1);

    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    m5.swap(m1);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    swap(m1, m5);

    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    swap(m1, m5);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    swap(m5, m1);

    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);
    checkEmpty(m1);

    swap(m5, m1);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);
    checkEmpty(m5);

    // --

    m5.set(1.1, 2.2, 3.3);
    m5.resize(6);

    checkTranslationMatrix(6, m5, 1.1, 2.2, 3.3);

    m1.swap(m5);

    checkTranslationMatrix(6, m1, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    m1.swap(m5);

    checkTranslationMatrix(6, m5, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    m5.swap(m1);

    checkTranslationMatrix(6, m1, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    m5.swap(m1);

    checkTranslationMatrix(6, m5, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    swap(m1, m5);

    checkTranslationMatrix(6, m1, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    swap(m1, m5);

    checkTranslationMatrix(6, m5, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    swap(m5, m1);

    checkTranslationMatrix(6, m1, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m5, 1.3, -2.3, 7.7);

    swap(m5, m1);

    checkTranslationMatrix(6, m5, 1.1, 2.2, 3.3);
    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    // --

    m1.swap(m1);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);

    swap(m1, m1);

    checkTranslationMatrix(5, m1, 1.3, -2.3, 7.7);
}
