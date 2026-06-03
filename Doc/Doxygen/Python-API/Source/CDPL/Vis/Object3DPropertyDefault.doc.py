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
# \brief Provides default values for built-in Vis.Object3D properties.
# 
# \since 1.3
# 
class Object3DPropertyDefault(Boost.Python.instance):

    ##
    # \brief Default value of the Vis.Object3DProperty.SHAPE property.
    # 
    SHAPE = None

    ##
    # \brief Default value of the Vis.Object3DProperty.TRANSFORMATION_MATRIX property.
    # 
    TRANSFORMATION_MATRIX = [4,4]((1,0,0,0),(0,1,0,0),(0,0,1,0),(0,0,0,1))
