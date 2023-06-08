/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Grid.hpp 
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
 * \brief Definition of grid data types.
 */

#ifndef CDPL_MATH_GRID_HPP
#define CDPL_MATH_GRID_HPP

#include <cstddef>
#include <algorithm>
#include <vector>
#include <limits>
#include <type_traits>
#include <utility>

#include <boost/shared_ptr.hpp>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/GridExpression.hpp"
#include "CDPL/Math/GridAssignment.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{

		template <typename G> 
		class GridReference : public GridExpression<GridReference<G> >
		{

			typedef GridReference<G> SelfType;

		public:
			typedef G GridType;
			typedef typename G::ValueType ValueType;
			typedef typename std::conditional<std::is_const<G>::value,
											 typename G::ConstReference,
											 typename G::Reference>::type Reference;
			typedef typename G::ConstReference ConstReference;
			typedef typename G::SizeType SizeType;
			typedef typename G::DifferenceType DifferenceType;
			typedef SelfType ClosureType;
			typedef const SelfType ConstClosureType;

			explicit GridReference(GridType& g): data(g) {}

			Reference operator()(SizeType i) {
				return data(i);
			}

			ConstReference operator()(SizeType i) const {
				return data(i);
			}
	
			Reference operator()(SizeType i, SizeType j, SizeType k) {
				return data(i, j, k);
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				return data(i, j, k);
			}
	
			SizeType getSize() const {
				return data.getSize();
			}

			SizeType getSize1() const {
				return data.getSize1();
			}

			SizeType getSize2() const {
				return data.getSize2();
			}

			SizeType getSize3() const {
				return data.getSize3();
			}

			SizeType getMaxSize() const {
				return data.getMaxSize();
			}
	
			SizeType getMaxSize1() const {
				return data.getMaxSize1();
			}

			SizeType getMaxSize2() const {
				return data.getMaxSize2();
			}
		
			SizeType getMaxSize3() const {
				return data.getMaxSize3();
			}
		
			bool isEmpty() const {
				return data.isEmpty();
			}
	
			const GridType& getData() const {
				return data;
			}

			GridType& getData() {
				return data;
			}

			GridReference& operator=(const GridReference& r) {
				data.operator=(r.data);
				return *this;
			}

			template <typename E>
			GridReference& operator=(const GridExpression<E>& e) {
				data.operator=(e);
				return *this;
			}

			template <typename E>
			GridReference& operator+=(const GridExpression<E>& e) {
				data.operator+=(e);
				return *this;
			}	

			template <typename E>
			GridReference& operator-=(const GridExpression<E>& e) {
				data.operator-=(e);
				return *this;
			}

			template <typename T>			
			typename std::enable_if<IsScalar<T>::value, GridReference>::type& operator*=(const T& t) {
				data.operator*=(t);
				return *this;
			}
	
			template <typename T>			
			typename std::enable_if<IsScalar<T>::value, GridReference>::type& operator/=(const T& t) {
				data.operator/=(t);
				return *this;
			}
			
			template <typename E>
			GridReference& assign(const GridExpression<E>& e) {
				data.assign(e);
				return *this;
			}

			template <typename E>
			GridReference& plusAssign(const GridExpression<E>& e) {
				data.plusAssign(e);
				return *this;
			}

			template <typename E>
			GridReference& minusAssign(const GridExpression<E>& e) {
				data.minusAssign(e);
				return *this;
			}

			void swap(GridReference& r) {
				data.swap(r.data);
			}
	
			friend void swap(GridReference& r1, GridReference& r2) {
				r1.swap(r2);
			}

		private:
			GridType& data;
		};

		template <typename T, typename A = std::vector<T> > 
		class Grid : public GridContainer<Grid<T, A> >
		{

			typedef Grid<T, A> SelfType;

		public:
			typedef T ValueType;
			typedef T& Reference;
			typedef const T& ConstReference;
			typedef typename A::size_type SizeType;
			typedef typename A::difference_type DifferenceType;
			typedef A ArrayType;
			typedef T* Pointer;
			typedef const T* ConstPointer;
			typedef GridReference<SelfType> ClosureType;
			typedef const GridReference<const SelfType> ConstClosureType;
			typedef SelfType GridTemporaryType;
			typedef boost::shared_ptr<SelfType> SharedPointer;

			Grid(): data(), size1(0), size2(0), size3(0) {}

			Grid(SizeType m, SizeType n, SizeType o): 
				data(storageSize(m, n, o)), size1(m), size2(n), size3(o)  {}

			Grid(SizeType m, SizeType n, SizeType o, const ValueType& v):  
				data(storageSize(m, n, o), v), size1(m), size2(n), size3(o) {}

			Grid(const Grid& g): data(g.data), size1(g.size1), size2(g.size2), size3(g.size3) {}

			Grid(Grid&& g): data(), size1(0), size2(0), size3(0) {
				swap(g);
			}

			template <typename E>
			Grid(const GridExpression<E>& e): 
				data(storageSize(e().getSize1(), e().getSize2(), e().getSize3())), size1(e().getSize1()), size2(e().getSize2()), size3(e().getSize3()) {
				gridAssignGrid<ScalarAssignment>(*this, e);
			}

			Reference operator()(SizeType i) {
				CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
				return data[i];
			}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
				return data[i];
			}

			Reference operator()(SizeType i, SizeType j, SizeType k) {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
				return data[(k * getSize2() + j) * getSize1() + i];
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
				return data[(k * getSize2() + j) * getSize1() + i];
			}

			bool isEmpty() const {
				return data.empty();
			}
	
			SizeType getSize() const {
				return (size1 * size2 * size3);
			}
	
			SizeType getSize1() const {
				return size1;
			}
	
			SizeType getSize2() const {
				return size2;
			}

			SizeType getSize3() const {
				return size3;
			}

			SizeType getMaxSize() const {
				return data.max_size();
			}

			ArrayType& getData() {
				return data;
			}
			
			const ArrayType& getData() const {
				return data;
			}

			Grid& operator=(const Grid& g) {
				data = g.data;
				size1 = g.size1;
				size2 = g.size2;
				size3 = g.size3;
				return *this;
			}

			Grid& operator=(Grid&& g) {
				swap(g);
				return *this;
			}

			template <typename C>
			Grid& operator=(const GridContainer<C>& c) {
				return assign(c);
			}

			template <typename E>
			Grid& operator=(const GridExpression<E>& e) {
				Grid tmp(e);
				swap(tmp);

				return *this;
			}

			template <typename C>
			Grid& operator+=(const GridContainer<C>& c) {
				return plusAssign(c);
			}

			template <typename E>
			Grid& operator+=(const GridExpression<E>& e) {
				Grid tmp(*this + e);
				swap(tmp);

				return *this;
			}	

			template <typename C>
			Grid& operator-=(const GridContainer<C>& c) {
				return minusAssign(c);
			}

			template <typename E>
			Grid& operator-=(const GridExpression<E>& e) {
				Grid tmp(*this - e);
				swap(tmp);

				return *this;
			}

			template <typename T1>			
			typename std::enable_if<IsScalar<T1>::value, Grid>::type& operator*=(const T1& t) {
				gridAssignScalar<ScalarMultiplicationAssignment>(*this, t);
				return *this;
			}
	
			template <typename T1>			
			typename std::enable_if<IsScalar<T1>::value, Grid>::type& operator/=(const T1& t) {
				gridAssignScalar<ScalarDivisionAssignment>(*this, t);
				return *this;
			}
			
			template <typename E>
			Grid& assign(const GridExpression<E>& e) {
				resize(e().getSize1(), e().getSize2());
				gridAssignGrid<ScalarAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			Grid& plusAssign(const GridExpression<E>& e) {
				gridAssignGrid<ScalarAdditionAssignment>(*this, e);
				return *this;
			}

			template <typename E>
			Grid& minusAssign(const GridExpression<E>& e) {
				gridAssignGrid<ScalarSubtractionAssignment>(*this, e);
				return *this;
			}

			void swap(Grid& g) {
				if (this != &g) {
					std::swap(data, g.data);
					std::swap(size1, g.size1);
					std::swap(size2, g.size2);
					std::swap(size3, g.size3);
				}
			}
	
			friend void swap(Grid& g1, Grid& g2) {
				g1.swap(g2);
			}

			void clear(const ValueType& v = ValueType()) {
				std::fill(data.begin(), data.end(), v);
			}

			void resize(SizeType m, SizeType n, SizeType o, bool preserve = true, const ValueType& v = ValueType()) {
				if (size1 == m && size2 == n && size3 == o)
					return;

				if (preserve) {
					Grid tmp(m, n, o, v);

					for (SizeType i = 0, min_size1 = std::min(size1, m); i < min_size1; i++)
						for (SizeType j = 0, min_size2 = std::min(size2, n); j < min_size2; j++)
							for (SizeType k = 0, min_size3 = std::min(size3, o); k < min_size3; k++)
							tmp(i, j, k) = (*this)(i, j, k);

					swap(tmp);

				} else {
					data.resize(storageSize(m, n, o), v);
					size1 = m;
					size2 = n;
					size3 = o;
				}
			}

		private:
			static SizeType storageSize(SizeType m, SizeType n, SizeType o) {
				CDPL_MATH_CHECK(n == 0 || o == 0 || 
								(n <= (std::numeric_limits<SizeType>::max() / o) && m <= (std::numeric_limits<SizeType>::max() / (n * o))),
								"Maximum size exceeded", Base::SizeError);
				return (m * n * o);
			}

			ArrayType data;
			SizeType  size1;
			SizeType  size2;
			SizeType  size3;
		};

		template <typename T> 
		class ZeroGrid : public GridContainer<ZeroGrid<T> >
		{

			typedef ZeroGrid<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef GridReference<SelfType> ClosureType;
			typedef const GridReference<const SelfType> ConstClosureType;
			typedef Grid<T> GridTemporaryType;

			ZeroGrid(): size1(0), size2(0), size3(0) {}

			ZeroGrid(SizeType m, SizeType n, SizeType o): size1(m), size2(n), size3(o) {}

			ZeroGrid(const ZeroGrid& m): size1(m.size1), size2(m.size2), size3(m.size3) {}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
				return zero;
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
				return zero;
			}

			bool isEmpty() const {
				return (size1 == 0 || size2 == 0 || size3 == 0);
			}
	
			SizeType getSize() const {
				return (size1 * size2 * size3);
			}
	
			SizeType getSize1() const {
				return size1;
			}
	
			SizeType getSize2() const {
				return size2;
			}

			SizeType getSize3() const {
				return size3;
			}

			SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}
	
			SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			SizeType getMaxSize3() const {
				return std::numeric_limits<SizeType>::max();
			}

			ZeroGrid& operator=(const ZeroGrid& g) {
				if (this != &g) {
					size1 = g.size1;
					size2 = g.size2;
					size3 = g.size3;
				}

				return *this;
			}

			void swap(ZeroGrid& g) {
				if (this != &g) {
					std::swap(size1, g.size1);
					std::swap(size2, g.size2);
					std::swap(size3, g.size3);
				}
			}
	
			friend void swap(ZeroGrid& g1, ZeroGrid& g2) {
				g1.swap(g2);
			}

			void resize(SizeType m, SizeType n, SizeType o) {
				size1 = m;
				size2 = n;
				size3 = o;
			}

		private:
			SizeType               size1;
			SizeType               size2;
			SizeType               size3;
			static const ValueType zero;
		};

		template <typename T> const typename ZeroGrid<T>::ValueType ZeroGrid<T>::zero = ZeroGrid<T>::ValueType();

		template <typename T> 
		class ScalarGrid : public GridContainer<ScalarGrid<T> >
		{

			typedef ScalarGrid<T> SelfType;

		public:
			typedef T ValueType;
			typedef const T& Reference;
			typedef const T& ConstReference;
			typedef std::size_t SizeType;
			typedef std::ptrdiff_t DifferenceType;
			typedef GridReference<SelfType> ClosureType;
			typedef const GridReference<const SelfType> ConstClosureType;
			typedef Grid<T> GridTemporaryType;

			ScalarGrid(): size1(0), size2(0), size3(0), value() {}

			ScalarGrid(SizeType m, SizeType n, SizeType o, const ValueType& v = ValueType()): size1(m), size2(n), size3(o), value(v) {}

			ScalarGrid(const ScalarGrid& m): size1(m.size1), size2(m.size2), size3(m.size3), value(m.value) {}

			ConstReference operator()(SizeType i) const {
				CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
				return value;
			}

			ConstReference operator()(SizeType i, SizeType j, SizeType k) const {
				CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
				return value;
			}

			bool isEmpty() const {
				return (size1 == 0 || size2 == 0 || size3 == 0);
			}
	
			SizeType getSize() const {
				return (size1 * size2 * size3);
			}
	
			SizeType getSize1() const {
				return size1;
			}
	
			SizeType getSize2() const {
				return size2;
			}

			SizeType getSize3() const {
				return size3;
			}

			SizeType getMaxSize1() const {
				return std::numeric_limits<SizeType>::max();
			}
	
			SizeType getMaxSize2() const {
				return std::numeric_limits<SizeType>::max();
			}

			SizeType getMaxSize3() const {
				return std::numeric_limits<SizeType>::max();
			}

			ScalarGrid& operator=(const ScalarGrid& g) {
				if (this != &g) {
					size1 = g.size1;
					size2 = g.size2;
					size3 = g.size3;
					value = g.value;
				}

				return *this;
			}

			void swap(ScalarGrid& g) {
				if (this != &g) {
					std::swap(size1, g.size1);
					std::swap(size2, g.size2);
					std::swap(size3, g.size3);
					std::swap(value, g.value);
				}
			}
	
			friend void swap(ScalarGrid& g1, ScalarGrid& g2) {
				g1.swap(g2);
			}

			void resize(SizeType m, SizeType n, SizeType o) {
				size1 = m;
				size2 = n;
				size3 = o;
			}

		private:
			SizeType  size1;
			SizeType  size2;
			SizeType  size3;
			ValueType value;
		};

		template <typename G>
		struct GridTemporaryTraits<GridReference<G> > : public GridTemporaryTraits<G> {};

		template <typename G>
		struct GridTemporaryTraits<const GridReference<G> > : public GridTemporaryTraits<G> {};

		typedef ZeroGrid<float> FZeroGrid;
		typedef ZeroGrid<double> DZeroGrid;

		typedef ScalarGrid<float> FScalarGrid;
		typedef ScalarGrid<double> DScalarGrid;

		/**
		 * \brief An unbounded dense grid holding floating point values of type <tt>float</tt>.
		 */
		typedef Grid<float> FGrid;

		/**
		 * \brief An unbounded dense grid holding floating point values of type <tt>double</tt>.
		 */
		typedef Grid<double> DGrid;
	}
}

#endif // CDPL_MATH_GRID_HPP
