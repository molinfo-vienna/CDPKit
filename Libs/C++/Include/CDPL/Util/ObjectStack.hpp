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
 * \brief Definition of class CDPL::Util::ObjectStack.
 */

#ifndef CDPL_UTIL_OBJECTSTACK_HPP
#define CDPL_UTIL_OBJECTSTACK_HPP

#include <cstddef>
#include <algorithm>

#include <boost/ptr_container/ptr_vector.hpp>


namespace CDPL
{

    namespace Util
    {

        /**
         * \brief Reusable object pool with stack-like borrow/return semantics.
         *
         * \c %ObjectStack allocates objects of type \a T lazily on demand and recycles them across
         * subsequent get() calls instead of destroying them on put(). An optional pool size limit
         * controls the maximum number of objects retained between requests; user-supplied init and
         * cleanup functions can be installed to be invoked when objects are handed out or returned.
         *
         * \tparam T The type of the pooled objects.
         */
        template <typename T>
        class ObjectStack
        {

          public:
            /**
             * \brief The type of the pooled objects.
             */
            typedef T ObjectType;

            /**
             * \brief Generic wrapper for functions creating new instances of \c ObjectType.
             */
            typedef std::function<ObjectType*()>     ConstructorFunction;

            /**
             * \brief Generic wrapper for functions operating on instances of \c ObjectType.
             */
            typedef std::function<void(ObjectType&)> ObjectFunction;

            /**
             * \brief Default object factory which creates new instances of \c ObjectType via \c new.
             */
            struct DefaultConstructor
            {

                /**
                 * \brief Creates a new instance of \c ObjectType via \c new.
                 * \return A pointer to the newly created object.
                 */
                T* operator()() const
                {
                    return new T();
                }
            };

            /**
             * \brief Copy constructor.
             * \param stack The other \c %ObjectStack instance.
             * \note The pool of allocated objects of \a stack is not copied; the new instance starts
             *       with an empty pool.
             */
            ObjectStack(const ObjectStack& stack):
                maxSize(stack.maxSize), freeIndex(0), ctorFunc(stack.ctorFunc),
                initFunc(stack.initFunc), cleanFunc(stack.cleanFunc) {}

            /**
             * \brief Constructs a default-configured \c %ObjectStack instance using DefaultConstructor as the object factory.
             * \param max_pool_size The maximum number of objects retained in the pool, or \e 0 for no limit.
             */
            ObjectStack(std::size_t max_pool_size = 0):
                maxSize(max_pool_size), freeIndex(0), ctorFunc(DefaultConstructor()) {}

            /**
             * \brief Constructs a \c %ObjectStack instance using a user-supplied object factory.
             * \param ctor_func The object factory to use for the creation of new instances.
             * \param max_pool_size The maximum number of objects retained in the pool, or \e 0 for no limit.
             */
            template <typename C>
            ObjectStack(const C& ctor_func, std::size_t max_pool_size):
                maxSize(max_pool_size), freeIndex(0), ctorFunc(ctor_func)
            {}

            /**
             * \brief Destructor.
             */
            ~ObjectStack() {}

            /**
             * \brief Returns a pointer to an object handed out from the pool.
             *
             * If no idle object is available a new one is created via the configured object factory.
             * If an init function has been set (see setInitFunction()) it is invoked on the object
             * before it is returned. The pool retains ownership of the object; it must be returned
             * via put() (or putAll()) before the \c %ObjectStack is destroyed.
             *
             * \return A pointer to a borrowed object.
             */
            ObjectType* get()
            {
                if (freeIndex == allocObjects.size())
                    allocObjects.push_back(ctorFunc());

                ObjectType& obj = allocObjects[freeIndex++];

                if (initFunc)
                    initFunc(obj);

                return &obj;
            }

            /**
             * \brief Returns the most recently borrowed object back to the pool.
             *
             * If a cleanup function has been set (see setCleanupFunction()) it is invoked on the
             * returned object. Excess objects above the configured maximum pool size are destroyed.
             */
            void put()
            {
                if (freeIndex > 0) {
                    freeIndex--;

                    if (cleanFunc)
                        cleanFunc(allocObjects[freeIndex]);
                }

                if (maxSize > 0 && freeIndex <= maxSize && allocObjects.size() > maxSize)
                    allocObjects.erase(allocObjects.begin() + maxSize, allocObjects.end());
            }

            /**
             * \brief Returns all currently borrowed objects back to the pool.
             *
             * If a cleanup function has been set (see setCleanupFunction()) it is invoked on each
             * returned object. Excess objects above the configured maximum pool size are destroyed.
             */
            void putAll()
            {
                if (cleanFunc)
                    std::for_each(allocObjects.begin(), allocObjects.begin() + freeIndex,
                                  [this](ObjectType& obj) { cleanFunc(obj); });
                freeIndex = 0;

                if (maxSize > 0 && allocObjects.size() > maxSize)
                    allocObjects.erase(allocObjects.begin() + maxSize, allocObjects.end());
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
             * Excess idle objects above the new pool size are destroyed. Currently borrowed objects
             * are never destroyed by this method.
             *
             * \param max_size The new maximum pool size, or \e 0 for no limit.
             */
            void setMaxSize(std::size_t max_size)
            {
                maxSize = max_size;

                if (maxSize > 0 && allocObjects.size() > maxSize)
                    allocObjects.erase(allocObjects.begin() + std::max(freeIndex, maxSize), allocObjects.end());
            }

            /**
             * \brief Releases memory held by the pool.
             *
             * If \a unused_only is \c true, only idle (currently not borrowed) objects are destroyed.
             * If \a unused_only is \c false, all objects (including currently borrowed ones) are
             * destroyed and any pointers obtained via get() are invalidated.
             *
             * \param unused_only If \c true, only idle objects are destroyed.
             */
            void freeMemory(bool unused_only = true)
            {
                if (unused_only) {
                    allocObjects.erase(allocObjects.begin() + freeIndex, allocObjects.end());
                    return;
                }

                freeIndex = 0;
                allocObjects.clear();
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
             * \brief Sets the function to be invoked on an object when it is returned by put() or putAll().
             * \param func The function to invoke on each returned object.
             */
            void setCleanupFunction(const ObjectFunction& func)
            {
                cleanFunc = func;
            }

            /**
             * \brief Copy assignment operator.
             * \param stack The other \c %ObjectStack instance.
             * \return A reference to itself.
             * \note The pool of allocated objects of \a stack is not copied; the pool of \c *this is left intact.
             */
            ObjectStack& operator=(const ObjectStack& stack)
            {
                if (this == &stack)
                    return *this;

                maxSize  = stack.maxSize;
                ctorFunc = stack.ctorFunc;
                initFunc = stack.initFunc;

                if (maxSize > 0 && allocObjects.size() > maxSize)
                    allocObjects.erase(allocObjects.begin() + std::max(freeIndex, maxSize), allocObjects.end());

                return *this;
            }

          private:
            typedef boost::ptr_vector<ObjectType> AllocObjectList;

            std::size_t         maxSize;
            std::size_t         freeIndex;
            AllocObjectList     allocObjects;
            ConstructorFunction ctorFunc;
            ObjectFunction      initFunc;
            ObjectFunction      cleanFunc;
        };
    } // namespace Util
} // namespace CDPL

#endif // CDPL_UTIL_OBJECTSTACK_HPP
