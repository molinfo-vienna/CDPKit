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
# \brief A graphics primitive representing a ellipse.
# 
class EllipsePrimitive2D(GraphicsPrimitive2D):

    ##
    # \brief Constructs an undefined ellipse primitive.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs an undefined ellipse primitive.
    # 
    def __init__(pos: Math.Vector2D, width: float, height: float) -> None: pass

    ##
    # \brief Initializes a copy of the \e %EllipsePrimitive2D instance \a prim.
    # \param prim The \e %EllipsePrimitive2D instance to copy.
    # 
    def __init__(prim: EllipsePrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %EllipsePrimitive2D instance \a prim.
    # \param prim The \c %EllipsePrimitive2D instance to copy.
    # \return \a self
    # 
    def assign(prim: EllipsePrimitive2D) -> EllipsePrimitive2D: pass

    ##
    # \brief Sets the diameter of the ellipse in x-direction.
    # 
    # \param width The width of the ellipse.
    # 
    def setWidth(width: float) -> None: pass

    ##
    # \brief Returns the diameter of the ellipse in x-direction.
    # 
    # \return The width of the ellipse.
    # 
    def getWidth() -> float: pass

    ##
    # \brief Sets the diameter of the ellipse in y-direction.
    # 
    # \param height The height of the ellipse.
    # 
    def setHeight(height: float) -> None: pass

    ##
    # \brief Returns the diameter of the ellipse in y-direction.
    # 
    # \return The height of the ellipse.
    # 
    def getHeight() -> float: pass

    ##
    # \brief Sets the position of the ellipse center.
    # 
    # \param pos The center position of the ellipse.
    # 
    def setPosition(pos: Math.Vector2D) -> None: pass

    ##
    # \brief Returns the position of the ellipse center.
    # 
    # \return The center position of the ellipse.
    # 
    def getPosition() -> Math.Vector2D: pass

    ##
    # \brief Sets the pen defining the color, width, line style, cap style and join style of the ellipse outline.
    # 
    # \param pen The pen defining the color, width, line style, cap style and join style of the ellipse's outline.
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Returns the pen defining the color, width, line style, cap style and join style of the ellipse outline.
    # 
    # \return The pen defining the color, width, line style, cap style and join style of the ellipse outline.
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

    width = property(getWidth, setWidth)

    height = property(getHeight, setHeight)

    position = property(getPosition, setPosition)

    pen = property(getPen, setPen)

    brush = property(getBrush, setBrush)
