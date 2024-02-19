/* 
 * VectorArrayAlignmentCalculator.hpp 
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

/**
 * \file
 * \brief Implementation of the Kabsch algorithm.
 */

#ifndef CDPL_MATH_VECTORARRAYALIGNMENTCALCULATOR_HPP
#define CDPL_MATH_VECTORARRAYALIGNMENTCALCULATOR_HPP

#include <cstddef>

#include "CDPL/Math/KabschAlgorithm.hpp"
#include "CDPL/Math/MatrixExpression.hpp"
#include "CDPL/Math/VectorExpression.hpp"


namespace CDPL
{

    namespace Math
    {

        template <typename VA, typename V = typename VA::ElementType, typename T = typename V::ValueType>
        class VectorArrayAlignmentCalculator
        {

          public:
            typedef VA                                              VectorArrayType;
            typedef V                                               VectorType;
            typedef T                                               ValueType;
            typedef typename KabschAlgorithm<ValueType>::MatrixType MatrixType;

            template <typename VE>
            bool calculate(const VectorArrayType& points, const VectorArrayType& ref_points, const VectorExpression<VE>& weights,
                           bool do_center = true, std::size_t max_svd_iter = 0)
            {

                return kabschAlgo.align(MatrixVectorArrayAdapter(points), MatrixVectorArrayAdapter(ref_points),
                                        weights, do_center, max_svd_iter);
            }

            bool calculate(const VectorArrayType& points, const VectorArrayType& ref_points,
                           bool do_center = true, std::size_t max_svd_iter = 0)
            {

                return kabschAlgo.align(MatrixVectorArrayAdapter(points), MatrixVectorArrayAdapter(ref_points),
                                        do_center, max_svd_iter);
            }

            const MatrixType& getTransform() const
            {
                return kabschAlgo.getTransform();
            }

          private:
            class MatrixVectorArrayAdapter : public MatrixExpression<MatrixVectorArrayAdapter>
            {

                typedef MatrixVectorArrayAdapter SelfType;

              public:
                typedef VectorArrayAlignmentCalculator::ValueType ValueType;
                typedef const ValueType                           Reference;
                typedef const ValueType                           ConstReference;
                typedef typename VectorArrayType::SizeType        SizeType;
                typedef std::ptrdiff_t                            DifferenceType;
                typedef SelfType                                  ClosureType;
                typedef const SelfType                            ConstClosureType;

                explicit MatrixVectorArrayAdapter(const VectorArrayType& va):
                    data(va) {}

                Reference operator()(SizeType i, SizeType j)
                {
                    return data.getData()[j].getData()[i];
                }

                ConstReference operator()(SizeType i, SizeType j) const
                {
                    return data[j][i];
                }

                SizeType getSize1() const
                {
                    return VectorType::Size;
                }

                SizeType getSize2() const
                {
                    return data.getSize();
                }

                SizeType getMaxSize() const
                {
                    return data.getMaxSize();
                }

                SizeType getMaxSize1() const
                {
                    return VectorType::Size;
                }

                SizeType getMaxSize2() const
                {
                    return data.getMaxSize();
                }

                bool isEmpty() const
                {
                    return data.isEmpty();
                }

                const VectorArrayType& getData() const
                {
                    return data;
                }

                VectorArrayType& getData()
                {
                    return data;
                }

                MatrixVectorArrayAdapter& operator=(const MatrixVectorArrayAdapter& a)
                {
                    data.operator=(a.data);
                    return *this;
                }

                void swap(MatrixVectorArrayAdapter& a)
                {
                    data.swap(a.data);
                }

                friend void swap(MatrixVectorArrayAdapter& a1, MatrixVectorArrayAdapter& a2)
                {
                    a1.swap(a2);
                }

              private:
                const VectorArrayType& data;
            };

            KabschAlgorithm<ValueType> kabschAlgo;
        };
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTORARRAYALIGNMENTCALCULATOR_HPP
