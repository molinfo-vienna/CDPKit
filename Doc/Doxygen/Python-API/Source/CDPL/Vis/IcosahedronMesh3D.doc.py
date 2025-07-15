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
# \brief A pre-defined triangle mesh providing the vertices and faces of a regular icosahedron.
# 
# \since 1.3
# 
class IcosahedronMesh3D(TriangleMesh3D):

    ##
    # \brief Initializes the \e %IcosahedronMesh3D instance.
    # \param radius 
    # 
    def __init__(radius: float = 1.0) -> None: pass

    ##
    # \brief Initializes a copy of the \e %IcosahedronMesh3D instance \a mesh.
    # \param mesh The \e %IcosahedronMesh3D instance to copy.
    # 
    def __init__(mesh: IcosahedronMesh3D) -> None: pass
