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
# \brief 
# \param mesh 
# \param angle 
# \param vtx_offs 
# \param vtx_count 
#
def rotateX(mesh: TriangleMesh3D, angle: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param angle 
# \param vtx_offs 
# \param vtx_count 
#
def rotateY(mesh: TriangleMesh3D, angle: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param angle 
# \param vtx_offs 
# \param vtx_count 
#
def rotateZ(mesh: TriangleMesh3D, angle: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param scale_x 
# \param scale_y 
# \param scale_z 
# \param vtx_offs 
# \param vtx_count 
#
def scale(mesh: TriangleMesh3D, scale_x: float, scale_y: float, scale_z: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param trans_x 
# \param trans_y 
# \param trans_z 
# \param vtx_offs 
# \param vtx_count 
#
def translate(mesh: TriangleMesh3D, trans_x: float, trans_y: float, trans_z: float, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
#
def subdivideSpherical(mesh: TriangleMesh3D) -> None: pass

##
# \brief 
# \param mesh 
# \param mtx 
# \param vtx_offs 
# \param vtx_count 
#
def transform(mesh: TriangleMesh3D, mtx: Math.Matrix4D, vtx_offs: int = 0, vtx_count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param check_vn 
# \param tol 
# \return 
#
def removeVertexDuplicates(mesh: TriangleMesh3D, check_vn: bool = True, tol: float = 0.0) -> int: pass

##
# \brief 
# \param mesh 
# \param weight_face_size 
#
def calcVertexFromFaceNormals(mesh: TriangleMesh3D, weight_face_size: bool = False) -> None: pass

##
# \brief 
# \param mesh 
# \param normals 
# \param weight_face_size 
#
def calcVertexFromFaceNormals(mesh: TriangleMesh3D, normals: Math.Vector3DArray, weight_face_size: bool = False) -> None: pass
