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
# \param a 
# \param vtx_offs 
# \param count 
#
def rotateX(mesh: TriangleMesh3D, a: float, vtx_offs: int = 0, count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param a 
# \param vtx_offs 
# \param count 
#
def rotateY(mesh: TriangleMesh3D, a: float, vtx_offs: int = 0, count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param a 
# \param vtx_offs 
# \param count 
#
def rotateZ(mesh: TriangleMesh3D, a: float, vtx_offs: int = 0, count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param sx 
# \param sy 
# \param sz 
# \param vtx_offs 
# \param count 
#
def scale(mesh: TriangleMesh3D, sx: float, sy: float, sz: float, vtx_offs: int = 0, count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
# \param tx 
# \param ty 
# \param tz 
# \param vtx_offs 
# \param count 
#
def translate(mesh: TriangleMesh3D, tx: float, ty: float, tz: float, vtx_offs: int = 0, count: int = 0) -> None: pass

##
# \brief 
# \param mesh 
#
def subdivideSpherical(mesh: TriangleMesh3D) -> None: pass
