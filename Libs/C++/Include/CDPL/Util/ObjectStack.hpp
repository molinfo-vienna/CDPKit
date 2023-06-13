/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ObjectStack.hpp 
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
 * \brief Definition of the class CDPL::Util::ObjectStack.
 */

#ifndef CDPL_UTIL_OBJECTSTACK_HPP
#define CDPL_UTIL_OBJECTSTACK_HPP

#include <vector>
#include <cstddef>
#include <algorithm>
#include <new>
#include <memory>

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include "CDPL/Util/Dereferencer.hpp"


namespace CDPL
{

    namespace Util
    {

		/**
		 * \brief ObjectStack.
		 */
		template <typename T>
		class ObjectStack
		{

		public:
			typedef T ObjectType;
			typedef std::shared_ptr<ObjectType> SharedObjectPointer;
			typedef boost::function0<ObjectType*> ConstructorFunction;
			typedef boost::function1<void, ObjectType*> DestructorFunction;
			typedef boost::function1<void, ObjectType&> ObjectFunction;

			struct DefaultConstructor
			{

				T* operator()() const {
					return new T();
				}
			};

			struct DefaultDestructor
			{

				void operator()(T* obj) const {
					delete obj;
				}
			};

			ObjectStack(const ObjectStack& stack): 
				maxSize(stack.maxSize), freeIndex(0), ctorFunc(stack.ctorFunc), dtorFunc(stack.dtorFunc),
				initFunc(stack.initFunc), cleanFunc(stack.cleanFunc) {}

			ObjectStack(std::size_t max_pool_size = 0): 
				maxSize(max_pool_size), freeIndex(0), ctorFunc(DefaultConstructor()), dtorFunc(DefaultDestructor()) {}
		
			template <typename C, typename D>
			ObjectStack(const C& ctor_func, const D& dtor_func, std::size_t max_pool_size = 0): 
				maxSize(max_pool_size), freeIndex(0), ctorFunc(ctor_func), dtorFunc(dtor_func) {}

			~ObjectStack() {}

			ObjectType* getRaw() {
				return get().get();
			}

			const SharedObjectPointer& get() {
				if (freeIndex == allocObjects.size()) {
					SharedObjectPointer obj_ptr(ctorFunc(), dtorFunc);

					if (!obj_ptr)
						throw std::bad_alloc();

					allocObjects.push_back(obj_ptr);
				}

				const SharedObjectPointer& obj_ptr = allocObjects[freeIndex++];

				if (initFunc) 
					initFunc(*obj_ptr);

				return obj_ptr;
			}

			void put() {
				if (freeIndex > 0) {
					freeIndex--;

					if (cleanFunc)
						cleanFunc(*allocObjects[freeIndex]);
				}

				if (maxSize > 0 && freeIndex <= maxSize && allocObjects.size() > maxSize)
					allocObjects.resize(maxSize);
			}

			void putAll() {
				if (cleanFunc)
					std::for_each(allocObjects.begin(), allocObjects.begin() + freeIndex, 
								  boost::bind(cleanFunc, boost::bind(Util::Dereferencer<SharedObjectPointer, ObjectType&>(), _1)));
				freeIndex = 0;

				if (maxSize > 0 && allocObjects.size() > maxSize)
					allocObjects.resize(maxSize);
			}

			std::size_t getMaxPoolSize() const {
				return maxSize;
			}

			void setMaxPoolSize(std::size_t max_size) {
				maxSize = max_size;
	
				if (maxSize > 0 && allocObjects.size() > maxSize)
					allocObjects.resize(std::max(freeIndex, maxSize));
			}

			void freeMemory(bool unused_only = true) {
				if (unused_only) {
					allocObjects.resize(freeIndex);
					return;
				}

				freeIndex = 0;
				allocObjects.clear();
			}

			void setInitFunction(const ObjectFunction& func) {
				initFunc = func;
			}

			void setCleanupFunction(const ObjectFunction& func) {
				cleanFunc = func;
			}

			ObjectStack& operator=(const ObjectStack& stack) {
				if (this == &stack)
					return *this;

				maxSize = stack.maxSize;
				ctorFunc = stack.ctorFunc;
				dtorFunc = stack.dtorFunc;
				initFunc = stack.initFunc;

				if (maxSize > 0 && allocObjects.size() > maxSize) 
					allocObjects.resize(std::max(freeIndex, maxSize));

				return *this;
			}

		private:
			typedef std::vector<SharedObjectPointer> AllocObjectList;

			std::size_t         maxSize;
			std::size_t         freeIndex;
			AllocObjectList     allocObjects;
			ConstructorFunction ctorFunc;
			DestructorFunction  dtorFunc;
			ObjectFunction      initFunc;
			ObjectFunction      cleanFunc;
		};
    }
}

#endif // CDPL_UTIL_OBJECTSTACK_HPP
