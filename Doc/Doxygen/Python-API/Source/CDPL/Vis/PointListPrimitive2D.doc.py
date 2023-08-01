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
# \brief A graphics primitive representing a list of points.
# 
class PointListPrimitive2D(PointArray2D, GraphicsPrimitive2D):

    ##
    # \brief Constructs an empty point list primitive.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %PointListPrimitive2D instance with a copy of the state of the \e %PointListPrimitive2D instance \a prim.
    # \param prim The \e %PointListPrimitive2D instance to copy.
    # 
    def __init__(prim: PointListPrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PointListPrimitive2D instance \a prim.
    # \param prim The \e %PointListPrimitive2D instance to copy.
    # \return \a self
    # 
    def assign(prim: PointListPrimitive2D) -> PointListPrimitive2D: pass

    ##
    # \brief Sets the pen defining the color and diameter of the points.
    # 
    # \param pen The pen defining the color and diameter of the points.
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Returns the pen defining the color and diameter of the points.
    # 
    # \return The pen defining the color and diameter of the points.
    # 
    def getPen() -> Pen: pass

    pen = property(getPen, setPen)
