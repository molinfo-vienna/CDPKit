/* 
 * QuaternionFunctionExport.cpp 
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


#include <utility>

#include <boost/python.hpp>

#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Math/QuaternionExpression.hpp"

#include "QuaternionExpression.hpp"
#include "QuaternionExpressionAdapter.hpp"
#include "FunctionExports.hpp"


namespace
{

    template <typename T>
    CDPL::Math::RealQuaternion<T> makeQuat1(const T& t) 
    {
        return CDPL::Math::RealQuaternion<T>(t);
    }

    template <typename T>
    CDPL::Math::Quaternion<T> makeQuat2(const T& t1, const T& t2) 
    {
        return CDPL::Math::Quaternion<T>(t1, t2);
    }

    template <typename T>
    CDPL::Math::Quaternion<T> makeQuat3(const T& t1, const T& t2, const T& t3) 
    {
        return CDPL::Math::Quaternion<T>(t1, t2, t3);
    }

    template <typename T>
    CDPL::Math::Quaternion<T> makeQuat4(const T& t1, const T& t2, const T& t3, const T& t4) 
    {
        return CDPL::Math::Quaternion<T>(t1, t2, t3, t4);
    }

    template <typename T>
    bool equals(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e1,
                const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e2,
                const T& eps)
    {
        return CDPL::Math::equals(*e1, *e2, eps);
    }

    template <typename T>
    typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer
    elemDiv(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e1,
            const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e2)
    {
        using namespace CDPLPythonMath;

        typedef typename ConstQuaternionExpression<T>::SharedPointer ExpressionPointer;

        return ExpressionPointer(makeConstQuaternionExpressionAdapter(CDPL::Math::elemDiv(*e1, *e2),
                                                                      std::make_pair(e1, e2)));
    }

    template <typename T>
    typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer
    elemProd(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e1,
             const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e2)
    {
        using namespace CDPLPythonMath;

        typedef typename ConstQuaternionExpression<T>::SharedPointer ExpressionPointer;

        return ExpressionPointer(makeConstQuaternionExpressionAdapter(CDPL::Math::elemProd(*e1, *e2),
                                                                      std::make_pair(e1, e2)));
    }

    template <typename T>
    T real(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        return CDPL::Math::real(*e);
    }

    template <typename T>
    typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer
    unreal(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        using namespace CDPLPythonMath;

        typedef typename ConstQuaternionExpression<T>::SharedPointer ExpressionPointer;

        return ExpressionPointer(makeConstQuaternionExpressionAdapter(CDPL::Math::unreal(*e), e));
    }

    template <typename T>
    typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer
    conj(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        using namespace CDPLPythonMath;

        typedef typename ConstQuaternionExpression<T>::SharedPointer ExpressionPointer;

        return ExpressionPointer(makeConstQuaternionExpressionAdapter(CDPL::Math::conj(*e), e));
    }

    template <typename T>
    typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer
    inv(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        using namespace CDPLPythonMath;

        typedef typename ConstQuaternionExpression<T>::SharedPointer ExpressionPointer;

        return ExpressionPointer(makeConstQuaternionExpressionAdapter(CDPL::Math::inv(*e), e));
    }

    template <typename T>
    T norm(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        return CDPL::Math::norm(*e);
    }

    template <typename T>
    T norm2(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        return CDPL::Math::norm2(*e);
    }

    template <typename T>
    T sum(const typename CDPLPythonMath::ConstQuaternionExpression<T>::SharedPointer& e)
    {
        return CDPL::Math::sum(*e);
    }
}


void CDPLPythonMath::exportQuaternionFunctions()
{
    using namespace boost;

    python::def("quat", &makeQuat1<float>, python::arg("t"));
    python::def("quat", &makeQuat1<double>, python::arg("t"));
    python::def("quat", &makeQuat1<long>, python::arg("t"));
    python::def("quat", &makeQuat1<unsigned long>, python::arg("t"));

    python::def("quat", &makeQuat2<float>, (python::arg("t1"), python::arg("t2")));
    python::def("quat", &makeQuat2<double>, (python::arg("t1"), python::arg("t2")));
    python::def("quat", &makeQuat2<long>, (python::arg("t1"), python::arg("t2")));
    python::def("quat", &makeQuat2<unsigned long>, (python::arg("t1"), python::arg("t2")));

    python::def("quat", &makeQuat3<float>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));
    python::def("quat", &makeQuat3<double>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));
    python::def("quat", &makeQuat3<long>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));
    python::def("quat", &makeQuat3<unsigned long>, (python::arg("t1"), python::arg("t2"), python::arg("t3")));

    python::def("quat", &makeQuat4<float>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));
    python::def("quat", &makeQuat4<double>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));
    python::def("quat", &makeQuat4<long>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));
    python::def("quat", &makeQuat4<unsigned long>, (python::arg("t1"), python::arg("t2"), python::arg("t3"), python::arg("t4")));

    python::def("equals", &equals<float>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
    python::def("equals", &equals<double>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
    python::def("equals", &equals<long>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));
    python::def("equals", &equals<unsigned long>, (python::arg("e1"), python::arg("e2"), python::arg("eps")));

    python::def("elemDiv", &elemDiv<float>, (python::arg("e1"), python::arg("e2")));
    python::def("elemDiv", &elemDiv<double>, (python::arg("e1"), python::arg("e2")));
    python::def("elemDiv", &elemDiv<long>, (python::arg("e1"), python::arg("e2")));
    python::def("elemDiv", &elemDiv<unsigned long>, (python::arg("e1"), python::arg("e2")));

    python::def("elemProd", &elemProd<float>, (python::arg("e1"), python::arg("e2")));
    python::def("elemProd", &elemProd<double>, (python::arg("e1"), python::arg("e2")));
    python::def("elemProd", &elemProd<long>, (python::arg("e1"), python::arg("e2")));
    python::def("elemProd", &elemProd<unsigned long>, (python::arg("e1"), python::arg("e2")));

    python::def("real", &real<float>, python::arg("e"));
    python::def("real", &real<double>, python::arg("e"));
    python::def("real", &real<long>, python::arg("e"));
    python::def("real", &real<unsigned long>, python::arg("e"));

    python::def("unreal", &unreal<float>, python::arg("e"));
    python::def("unreal", &unreal<double>, python::arg("e"));
    python::def("unreal", &unreal<long>, python::arg("e"));
    python::def("unreal", &unreal<unsigned long>, python::arg("e"));

    python::def("conj", &conj<float>, python::arg("e"));
    python::def("conj", &conj<double>, python::arg("e"));
    python::def("conj", &conj<long>, python::arg("e"));
    python::def("conj", &conj<unsigned long>, python::arg("e"));

    python::def("inv", &inv<float>, python::arg("e"));
    python::def("inv", &inv<double>, python::arg("e"));
    python::def("inv", &inv<long>, python::arg("e"));
    python::def("inv", &inv<unsigned long>, python::arg("e"));

    python::def("norm", &norm<float>, python::arg("e"));
    python::def("norm", &norm<double>, python::arg("e"));
    python::def("norm", &norm<long>, python::arg("e"));
    python::def("norm", &norm<unsigned long>, python::arg("e"));

    python::def("norm2", &norm2<float>, python::arg("e"));
    python::def("norm2", &norm2<double>, python::arg("e"));
    python::def("norm2", &norm2<long>, python::arg("e"));
    python::def("norm2", &norm2<unsigned long>, python::arg("e"));

    python::def("sum", &sum<float>, python::arg("e"));
    python::def("sum", &sum<double>, python::arg("e"));
    python::def("sum", &sum<long>, python::arg("e"));
    python::def("sum", &sum<unsigned long>, python::arg("e"));
}
