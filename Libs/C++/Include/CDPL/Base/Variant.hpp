/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Variant.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::Base::Variant.
 */

#ifndef CDPL_BASE_VARIANT_HPP
#define CDPL_BASE_VARIANT_HPP

#ifdef _MSC_VER
#  pragma warning (disable : 4244) // disable possible loss of data warning
#endif // _MSC_VER

#include <cstddef>
#include <typeinfo>

#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/atomic.hpp>

#include "CDPL/Config.hpp"

#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{ 

	namespace Base
	{

		/**
		 * \brief A safe, type checked container for arbitrary data of variable type.
		 *
		 * \c %Variant implements a safe, type checked container for data of variable type. Instances of \c %Variant
		 * are similar to variables in dynamic programming languages like \e Python where the type of the stored
		 * values may change at runtime. \c %Variant was inspired by <em>Boost.Any</em> [\ref BANY] which serves the
		 * same purpose and provides similar functionality but is not as flexible regarding the handling of built-in 
		 * primitive C++ types.
		 *
		 * \c %Variant allows to store any data whose type fulfills the following requirements:
		 * - The type is copy constructible
		 * - The destructor of the value type upholds the no-throw exception-safety guarantee
		 *
		 * \c %Variant provides three kinds of contructors: A default constructor, a copy constructor and
		 * a constructor that accepts a reference to data of any type. 
		 *
		 * If a \c %Variant instance is created using the latter type of constructor, the instance will
		 * store a copy of the passed data (hence the requirement for copy constructibility of the data type).
		 * A default constructed \c %Variant does not contain any data and is \e empty. To check whether
		 * a \c %Variant object is currently empty, \c %Variant provides the method isEmpty().
		 *
		 * Data objects held by \c %Variant instances are reference counted and a given data object may be referenced
		 * by more than one \c %Variant instance (as a result of copy construction and assignment) at the same time.
		 * When the reference count of a data object reaches zero, i.e. the last \c %Variant instance referencing the
		 * data gets destroyed, the data object is released. Since only object pointers need to be passed, copying of
		 * \c %Variant instances is computationally inexpensive.
		 * 
		 * For direct access to the stored data, \c %Variant provides the member function template getData().
		 * The template argument specifies the type of the contained data that will be returned to the caller by
		 * reference. If the \c %Variant instance is empty, or the stored data are not of the specified
		 * type, getData() will throw a Base::BadCast exception. 
		 * Runtime information regarding the type of the held data can be obtained by the method getTypeID() which
		 * returns a reference to a corresponding <tt>std::type_info</tt> object.
		 *
		 * Normally, stored data can only be extracted under specification of the original data type. However, contained
		 * data of type <tt>std::string</tt> and values of built-in primitive C++ types (\c int, \c long, ...) may also be
		 * retrieved as values of a different type when the conversion to the target type does not result in a loss of
		 * information. For this purpose member functions in the form <tt>type toTYPECODE()</tt> are provided, which 
		 * convert the stored data value into an equivalent value of the specified target type.
		 * The following table provides an overview of the supported conversions from a given source type (specified
		 * in the first column) to the different target types:
		 *
		 * <table bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th rowspan="2" width="5%"><i>Source Type</i></th> <th colspan="16"><i>Target Type</i></th>
		 *  </tr>
		 *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
		 *   <th width="5%"><tt>char</tt></th> <th width="5%"><tt>unsigned char</tt></th>
		 *   <th width="5%"><tt>signed char</tt></th> <th width="5%"><tt>unsigned short</tt></th>
		 *   <th width="5%"><tt>short</tt></th> <th width="5%"><tt>unsigned int</tt></th>
		 *   <th width="5%"><tt>int</tt></th> <th width="5%"><tt>unsigned long</tt></th>
		 *   <th width="5%"><tt>long</tt></th> <th width="5%"><tt>Base::uint64</tt></th>
		 *   <th width="5%"><tt>Base::int64</tt></th> <th width="5%"><tt>float</tt></th>
		 *   <th width="5%"><tt>double</tt></th> <th width="5%"><tt>long double</tt></th>
		 *   <th width="5%"><tt>bool</tt></th> <th width="5%"><tt>std::string</tt></th>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>char</tt></th> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>unsigned char</tt></th> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>signed char</tt></th> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>unsigned short</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>short</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>unsigned int</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>int</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>unsigned long</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>long</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>Base::uint64</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>Base::int64</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>float</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>double</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>long double</tt></th> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td> <td>-</td>
		 *   <td>-</td> <td>-</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>bool</tt></th> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *   <td>+</td> <td>+</td> <td>+</td> <td>+</td> <td>+</td>
		 *  </tr>
		 *  <tr align="center" valign="middle">
		 *   <th bgcolor="#DDDDDD"><tt>std::string</tt></th> <td>+/-</td> <td>+/-</td> <td>+/-</td>
		 *   <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+/-</td>
		 *   <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+/-</td> <td>+</td>
		 *  </tr>
		 * </table>
		 *
		 * In the table a '+' sign denotes that the conversion of the source type to the target type is possible and always
		 * succeeds. A '-' sign indicates that the conversion is \e not supported and any attempt to do so results in a Base::BadCast
		 * exception. The conversion of <tt>std::string</tt> to one of the numeric target types only succeeds if the
		 * string is not empty, contains no whitespace, encodes the numeric value in a supported number format and
		 * the decoded value can be adequately represented by the target type (no overflow/underflow would occur). A
		 * successful conversion of <tt>std::string</tt> to \c char requires that the string contains exactly one character.
		 */
		class Variant 
		{			

		public:
			/**
			 * \brief Constructs an empty \c %Variant instance.
			 */
			Variant() throw(): data(0) {}

			/**
			 * \brief Constructs a \c %Variant instance that references the same data as \a var.
			 * \param var The other \c %Variant instance.
			 * \throw None.
			 */
			Variant(const Variant& var) throw(): data(var.data) {
				if (data)
					data->addRef();
			}

			/**
			 * \brief Constructs a \c %Variant instance that contains a copy of \a data.
			 * \param data The data to store in the created \c %Variant instance.
			 * \throw Throws <tt>std::bad_alloc</tt> or any exceptions arising from the copy constructor of the type \a T.
			 */
			template <typename T>
			Variant(const T& data): data(new DataHolder<T>(data)) {
				this->data->addRef();
			}


			/**
			 * \brief Destroys the \c %Variant instance.
			 */
			~Variant() {
				if (data)
					data->release(); 
			}


			/**
			 * \brief Returns information about the type of the stored data.
			 * \return If non-empty, a reference to the <tt>std::type_info</tt> object describing the type of the
			 *         stored data, and \c typeid(void) otherwise.
			 */
			const std::type_info& getTypeID() const {
				return (data ? data->getTypeID() : typeid(void));
			}
	
			/**
			 * \brief Tells whether the \c %Variant instance stores any data.
			 * \return \c false if the \c %Variant instance is not empty, and \c true otherwise.
			 * \throw None.
			 */
			bool isEmpty() const throw() {
				return (data == 0);
			}

			/**
			 * \brief Assignment operator.
			 *
			 * The currently stored data object gets replaced by the data contained in \a var. 
			 * A self assignment has no effect.
			 *
			 * \param var The other \c %Variant instance.
			 * \return A reference to itself.
			 * \throw None.
			 */
			Variant& operator=(const Variant& var) throw() {
				Variant(var).swap(*this);
				return* this;
			}  
			
			/**
			 * \brief Assignment operator.
			 *
			 * The currently stored data object gets replaced by a copy of \a data. 
			 *
			 * \param data The new data.
			 * \return A reference to itself.
			 * \throw Throws <tt>std::bad_alloc</tt> or any exceptions arising from the copy constructor of the type \a T.
			 */
			template <typename T>
			Variant& operator=(const T& data) {
				Variant(data).swap(*this);
				return* this;
			}

			/**
			 * \brief Swaps the data contained in <tt>*this</tt> and \a var.
			 * \post \a var contains the data previously stored in <tt>*this</tt> and vice versa.
			 * \throw None.
			 */
			void swap(Variant& var) throw() {
				Data* tmp = data;
				data = var.data;
				var.data = tmp;
			}

			/**
			 * \brief Returns a raw pointer to the memory occupied by the stored data.
			 * \return A \c void pointer to the storage occupied by the held data, or \e null if the
			 *         \c %Variant instance is empty.
			 */
			const void* getDataPointer() const {
				if (!data)
					return 0;

				return data->getDataPointer();
			}
				  
			/**
			 * \brief Returns a \c const reference to the stored data of type \a T, or <tt>*this</tt> if \a T is \c %Variant.
			 * \return A \c const reference to the contained data of type \a T, or <tt>*this</tt> if \a T is \c %Variant.
			 * \throw Base::BadCast if the \c %Variant instance is empty, or the stored
			 *        data object is not of the specified type \a T.
			 */
			template <typename T>
			const T& getData() const {
				DataChecker<T>::checkData(data);
				return DataGetter<T>::getData(this);
			}

#define CDPL_MAKE_CONVERSION_FUNC_BODY(TYPE_NAME)          \
				if (!data)                                 \
					throw BadCast("Variant: no data set"); \
														   \
				return data->to##TYPE_NAME()

			/**
			 * \brief Returns the stored data converted into a value of type \c bool.
			 * \return The stored data converted into a value of type \c bool.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type \c bool is not supported.
			 */
			bool toBool() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Bool);
			}
	
			/**
			 * \brief Returns the stored data converted into a value of type \c char.
			 * \return The stored data converted into a value of type \c char.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type \c char is not supported.
			 */
			char toChar() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Char);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>unsigned char</tt>.
			 * \return The stored data converted into a value of type <tt>unsigned char</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>unsigned char</tt> is not supported.
			 */
			unsigned char toUChar() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(UChar);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>signed char</tt>.
			 * \return The stored data converted into a value of type <tt>signed char</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>signed char</tt> is not supported.
			 */
			signed char toSChar() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(SChar);
			}
	
			/**
			 * \brief Returns the stored data converted into a value of type <tt>unsigned short</tt>.
			 * \return The stored data converted into a value of type <tt>unsigned short</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>unsigned short</tt> is not supported.
			 */
			unsigned short toUShort() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(UShort);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>signed short</tt>.
			 * \return The stored data converted into a value of type <tt>signed short</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>signed short</tt> is not supported.
			 */
			signed short toShort() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Short);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>unsigned int</tt>.
			 * \return The stored data converted into a value of type <tt>unsigned int</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>unsigned int</tt> is not supported.
			 */
			unsigned int toUInt() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(UInt);
			}
	
			/**
			 * \brief Returns the stored data converted into a value of type <tt>signed int</tt>.
			 * \return The stored data converted into a value of type <tt>signed int</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>signed int</tt> is not supported.
			 */
			signed int toInt() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Int);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>unsigned long</tt>.
			 * \return The stored data converted into a value of type <tt>unsigned long</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>unsigned long</tt> is not supported.
			 */
			unsigned long toULong() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(ULong);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>signed long</tt>.
			 * \return The stored data converted into a value of type <tt>signed long</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>signed long</tt> is not supported.
			 */
			signed long toLong() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Long);
			}

			/**
			 * \brief Returns the stored data converted into a value of type \c uint64.
			 * \return The stored data converted into a value of type \c uint64.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type \c uint64 is not supported.
			 */
			uint64 toUInt64() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(UInt64);
			}

			/**
			 * \brief Returns the stored data converted into a value of type \c int64.
			 * \return The stored data converted into a value of type \c int64.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type \c int64 is not supported.
			 */
			int64 toInt64() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Int64);
			}

			/**
			 * \brief Returns the stored data converted into a value of type \c float.
			 * \return The stored data converted into a value of type \c float.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type \c float is not supported.
			 */
			float toFloat() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Float);
			}
	
			/**
			 * \brief Returns the stored data converted into a value of type \c double.
			 * \return The stored data converted into a value of type \c double.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type \c double is not supported.
			 */
			double toDouble() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(Double);
			}

			/**
			 * \brief Returns the stored data converted into a value of type <tt>long double</tt>.
			 * \return The stored data converted into a value of type <tt>long double</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>long double</tt> is not supported.
			 */
			long double toLDouble() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(LDouble);
			}
		
			/**
			 * \brief Returns the stored data converted into a value of type <tt>std::string</tt>.
			 * \return The stored data converted into a value of type <tt>std::string</tt>.
			 * \throw Base::BadCast if the \c %Variant instance is empty or the conversion
			 *        of the stored data into the type <tt>std::string</tt> is not supported.
			 */
			std::string toString() const {
				CDPL_MAKE_CONVERSION_FUNC_BODY(String);
			}

#undef CDPL_MAKE_CONVERSION_FUNC_BODY

		private:
			class Data 
			{

			public:
				Data(): refCount(0) {}
				
				virtual ~Data() {}
					
				virtual const std::type_info& getTypeID() const = 0;

				virtual const void* getDataPointer() const = 0;

				void addRef() throw() {
					refCount.fetch_add(1, boost::memory_order_relaxed);
				}

				void release() {
					if (refCount.fetch_sub(1, boost::memory_order_release) == 1) {
						boost::atomic_thread_fence(boost::memory_order_acquire);
						delete this;
					}
				}

#define CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(TYPE, TYPE_NAME)		                                                  \
				virtual TYPE to##TYPE_NAME() const {                                                              \
					throw BadCast(std::string("Variant: conversion of held data of type ") + getTypeID().name() + \
								  std::string("to target type '"#TYPE"' not possible"));                          \
				}

				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(char, Char)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(unsigned char, UChar)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(signed char, SChar)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(unsigned short, UShort)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(signed short, Short)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(unsigned int, UInt)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(signed int, Int)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(unsigned long, ULong)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(signed long, Long)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(bool, Bool)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(float, Float)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(double, Double)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(long double, LDouble)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(uint64, UInt64)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(int64, Int64)
				CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL(std::string, String)

#undef CDPL_MAKE_CONVERSION_FUNC_DEF_IMPL

			private:
				boost::atomic<std::size_t> refCount;
			};

			template <typename T>
			struct DataHolderBase : public Data
			{ 

				const std::type_info& getTypeID() const {
					return typeid(T);
				}

				const void* getDataPointer() const {
					return &getData();
				}

				virtual const T& getData() const = 0;
			};

			template <typename T>
			class DataHolder : public DataHolderBase<T>
			{ 

			public:
				DataHolder(const T& d): data(d) {}

				const T& getData() const {
					return data;
				}

			private:
				const T data;
			};

			template <typename T>
			struct DataGetter
			{ 

				static const T& getData(const Variant* var) { 
					if (var->data->getTypeID() == typeid(T)) {
						const Variant::DataHolderBase<T>* dh = static_cast<const DataHolderBase<T>*>(var->data);
						return dh->getData();
					}

					throw BadCast(std::string("Variant: extraction of held data of type '") + var->data->getTypeID().name() + 
								  std::string("' as data of type '") + typeid(T).name() + "' not possible");
				}
			};

			template <typename T>
			struct DataChecker
			{ 

				static void checkData(const Data* data) { 
					if (!data)
						throw BadCast("Variant: no data set");
				}
			};

			Data* data;
		};

		template <>
		struct Variant::DataGetter<Variant>
		{ 

			static const Variant& getData(const Variant* var) {
				return *var;
			}
		};

		template <>
		struct Variant::DataChecker<Variant>
		{ 

			static void checkData(const Variant::Data*) {}
		};

#define CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(TYPE, TYPE_NAME) \
			TYPE to##TYPE_NAME() const {                    \
				return data;                                \
			}

#define CDPL_MAKE_TO_STRING_CONVERSION_FUNC(TYPE)                                  \
			std::string toString() const {                                         \
				return boost::lexical_cast<std::string>(static_cast<TYPE>(data));  \
			}

#define CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(TYPE, TYPE_NAME)                            \
			TYPE to##TYPE_NAME() const {                                                    \
				try {														                \
					return boost::lexical_cast<TYPE>(data);                                 \
                                                                                            \
				} catch (std::bad_cast& ex) {                                               \
					throw BadCast("Variant: conversion of held data of type 'std::string' " \
								  "to target type '"#TYPE"' failed");                       \
				}                                                                           \
			}

#define CDPL_STRING_HOLDER_CONVERSION_FUNC_UCHAR                                                          \
			unsigned char toUChar() const {                                                               \
				try {														                              \
					return boost::numeric_cast<unsigned char>(boost::lexical_cast<unsigned short>(data)); \
                                                                                                          \
				} catch (std::bad_cast& ex) {                                                             \
					throw BadCast("Variant: conversion of held data of type 'std::string' "               \
								  "to target type 'unsigned char' failed");                               \
				}                                                                                         \
			}

#define CDPL_STRING_HOLDER_CONVERSION_FUNC_SCHAR                                                          \
			signed char toSChar() const {                                                                 \
				try {													                                  \
					return boost::numeric_cast<signed char>(boost::lexical_cast<signed short>(data));     \
                                                                                                          \
				} catch (std::bad_cast& ex) {                                                             \
					throw BadCast("Variant: conversion of held data of type 'std::string' "               \
								  "to target type 'unsigned char' failed");                               \
				}                                                                                         \
			}

#define CDPL_CONVERSION_FUNC_CHAR    CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(char, Char)
#define CDPL_CONVERSION_FUNC_UCHAR   CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(unsigned char, UChar)
#define CDPL_CONVERSION_FUNC_SCHAR   CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(signed char, SChar)
#define CDPL_CONVERSION_FUNC_USHORT  CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(unsigned short, UShort)
#define CDPL_CONVERSION_FUNC_SHORT   CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(signed short, Short)
#define CDPL_CONVERSION_FUNC_UINT    CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(unsigned int, UInt)
#define CDPL_CONVERSION_FUNC_INT     CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(signed int, Int)
#define CDPL_CONVERSION_FUNC_ULONG   CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(unsigned long, ULong)
#define CDPL_CONVERSION_FUNC_LONG    CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(signed long, Long)
#define CDPL_CONVERSION_FUNC_BOOL    CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(bool, Bool)
#define CDPL_CONVERSION_FUNC_FLOAT   CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(float, Float)
#define CDPL_CONVERSION_FUNC_DOUBLE  CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(double, Double)
#define CDPL_CONVERSION_FUNC_LDOUBLE CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(long double, LDouble)
#define CDPL_CONVERSION_FUNC_UINT64  CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(uint64, UInt64)
#define CDPL_CONVERSION_FUNC_INT64   CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(int64, Int64)

#define CDPL_MAKE_DATA_HOLDER(TYPE, CONVERSION_FUNCS)                          \
		template <>                                                            \
		class Variant::DataHolder<TYPE> : public Variant::DataHolderBase<TYPE> \
		{                                                                      \
                                                                               \
		public:                                                                \
			DataHolder(const TYPE& d): data(d) {}                              \
                                                                               \
 			const TYPE& getData() const {                                      \
				return data;                                                   \
			}                                                                  \
                                                                               \
			CONVERSION_FUNCS                                                   \
                                                                               \
		private:                                                               \
			const TYPE data;                                                   \
		};

		CDPL_MAKE_DATA_HOLDER(std::string,                                                    \
                              CDPL_MAKE_IMPLICIT_CONVERSION_FUNC(std::string, String)         \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(char, Char)             \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(unsigned short, UShort) \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(signed short, Short)    \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(unsigned int, UInt)     \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(signed int, Int)        \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(unsigned long, ULong)   \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(signed long, Long)      \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(bool, Bool)             \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(float, Float)           \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(double, Double)         \
							  CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(long double, LDouble)   \
                              CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(uint64, UInt64)         \
                              CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC(int64, Int64)           \
							  CDPL_STRING_HOLDER_CONVERSION_FUNC_UCHAR                        \
							  CDPL_STRING_HOLDER_CONVERSION_FUNC_SCHAR)
  
		CDPL_MAKE_DATA_HOLDER(char,                                      \
							  CDPL_CONVERSION_FUNC_CHAR                  \
							  CDPL_CONVERSION_FUNC_UCHAR                 \
							  CDPL_CONVERSION_FUNC_SCHAR                 \
							  CDPL_CONVERSION_FUNC_USHORT				 \
							  CDPL_CONVERSION_FUNC_SHORT                 \
							  CDPL_CONVERSION_FUNC_UINT                  \
							  CDPL_CONVERSION_FUNC_INT                   \
							  CDPL_CONVERSION_FUNC_ULONG				 \
							  CDPL_CONVERSION_FUNC_LONG                  \
							  CDPL_CONVERSION_FUNC_BOOL                  \
							  CDPL_CONVERSION_FUNC_FLOAT                 \
							  CDPL_CONVERSION_FUNC_DOUBLE				 \
							  CDPL_CONVERSION_FUNC_LDOUBLE               \
							  CDPL_CONVERSION_FUNC_UINT64                \
							  CDPL_CONVERSION_FUNC_INT64	             \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(char))

		CDPL_MAKE_DATA_HOLDER(unsigned char,                                       \
							  CDPL_CONVERSION_FUNC_UCHAR                           \
							  CDPL_CONVERSION_FUNC_CHAR                            \
							  CDPL_CONVERSION_FUNC_SCHAR                           \
							  CDPL_CONVERSION_FUNC_USHORT				           \
							  CDPL_CONVERSION_FUNC_SHORT                           \
							  CDPL_CONVERSION_FUNC_UINT                            \
							  CDPL_CONVERSION_FUNC_INT                             \
							  CDPL_CONVERSION_FUNC_ULONG				           \
							  CDPL_CONVERSION_FUNC_LONG                            \
							  CDPL_CONVERSION_FUNC_BOOL                            \
							  CDPL_CONVERSION_FUNC_FLOAT                           \
							  CDPL_CONVERSION_FUNC_DOUBLE				           \
							  CDPL_CONVERSION_FUNC_LDOUBLE                         \
							  CDPL_CONVERSION_FUNC_UINT64                          \
							  CDPL_CONVERSION_FUNC_INT64		                   \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(unsigned short))
				
		CDPL_MAKE_DATA_HOLDER(unsigned short,                                      \
							  CDPL_CONVERSION_FUNC_USHORT                          \
							  CDPL_CONVERSION_FUNC_SHORT                           \
							  CDPL_CONVERSION_FUNC_UINT                            \
							  CDPL_CONVERSION_FUNC_INT					           \
							  CDPL_CONVERSION_FUNC_ULONG                           \
							  CDPL_CONVERSION_FUNC_LONG                            \
							  CDPL_CONVERSION_FUNC_BOOL                            \
							  CDPL_CONVERSION_FUNC_FLOAT				           \
							  CDPL_CONVERSION_FUNC_DOUBLE                          \
							  CDPL_CONVERSION_FUNC_LDOUBLE                         \
							  CDPL_CONVERSION_FUNC_UINT64                          \
							  CDPL_CONVERSION_FUNC_INT64			               \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(unsigned short))

		CDPL_MAKE_DATA_HOLDER(unsigned int,                                      \
							  CDPL_CONVERSION_FUNC_UINT                          \
							  CDPL_CONVERSION_FUNC_INT                           \
							  CDPL_CONVERSION_FUNC_ULONG                         \
							  CDPL_CONVERSION_FUNC_LONG					         \
							  CDPL_CONVERSION_FUNC_BOOL                          \
							  CDPL_CONVERSION_FUNC_FLOAT                         \
							  CDPL_CONVERSION_FUNC_DOUBLE                        \
							  CDPL_CONVERSION_FUNC_LDOUBLE				         \
							  CDPL_CONVERSION_FUNC_UINT64                        \
							  CDPL_CONVERSION_FUNC_INT64				         \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(unsigned int))

		CDPL_MAKE_DATA_HOLDER(unsigned long,                                      \
							  CDPL_CONVERSION_FUNC_ULONG                          \
							  CDPL_CONVERSION_FUNC_LONG                           \
							  CDPL_CONVERSION_FUNC_BOOL                           \
							  CDPL_CONVERSION_FUNC_FLOAT				          \
							  CDPL_CONVERSION_FUNC_DOUBLE                         \
							  CDPL_CONVERSION_FUNC_LDOUBLE                        \
							  CDPL_CONVERSION_FUNC_UINT64                         \
							  CDPL_CONVERSION_FUNC_INT64				          \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(unsigned long))

		CDPL_MAKE_DATA_HOLDER(signed char,                                       \
							  CDPL_CONVERSION_FUNC_SCHAR                         \
							  CDPL_CONVERSION_FUNC_UCHAR                         \
							  CDPL_CONVERSION_FUNC_CHAR                          \
							  CDPL_CONVERSION_FUNC_USHORT				         \
							  CDPL_CONVERSION_FUNC_SHORT                         \
							  CDPL_CONVERSION_FUNC_UINT                          \
							  CDPL_CONVERSION_FUNC_INT                           \
							  CDPL_CONVERSION_FUNC_ULONG				         \
							  CDPL_CONVERSION_FUNC_LONG                          \
							  CDPL_CONVERSION_FUNC_BOOL                          \
							  CDPL_CONVERSION_FUNC_FLOAT                         \
							  CDPL_CONVERSION_FUNC_DOUBLE				         \
							  CDPL_CONVERSION_FUNC_LDOUBLE                       \
							  CDPL_CONVERSION_FUNC_UINT64                        \
							  CDPL_CONVERSION_FUNC_INT64				         \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(signed short))

		CDPL_MAKE_DATA_HOLDER(signed short,                                      \
							  CDPL_CONVERSION_FUNC_SHORT                         \
							  CDPL_CONVERSION_FUNC_USHORT                        \
							  CDPL_CONVERSION_FUNC_UINT                          \
							  CDPL_CONVERSION_FUNC_INT					         \
							  CDPL_CONVERSION_FUNC_ULONG                         \
							  CDPL_CONVERSION_FUNC_LONG                          \
							  CDPL_CONVERSION_FUNC_BOOL                          \
							  CDPL_CONVERSION_FUNC_FLOAT				         \
							  CDPL_CONVERSION_FUNC_DOUBLE                        \
							  CDPL_CONVERSION_FUNC_LDOUBLE                       \
							  CDPL_CONVERSION_FUNC_UINT64                        \
							  CDPL_CONVERSION_FUNC_INT64				         \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(signed short))

		CDPL_MAKE_DATA_HOLDER(signed int,                                      \
							  CDPL_CONVERSION_FUNC_INT                         \
							  CDPL_CONVERSION_FUNC_UINT                        \
							  CDPL_CONVERSION_FUNC_ULONG                       \
							  CDPL_CONVERSION_FUNC_LONG                        \
							  CDPL_CONVERSION_FUNC_BOOL                        \
							  CDPL_CONVERSION_FUNC_FLOAT                       \
							  CDPL_CONVERSION_FUNC_DOUBLE                      \
							  CDPL_CONVERSION_FUNC_LDOUBLE                     \
							  CDPL_CONVERSION_FUNC_UINT64                      \
							  CDPL_CONVERSION_FUNC_INT64                       \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(signed int))

		CDPL_MAKE_DATA_HOLDER(signed long,                                      \
							  CDPL_CONVERSION_FUNC_LONG                         \
							  CDPL_CONVERSION_FUNC_ULONG                        \
							  CDPL_CONVERSION_FUNC_BOOL                         \
							  CDPL_CONVERSION_FUNC_FLOAT                        \
							  CDPL_CONVERSION_FUNC_DOUBLE                       \
							  CDPL_CONVERSION_FUNC_LDOUBLE                      \
							  CDPL_CONVERSION_FUNC_UINT64                       \
							  CDPL_CONVERSION_FUNC_INT64                        \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(signed long))

		CDPL_MAKE_DATA_HOLDER(bool,                                      \
							  CDPL_CONVERSION_FUNC_BOOL                  \
							  CDPL_CONVERSION_FUNC_CHAR                  \
							  CDPL_CONVERSION_FUNC_UCHAR                 \
							  CDPL_CONVERSION_FUNC_SCHAR                 \
							  CDPL_CONVERSION_FUNC_USHORT                \
							  CDPL_CONVERSION_FUNC_SHORT                 \
							  CDPL_CONVERSION_FUNC_UINT                  \
							  CDPL_CONVERSION_FUNC_INT                   \
							  CDPL_CONVERSION_FUNC_ULONG                 \
							  CDPL_CONVERSION_FUNC_LONG                  \
							  CDPL_CONVERSION_FUNC_FLOAT                 \
							  CDPL_CONVERSION_FUNC_DOUBLE                \
							  CDPL_CONVERSION_FUNC_LDOUBLE               \
							  CDPL_CONVERSION_FUNC_UINT64                \
							  CDPL_CONVERSION_FUNC_INT64                 \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(bool))

		CDPL_MAKE_DATA_HOLDER(float,                                      \
							  CDPL_CONVERSION_FUNC_FLOAT                  \
							  CDPL_CONVERSION_FUNC_BOOL                   \
							  CDPL_CONVERSION_FUNC_DOUBLE                 \
							  CDPL_CONVERSION_FUNC_LDOUBLE				  \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(float))
	
		CDPL_MAKE_DATA_HOLDER(double,                                      \
							  CDPL_CONVERSION_FUNC_DOUBLE                  \
							  CDPL_CONVERSION_FUNC_BOOL                    \
							  CDPL_CONVERSION_FUNC_LDOUBLE				   \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(double))

		CDPL_MAKE_DATA_HOLDER(long double,                                      \
							  CDPL_CONVERSION_FUNC_LDOUBLE                      \
							  CDPL_CONVERSION_FUNC_BOOL					        \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(long double))

#if SIZEOF_LONG_INT != 8
		CDPL_MAKE_DATA_HOLDER(uint64,                                      \
							  CDPL_CONVERSION_FUNC_UINT64                  \
							  CDPL_CONVERSION_FUNC_INT64                   \
							  CDPL_CONVERSION_FUNC_BOOL                    \
							  CDPL_CONVERSION_FUNC_FLOAT				   \
							  CDPL_CONVERSION_FUNC_DOUBLE                  \
							  CDPL_CONVERSION_FUNC_LDOUBLE				   \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(uint64))

		CDPL_MAKE_DATA_HOLDER(int64,                                      \
							  CDPL_CONVERSION_FUNC_INT64                  \
							  CDPL_CONVERSION_FUNC_UINT64                 \
							  CDPL_CONVERSION_FUNC_BOOL                   \
							  CDPL_CONVERSION_FUNC_FLOAT				  \
							  CDPL_CONVERSION_FUNC_DOUBLE                 \
							  CDPL_CONVERSION_FUNC_LDOUBLE				  \
							  CDPL_MAKE_TO_STRING_CONVERSION_FUNC(int64))
#endif // SIZEOF_LONG_INT != 8

#undef CDPL_MAKE_IMPLICIT_CONVERSION_FUNC
#undef CDPL_MAKE_TO_STRING_CONVERSION_FUNC
#undef CDPL_MAKE_STRING_HOLDER_CONVERSION_FUNC
#undef CDPL_STRING_HOLDER_CONVERSION_FUNC_UCHAR
#undef CDPL_STRING_HOLDER_CONVERSION_FUNC_SCHAR
#undef CDPL_CONVERSION_FUNC_CHAR
#undef CDPL_CONVERSION_FUNC_UCHAR
#undef CDPL_CONVERSION_FUNC_SCHAR
#undef CDPL_CONVERSION_FUNC_USHORT
#undef CDPL_CONVERSION_FUNC_SHORT
#undef CDPL_CONVERSION_FUNC_UINT
#undef CDPL_CONVERSION_FUNC_INT
#undef CDPL_CONVERSION_FUNC_ULONG
#undef CDPL_CONVERSION_FUNC_LONG
#undef CDPL_CONVERSION_FUNC_BOOL
#undef CDPL_CONVERSION_FUNC_FLOAT
#undef CDPL_CONVERSION_FUNC_DOUBLE
#undef CDPL_CONVERSION_FUNC_LDOUBLE
#undef CDPL_CONVERSION_FUNC_UINT64
#undef CDPL_CONVERSION_FUNC_INT64
#undef CDPL_MAKE_DATA_HOLDER

	}
}

#endif // CDPL_BASE_VARIANT_HPP
