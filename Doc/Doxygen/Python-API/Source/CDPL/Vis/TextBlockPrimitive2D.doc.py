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
# \brief A graphics primitive representing a block of styled text.
# 
# Class <tt>TextBlockPrimitive2D</tt> is smiliar to Vis.TextLabelPrimitive2D but way more versatile. <tt>TextBlockPrimitive2D</tt> can store/render text that spans multiple lines with configurable line spacing (see setLineSpacing()) and alignment (see setAlignment()), and supports changing text color and various attributes like font weight and slant for individual text portions. Furthermore, text fragments can be rendered sub/super-scripted, under- and overlined as well as striked out. This is achieved by using an XML-based syntax where a portion of text to be rendered in a particular style is enclosed in specific start and end tags. More information on the syntax, the supported styling tags and their meaning can be found in the documentation of the method setText().
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
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TextBlockPrimitive2D instance \a prim.
    # \param prim The \c %TextBlockPrimitive2D instance to copy.
    # \return \a self
    # 
    def assign(prim: TextBlockPrimitive2D) -> TextBlockPrimitive2D: pass

    ##
    # \brief Specifies the block's text content.
    # 
    # Color, font attributes and style of individual text fragments can be controlled by enclosing the concerned piece of text in specific XML tags. The following tags are supported:
    # 
    # <table>
    #  <tr><th>Tag</th><th>Effect/Description</th></tr>
    #  <tr><td><br/></td><td>Line break</td></tr>
    #  <tr><td><b></td><td>Boldfaced text</td></tr>
    #  <tr><td><i></td><td>Italicized text</td></tr>
    #  <tr><td><o></td><td>Overlined text</td></tr>
    #  <tr><td><u></td><td>Underlined text</td></tr>
    #  <tr><td><s></td><td>Striked-out text</td></tr>
    #  <tr><td><sub></td><td>Subscripted text</td></tr>
    #  <tr><td><sup></td><td>Superscripted text</td></tr>
    #  <tr><td><color></td><td>Text color; supports the attributes <em>r</em>, <em>g</em>, <em>b</em> and <em>a</em> with a value in the range [0.0, 1.0]; default component values are <em>r=0</em>, <em>b=0</em>, <em>g=0</em> and <em>a=1</em></td></tr>
    # </table>
    # 
    # Newline characters <tt>\n</tt> are regarded and interpreted as such. Tab characters <tt>\t</tt> are replaced by a single whitespace character. Any other special characters are deleted. The supported tags listed above are all optional. Plain ASCII text will thus be rendered using the set font (see setFont()) and color (see setPen()).
    # 
    # \param text The text content of the block.
    # 
    # \throw Base.ValueError if XML parsing of the specified text failed.
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
    # \brief Tells whether the text block has any visible text (includes whitespace).
    # 
    # \return <tt>True</tt> if there is any visible text and <tt>False</tt> otherwise.
    # 
    def hasText() -> bool: pass

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
    # \note Calling this method invalidates the current layout (see layout()).
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
    # Possible horizontal alignment values are defined in namespace Vis.Alignment.
    # 
    # \param alignment The horizontal text alignment specification.
    # 
    def setAlignment(alignment: int) -> None: pass

    ##
    # \brief Returns the active horizontal text alignment specification.
    # 
    # Possible horizontal alignment values are defined in namespace Vis.Alignment.
    # 
    # \return The current horizontal text alignment specification.
    # 
    def getAlignment() -> int: pass

    ##
    # \brief Sets the line spacing value.
    # 
    # The final base line spacing is the product of the specified line spacing and the font height returned by the method Vis.FontMetrics.getHeight() for the set font.
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
    # \brief Performs a layout of the text for the currently specified font using the provided Vis.FontMetrics instance <em>font_metrics</em>.
    # 
    # \param font_metrics An instance of a class implementing the Vis.FontMetrics interface.
    # 
    # \note This method must be called before the text is rendered by calling the method render(). The methods setText() or setFont() invalidate the text layout.
    # 
    def layout(font_metrics: FontMetrics) -> None: pass

    text = property(getText, setText)

    position = property(getPosition, setPosition)

    pen = property(getPen, setPen)

    font = property(getFont, setFont)

    alignment = property(getAlignment, setAlignment)

    lineSpacing = property(getLineSpacing, setLineSpacing)
