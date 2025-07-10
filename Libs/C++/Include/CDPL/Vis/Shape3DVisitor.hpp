/* 
 * Shape3DVisitor.hpp 
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
 * \brief Definition of the class CDPL::Vis::Shape3DVisitor.
 */

#ifndef CDPL_VIS_SHAPE3DVISITOR_HPP
#define CDPL_VIS_SHAPE3DVISITOR_HPP

#include "CDPL/Vis/APIPrefix.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Shape3D;
        
        /**
         * \brief The base of all Vis::Shape3D visitor implementations [\ref VPTN].
         * \since 1.3
         */
        class CDPL_VIS_API Shape3DVisitor
        {

          public:
            /**
             * \brief Virtual destructor.
             */
            virtual ~Shape3DVisitor() {}

            /**
             * \brief Generic visit method for Shape3D instances.
             * \param shape The Vis::Shape3D instance to visit.
             */
            virtual void visit(const Shape3D& shape) {}
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_SHAPE3DVISITOR_HPP
