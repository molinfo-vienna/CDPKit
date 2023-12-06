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

#include <cstddef>
#include <algorithm>
#include <new>
#include <memory>

#include <boost/ptr_container/ptr_vector.hpp>


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

            typedef std::function<ObjectType*()>     ConstructorFunction;
            typedef std::function<void(ObjectType&)> ObjectFunction;

            struct DefaultConstructor
            {

                T* operator()() const
                {
                    return new T();
                }
            };

            ObjectStack(const ObjectStack& stack):
                maxSize(stack.maxSize), freeIndex(0), ctorFunc(stack.ctorFunc),
                initFunc(stack.initFunc), cleanFunc(stack.cleanFunc) {}

            ObjectStack(std::size_t max_pool_size = 0):
                maxSize(max_pool_size), freeIndex(0), ctorFunc(DefaultConstructor()) {}

            template <typename C>
            ObjectStack(const C& ctor_func, std::size_t max_pool_size):
                maxSize(max_pool_size), freeIndex(0), ctorFunc(ctor_func)
            {}

            ~ObjectStack() {}

            ObjectType* get()
            {
                if (freeIndex == allocObjects.size())
                    allocObjects.push_back(ctorFunc());

                ObjectType& obj = allocObjects[freeIndex++];

                if (initFunc)
                    initFunc(obj);

                return &obj;
            }

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

            void putAll()
            {
                if (cleanFunc)
                    std::for_each(allocObjects.begin(), allocObjects.begin() + freeIndex,
                                  [this](ObjectType& obj) { cleanFunc(obj); });
                freeIndex = 0;

                if (maxSize > 0 && allocObjects.size() > maxSize)
                    allocObjects.erase(allocObjects.begin() + maxSize, allocObjects.end());
            }

            std::size_t getMaxSize() const
            {
                return maxSize;
            }

            void setMaxSize(std::size_t max_size)
            {
                maxSize = max_size;

                if (maxSize > 0 && allocObjects.size() > maxSize)
                    allocObjects.erase(allocObjects.begin() + std::max(freeIndex, maxSize), allocObjects.end());
            }

            void freeMemory(bool unused_only = true)
            {
                if (unused_only) {
                    allocObjects.erase(allocObjects.begin() + freeIndex, allocObjects.end());
                    return;
                }

                freeIndex = 0;
                allocObjects.clear();
            }

            void setInitFunction(const ObjectFunction& func)
            {
                initFunc = func;
            }

            void setCleanupFunction(const ObjectFunction& func)
            {
                cleanFunc = func;
            }

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
