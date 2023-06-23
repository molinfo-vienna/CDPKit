/* 
 * MatrixAdapterTest.cpp 
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

#include "CDPL/Math/MatrixAdapter.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

    template <typename T>
    class TestTriangularAdapter 
    {

    public:
        typedef std::size_t SizeType;
        typedef const T ConstReference;

        class Data
        {

        public:
            Data(SizeType n): numCols(n) {}

            ConstReference operator()(SizeType i, SizeType j) const {
                return (i * numCols + j + 10);
            }

        private:
            SizeType numCols;
        };

        TestTriangularAdapter(SizeType n): one(1), zero(), data(n) {}
        
        const Data& getData() const {
            return data;
        }
                                                       
        const T one;
        const T zero;
        
    private:
        const Data data;
    };

    template <typename TM, typename M>
    void checkLowerTriangularMatrix(TM& tm, const M& m)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(tm.getSize1(), m.getSize1());
        BOOST_CHECK_EQUAL(tm.getSize2(), m.getSize2());
        BOOST_CHECK(tm.isEmpty() == m.isEmpty());

        BOOST_CHECK(&tm.getData().getData() == &m);
        BOOST_CHECK(&const_cast<const TM&>(tm).getData().getData() == &m);

        typedef typename M::SizeType SizeType;
        typedef typename M::ValueType ValueType;

        for (SizeType i = 0; i < m.getSize1() + 3; i++) {
            for (SizeType j = 0; j < m.getSize2() + 4; j++) {
                if (i >= j) {
                    if (i >= m.getSize1() || j >= m.getSize2()) { 
                        BOOST_CHECK_THROW(tm(i, j), Base::IndexError);
                    } else
                        BOOST_CHECK_EQUAL(tm(i, j), m(i, j));

                } else 
                    BOOST_CHECK_EQUAL(tm(i, j), ValueType());
            }
        }
    }

    template <typename TM, typename M>
    void checkUnitLowerTriangularMatrix(TM& tm, const M& m)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(tm.getSize1(), m.getSize1());
        BOOST_CHECK_EQUAL(tm.getSize2(), m.getSize2());
        BOOST_CHECK(tm.isEmpty() == m.isEmpty());

        BOOST_CHECK(&tm.getData().getData() == &m);
        BOOST_CHECK(&const_cast<const TM&>(tm).getData().getData() == &m);
        
        typedef typename M::SizeType SizeType;
        typedef typename M::ValueType ValueType;

        for (SizeType i = 0; i < m.getSize1() + 3; i++)  {
            for (SizeType j = 0; j < m.getSize2() + 4; j++) {
                if (i > j) {
                    if (i >= m.getSize1() || j >= m.getSize2()) { 
                        BOOST_CHECK_THROW(tm(i, j), Base::IndexError);
                    } else
                        BOOST_CHECK_EQUAL(tm(i, j), m(i, j));

                } else if (i == j) {
                    BOOST_CHECK_EQUAL(tm(i, j), ValueType(1));
                } else
                    BOOST_CHECK_EQUAL(tm(i, j), ValueType());
            }
        }
    }

    template <typename TM, typename M>
    void checkUpperTriangularMatrix(TM& tm, const M& m)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(tm.getSize1(), m.getSize1());
        BOOST_CHECK_EQUAL(tm.getSize2(), m.getSize2());
        BOOST_CHECK(tm.isEmpty() == m.isEmpty());

        BOOST_CHECK(&tm.getData().getData() == &m);
        BOOST_CHECK(&const_cast<const TM&>(tm).getData().getData() == &m);

        typedef typename M::SizeType SizeType;
        typedef typename M::ValueType ValueType;

        for (SizeType i = 0; i < m.getSize1() + 3; i++) {
            for (SizeType j = 0; j < m.getSize2() + 4; j++) {
                if (i <= j) {
                    if (i >= m.getSize1() || j >= m.getSize2()) { 
                        BOOST_CHECK_THROW(tm(i, j), Base::IndexError);
                    } else
                        BOOST_CHECK_EQUAL(tm(i, j), m(i, j));

                } else 
                    BOOST_CHECK_EQUAL(tm(i, j), ValueType());
            }
        }
    }

    template <typename TM, typename M>
    void checkUnitUpperTriangularMatrix(TM& tm, const M& m)
    {
        using namespace CDPL;

        BOOST_CHECK_EQUAL(tm.getSize1(), m.getSize1());
        BOOST_CHECK_EQUAL(tm.getSize2(), m.getSize2());
        BOOST_CHECK(tm.isEmpty() == m.isEmpty());

        BOOST_CHECK(&tm.getData().getData() == &m);
        BOOST_CHECK(&const_cast<const TM&>(tm).getData().getData() == &m);

        typedef typename M::SizeType SizeType;
        typedef typename M::ValueType ValueType;

        for (SizeType i = 0; i < m.getSize1() + 3; i++) {
            for (SizeType j = 0; j < m.getSize2() + 4; j++) {
                if (i < j) {
                    if (i >= m.getSize1() || j >= m.getSize2()) { 
                        BOOST_CHECK_THROW(tm(i, j), Base::IndexError);
                    } else
                        BOOST_CHECK_EQUAL(tm(i, j), m(i, j));

                } else if (i == j)
                    BOOST_CHECK_EQUAL(tm(i, j), ValueType(1));
                else
                    BOOST_CHECK_EQUAL(tm(i, j), ValueType());
            }
        }
    }
}


BOOST_AUTO_TEST_CASE(LowerTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef TestTriangularAdapter<double>::SizeType SizeType;
    TestTriangularAdapter<double> tad(100);
    
    BOOST_CHECK(tad.one != tad.zero);

    for (SizeType i = 0; i < 70; i++)
        for (SizeType j = 0; j < 70; j++) {
            BOOST_CHECK(tad.getData()(i, j) != tad.one);
            BOOST_CHECK(tad.getData()(i, j) != tad.zero);

            if (i >= j) 
                BOOST_CHECK_EQUAL(Lower::get(tad, i, j), tad.getData()(i, j));
            else
                BOOST_CHECK_EQUAL(Lower::get(tad, i, j), tad.zero);
        }
}

BOOST_AUTO_TEST_CASE(UnitLowerTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef TestTriangularAdapter<std::complex<float> >::SizeType SizeType;
    TestTriangularAdapter<std::complex<float> > tad(100);

    BOOST_CHECK(tad.one != tad.zero);

    for (SizeType i = 0; i < 70; i++)
        for (SizeType j = 0; j < 70; j++) {
            BOOST_CHECK(tad.getData()(i, j) != tad.one);
            BOOST_CHECK(tad.getData()(i, j) != tad.zero);

            if (i > j) 
                BOOST_CHECK_EQUAL(UnitLower::get(tad, i, j), tad.getData()(i, j));
            else if (i == j) 
                BOOST_CHECK_EQUAL(UnitLower::get(tad, i, j), tad.one);
            else
                BOOST_CHECK_EQUAL(UnitLower::get(tad, i, j), tad.zero);
        }
}

BOOST_AUTO_TEST_CASE(UpperTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef TestTriangularAdapter<unsigned int>::SizeType SizeType;
    TestTriangularAdapter<unsigned int> tad(100);
    
    BOOST_CHECK(tad.one != tad.zero);

    for (SizeType i = 0; i < 70; i++)
        for (SizeType j = 0; j < 70; j++) {
            BOOST_CHECK(tad.getData()(i, j) != tad.one);
            BOOST_CHECK(tad.getData()(i, j) != tad.zero);

            if (i <= j) 
                BOOST_CHECK_EQUAL(Upper::get(tad, i, j), tad.getData()(i, j));
            else
                BOOST_CHECK_EQUAL(Upper::get(tad, i, j), tad.zero);
        }
}

BOOST_AUTO_TEST_CASE(UnitUpperTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef TestTriangularAdapter<float>::SizeType SizeType;
    TestTriangularAdapter<float> tad(100);

    BOOST_CHECK(tad.one != tad.zero);

    for (SizeType i = 0; i < 70; i++)
        for (SizeType j = 0; j < 70; j++) {
            BOOST_CHECK(tad.getData()(i, j) != tad.one);
            BOOST_CHECK(tad.getData()(i, j) != tad.zero);

            if (i < j) 
                BOOST_CHECK_EQUAL(UnitUpper::get(tad, i, j), tad.getData()(i, j));
            else if (i == j) 
                BOOST_CHECK_EQUAL(UnitUpper::get(tad, i, j), tad.one);
            else
                BOOST_CHECK_EQUAL(UnitUpper::get(tad, i, j), tad.zero);
        }
}

BOOST_AUTO_TEST_CASE(TriangularAdapterTest)
{
    using namespace CDPL;
    using namespace Math;

    BOOST_CHECK(typeid(Matrix<double>) == typeid(TriangularAdapter<Matrix<double>, Lower>::MatrixType));
    BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(TriangularAdapter<Matrix<double>, Lower>::ValueType));
    BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(TriangularAdapter<Matrix<double>, Lower>::SizeType));
    BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(TriangularAdapter<Matrix<double>, Lower>::DifferenceType));
    BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(TriangularAdapter<Matrix<double>, Lower>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<Matrix<double>, Lower>::ConstReference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, Lower>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, Lower>::ConstReference));

    // ---------

    BOOST_CHECK(typeid(Matrix<double>) == typeid(TriangularAdapter<Matrix<double>, UnitLower>::MatrixType));
    BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(TriangularAdapter<Matrix<double>, UnitLower>::ValueType));
    BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(TriangularAdapter<Matrix<double>, UnitLower>::SizeType));
    BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(TriangularAdapter<Matrix<double>, UnitLower>::DifferenceType));
    BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(TriangularAdapter<Matrix<double>, UnitLower>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<Matrix<double>, UnitLower>::ConstReference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, UnitLower>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, UnitLower>::ConstReference));

    // ---------

    BOOST_CHECK(typeid(Matrix<double>) == typeid(TriangularAdapter<Matrix<double>, Upper>::MatrixType));
    BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(TriangularAdapter<Matrix<double>, Upper>::ValueType));
    BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(TriangularAdapter<Matrix<double>, Upper>::SizeType));
    BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(TriangularAdapter<Matrix<double>, Upper>::DifferenceType));
    BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(TriangularAdapter<Matrix<double>, Upper>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<Matrix<double>, Upper>::ConstReference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, Upper>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, Upper>::ConstReference));

    // ---------

    BOOST_CHECK(typeid(Matrix<double>) == typeid(TriangularAdapter<Matrix<double>, UnitUpper>::MatrixType));
    BOOST_CHECK(typeid(Matrix<double>::ValueType) == typeid(TriangularAdapter<Matrix<double>, UnitUpper>::ValueType));
    BOOST_CHECK(typeid(Matrix<double>::SizeType) == typeid(TriangularAdapter<Matrix<double>, UnitUpper>::SizeType));
    BOOST_CHECK(typeid(Matrix<double>::DifferenceType) == typeid(TriangularAdapter<Matrix<double>, UnitUpper>::DifferenceType));
    BOOST_CHECK(typeid(Matrix<double>::Reference) == typeid(TriangularAdapter<Matrix<double>, UnitUpper>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<Matrix<double>, UnitUpper>::ConstReference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, UnitUpper>::Reference));
    BOOST_CHECK(typeid(Matrix<double>::ConstReference) == typeid(TriangularAdapter<const Matrix<double>, UnitUpper>::ConstReference));

    // ---------

    typedef Matrix<double>::SizeType SizeType;

    Matrix<double> m1(10, 12);
                
    for (SizeType i = 0; i < m1.getSize1(); i++)
        for (SizeType j = 0; j < m1.getSize2(); j++)
            m1(i, j) = i * m1.getSize2() + j  + j / 10.0 + 10;

    TriangularAdapter<Matrix<double>, Lower> tm1(m1);
    TriangularAdapter<Matrix<double>, Lower> tm1c(tm1);

    checkLowerTriangularMatrix(tm1, m1);        
    checkLowerTriangularMatrix(tm1c, m1);    

    // ---------

    TriangularAdapter<Matrix<double>, UnitLower> tm2(m1);
    TriangularAdapter<Matrix<double>, UnitLower> tm2c(tm2);

    checkUnitLowerTriangularMatrix(tm2, m1);        
    checkUnitLowerTriangularMatrix(tm2c, m1);    

    // ---------

    TriangularAdapter<Matrix<double>, Upper> tm3(m1);
    TriangularAdapter<Matrix<double>, Upper> tm3c(tm3);

    checkUpperTriangularMatrix(tm3, m1);        
    checkUpperTriangularMatrix(tm3c, m1);    

    // ---------

    TriangularAdapter<Matrix<double>, UnitUpper> tm4(m1);
    TriangularAdapter<Matrix<double>, UnitUpper> tm4c(tm4);

    checkUnitUpperTriangularMatrix(tm4, m1);        
    checkUnitUpperTriangularMatrix(tm4c, m1);    

    // ---------

    m1.resize(10, 10, true);

    checkLowerTriangularMatrix(tm1, m1);        
    checkLowerTriangularMatrix(tm1c, m1);    

    checkUnitLowerTriangularMatrix(tm2, m1);        
    checkUnitLowerTriangularMatrix(tm2c, m1);    

    checkUpperTriangularMatrix(tm3, m1);        
    checkUpperTriangularMatrix(tm3c, m1);    

    checkUnitUpperTriangularMatrix(tm4, m1);        
    checkUnitUpperTriangularMatrix(tm4c, m1);    

    // ---------

    m1.resize(9, 8, true);

    checkLowerTriangularMatrix(tm1, m1);        
    checkLowerTriangularMatrix(tm1c, m1);    

    checkUnitLowerTriangularMatrix(tm2, m1);        
    checkUnitLowerTriangularMatrix(tm2c, m1);    

    checkUpperTriangularMatrix(tm3, m1);        
    checkUpperTriangularMatrix(tm3c, m1);    

    checkUnitUpperTriangularMatrix(tm4, m1);        
    checkUnitUpperTriangularMatrix(tm4c, m1);    
}

BOOST_AUTO_TEST_CASE(TriangFunctionTest)
{
    using namespace CDPL;
    using namespace Math;

    typedef Matrix<float>::SizeType SizeType;

    Matrix<float> m1(10, 12);
    const Matrix<float>& m1_cref = m1;
                
    for (SizeType i = 0; i < m1.getSize1(); i++)
        for (SizeType j = 0; j < m1.getSize2(); j++)
            m1(i, j) = i * m1.getSize2() + j  + j / 10.0f + 10;

    // ---------

    checkLowerTriangularMatrix<const TriangularAdapter<Matrix<float>, Lower> >(triang<Lower>(m1), m1);        
    checkLowerTriangularMatrix<const TriangularAdapter<const Matrix<float>, Lower> >(triang<Lower>(m1_cref), m1);        

    // ---------

    checkUnitLowerTriangularMatrix<const TriangularAdapter<Matrix<float>, UnitLower> >(triang<UnitLower>(m1), m1);        
    checkUnitLowerTriangularMatrix<const TriangularAdapter<const Matrix<float>, UnitLower> >(triang<UnitLower>(m1_cref), m1);        

    // ---------

    checkUpperTriangularMatrix<const TriangularAdapter<Matrix<float>, Upper> >(triang<Upper>(m1), m1);        
    checkUpperTriangularMatrix<const TriangularAdapter<const Matrix<float>, Upper> >(triang<Upper>(m1_cref), m1);        

    // ---------

    checkUnitUpperTriangularMatrix<const TriangularAdapter<Matrix<float>, UnitUpper> >(triang<UnitUpper>(m1), m1);        
    checkUnitUpperTriangularMatrix<const TriangularAdapter<const Matrix<float>, UnitUpper> >(triang<UnitUpper>(m1_cref), m1);        
}
