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
# \brief A graphics primitive representing a set of connected line segments.
# 
class PolylinePrimitive2D(PointArray2D, GraphicsPrimitive2D):

    ##
    # \brief Constructs an empty polyline primitive.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %PolylinePrimitive2D instance \a prim.
    # \param prim The \e %PolylinePrimitive2D instance to copy.
    # 
    def __init__(prim: PolylinePrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %PolylinePrimitive2D instance \a prim.
    # \param prim The \c %PolylinePrimitive2D instance to copy.
    # \return \a self
    # 
    def assign(prim: PolylinePrimitive2D) -> PolylinePrimitive2D: pass

    ##
    # \brief Sets the pen defining the color, width, line style, join style and cap style of the line segments.
    # 
    # \param pen The pen defining the color, width, line style, join style and cap style of the line segments.
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Returns the pen defining the color, width, line style, join style and cap style of the line segments.
    # 
    # \return The pen defining the color, width, line style, join style and cap style of the line segments.
    # 
    def getPen() -> Pen: pass

    pen = property(getPen, setPen)
