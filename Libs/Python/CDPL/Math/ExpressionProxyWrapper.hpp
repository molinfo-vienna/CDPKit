/* 
 * ExpressionProxyWrapper.hpp 
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


#ifndef CDPL_PYTHON_MATH_EXPRESSIONPROXYWRAPPER_HPP
#define CDPL_PYTHON_MATH_EXPRESSIONPROXYWRAPPER_HPP

#include <memory>

#include <boost/python.hpp>


namespace CDPLPythonMath
{

    template <typename ExpressionType, typename ProxySpec, typename ProxyType>
    struct VectorExpressionProxyWrapper : ProxyType, boost::python::wrapper<ProxyType>
    {

        typedef typename ExpressionType::SharedPointer ExpressionPointerType;
        typedef std::shared_ptr<VectorExpressionProxyWrapper> SharedPointer;

        VectorExpressionProxyWrapper(const VectorExpressionProxyWrapper& ph): ProxyType(ph), exprPointer(ph.exprPointer) {}

        VectorExpressionProxyWrapper(const ExpressionPointerType& expr_ptr, const ProxySpec& proxy_spec): 
            ProxyType(*expr_ptr, proxy_spec), exprPointer(expr_ptr) {}
        
        ExpressionPointerType getData() const {
            return exprPointer;
        } 

        ExpressionPointerType exprPointer;
    };

    template <typename ExpressionType, typename ProxySpec, typename ProxyType>
    struct MatrixExpressionProxyWrapper : ProxyType, boost::python::wrapper<ProxyType>
    {

        typedef typename ExpressionType::SharedPointer ExpressionPointerType;
        typedef std::shared_ptr<MatrixExpressionProxyWrapper> SharedPointer;

        MatrixExpressionProxyWrapper(const MatrixExpressionProxyWrapper& ph): ProxyType(ph), exprPointer(ph.exprPointer) {}

        MatrixExpressionProxyWrapper(const ExpressionPointerType& expr_ptr, const ProxySpec& proxy_spec1, const ProxySpec& proxy_spec2): 
            ProxyType(*expr_ptr, proxy_spec1, proxy_spec2), exprPointer(expr_ptr) {}

        ExpressionPointerType getData() const {
            return exprPointer;
        } 

        ExpressionPointerType exprPointer;
    };
}

#endif // CDPL_PYTHON_MATH_EXPRESSIONPROXYWRAPPER_HPP
