/* 
 * Grid.hpp 
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
#include <memory>

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

        /**
         * \brief Lightweight grid expression that proxies a reference to an underlying grid container.
         * \tparam G The wrapped grid type.
         */
        template <typename G>
        class GridReference : public GridExpression<GridReference<G> >
        {

            typedef GridReference<G> SelfType;

          public:
            /**
             * \brief The wrapped grid type.
             */
            typedef G                                                      GridType;

            /**
             * \brief The element value type of the wrapped grid.
             */
            typedef typename G::ValueType                                  ValueType;

            /**
             * \brief Mutable reference type (degrades to ConstReference when the wrapped grid is \c const).
             */
            typedef typename std::conditional<std::is_const<G>::value,
                                              typename G::ConstReference,
                                              typename G::Reference>::type Reference;

            /**
             * \brief Constant reference type to an element.
             */
            typedef typename G::ConstReference                             ConstReference;

            /**
             * \brief The unsigned size type used by the wrapped grid.
             */
            typedef typename G::SizeType                                   SizeType;

            /**
             * \brief The signed difference type used by the wrapped grid.
             */
            typedef typename G::DifferenceType                             DifferenceType;

            /**
             * \brief Closure type used when this reference appears inside another expression.
             */
            typedef SelfType                                               ClosureType;

            /**
             * \brief Constant closure type used when this reference appears inside another expression.
             */
            typedef const SelfType                                         ConstClosureType;

            /**
             * \brief Constructs the reference wrapping the grid \a g.
             * \param g The grid to wrap.
             */
            explicit GridReference(GridType& g):
                data(g) {}

            /**
             * \brief Returns a mutable reference to the element at the linear index \a i of the wrapped grid.
             * \param i The zero-based linear index.
             * \return A mutable reference to the element.
             */
            Reference operator()(SizeType i)
            {
                return data(i);
            }

            /**
             * \brief Returns a \c const reference to the element at the linear index \a i of the wrapped grid.
             * \param i The zero-based linear index.
             * \return A \c const reference to the element.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(i);
            }

            /**
             * \brief Returns a mutable reference to the element at the (\a i, \a j, \a k) cell of the wrapped grid.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return A mutable reference to the element.
             */
            Reference operator()(SizeType i, SizeType j, SizeType k)
            {
                return data(i, j, k);
            }

            /**
             * \brief Returns a \c const reference to the element at the (\a i, \a j, \a k) cell of the wrapped grid.
             * \param i The zero-based first-dimension index.
             * \param j The zero-based second-dimension index.
             * \param k The zero-based third-dimension index.
             * \return A \c const reference to the element.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                return data(i, j, k);
            }

            /**
             * \brief Returns the total number of cells of the wrapped grid.
             * \return The wrapped grid's total cell count.
             */
            SizeType getSize() const
            {
                return data.getSize();
            }

            /**
             * \brief Returns the size of the wrapped grid along the first dimension.
             * \return The wrapped grid's first-dimension size.
             */
            SizeType getSize1() const
            {
                return data.getSize1();
            }

            /**
             * \brief Returns the size of the wrapped grid along the second dimension.
             * \return The wrapped grid's second-dimension size.
             */
            SizeType getSize2() const
            {
                return data.getSize2();
            }

            /**
             * \brief Returns the size of the wrapped grid along the third dimension.
             * \return The wrapped grid's third-dimension size.
             */
            SizeType getSize3() const
            {
                return data.getSize3();
            }

            /**
             * \brief Returns the maximum total number of cells the wrapped grid can hold.
             * \return The wrapped grid's maximum total cell capacity.
             */
            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            /**
             * \brief Returns the maximum size of the wrapped grid along the first dimension.
             * \return The wrapped grid's maximum first-dimension size.
             */
            SizeType getMaxSize1() const
            {
                return data.getMaxSize1();
            }

            /**
             * \brief Returns the maximum size of the wrapped grid along the second dimension.
             * \return The wrapped grid's maximum second-dimension size.
             */
            SizeType getMaxSize2() const
            {
                return data.getMaxSize2();
            }

            /**
             * \brief Returns the maximum size of the wrapped grid along the third dimension.
             * \return The wrapped grid's maximum third-dimension size.
             */
            SizeType getMaxSize3() const
            {
                return data.getMaxSize3();
            }

            /**
             * \brief Tells whether the wrapped grid is empty (zero cells along any dimension).
             * \return \c true if the wrapped grid is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.isEmpty();
            }

            /**
             * \brief Returns a \c const reference to the wrapped grid.
             * \return A \c const reference to the wrapped grid.
             */
            const GridType& getData() const
            {
                return data;
            }

            /**
             * \brief Returns a mutable reference to the wrapped grid.
             * \return A mutable reference to the wrapped grid.
             */
            GridType& getData()
            {
                return data;
            }

            /**
             * \brief Copies the cells of \a r into the wrapped grid.
             * \param r The source reference.
             * \return A reference to itself.
             */
            GridReference& operator=(const GridReference& r)
            {
                data.operator=(r.data);
                return *this;
            }

            /**
             * \brief Assigns the grid expression \a e to the wrapped grid.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            GridReference& operator=(const GridExpression<E>& e)
            {
                data.operator=(e);
                return *this;
            }

            /**
             * \brief Adds the grid expression \a e cell-wise to the wrapped grid.
             * \tparam E The source grid expression type.
             * \param e The grid expression to add.
             * \return A reference to itself.
             */
            template <typename E>
            GridReference& operator+=(const GridExpression<E>& e)
            {
                data.operator+=(e);
                return *this;
            }

            /**
             * \brief Subtracts the grid expression \a e cell-wise from the wrapped grid.
             * \tparam E The source grid expression type.
             * \param e The grid expression to subtract.
             * \return A reference to itself.
             */
            template <typename E>
            GridReference& operator-=(const GridExpression<E>& e)
            {
                data.operator-=(e);
                return *this;
            }

            /**
             * \brief Multiplies every cell of the wrapped grid by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, GridReference>::type& operator*=(const T& t)
            {
                data.operator*=(t);
                return *this;
            }

            /**
             * \brief Divides every cell of the wrapped grid by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, GridReference>::type& operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            /**
             * \brief Assigns the grid expression \a e to the wrapped grid without intermediate temporary
             *        (use only when \a e does not alias the wrapped grid).
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            GridReference& assign(const GridExpression<E>& e)
            {
                data.assign(e);
                return *this;
            }

            /**
             * \brief Adds the grid expression \a e to the wrapped grid without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            GridReference& plusAssign(const GridExpression<E>& e)
            {
                data.plusAssign(e);
                return *this;
            }

            /**
             * \brief Subtracts the grid expression \a e from the wrapped grid without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            GridReference& minusAssign(const GridExpression<E>& e)
            {
                data.minusAssign(e);
                return *this;
            }

            /**
             * \brief Swaps the contents of the wrapped grid with those of the grid wrapped by \a r.
             * \param r The reference to swap with.
             */
            void swap(GridReference& r)
            {
                data.swap(r.data);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param r1 The first reference.
             * \param r2 The second reference.
             */
            friend void swap(GridReference& r1, GridReference& r2)
            {
                r1.swap(r2);
            }

          private:
            GridType& data;
        };

        /**
         * \brief Dynamically-sized dense 3D grid (\f$ d_1 \times d_2 \times d_3 \f$) with configurable underlying storage.
         * \tparam T The scalar value type.
         * \tparam A The underlying storage container type (default: \c std::vector).
         */
        template <typename T, typename A = std::vector<T> >
        class Grid : public GridContainer<Grid<T, A> >
        {

            typedef Grid<T, A> SelfType;

          public:
            /**
             * \brief The scalar value type stored in the grid.
             */
            typedef T                                   ValueType;

            /**
             * \brief Mutable reference type to an element.
             */
            typedef T&                                  Reference;

            /**
             * \brief Constant reference type to an element.
             */
            typedef const T&                            ConstReference;

            /**
             * \brief The unsigned size type used by the underlying storage container.
             */
            typedef typename A::size_type               SizeType;

            /**
             * \brief The signed difference type used by the underlying storage container.
             */
            typedef typename A::difference_type         DifferenceType;

            /**
             * \brief The underlying storage container type.
             */
            typedef A                                   ArrayType;

            /**
             * \brief Pointer type for raw element access.
             */
            typedef T*                                  Pointer;

            /**
             * \brief Constant pointer type for raw element access.
             */
            typedef const T*                            ConstPointer;

            /**
             * \brief Closure type used when this grid appears inside another expression.
             */
            typedef GridReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this grid appears inside another expression.
             */
            typedef const GridReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary grid type used by expression-template machinery.
             */
            typedef SelfType                            GridTemporaryType;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Grid instances.
             */
            typedef std::shared_ptr<SelfType>           SharedPointer;

            /**
             * \brief Constructs an empty grid (zero size on every axis).
             */
            Grid():
                data(), size1(0), size2(0), size3(0) {}

            /**
             * \brief Constructs an \e m &times; \e n &times; \e o grid with default-initialized elements.
             * \param m The size along the first axis.
             * \param n The size along the second axis.
             * \param o The size along the third axis.
             */
            Grid(SizeType m, SizeType n, SizeType o):
                data(storageSize(m, n, o)), size1(m), size2(n), size3(o) {}

            /**
             * \brief Constructs an \e m &times; \e n &times; \e o grid with every element initialized to \a v.
             * \param m The size along the first axis.
             * \param n The size along the second axis.
             * \param o The size along the third axis.
             * \param v The element value used to initialize every cell.
             */
            Grid(SizeType m, SizeType n, SizeType o, const ValueType& v):
                data(storageSize(m, n, o), v), size1(m), size2(n), size3(o) {}

            /**
             * \brief Constructs a copy of the grid \a g.
             * \param g The grid to copy.
             */
            Grid(const Grid& g):
                data(g.data), size1(g.size1), size2(g.size2), size3(g.size3) {}

            /**
             * \brief Move-constructs a grid from \a g (\a g is left in a valid empty state).
             * \param g The grid to move from.
             */
            Grid(Grid&& g):
                data(), size1(0), size2(0), size3(0)
            {
                swap(g);
            }

            /**
             * \brief Constructs the grid from the grid expression \a e (materializing the expression result).
             * \tparam E The grid expression type.
             * \param e The grid expression to materialize.
             */
            template <typename E>
            Grid(const GridExpression<E>& e):
                data(storageSize(e().getSize1(), e().getSize2(), e().getSize3())), size1(e().getSize1()), size2(e().getSize2()), size3(e().getSize3())
            {
                gridAssignGrid<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable reference to the element at linear index \a i.
             * \param i The zero-based linear index.
             * \return A mutable reference to the cell.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Returns a \c const reference to the element at linear index \a i.
             * \param i The zero-based linear index.
             * \return A \c const reference to the cell.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Returns a mutable reference to the element at (\a i, \a j, \a k).
             * \param i The zero-based first-axis index.
             * \param j The zero-based second-axis index.
             * \param k The zero-based third-axis index.
             * \return A mutable reference to the cell.
             * \throw Base::IndexError if any of the indices is out of range.
             */
            Reference operator()(SizeType i, SizeType j, SizeType k)
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
                return data[(k * getSize2() + j) * getSize1() + i];
            }

            /**
             * \brief Returns a \c const reference to the element at (\a i, \a j, \a k).
             * \param i The zero-based first-axis index.
             * \param j The zero-based second-axis index.
             * \param k The zero-based third-axis index.
             * \return A \c const reference to the cell.
             * \throw Base::IndexError if any of the indices is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
                return data[(k * getSize2() + j) * getSize1() + i];
            }

            /**
             * \brief Tells whether the grid is empty.
             * \return \c true if the underlying storage holds no elements, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.empty();
            }

            /**
             * \brief Returns the total cell count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
             * \return The total number of cells.
             */
            SizeType getSize() const
            {
                return (size1 * size2 * size3);
            }

            /**
             * \brief Returns the first-axis size.
             * \return The size along the first axis.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the second-axis size.
             * \return The size along the second axis.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the third-axis size.
             * \return The size along the third axis.
             */
            SizeType getSize3() const
            {
                return size3;
            }

            /**
             * \brief Returns the maximum total cell count the underlying storage container can hold.
             * \return The maximum cell count.
             */
            SizeType getMaxSize() const
            {
                return data.max_size();
            }

            /**
             * \brief Returns a mutable reference to the underlying storage container.
             * \return A mutable reference to the storage container.
             */
            ArrayType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the underlying storage container.
             * \return A \c const reference to the storage container.
             */
            const ArrayType& getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the contents of \a g to this grid.
             * \param g The source grid.
             * \return A reference to itself.
             */
            Grid& operator=(const Grid& g)
            {
                data  = g.data;
                size1 = g.size1;
                size2 = g.size2;
                size3 = g.size3;
                return *this;
            }

            /**
             * \brief Move-assigns the contents of \a g to this grid.
             * \param g The source grid (left in a valid but unspecified state).
             * \return A reference to itself.
             */
            Grid& operator=(Grid&& g)
            {
                swap(g);
                return *this;
            }

            /**
             * \brief Assigns the contents of the grid container \a c to this grid (no alias check needed).
             * \tparam C The source grid container type.
             * \param c The source grid container.
             * \return A reference to itself.
             */
            template <typename C>
            Grid& operator=(const GridContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the grid expression \a e to this grid (via a temporary to handle aliasing).
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            Grid& operator=(const GridExpression<E>& e)
            {
                Grid tmp(e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Adds the contents of the grid container \a c cell-wise to this grid (no alias check needed).
             * \tparam C The source grid container type.
             * \param c The source grid container.
             * \return A reference to itself.
             */
            template <typename C>
            Grid& operator+=(const GridContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the grid expression \a e cell-wise to this grid (via a temporary to handle aliasing).
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            Grid& operator+=(const GridExpression<E>& e)
            {
                Grid tmp(*this + e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the grid container \a c cell-wise from this grid (no alias check needed).
             * \tparam C The source grid container type.
             * \param c The source grid container.
             * \return A reference to itself.
             */
            template <typename C>
            Grid& operator-=(const GridContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the grid expression \a e cell-wise from this grid (via a temporary to handle aliasing).
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            Grid& operator-=(const GridExpression<E>& e)
            {
                Grid tmp(*this - e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Multiplies every cell by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Grid>::type& operator*=(const T1& t)
            {
                gridAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every cell by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Grid>::type& operator/=(const T1& t)
            {
                gridAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Resizes this grid to match \a e and assigns its cells without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            Grid& assign(const GridExpression<E>& e)
            {
                resize(e().getSize1(), e().getSize2(), false);
                gridAssignGrid<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the cells of the grid expression \a e to this grid without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            Grid& plusAssign(const GridExpression<E>& e)
            {
                gridAssignGrid<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the cells of the grid expression \a e from this grid without intermediate temporary.
             * \tparam E The source grid expression type.
             * \param e The source grid expression.
             * \return A reference to itself.
             */
            template <typename E>
            Grid& minusAssign(const GridExpression<E>& e)
            {
                gridAssignGrid<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Swaps the contents of this grid with those of \a g.
             * \param g The grid to swap with.
             */
            void swap(Grid& g)
            {
                if (this != &g) {
                    std::swap(data, g.data);
                    std::swap(size1, g.size1);
                    std::swap(size2, g.size2);
                    std::swap(size3, g.size3);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param g1 The first grid.
             * \param g2 The second grid.
             */
            friend void swap(Grid& g1, Grid& g2)
            {
                g1.swap(g2);
            }

            /**
             * \brief Sets every cell of the grid to the value \a v.
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                std::fill(data.begin(), data.end(), v);
            }

            /**
             * \brief Resizes the grid to \f$ m \times n \times o \f$ cells.
             * \param m The new first-axis size.
             * \param n The new second-axis size.
             * \param o The new third-axis size.
             * \param preserve If \c true, existing cell values at indices that remain valid are kept. If \c false, all cells are set to \a v.
             * \param v The fill value for newly added cells (or for all cells when \a preserve is \c false).
             */
            void resize(SizeType m, SizeType n, SizeType o, bool preserve = true, const ValueType& v = ValueType())
            {
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
            static SizeType storageSize(SizeType m, SizeType n, SizeType o)
            {
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

        /**
         * \brief Constant grid expression whose cells are all zero.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ZeroGrid : public GridContainer<ZeroGrid<T> >
        {

            typedef ZeroGrid<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                   ValueType;

            /**
             * \brief Reference type (always a \c const reference — all cells are zero).
             */
            typedef const T&                            Reference;

            /**
             * \brief Constant reference type to the zero element.
             */
            typedef const T&                            ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                         SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                      DifferenceType;

            /**
             * \brief Closure type used when this grid appears inside another expression.
             */
            typedef GridReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this grid appears inside another expression.
             */
            typedef const GridReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary grid type used by expression-template machinery.
             */
            typedef Grid<T>                             GridTemporaryType;

            /**
             * \brief Constructs an empty zero grid (zero size on every axis).
             */
            ZeroGrid():
                size1(0), size2(0), size3(0) {}

            /**
             * \brief Constructs a zero grid of size \f$ m \times n \times o \f$.
             * \param m The first-axis size.
             * \param n The second-axis size.
             * \param o The third-axis size.
             */
            ZeroGrid(SizeType m, SizeType n, SizeType o):
                size1(m), size2(n), size3(o) {}

            /**
             * \brief Constructs a copy of the zero grid \a m.
             * \param m The zero grid to copy.
             */
            ZeroGrid(const ZeroGrid& m):
                size1(m.size1), size2(m.size2), size3(m.size3) {}

            /**
             * \brief Returns a \c const reference to the zero element (linear-index form).
             * \param i The zero-based linear index.
             * \return A \c const reference to the zero element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
                return zero;
            }

            /**
             * \brief Returns a \c const reference to the zero element (3D-index form).
             * \param i The zero-based first-axis index.
             * \param j The zero-based second-axis index.
             * \param k The zero-based third-axis index.
             * \return A \c const reference to the zero element.
             * \throw Base::IndexError if any of the indices is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
                return zero;
            }

            /**
             * \brief Tells whether the grid is empty (any axis has zero size).
             * \return \c true if any axis is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0 || size3 == 0);
            }

            /**
             * \brief Returns the total cell count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
             * \return The total number of cells.
             */
            SizeType getSize() const
            {
                return (size1 * size2 * size3);
            }

            /**
             * \brief Returns the first-axis size.
             * \return The size along the first axis.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the second-axis size.
             * \return The size along the second axis.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the third-axis size.
             * \return The size along the third axis.
             */
            SizeType getSize3() const
            {
                return size3;
            }

            /**
             * \brief Returns the maximum representable first-axis size.
             * \return The maximum first-axis size.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable second-axis size.
             * \return The maximum second-axis size.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable third-axis size.
             * \return The maximum third-axis size.
             */
            SizeType getMaxSize3() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the axis sizes from \a g.
             * \param g The source zero grid.
             * \return A reference to itself.
             */
            ZeroGrid& operator=(const ZeroGrid& g)
            {
                if (this != &g) {
                    size1 = g.size1;
                    size2 = g.size2;
                    size3 = g.size3;
                }

                return *this;
            }

            /**
             * \brief Swaps the axis sizes with \a g.
             * \param g The zero grid to swap with.
             */
            void swap(ZeroGrid& g)
            {
                if (this != &g) {
                    std::swap(size1, g.size1);
                    std::swap(size2, g.size2);
                    std::swap(size3, g.size3);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param g1 The first zero grid.
             * \param g2 The second zero grid.
             */
            friend void swap(ZeroGrid& g1, ZeroGrid& g2)
            {
                g1.swap(g2);
            }

            /**
             * \brief Resizes the grid axes to (\a m, \a n, \a o).
             * \param m The new first-axis size.
             * \param n The new second-axis size.
             * \param o The new third-axis size.
             */
            void resize(SizeType m, SizeType n, SizeType o)
            {
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

        template <typename T>
        const typename ZeroGrid<T>::ValueType ZeroGrid<T>::zero = ZeroGrid<T>::ValueType();

        /**
         * \brief Constant grid expression in which every cell equals the same scalar value.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ScalarGrid : public GridContainer<ScalarGrid<T> >
        {

            typedef ScalarGrid<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                   ValueType;

            /**
             * \brief Reference type (always a \c const reference — cells are immutable).
             */
            typedef const T&                            Reference;

            /**
             * \brief Constant reference type to a cell.
             */
            typedef const T&                            ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                         SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                      DifferenceType;

            /**
             * \brief Closure type used when this grid appears inside another expression.
             */
            typedef GridReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this grid appears inside another expression.
             */
            typedef const GridReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary grid type used by expression-template machinery.
             */
            typedef Grid<T>                             GridTemporaryType;

            /**
             * \brief Constructs an empty scalar grid.
             */
            ScalarGrid():
                size1(0), size2(0), size3(0), value() {}

            /**
             * \brief Constructs a scalar grid of size \f$ m \times n \times o \f$ in which every cell equals \a v.
             * \param m The first-axis size.
             * \param n The second-axis size.
             * \param o The third-axis size.
             * \param v The common cell value.
             */
            ScalarGrid(SizeType m, SizeType n, SizeType o, const ValueType& v = ValueType()):
                size1(m), size2(n), size3(o), value(v) {}

            /**
             * \brief Constructs a copy of the scalar grid \a m.
             * \param m The scalar grid to copy.
             */
            ScalarGrid(const ScalarGrid& m):
                size1(m.size1), size2(m.size2), size3(m.size3), value(m.value) {}

            /**
             * \brief Returns a \c const reference to the common cell value (linear-index form).
             * \param i The zero-based linear index.
             * \return A \c const reference to the common cell value.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < (getSize1() * getSize2() * getSize3()), "Index out of range", Base::IndexError);
                return value;
            }

            /**
             * \brief Returns a \c const reference to the common cell value (3D-index form).
             * \param i The zero-based first-axis index.
             * \param j The zero-based second-axis index.
             * \param k The zero-based third-axis index.
             * \return A \c const reference to the common cell value.
             * \throw Base::IndexError if any of the indices is out of range.
             */
            ConstReference operator()(SizeType i, SizeType j, SizeType k) const
            {
                CDPL_MATH_CHECK(i < getSize1() && j < getSize2() && k < getSize3(), "Index out of range", Base::IndexError);
                return value;
            }

            /**
             * \brief Tells whether the grid is empty (any axis has zero size).
             * \return \c true if any axis is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size1 == 0 || size2 == 0 || size3 == 0);
            }

            /**
             * \brief Returns the total cell count \f$ \mathrm{size}_1 \cdot \mathrm{size}_2 \cdot \mathrm{size}_3 \f$.
             * \return The total number of cells.
             */
            SizeType getSize() const
            {
                return (size1 * size2 * size3);
            }

            /**
             * \brief Returns the first-axis size.
             * \return The size along the first axis.
             */
            SizeType getSize1() const
            {
                return size1;
            }

            /**
             * \brief Returns the second-axis size.
             * \return The size along the second axis.
             */
            SizeType getSize2() const
            {
                return size2;
            }

            /**
             * \brief Returns the third-axis size.
             * \return The size along the third axis.
             */
            SizeType getSize3() const
            {
                return size3;
            }

            /**
             * \brief Returns the maximum representable first-axis size.
             * \return The maximum first-axis size.
             */
            SizeType getMaxSize1() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable second-axis size.
             * \return The maximum second-axis size.
             */
            SizeType getMaxSize2() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Returns the maximum representable third-axis size.
             * \return The maximum third-axis size.
             */
            SizeType getMaxSize3() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the axis sizes and common value from \a g.
             * \param g The source scalar grid.
             * \return A reference to itself.
             */
            ScalarGrid& operator=(const ScalarGrid& g)
            {
                if (this != &g) {
                    size1 = g.size1;
                    size2 = g.size2;
                    size3 = g.size3;
                    value = g.value;
                }

                return *this;
            }

            /**
             * \brief Swaps the axis sizes and common value with \a g.
             * \param g The scalar grid to swap with.
             */
            void swap(ScalarGrid& g)
            {
                if (this != &g) {
                    std::swap(size1, g.size1);
                    std::swap(size2, g.size2);
                    std::swap(size3, g.size3);
                    std::swap(value, g.value);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param g1 The first scalar grid.
             * \param g2 The second scalar grid.
             */
            friend void swap(ScalarGrid& g1, ScalarGrid& g2)
            {
                g1.swap(g2);
            }

            /**
             * \brief Resizes the grid axes to (\a m, \a n, \a o).
             * \param m The new first-axis size.
             * \param n The new second-axis size.
             * \param o The new third-axis size.
             */
            void resize(SizeType m, SizeType n, SizeType o)
            {
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

        /**
         * \brief Math::GridTemporaryTraits specialization inheriting the temporary type of the underlying grid for a Math::GridReference view.
         * \tparam G The underlying grid type.
         */
        template <typename G>
        struct GridTemporaryTraits<GridReference<G> > : public GridTemporaryTraits<G>
        {};

        /**
         * \brief Math::GridTemporaryTraits specialization inheriting the temporary type of the underlying grid for a \c const Math::GridReference view.
         * \tparam G The underlying grid type.
         */
        template <typename G>
        struct GridTemporaryTraits<const GridReference<G> > : public GridTemporaryTraits<G>
        {};

        /**
         * \brief Immutable grid where all elements have the value zero of type <tt>float</tt>.
         */
        typedef ZeroGrid<float>  FZeroGrid;
        
        /**
         * \brief Immutable grid where all elements have the value zero of type <tt>double</tt>.
         */
        typedef ZeroGrid<double> DZeroGrid;

        /**
         * \brief Immutable grid where all elements have the same value of type <tt>float</tt>.
         */
        typedef ScalarGrid<float>  FScalarGrid;
        
        /**
         * \brief Immutable grid where all elements have the same value of type <tt>double</tt>.
         */
        typedef ScalarGrid<double> DScalarGrid;

        /**
         * \brief Unbounded dense grid storing floating-point values of type <tt>float</tt>.
         */
        typedef Grid<float> FGrid;

        /**
         * \brief Unbounded dense grid storing floating-point values of type <tt>double</tt>.
         */
        typedef Grid<double> DGrid;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_GRID_HPP
