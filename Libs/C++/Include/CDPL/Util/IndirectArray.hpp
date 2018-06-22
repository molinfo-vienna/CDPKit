/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * IndirectArray.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Util::IndirectArray.
 */

#ifndef CDPL_UTIL_INDIRECTARRAY_HPP
#define CDPL_UTIL_INDIRECTARRAY_HPP

#include <boost/iterator/transform_iterator.hpp>
#include <boost/mpl/if.hpp>

#include "CDPL/Util/Dereferencer.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

	namespace Util
	{

		/**
		 * \addtogroup CDPL_UTIL_CONTAINERS
		 * @{
		 */

		/**
		 * \brief A dynamic array class for the storage of object pointers with an indirected query interface.
		 *
		 * \c %IndirectArray stores pointers to objects instead of object copies and provides an indirected query
		 * interface. That is, methods for accessing an array element do not directly return the stored pointer
		 * but return a reference to the pointed-to object. This is also true for iterators pointing into the
		 * array which will return a reference to the pointed-to object upon dereferenciation. To  
		 * increase code correctness and safety, \c %IndirectArray can be configured to check if 
		 * an object pointer is \e null before a dereferenciation or object access is attempted.
		 * Since \c %IndirectArray publicly derives from Util::Array (which provides the storage for the pointers),
		 * \c %IndirectArray has the same characteristics regarding dynamic memory management and time complexity
		 * of various modifying and non-modifying operations. 
		 * 		  
		 * \tparam ValueType The type of the pointed-to objects.
		 * \tparam PointerType The type of the stored pointers.
		 * \tparam NullPointerCheck Whether to check for \e null pointers.
		 * \note If \e null pointer checking is enabled, a Base::NullPointerException will
		 *       be thrown whenever an operation on an iterator object or array element access
		 *       would require the dereferenciation of a \e null pointer.
		 */
		template <typename ValueType, typename PointerType = typename ValueType::SharedPointer, bool NullPointerCheck = true>
		class IndirectArray : public Array<PointerType>
		{

			typedef typename boost::mpl::if_c<NullPointerCheck, 
											  NullCheckDereferencer<PointerType, ValueType&>, 
											  Dereferencer<PointerType, ValueType&> >::type DerefFunc;	

		public:
			/**
			 * \brief The type of the public Array<PointerType> base class storing the
			 *        pointer elements. 
			 */
			typedef Array<PointerType> BaseType;

			/**
			 * \brief The type of the object that is obtained after dereferenciation of
			 *        a stored pointer element. 
			 */
			typedef ValueType ElementType;

			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %IndirectArray instances.
			 */
			typedef boost::shared_ptr<IndirectArray> SharedPointer;
 
			/**
			 * \brief A constant random access iterator used to iterate
			 *        over the pointed-to objects.
			 */
			typedef boost::transform_iterator<DerefFunc, typename BaseType::ConstElementIterator, 
											  const ValueType&> ConstElementIterator;

			/**
			 * \brief A constant random access iterator used to iterate
			 *        over the pointed-to objects in reverse order.
			 */
			typedef boost::transform_iterator<DerefFunc, typename BaseType::ConstReverseElementIterator, 
											  const ValueType&> ConstReverseElementIterator;

			/**
			 * \brief A mutable random access iterator used to iterate
			 *        over the pointed-to objects.
			 */
			typedef boost::transform_iterator<DerefFunc, typename BaseType::ElementIterator, 
											  ValueType&> ElementIterator;

			/**
			 * \brief A mutable random access iterator used to iterate
			 *        over the pointed-to objects in reverse order.
			 */
			typedef boost::transform_iterator<DerefFunc, typename BaseType::ReverseElementIterator, 
											  ValueType&> ReverseElementIterator;
			/**
			 * \brief Creates an empty array.
			 */
			IndirectArray(): BaseType() {}

			/**
			 * \brief Creates and initializes the array with \a num_elem copies of \a ptr.
			 * \param num_elem The size of the created array.
			 * \param ptr The value with which each pointer element of the array will be initialized.
			 */
			IndirectArray(std::size_t num_elem, const PointerType& ptr = PointerType()): BaseType(num_elem, ptr) {}

			/**
			 * \brief Creates and initializes the array with copies of the pointers in the
			 *        range <em>[first, last)</em>.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			template <typename InputIter>
			IndirectArray(const InputIter& first, const InputIter& last): BaseType(first, last) {}

			/**
			 * \brief Virtual destructor. 
			 */
			virtual ~IndirectArray() {}
	
			using BaseType::insertElement;

			/**
			 * \brief Inserts a new element before the location specified by the iterator \a it.
			 * \param it The location where to insert the new element.
			 * \param ptr The value of pointer element to insert.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd()].
			 */
			ElementIterator insertElement(const ElementIterator& it, const PointerType& ptr);

			using BaseType::insertElements;

			/**
			 * \brief Inserts \a num_elem copies of \a ptr before the location specified by the iterator \a it.
			 * \param it The location where to insert the new pointers.
			 * \param num_elem The number of pointers to insert.
			 * \param ptr The value of the pointer elements to insert.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd()].
			 */		
			void insertElements(const ElementIterator& it, std::size_t num_elem, const PointerType& ptr);

			/**
			 * \brief Inserts the range of pointers <em>[first, last)</em> before the location specified by the
			 *        iterator \a it.
			 * \param it The location where to insert the new pointer elements.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd()].
			 */		
			template <typename InputIter>
			void insertElements(const ElementIterator& it, const InputIter& first, const InputIter& last);

			using BaseType::removeElement;
	
			/**
			 * \brief Removes the element at the position specified by the iterator \a it.
			 * \param it The iterator specifying the pointer to remove.
			 * \return An iterator pointing to the position of the pointer element immediately 
			 *         following the one that was removed.
			 * \throw Base::RangeError if \a it is not in the range [getElementsBegin(), getElementsEnd() - 1].
			 */
			ElementIterator removeElement(const ElementIterator& it);

			using BaseType::removeElements;

			/**
			 * \brief Removes the elements pointed to by the iterators in the range <em>[first, last)</em>.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 * \return An iterator pointing to the position of the pointer element immediately 
			 *         following the ones that were removed.
			 * \throw Base::RangeError if \a first or \a last is not in the range
			 *        [getElementsBegin(), getElementsEnd()] or \a last < \a first.
			 */
			ElementIterator removeElements(const ElementIterator& first, const ElementIterator& last);

			/**
			 * \brief Returns a \c const reference to the object pointed to by the first 
			 *        element of the array.
			 * \return A \c const reference to the first pointed-to object.
			 * \throw Base::OperationFailed if the array is empty. Base::NullPointerException
			 *        if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			const ValueType& getFirstElement() const;

			/**
			 * \brief Returns a \c const reference to the object pointed to by the last 
			 *        element of the array.
			 * \return A \c const reference to the last pointed-to object.
			 * \throw Base::OperationFailed if the array is empty. Base::NullPointerException
			 *        if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			const ValueType& getLastElement() const;

			/**
			 * \brief Returns a non-\c const reference to the object pointed to by the first 
			 *        element of the array.
			 * \return A non-\c const reference to the first pointed-to object.
			 * \throw Base::OperationFailed if the array is empty. Base::NullPointerException
			 *        if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			ValueType& getFirstElement();

			/**
			 * \brief Returns a non-\c const reference to the object pointed to by the last 
			 *        element of the array.
			 * \return A non-\c const reference to the last pointed-to object.
			 * \throw Base::OperationFailed if the array is empty. Base::NullPointerException
			 *        if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			ValueType& getLastElement();

			/**
			 * \brief Returns a constant iterator over the pointed-to objects that points to
			 *        the beginning of the array.
			 * \return A constant iterator over the pointed-to objects.
			 */
			ConstElementIterator getElementsBegin() const;

			/**
			 * \brief Returns a mutable iterator over the pointed-to objects that points to
			 *        the beginning of the array.
			 * \return A mutable iterator over the pointed-to objects.
			 */
			ElementIterator getElementsBegin();

			/**
			 * \brief Returns a constant iterator over the pointed-to objects that points to
			 *        the end of the array.
			 * \return A constant iterator over the pointed-to objects.
			 */
			ConstElementIterator getElementsEnd() const;

			/**
			 * \brief Returns a mutable iterator over the pointed-to objects that points to
			 *        the end of the array.
			 * \return A mutable iterator over the pointed-to objects.
			 */
			ElementIterator getElementsEnd();

			/**
			 * \brief Returns a constant iterator over the pointed-to objects that points to
			 *        the beginning of the reversed array.
			 * \return A constant iterator over the pointed-to objects.
			 */
			ConstReverseElementIterator getElementsReverseBegin() const;

			/**
			 * \brief Returns a mutable iterator over the pointed-to objects that points to
			 *        the beginning of the reversed array.
			 * \return A mutable iterator over the pointed-to objects.
			 */
			ReverseElementIterator getElementsReverseBegin();

			/**
			 * \brief Returns a constant iterator over the pointed-to objects that points to
			 *        the end of the reversed array.
			 * \return A constant iterator over the pointed-to objects.
			 */
			ConstReverseElementIterator getElementsReverseEnd() const;

			/**
			 * \brief Returns a mutable iterator over the pointed-to objects that points to
			 *        the end of the reversed array.
			 * \return A mutable iterator over the pointed-to objects.
			 */
			ReverseElementIterator getElementsReverseEnd();
	
			/**
			 * \brief Returns a \c const reference to the object pointed-to by the pointer
			 *        element at index \a idx.
			 *
			 * The method is equivalent to operator[](std::size_t) const.
			 *
			 * \param idx The zero-based index of the pointer element.
			 * \return A \c const reference to the pointed-to object.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1]. 
			 *        Base::NullPointerException if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			const ValueType& getElement(std::size_t idx) const;

			/**
			 * \brief Returns a non-\c const reference to the object pointed-to by the pointer
			 *        element at index \a idx.
			 *
			 * The method is equivalent to operator[](std::size_t) const.
			 *
			 * \param idx The zero-based index of the pointer element.
			 * \return A non-\c const reference to the pointed-to object.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1]. 
			 *        Base::NullPointerException if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			ValueType& getElement(std::size_t idx);

			/**
			 * \brief Returns a \c const reference to the object pointed-to by the pointer
			 *        element at index \a idx.
			 * \param idx The zero-based index of the pointer element.
			 * \return A \c const reference to the pointed-to object.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1]. 
			 *        Base::NullPointerException if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			const ValueType& operator[](std::size_t idx) const;

			/**
			 * \brief Returns a non-\c const reference to the object pointed-to by the
			 *        pointer element at index \a idx.
			 * \param idx The zero-based index of the pointer element.
			 * \return A non-\c const reference to the pointed-to object.
			 * \throw Base::IndexError if the array is empty or \a idx is not in the range [0, getSize() - 1].  
			 *        Base::NullPointerException if \e null pointer checking is enabled and the object pointer is \e null.
			 */
			ValueType& operator[](std::size_t idx);

		private:
			virtual const char* getClassName() const;

			DerefFunc dereferencer;
		};

		/**
		 * @}
		 */
	}
}


// Implementation of IndirectArray<>

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::insertElement(const ElementIterator& it, const PointerType& ptr)  
{
	return ElementIterator(Array<PointerType>::insertElement(it.base(), ptr));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
void CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::insertElements(const ElementIterator& it, std::size_t n, 
																								const PointerType& ptr)  
{
	Array<PointerType>::insertElements(it.base(), n, ptr);	
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
template <typename InputIter>
void CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::insertElements(const ElementIterator& it, const InputIter& first, 
																								const InputIter& last)  
{	
	Array<PointerType>::insertElements(it.base(), first, last);	
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::removeElement(const ElementIterator& it)  
{
	return ElementIterator(Array<PointerType>::removeElement(it.base()));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::removeElements(const ElementIterator& first, const ElementIterator& last)  
{
	return ElementIterator(Array<PointerType>::removeElements(first.base(), last.base()));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
const ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getFirstElement() const  
{
	return dereferencer(Array<PointerType>::getFirstElement());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
const ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getLastElement() const  
{
	return dereferencer(Array<PointerType>::getLastElement());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getFirstElement()  
{
	return dereferencer(Array<PointerType>::getFirstElement());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getLastElement()  
{
	return dereferencer(Array<PointerType>::getLastElement());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ConstElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsBegin() const  
{
	return ConstElementIterator(Array<PointerType>::getElementsBegin());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsBegin()  
{
	return ElementIterator(Array<PointerType>::getElementsBegin());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>		
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ConstElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsEnd() const  
{
	return ConstElementIterator(Array<PointerType>::getElementsEnd());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsEnd()  
{
	return ElementIterator(Array<PointerType>::getElementsEnd());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ConstReverseElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsReverseBegin() const  
{
	return ConstReverseElementIterator(Array<PointerType>::getElementsReverseBegin());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ReverseElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsReverseBegin()  
{
	return ReverseElementIterator(Array<PointerType>::getElementsReverseBegin());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ConstReverseElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsReverseEnd() const  
{
	return ConstReverseElementIterator(Array<PointerType>::getElementsReverseEnd());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
typename CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::ReverseElementIterator 
CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElementsReverseEnd()  
{
	return ReverseElementIterator(Array<PointerType>::getElementsReverseEnd());
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
const ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElement(std::size_t idx) const  
{
	return dereferencer(Array<PointerType>::getElement(idx));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getElement(std::size_t idx)  
{
	return dereferencer(Array<PointerType>::getElement(idx));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
const ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::operator[](std::size_t idx) const  
{
	return dereferencer(Array<PointerType>::operator[](idx));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
ValueType& CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::operator[](std::size_t idx)  
{
	return dereferencer(Array<PointerType>::operator[](idx));
}

template <typename ValueType, typename PointerType, bool NullPointerCheck>
const char* CDPL::Util::IndirectArray<ValueType, PointerType, NullPointerCheck>::getClassName() const 
{
	return "IndirectArray";
}

#endif // CDPL_UTIL_INDIRECTARRAY_HPP
