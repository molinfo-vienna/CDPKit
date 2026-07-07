/* 
 * Vector.hpp 
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
 * \brief Definition of vector data types.
 */

#ifndef CDPL_MATH_VECTOR_HPP
#define CDPL_MATH_VECTOR_HPP

#include <cstddef>
#include <algorithm>
#include <vector>
#include <limits>
#include <utility>
#include <unordered_map>
#include <type_traits>
#include <initializer_list>
#include <memory>

#include "CDPL/Math/Check.hpp"
#include "CDPL/Math/VectorExpression.hpp"
#include "CDPL/Math/VectorAssignment.hpp"
#include "CDPL/Math/DirectAssignmentProxy.hpp"
#include "CDPL/Math/Functional.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/SparseContainerElement.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

    namespace Math
    {

        /**
         * \brief Lightweight vector expression that proxies a reference to an underlying vector container.
         * \tparam V The wrapped vector type.
         */
        template <typename V>
        class VectorReference : public VectorExpression<VectorReference<V> >
        {

            typedef VectorReference<V> SelfType;

          public:
            /**
             * \brief The wrapped vector type.
             */
            typedef V                                                      VectorType;

            /**
             * \brief The element value type of the wrapped vector.
             */
            typedef typename V::ValueType                                  ValueType;

            /**
             * \brief Mutable element reference type (degrades to ConstReference when the wrapped vector is \c const).
             */
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstReference,
                                              typename V::Reference>::type Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef typename V::ConstReference                             ConstReference;

            /**
             * \brief The unsigned size type of the wrapped vector.
             */
            typedef typename V::SizeType                                   SizeType;

            /**
             * \brief The signed difference type of the wrapped vector.
             */
            typedef typename V::DifferenceType                             DifferenceType;

            /**
             * \brief Closure type used when this proxy appears inside another expression.
             */
            typedef SelfType                                               ClosureType;

            /**
             * \brief Constant closure type used when this proxy appears inside another expression.
             */
            typedef const SelfType                                         ConstClosureType;

            /**
             * \brief Constructs the reference proxy referring to \a v.
             * \param v The wrapped vector to proxy.
             */
            explicit VectorReference(VectorType& v):
                data(v) {}

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             */
            Reference operator[](SizeType i)
            {
                return data[i];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             */
            ConstReference operator[](SizeType i) const
            {
                return data[i];
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             */
            Reference operator()(SizeType i)
            {
                return data(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             */
            ConstReference operator()(SizeType i) const
            {
                return data(i);
            }

            /**
             * \brief Returns the wrapped vector's element count.
             * \return The number of elements.
             */
            SizeType getSize() const
            {
                return data.getSize();
            }

            /**
             * \brief Returns the wrapped vector's capacity (maximum element count without reallocation).
             * \return The maximum element count.
             */
            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            /**
             * \brief Tells whether the wrapped vector is empty.
             * \return \c true if the wrapped vector has zero elements, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.isEmpty();
            }

            /**
             * \brief Returns a \c const reference to the wrapped vector.
             * \return A \c const reference to the wrapped vector.
             */
            const VectorType& getData() const
            {
                return data;
            }

            /**
             * \brief Returns a reference to the wrapped vector.
             * \return A reference to the wrapped vector.
             */
            VectorType& getData()
            {
                return data;
            }

            /**
             * \brief Copy-assigns the wrapped vector from the vector referenced by \a r.
             * \param r The source reference proxy.
             * \return A reference to itself.
             */
            VectorReference& operator=(const VectorReference& r)
            {
                data.operator=(r.data);
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to the wrapped vector.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorReference& operator=(const VectorExpression<E>& e)
            {
                data.operator=(e);
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e element-wise to the wrapped vector.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorReference& operator+=(const VectorExpression<E>& e)
            {
                data.operator+=(e);
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e element-wise from the wrapped vector.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorReference& operator-=(const VectorExpression<E>& e)
            {
                data.operator-=(e);
                return *this;
            }

            /**
             * \brief Multiplies every element of the wrapped vector by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorReference>::type& operator*=(const T& t)
            {
                data.operator*=(t);
                return *this;
            }

            /**
             * \brief Divides every element of the wrapped vector by the scalar \a t.
             * \tparam T The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorReference>::type& operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            /**
             * \brief Assigns the vector expression \a e to the wrapped vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorReference& assign(const VectorExpression<E>& e)
            {
                data.assign(e);
                return *this;
            }

            /**
             * \brief Adds the vector expression \a e to the wrapped vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorReference& plusAssign(const VectorExpression<E>& e)
            {
                data.plusAssign(e);
                return *this;
            }

            /**
             * \brief Subtracts the vector expression \a e from the wrapped vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            VectorReference& minusAssign(const VectorExpression<E>& e)
            {
                data.minusAssign(e);
                return *this;
            }

            /**
             * \brief Swaps the contents of the two wrapped vectors.
             * \param r The reference proxy to swap with.
             */
            void swap(VectorReference& r)
            {
                data.swap(r.data);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param r1 The first reference proxy.
             * \param r2 The second reference proxy.
             */
            friend void swap(VectorReference& r1, VectorReference& r2)
            {
                r1.swap(r2);
            }

          private:
            VectorType& data;
        };

        template <typename T, typename A>
        class Vector;

        /**
         * \brief Lightweight vector container that wraps a \c std::initializer_list for construction-style initialization.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class InitListVector : public VectorContainer<InitListVector<T> >
        {

          public:
            typedef InitListVector                                SelfType;

            /**
             * \brief The wrapped \c std::initializer_list type.
             */
            typedef std::initializer_list<T>                      InitializerListType;

            /**
             * \brief The scalar value type.
             */
            typedef typename InitializerListType::value_type      ValueType;

            /**
             * \brief Constant element reference type.
             */
            typedef typename InitializerListType::const_reference ConstReference;

            /**
             * \brief Mutable element reference type (degrades to ConstReference for the immutable initializer list).
             */
            typedef typename InitializerListType::reference       Reference;

            /**
             * \brief The unsigned size type.
             */
            typedef typename InitializerListType::size_type       SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef typename std::ptrdiff_t                       DifferenceType;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef SelfType                                      ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const SelfType                                ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery.
             */
            typedef Vector<T, std::vector<T> >                    VectorTemporaryType;

            /**
             * \brief Constructs the vector by wrapping the initializer list \a l (no copy).
             * \param l The initializer list to wrap.
             */
            InitListVector(InitializerListType l):
                list(l) {}

            /**
             * \brief Returns a reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return *(list.begin() + i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return *(list.begin() + i);
            }

            /**
             * \brief Returns the size of the wrapped initializer list.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return list.size();
            }

            /**
             * \brief Tells whether the wrapped initializer list is empty.
             * \return \c true if the list is empty, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (list.size() == 0);
            }

          private:
            InitializerListType list;
        };

        /**
         * \brief Dynamically-sized dense vector with configurable underlying storage.
         * \tparam T The scalar value type.
         * \tparam A The underlying storage container type (default: \c std::vector).
         */
        template <typename T, typename A = std::vector<T> >
        class Vector : public VectorContainer<Vector<T, A> >
        {

            typedef Vector<T, A> SelfType;

          public:
            /**
             * \brief The scalar value type stored in the vector.
             */
            typedef T                                     ValueType;

            /**
             * \brief Mutable element reference type.
             */
            typedef T&                                    Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T&                              ConstReference;

            /**
             * \brief The unsigned size type used by the underlying storage container.
             */
            typedef typename A::size_type                 SizeType;

            /**
             * \brief The signed difference type used by the underlying storage container.
             */
            typedef typename A::difference_type           DifferenceType;

            /**
             * \brief The underlying storage container type.
             */
            typedef A                                     ArrayType;

            /**
             * \brief Pointer type for raw element access.
             */
            typedef T*                                    Pointer;

            /**
             * \brief Constant pointer type for raw element access.
             */
            typedef const T*                              ConstPointer;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery.
             */
            typedef SelfType                              VectorTemporaryType;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Vector instances.
             */
            typedef std::shared_ptr<SelfType>             SharedPointer;

            /**
             * \brief Type of the brace-initializer list accepted by the corresponding constructor.
             */
            typedef std::initializer_list<T>              InitializerListType;

            /**
             * \brief Constructs an empty vector (size zero).
             */
            Vector():
                data() {}

            /**
             * \brief Constructs a vector of size \a n with default-initialized elements.
             * \param n The desired vector size.
             */
            explicit Vector(SizeType n):
                data(storageSize(n)) {}

            /**
             * \brief Constructs a vector of size \a n with every element initialized to \a v.
             * \param n The desired vector size.
             * \param v The value used for element initialization.
             */
            Vector(SizeType n, const ValueType& v):
                data(storageSize(n), v) {}

            /**
             * \brief Constructs a vector that copies its data directly from the underlying-array container \a data.
             * \param data The source storage container.
             */
            Vector(const ArrayType& data):
                data(data) {}

            /**
             * \brief Constructs a copy of the vector \a v.
             * \param v The vector to copy.
             */
            Vector(const Vector& v):
                data(v.data) {}

            /**
             * \brief Move-constructs a vector from \a v (\a v is left in a valid empty state).
             * \param v The vector to move from.
             */
            Vector(Vector&& v):
                data(std::move(v.data)) {}

            /**
             * \brief Constructs the vector from a brace-initializer list \a l.
             * \param l The initializer list (one element per vector entry).
             */
            Vector(InitializerListType l):
                data(l) {}

            /**
             * \brief Constructs the vector from the vector expression \a e (materializing the expression result).
             * \tparam E The vector expression type.
             * \param e The vector expression to materialize.
             */
            template <typename E>
            Vector(const VectorExpression<E>& e):
                data(storageSize(e().getSize()))
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Tells whether the vector is empty.
             * \return \c true if the vector contains no elements, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return data.empty();
            }

            /**
             * \brief Returns the current element count.
             * \return The number of elements.
             */
            SizeType getSize() const
            {
                return data.size();
            }

            /**
             * \brief Returns the maximum number of elements the underlying storage container can hold.
             * \return The maximum element count.
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
             * \brief Copy-assigns the elements of \a v to this vector.
             * \param v The source vector.
             * \return A reference to itself.
             */
            Vector& operator=(const Vector& v)
            {
                data = v.data;
                return *this;
            }

            /**
             * \brief Move-assigns the elements of \a v to this vector.
             * \param v The source vector (left in a valid but unspecified state).
             * \return A reference to itself.
             */
            Vector& operator=(Vector&& v)
            {
                data = std::move(v.data);
                return *this;
            }

            /**
             * \brief Assigns the contents of the initializer list \a l to this vector (resizes to fit).
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             */
            Vector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the contents of the vector container \a c to this vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            Vector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the vector expression \a e to this vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            Vector& operator=(const VectorExpression<E>& e)
            {
                Vector tmp(e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Adds the contents of the vector container \a c element-wise to this vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            Vector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this vector.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            Vector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the vector expression \a e element-wise to this vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            Vector& operator+=(const VectorExpression<E>& e)
            {
                Vector tmp(*this + e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the vector container \a c element-wise from this vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            Vector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this vector.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            Vector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the vector expression \a e element-wise from this vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            Vector& operator-=(const VectorExpression<E>& e)
            {
                Vector tmp(*this - e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Multiplies every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Vector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Vector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Resizes this vector to match \a e and assigns the elements of \a e without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            Vector& assign(const VectorExpression<E>& e)
            {
                resize(e().getSize());
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Assigns the contents of the initializer list \a l to this vector.
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             */
            Vector& assign(InitializerListType l)
            {
                data = l;
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            Vector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this vector without intermediate temporary.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            Vector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            Vector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this vector without intermediate temporary.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            Vector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this vector with those of \a v.
             * \param v The vector to swap with.
             */
            void swap(Vector& v)
            {
                if (this != &v)
                    std::swap(data, v.data);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first vector.
             * \param v2 The second vector.
             */
            friend void swap(Vector& v1, Vector& v2)
            {
                v1.swap(v2);
            }

            /**
             * \brief Sets every element of the vector to the value \a v.
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                std::fill(data.begin(), data.end(), v);
            }

            /**
             * \brief Resizes the vector to \a n elements.
             * \param n The new element count.
             * \param v The fill value for newly added elements.
             */
            void resize(SizeType n, const ValueType& v = ValueType())
            {
                data.resize(storageSize(n), v);
            }

          private:
            SizeType storageSize(SizeType n)
            {
                return CDPL_MATH_CHECK_MAX_SIZE(n, data.max_size(), Base::SizeError);
            }

            ArrayType data;
        };

        /**
         * \brief Sparse vector that stores only non-default entries in an associative key-to-value container.
         * \tparam T The scalar value type.
         * \tparam A The underlying associative container type (default: \c std::unordered_map).
         */
        template <typename T, typename A = std::unordered_map<std::size_t, T> >
        class SparseVector : public VectorContainer<SparseVector<T, A> >
        {

            typedef SparseVector<T> SelfType;

          public:
            /**
             * \brief The scalar value type stored in the vector.
             */
            typedef T                                         ValueType;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                               SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                            DifferenceType;

            /**
             * \brief The key type used by the underlying associative container.
             */
            typedef typename A::key_type                      KeyType;

            /**
             * \brief Constant reference type to a stored element value.
             */
            typedef const T&                                  ConstReference;

            /**
             * \brief Mutable element reference type (a proxy object that inserts on assignment to a previously-absent key).
             */
            typedef SparseContainerElement<SelfType, KeyType> Reference;

            /**
             * \brief The underlying associative container type.
             */
            typedef A                                         ArrayType;

            /**
             * \brief Pointer type for raw access to stored entries.
             */
            typedef T*                                        Pointer;

            /**
             * \brief Constant pointer type for raw access to stored entries.
             */
            typedef const T*                                  ConstPointer;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>                 ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType>     ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery.
             */
            typedef SelfType                                  VectorTemporaryType;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %SparseVector instances.
             */
            typedef std::shared_ptr<SelfType>                 SharedPointer;

            /**
             * \brief The initializer list type accepted by constructors and assignment.
             */
            typedef std::initializer_list<T>                  InitializerListType;

            /**
             * \brief Constructs an empty sparse vector (size zero, no stored entries).
             */
            SparseVector():
                data(), size(0) {}

            /**
             * \brief Constructs a sparse vector of size \a n with no stored entries (every position reads as the default value).
             * \param n The logical element count.
             */
            explicit SparseVector(SizeType n):
                data(), size(storageSize(n)) {}

            /**
             * \brief Constructs a copy of the sparse vector \a v.
             * \param v The sparse vector to copy.
             */
            SparseVector(const SparseVector& v):
                data(v.data), size(v.size) {}

            /**
             * \brief Move-constructs from \a v (\a v is left in a valid empty state).
             * \param v The sparse vector to move from.
             */
            SparseVector(SparseVector&& v):
                data(), size(0)
            {
                swap(v);
            }

            /**
             * \brief Constructs a sparse vector with the contents of the initializer list \a l.
             * \param l The initializer list providing the initial elements.
             */
            SparseVector(InitializerListType l)
            {
                assign(l);
            }

            /**
             * \brief Constructs a sparse vector from the vector expression \a e.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             */
            template <typename E>
            SparseVector(const VectorExpression<E>& e):
                data(), size(0)
            {
                assign(e);
            }

            /**
             * \brief Returns a mutable proxy reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable proxy reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element (or to the zero element if no entry is stored at \a i).
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a mutable proxy reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable proxy reference (creates a stored entry on first assignment).
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return Reference(*this, i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the stored value, or to the zero element if no entry exists at \a i.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);

                typename ArrayType::const_iterator it = data.find(i);

                if (it == data.end())
                    return zero;

                return it->second;
            }

            /**
             * \brief Returns the number of explicitly stored (non-default) entries.
             * \return The number of stored entries.
             */
            SizeType getNumElements() const
            {
                return data.size();
            }

            /**
             * \brief Tells whether the vector's logical size is zero.
             * \return \c true if the logical size is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the logical element count.
             * \return The number of elements.
             */
            SizeType getSize() const
            {
                return size;
            }

            /**
             * \brief Returns the maximum number of stored entries the underlying associative container can hold.
             * \return The maximum entry count.
             */
            SizeType getMaxSize() const
            {
                return std::min(SizeType(data.max_size()), std::numeric_limits<SizeType>::max());
            }

            /**
             * \brief Returns a mutable reference to the underlying associative container of stored entries.
             * \return A mutable reference to the storage container.
             */
            ArrayType& getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const reference to the underlying associative container of stored entries.
             * \return A \c const reference to the storage container.
             */
            const ArrayType& getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the contents of \a v to this sparse vector.
             * \param v The source sparse vector.
             * \return A reference to itself.
             */
            SparseVector& operator=(const SparseVector& v)
            {
                data = v.data;
                size = v.size;
                return *this;
            }

            /**
             * \brief Move-assigns the contents of \a v to this sparse vector.
             * \param v The source sparse vector (left in a valid but unspecified state).
             * \return A reference to itself.
             */
            SparseVector& operator=(SparseVector&& v)
            {
                swap(v);
                return *this;
            }

            /**
             * \brief Assigns the contents of the initializer list \a l to this sparse vector.
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             */
            SparseVector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the contents of the vector container \a c to this sparse vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            SparseVector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the vector expression \a e to this sparse vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseVector& operator=(const VectorExpression<E>& e)
            {
                SparseVector tmp(e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Adds the contents of the vector container \a c element-wise to this sparse vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            SparseVector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this sparse vector.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            SparseVector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the vector expression \a e element-wise to this sparse vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseVector& operator+=(const VectorExpression<E>& e)
            {
                SparseVector tmp(*this + e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the vector container \a c element-wise from this sparse vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            SparseVector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this sparse vector.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            SparseVector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the vector expression \a e element-wise from this sparse vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseVector& operator-=(const VectorExpression<E>& e)
            {
                SparseVector tmp(*this - e);
                swap(tmp);
                return *this;
            }

            /**
             * \brief Multiplies every stored entry by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, SparseVector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every stored entry by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, SparseVector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Resizes this vector to match \a e and assigns the elements of \a e without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseVector& assign(const VectorExpression<E>& e)
            {
                resize(e().getSize());
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Resizes this vector to match \a l and assigns the elements of \a l.
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             */
            SparseVector& assign(InitializerListType l)
            {
                resize(l.size());
                vectorAssignVector<ScalarAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseVector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this vector without intermediate temporary.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            SparseVector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            SparseVector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this vector without intermediate temporary.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            SparseVector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this sparse vector with those of \a v.
             * \param v The sparse vector to swap with.
             */
            void swap(SparseVector& v)
            {
                if (this != &v) {
                    std::swap(data, v.data);
                    std::swap(size, v.size);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first sparse vector.
             * \param v2 The second sparse vector.
             */
            friend void swap(SparseVector& v1, SparseVector& v2)
            {
                v1.swap(v2);
            }

            /**
             * \brief Removes all explicitly stored entries (the logical size remains unchanged).
             */
            void clear()
            {
                data.clear();
            }

            /**
             * \brief Resizes the logical element count to \a n, dropping any stored entries at indices beyond \a n.
             * \param n The new logical element count.
             */
            void resize(SizeType n)
            {
                n = storageSize(n);

                for (typename ArrayType::iterator it = data.begin(); it != data.end();) {
                    if (it->first >= n)
                        it = data.erase(it);
                    else
                        ++it;
                }

                size = n;
            }

          private:
            SizeType storageSize(SizeType n)
            {
                return CDPL_MATH_CHECK_MAX_SIZE(n, getMaxSize(), Base::SizeError);
            }

            ArrayType              data;
            SizeType               size;
            static const ValueType zero;
        };

        template <typename T, typename A>
        const typename SparseVector<T, A>::ValueType SparseVector<T, A>::zero = SparseVector<T, A>::ValueType();

        /**
         * \brief Variable-size vector with a fixed upper capacity \a N stored in a stack-allocated array.
         * \tparam T The scalar value type.
         * \tparam N The maximum vector size.
         */
        template <typename T, std::size_t N>
        class BoundedVector : public VectorContainer<BoundedVector<T, N> >
        {

            typedef BoundedVector<T, N> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Mutable element reference type.
             */
            typedef T&                                    Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T&                              ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief The fixed-capacity C-array type used for in-memory storage.
             */
            typedef ValueType                             ArrayType[N];

            /**
             * \brief Pointer type for raw access to the element array.
             */
            typedef T*                                    Pointer;

            /**
             * \brief Constant pointer type for raw access to the element array.
             */
            typedef const T*                              ConstPointer;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery (one element larger than the bound).
             */
            typedef BoundedVector<T, N + 1>               VectorTemporaryType;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BoundedVector instances.
             */
            typedef std::shared_ptr<SelfType>             SharedPointer;

            /**
             * \brief The initializer list type accepted by constructors and assignment.
             */
            typedef std::initializer_list<T>              InitializerListType;


            /**
             * \brief The compile-time maximum capacity \a N.
             */
            static const SizeType MaxSize = N;

            /**
             * \brief Constructs an empty bounded vector (size zero, capacity \a N).
             */
            BoundedVector():
                size(0) {}

            /**
             * \brief Constructs a bounded vector of size \a n with value-initialized elements.
             * \param n The initial element count.
             * \throw Base::SizeError if \a n exceeds the bound \a N.
             */
            explicit BoundedVector(SizeType n):
                size(0)
            {
                resize(n);
            }

            /**
             * \brief Constructs a bounded vector of size \a n with every element initialized to \a v.
             * \param n The initial element count.
             * \param v The initial element value.
             * \throw Base::SizeError if \a n exceeds the bound \a N.
             */
            BoundedVector(SizeType n, const ValueType& v):
                size(0)
            {
                resize(n, v);
            }

            /**
             * \brief Constructs a copy of the bounded vector \a v.
             * \param v The bounded vector to copy.
             */
            BoundedVector(const BoundedVector& v):
                size(v.size)
            {
                std::copy(v.data, v.data + v.size, data);
            }

            /**
             * \brief Constructs a bounded vector with the contents of the initializer list \a l.
             * \param l The initializer list providing the initial elements.
             * \throw Base::SizeError if \c l.size() exceeds the bound \a N.
             */
            BoundedVector(InitializerListType l)
            {
                assign(l);
            }

            /**
             * \brief Constructs a bounded vector from the vector expression \a e.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \throw Base::SizeError if the size of \a e exceeds the bound \a N.
             */
            template <typename E>
            BoundedVector(const VectorExpression<E>& e):
                size(0)
            {
                assign(e);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Tells whether the vector is empty.
             * \return \c true if the vector contains no elements, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the current element count.
             * \return The number of elements.
             */
            SizeType getSize() const
            {
                return size;
            }

            /**
             * \brief Returns the compile-time maximum capacity \a N.
             * \return The maximum element count.
             */
            SizeType getMaxSize() const
            {
                return N;
            }

            /**
             * \brief Returns a mutable pointer to the contiguous element array.
             * \return A mutable pointer to the element array.
             */
            Pointer getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const pointer to the contiguous element array.
             * \return A \c const pointer to the element array.
             */
            ConstPointer getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the elements of \a v to this bounded vector.
             * \param v The source bounded vector.
             * \return A reference to itself.
             */
            BoundedVector& operator=(const BoundedVector& v)
            {
                if (this != &v) {
                    std::copy(v.data, v.data + v.size, data);
                    size = v.size;
                }

                return *this;
            }

            /**
             * \brief Assigns the contents of the initializer list \a l to this bounded vector.
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             * \throw Base::SizeError if \c l.size() exceeds the bound \a N.
             */
            BoundedVector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the contents of the vector container \a c to this bounded vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            BoundedVector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the vector expression \a e to this bounded vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedVector& operator=(const VectorExpression<E>& e)
            {
                BoundedVector tmp(e);
                return this-> operator=(tmp);
            }

            /**
             * \brief Adds the contents of the vector container \a c element-wise to this bounded vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            BoundedVector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this bounded vector.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            BoundedVector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the vector expression \a e element-wise to this bounded vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedVector& operator+=(const VectorExpression<E>& e)
            {
                BoundedVector tmp(*this + e);
                return this-> operator=(tmp);
            }

            /**
             * \brief Subtracts the contents of the vector container \a c element-wise from this bounded vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            BoundedVector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this bounded vector.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            BoundedVector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the vector expression \a e element-wise from this bounded vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedVector& operator-=(const VectorExpression<E>& e)
            {
                BoundedVector tmp(*this - e);
                return this-> operator=(tmp);
            }

            /**
             * \brief Multiplies every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, BoundedVector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, BoundedVector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Resizes this vector to match \a e and assigns the elements of \a e without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             * \throw Base::SizeError if the size of \a e exceeds the bound \a N.
             */
            template <typename E>
            BoundedVector& assign(const VectorExpression<E>& e)
            {
                resize(e().getSize());
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Resizes this vector to match \a l and copies the elements of \a l in.
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             * \throw Base::SizeError if the size of \a l exceeds the bound \a N.
             */
            BoundedVector& assign(InitializerListType l)
            {
                resize(l.size());
                std::copy(l.begin(), l.begin() + size, data);
                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedVector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this vector without intermediate temporary.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            BoundedVector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            BoundedVector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this vector without intermediate temporary.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            BoundedVector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this bounded vector with those of \a v.
             * \param v The bounded vector to swap with.
             */
            void swap(BoundedVector& v)
            {
                if (this != &v) {
                    std::swap_ranges(data, data + std::max(size, v.size), v.data);
                    std::swap(size, v.size);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first bounded vector.
             * \param v2 The second bounded vector.
             */
            friend void swap(BoundedVector& v1, BoundedVector& v2)
            {
                v1.swap(v2);
            }

            /**
             * \brief Sets every element of the vector to the value \a v (size is unchanged).
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                std::fill(data, data + size, v);
            }

            /**
             * \brief Resizes the vector to \a n elements (new elements are left value-uninitialized).
             * \param n The new element count.
             * \throw Base::SizeError if \a n exceeds the bound \a N.
             */
            void resize(SizeType n)
            {
                size = storageSize(n);
            }

            /**
             * \brief Resizes the vector to \a n elements; newly added elements are set to \a v.
             * \param n The new element count.
             * \param v The fill value for newly added elements.
             * \throw Base::SizeError if \a n exceeds the bound \a N.
             */
            void resize(SizeType n, const ValueType& v)
            {
                n = storageSize(n);

                if (n > size)
                    std::fill(data + size, data + n, v);

                size = n;
            }

          private:
            SizeType storageSize(SizeType n)
            {
                return CDPL_MATH_CHECK_MAX_SIZE(n, N, Base::SizeError);
            }

            ArrayType data;
            SizeType  size;
        };

        template <typename T, std::size_t N>
        const typename BoundedVector<T, N>::SizeType BoundedVector<T, N>::MaxSize;

        /**
         * \brief Fixed-size vector of dimension \a N backed by a C-array (no dynamic allocation).
         * \tparam T The scalar value type.
         * \tparam N The vector dimension.
         */
        template <typename T, std::size_t N>
        class CVector : public VectorContainer<CVector<T, N> >
        {

            typedef CVector<T, N> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Mutable element reference type.
             */
            typedef T&                                    Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T&                              ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief The fixed-size C-array type used for in-memory storage of \a N elements.
             */
            typedef ValueType                             ArrayType[N];

            /**
             * \brief Pointer type for raw access to the element array.
             */
            typedef T*                                    Pointer;

            /**
             * \brief Constant pointer type for raw access to the element array.
             */
            typedef const T*                              ConstPointer;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery (a Math::BoundedVector of \a N + \e 1 capacity).
             */
            typedef BoundedVector<T, N + 1>               VectorTemporaryType;

            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CVector instances.
             */
            typedef std::shared_ptr<SelfType>             SharedPointer;

            /**
             * \brief The initializer list type accepted by constructors and assignment.
             */
            typedef std::initializer_list<T>              InitializerListType;


            /**
             * \brief The compile-time fixed size \a N.
             */
            static const SizeType Size = N;

            /**
             * \brief Constructs a zero-initialized \a N element vector.
             */
            CVector()
            {
                clear();
            }

            /**
             * \brief Constructs an \a N-element vector with every element initialized to \a v.
             * \param v The initial element value.
             */
            explicit CVector(const ValueType& v)
            {
                clear(v);
            }

            /**
             * \brief Constructs a copy of the fixed-size vector \a v.
             * \param v The fixed-size vector to copy.
             */
            CVector(const CVector& v)
            {
                std::copy(v.data, v.data + N, data);
            }

            /**
             * \brief Constructs a fixed-size vector with the contents of the initializer list \a l.
             * \param l The initializer list providing the initial elements (truncated to \a N if longer and zero-padded if shorter).
             */
            CVector(InitializerListType l)
            {
                assign(l);
            }

            /**
             * \brief Constructs a fixed-size vector from the vector expression \a e.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             */
            template <typename E>
            CVector(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a mutable reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A mutable reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            /**
             * \brief Tells whether the vector is empty (\a N is zero).
             * \return \c true if \a N is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (N == 0);
            }

            /**
             * \brief Returns the fixed element count \a N.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return N;
            }

            /**
             * \brief Returns the fixed element count \a N (capacity equals size for Math::CVector).
             * \return The element count.
             */
            SizeType getMaxSize() const
            {
                return N;
            }

            /**
             * \brief Returns a mutable pointer to the contiguous element array.
             * \return A mutable pointer to the element array.
             */
            Pointer getData()
            {
                return data;
            }

            /**
             * \brief Returns a \c const pointer to the contiguous element array.
             * \return A \c const pointer to the element array.
             */
            ConstPointer getData() const
            {
                return data;
            }

            /**
             * \brief Copy-assigns the elements of \a v to this fixed-size vector.
             * \param v The source fixed-size vector.
             * \return A reference to itself.
             */
            CVector& operator=(const CVector& v)
            {
                if (this != &v)
                    std::copy(v.data, v.data + N, data);

                return *this;
            }

            /**
             * \brief Assigns the contents of the initializer list \a l to this fixed-size vector.
             * \param l The initializer list providing the new elements (truncated to \a N if longer and zero-padded if shorter).
             * \return A reference to itself.
             */
            CVector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            /**
             * \brief Assigns the contents of the vector container \a c to this fixed-size vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            CVector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            /**
             * \brief Assigns the vector expression \a e to this fixed-size vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            CVector& operator=(const VectorExpression<E>& e)
            {
                CVector      tmp(e);
                return this->operator=(tmp);
            }

            /**
             * \brief Adds the contents of the vector container \a c element-wise to this fixed-size vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            CVector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this fixed-size vector.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            CVector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            /**
             * \brief Adds the vector expression \a e element-wise to this fixed-size vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            CVector& operator+=(const VectorExpression<E>& e)
            {
                CVector      tmp(*this + e);
                return this->operator=(tmp);
            }

            /**
             * \brief Subtracts the contents of the vector container \a c element-wise from this fixed-size vector (no alias check needed).
             * \tparam C The source vector container type.
             * \param c The source vector container.
             * \return A reference to itself.
             */
            template <typename C>
            CVector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this fixed-size vector.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            CVector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            /**
             * \brief Subtracts the vector expression \a e element-wise from this fixed-size vector (via a temporary to handle aliasing).
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            CVector& operator-=(const VectorExpression<E>& e)
            {
                CVector      tmp(*this - e);
                return this->operator=(tmp);
            }

            /**
             * \brief Multiplies every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar multiplier.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, CVector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Divides every element by the scalar \a t.
             * \tparam T1 The scalar type.
             * \param t The scalar divisor.
             * \return A reference to itself.
             */
            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, CVector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            /**
             * \brief Assigns the elements of the vector expression \a e to this fixed-size vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            CVector& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Assigns the contents of the initializer list \a l to this fixed-size vector (truncated to \a N if longer; zero-padded if shorter).
             * \param l The initializer list providing the new elements.
             * \return A reference to itself.
             * \throw Base::SizeError if the size of \a l exceeds \a N.
             */
            CVector& assign(InitializerListType l)
            {
                SizeType n = CDPL_MATH_CHECK_MAX_SIZE(l.size(), N, Base::SizeError);
                std::copy(l.begin(), l.begin() + n, data);

                if (n < N)
                    std::fill(data + n, data + N, ValueType());

                return *this;
            }

            /**
             * \brief Adds the elements of the vector expression \a e to this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            CVector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Adds the contents of the initializer list \a l element-wise to this vector without intermediate temporary.
             * \param l The initializer list providing the addends.
             * \return A reference to itself.
             */
            CVector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Subtracts the elements of the vector expression \a e from this vector without intermediate temporary.
             * \tparam E The source vector expression type.
             * \param e The source vector expression.
             * \return A reference to itself.
             */
            template <typename E>
            CVector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            /**
             * \brief Subtracts the contents of the initializer list \a l element-wise from this vector without intermediate temporary.
             * \param l The initializer list providing the subtrahends.
             * \return A reference to itself.
             */
            CVector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            /**
             * \brief Swaps the contents of this fixed-size vector with those of \a v.
             * \param v The fixed-size vector to swap with.
             */
            void swap(CVector& v)
            {
                if (this != &v)
                    std::swap_ranges(data, data + N, v.data);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first fixed-size vector.
             * \param v2 The second fixed-size vector.
             */
            friend void swap(CVector& v1, CVector& v2)
            {
                v1.swap(v2);
            }

            /**
             * \brief Sets every element of the vector to the value \a v.
             * \param v The fill value.
             */
            void clear(const ValueType& v = ValueType())
            {
                std::fill(data, data + N, v);
            }

          private:
            ArrayType data;
        };

        template <typename T, std::size_t N>
        const typename CVector<T, N>::SizeType CVector<T, N>::Size;

        /**
         * \brief Constant vector expression whose elements are all zero.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ZeroVector : public VectorContainer<ZeroVector<T> >
        {

            typedef ZeroVector<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Reference type (always a \c const reference — all elements are zero).
             */
            typedef const T&                              Reference;

            /**
             * \brief Constant reference type to the zero element.
             */
            typedef const T&                              ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery.
             */
            typedef Vector<T>                             VectorTemporaryType;

            /**
             * \brief Constructs an empty zero vector.
             */
            ZeroVector():
                size(0) {}

            /**
             * \brief Constructs a zero vector of size \a n.
             * \param n The element count.
             */
            explicit ZeroVector(SizeType n):
                size(n) {}

            /**
             * \brief Constructs a copy of the zero vector \a v.
             * \param v The zero vector to copy.
             */
            ZeroVector(const ZeroVector& v):
                size(v.size) {}

            /**
             * \brief Returns a \c const reference to the zero element.
             * \param i The zero-based element index.
             * \return A \c const reference to the zero element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the zero element.
             * \param i The zero-based element index.
             * \return A \c const reference to the zero element.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return zero;
            }

            /**
             * \brief Tells whether the vector has zero logical size.
             * \return \c true if the logical size is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the logical element count.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return size;
            }

            /**
             * \brief Returns the maximum representable element count.
             * \return The maximum element count.
             */
            SizeType getMaxSize() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the logical size from \a v.
             * \param v The source zero vector.
             * \return A reference to itself.
             */
            ZeroVector& operator=(const ZeroVector& v)
            {
                size = v.size;
                return *this;
            }

            /**
             * \brief Resizes the logical element count to \a n.
             * \param n The new element count.
             */
            void resize(SizeType n)
            {
                size = n;
            }

            /**
             * \brief Swaps the logical sizes with \a v.
             * \param v The zero vector to swap with.
             */
            void swap(ZeroVector& v)
            {
                if (this != &v)
                    std::swap(size, v.size);
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first zero vector.
             * \param v2 The second zero vector.
             */
            friend void swap(ZeroVector& v1, ZeroVector& v2)
            {
                v1.swap(v2);
            }

          private:
            SizeType               size;
            static const ValueType zero;
        };

        template <typename T>
        const typename ZeroVector<T>::ValueType ZeroVector<T>::zero = ZeroVector<T>::ValueType();

        /**
         * \brief Constant vector expression \f$ e_i \f$ that contains \e 1 at a single specified index and \e 0 elsewhere.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class UnitVector : public VectorContainer<UnitVector<T> >
        {

            typedef UnitVector<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Reference type (always a \c const reference — elements are immutable).
             */
            typedef const T&                              Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T&                              ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery.
             */
            typedef Vector<T>                             VectorTemporaryType;

            /**
             * \brief Constructs an empty unit vector (size zero, index zero).
             */
            UnitVector():
                size(0), index(0) {}

            /**
             * \brief Constructs a unit vector of size \a n with the \e 1 element at index \a i.
             * \param n The element count.
             * \param i The zero-based index of the non-zero element.
             */
            UnitVector(SizeType n, SizeType i):
                size(n), index(i) {}

            /**
             * \brief Constructs a copy of the unit vector \a v.
             * \param v The unit vector to copy.
             */
            UnitVector(const UnitVector& v):
                size(v.size), index(v.index) {}

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to either \e 1 (if \a i equals the unit index) or \e 0.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i.
             * \param i The zero-based element index.
             * \return A \c const reference to either \e 1 (if \a i equals the unit index) or \e 0.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);

                return (i == index ? one : zero);
            }

            /**
             * \brief Tells whether the vector has zero logical size.
             * \return \c true if the logical size is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the logical element count.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return size;
            }

            /**
             * \brief Returns the index of the non-zero (unit) element.
             * \return The zero-based unit index.
             */
            SizeType getIndex() const
            {
                return index;
            }

            /**
             * \brief Returns the maximum representable element count.
             * \return The maximum element count.
             */
            SizeType getMaxSize() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the size and unit index from \a v.
             * \param v The source unit vector.
             * \return A reference to itself.
             */
            UnitVector& operator=(const UnitVector& v)
            {
                if (this != &v) {
                    size  = v.size;
                    index = v.index;
                }

                return *this;
            }

            /**
             * \brief Resizes the logical element count to \a n.
             * \param n The new element count.
             */
            void resize(SizeType n)
            {
                size = n;
            }

            /**
             * \brief Swaps the size and unit index with \a v.
             * \param v The unit vector to swap with.
             */
            void swap(UnitVector& v)
            {
                if (this != &v) {
                    std::swap(size, v.size);
                    std::swap(index, v.index);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first unit vector.
             * \param v2 The second unit vector.
             */
            friend void swap(UnitVector& v1, UnitVector& v2)
            {
                v1.swap(v2);
            }

          private:
            SizeType               size;
            SizeType               index;
            static const ValueType zero;
            static const ValueType one;
        };

        template <typename T>
        const typename UnitVector<T>::ValueType UnitVector<T>::zero = UnitVector<T>::ValueType();
        template <typename T>
        const typename UnitVector<T>::ValueType UnitVector<T>::one = UnitVector<T>::ValueType(1);

        /**
         * \brief Constant vector expression in which every element equals the same scalar value.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class ScalarVector : public VectorContainer<ScalarVector<T> >
        {

            typedef ScalarVector<T> SelfType;

          public:
            /**
             * \brief The scalar value type.
             */
            typedef T                                     ValueType;

            /**
             * \brief Reference type (always a \c const reference — elements are immutable).
             */
            typedef const T&                              Reference;

            /**
             * \brief Constant element reference type.
             */
            typedef const T&                              ConstReference;

            /**
             * \brief The unsigned size type.
             */
            typedef std::size_t                           SizeType;

            /**
             * \brief The signed difference type.
             */
            typedef std::ptrdiff_t                        DifferenceType;

            /**
             * \brief Closure type used when this vector appears inside another expression.
             */
            typedef VectorReference<SelfType>             ClosureType;

            /**
             * \brief Constant closure type used when this vector appears inside another expression.
             */
            typedef const VectorReference<const SelfType> ConstClosureType;

            /**
             * \brief Concrete temporary vector type used by expression template machinery.
             */
            typedef Vector<T>                             VectorTemporaryType;

            /**
             * \brief Constructs an empty scalar vector.
             */
            ScalarVector():
                size(0) {}

            /**
             * \brief Constructs a scalar vector of size \a n in which every element equals \a v.
             * \param n The element count.
             * \param v The common element value.
             */
            ScalarVector(SizeType n, const ValueType& v = ValueType()):
                size(n), value(v) {}

            /**
             * \brief Constructs a copy of the scalar vector \a v.
             * \param v The scalar vector to copy.
             */
            ScalarVector(const ScalarVector& v):
                size(v.size), value(v.value) {}

            /**
             * \brief Returns a \c const reference to the common element value.
             * \param i The zero-based element index.
             * \return A \c const reference to the common element value.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the common element value.
             * \param i The zero-based element index.
             * \return A \c const reference to the common element value.
             * \throw Base::IndexError if \a i is out of range.
             */
            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return value;
            }

            /**
             * \brief Tells whether the vector has zero logical size.
             * \return \c true if the logical size is zero, and \c false otherwise.
             */
            bool isEmpty() const
            {
                return (size == 0);
            }

            /**
             * \brief Returns the logical element count.
             * \return The element count.
             */
            SizeType getSize() const
            {
                return size;
            }

            /**
             * \brief Returns the maximum representable element count.
             * \return The maximum element count.
             */
            SizeType getMaxSize() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            /**
             * \brief Copy-assigns the size and common value from \a v.
             * \param v The source scalar vector.
             * \return A reference to itself.
             */
            ScalarVector& operator=(const ScalarVector& v)
            {
                if (this != &v) {
                    size  = v.size;
                    value = v.value;
                }

                return *this;
            }

            /**
             * \brief Resizes the logical element count to \a n.
             * \param n The new element count.
             */
            void resize(SizeType n)
            {
                size = n;
            }

            /**
             * \brief Swaps the size and common value with \a v.
             * \param v The scalar vector to swap with.
             */
            void swap(ScalarVector& v)
            {
                if (this != &v) {
                    std::swap(size, v.size);
                    std::swap(value, v.value);
                }
            }

            /**
             * \brief ADL-enabled free-function form of swap().
             * \param v1 The first scalar vector.
             * \param v2 The second scalar vector.
             */
            friend void swap(ScalarVector& v1, ScalarVector& v2)
            {
                v1.swap(v2);
            }

          private:
            SizeType  size;
            ValueType value;
        };

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying vector for a \c const Math::VectorReference view.
         * \tparam V The underlying vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<const VectorReference<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Math::VectorTemporaryTraits specialization inheriting the temporary type of the underlying vector for a Math::VectorReference view.
         * \tparam V The underlying vector type.
         */
        template <typename V>
        struct VectorTemporaryTraits<VectorReference<V> > : public VectorTemporaryTraits<V>
        {};

        /**
         * \brief Constructs a Math::CVector of size 2 from the components \a t1 and \a t2.
         * \tparam T1 The type of the first component.
         * \tparam T2 The type of the second component.
         * \param t1 The first component.
         * \param t2 The second component.
         * \return A 2-element vector with components (\a t1, \a t2).
         */
        template <typename T1, typename T2>
        CVector<typename CommonType<T1, T2>::Type, 2>
        vec(const T1& t1, const T2& t2)
        {
            CVector<typename CommonType<T1, T2>::Type, 2> v;

            v(0) = t1;
            v(1) = t2;

            return v;
        }

        /**
         * \brief Constructs a Math::CVector of size \e 3 from the components \a t1, \a t2 and \a t3.
         * \tparam T1 The type of the first component.
         * \tparam T2 The type of the second component.
         * \tparam T3 The type of the third component.
         * \param t1 The first component.
         * \param t2 The second component.
         * \param t3 The third component.
         * \return A 3-element vector with components (\a t1, \a t2, \a t3).
         */
        template <typename T1, typename T2, typename T3>
        CVector<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, 3>
        vec(const T1& t1, const T2& t2, const T3& t3)
        {
            CVector<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, 3> v;

            v(0) = t1;
            v(1) = t2;
            v(2) = t3;

            return v;
        }

        /**
         * \brief Constructs a Math::CVector of size \e 4 from the components \a t1, \a t2, \a t3 and \a t4.
         * \tparam T1 The type of the first component.
         * \tparam T2 The type of the second component.
         * \tparam T3 The type of the third component.
         * \tparam T4 The type of the fourth component.
         * \param t1 The first component.
         * \param t2 The second component.
         * \param t3 The third component.
         * \param t4 The fourth component.
         * \return A 4-element vector with components (\a t1, \a t2, \a t3, \a t4).
         */
        template <typename T1, typename T2, typename T3, typename T4>
        CVector<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type, 4>
        vec(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
        {
            CVector<typename CommonType<typename CommonType<typename CommonType<T1, T2>::Type, T3>::Type, T4>::Type, 4> v;

            v(0) = t1;
            v(1) = t2;
            v(2) = t3;
            v(3) = t4;

            return v;
        }

        /**
         * \brief Memory-efficient immutable vector where all elements have the same value of type <tt>float</tt>.
         */
        typedef ScalarVector<float> FScalarVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the same value of type <tt>double</tt>.
         */
        typedef ScalarVector<double> DScalarVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the same value of type <tt>long</tt>.
         */
        typedef ScalarVector<long> LScalarVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the same value of type <tt>unsigned long</tt>.
         */
        typedef ScalarVector<unsigned long> ULScalarVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the value zero of type <tt>float</tt>.
         */
        typedef ZeroVector<float> FZeroVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the value zero of type <tt>double</tt>.
         */
        typedef ZeroVector<double> DZeroVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the value zero of type <tt>long</tt>.
         */
        typedef ZeroVector<long> LZeroVector;

        /**
         * \brief Memory-efficient immutable vector where all elements have the value zero of type <tt>unsigned long</tt>.
         */
        typedef ZeroVector<unsigned long> ULZeroVector;

        /**
         * \brief Memory-efficient immutable unit vector with element values of type <tt>float</tt>.
         */
        typedef UnitVector<float> FUnitVector;

        /**
         * \brief Memory-efficient immutable unit vector with element values of type <tt>double</tt>.
         */
        typedef UnitVector<double> DUnitVector;

        /**
         * \brief Memory-efficient immutable unit vector with element values of type <tt>long</tt>.
         */
        typedef UnitVector<long> LUnitVector;

        /**
         * \brief Memory-efficient immutable unit vector with element values of type <tt>unsigned long</tt>.
         */
        typedef UnitVector<unsigned long> ULUnitVector;

        /**
         * \brief Bounded \e 2 element vector holding floating-point values of type <tt>float</tt>.
         */
        typedef CVector<float, 2> Vector2F;

        /**
         * \brief Bounded \e 3 element vector holding floating-point values of type <tt>float</tt>.
         */
        typedef CVector<float, 3> Vector3F;

        /**
         * \brief Bounded \e 4 element vector holding floating-point values of type <tt>float</tt>.
         */
        typedef CVector<float, 4> Vector4F;

        /**
         * \brief Bounded \e 2 element vector holding floating-point values of type <tt>double</tt>.
         */
        typedef CVector<double, 2> Vector2D;

        /**
         * \brief Bounded \e 3 element vector holding floating-point values of type <tt>double</tt>.
         */
        typedef CVector<double, 3> Vector3D;

        /**
         * \brief Bounded \e 4 element vector holding floating-point values of type <tt>double</tt>.
         */
        typedef CVector<double, 4> Vector4D;

        /**
         * \brief Bounded 7 element vector holding floating-point values of type <tt>double</tt>.
         */
        typedef CVector<double, 7> Vector7D;

        /**
         * \brief Bounded \e 2 element vector holding signed integers of type <tt>long</tt>.
         */
        typedef CVector<long, 2> Vector2L;

        /**
         * \brief Bounded \e 3 element vector holding signed integers of type <tt>long</tt>.
         */
        typedef CVector<long, 3> Vector3L;

        /**
         * \brief Bounded \e 4 element vector holding signed integers of type <tt>long</tt>.
         */
        typedef CVector<long, 4> Vector4L;

        /**
         * \brief Bounded \e 2 element vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CVector<unsigned long, 2> Vector2UL;

        /**
         * \brief Bounded \e 3 element vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CVector<unsigned long, 3> Vector3UL;

        /**
         * \brief Bounded \e 4 element vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CVector<unsigned long, 4> Vector4UL;

        /**
         * \brief Unbounded dense vector holding floating-point values of type <tt>float</tt>.
         */
        typedef Vector<float> FVector;

        /**
         * \brief Unbounded dense vector holding floating-point values of type <tt>double</tt>.
         */
        typedef Vector<double> DVector;

        /**
         * \brief Unbounded dense vector holding signed integers of type <tt>long</tt>.
         */
        typedef Vector<long> LVector;

        /**
         * \brief Unbounded dense vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef Vector<unsigned long> ULVector;

        /**
         * \brief Unbounded sparse vector holding floating-point values of type <tt>float</tt>.
         */
        typedef SparseVector<float> SparseFVector;

        /**
         * \brief Unbounded sparse vector holding floating-point values of type <tt>double</tt>.
         */
        typedef SparseVector<double> SparseDVector;

        /**
         * \brief Unbounded sparse vector holding signed integers of type <tt>long</tt>.
         */
        typedef SparseVector<long> SparseLVector;

        /**
         * \brief Unbounded sparse vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef SparseVector<unsigned long> SparseULVector;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTOR_HPP
