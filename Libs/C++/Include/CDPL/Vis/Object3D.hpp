/* 
 * Object3D.hpp
 *
 * This file is part of the Visical Data Processing Toolkit
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
 * \brief Definition of the class CDPL::Vis::Object3D.
 */

#ifndef CDPL_VIS_OBJECT3D_HPP
#define CDPL_VIS_OBJECT3D_HPP

#include <vector>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Object3D.
         * \since 1.3
         */
        class CDPL_VIS_API Object3D : public Base::PropertyContainer
        {
            

  
          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Object3D instances.
             */
            typedef std::shared_ptr<Object3D> SharedPointer;

          private:
            typedef std::vector<SharedPointer>                                             Object3DList;
            typedef boost::indirect_iterator<Object3DList::iterator, Object3D>             Object3DIterator;
            typedef boost::indirect_iterator<Object3DList::const_iterator, const Object3D> ConstObject3DIterator;

          public:
            /**
             * \brief Default constructor.
             */
            Object3D();

            /**
             * \brief Constructs a copy of the \c %Object3D instance \a object.
             * \param object The \c %Object3D instance to copy.
             */
            Object3D(const Object3D& object);

            /**
             * \brief Virtual destructor.
             */
            virtual ~Object3D() {}

            /**
             * \brief Assignment operator.
             * \param cntnr The \c %Object3D instance to copy.
             * \return A reference to itself.
             */
            Object3D& operator=(const Object3D& object);

            void clear();

            std::size_t getNumObjects() const;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the sub-objects.
             * \return A constant iterator pointing to the beginning of the sub-objects.
             */
            ConstObject3DIterator getSubObjectsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the sub-objects.
             * \return A mutable iterator pointing to the beginning of the sub-objects.
             */
            Object3DIterator getSubObjectsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the sub-objects.
             * \return A constant iterator pointing to the end of the sub-objects.
             */
            ConstObject3DIterator getSubObjectsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the sub-objects.
             * \return A mutable iterator pointing to the end of the sub-objects.
             */
            Object3DIterator getSubObjectsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the sub-objects.
             * \return A constant iterator pointing to the beginning of the sub-objects.
             */
            ConstObject3DIterator begin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the sub-objects.
             * \return A mutable iterator pointing to the beginning of the sub-objects.
             */
            Object3DIterator begin();

            /**
             * \brief Returns a constant iterator pointing to the end of the sub-objects.
             * \return A constant iterator pointing to the end of the sub-objects.
             */
            ConstObject3DIterator end() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the sub-objects.
             * \return A mutable iterator pointing to the end of the sub-objects.
             */
            Object3DIterator end();

            const Object3D& getSubObject(std::size_t idx) const;

            Object3D& getSubObject(std::size_t idx);

            Object3D& addSubObject();

            Object3D& addSubObject(const SharedPointer& object);

            void removeSubObject(std::size_t idx);

            /**
             * \brief Removes the sub-object specified by the iterator \a it.
             *
             * \param it An iterator that specifies the sub-object to remove.
             * \return A mutable iterator pointing to the next sub-object in the list.
             * \throw Base::RangeError if the number of sub-objects is zero or \a it is not in the range
             *        [getSubObjectsBegin(), getSubObjectsEnd() - 1].
             */
            Object3DIterator removeSubObject(const Object3DIterator& it);

          private:
            Object3DList subObjects;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3D_HPP
