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
# \brief Implements the FontMetrics interface for the <em>Cairo</em> rendering backend.
# 
# For more information about the <em>Cairo 2D Graphics Library</em> see [\ref CAIRO].
# 
class CairoFontMetrics(Vis.FontMetrics):

    ##
    # \brief Constructs a font metrics object that operates on the <em>Cairo</em> drawing context specified by <em>cairo_ctxt</em>.
    # 
    # \param cairo_ctxt The <em>Cairo</em> drawing context.
    # 
    # \throw Base.NullPointerException if <em>cairo_ctxt</em> is <em>None</em>.
    # 
    def __init__(cairo_ctxt: cairo.Context) -> None: pass

    ##
    # \brief Specifies the font for which to obtain the metrics.
    # 
    # \param font Specifies the font for which to retrieve the metrics.
    # 
    def setFont(font: Vis.Font) -> None: pass

    ##
    # \brief Returns the ascent of the font.
    # 
    # The ascent is the maximum distance from the baseline to the highest position characters extend to. Some font designers break this rule, e.g. when they put more than one accent on top of a character, or to accommodate an unusual character in an exotic language, so it is possible (though rare) that this value will be too small.
    # 
    # \return The ascent of the font. 
    # 
    # \see getDescent()
    # 
    def getAscent() -> float: pass

    ##
    # \brief Returns the descent of the font.
    # 
    # The descent is the distance from the baseline to the lowest position characters extend to. Some font designers break this rule, e.g. to accommodate an unusual character in an exotic language, so it is possible (though rare) that this value will be too small.
    # 
    # \return The descent of the font. 
    # 
    # \see getAscent()
    # 
    def getDescent() -> float: pass

    ##
    # \brief Returns the height of the font.
    # 
    # The returned height is the sum of the ascent and descent plus some possible implementation dependent extra space.
    # 
    # \return The height of the font.
    # 
    def getHeight() -> float: pass

    ##
    # \brief Returns the leading of the font.
    # 
    # The leading, or interline spacing, is the logical amount of space to be reserved between the descent of one line of text and the ascent of the next line.
    # 
    # \return The leading of the font.
    # 
    def getLeading() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getWidth() -> float: pass

    ##
    # \brief 
    # \param string 
    # \param bounds 
    # \return 
    #
    def getBounds(string: str, bounds: Vis.Rectangle2D) -> float: pass
