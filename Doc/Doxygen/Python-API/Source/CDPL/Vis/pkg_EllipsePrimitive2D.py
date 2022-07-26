#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    # \param self The \e %EllipsePrimitive2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %EllipsePrimitive2D instance.
    # \param self The \e %EllipsePrimitive2D instance to initialize.
    # \param pos 
    # \param width 
    # \param height 
    #
    def __init__(self: object, pos: CDPL.Math.Vector2D, width: float, height: float) -> None: pass

    ##
    # \brief Initializes the \e %EllipsePrimitive2D instance.
    # \param self The \e %EllipsePrimitive2D instance to initialize.
    # \param prim 
    #
    def __init__(self: object, prim: EllipsePrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %EllipsePrimitive2D instance \a prim.
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \param prim The \e %EllipsePrimitive2D instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: EllipsePrimitive2D, prim: EllipsePrimitive2D) -> EllipsePrimitive2D: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \param width 
    #
    def setWidth(self: EllipsePrimitive2D, width: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \return 
    #
    def getWidth(self: EllipsePrimitive2D) -> float: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \param height 
    #
    def setHeight(self: EllipsePrimitive2D, height: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \return 
    #
    def getHeight(self: EllipsePrimitive2D) -> float: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \param pos 
    #
    def setPosition(self: EllipsePrimitive2D, pos: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \return 
    #
    def getPosition(self: EllipsePrimitive2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \param pen 
    #
    def setPen(self: EllipsePrimitive2D, pen: Pen) -> None: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \return 
    #
    def getPen(self: EllipsePrimitive2D) -> Pen: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \param brush 
    #
    def setBrush(self: EllipsePrimitive2D, brush: Brush) -> None: pass

    ##
    # \brief 
    # \param self The \e %EllipsePrimitive2D instance this method is called upon.
    # \return 
    #
    def getBrush(self: EllipsePrimitive2D) -> Brush: pass

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
