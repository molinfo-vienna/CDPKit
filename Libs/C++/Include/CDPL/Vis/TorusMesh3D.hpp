/* 
 * TorusMesh3D.hpp 
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
 * \brief Definition of the class CDPL::Vis::TorusMesh3D.
 */

#ifndef CDPL_VIS_TORUSMESH3D_HPP
#define CDPL_VIS_TORUSMESH3D_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/TriangleMesh3D.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief A pre-defined triangle mesh providing the vertices and faces of a torus specified
         *        by the contructor arguments.
         * \since 1.3
         */
        class CDPL_VIS_API TorusMesh3D : public TriangleMesh3D
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TorusMesh3D instances.
             */
            typedef std::shared_ptr<TorusMesh3D> SharedPointer;

            TorusMesh3D(double radius1, double radius2, std::size_t num_sect1, std::size_t num_sect2);
         };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_TORUSMESH3D_HPP
