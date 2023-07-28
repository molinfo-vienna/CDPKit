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
# \brief A graphics primitive representing a polygon.
# 
class PolygonPrimitive2D(PointArray2D, GraphicsPrimitive2D):

    ##
    # \brief Constructs an undefined polygon primitive.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %PolygonPrimitive2D instance.
    # \param self The \e %PolygonPrimitive2D instance to initialize.
    # \param prim 
    # 
    def __init__(prim: PolygonPrimitive2D) -> None: pass

    ##
    # \brief 
    # \param prim 
    # \return 
    #
    def assign(prim: PolygonPrimitive2D) -> PolygonPrimitive2D: pass

    ##
    # \brief Sets the pen defining the color, width, line style, cap style and join style of the polygon outline.
    # 
    # \param pen The pen defining the color, width, line style, cap style and join style of the polygon's outline.
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Returns the pen defining the color, width, line style, cap style and join style of the polygon outline.
    # 
    # \return The pen defining the color, width, line style, cap style and join style of the polygon outline.
    # 
    def getPen() -> Pen: pass

    ##
    # \brief Sets the brush defining the fill color and fill pattern.
    # 
    # \param brush The brush defining the fill color and fill pattern.
    # 
    def setBrush(brush: Brush) -> None: pass

    ##
    # \brief Returns the brush defining the fill color and fill pattern.
    # 
    # \return The brush defining the fill color and fill pattern.
    # 
    def getBrush() -> Brush: pass

    pen = property(getPen, setPen)

    brush = property(getBrush, setBrush)
