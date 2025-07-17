/* 
 * TriangleMesh3DFunctions.hpp 
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
 * \brief Declaration of functions that operate on Vis::TriangleMesh3D instances.
 */

#ifndef CDPL_VIS_TRIANGLEMESH3DFUNCTIONS_HPP
#define CDPL_VIS_TRIANGLEMESH3DFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL
{

    namespace Vis
    {

        class TriangleMesh3D;

        /**
         * \since 1.3
         */
        CDPL_VIS_API void subdivideSpherical(TriangleMesh3D& mesh);

        /**
         * \since 1.3
         */
        CDPL_VIS_API std::size_t removeVertexDuplicates(TriangleMesh3D& mesh);

        /**
         * \since 1.3
         */
        CDPL_VIS_API void calcVertexFromFaceNormals(TriangleMesh3D& mesh, bool weight_face_size = false);
    
        /**
         * \since 1.3
         */
        CDPL_VIS_API void translate(TriangleMesh3D& mesh, double trans_x, double trans_y, double trans_z,
                                    std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \since 1.3
         */
        CDPL_VIS_API void scale(TriangleMesh3D& mesh, double scale_x, double scale_y, double scale_z,
                                std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \since 1.3
         */
        CDPL_VIS_API void rotateX(TriangleMesh3D& mesh, double angle,
                                  std::size_t vtx_offs = 0, std::size_t vtx_count = 0);
        
        /**
         * \since 1.3
         */
        CDPL_VIS_API void rotateY(TriangleMesh3D& mesh, double angle,
                                  std::size_t vtx_offs = 0, std::size_t vtx_count = 0);
        
        /**
         * \since 1.3
         */
        CDPL_VIS_API void rotateZ(TriangleMesh3D& mesh, double angle,
                                  std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \since 1.3
         */
        CDPL_VIS_API void transform(TriangleMesh3D& mesh, const Math::Matrix4D& mtx,
                                    std::size_t vtx_offs = 0, std::size_t vtx_count = 0);
        
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_TRIANGLEMESH3DFUNCTIONS_HPP
