/* 
 * TriangleMesh3D.hpp 
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
 * \brief Definition of class CDPL::Vis::TriangleMesh3D.
 */

#ifndef CDPL_VIS_TRIANGLEMESH3D_HPP
#define CDPL_VIS_TRIANGLEMESH3D_HPP

#include <memory>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/Shape3D.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Data structure for the storage of 3D triangle mesh vertices, vertex normals and faces.
         * \since 1.3
         */
        class CDPL_VIS_API TriangleMesh3D : public Shape3D
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TriangleMesh3D instances.
             */
            typedef std::shared_ptr<TriangleMesh3D> SharedPointer;

            /**
             * \brief Creates a dynamically allocated copy of the triangle mesh.
             * \return A smart pointer to the copy.
             */
            Shape3D::SharedPointer clone() const;

            /**
             * \brief Accepts the Vis::Shape3DVisitor instance \a visitor by dispatching to its visitTriangleMesh() method [\ref VPTN].
             * \param visitor The Vis::Shape3DVisitor instance to accept.
             */
            void accept(Shape3DVisitor& visitor) const;

            /**
             * \brief Returns a non-\c const reference to the array storing the mesh vertices.
             * \return A non-\c const reference to the vertex array.
             */
            Math::Vector3DArray& getVertices();

            /**
             * \brief Returns a \c const reference to the array storing the mesh vertices.
             * \return A \c const reference to the vertex array.
             */
            const Math::Vector3DArray& getVertices() const;

            /**
             * \brief Appends a new vertex at the position <em>(x, y, z)</em>.
             * \param x The x-coordinate of the vertex.
             * \param y The y-coordinate of the vertex.
             * \param z The z-coordinate of the vertex.
             */
            void addVertex(double x, double y, double z);

            /**
             * \brief Returns the number of stored vertices.
             * \return The vertex count.
             */
            std::size_t getNumVertices() const;

            /**
             * \brief Returns a non-\c const reference to the array storing the per-vertex normals.
             * \return A non-\c const reference to the vertex-normal array.
             */
            Math::Vector3DArray& getVertexNormals();

            /**
             * \brief Returns a \c const reference to the array storing the per-vertex normals.
             * \return A \c const reference to the vertex-normal array.
             */
            const Math::Vector3DArray& getVertexNormals() const;

            /**
             * \brief Appends a new vertex normal with the components <em>(x, y, z)</em>.
             * \param x The x-component of the normal vector.
             * \param y The y-component of the normal vector.
             * \param z The z-component of the normal vector.
             */
            void addVertexNormal(double x, double y, double z);

            /**
             * \brief Returns the number of stored vertex normals.
             * \return The vertex normal count.
             */
            std::size_t getNumVertexNormals() const;

            /**
             * \brief Returns a non-\c const reference to the array storing the triangle faces.
             * \return A non-\c const reference to the face array.
             */
            Math::Vector3ULArray& getFaces();

            /**
             * \brief Returns a \c const reference to the array storing the triangle faces.
             * \return A \c const reference to the face array.
             */
            const Math::Vector3ULArray& getFaces() const;

            /**
             * \brief Appends a new triangle face defined by the three vertex indices \a v1_idx, \a v2_idx and \a v3_idx.
             * \param v1_idx The zero-based index of the first vertex.
             * \param v2_idx The zero-based index of the second vertex.
             * \param v3_idx The zero-based index of the third vertex.
             */
            void addFace(unsigned long v1_idx, unsigned long v2_idx, unsigned long v3_idx);

            /**
             * \brief Returns the number of stored triangle faces.
             * \return The face count.
             */
            std::size_t getNumFaces() const;

            /**
             * \brief Tells whether the mesh has been flagged as a closed surface.
             * \return \c true if the mesh is flagged as closed, and \c false otherwise.
             */
            bool isClosed() const;

            /**
             * \brief Sets the flag that marks the mesh as a closed surface.
             * \param closed \c true to flag the mesh as closed, and \c false otherwise.
             */
            void setClosed(bool closed = true);

            /**
             * \brief Removes all vertices, vertex normals and faces and resets the closed-surface flag.
             */
            void clear();

            /**
             * \brief Swaps the vertices, vertex normals and faces of this mesh with those of \a mesh.
             * \param mesh The mesh to swap with.
             */
            void swap(TriangleMesh3D& mesh);

            /**
             * \brief Appends the vertices, vertex normals and (vertex index corrected) faces of \a mesh to this mesh.
             * \param mesh The mesh to append.
             * \return A reference to itself.
             */
            TriangleMesh3D& operator+=(const TriangleMesh3D& mesh);
            
          private:
            Math::Vector3DArray  vertices;
            Math::Vector3DArray  normals;
            Math::Vector3ULArray faces;
            bool                 closed{false};
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_TRIANGLEMESH3D_HPP
