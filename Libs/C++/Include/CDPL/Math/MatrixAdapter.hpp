/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MatrixAdapter.hpp 
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
 * \brief Provides matrix adapter classes.
 */

#ifndef CDPL_MATH_MATRIXADAPTER_HPP
#define CDPL_MATH_MATRIXADAPTER_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

#include "CDPL/Math/Expression.hpp"
#include "CDPL/Math/TypeTraits.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename T> class Range;

		struct Lower
		{

			template <typename M>
			static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j) {
				if (i >= j)
					return m.getData()(i, j);

				return m.zero;
			}
		};
	
		struct UnitLower
		{

			template <typename M>
			static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j) {
				if (i == j)
					return m.one;

				if (i >= j)
					return m.getData()(i, j);

				return m.zero;
			}
		};

		struct Upper
		{

			template <typename M>
			static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j) {
				if (i <= j)
					return m.getData()(i, j);

				return m.zero;
			}
		};

		struct UnitUpper
		{

			template <typename M>
			static typename M::ConstReference get(const M& m, typename M::SizeType i, typename M::SizeType j) {
				if (i == j)
					return m.one;

				if (i <= j)
					return m.getData()(i, j);

				return m.zero;
			}
		};

		template <typename M, typename Tri>
		class TriangularAdapter : public MatrixExpression<TriangularAdapter<M, Tri> >
		{

			typedef TriangularAdapter<M, Tri> SelfType;

			friend struct Lower;
			friend struct UnitLower;
			friend struct Upper;
			friend struct UnitUpper;

		public:
			typedef M MatrixType;
			typedef Tri TriangularType;
			typedef typename M::SizeType SizeType;
			typedef typename M::DifferenceType DifferenceType;
			typedef typename M::ValueType ValueType;
			typedef typename M::ConstReference ConstReference;
			typedef typename boost::mpl::if_<boost::is_const<M>,
											 typename M::ConstReference,
											 typename M::Reference>::type Reference;
			typedef typename boost::mpl::if_<boost::is_const<M>,
											 typename M::ConstClosureType,
											 typename M::ClosureType>::type MatrixClosureType;
			typedef const SelfType ConstClosureType;
			typedef SelfType ClosureType;
			typedef Range<SizeType> RangeType;
			
			explicit TriangularAdapter(MatrixType& m): data(m) {}

			ConstReference operator()(SizeType i, SizeType j) const {
				return TriangularType::template get<SelfType>(*this, i, j);
			}

			SizeType getSize1() const {
				return data.getSize1();
			}

			SizeType getSize2() const {
				return data.getSize2();
			}

			MatrixClosureType& getData() {
				return data;
			}

			const MatrixClosureType& getData() const {
				return data;
			}

			bool isEmpty() const {
				return (data.getSize1() == 0 || data.getSize2() == 0);
			}

		private:
			MatrixClosureType      data;
			static const ValueType zero;
			static const ValueType one;
		};

		template <typename M, typename Tri>
		const typename TriangularAdapter<M, Tri>::ValueType TriangularAdapter<M, Tri>::zero = TriangularAdapter<M, Tri>::ValueType();
		
		template <typename M, typename Tri>
		const typename TriangularAdapter<M, Tri>::ValueType TriangularAdapter<M, Tri>::one  = TriangularAdapter<M, Tri>::ValueType(1);

		template <typename M, typename Tri>
		struct VectorTemporaryTraits<TriangularAdapter<M, Tri> > : public VectorTemporaryTraits<M> {};

		template <typename M, typename Tri>
		struct VectorTemporaryTraits<const TriangularAdapter<M, Tri> > : public VectorTemporaryTraits<M> {};

		template <typename M, typename Tri>
		struct MatrixTemporaryTraits<TriangularAdapter<M, Tri> > : public MatrixTemporaryTraits<M> {};

		template <typename M, typename Tri>
		struct MatrixTemporaryTraits<const TriangularAdapter<M, Tri> > : public MatrixTemporaryTraits<M> {};

		template <typename Tri, typename E>
		TriangularAdapter<E, Tri> 
		triang(MatrixExpression<E>& e)
		{
			return TriangularAdapter<E, Tri>(e());
		}

		template <typename Tri, typename E>
		TriangularAdapter<const E, Tri> 
		triang(const MatrixExpression<E>& e)
		{
			return TriangularAdapter<const E, Tri>(e());
		}
	}
}

#endif // CDPL_MATH_MATRIXADAPTER_HPP
