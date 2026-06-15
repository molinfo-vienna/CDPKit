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
# \brief Pre-defined triangle mesh providing the vertices and faces of a torus specified by the contructor arguments.
# 
# \since 1.3
# 
class TorusMesh3D(TriangleMesh3D):

    ##
    # \brief Constructs a torus triangle mesh with the specified ring radius, tube radius, ring/tube subdivision counts and optional start-angle/first-section sizing.
    # 
    # \param radius1 The radius of the torus ring (distance from the torus center to the tube center).
    # \param radius2 The radius of the tube.
    # \param num_sect1 The number of sections subdividing the torus ring.
    # \param num_sect2 The number of sections subdividing the tube.
    # \param start_angle The angle (in radians) at which the first ring section starts.
    # \param first_sect_size The angular size of the first ring section (<em>0</em> to use a uniform section size).
    # 
    def __init__(radius1: float, radius2: float, num_sect1: int, num_sect2: int, start_angle: float = 0.0, first_sect_size: float = 0.0) -> None: pass

    ##
    # \brief Initializes a copy of the \c %TorusMesh3D instance \a mesh.
    # \param mesh The \c %TorusMesh3D instance to copy.
    # 
    def __init__(mesh: TorusMesh3D) -> None: pass
