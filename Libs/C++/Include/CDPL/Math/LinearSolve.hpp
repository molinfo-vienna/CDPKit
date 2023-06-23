/* 
 * LinearSolve.hpp 
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
 * \brief Functions for solving linear equations.
 */

#ifndef CDPL_MATH_LINEARSOLVE_HPP
#define CDPL_MATH_LINEARSOLVE_HPP

#include "CDPL/Math/CommonType.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename E> class VectorExpression;
		template <typename E> class MatrixExpression;

		template <typename E1, typename E2>
		bool
		solveLower(const MatrixExpression<E1>& e1, VectorExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize()))
				return false;
		
			SizeType size = e2().getSize();

			for (SizeType n = 0; n < size; n++) {
				if (e1()(n, n) == typename E1::ValueType(0))
					return false;

				ValueType t = e2()(n) /= e1()(n, n);

				if (t != ValueType(0)) 
					for (SizeType m = n + 1; m < size; m++)
						e2()(m) -= e1()(m, n) * t;
			}

			return true;
		}

		template <typename E1, typename E2>
		bool
		solveUnitLower(const MatrixExpression<E1>& e1, VectorExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize()))
				return false;
		
			SizeType size = e2().getSize();

			for (SizeType n = 0; n < size; n++) {
				ValueType t = e2()(n);

				if (t != ValueType(0)) 
					for (SizeType m = n + 1; m < size; m++)
						e2()(m) -= e1()(m, n) * t;
			}

			return true;
		}

		template <typename E1, typename E2>		
		bool
		solveLower(const MatrixExpression<E1>& e1, MatrixExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize1()))
				return false;
		
			SizeType size1 = e2().getSize1();
			SizeType size2 = e2().getSize2();

			for (SizeType n = 0; n < size1; n++) {
				if (e1()(n, n) == typename E1::ValueType(0))
					return false;

				for (SizeType l = 0; l < size2; l++) {
					ValueType t = e2()(n, l) /= e1()(n, n);

					if (t != ValueType(0))
						for (SizeType m = n + 1; m < size1; m++)
							e2()(m, l) -= e1()(m, n) * t;
				}
			}

			return true;
		}

		template <typename E1, typename E2>		
		bool
		solveUnitLower(const MatrixExpression<E1>& e1, MatrixExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize1()))
				return false;
		
			SizeType size1 = e2().getSize1();
			SizeType size2 = e2().getSize2();

			for (SizeType n = 0; n < size1; n++) {
				for (SizeType l = 0; l < size2; l++) {
					ValueType t = e2()(n, l);

					if (t != ValueType(0))
						for (SizeType m = n + 1; m < size1; m++)
							e2()(m, l) -= e1()(m, n) * t;
				}
			}

			return true;
		}

		template <typename E1, typename E2>		
		bool
		solveUpper(const MatrixExpression<E1>& e1, VectorExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize()))
				return false;

			SizeType size = e2().getSize();

			for (DifferenceType n = size - 1; n >= 0; n--) {
				if (e1()(n, n) == typename E1::ValueType(0))
					return false;

				ValueType t = e2()(n) /= e1()(n, n);

				if (t != ValueType(0))
					for (DifferenceType m = n - 1; m >= 0; m--)
						e2()(m) -= e1()(m, n) * t;
			}

			return true;
		}
	
		template <typename E1, typename E2>		
		bool
		solveUnitUpper(const MatrixExpression<E1>& e1, VectorExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize()))
				return false;

			SizeType size = e2().getSize();

			for (DifferenceType n = size - 1; n >= 0; n--) {
				ValueType t = e2()(n);

				if (t != ValueType(0))
					for (DifferenceType m = n - 1; m >= 0; m--)
						e2()(m) -= e1()(m, n) * t;
			}

			return true;
		}

		template <typename E1, typename E2>		
		bool
		solveUpper(const MatrixExpression<E1>& e1, MatrixExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize1()))
				return false;
		
			SizeType size1 = e2().getSize1();
			SizeType size2 = e2().getSize2();

			for (DifferenceType n = size1 - 1; n >= 0; n--) {
				if (e1()(n, n) == typename E1::ValueType(0))
					return false;

				for (DifferenceType l = size2 - 1; l >= 0; l--) {
					ValueType t = e2()(n, l) /= e1()(n, n);

					if (t != ValueType(0))
						for (DifferenceType m = n - 1; m >= 0; m--)
							e2()(m, l) -= e1()(m, n) * t;
				}
			}

			return true;
		}

		template <typename E1, typename E2>		
		bool
		solveUnitUpper(const MatrixExpression<E1>& e1, MatrixExpression<E2>& e2)
		{
			typedef typename CommonType<typename E1::SizeType, typename E2::SizeType>::Type SizeType;
			typedef typename CommonType<typename E1::DifferenceType, typename E2::DifferenceType>::Type DifferenceType;
			typedef typename CommonType<typename E1::ValueType, typename E2::ValueType>::Type ValueType;

			if (e1().getSize1() != e1().getSize2())
				return false;

			if (SizeType(e1().getSize2()) != SizeType(e2().getSize1()))
				return false;
		
			SizeType size1 = e2().getSize1();
			SizeType size2 = e2().getSize2();

			for (DifferenceType n = size1 - 1; n >= 0; n--) {
				for (DifferenceType l = size2 - 1; l >= 0; l--) {
					ValueType t = e2()(n, l);

					if (t != ValueType(0))
						for (DifferenceType m = n - 1; m >= 0; m--)
							e2()(m, l) -= e1()(m, n) * t;
				}
			}

			return true;
		}
	}
}

#endif // CDPL_MATH_LINEARSOLVE_HPP
