/* 
 * ExpressionAdapterWrapper.hpp 
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


#ifndef CDPL_PYTHON_MATH_EXPRESSIONADAPTERWRAPPER_HPP
#define CDPL_PYTHON_MATH_EXPRESSIONADAPTERWRAPPER_HPP

#include <memory>

#include <boost/python.hpp>


namespace CDPLPythonMath
{

    template <typename ExpressionType, typename AdapterType>
    struct ExpressionAdapterWrapper : AdapterType,
                                      boost::python::wrapper<AdapterType>
    {

        typedef typename ExpressionType::SharedPointer    ExpressionPointerType;
        typedef std::shared_ptr<ExpressionAdapterWrapper> SharedPointer;

        ExpressionAdapterWrapper(const ExpressionAdapterWrapper& ph):
            AdapterType(ph), exprPointer(ph.exprPointer) {}

        ExpressionAdapterWrapper(const ExpressionPointerType& expr_ptr):
            AdapterType(*expr_ptr), exprPointer(expr_ptr) {}

        ExpressionPointerType getData() const
        {
            return exprPointer;
        }

        ExpressionPointerType exprPointer;
    };
} // namespace CDPLPythonMath

#endif // CDPL_PYTHON_MATH_EXPRESSIONADAPTERWRAPPER_HPP
