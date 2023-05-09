/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LUDecomposition.hpp 
 *
 * Copyright (C) 2010-2011 Thomas Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Implementation of matrix LU-decomposition and associated operations.
 */

#ifndef CDPL_MATH_LUDECOMPOSITION_HPP
#define CDPL_MATH_LUDECOMPOSITION_HPP

#include <algorithm>

#include <boost/swap.hpp>

#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/LinearSolve.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename E>
		typename E::SizeType 
		luDecompose(MatrixExpression<E>& e) 
		{
			typedef typename E::SizeType SizeType;
			typedef typename E::ValueType ValueType;
			typedef typename MatrixRange<E>::RangeType MatrixRangeType;
			typedef typename VectorRange<MatrixRow<E> >::RangeType RowRangeType;
			typedef typename VectorRange<MatrixColumn<E> >::RangeType ColumnRangeType;

			SizeType size1 = e().getSize1();
			SizeType size2 = e().getSize2();
			SizeType size = std::min(size1, size2);
		
			if (size == 0)
				return 0;
		
			SizeType singular = 0;

			for (SizeType i = 0; i < size; i++) {
				MatrixColumn<E> col_i(column(e, i));
				MatrixRow<E> row_i(row(e, i));

				if (e()(i, i) != ValueType(0)) {
					ValueType m_inv = ValueType(1) / e()(i, i);
					range(col_i, ColumnRangeType(i + 1, size1)) *= m_inv;
				
				} else if (singular == 0)
					singular = i + 1;

				range(e, MatrixRangeType(i + 1, size1), MatrixRangeType(i + 1, size2))
					.minusAssign(outerProd(range(col_i, ColumnRangeType(i + 1, size1)),
										   range(row_i, RowRangeType(i + 1, size2))));
			}

			return singular;
		}

		template <typename E, typename PV, typename T>
		typename E::SizeType 
		luDecompose(MatrixExpression<E>& e, PV& pv, T& num_row_swaps) 
		{
			typedef typename E::SizeType SizeType;
			typedef typename E::ValueType ValueType;
			typedef typename MatrixRange<E>::RangeType MatrixRangeType;
			typedef typename VectorRange<MatrixRow<E> >::RangeType RowRangeType;
			typedef typename VectorRange<MatrixColumn<E> >::RangeType ColumnRangeType;
	
			SizeType size1 = e().getSize1();
			SizeType size2 = e().getSize2();
			SizeType size = std::min(size1, size2);

			num_row_swaps = 0;

			if (size == 0)
				return 0;

			SizeType singular = 0;

			for (SizeType i = 0; i < size; i++) {
				MatrixColumn<E> col_i(column(e, i));
				MatrixRow<E> row_i(row(e, i));
				SizeType norm_inf_idx = i + normInfIndex(range(col_i, ColumnRangeType(i, size1)));
            
				if (e()(norm_inf_idx, i) != ValueType(0)) {
					pv[i] = norm_inf_idx;

					if (norm_inf_idx != i) {
						row(e, norm_inf_idx).swap(row_i);
						num_row_swaps++;
					}

					ValueType m_inv = ValueType(1) / e()(i, i);
					range(col_i, ColumnRangeType(i + 1, size1)) *= m_inv;

				} else if (singular == 0) 
					singular = i + 1;

				range(e, MatrixRangeType(i + 1, size1), MatrixRangeType(i + 1, size2))
					.minusAssign(outerProd(range(col_i, ColumnRangeType(i + 1, size1)),
										   range(row_i, RowRangeType(i + 1, size2))));
			}

			return singular;
		}

		template <typename E, typename PV>		
		void 
		swapRows(VectorExpression<E>& e, const PV& pv)
		{
			typedef typename E::SizeType SizeType;

			for (SizeType i = 0, size = e().getSize(); i < size; i++) {
				if (i != SizeType(pv[i]))
					std::swap(e()(i), e()(pv[i]));
			}
		}

		template <typename E, typename PV>		
		void 
		swapRows(MatrixExpression<E>& e, const PV& pv)
		{
			typedef typename E::SizeType SizeType;

			for (SizeType i = 0, size = e().getSize1(); i < size; i++) {
				if (i != SizeType(pv[i])) {
					MatrixRow<E> other_row(e(), pv[i]);
					row(e, i).swap(other_row);
				}
			}
		}

		template <typename E1, typename E2>
		bool
		luSubstitute(const MatrixExpression<E1>& lu, VectorExpression<E2>& b)
		{
			if (!solveUnitLower(lu, b))
				return false;

			return solveUpper(lu, b);
		}

		template <typename E1, typename E2, typename PV>
		bool
		luSubstitute(const MatrixExpression<E1>& lu, const PV& pv, VectorExpression<E2>& b)
		{
			swapRows(b, pv);
			
			return luSubstitute(lu, b);
		}

		template <typename E1, typename E2>
		bool
		luSubstitute(const MatrixExpression<E1>& lu, MatrixExpression<E2>& b)
		{
			if (!solveUnitLower(lu, b))
				return false;

			return solveUpper(lu, b);
		}

		template <typename E1, typename E2, typename PV>
		bool
		luSubstitute(const MatrixExpression<E1>& lu, const PV& pv, MatrixExpression<E2>& b)
		{
			swapRows(b, pv);

			return luSubstitute(lu, b);
		}
	}
}

#endif // CDPL_MATH_LUDECOMPOSITION_HPP
