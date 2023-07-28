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
# \brief An interface class with methods that provide information about the metrics of a font.
# 
# Implementations of the <tt>FontMetrics</tt> interface provide height and width information for a given font and specific character glyphs in that font. Once a font has been specified with setFont(), there are several methods that operate on the font.
# 
# The methods
#  - getAscent()
#  - getDescent()
#  - getHeight()
#  - and getLeading()
# 
# return basic size properties of the font. The ascent is the maximum amount by which characters ascend <em>above</em> the baseline, and the descent is the maximum amount by which characters descend <em>below</em> the baseline. The leading, or interline spacing, is the logical amount of space to be reserved between the descent of one line of text and the ascent of the next line. The height metric is the sum of the ascent and descent plus some implementation dependent extra space.
# 
# For single characters or strings, the advance width can be obtained by getWidth(). The advance width specifies the distance to a position on the baseline where the next character(s) should be drawn. A bounding rectangle large enough to contain the rendered glyph of a character, or a set of glyphs for a string, can be retrieved by getBounds().
# 
class FontMetrics(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FontMetrics instance.
    # \param self The \e %FontMetrics instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FontMetrics instance this method is called upon.
    # 
    # Different Python \e %FontMetrics instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FontMetrics instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Specifies the font for which to obtain the metrics.
    # 
    # \param font Specifies the font for which to retrieve the metrics.
    # 
    def setFont(font: Font) -> None: pass

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
    # \param string 
    # \return 
    #
    def getWidth(string: str) -> float: pass

    ##
    # \brief 
    # \param string 
    # \param bounds 
    #
    def getBounds(string: str, bounds: Rectangle2D) -> None: pass

    objectID = property(getObjectID)
