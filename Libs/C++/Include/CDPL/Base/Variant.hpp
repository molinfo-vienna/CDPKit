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
#include <atomic>

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
		 * same purpose and provides similar functionality.
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
				return (!data);
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

		private:
			class Data 
			{

			public:
				Data(): refCount(0) {}
				
				virtual ~Data() {}
					
				virtual const std::type_info& getTypeID() const = 0;

				virtual const void* getDataPointer() const = 0;

				void addRef() throw() {
					refCount.fetch_add(1, std::memory_order_relaxed);
				}

				void release() {
					if (refCount.fetch_sub(1, std::memory_order_release) == 1) {
						std::atomic_thread_fence(std::memory_order_acquire);
						delete this;
					}
				}

			private:
				std::atomic<std::size_t> refCount;
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
	}
}

#endif // CDPL_BASE_VARIANT_HPP
