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
    # \brief Specifies the font to use for the calculation of text metrics.
    # 
    # \param font The font used for the calculation of text metrics.
    # 
    def setFont(font: Vis.Font) -> None: pass

    ##
    # \brief Returns the ascent of the current font.
    # 
    # \return The ascent of the current font.
    # 
    def getAscent() -> float: pass

    ##
    # \brief Returns the descent of the current font.
    # 
    # \return The descent of the current font.
    # 
    def getDescent() -> float: pass

    ##
    # \brief Returns the height of the current font.
    # 
    # \return The height of the current font.
    # 
    def getHeight() -> float: pass

    ##
    # \brief Returns the leading of the current font.
    # 
    # \return The leading of the current font.
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
