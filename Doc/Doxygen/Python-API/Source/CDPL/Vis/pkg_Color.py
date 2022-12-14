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
class Color(Boost.Python.instance):

    ##
    # \brief 
    #
    BLACK = Color(r=0, g=0, b=0)

    ##
    # \brief 
    #
    BLUE = Color(r=0, g=0, b=1)

    ##
    # \brief 
    #
    CYAN = Color(r=0, g=1, b=1)

    ##
    # \brief 
    #
    DARK_BLUE = Color(r=0, g=0, b=0.5)

    ##
    # \brief 
    #
    DARK_CYAN = Color(r=0, g=0.5, b=0.5)

    ##
    # \brief 
    #
    DARK_GRAY = Color(r=0.5, g=0.5, b=0.5)

    ##
    # \brief 
    #
    DARK_GREEN = Color(r=0, g=0.5, b=0)

    ##
    # \brief 
    #
    DARK_MAGENTA = Color(r=0.5, g=0, b=0.5)

    ##
    # \brief 
    #
    DARK_RED = Color(r=0.5, g=0, b=0)

    ##
    # \brief 
    #
    DARK_YELLOW = Color(r=0.5, g=0.5, b=0)

    ##
    # \brief 
    #
    GRAY = Color(r=0.625, g=0.625, b=0.625)

    ##
    # \brief 
    #
    GREEN = Color(r=0, g=1, b=0)

    ##
    # \brief 
    #
    LIGHT_GRAY = Color(r=0.75, g=0.75, b=0.75)

    ##
    # \brief 
    #
    MAGENTA = Color(r=1, g=0, b=1)

    ##
    # \brief 
    #
    RED = Color(r=1, g=0, b=0)

    ##
    # \brief 
    #
    TRANSPARENT = Color()

    ##
    # \brief 
    #
    WHITE = Color(r=1, g=1, b=1)

    ##
    # \brief 
    #
    YELLOW = Color(r=1, g=1, b=0)

    ##
    # \brief Initializes the \e %Color instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Color instance.
    # \param color 
    #
    def __init__(color: Color) -> None: pass

    ##
    # \brief Initializes the \e %Color instance.
    # \param red 
    # \param green 
    # \param blue 
    # \param alpha 
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
    # \brief 
    # \return 
    #
    def getAlpha() -> float: pass

    ##
    # \brief 
    # \param alpha 
    #
    def setAlpha(alpha: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBlue() -> float: pass

    ##
    # \brief 
    # \param blue 
    #
    def setBlue(blue: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGreen() -> float: pass

    ##
    # \brief 
    # \param green 
    #
    def setGreen(green: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRed() -> float: pass

    ##
    # \brief 
    # \param red 
    #
    def setRed(red: float) -> None: pass

    ##
    # \brief 
    # \param red 
    # \param green 
    # \param blue 
    # \param alpha 
    #
    def setRGBA(red: float, green: float, blue: float, alpha: float = 1.0) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == color</tt>.
    # \param color The \e %Color instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(color: Color) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != color</tt>.
    # \param color The \e %Color instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(color: Color) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Color instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    red = property(getRed, setRed)

    ##
    # \brief 
    #
    green = property(getGreen, setGreen)

    ##
    # \brief 
    #
    blue = property(getBlue, setBlue)

    ##
    # \brief 
    #
    alpha = property(getAlpha, setAlpha)
