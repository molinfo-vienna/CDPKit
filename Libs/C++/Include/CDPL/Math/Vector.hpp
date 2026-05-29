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
            typedef V                                                      VectorType;
            typedef typename V::ValueType                                  ValueType;
            typedef typename std::conditional<std::is_const<V>::value,
                                              typename V::ConstReference,
                                              typename V::Reference>::type Reference;
            typedef typename V::ConstReference                             ConstReference;
            typedef typename V::SizeType                                   SizeType;
            typedef typename V::DifferenceType                             DifferenceType;
            typedef SelfType                                               ClosureType;
            typedef const SelfType                                         ConstClosureType;

            explicit VectorReference(VectorType& v):
                data(v) {}

            Reference operator[](SizeType i)
            {
                return data[i];
            }

            ConstReference operator[](SizeType i) const
            {
                return data[i];
            }

            Reference operator()(SizeType i)
            {
                return data(i);
            }

            ConstReference operator()(SizeType i) const
            {
                return data(i);
            }

            SizeType getSize() const
            {
                return data.getSize();
            }

            SizeType getMaxSize() const
            {
                return data.getMaxSize();
            }

            bool isEmpty() const
            {
                return data.isEmpty();
            }

            const VectorType& getData() const
            {
                return data;
            }

            VectorType& getData()
            {
                return data;
            }

            VectorReference& operator=(const VectorReference& r)
            {
                data.operator=(r.data);
                return *this;
            }

            template <typename E>
            VectorReference& operator=(const VectorExpression<E>& e)
            {
                data.operator=(e);
                return *this;
            }

            template <typename E>
            VectorReference& operator+=(const VectorExpression<E>& e)
            {
                data.operator+=(e);
                return *this;
            }

            template <typename E>
            VectorReference& operator-=(const VectorExpression<E>& e)
            {
                data.operator-=(e);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorReference>::type& operator*=(const T& t)
            {
                data.operator*=(t);
                return *this;
            }

            template <typename T>
            typename std::enable_if<IsScalar<T>::value, VectorReference>::type& operator/=(const T& t)
            {
                data.operator/=(t);
                return *this;
            }

            template <typename E>
            VectorReference& assign(const VectorExpression<E>& e)
            {
                data.assign(e);
                return *this;
            }

            template <typename E>
            VectorReference& plusAssign(const VectorExpression<E>& e)
            {
                data.plusAssign(e);
                return *this;
            }

            template <typename E>
            VectorReference& minusAssign(const VectorExpression<E>& e)
            {
                data.minusAssign(e);
                return *this;
            }

            void swap(VectorReference& r)
            {
                data.swap(r.data);
            }

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
            /** \brief The wrapped \c std::initializer_list type. */
            typedef std::initializer_list<T>                      InitializerListType;
            /** \brief The scalar value type. */
            typedef typename InitializerListType::value_type      ValueType;
            /** \brief Constant reference type to an element. */
            typedef typename InitializerListType::const_reference ConstReference;
            /** \brief Mutable reference type (degrades to ConstReference for the immutable initializer list). */
            typedef typename InitializerListType::reference       Reference;
            /** \brief The unsigned size type. */
            typedef typename InitializerListType::size_type       SizeType;
            /** \brief The signed difference type. */
            typedef typename std::ptrdiff_t                       DifferenceType;
            /** \brief Closure type used when this vector appears inside another expression. */
            typedef SelfType                                      ClosureType;
            /** \brief Constant closure type used when this vector appears inside another expression. */
            typedef const SelfType                                ConstClosureType;
            /** \brief Concrete temporary vector type used by expression-template machinery. */
            typedef Vector<T, std::vector<T> >                    VectorTemporaryType;

            /**
             * \brief Constructs the vector by wrapping the initializer list \a l (no copy).
             * \param l The initializer list to wrap.
             */
            InitListVector(InitializerListType l):
                list(l) {}

            /**
             * \brief Returns a reference to the element at index \a i (alias for operator()).
             * \param i The zero-based element index.
             * \return A reference to the element.
             * \throw Base::IndexError if \a i is out of range.
             */
            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            /**
             * \brief Returns a \c const reference to the element at index \a i (alias for operator()).
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
            /** \brief The scalar value type stored in the vector. */
            typedef T                                     ValueType;
            /** \brief Mutable reference type to an element. */
            typedef T&                                    Reference;
            /** \brief Constant reference type to an element. */
            typedef const T&                              ConstReference;
            /** \brief The unsigned size type used by the underlying storage container. */
            typedef typename A::size_type                 SizeType;
            /** \brief The signed difference type used by the underlying storage container. */
            typedef typename A::difference_type           DifferenceType;
            /** \brief The underlying storage container type. */
            typedef A                                     ArrayType;
            /** \brief Pointer type for raw element access. */
            typedef T*                                    Pointer;
            /** \brief Constant pointer type for raw element access. */
            typedef const T*                              ConstPointer;
            /** \brief Closure type used when this vector appears inside another expression. */
            typedef VectorReference<SelfType>             ClosureType;
            /** \brief Constant closure type used when this vector appears inside another expression. */
            typedef const VectorReference<const SelfType> ConstClosureType;
            /** \brief Concrete temporary vector type used by expression-template machinery. */
            typedef SelfType                              VectorTemporaryType;
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Vector instances. */
            typedef std::shared_ptr<SelfType>             SharedPointer;
            /** \brief Type of the brace-initializer list accepted by the corresponding constructor. */
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
             * \param v The element value used to initialize every entry.
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

            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            bool isEmpty() const
            {
                return data.empty();
            }

            SizeType getSize() const
            {
                return data.size();
            }

            SizeType getMaxSize() const
            {
                return data.max_size();
            }

            ArrayType& getData()
            {
                return data;
            }

            const ArrayType& getData() const
            {
                return data;
            }

            Vector& operator=(const Vector& v)
            {
                data = v.data;
                return *this;
            }

            Vector& operator=(Vector&& v)
            {
                data = std::move(v.data);
                return *this;
            }

            Vector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            template <typename C>
            Vector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            template <typename E>
            Vector& operator=(const VectorExpression<E>& e)
            {
                Vector tmp(e);
                swap(tmp);
                return *this;
            }

            template <typename C>
            Vector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            Vector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            template <typename E>
            Vector& operator+=(const VectorExpression<E>& e)
            {
                Vector tmp(*this + e);
                swap(tmp);
                return *this;
            }

            template <typename C>
            Vector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            Vector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            template <typename E>
            Vector& operator-=(const VectorExpression<E>& e)
            {
                Vector tmp(*this - e);
                swap(tmp);
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Vector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, Vector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            Vector& assign(const VectorExpression<E>& e)
            {
                resize(e().getSize());
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            Vector& assign(InitializerListType l)
            {
                data = l;
                return *this;
            }

            template <typename E>
            Vector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            Vector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            template <typename E>
            Vector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            Vector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            void swap(Vector& v)
            {
                if (this != &v)
                    std::swap(data, v.data);
            }

            friend void swap(Vector& v1, Vector& v2)
            {
                v1.swap(v2);
            }

            void clear(const ValueType& v = ValueType())
            {
                std::fill(data.begin(), data.end(), v);
            }

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
            typedef T                                         ValueType;
            typedef std::size_t                               SizeType;
            typedef std::ptrdiff_t                            DifferenceType;
            typedef typename A::key_type                      KeyType;
            typedef const T&                                  ConstReference;
            typedef SparseContainerElement<SelfType, KeyType> Reference;
            typedef A                                         ArrayType;
            typedef T*                                        Pointer;
            typedef const T*                                  ConstPointer;
            typedef VectorReference<SelfType>                 ClosureType;
            typedef const VectorReference<const SelfType>     ConstClosureType;
            typedef SelfType                                  VectorTemporaryType;
            typedef std::shared_ptr<SelfType>                 SharedPointer;
            typedef std::initializer_list<T>                  InitializerListType;

            SparseVector():
                data(), size(0) {}

            explicit SparseVector(SizeType n):
                data(), size(storageSize(n)) {}

            SparseVector(const SparseVector& v):
                data(v.data), size(v.size) {}

            SparseVector(SparseVector&& v):
                data(), size(0)
            {
                swap(v);
            }

            SparseVector(InitializerListType l)
            {
                assign(l);
            }

            template <typename E>
            SparseVector(const VectorExpression<E>& e):
                data(), size(0)
            {
                assign(e);
            }

            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return Reference(*this, i);
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);

                typename ArrayType::const_iterator it = data.find(i);

                if (it == data.end())
                    return zero;

                return it->second;
            }

            SizeType getNumElements() const
            {
                return data.size();
            }

            bool isEmpty() const
            {
                return (size == 0);
            }

            SizeType getSize() const
            {
                return size;
            }

            SizeType getMaxSize() const
            {
                return std::min(SizeType(data.max_size()), std::numeric_limits<SizeType>::max());
            }

            ArrayType& getData()
            {
                return data;
            }

            const ArrayType& getData() const
            {
                return data;
            }

            SparseVector& operator=(const SparseVector& v)
            {
                data = v.data;
                size = v.size;
                return *this;
            }

            SparseVector& operator=(SparseVector&& v)
            {
                swap(v);
                return *this;
            }

            SparseVector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            template <typename C>
            SparseVector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            template <typename E>
            SparseVector& operator=(const VectorExpression<E>& e)
            {
                SparseVector tmp(e);
                swap(tmp);
                return *this;
            }

            template <typename C>
            SparseVector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            SparseVector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            template <typename E>
            SparseVector& operator+=(const VectorExpression<E>& e)
            {
                SparseVector tmp(*this + e);
                swap(tmp);
                return *this;
            }

            template <typename C>
            SparseVector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            SparseVector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            template <typename E>
            SparseVector& operator-=(const VectorExpression<E>& e)
            {
                SparseVector tmp(*this - e);
                swap(tmp);
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, SparseVector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, SparseVector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            SparseVector& assign(const VectorExpression<E>& e)
            {
                resize(e().getSize());
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            SparseVector& assign(InitializerListType l)
            {
                resize(l.size());
                vectorAssignVector<ScalarAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            template <typename E>
            SparseVector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            SparseVector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            template <typename E>
            SparseVector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            SparseVector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            void swap(SparseVector& v)
            {
                if (this != &v) {
                    std::swap(data, v.data);
                    std::swap(size, v.size);
                }
            }

            friend void swap(SparseVector& v1, SparseVector& v2)
            {
                v1.swap(v2);
            }

            void clear()
            {
                data.clear();
            }

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
            typedef T                                     ValueType;
            typedef T&                                    Reference;
            typedef const T&                              ConstReference;
            typedef std::size_t                           SizeType;
            typedef std::ptrdiff_t                        DifferenceType;
            typedef ValueType                             ArrayType[N];
            typedef T*                                    Pointer;
            typedef const T*                              ConstPointer;
            typedef VectorReference<SelfType>             ClosureType;
            typedef const VectorReference<const SelfType> ConstClosureType;
            typedef BoundedVector<T, N + 1>               VectorTemporaryType;
            typedef std::shared_ptr<SelfType>             SharedPointer;
            typedef std::initializer_list<T>              InitializerListType;

            static const SizeType MaxSize = N;

            BoundedVector():
                size(0) {}

            explicit BoundedVector(SizeType n):
                size(0)
            {
                resize(n);
            }

            BoundedVector(SizeType n, const ValueType& v):
                size(0)
            {
                resize(n, v);
            }

            BoundedVector(const BoundedVector& v):
                size(v.size)
            {
                std::copy(v.data, v.data + v.size, data);
            }

            BoundedVector(InitializerListType l)
            {
                assign(l);
            }

            template <typename E>
            BoundedVector(const VectorExpression<E>& e):
                size(0)
            {
                assign(e);
            }

            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            bool isEmpty() const
            {
                return (size == 0);
            }

            SizeType getSize() const
            {
                return size;
            }

            SizeType getMaxSize() const
            {
                return N;
            }

            Pointer getData()
            {
                return data;
            }

            ConstPointer getData() const
            {
                return data;
            }

            BoundedVector& operator=(const BoundedVector& v)
            {
                if (this != &v) {
                    std::copy(v.data, v.data + v.size, data);
                    size = v.size;
                }

                return *this;
            }

            BoundedVector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            template <typename C>
            BoundedVector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            template <typename E>
            BoundedVector& operator=(const VectorExpression<E>& e)
            {
                BoundedVector tmp(e);
                return this-> operator=(tmp);
            }

            template <typename C>
            BoundedVector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            BoundedVector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            template <typename E>
            BoundedVector& operator+=(const VectorExpression<E>& e)
            {
                BoundedVector tmp(*this + e);
                return this-> operator=(tmp);
            }

            template <typename C>
            BoundedVector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            BoundedVector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            template <typename E>
            BoundedVector& operator-=(const VectorExpression<E>& e)
            {
                BoundedVector tmp(*this - e);
                return this-> operator=(tmp);
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, BoundedVector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, BoundedVector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            BoundedVector& assign(const VectorExpression<E>& e)
            {
                resize(e().getSize());
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            BoundedVector& assign(InitializerListType l)
            {
                resize(l.size());
                std::copy(l.begin(), l.begin() + size, data);
                return *this;
            }

            template <typename E>
            BoundedVector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            BoundedVector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            template <typename E>
            BoundedVector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            BoundedVector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            void swap(BoundedVector& v)
            {
                if (this != &v) {
                    std::swap_ranges(data, data + std::max(size, v.size), v.data);
                    std::swap(size, v.size);
                }
            }

            friend void swap(BoundedVector& v1, BoundedVector& v2)
            {
                v1.swap(v2);
            }

            void clear(const ValueType& v = ValueType())
            {
                std::fill(data, data + size, v);
            }

            void resize(SizeType n)
            {
                size = storageSize(n);
            }

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
            typedef T                                     ValueType;
            typedef T&                                    Reference;
            typedef const T&                              ConstReference;
            typedef std::size_t                           SizeType;
            typedef std::ptrdiff_t                        DifferenceType;
            typedef ValueType                             ArrayType[N];
            typedef T*                                    Pointer;
            typedef const T*                              ConstPointer;
            typedef VectorReference<SelfType>             ClosureType;
            typedef const VectorReference<const SelfType> ConstClosureType;
            typedef BoundedVector<T, N + 1>               VectorTemporaryType;
            typedef std::shared_ptr<SelfType>             SharedPointer;
            typedef std::initializer_list<T>              InitializerListType;

            static const SizeType Size = N;

            CVector()
            {
                clear();
            }

            explicit CVector(const ValueType& v)
            {
                clear(v);
            }

            CVector(const CVector& v)
            {
                std::copy(v.data, v.data + N, data);
            }

            CVector(InitializerListType l)
            {
                assign(l);
            }

            template <typename E>
            CVector(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
            }

            Reference operator[](SizeType i)
            {
                return this->operator()(i);
            }

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            Reference operator()(SizeType i)
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return data[i];
            }

            bool isEmpty() const
            {
                return (N == 0);
            }

            SizeType getSize() const
            {
                return N;
            }

            SizeType getMaxSize() const
            {
                return N;
            }

            Pointer getData()
            {
                return data;
            }

            ConstPointer getData() const
            {
                return data;
            }

            CVector& operator=(const CVector& v)
            {
                if (this != &v)
                    std::copy(v.data, v.data + N, data);

                return *this;
            }

            CVector& operator=(InitializerListType l)
            {
                return assign(l);
            }

            template <typename C>
            CVector& operator=(const VectorContainer<C>& c)
            {
                return assign(c);
            }

            template <typename E>
            CVector& operator=(const VectorExpression<E>& e)
            {
                CVector      tmp(e);
                return this->operator=(tmp);
            }

            template <typename C>
            CVector& operator+=(const VectorContainer<C>& c)
            {
                return plusAssign(c);
            }

            CVector& operator+=(InitializerListType l)
            {
                return plusAssign(l);
            }

            template <typename E>
            CVector& operator+=(const VectorExpression<E>& e)
            {
                CVector      tmp(*this + e);
                return this->operator=(tmp);
            }

            template <typename C>
            CVector& operator-=(const VectorContainer<C>& c)
            {
                return minusAssign(c);
            }

            CVector& operator-=(InitializerListType l)
            {
                return minusAssign(l);
            }

            template <typename E>
            CVector& operator-=(const VectorExpression<E>& e)
            {
                CVector      tmp(*this - e);
                return this->operator=(tmp);
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, CVector>::type& operator*=(const T1& t)
            {
                vectorAssignScalar<ScalarMultiplicationAssignment>(*this, t);
                return *this;
            }

            template <typename T1>
            typename std::enable_if<IsScalar<T1>::value, CVector>::type& operator/=(const T1& t)
            {
                vectorAssignScalar<ScalarDivisionAssignment>(*this, t);
                return *this;
            }

            template <typename E>
            CVector& assign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAssignment>(*this, e);
                return *this;
            }

            CVector& assign(InitializerListType l)
            {
                SizeType n = CDPL_MATH_CHECK_MAX_SIZE(l.size(), N, Base::SizeError);
                std::copy(l.begin(), l.begin() + n, data);

                if (n < N)
                    std::fill(data + n, data + N, ValueType());

                return *this;
            }

            template <typename E>
            CVector& plusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, e);
                return *this;
            }

            CVector& plusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarAdditionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            template <typename E>
            CVector& minusAssign(const VectorExpression<E>& e)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, e);
                return *this;
            }

            CVector& minusAssign(InitializerListType l)
            {
                vectorAssignVector<ScalarSubtractionAssignment>(*this, InitListVector<ValueType>(l));
                return *this;
            }

            void swap(CVector& v)
            {
                if (this != &v)
                    std::swap_ranges(data, data + N, v.data);
            }

            friend void swap(CVector& v1, CVector& v2)
            {
                v1.swap(v2);
            }

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
            typedef T                                     ValueType;
            typedef const T&                              Reference;
            typedef const T&                              ConstReference;
            typedef std::size_t                           SizeType;
            typedef std::ptrdiff_t                        DifferenceType;
            typedef VectorReference<SelfType>             ClosureType;
            typedef const VectorReference<const SelfType> ConstClosureType;
            typedef Vector<T>                             VectorTemporaryType;

            ZeroVector():
                size(0) {}

            explicit ZeroVector(SizeType n):
                size(n) {}

            ZeroVector(const ZeroVector& v):
                size(v.size) {}

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return zero;
            }

            bool isEmpty() const
            {
                return (size == 0);
            }

            SizeType getSize() const
            {
                return size;
            }

            SizeType getMaxSize() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            ZeroVector& operator=(const ZeroVector& v)
            {
                size = v.size;
                return *this;
            }

            void resize(SizeType n)
            {
                size = n;
            }

            void swap(ZeroVector& v)
            {
                if (this != &v)
                    std::swap(size, v.size);
            }

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
         * \brief Constant vector expression \f$ e_i \f$ that contains \c 1 at a single specified index and \c 0 elsewhere.
         * \tparam T The scalar value type.
         */
        template <typename T>
        class UnitVector : public VectorContainer<UnitVector<T> >
        {

            typedef UnitVector<T> SelfType;

          public:
            typedef T                                     ValueType;
            typedef const T&                              Reference;
            typedef const T&                              ConstReference;
            typedef std::size_t                           SizeType;
            typedef std::ptrdiff_t                        DifferenceType;
            typedef VectorReference<SelfType>             ClosureType;
            typedef const VectorReference<const SelfType> ConstClosureType;
            typedef Vector<T>                             VectorTemporaryType;

            UnitVector():
                size(0), index(0) {}

            UnitVector(SizeType n, SizeType i):
                size(n), index(i) {}

            UnitVector(const UnitVector& v):
                size(v.size), index(v.index) {}

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);

                return (i == index ? one : zero);
            }

            bool isEmpty() const
            {
                return (size == 0);
            }

            SizeType getSize() const
            {
                return size;
            }

            SizeType getIndex() const
            {
                return index;
            }

            SizeType getMaxSize() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            UnitVector& operator=(const UnitVector& v)
            {
                if (this != &v) {
                    size  = v.size;
                    index = v.index;
                }

                return *this;
            }

            void resize(SizeType n)
            {
                size = n;
            }

            void swap(UnitVector& v)
            {
                if (this != &v) {
                    std::swap(size, v.size);
                    std::swap(index, v.index);
                }
            }

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
            typedef T                                     ValueType;
            typedef const T&                              Reference;
            typedef const T&                              ConstReference;
            typedef std::size_t                           SizeType;
            typedef std::ptrdiff_t                        DifferenceType;
            typedef VectorReference<SelfType>             ClosureType;
            typedef const VectorReference<const SelfType> ConstClosureType;
            typedef Vector<T>                             VectorTemporaryType;

            ScalarVector():
                size(0) {}

            ScalarVector(SizeType n, const ValueType& v = ValueType()):
                size(n), value(v) {}

            ScalarVector(const ScalarVector& v):
                size(v.size), value(v.value) {}

            ConstReference operator[](SizeType i) const
            {
                return this->operator()(i);
            }

            ConstReference operator()(SizeType i) const
            {
                CDPL_MATH_CHECK(i < getSize(), "Index out of range", Base::IndexError);
                return value;
            }

            bool isEmpty() const
            {
                return (size == 0);
            }

            SizeType getSize() const
            {
                return size;
            }

            SizeType getMaxSize() const
            {
                return std::numeric_limits<SizeType>::max();
            }

            ScalarVector& operator=(const ScalarVector& v)
            {
                if (this != &v) {
                    size  = v.size;
                    value = v.value;
                }

                return *this;
            }

            void resize(SizeType n)
            {
                size = n;
            }

            void swap(ScalarVector& v)
            {
                if (this != &v) {
                    std::swap(size, v.size);
                    std::swap(value, v.value);
                }
            }

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
         * \brief Constructs a Math::CVector of size 3 from the components \a t1, \a t2 and \a t3.
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
         * \brief Constructs a Math::CVector of size 4 from the components \a t1, \a t2, \a t3 and \a t4.
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
         * \brief A memory-efficient immutable vector where all elements have the same value of type <tt>float</tt>.
         */
        typedef ScalarVector<float> FScalarVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the same value of type <tt>double</tt>.
         */
        typedef ScalarVector<double> DScalarVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the same value of type <tt>long</tt>.
         */
        typedef ScalarVector<long> LScalarVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the same value of type <tt>unsigned long</tt>.
         */
        typedef ScalarVector<unsigned long> ULScalarVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the value zero of type <tt>float</tt>.
         */
        typedef ZeroVector<float> FZeroVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the value zero of type <tt>double</tt>.
         */
        typedef ZeroVector<double> DZeroVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the value zero of type <tt>long</tt>.
         */
        typedef ZeroVector<long> LZeroVector;

        /**
         * \brief A memory-efficient immutable vector where all elements have the value zero of type <tt>unsigned long</tt>.
         */
        typedef ZeroVector<unsigned long> ULZeroVector;

        /**
         * \brief A memory-efficient immutable unit vector with element values of type <tt>float</tt>.
         */
        typedef UnitVector<float> FUnitVector;

        /**
         * \brief A memory-efficient immutable unit vector with element values of type <tt>double</tt>.
         */
        typedef UnitVector<double> DUnitVector;

        /**
         * \brief A memory-efficient immutable unit vector with element values of type <tt>long</tt>.
         */
        typedef UnitVector<long> LUnitVector;

        /**
         * \brief A memory-efficient immutable unit vector with element values of type <tt>unsigned long</tt>.
         */
        typedef UnitVector<unsigned long> ULUnitVector;

        /**
         * \brief A bounded 2 element vector holding floating point values of type <tt>float</tt>.
         */
        typedef CVector<float, 2> Vector2F;

        /**
         * \brief A bounded 3 element vector holding floating point values of type <tt>float</tt>.
         */
        typedef CVector<float, 3> Vector3F;

        /**
         * \brief A bounded 4 element vector holding floating point values of type <tt>float</tt>.
         */
        typedef CVector<float, 4> Vector4F;

        /**
         * \brief A bounded 2 element vector holding floating point values of type <tt>double</tt>.
         */
        typedef CVector<double, 2> Vector2D;

        /**
         * \brief A bounded 3 element vector holding floating point values of type <tt>double</tt>.
         */
        typedef CVector<double, 3> Vector3D;

        /**
         * \brief A bounded 4 element vector holding floating point values of type <tt>double</tt>.
         */
        typedef CVector<double, 4> Vector4D;

        /**
         * \brief A bounded 7 element vector holding floating point values of type <tt>double</tt>.
         */
        typedef CVector<double, 7> Vector7D;

        /**
         * \brief A bounded 2 element vector holding signed integers of type <tt>long</tt>.
         */
        typedef CVector<long, 2> Vector2L;

        /**
         * \brief A bounded 3 element vector holding signed integers of type <tt>long</tt>.
         */
        typedef CVector<long, 3> Vector3L;

        /**
         * \brief A bounded 4 element vector holding signed integers of type <tt>long</tt>.
         */
        typedef CVector<long, 4> Vector4L;

        /**
         * \brief A bounded 2 element vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CVector<unsigned long, 2> Vector2UL;

        /**
         * \brief A bounded 3 element vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CVector<unsigned long, 3> Vector3UL;

        /**
         * \brief A bounded 4 element vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef CVector<unsigned long, 4> Vector4UL;

        /**
         * \brief An unbounded dense vector holding floating point values of type <tt>float</tt>.
         */
        typedef Vector<float> FVector;

        /**
         * \brief An unbounded dense vector holding floating point values of type <tt>double</tt>.
         */
        typedef Vector<double> DVector;

        /**
         * \brief An unbounded dense vector holding signed integers of type <tt>long</tt>.
         */
        typedef Vector<long> LVector;

        /**
         * \brief An unbounded dense vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef Vector<unsigned long> ULVector;

        /**
         * \brief An unbounded sparse vector holding floating point values of type <tt>float</tt>.
         */
        typedef SparseVector<float> SparseFVector;

        /**
         * \brief An unbounded sparse vector holding floating point values of type <tt>double</tt>.
         */
        typedef SparseVector<double> SparseDVector;

        /**
         * \brief An unbounded sparse vector holding signed integers of type <tt>long</tt>.
         */
        typedef SparseVector<long> SparseLVector;

        /**
         * \brief An unbounded sparse vector holding unsigned integers of type <tt>unsigned long</tt>.
         */
        typedef SparseVector<unsigned long> SparseULVector;
    } // namespace Math
} // namespace CDPL

#endif // CDPL_MATH_VECTOR_HPP
