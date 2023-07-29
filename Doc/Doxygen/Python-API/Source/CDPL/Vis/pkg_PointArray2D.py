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
# \brief Stores a set of points in 2D space.
# 
class PointArray2D(Math.Vector2DArray):

    ##
    # \brief Initializes the \e %PointArray2D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %PointArray2D instance.
    # \param array 
    # 
    def __init__(array: PointArray2D) -> None: pass

    ##
    # \brief Translates all points by <em>vec</em>.
    # 
    # \param vec The translation vector.
    # 
    def translate(vec: Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param bbox 
    #
    def getBounds(bbox: Rectangle2D) -> None: pass
