/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ObjectPool.hpp 
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
 * \brief Definition of the class CDPL::Util::ObjectPool.
 */

#ifndef CDPL_UTIL_OBJECTPOOL_HPP
#define CDPL_UTIL_OBJECTPOOL_HPP

#include <vector>
#include <cstddef>
#include <algorithm>
#include <new>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>


namespace CDPL
{

    namespace Util
    {

		/**
		 * \addtogroup CDPL_UTIL_MISCELLANEOUS
		 * @{
		 */
	
		/**
		 * \brief A data structure that caches instances of type \c T up to a user specified amount. 
		 *
		 * Instances of type \c T that are allocated via this pool (see get()) are preferentially taken from an
		 * internally maintained list of previously allocated but now unused objects. If there are no
		 * free objects a new object instance will be created on the fly. Allocated objects are returned as
		 * smart pointers which keep track of all current references to the object. If the reference count
		 * drops to zero at some point, the object is automatically returned to the pool it was allocated from.
		 * \e Warning: Due to this automatic return of unused objects it is necessary that all objects have returned
		 * to their source pool before the pool instance gets destroyed!!!!
		 */
		template <typename T>
		class ObjectPool
		{

		public:
			typedef T ObjectType;
			typedef boost::shared_ptr<ObjectType> SharedObjectPointer;
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

			ObjectPool(const ObjectPool& pool): 
				maxSize(pool.maxSize), ctorFunc(pool.ctorFunc), dtorFunc(pool.dtorFunc),
				initFunc(pool.initFunc), cleanFunc(pool.cleanFunc) {}

			ObjectPool(std::size_t max_size = 0): 
				maxSize(max_size), ctorFunc(DefaultConstructor()), dtorFunc(DefaultDestructor()) {}
	
			template <typename C, typename D>
			ObjectPool(const C& ctor_func, const D& dtor_func, std::size_t max_size = 0): 
				maxSize(max_size), ctorFunc(ctor_func), dtorFunc(dtor_func) {}

			~ObjectPool() {
				std::for_each(pool.begin(), pool.end(), dtorFunc);
			}

			SharedObjectPointer get() {
				ObjectType* obj;

				if (!pool.empty()) {
					obj = pool.back();
					pool.pop_back();

				} else {
					obj = ctorFunc();

					if (!obj)
						throw std::bad_alloc();
				}

				SharedObjectPointer obj_ptr(obj, PutObject(*this));

				if (initFunc) 
					initFunc(*obj);

				return obj_ptr;
			}

			std::size_t getMaxSize() const {
				return maxSize;
			}

			void setMaxSize(std::size_t max_size) {
				maxSize = max_size;

				shrinkToMaxSize();
			}

			void freeMemory() {
				std::for_each(pool.begin(), pool.end(), dtorFunc);

				pool.clear();
			}

			void setInitFunction(const ObjectFunction& func) {
				initFunc = func;
			}

			void setCleanupFunction(const ObjectFunction& func) {
				cleanFunc = func;
			}

			ObjectPool& operator=(const ObjectPool& pool) {
				if (this == &pool)
					return *this;

				maxSize = pool.maxSize;
				ctorFunc = pool.ctorFunc;
				dtorFunc = pool.dtorFunc;
				initFunc = pool.initFunc;

				shrinkToMaxSize();

				return *this;
			}

		private:
			void shrinkToMaxSize() {
				if (maxSize == 0)
					return;

				while (pool.size() > maxSize) {
					dtorFunc(pool.back());
					pool.pop_back();
				} 
			}

			struct PutObject
			{

				PutObject(ObjectPool& pool): pool(pool) {}

				void operator()(ObjectType* obj) const {
					pool.put(obj);
				}

				ObjectPool& pool;
			};
	    
			void put(ObjectType* obj) {
				if (maxSize > 0 && pool.size() >= maxSize) {
					dtorFunc(obj);
					return;
				}

				try {
					if (cleanFunc)
						cleanFunc(*obj);

					pool.push_back(obj);

				} catch (...) {
					dtorFunc(obj);
				}
			}

			typedef std::vector<ObjectType*> PooledObjectList;

			std::size_t         maxSize;
			PooledObjectList    pool;
			ConstructorFunction ctorFunc;
			DestructorFunction  dtorFunc;
			ObjectFunction      initFunc;
			ObjectFunction      cleanFunc;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_UTIL_OBJECTPOOL_HPP
