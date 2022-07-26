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
class TextLabelPrimitive2D(GraphicsPrimitive2D):

    ##
    # \brief Initializes the \e %TextLabelPrimitive2D instance.
    # \param self The \e %TextLabelPrimitive2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TextLabelPrimitive2D instance.
    # \param self The \e %TextLabelPrimitive2D instance to initialize.
    # \param prim 
    #
    def __init__(self: object, prim: TextLabelPrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TextLabelPrimitive2D instance \a prim.
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \param prim The \e %TextLabelPrimitive2D instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: TextLabelPrimitive2D, prim: TextLabelPrimitive2D) -> TextLabelPrimitive2D: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \param txt 
    #
    def setText(self: TextLabelPrimitive2D, txt: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \return 
    #
    def getText(self: TextLabelPrimitive2D) -> str: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \param pos 
    #
    def setPosition(self: TextLabelPrimitive2D, pos: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def setPosition(self: TextLabelPrimitive2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \return 
    #
    def getPosition(self: TextLabelPrimitive2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \param pen 
    #
    def setPen(self: TextLabelPrimitive2D, pen: Pen) -> None: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \return 
    #
    def getPen(self: TextLabelPrimitive2D) -> Pen: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \param font 
    #
    def setFont(self: TextLabelPrimitive2D, font: Font) -> None: pass

    ##
    # \brief 
    # \param self The \e %TextLabelPrimitive2D instance this method is called upon.
    # \return 
    #
    def getFont(self: TextLabelPrimitive2D) -> Font: pass

    ##
    # \brief 
    #
    text = property(getText, setText)

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
    font = property(getFont, setFont)
