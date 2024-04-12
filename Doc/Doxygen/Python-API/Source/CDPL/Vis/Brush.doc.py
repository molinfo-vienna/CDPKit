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
# \brief Specifies the fill pattern and fill color of shapes.
# 
# A brush has a style and a color attribute. The style defines the look of the fill pattern and the color attribute specifies the color of the specified fill pattern. The style of a default constructed <tt>Brush</tt> object is Brush.NO_PATTERN, which tells the renderer not to fill drawn shapes.
# 
class Brush(Boost.Python.instance):

    ##
    # \brief Defines constants for supported fill pattern styles.
    # 
    class Style(Boost.Python.enum):

        ##
        # \brief Specifies that shapes should not be filled.
        # 
        NO_PATTERN = 0

        ##
        # \brief Specifies a solid pattern without any transparent pixels.
        # 
        SOLID_PATTERN = 1

        ##
        # \brief Specifies a pattern with <em>6.25%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE1_PATTERN = 2

        ##
        # \brief Specifies a pattern with <em>12.5%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE2_PATTERN = 3

        ##
        # \brief Specifies a pattern with <em>37.5%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE3_PATTERN = 4

        ##
        # \brief Specifies a pattern with <em>50.0%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE4_PATTERN = 5

        ##
        # \brief Specifies a pattern with <em>62.5%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE5_PATTERN = 6

        ##
        # \brief Specifies a pattern with <em>87.5%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE6_PATTERN = 7

        ##
        # \brief Specifies a pattern with <em>93.75%</em> uniformly distributed transparent pixels. <br>
        # 
        DENSE7_PATTERN = 8

        ##
        # \brief Specifies a pattern with equidistant horizontal lines.
        # 
        H_PATTERN = 9

        ##
        # \brief Specifies a pattern with equidistant vertical lines.
        # 
        V_PATTERN = 10

        ##
        # \brief Specifies a pattern with equidistant horizontal and vertical lines.
        # 
        CROSS_PATTERN = 11

        ##
        # \brief Specifies a pattern with equidistant diagonal lines from the upper right to the lower left corner.
        # 
        LEFT_DIAG_PATTERN = 12

        ##
        # \brief Specifies a pattern with equidistant diagonal lines from the upper left to the lower right corner.
        # 
        RIGHT_DIAG_PATTERN = 13

        ##
        # \brief Specifies a pattern with equidistant diagonal lines in both directions.
        # 
        DIAG_CROSS_PATTERN = 14

    ##
    # \brief Constructs a brush with fill pattern style Brush.NO_PATTERN and color Color.BLACK.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %Brush instance \a brush.
    # \param brush The \e %Brush instance to copy.
    # 
    def __init__(brush: Brush) -> None: pass

    ##
    # \brief Constructs a brush with the specified fill pattern style and the color Color.BLACK.
    # 
    # \param style The style of the fill pattern.
    # 
    def __init__(style: Style) -> None: pass

    ##
    # \brief Constructs a brush with the specified fill pattern style and color.
    # 
    # \param color The fill pattern color.
    # \param style The fill pattern style .
    # 
    def __init__(color: Color, style: Style = CDPL.Vis.Style.SOLID_PATTERN) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Brush instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Brush instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Brush instance \a brush.
    # \param brush The \e %Brush instance to copy.
    # \return \a self
    # 
    def assign(brush: Brush) -> Brush: pass

    ##
    # \brief Returns the fill pattern color.
    # 
    # \return The fill pattern color.
    # 
    def getColor() -> Color: pass

    ##
    # \brief Sets the fill pattern color.
    # 
    # \param color The fill pattern color.
    # 
    def setColor(color: Color) -> None: pass

    ##
    # \brief Returns the fill pattern style.
    # 
    # \return The fill pattern style.
    # 
    def getStyle() -> Style: pass

    ##
    # \brief Sets the fill pattern style.
    # 
    # \param style The the fill pattern style.
    # 
    def setStyle(style: Style) -> None: pass

    ##
    # \brief Returns a string representation of the \e %Brush instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param brush The other <tt>Brush</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the style and color attributes compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(brush: Brush) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == brush)</tt>.
    # 
    # \param brush The other <tt>Brush</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if either the style or the color attributes compare non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(brush: Brush) -> bool: pass

    objectID = property(getObjectID)

    color = property(getColor, setColor)

    style = property(getStyle, setStyle)
