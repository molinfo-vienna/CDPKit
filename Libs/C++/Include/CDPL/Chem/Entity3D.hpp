/* 
 * Entity3D.hpp
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
 * \brief Definition of class CDPL::Chem::Entity3D.
 */

#ifndef CDPL_CHEM_ENTITY3D_HPP
#define CDPL_CHEM_ENTITY3D_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Entity3D.
         */
        class CDPL_CHEM_API Entity3D : public Base::PropertyContainer
        {

          protected:
            /**
             * \brief Default constructor.
             */
            Entity3D();

            /**
             * \brief Constructs a copy of the \c %Entity3D instance \a entity.
             * \param entity The \c %Entity3D instance to copy.
             */
            Entity3D(const Entity3D& entity);

            /**
             * \brief Virtual destructor.
             */
            virtual ~Entity3D() {}

            /**
             * \brief Assignment operator.
             * \param cntnr The \c %Entity3D instance to copy.
             * \return A reference to itself.
             */
            Entity3D& operator=(const Entity3D& cntnr);
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ENTITY3D_HPP
