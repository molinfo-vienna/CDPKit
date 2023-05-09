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
# \brief 
#
class EllipsePrimitive2D(GraphicsPrimitive2D):

    ##
    # \brief Initializes the \e %EllipsePrimitive2D instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %EllipsePrimitive2D instance.
    # \param pos 
    # \param width 
    # \param height 
    #
    def __init__(pos: CDPL.Math.Vector2D, width: float, height: float) -> None: pass

    ##
    # \brief Initializes the \e %EllipsePrimitive2D instance.
    # \param prim 
    #
    def __init__(prim: EllipsePrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %EllipsePrimitive2D instance \a prim.
    # \param prim The \e %EllipsePrimitive2D instance to copy.
    # \return \a self
    #
    def assign(prim: EllipsePrimitive2D) -> EllipsePrimitive2D: pass

    ##
    # \brief 
    # \param width 
    #
    def setWidth(width: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getWidth() -> float: pass

    ##
    # \brief 
    # \param height 
    #
    def setHeight(height: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getHeight() -> float: pass

    ##
    # \brief 
    # \param pos 
    #
    def setPosition(pos: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPosition() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param pen 
    #
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPen() -> Pen: pass

    ##
    # \brief 
    # \param brush 
    #
    def setBrush(brush: Brush) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBrush() -> Brush: pass

    ##
    # \brief 
    #
    width = property(getWidth, setWidth)

    ##
    # \brief 
    #
    height = property(getHeight, setHeight)

    ##
    # \brief 
    #
    position = property(getPosition, setPosition)

    ##
    # \brief 
    #
    pen = property(getPen, setPen)

    ##
    # \brief 
    #
    brush = property(getBrush, setBrush)
