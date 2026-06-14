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
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Vis
    {

        class TriangleMesh3D;

        /**
         * \brief Subdivides each triangle face of \a mesh and projects the new vertices onto the unit sphere.
         *
         * Each face is split into four sub-triangles by inserting a new vertex at the midpoint of every edge; the new
         * vertices are then normalized so that they lie on the unit sphere. Repeated application yields a finer spherical
         * approximation.
         *
         * \param mesh The triangle mesh to subdivide (modified in place).
         * \since 1.3
         */
        CDPL_VIS_API void subdivideSpherical(TriangleMesh3D& mesh);

        /**
         * \brief Merges duplicate vertices of \a mesh and updates the face vertex indices accordingly.
         * \param mesh The triangle mesh to deduplicate (modified in place).
         * \param check_vn If \c true, two vertices are only merged when their associated vertex normals also agree.
         * \param tol The position-equality tolerance; vertices closer than \a tol are considered duplicates.
         * \return The number of removed (merged-away) vertices.
         * \since 1.3
         */
        CDPL_VIS_API std::size_t removeVertexDuplicates(TriangleMesh3D& mesh, bool check_vn = true, double tol = 0.0);

        /**
         * \brief Computes per-vertex normals of \a mesh from its face normals and stores them in the mesh.
         * \param mesh The triangle mesh for which to compute vertex normals (modified in place).
         * \param weight_face_size If \c true, each face normal is weighted by the face area when accumulated into the vertex normals.
         * \since 1.3
         */
        CDPL_VIS_API void calcVertexFromFaceNormals(TriangleMesh3D& mesh, bool weight_face_size = false);

        /**
         * \brief Computes per-vertex normals of \a mesh from its face normals and stores them in \a normals.
         * \param mesh The triangle mesh for which to compute vertex normals.
         * \param normals The output array receiving the computed per-vertex normals.
         * \param weight_face_size If \c true, each face normal is weighted by the face area when accumulated into the vertex normals.
         * \since 1.3
         */
        CDPL_VIS_API void calcVertexFromFaceNormals(const TriangleMesh3D& mesh, Math::Vector3DArray& normals, bool weight_face_size = false);

        /**
         * \brief Translates the vertices of \a mesh by the vector <em>(trans_x, trans_y, trans_z)</em>.
         * \param mesh The triangle mesh to translate (modified in place).
         * \param trans_x The translation along the x-axis.
         * \param trans_y The translation along the y-axis.
         * \param trans_z The translation along the z-axis.
         * \param vtx_offs The index of the first vertex to translate.
         * \param vtx_count The number of vertices to translate (\e 0 to process all vertices from \a vtx_offs onwards).
         * \since 1.3
         */
        CDPL_VIS_API void translate(TriangleMesh3D& mesh, double trans_x, double trans_y, double trans_z,
                                    std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \brief Scales the vertices of \a mesh by the per-axis factors <em>(scale_x, scale_y, scale_z)</em>.
         * \param mesh The triangle mesh to scale (modified in place).
         * \param scale_x The scaling factor along the x-axis.
         * \param scale_y The scaling factor along the y-axis.
         * \param scale_z The scaling factor along the z-axis.
         * \param vtx_offs The index of the first vertex to scale.
         * \param vtx_count The number of vertices to scale (\e 0 to process all vertices from \a vtx_offs onwards).
         * \since 1.3
         */
        CDPL_VIS_API void scale(TriangleMesh3D& mesh, double scale_x, double scale_y, double scale_z,
                                std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \brief Rotates the vertices of \a mesh around the x-axis by the angle \a angle.
         * \param mesh The triangle mesh to rotate (modified in place).
         * \param angle The rotation angle in radians.
         * \param vtx_offs The index of the first vertex to rotate.
         * \param vtx_count The number of vertices to rotate (\e 0 to process all vertices from \a vtx_offs onwards).
         * \since 1.3
         */
        CDPL_VIS_API void rotateX(TriangleMesh3D& mesh, double angle,
                                  std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \brief Rotates the vertices of \a mesh around the y-axis by the angle \a angle.
         * \param mesh The triangle mesh to rotate (modified in place).
         * \param angle The rotation angle in radians.
         * \param vtx_offs The index of the first vertex to rotate.
         * \param vtx_count The number of vertices to rotate (\e 0 to process all vertices from \a vtx_offs onwards).
         * \since 1.3
         */
        CDPL_VIS_API void rotateY(TriangleMesh3D& mesh, double angle,
                                  std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \brief Rotates the vertices of \a mesh around the z-axis by the angle \a angle.
         * \param mesh The triangle mesh to rotate (modified in place).
         * \param angle The rotation angle in radians.
         * \param vtx_offs The index of the first vertex to rotate.
         * \param vtx_count The number of vertices to rotate (\e 0 to process all vertices from \a vtx_offs onwards).
         * \since 1.3
         */
        CDPL_VIS_API void rotateZ(TriangleMesh3D& mesh, double angle,
                                  std::size_t vtx_offs = 0, std::size_t vtx_count = 0);

        /**
         * \brief Applies the affine transformation matrix \a mtx to the vertices of \a mesh.
         * \param mesh The triangle mesh to transform (modified in place).
         * \param mtx The \f$ 4 \times 4 \f$ homogeneous transformation matrix to apply.
         * \param vtx_offs The index of the first vertex to transform.
         * \param vtx_count The number of vertices to transform (\e 0 to process all vertices from \a vtx_offs onwards).
         * \since 1.3
         */
        CDPL_VIS_API void transform(TriangleMesh3D& mesh, const Math::Matrix4D& mtx,
                                    std::size_t vtx_offs = 0, std::size_t vtx_count = 0);
        
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_TRIANGLEMESH3DFUNCTIONS_HPP
