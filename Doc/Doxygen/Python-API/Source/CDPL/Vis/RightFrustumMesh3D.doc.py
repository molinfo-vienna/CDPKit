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
# \brief A pre-defined triangle mesh providing the vertices and faces of a right frustum specified by the contructor arguments.
# 
# \since 1.3
# 
class RightFrustumMesh3D(TriangleMesh3D):

    ##
    # \brief Constructs a right-frustum triangle mesh with the specified bottom radius, top radius, height, side count and optional bottom/top caps.
    # 
    # \param radius1 The radius of the bottom circle.
    # \param radius2 The radius of the top circle.
    # \param height The height of the frustum.
    # \param num_sides The number of sides used to approximate the lateral surface.
    # \param close_btm <tt>True</tt> to include the bottom cap, and <tt>False</tt> to leave the bottom open.
    # \param close_top <tt>True</tt> to include the top cap, and <tt>False</tt> to leave the top open.
    # 
    def __init__(radius1: float, radius2: float, height: float, num_sides: int, close_btm: bool = True, close_top: bool = True) -> None: pass

    ##
    # \brief Initializes a copy of the \c %RightFrustumMesh3D instance \a mesh.
    # \param mesh The \c %RightFrustumMesh3D instance to copy.
    # 
    def __init__(mesh: RightFrustumMesh3D) -> None: pass
