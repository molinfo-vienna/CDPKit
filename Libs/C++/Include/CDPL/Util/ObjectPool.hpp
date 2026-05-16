/* 
 * ObjectPool.hpp 
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
 * \brief Definition of class CDPL::Util::ObjectPool.
 */

#ifndef CDPL_UTIL_OBJECTPOOL_HPP
#define CDPL_UTIL_OBJECTPOOL_HPP

#include <vector>
#include <cstddef>
#include <algorithm>
#include <new>
#include <memory>
#include <functional>


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief A data structure that caches instances of type \c T up to a user specified amount. 
         *
         * Instances of type \c T that are allocated via this pool (see get()) are preferentially taken from an
         * internally maintained list of previously allocated but now unused objects. If there are no
         * free objects a new object instance will be created on the fly. Allocated objects are returned as
         * smart pointers which keep track of all current references to the object. If the reference count
         * drops to zero at some point, the object is automatically returned to the pool it was allocated from.
         *
         * \e Warning: Due to this automatic return of unused objects it is necessary that all objects have returned
         * to their source pool before the pool instance gets destroyed!!!!
         */
        template <typename T>
        class ObjectPool
        {

          public:
            /**
             * \brief The type of the pooled objects.
             */
            typedef T ObjectType;

            /**
             * \brief A smart pointer to a borrowed object that returns the object to the pool on destruction.
             */
            typedef std::shared_ptr<ObjectType> SharedObjectPointer;

            /**
             * \brief A generic wrapper for functions creating new instances of \c ObjectType.
             */
            typedef std::function<ObjectType*()>     ConstructorFunction;

            /**
             * \brief A generic wrapper for functions destroying instances of \c ObjectType.
             */
            typedef std::function<void(ObjectType*)> DestructorFunction;

            /**
             * \brief A generic wrapper for functions operating on instances of \c ObjectType.
             */
            typedef std::function<void(ObjectType&)> ObjectFunction;

            /**
             * \brief Default object factory which creates new instances of \c ObjectType via \c new.
             */
            struct DefaultConstructor
            {

                T* operator()() const
                {
                    return new T();
                }
            };

            /**
             * \brief Default object destructor which destroys instances of \c ObjectType via \c delete.
             */
            struct DefaultDestructor
            {

                void operator()(T* obj) const
                {
                    delete obj;
                }
            };

            /**
             * \brief Copy constructor.
             * \param pool The other \c %ObjectPool instance.
             * \note The pool of allocated objects of \a pool is not copied; the new instance starts
             *       with an empty pool.
             */
            ObjectPool(const ObjectPool& pool):
                maxSize(pool.maxSize), ctorFunc(pool.ctorFunc), dtorFunc(pool.dtorFunc),
                initFunc(pool.initFunc), cleanFunc(pool.cleanFunc) {}

            /**
             * \brief Constructs a default-configured \c %ObjectPool instance using DefaultConstructor and DefaultDestructor.
             * \param max_size The maximum number of objects retained in the pool, or \e 0 for no limit.
             */
            ObjectPool(std::size_t max_size = 0):
                maxSize(max_size), ctorFunc(DefaultConstructor()), dtorFunc(DefaultDestructor()) {}

            /**
             * \brief Constructs an \c %ObjectPool instance using a user-supplied factory and destructor.
             * \param ctor_func The factory used to create new instances.
             * \param dtor_func The destructor used to release instances.
             * \param max_size The maximum number of objects retained in the pool, or \e 0 for no limit.
             */
            template <typename C, typename D>
            ObjectPool(const C& ctor_func, const D& dtor_func, std::size_t max_size = 0):
                maxSize(max_size), ctorFunc(ctor_func), dtorFunc(dtor_func)
            {}

            /**
             * \brief Destructor. Destroys all currently idle pool entries.
             * \warning All previously handed-out smart pointers must have been released before
             *          destruction; otherwise the deferred put() will operate on a destroyed pool.
             */
            ~ObjectPool()
            {
                std::for_each(pool.begin(), pool.end(), dtorFunc);
            }

            /**
             * \brief Returns a smart pointer to a pool-owned object.
             *
             * If no idle object is available a new one is created via the configured object factory.
             * If an init function has been set (see setInitFunction()) it is invoked on the object
             * before it is returned. The object is automatically returned to the pool when the last
             * reference to the smart pointer is released.
             *
             * \return A smart pointer to a borrowed object.
             */
            SharedObjectPointer get()
            {
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

            /**
             * \brief Returns the current number of idle objects in the pool.
             * \return The current pool size.
             */
            std::size_t getSize() const
            {
                return pool.size();
            }

            /**
             * \brief Returns the currently configured maximum pool size.
             * \return The maximum number of objects retained in the pool, or \e 0 for no limit.
             */
            std::size_t getMaxSize() const
            {
                return maxSize;
            }

            /**
             * \brief Sets the maximum pool size.
             *
             * Excess idle objects above the new pool size are destroyed.
             *
             * \param max_size The new maximum pool size, or \e 0 for no limit.
             */
            void setMaxSize(std::size_t max_size)
            {
                maxSize = max_size;

                shrinkToMaxSize();
            }

            /**
             * \brief Destroys all currently idle pool entries and releases their memory.
             */
            void freeMemory()
            {
                std::for_each(pool.begin(), pool.end(), dtorFunc);

                pool.clear();
            }

            /**
             * \brief Sets the function to be invoked on an object when it is handed out by get().
             * \param func The function to invoke on each newly handed-out object.
             */
            void setInitFunction(const ObjectFunction& func)
            {
                initFunc = func;
            }

            /**
             * \brief Sets the function to be invoked on an object when it is returned to the pool.
             * \param func The function to invoke on each returned object.
             */
            void setCleanupFunction(const ObjectFunction& func)
            {
                cleanFunc = func;
            }

            /**
             * \brief Copy assignment operator.
             * \param pool The other \c %ObjectPool instance.
             * \return A reference to itself.
             * \note The pool of allocated objects of \a pool is not copied; only the configuration
             *       (max size, factory, destructor and init function) is taken over. The cleanup
             *       function is **not** copied — re-install it via setCleanupFunction() if needed.
             */
            ObjectPool& operator=(const ObjectPool& pool)
            {
                if (this == &pool)
                    return *this;

                maxSize  = pool.maxSize;
                ctorFunc = pool.ctorFunc;
                dtorFunc = pool.dtorFunc;
                initFunc = pool.initFunc;

                shrinkToMaxSize();

                return *this;
            }

          private:
            void shrinkToMaxSize()
            {
                if (maxSize == 0)
                    return;

                while (pool.size() > maxSize) {
                    dtorFunc(pool.back());
                    pool.pop_back();
                }
            }

            struct PutObject
            {

                PutObject(ObjectPool& pool):
                    pool(pool) {}

                void operator()(ObjectType* obj) const
                {
                    pool.put(obj);
                }

                ObjectPool& pool;
            };

            void put(ObjectType* obj)
            {
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
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_OBJECTPOOL_HPP
