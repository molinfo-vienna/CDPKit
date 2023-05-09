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
class TextLabelPrimitive2D(GraphicsPrimitive2D):

    ##
    # \brief Initializes the \e %TextLabelPrimitive2D instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %TextLabelPrimitive2D instance.
    # \param prim 
    #
    def __init__(prim: TextLabelPrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TextLabelPrimitive2D instance \a prim.
    # \param prim The \e %TextLabelPrimitive2D instance to copy.
    # \return \a self
    #
    def assign(prim: TextLabelPrimitive2D) -> TextLabelPrimitive2D: pass

    ##
    # \brief 
    # \param txt 
    #
    def setText(txt: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getText() -> str: pass

    ##
    # \brief 
    # \param pos 
    #
    def setPosition(pos: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def setPosition(x: float, y: float) -> None: pass

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
    # \param font 
    #
    def setFont(font: Font) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFont() -> Font: pass

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
