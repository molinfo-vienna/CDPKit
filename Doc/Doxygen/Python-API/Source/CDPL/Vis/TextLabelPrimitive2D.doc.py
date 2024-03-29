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
# \brief A graphics primitive representing a text label.
# 
class TextLabelPrimitive2D(GraphicsPrimitive2D):

    ##
    # \brief Construct an empty text label primitive at position <em>(0, 0)</em>.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %TextLabelPrimitive2D instance \a prim.
    # \param prim The \e %TextLabelPrimitive2D instance to copy.
    # 
    def __init__(prim: TextLabelPrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TextLabelPrimitive2D instance \a prim.
    # \param prim The \e %TextLabelPrimitive2D instance to copy.
    # \return \a self
    # 
    def assign(prim: TextLabelPrimitive2D) -> TextLabelPrimitive2D: pass

    ##
    # \brief Sets the text of the label.
    # 
    # \param txt The text of the label.
    # 
    def setText(text: str) -> None: pass

    ##
    # \brief Returns the text of the label.
    # 
    # \return The text of the label.
    # 
    def getText() -> str: pass

    ##
    # \brief Sets the position of the text label.
    # 
    # \param pos The baseline position of the text label.
    # 
    def setPosition(pos: Math.Vector2D) -> None: pass

    ##
    # \brief Sets the position of the text label to <em>(x, y)</em>.
    # 
    # \param x The x-position of the text label.
    # \param y The y-position of the baseline.
    # 
    def setPosition(x: float, y: float) -> None: pass

    ##
    # \brief Returns the position of the text label.
    # 
    # \return The position of the text label.
    # 
    def getPosition() -> Math.Vector2D: pass

    ##
    # \brief Sets the pen defining the color of the text label.
    # 
    # \param pen The pen defining the color of the text label.
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Returns the pen defining the color of the text label.
    # 
    # \return The pen defining the color of the text label.
    # 
    def getPen() -> Pen: pass

    ##
    # \brief Sets the font of the text label.
    # 
    # \param font The font of the text label.
    # 
    def setFont(font: Font) -> None: pass

    ##
    # \brief Returns the font of the text label.
    # 
    # \return The font of the text label.
    # 
    def getFont() -> Font: pass

    text = property(getText, setText)

    position = property(getPosition, setPosition)

    pen = property(getPen, setPen)

    font = property(getFont, setFont)
