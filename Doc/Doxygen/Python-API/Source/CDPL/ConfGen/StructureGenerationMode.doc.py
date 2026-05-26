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
# \brief Provides constants used to specify the 3D structure generation method that shall be employed.
# 
class StructureGenerationMode(Boost.Python.instance):

    ##
    # \brief Specifies to select the structure generation strategy heuristically based on characteristics of the input molecule.
    # 
    AUTO = 0

    ##
    # \brief Specifies to perform structure generation by assembly of pre-built fragment conformers.
    # 
    FRAGMENT = 1

    ##
    # \brief Specifies to perform structure generation by a combination of distance geometry-based raw coordinates generation and subsequent force field refinement.
    # 
    DISTANCE_GEOMETRY = 2
