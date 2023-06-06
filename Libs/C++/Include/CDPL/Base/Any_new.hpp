/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Any.hpp 
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
 * \brief Definition of the class CDPL::Base::Any.
 */

#ifndef CDPL_BASE_ANY_HPP
#define CDPL_BASE_ANY_HPP

#include <typeinfo>
#include <type_traits>
#include <stdexcept>
#include <utility>
#include <new>

#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{ 

	namespace Base
	{

		/**
		 * \brief A safe, type checked container for arbitrary data of variable type.
		 *
		 * The code is based on the std::experimental::any (N4562, merged into C++17) implementation for C++11 compilers
		 * by <a href="https://github.com/thelink2012">Denilson das Mercês Amorim</a>. 
		 * \c %Any provides an optimization for small objects objects with a size of up to 2 words (such as <tt>int<tt>, <tt>float</tt> 
		 * and <tt>std::shared_ptr</tt>). Storing those objects in the container will not trigger a dynamic allocation.
		 *
		 * For a easy to understand documentation, see [\ref ANY],
		 */
		class Any final
		{			

		public:
			/// Constructs an object of type \c %Any with an empty state.
			Any(): vtable(nullptr) {}

			/// Constructs an object of type \c %Any with an equivalent state as other.
			Any(const Any& rhs): vtable(rhs.vtable) {
				if (!rhs.isEmpty())
					rhs.vtable->copy(rhs.storage, this->storage);
			}

			/// Constructs an object of type \c %Any with a state equivalent to the original state of other.
			/// rhs is left in a valid but otherwise unspecified state.
			Any(Any&& rhs) noexcept: vtable(rhs.vtable) {
				if (!rhs.isEmpty()) {
					rhs.vtable->move(rhs.storage, this->storage);
					rhs.vtable = nullptr;
				}
			}

			/// Same effect as <tt>this->clear()</tt>.
			~Any() {
				this->clear();
			}

			/// Constructs an object of type \c %Any that contains an object of type \e T direct-initialized with <tt>std::forward<ValueType>(value)</tt>.
			///
			/// T shall satisfy the CopyConstructible requirements, otherwise the program is ill-formed.
			/// This is because an \c %Any may be copy constructed into another \c %Any at any time, so a copy should always be allowed.
			template<typename ValueType, typename = typename std::enable_if<!std::is_same<typename std::decay<ValueType>::type, Any>::value>::type>
			Any(ValueType&& value) {
				static_assert(std::is_copy_constructible<typename std::decay<ValueType>::type>::value,
							  "T shall satisfy the CopyConstructible requirements.");
				
				this->construct(std::forward<ValueType>(value));
			}

			/// Has the same effect as <tt>Any(rhs).swap(*this)</tt>. No effects if an exception is thrown.
			Any& operator=(const Any& rhs) {
				Any(rhs).swap(*this);
				return *this;
			}

			/// Has the same effect as Any(std::move(rhs)).swap(*this).
			///
			/// The state of *this is equivalent to the original state of rhs and rhs is left in a valid
			/// but otherwise unspecified state.
			Any& operator=(Any&& rhs) noexcept {
				Any(std::move(rhs)).swap(*this);
				return *this;
			}

			/// Has the same effect as Any(std::forward<ValueType>(value)).swap(*this). No effect if a exception is thrown.
			///
			/// T shall satisfy the CopyConstructible requirements, otherwise the program is ill-formed.
			/// This is because an `Any` may be copy constructed into another `Any` at any time, so a copy should always be allowed.
			template<typename ValueType, typename = typename std::enable_if<!std::is_same<typename std::decay<ValueType>::type, Any>::value>::type>
			Any& operator=(ValueType&& value) {
				static_assert(std::is_copy_constructible<typename std::decay<ValueType>::type>::value,
							  "T shall satisfy the CopyConstructible requirements.");

				Any(std::forward<ValueType>(value)).swap(*this);
				return *this;
			}
			
			/// If not empty, destroys the contained object.
			void clear() noexcept {
				if (!isEmpty()) {
					this->vtable->destroy(storage);
					this->vtable = nullptr;
				}
			}

			/// Returns true if *this has no contained object, otherwise false.
			bool isEmpty() const noexcept {
				return (this->vtable == nullptr);
			}

			/// If *this has a contained object of type T, typeid(T); otherwise typeid(void).
			const std::type_info& getTypeID() const noexcept {
				return (isEmpty() ? typeid(void) : this->vtable->type());
			}

			/// Exchange the states of *this and rhs.
			void swap(Any& rhs) noexcept {
				if (this->vtable != rhs.vtable) {
					Any tmp(std::move(rhs));

					// move from *this to rhs.
					rhs.vtable = this->vtable;

					if (this->vtable != nullptr) {
						this->vtable->move(this->storage, rhs.storage);
						//this->vtable = nullptr; -- unneeded, see below
					}

					// move from tmp (previously rhs) to *this.
					this->vtable = tmp.vtable;

					if (tmp.vtable != nullptr) {
						tmp.vtable->move(tmp.storage, this->storage);
						tmp.vtable = nullptr;
					}
					
				} else { // same types
					if (this->vtable != nullptr)
						this->vtable->swap(this->storage, rhs.storage);
				}
			}

		private: // Storage and Virtual Method Table
			union Storage
			{
				using StackStorageT = typename std::aligned_storage<2 * sizeof(void*), std::alignment_of<void*>::value>::type;

				void*         dynamic;
				StackStorageT stack;      // 2 words for e.g. shared_ptr
			};

			/// Base VTable specification.
			struct VTable
			{
				// Note: The caller is responssible for doing .vtable = nullptr after destructful operations
				// such as destroy() and/or move().

				/// The type of the object this vtable is for.
				const std::type_info& (*type)() noexcept;

				/// Destroys the object in the union.
				/// The state of the union after this call is unspecified, caller must ensure not to use src anymore.
				void(*destroy)(Storage&) noexcept;

				/// Copies the **inner** content of the src union into the yet unitialized dest union.
				/// As such, both inner objects will have the same state, but on separate memory locations.
				void(*copy)(const Storage& src, Storage& dest);

				/// Moves the storage from src to the yet unitialized dest union.
				/// The state of src after this call is unspecified, caller must ensure not to use src anymore.
				void(*move)(Storage& src, Storage& dest) noexcept;

				/// Exchanges the storage between lhs and rhs.
				void(*swap)(Storage& lhs, Storage& rhs) noexcept;
			};

			/// VTable for dynamically allocated storage.
			template<typename T>
			struct VTableDynamic
			{

				static const std::type_info& type() noexcept {
					return typeid(T);
				}

				static void destroy(Storage& storage) noexcept {
					//assert(reinterpret_cast<T*>(storage.dynamic));
					delete reinterpret_cast<T*>(storage.dynamic);
				}

				static void copy(const Storage& src, Storage& dest) {
					dest.dynamic = new T(*reinterpret_cast<const T*>(src.dynamic));
				}

				static void move(Storage& src, Storage& dest) noexcept {
					dest.dynamic = src.dynamic;
					src.dynamic = nullptr;
				}

				static void swap(Storage& lhs, Storage& rhs) noexcept {
					// just exchage the storage pointers.
					std::swap(lhs.dynamic, rhs.dynamic);
				}
			};

			/// VTable for stack allocated storage.
			template<typename T>
			struct VTableStack
			{

				static const std::type_info& type() noexcept {
					return typeid(T);
				}

				static void destroy(Storage& storage) noexcept {
					reinterpret_cast<T*>(&storage.stack)->~T();
				}

				static void copy(const Storage& src, Storage& dest) {
					new (&dest.stack) T(reinterpret_cast<const T&>(src.stack));
				}

				static void move(Storage& src, Storage& dest) noexcept {
					// one of the conditions for using VTableStack is a nothrow move constructor,
					// so this move constructor will never throw a exception.
					new (&dest.stack) T(std::move(reinterpret_cast<T&>(src.stack)));
					destroy(src);
				}

				static void swap(Storage& lhs, Storage& rhs) noexcept {
					Storage tmp_storage;
					
					move(rhs, tmp_storage);
					move(lhs, rhs);
					move(tmp_storage, lhs);
				}
			};

			/// Whether the type T must be dynamically allocated or can be stored on the stack.
			template<typename T>
			struct RequiresAlloc :
				std::integral_constant<bool,
									   !(std::is_nothrow_move_constructible<T>::value      // N4562 §6.3/3 [any.class]
										 && sizeof(T) <= sizeof(Storage::stack)
										 && std::alignment_of<T>::value <= std::alignment_of<Storage::stack_storage_t>::value)> {};

			/// Returns the pointer to the vtable of the type T.
			template<typename T>
			static VTable* getVTableForType()
			{

				using VTableType = typename std::conditional<RequiresAlloc<T>::value, VTableDynamic<T>, VTableStack<T>>::type;

				static VTable table = {
				    VTableType::type,
					VTableType::destroy,
					VTableType::copy, VTableType::move,
					VTableType::swap,
				};
				
				return &table;
			}

			/// Same effect as is_same(this->getTypeID(), t);
			bool is_typed(const std::type_info& t) const {
				return is_same(this->getTypeID(), t);
			}

			/// Checks if two type infos are the same.
			static bool is_same(const std::type_info& a, const std::type_info& b){
				return (a == b);
			}

			/// Casts (with no type_info checks) the storage pointer as const T*.
			template<typename T>
			const T* cast() const noexcept {
				return RequiresAlloc<typename std::decay<T>::type>::value ?
					reinterpret_cast<const T*>(storage.dynamic) :
					reinterpret_cast<const T*>(&storage.stack);
			}

			/// Casts (with no type_info checks) the storage pointer as T*.
			template<typename T>
			T* cast() noexcept {
				return RequiresAlloc<typename std::decay<T>::type>::value ?
					reinterpret_cast<T*>(storage.dynamic) :
					reinterpret_cast<T*>(&storage.stack);
			}

			template<typename ValueType, typename T>
			typename std::enable_if<RequiresAlloc<T>::value>::type
			doConstruct(ValueType&& value) {
				storage.dynamic = new T(std::forward<ValueType>(value));
			}

			template<typename ValueType, typename T>
			typename std::enable_if<!RequiresAlloc<T>::value>::type
			doConstruct(ValueType&& value) {
				new (&storage.stack) T(std::forward<ValueType>(value));
			}

			/// Chooses between stack and dynamic allocation for the type decay_t<ValueType>,
			/// assigns the correct vtable, and constructs the object on our storage.
			template<typename ValueType>
			void construct(ValueType&& value) {
				using T = typename std::decay<ValueType>::type;

				this->vtable = getVTableForType<T>();

				doConstruct<ValueType, T>(std::forward<ValueType>(value));
			}
			
			Storage storage; // on offset(0) so no padding for align
			VTable* vtable;
		};
	}
}

#endif // CDPL_BASE_ANY_HPP
