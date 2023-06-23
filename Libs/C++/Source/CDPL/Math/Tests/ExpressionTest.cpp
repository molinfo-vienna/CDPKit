/* 
 * ExpressionTest.cpp 
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

#include "CDPL/Math/Expression.hpp"


namespace
{

    struct TestVectorExpression : public CDPL::Math::VectorExpression<TestVectorExpression> {};

    struct TestMatrixExpression : public CDPL::Math::MatrixExpression<TestMatrixExpression> {};

    struct TestQuaternionExpression : public CDPL::Math::QuaternionExpression<TestQuaternionExpression> {};

    struct TestVectorContainer : public CDPL::Math::VectorContainer<TestVectorContainer> {};

    struct TestMatrixContainer : public CDPL::Math::MatrixContainer<TestMatrixContainer> {};

    struct TestQuaternionContainer : public CDPL::Math::QuaternionContainer<TestQuaternionContainer> {};
}


BOOST_AUTO_TEST_CASE(VectorExpressionTest)
{
    using namespace CDPL;
    using namespace Math;

    TestVectorExpression expr_impl;

    VectorExpression<TestVectorExpression>& expr = expr_impl;
    const VectorExpression<TestVectorExpression>& const_expr = expr_impl;

    TestVectorExpression& expr_impl_ref = expr();
    const TestVectorExpression& const_expr_impl_ref = const_expr();

    BOOST_CHECK(&expr_impl_ref == &expr_impl);
    BOOST_CHECK(&const_expr_impl_ref == &expr_impl);
}

BOOST_AUTO_TEST_CASE(MatrixExpressionTest)
{
    using namespace CDPL;
    using namespace Math;

    TestMatrixExpression expr_impl;

    MatrixExpression<TestMatrixExpression>& expr = expr_impl;
    const MatrixExpression<TestMatrixExpression>& const_expr = expr_impl;

    TestMatrixExpression& expr_impl_ref = expr();
    const TestMatrixExpression& const_expr_impl_ref = const_expr();

    BOOST_CHECK(&expr_impl_ref == &expr_impl);
    BOOST_CHECK(&const_expr_impl_ref == &expr_impl);
}

BOOST_AUTO_TEST_CASE(QuaternionExpressionTest)
{
    using namespace CDPL;
    using namespace Math;

    TestQuaternionExpression expr_impl;

    QuaternionExpression<TestQuaternionExpression>& expr = expr_impl;
    const QuaternionExpression<TestQuaternionExpression>& const_expr = expr_impl;

    TestQuaternionExpression& expr_impl_ref = expr();
    const TestQuaternionExpression& const_expr_impl_ref = const_expr();

    BOOST_CHECK(&expr_impl_ref == &expr_impl);
    BOOST_CHECK(&const_expr_impl_ref == &expr_impl);
}

BOOST_AUTO_TEST_CASE(VectorContainerTest)
{
    using namespace CDPL;
    using namespace Math;

    TestVectorContainer cont_impl;

    VectorContainer<TestVectorContainer>& cont = cont_impl;
    const VectorContainer<TestVectorContainer>& const_cont = cont_impl;

    TestVectorContainer& cont_impl_ref = cont();
    const TestVectorContainer& const_cont_impl_ref = const_cont();

    BOOST_CHECK(&cont_impl_ref == &cont_impl);
    BOOST_CHECK(&const_cont_impl_ref == &cont_impl);

    VectorExpression<TestVectorContainer>& expr = cont_impl;
    const VectorExpression<TestVectorContainer>& const_expr = cont_impl;

    TestVectorContainer& expr_impl_ref = expr();
    const TestVectorContainer& const_expr_impl_ref = const_expr();

    BOOST_CHECK(&expr_impl_ref == &cont_impl);
    BOOST_CHECK(&const_expr_impl_ref == &cont_impl);
}

BOOST_AUTO_TEST_CASE(MatrixContainerTest)
{
    using namespace CDPL;
    using namespace Math;

    TestMatrixContainer cont_impl;

    MatrixContainer<TestMatrixContainer>& cont = cont_impl;
    const MatrixContainer<TestMatrixContainer>& const_cont = cont_impl;

    TestMatrixContainer& cont_impl_ref = cont();
    const TestMatrixContainer& const_cont_impl_ref = const_cont();

    BOOST_CHECK(&cont_impl_ref == &cont_impl);
    BOOST_CHECK(&const_cont_impl_ref == &cont_impl);

    MatrixExpression<TestMatrixContainer>& expr = cont_impl;
    const MatrixExpression<TestMatrixContainer>& const_expr = cont_impl;

    TestMatrixContainer& expr_impl_ref = expr();
    const TestMatrixContainer& const_expr_impl_ref = const_expr();

    BOOST_CHECK(&expr_impl_ref == &cont_impl);
    BOOST_CHECK(&const_expr_impl_ref == &cont_impl);
}

BOOST_AUTO_TEST_CASE(QuaternionContainerTest)
{
    using namespace CDPL;
    using namespace Math;
    using namespace CDPL;
    using namespace Math;

    TestQuaternionContainer cont_impl;

    QuaternionContainer<TestQuaternionContainer>& cont = cont_impl;
    const QuaternionContainer<TestQuaternionContainer>& const_cont = cont_impl;

    TestQuaternionContainer& cont_impl_ref = cont();
    const TestQuaternionContainer& const_cont_impl_ref = const_cont();

    BOOST_CHECK(&cont_impl_ref == &cont_impl);
    BOOST_CHECK(&const_cont_impl_ref == &cont_impl);

    QuaternionExpression<TestQuaternionContainer>& expr = cont_impl;
    const QuaternionExpression<TestQuaternionContainer>& const_expr = cont_impl;

    TestQuaternionContainer& expr_impl_ref = expr();
    const TestQuaternionContainer& const_expr_impl_ref = const_expr();

    BOOST_CHECK(&expr_impl_ref == &cont_impl);
    BOOST_CHECK(&const_expr_impl_ref == &cont_impl);
}

