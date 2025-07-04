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

#include <memory>

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
            Object3D& operator=(const Object3D& cntnr);
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_OBJECT3D_HPP
