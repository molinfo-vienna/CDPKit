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
    # \param self The \e %Color instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Color instance.
    # \param self The \e %Color instance to initialize.
    # \param color 
    #
    def __init__(self: object, color: Color) -> None: pass

    ##
    # \brief Initializes the \e %Color instance.
    # \param self The \e %Color instance to initialize.
    # \param red 
    # \param green 
    # \param blue 
    # \param alpha 
    #
    def __init__(self: object, red: float, green: float, blue: float, alpha: float = 1.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Color instance this method is called upon.
    #
    # Different Python \e %Color instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Color instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Color) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Color instance \a color.
    # \param self The \e %Color instance this method is called upon.
    # \param color The \e %Color instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Color, color: Color) -> Color: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \return 
    #
    def getAlpha(self: Color) -> float: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \param alpha 
    #
    def setAlpha(self: Color, alpha: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \return 
    #
    def getBlue(self: Color) -> float: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \param blue 
    #
    def setBlue(self: Color, blue: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \return 
    #
    def getGreen(self: Color) -> float: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \param green 
    #
    def setGreen(self: Color, green: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \return 
    #
    def getRed(self: Color) -> float: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \param red 
    #
    def setRed(self: Color, red: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Color instance this method is called upon.
    # \param red 
    # \param green 
    # \param blue 
    # \param alpha 
    #
    def setRGBA(self: Color, red: float, green: float, blue: float, alpha: float = 1.0) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == color</tt>.
    # \param self The \e %Color instance this method is called upon.
    # \param color The \e %Color instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Color, color: Color) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != color</tt>.
    # \param self The \e %Color instance this method is called upon.
    # \param color The \e %Color instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Color, color: Color) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Color instance.
    # \param self The \e %Color instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: Color) -> str: pass

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
