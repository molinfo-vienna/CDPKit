/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Array.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Util::Array.
 */

#ifndef CDPL_UTIL_ARRAY_HPP
#define CDPL_UTIL_ARRAY_HPP

#include <vector>
#include <string>
#include <cstddef>
#include <utility>

#include <boost/shared_ptr.hpp>

#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/BitSet.hpp"


#ifndef CDPL_UTIL_ARRAY_CHECKS_DISABLE
#  define CDPL_UTIL_ARRAY_CHECKS_DISABLE 0
#endif // CDPL_UTIL_ARRAY_CHECKS_DISABLE

#ifndef CDPL_UTIL_ARRAY_CHECK_INDEX
#  if (CDPL_UTIL_ARRAY_CHECKS_DISABLE == 0)
#    define CDPL_UTIL_ARRAY_CHECK_INDEX(idx, allow_end) \
	   checkIndex(idx, allow_end)
#  else // CDPL_UTIL_ARRAY_CHECKS_DISABLE != 0
#    define CDPL_UTIL_ARRAY_CHECK_INDEX(idx, allow_end)
#  endif // CDPL_UTIL_ARRAY_CHECKS_DISABLE == 0
#endif // CDPL_UTIL_ARRAY_CHECK_INDEX

#ifndef CDPL_UTIL_ARRAY_CHECK_ITER
#  if (CDPL_UTIL_ARRAY_CHECKS_DISABLE == 0)
#    define CDPL_UTIL_ARRAY_CHECK_ITER(it, allow_end) \
	   checkIterator(it, allow_end)
#  else // CDPL_UTIL_ARRAY_CHECKS_DISABLE != 0
#    define CDPL_UTIL_ARRAY_CHECK_ITER(it, allow_end)
#  endif // CDPL_UTIL_ARRAY_CHECKS_DISABLE == 0
#endif // CDPL_UTIL_ARRAY_CHECK_INDEX


namespace CDPL
{

	namespace Util
	{

		/**
		 * \brief A dynamic array class providing amortized constant time
		 *        access to arbitrary elements.
		 *
		 * \c %Array is essentially a wrapper around \c std::vector and provides similar
		 * (but differently named) methods with the same semantics. Therefore, \c %Array
		 * also models a sequence that supports random access to elements, constant time
		 * insertion and removal of elements at the end, and linear time insertion
		 * and removal of elements at the beginning or in the middle. The number of
		 * elements in the array may vary dynamically and memory management is done
		 * automatically.
		 * However, in contrast to a STL vector, \c %Array provides a virtual destructor
		 * which makes it safe to use \c %Array as a public base class. Furthermore, 
		 * element indices and iterators are generally checked for validity which
		 * makes data access safer and bugs easier to detect. 
		 *
		 * \note Memory will be reallocated automatically if the current capacity of 
		 *       the array is exceeded. Reallocation does not change the size nor does it
		 *       change the values of any elements in the array. However, reallocation
		 *       invalidates any iterators that point into the array and accessing an
		 *       element via an invalid iterator results in undefined behaviour.
		 *       To avoid a memory reallocation, reserve() can be used to allocate enough
		 *       memory in advance.
		 *   
		 * \tparam ValueType The type of objects stored by the array.
		 */
		template <typename ValueType>
		class Array
		{

		public:
			typedef std::vector<ValueType> StorageType;

			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %Array instances.
			 */
			typedef boost::shared_ptr<Array> SharedPointer;

			/**
			 * \brief The type of objects stored by the array. 
			 */
			typedef ValueType ElementType; 

			/**
			 * \brief The type of objects stored by the array. 
			 */
			typedef std::size_t SizeType; 

			/**
			 * \brief Specifies for derived classes the type of the \c %Array base class.
			 *
			 * In this case, the base class is \c %Array itself.
			 *
			 * \see Util::IndirectArray
			 */
			typedef Array BaseType;

			/**
			 * \brief A constant random access iterator used to iterate
			 *        over the elements of the array.
			 */
			typedef typename StorageType::const_iterator ConstElementIterator;

			/**
			 * \brief A constant random access iterator used to iterate
			 *        over the elements of the array in reverse order.
			 */
			typedef typename StorageType::const_reverse_iterator ConstReverseElementIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the
			 *        elements of the array.
			 */
			typedef typename StorageType::iterator ElementIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over
			 *        the elements of the array in reverse order.
			 */
			typedef typename StorageType::reverse_iterator ReverseElementIterator;

			/**
			 * \brief Creates an empty array.
			 */
			Array(): data() {}

			/**
			 * \brief Creates and initializes the array with \a num_elem copies of \a value.
			 * \param num_elem The size of the created array.
			 * \param value The value with which each element of the array will be initialized.
			 */
			Array(std::size_t num_elem, const ValueType& value = ValueType()): data(num_elem, value) {}

			/**
			 * \brief Creates and initializes the array with copies of the elements in the range <em>[first, last)</em>.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			template <typename InputIter>
			Array(const InputIter& first, const InputIter& last): data(first, last) {}

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Array() {}

			StorageType& getData();

			const StorageType& getData() const;

			/**
			 * \brief Returns a non-\c const reference to itself.
			 * \return A non-\c const reference to itself.
			 * \see Util::IndirectArray
			 */
			BaseType& getBase();

			/**
			 * \brief Returns a \c const reference to itself.
			 * \return A \c const reference to itself.
			 * \see Util::IndirectArray
			 */
			const BaseType& getBase() const;

			/**
			 * \brief Returns the number of elements stored in the array.
			 * \return The size of the array.
			 */
			std::size_t getSize() const;

			/**
			 * \brief Returns the number of elements stored in the array.
			 * \return The size of the array.
			 */
			std::size_t size() const;

			/**
			 * \brief Tells whether the array is empty (getSize() == 0).
			 * \return \c true if the array is empty, \c false otherwise.
			 */
			bool isEmpty() const;

			/**
			 * \brief Inserts or erases elements at the end so that the size becomes \a num_elem.
			 * \param num_elem The new size.
			 * \param value The value for newly inserted elements.
			 */
			void resize(std::size_t num_elem, const ValueType& value = ValueType());

			/**
			 * \brief Preallocates memory for (at least) \a num_elem elements.
			 *
			 * If \a num_elem is less than or equal to the current capacity, this call has no effect.
			 * Otherwise, it is a request for allocation of additional memory. If the request is
			 * successful, then the capacity is greater than or equal to \a num_elem. Otherwise, the
			 * capacity is unchanged. In either case, the number of elements will not change.
			 *
			 * \param num_elem The number of elements to reserve memory for.
			 * \see getCapacity()
			 */
			void reserve(std::size_t num_elem);

			/**
			 * \brief Returns the number of elements for which memory has been allocated.
			 * 
			 * The capacity is always greater than or equal to the number of currently 
			 * stored elements.
			 *
			 * \return The current capacity.
			 */
			std::size_t getCapacity() const;

			/**
			 * \brief Erases all elements.
			 */
			void clear();

			/**
			 * \brief Swaps the contents with \a array.
			 * \param array The other array with which the contents will be exchanged.
			 */
			void swap(Array& array);

			/**
			 * \brief This function fills the array with \a num_elem copies of the given \a value.
			 *
			 * Note that the assignment completely changes the array and the new size 
			 * is the same as the number of elements assigned. Old data will be lost.
			 *
			 * \param num_elem The number of elements to be assigned.
			 * \param value The value to be assigned. 
			 */
			void assign(std::size_t num_elem, const ValueType& value = ValueType());

			/**
			 * \brief This function fills a vector with copies of the elements in the range
			 *        <em>[first, last)</em>.
			 *
			 * Note that the assignment completely changes the array and the new size 
			 * is the same as the number of elements assigned. Old data will be lost. 
			 *
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			template <typename InputIter>
			void assign(const InputIter& first, const InputIter& last);

			/**
			 * \brief Inserts a new element at the end of the array.
			 * \param value The value of the new element.
			 */
			void addElement(const ValueType& value = ValueType());

			/**
			 * \brief Inserts a new element before the location specified by the index \a idx.
			 * \param idx The location where to insert the new element.
			 * \param value The value of the element to insert.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize()].
			 */
			void insertElement(std::size_t idx, const ValueType& value = ValueType());

			/**
			 * \brief Inserts a new element before the location specified by the iterator \a it.
			 * \param it The location where to insert the new element.
			 * \param value The value of the element to insert.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd()].
			 */
			ElementIterator insertElement(const ElementIterator& it, const ValueType& value = ValueType());

			/**
			 * \brief Inserts \a num_elem copies of \a value before the location specified by the index \a idx.
			 * \param idx The location where to insert the new elements.
			 * \param num_elem The number of elements to insert.
			 * \param value The value of the elements to insert.
			 * \throw Base::IndexError if \a idx is not in the range [0, getSize()].
			 */
			void insertElements(std::size_t idx, std::size_t num_elem, const ValueType& value = ValueType());

			/**
			 * \brief Inserts \a num_elem copies of \a value before the location specified by the iterator \a it.
			 * \param it The location where to insert the new elements.
			 * \param num_elem The number of elements to insert.
			 * \param value The value of the elements to insert.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd()].
			 */			
			void insertElements(const ElementIterator& it, std::size_t num_elem, const ValueType& value = ValueType());

			/**
			 * \brief Inserts the range of elements <em>[first, last)</em> before the location specified by the index \a idx.
			 * \param idx The location where to insert the new elements.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 * \throw Base::IndexError if \a idx is not in the range [0, getSize()].
			 */			
			template <typename InputIter>
			void insertElements(std::size_t idx, const InputIter& first, const InputIter& last);

			/**
			 * \brief Inserts the range of elements <em>[first, last)</em> before the location specified by the
			 *        iterator \a it.
			 * \param it The location where to insert the new elements.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd()].
			 */		
			template <typename InputIter>
			void insertElements(const ElementIterator& it, const InputIter& first, const InputIter& last);

			/**
			 * \brief Removes the last element of the array.
			 * \throw Base::OperationFailed if the array is empty.
			 */
			void popLastElement();

			/**
			 * \brief Removes the element at the position specified by the index \a idx.
			 * \param idx The zero-based index of the element to remove.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].
			 */
			void removeElement(std::size_t idx);

			/**
			 * \brief Removes the element at the position specified by the iterator \a it.
			 * \param it The iterator specifying the element to remove.
			 * \return An iterator pointing to the position of the element immediately 
			 *         following the one that was removed.
			 * \throw Base::RangeError if the array is empty or \a it is not in the range [getElementsBegin(), getElementsEnd() - 1].
			 */
			ElementIterator removeElement(const ElementIterator& it);
	
			/**
			 * \brief Removes the elements pointed to by the iterators in the range <em>[first, last)</em>.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 * \return An iterator pointing to the position of the element immediately 
			 *         following the ones that were removed.
			 * \throw Base::RangeError if \a first or \a last is not in the range
			 *        [getElementsBegin(), getElementsEnd()] or \a last < \a first.
			 */
			ElementIterator removeElements(const ElementIterator& first, const ElementIterator& last);

			/**
			 * \brief Returns a \c const reference to the first element of the array.
			 * \return A \c const reference to the first element.
			 * \throw Base::OperationFailed if the array is empty.
			 */
			const ValueType& getFirstElement() const;

			/**
			 * \brief Returns a \c const reference to the last element of the array.
			 * \return A \c const reference to the last element.
			 * \throw Base::OperationFailed if the array is empty.
			 */
			const ValueType& getLastElement() const;

			/**
			 * \brief Returns a non-\c const reference to the first element of the array.
			 * \return A non-\c const reference to the first element.
			 * \throw Base::OperationFailed if the array is empty.
			 */
			ValueType& getFirstElement();

			/**
			 * \brief Returns a non-\c const reference to the last element of the array.
			 * \return A non-\c const reference to the last element.
			 * \throw Base::OperationFailed if the array is empty.
			 */
			ValueType& getLastElement();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the array.
			 * \return A constant iterator pointing to the beginning of the array.
			 */
			ConstElementIterator getElementsBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the array.
			 * \return A mutable iterator pointing to the beginning of the array.
			 */
			ElementIterator getElementsBegin();

			/**
			 * \brief Returns a constant iterator pointing to the end of the array.
			 * \return A constant iterator pointing to the end of the array.
			 */
			ConstElementIterator getElementsEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the array.
			 * \return A mutable iterator pointing to the end of the array.
			 */
			ElementIterator getElementsEnd();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the reversed array.
			 * \return A constant iterator pointing to the beginning of the reversed array.
			 */
			ConstReverseElementIterator getElementsReverseBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the reversed array.
			 * \return A mutable iterator pointing to the beginning of the reversed array.
			 */
			ReverseElementIterator getElementsReverseBegin();

			/**
			 * \brief Returns a constant iterator pointing to the end of the reversed array.
			 * \return A constant iterator pointing to the end of the reversed array.
			 */
			ConstReverseElementIterator getElementsReverseEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the reversed array.
			 * \return A mutable iterator pointing to the end of the reversed array.
			 */
			ReverseElementIterator getElementsReverseEnd();

			/**
			 * \brief Returns a \c const reference to the element at index \a idx.
			 *
			 * The method is equivalent to operator[](std::size_t) const.
			 *
			 * \param idx The zero-based index of the element.
			 * \return A \c const reference to the element.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].
			 */
			const ValueType& getElement(std::size_t idx) const;

			/**
			 * \brief Returns a non-\c const reference to the element at index \a idx.
			 *
			 * The method is equivalent to operator[](std::size_t).
			 *
			 * \param idx The zero-based index of the element.
			 * \return A non-\c const reference to the element.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].
			 */
			ValueType& getElement(std::size_t idx);

			/**
			 * \brief Assigns a new value to the element specified by the index \a idx.
			 * \param idx The zero-based index of the element for which to assign a new value.
			 * \param value The new value of the element after assignment.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].
			 */
			void setElement(std::size_t idx, const ValueType& value = ValueType());

			/**
			 * \brief Returns a \c const reference to the element at index \a idx.
			 * \param idx The zero-based index of the element.
			 * \return A \c const reference to the element.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].
			 */
			const ValueType& operator[](std::size_t idx) const;

			/**
			 * \brief Returns a non-\c const reference to the element at index \a idx.
			 * \param idx The zero-based index of the element.
			 * \return A non-\c const reference to the element.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].
			 */
			ValueType& operator[](std::size_t idx);

			/**
			 * \brief Equality comparison operator.
			 *
			 * This is an equivalence relation. It is linear in the size of the
			 * arrays. Two arrays are considered equivalent if their sizes are equal,
			 * and if the corresponding elements compare equal.
			 *
			 * \param array The other array to be compared with.
			 * \return \c true if the sizes and elements of the arrays are 
			 *         equal, and \c false otherwise.
			 * \note \a ValueType must be equality comparable.
			 */
			bool operator==(const Array& array) const;

			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == array)</tt>.
			 *
			 * \param array The array to be compared with.
			 * \return \c true if the sizes or elements of the arrays are 
			 *         non-equal, and \c false otherwise.
			 * \see operator==()
			 */
			bool operator!=(const Array& array) const;

			/**
			 * \brief Less or equal comparison operator.
			 *
			 * The result is equivalent to <tt>!(array < *this)</tt>.
			 *
			 * \param array The other array to be compared with.
			 * \return \c true if this array is lexicographically less
			 *         than or equal to \a array, and \c false otherwise.
			 * \see operator<()
			 */
			bool operator<=(const Array& array) const;

			/**
			 * \brief Greater or equal comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this < array)</tt>.
			 *
			 * \param array The other array to be compared with.
			 * \return \c true if this array is lexicographically greater
			 *         than or equal to \a array, and \c false otherwise.
			 * \see operator<()
			 */
			bool operator>=(const Array& array) const;

			/**
			 * \brief Less than comparison operator.
			 *
			 * The result is \c true if the elements of the array are lexicographically less
			 * than the elements in \a array, and \c false otherwise.
			 *
			 * \param array The other array to be compared with.
			 * \return \c true if this array is lexicographically less than \a array, and 
			 *         \c false otherwise.
			 * \note \a ValueType must be less than comparable.
			 */
			bool operator<(const Array& array) const;

			/**
			 * \brief Greater than comparison operator.
			 *
			 * The result is equivalent to <tt>(array < *this)</tt>.
			 *
			 * \param array The other array to be compared with.
			 * \return \c true if this array is lexicographically greater than \a array, and 
			 *         \c false otherwise.
			 * \see operator<()
			 */
			bool operator>(const Array& array) const;

		protected:
			void checkIfNonEmpty() const;
			void checkIndex(std::size_t idx, bool allow_end) const;
			void checkIterator(const ElementIterator& it, bool allow_end);
			void checkIterator(const ConstElementIterator& it, bool allow_end) const;

			/**
			 * \brief Returns the name of the (derived) array class.
			 *
			 * Overriding this method provides an easy way to customize exception
			 * messages with the name of a derived class. 
			 *
			 * Consider the class \c MyArray which inherits publicly from \c Array<int> and overrides getClassName():
			 * \code
			 * class MyArray : public CDPL::Util::Array<int>
			 * {
			 *
			 *    .....
			 *
			 * private:
			 *    const char* getClassName() const {
			 *       return "MyArray";
			 *    }
			 * };
			 * \endcode
			 *
			 * If, for example, the index in an element access is out of bounds, the error message
			 * of the thrown Base::IndexError will now start with "MyArray: ...." instead of
			 * the default "Array: ....". This small difference already makes the message much
			 * more informative and the bug easier to locate.
			 *
			 * \return The name of the class as a C-string.
			 */
			virtual const char* getClassName() const;

		private:
			void throwIndexError() const;
			void throwRangeError() const;
			void throwOperationFailed() const;

			StorageType data;
		};


		/**
		 * \brief An array of unsigned integers.
		 */
		typedef Array<unsigned int> UIArray;

		/**
		 * \brief An array of unsigned integers of type <tt>std::size_t</tt>.
		 */
		typedef Array<std::size_t> STArray;

		/**
		 * \brief An array of unsigned integers of type <tt>long</tt>.
		 */
		typedef Array<long> LArray;

		/**
		 * \brief A pair of unsigned integers of type <tt>std::size_t</tt>.
		 */
		typedef std::pair<std::size_t, std::size_t> STPair;
		
		/**
		 * \brief An array of pairs of unsigned integers of type <tt>std::size_t</tt>.
		 */
		typedef Array<STPair> STPairArray;

		/**
		 * \brief An array of double precision floating-point numbers.
		 */
		typedef Array<double> DArray;

		/**
		 * \brief An array of <tt>std::string</tt> objects.
		 */
		typedef Array<std::string> SArray;

		/**
		 * \brief An array of <tt>Util::BitSet</tt> objects.
		 */
		typedef Array<BitSet> BitSetArray;
	}
}


// Implementation

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::StorageType& CDPL::Util::Array<ValueType>::getData()
{
	return data;
}

template <typename ValueType>
const typename CDPL::Util::Array<ValueType>::StorageType& CDPL::Util::Array<ValueType>::getData() const
{
	return data;
}

template <typename ValueType>
CDPL::Util::Array<ValueType>& CDPL::Util::Array<ValueType>::getBase()
{
	return *this;
}

template <typename ValueType>
const CDPL::Util::Array<ValueType>& CDPL::Util::Array<ValueType>::getBase() const
{
	return *this;
}

template <typename ValueType>
std::size_t CDPL::Util::Array<ValueType>::getSize() const 
{
	return data.size();
}

template <typename ValueType>
std::size_t CDPL::Util::Array<ValueType>::size() const 
{
	return data.size();
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::isEmpty() const  
{	
	return data.empty();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::resize(std::size_t n, const ValueType& value)  
{
	data.resize(n, value);
}

template <typename ValueType>
std::size_t CDPL::Util::Array<ValueType>::getCapacity() const  
{
	return data.capacity();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::reserve(std::size_t min_size)  
{
	data.reserve(min_size);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::clear()  
{
	data.clear();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::swap(Array& array)  
{
	data.swap(array.data);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::assign(std::size_t n, const ValueType& value)  
{
	data.assign(n, value);
}

template <typename ValueType>
template <typename InputIter>
void CDPL::Util::Array<ValueType>::assign(const InputIter& first, const InputIter& last)  
{
	data.assign(first, last);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::addElement(const ValueType& value)  
{
	data.push_back(value);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::insertElement(std::size_t idx, const ValueType& value)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, true);

	data.insert(data.begin() + idx, value);
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ElementIterator CDPL::Util::Array<ValueType>::insertElement(const ElementIterator& it, 
																								   const ValueType& value)  
{
	CDPL_UTIL_ARRAY_CHECK_ITER(it, true);
	
	return data.insert(it, value);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::insertElements(std::size_t idx, std::size_t n, const ValueType& value)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, true);

	data.insert(data.begin() + idx, n, value);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::insertElements(const ElementIterator& it, std::size_t n, const ValueType& value)  
{
	CDPL_UTIL_ARRAY_CHECK_ITER(it, true);

	data.insert(it, n, value);
}

template <typename ValueType>
template <typename InputIter>
void CDPL::Util::Array<ValueType>::insertElements(std::size_t idx, const InputIter& first, const InputIter& last)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, true);

	data.insert(data.begin() + idx, first, last);
}

template <typename ValueType>
template <typename InputIter>
void CDPL::Util::Array<ValueType>::insertElements(const ElementIterator& it, const InputIter& first, const InputIter& last)  
{	
	CDPL_UTIL_ARRAY_CHECK_ITER(it, true);

	data.insert(it, first, last);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::popLastElement()  
{
	if (data.empty())
		throw Base::OperationFailed("Array: attempt to pop element from an empty array");

	data.pop_back();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::removeElement(std::size_t idx)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, false);

	data.erase(data.begin() + idx);
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ElementIterator CDPL::Util::Array<ValueType>::removeElement(const ElementIterator& it)  
{
	CDPL_UTIL_ARRAY_CHECK_ITER(it, false);

	return data.erase(it);
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ElementIterator CDPL::Util::Array<ValueType>::removeElements(const ElementIterator& first, 
																									const ElementIterator& last)  
{
	CDPL_UTIL_ARRAY_CHECK_ITER(first, true);
	CDPL_UTIL_ARRAY_CHECK_ITER(last, true);

	if (first > last)
		throw Base::RangeError(std::string(getClassName()) + ": invalid iterator range: first > last");

	return data.erase(first, last);
}

template <typename ValueType>
const ValueType& CDPL::Util::Array<ValueType>::getFirstElement() const  
{
	checkIfNonEmpty();
		
	return data.front();
}

template <typename ValueType>
const ValueType& CDPL::Util::Array<ValueType>::getLastElement() const  
{
	checkIfNonEmpty();

	return data.back();
}

template <typename ValueType>
ValueType& CDPL::Util::Array<ValueType>::getFirstElement()  
{
	checkIfNonEmpty();

	return data.front();
}

template <typename ValueType>
ValueType& CDPL::Util::Array<ValueType>::getLastElement()  
{
	checkIfNonEmpty();

	return data.back();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ConstElementIterator CDPL::Util::Array<ValueType>::getElementsBegin() const  
{
	return data.begin();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ElementIterator CDPL::Util::Array<ValueType>::getElementsBegin()  
{
	return data.begin();
}

template <typename ValueType>		
typename CDPL::Util::Array<ValueType>::ConstElementIterator CDPL::Util::Array<ValueType>::getElementsEnd() const  
{
	return data.end();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ElementIterator CDPL::Util::Array<ValueType>::getElementsEnd()  
{
	return data.end();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ConstReverseElementIterator CDPL::Util::Array<ValueType>::getElementsReverseBegin() const  
{
	return data.rbegin();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ReverseElementIterator CDPL::Util::Array<ValueType>::getElementsReverseBegin()  
{
	return data.rbegin();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ConstReverseElementIterator CDPL::Util::Array<ValueType>::getElementsReverseEnd() const  
{
	return data.rend();
}

template <typename ValueType>
typename CDPL::Util::Array<ValueType>::ReverseElementIterator CDPL::Util::Array<ValueType>::getElementsReverseEnd()  
{
	return data.rend();
}

template <typename ValueType>
const ValueType& CDPL::Util::Array<ValueType>::getElement(std::size_t idx) const  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, false);

	return data[idx];
}

template <typename ValueType>
ValueType& CDPL::Util::Array<ValueType>::getElement(std::size_t idx)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, false);

	return data[idx];
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::setElement(std::size_t idx, const ValueType& value)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, false);

	data[idx] = value;
}

template <typename ValueType>
const ValueType& CDPL::Util::Array<ValueType>::operator[](std::size_t idx) const  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, false);

	return data[idx];
}

template <typename ValueType>
ValueType& CDPL::Util::Array<ValueType>::operator[](std::size_t idx)  
{
	CDPL_UTIL_ARRAY_CHECK_INDEX(idx, false);

	return data[idx];
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::operator==(const Array& array) const  
{
	return (data == array.data);
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::operator!=(const Array& array) const  
{
	return (data != array.data);
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::operator<=(const Array& array) const  
{
	return (data <= array.data);
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::operator>=(const Array& array) const  
{
	return (data >= array.data);
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::operator<(const Array& array) const  
{
	return (data < array.data);
}

template <typename ValueType>
bool CDPL::Util::Array<ValueType>::operator>(const Array& array) const  
{
	return (data > array.data);
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::checkIfNonEmpty() const 
{
	if (data.empty())
		throwOperationFailed();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::checkIndex(std::size_t idx, bool allow_end) const 
{
	if ((allow_end && idx > data.size()) || (!allow_end && idx >= data.size()))
		throwIndexError();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::checkIterator(const ElementIterator& it, bool allow_end) 
{
	if (it < data.begin() || (allow_end && it > data.end()) || (!allow_end && it >= data.end()))	
		throwRangeError();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::checkIterator(const ConstElementIterator& it, bool allow_end) const 
{
	if (it < data.begin() || allow_end && it > data.end() || !allow_end && it >= data.end())	
		throwRangeError();
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::throwIndexError() const
{
	throw Base::IndexError(std::string(getClassName()) + ": element index out of bounds");
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::throwRangeError() const
{
	throw Base::RangeError(std::string(getClassName()) + ": invalid iterator");
}

template <typename ValueType>
void CDPL::Util::Array<ValueType>::throwOperationFailed() const 
{
	throw Base::OperationFailed(std::string(getClassName()) + ": operation requires non-empty array");
}

template <typename ValueType>
const char* CDPL::Util::Array<ValueType>::getClassName() const 
{
	return "Array";
}

#endif // CDPL_UTIL_ARRAY_HPP
