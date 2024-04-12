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
# \brief A graphics primitive representing a block of styled text that comprises multiple lines.
# 
class TextBlockPrimitive2D(GraphicsPrimitive2D):

    ##
    # \brief Construct an empty text block primitive at position <em>(0, 0)</em>.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %TextBlockPrimitive2D instance \a prim.
    # \param prim The \e %TextBlockPrimitive2D instance to copy.
    # 
    def __init__(prim: TextBlockPrimitive2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TextBlockPrimitive2D instance \a prim.
    # \param prim The \e %TextBlockPrimitive2D instance to copy.
    # \return \a self
    # 
    def assign(prim: TextBlockPrimitive2D) -> TextBlockPrimitive2D: pass

    ##
    # \brief Specifies the block's text content.
    # 
    # \param text The text content of the block.
    # 
    def setText(text: str) -> None: pass

    ##
    # \brief Clears the block's text content.
    # 
    def clearText() -> None: pass

    ##
    # \brief Returns the block's text content.
    # 
    # \return The text content of the block.
    # 
    def getText() -> str: pass

    ##
    # \brief Sets the position of the text block in 2D space.
    # 
    # The position specifies the upper-left corner of the text block's bounding box.
    # 
    # \param pos Theposition of the text block.
    # 
    def setPosition(pos: Math.Vector2D) -> None: pass

    ##
    # \brief Sets the position of the text block to <em>(x, y)</em>.
    # 
    # The position specifies the upper-left corner of the text block's bounding box.
    # 
    # \param x The x-position of the text block.
    # \param y The y-position of the baseline.
    # 
    def setPosition(x: float, y: float) -> None: pass

    ##
    # \brief Returns the position of the text block.
    # 
    # \return The position of the text block. 
    # 
    # \see setPosition()
    # 
    def getPosition() -> Math.Vector2D: pass

    ##
    # \brief Sets the pen defining the default text color.
    # 
    # \param pen The pen defining the default text color.
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Returns the pen defining the default text color.
    # 
    # \return The pen defining the default text color.
    # 
    def getPen() -> Pen: pass

    ##
    # \brief Sets the font used for text rendering.
    # 
    # \param font The font used for text rendering.
    # 
    def setFont(font: Font) -> None: pass

    ##
    # \brief Returns the font used for text rendering.
    # 
    # \return The font used for text rendering.
    # 
    def getFont() -> Font: pass

    ##
    # \brief Specifies the way lines should be horizontally aligned.
    # 
    # Possible values are defined in namespace Vis.Alignment.
    # 
    # \param alignment The horizontal text alignment specification.
    # 
    def setAlignment(alignment: int) -> None: pass

    ##
    # \brief Returns the active horizontal text alignment specification.
    # 
    # Possible values are defined in namespace Vis.Alignment.
    # 
    # \return The current horizontal text alignment specification.
    # 
    def getAlignment() -> int: pass

    ##
    # \brief Sets the line spacing value.
    # 
    # The final base line spacing is the product of the specified line spacing and the font height returned by the method FontMetrics.getHeight() for the set font.
    # 
    # \param spacing The desired line spacing.
    # 
    def setLineSpacing(spacing: float) -> None: pass

    ##
    # \brief Returns the active line spacing value.
    # 
    # \return The line spacing value.
    # 
    def getLineSpacing() -> float: pass

    ##
    # \brief 
    # \param font_metrics 
    #
    def layout(font_metrics: FontMetrics) -> None: pass

    text = property(getText, setText)

    position = property(getPosition, setPosition)

    pen = property(getPen, setPen)

    font = property(getFont, setFont)

    alignment = property(getAlignment, setAlignment)

    lineSpacing = property(getLineSpacing, setLineSpacing)
