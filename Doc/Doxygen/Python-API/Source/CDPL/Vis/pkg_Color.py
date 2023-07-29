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
# \brief Specifies a color in terms of its red, green and blue components and an alpha-channel for transparency.
# 
# Each component of the RGBA quadruplet is represented by a double precision floating-point value in the interval <em>[0, 1]</em>, where <em>0</em> corresponds to the lowest (zero) intensity of a color component and the value <em>1</em> represents the highest intensity. Likewise, a value of <em>1</em> for the alpha-channel corresponds to complete opaqueness and <em>0</em> represents complete transparency.
# 
class Color(Boost.Python.instance):

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>black</em>.
    # 
    BLACK = Color(r=0, g=0, b=0)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>blue</em>.
    # 
    BLUE = Color(r=0, g=0, b=1)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>cyan</em>.
    # 
    CYAN = Color(r=0, g=1, b=1)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark blue</em>.
    # 
    DARK_BLUE = Color(r=0, g=0, b=0.5)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark cyan</em>.
    # 
    DARK_CYAN = Color(r=0, g=0.5, b=0.5)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark gray</em>.
    # 
    DARK_GRAY = Color(r=0.5, g=0.5, b=0.5)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark green</em>.
    # 
    DARK_GREEN = Color(r=0, g=0.5, b=0)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark magenta</em>.
    # 
    DARK_MAGENTA = Color(r=0.5, g=0, b=0.5)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark red</em>.
    # 
    DARK_RED = Color(r=0.5, g=0, b=0)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>dark yellow</em>.
    # 
    DARK_YELLOW = Color(r=0.5, g=0.5, b=0)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>gray</em>.
    # 
    GRAY = Color(r=0.625, g=0.625, b=0.625)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>green</em>.
    # 
    GREEN = Color(r=0, g=1, b=0)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>light gray</em>.
    # 
    LIGHT_GRAY = Color(r=0.75, g=0.75, b=0.75)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>magenta</em>.
    # 
    MAGENTA = Color(r=1, g=0, b=1)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>red</em>.
    # 
    RED = Color(r=1, g=0, b=0)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for a totally transparent (alpha = 0) <em>black</em>.
    # 
    TRANSPARENT = Color()

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>white</em>.
    # 
    WHITE = Color(r=1, g=1, b=1)

    ##
    # \brief A preinitialized <tt>Color</tt> instance for the color <em>yellow</em>.
    # 
    YELLOW = Color(r=1, g=1, b=0)

    ##
    # \brief Constructs and initializes a <tt>Color</tt> object with all RGBA components set to zero.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Color instance.
    # \param color 
    # 
    def __init__(color: Color) -> None: pass

    ##
    # \brief Constructs and initializes a <tt>Color</tt> object with the RGBA components set to the specified values.
    # 
    # Component values outside the interval <em>[0, 1]</em> are clamped to the nearest interval bound, i.e. <em>0</em> if the value is negative and <em>1</em> if the value is greater than one.
    # 
    # \param red The value of the red color component.
    # \param green The value of the green color component.
    # \param blue The value of the blue color component.
    # \param alpha The value of the alpha component.
    # 
    def __init__(red: float, green: float, blue: float, alpha: float = 1.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Color instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Color instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Color instance \a color.
    # \param color The \e %Color instance to copy.
    # \return \a self
    # 
    def assign(color: Color) -> Color: pass

    ##
    # \brief Returns the value of the alpha component.
    # 
    # \return The value of the alpha component.
    # 
    def getAlpha() -> float: pass

    ##
    # \brief Sets the value of the alpha component to <em>alpha</em>.
    # 
    # If <em>alpha</em> is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval bound, i.e. <em>0</em> if <em>alpha</em> is negative and <em>1</em> if <em>alpha</em> is greater than one.
    # 
    # \param alpha The value of the alpha component.
    # 
    def setAlpha(alpha: float) -> None: pass

    ##
    # \brief Returns the value of the blue color component.
    # 
    # \return The value of the blue color component.
    # 
    def getBlue() -> float: pass

    ##
    # \brief Sets the value of the blue color component to <em>blue</em>.
    # 
    # If <em>blue</em> is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval bound, i.e. <em>0</em> if <em>blue</em> is negative and <em>1</em> if <em>blue</em> is greater than one.
    # 
    # \param blue The value of the blue color component.
    # 
    def setBlue(blue: float) -> None: pass

    ##
    # \brief Returns the value of the green color component.
    # 
    # \return The value of the green color component.
    # 
    def getGreen() -> float: pass

    ##
    # \brief Sets the the value of green color component to <em>green</em>.
    # 
    # If <em>green</em> is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval bound, i.e. <em>0</em> if <em>green</em> is negative and <em>1</em> if <em>green</em> is greater than one.
    # 
    # \param green The value of the green color component.
    # 
    def setGreen(green: float) -> None: pass

    ##
    # \brief Returns the value of the red color component.
    # 
    # \return The value of the red color component.
    # 
    def getRed() -> float: pass

    ##
    # \brief Sets the value of the red color component to <em>red</em>.
    # 
    # If <em>red</em> is outside the interval <em>[0, 1]</em> the value is clamped to the nearest interval bound, i.e. <em>0</em> if <em>red</em> is negative and <em>1</em> if <em>red</em> is greater than one.
    # 
    # \param red The value of the red color component.
    # 
    def setRed(red: float) -> None: pass

    ##
    # \brief Sets the values of the RGBA components to specified values.
    # 
    # Component values outside the interval <em>[0, 1]</em> are clamped to the nearest interval bound, i.e. <em>0</em> if the value is negative and <em>1</em> if the value is greater than one.
    # 
    # \param red The value of the red color component.
    # \param green The value of the green color component.
    # \param blue The value of the blue color component.
    # \param alpha The value of the alpha component.
    # 
    def setRGBA(red: float, green: float, blue: float, alpha: float = 1.0) -> None: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param color The other <tt>Color</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if all pairs of the RGBA components compare equal, <tt>False</tt> otherwise.
    # 
    def __eq__(color: Color) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == color)</tt>.
    # 
    # \param color The other <tt>Color</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if at least one pair of the RGBA components compares non-equal, <tt>False</tt> otherwise.
    # 
    def __ne__(color: Color) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Color instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    red = property(getRed, setRed)

    green = property(getGreen, setGreen)

    blue = property(getBlue, setBlue)

    alpha = property(getAlpha, setAlpha)
