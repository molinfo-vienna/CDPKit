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
# \brief Data structure for describing the geometric shape of 3D objects by means of a triangle mesh.
# 
# \since 1.3
# 
class TriangleMesh3D(Shape3D):

    ##
    # \brief Initializes the \e %TriangleMesh3D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %TriangleMesh3D instance \a mesh.
    # \param mesh The \e %TriangleMesh3D instance to copy.
    # 
    def __init__(mesh: TriangleMesh3D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TriangleMesh3D instance \a mesh.
    # \param mesh The \c %TriangleMesh3D instance to copy.
    # \return \a self
    # 
    def assign(mesh: TriangleMesh3D) -> TriangleMesh3D: pass

    ##
    # \brief 
    # \return 
    #
    def getVertices() -> Math.Vector3DArray: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    # \param z 
    #
    def addVertex(x: float, y: float, z: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumVertices() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getVertexNormals() -> Math.Vector3DArray: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    # \param z 
    #
    def addVertexNormal(x: float, y: float, z: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumVertexNormals() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getFaces() -> Math.Vector3ULArray: pass

    ##
    # \brief 
    # \param v1_idx 
    # \param v2_idx 
    # \param v3_idx 
    #
    def addFace(v1_idx: int, v2_idx: int, v3_idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFaces() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isClosed() -> bool: pass

    ##
    # \brief 
    # \param closed 
    #
    def setClosed(closed: bool = True) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param mesh 
    # \return 
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
