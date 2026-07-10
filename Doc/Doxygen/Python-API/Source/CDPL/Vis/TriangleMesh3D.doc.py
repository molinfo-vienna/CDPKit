#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Data structure for the storage of 3D triangle mesh vertices, vertex normals and faces.
# 
# \since 1.3
# 
class TriangleMesh3D(Shape3D):

    ##
    # \brief Initializes the \c %TriangleMesh3D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %TriangleMesh3D instance \a mesh.
    # \param mesh The \c %TriangleMesh3D instance to copy.
    # 
    def __init__(mesh: TriangleMesh3D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TriangleMesh3D instance \a mesh.
    # \param mesh The \c %TriangleMesh3D instance to copy.
    # \return \a self
    # 
    def assign(mesh: TriangleMesh3D) -> TriangleMesh3D: pass

    ##
    # \brief Returns a reference to the array storing the mesh vertices.
    # 
    # \return A reference to the vertex array.
    # 
    def getVertices() -> Math.Vector3DArray: pass

    ##
    # \brief Appends a new vertex at the position <em>(x, y, z)</em>.
    # 
    # \param x The x-coordinate of the vertex.
    # \param y The y-coordinate of the vertex.
    # \param z The z-coordinate of the vertex.
    # 
    def addVertex(x: float, y: float, z: float) -> None: pass

    ##
    # \brief Returns the number of stored vertices.
    # 
    # \return The vertex count.
    # 
    def getNumVertices() -> int: pass

    ##
    # \brief Returns a reference to the array storing the per-vertex normals.
    # 
    # \return A reference to the vertex-normal array.
    # 
    def getVertexNormals() -> Math.Vector3DArray: pass

    ##
    # \brief Appends a new vertex normal with the components <em>(x, y, z)</em>.
    # 
    # \param x The x-component of the normal vector.
    # \param y The y-component of the normal vector.
    # \param z The z-component of the normal vector.
    # 
    def addVertexNormal(x: float, y: float, z: float) -> None: pass

    ##
    # \brief Returns the number of stored vertex normals.
    # 
    # \return The vertex normal count.
    # 
    def getNumVertexNormals() -> int: pass

    ##
    # \brief Returns a reference to the array storing the triangle faces.
    # 
    # \return A reference to the face array.
    # 
    def getFaces() -> Math.Vector3ULArray: pass

    ##
    # \brief Appends a new triangle face defined by the three vertex indices <em>v1_idx</em>, <em>v2_idx</em> and <em>v3_idx</em>.
    # 
    # \param v1_idx The zero-based index of the first vertex.
    # \param v2_idx The zero-based index of the second vertex.
    # \param v3_idx The zero-based index of the third vertex.
    # 
    def addFace(v1_idx: int, v2_idx: int, v3_idx: int) -> None: pass

    ##
    # \brief Returns the number of stored triangle faces.
    # 
    # \return The face count.
    # 
    def getNumFaces() -> int: pass

    ##
    # \brief Tells whether the mesh has been flagged as a closed surface.
    # 
    # \return <tt>True</tt> if the mesh is flagged as closed, and <tt>False</tt> otherwise.
    # 
    def isClosed() -> bool: pass

    ##
    # \brief Sets the flag that marks the mesh as a closed surface.
    # 
    # \param closed <tt>True</tt> to flag the mesh as closed, and <tt>False</tt> otherwise.
    # 
    def setClosed(closed: bool = True) -> None: pass

    ##
    # \brief Removes all vertices, vertex normals and faces and resets the closed-surface flag.
    # 
    def clear() -> None: pass

    ##
    # \brief Swaps the vertices, vertex normals and faces of this mesh with those of <em>mesh</em>.
    # 
    # \param mesh The mesh to swap with.
    # 
    def swap(mesh: TriangleMesh3D) -> TriangleMesh3D: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += mesh</tt>.
    # \param mesh Specifies the second addend.
    # \return The updated \c %TriangleMesh3D instance \a self.
    # 
    def __iadd__(mesh: TriangleMesh3D) -> TriangleMesh3D: pass

    vertices = property(getVertices)

    numVertices = property(getNumVertices)

    vertexNormals = property(getVertexNormals)

    numVertexNormals = property(getNumVertexNormals)

    faces = property(getFaces)

    numFaces = property(getNumFaces)

    closed = property(isClosed, setClosed)
