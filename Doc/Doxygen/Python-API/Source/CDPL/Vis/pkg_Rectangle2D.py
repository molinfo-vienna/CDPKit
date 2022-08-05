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
class Rectangle2D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    # \param rect 
    #
    def __init__(rect: Rectangle2D) -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    # \param min 
    # \param max 
    #
    def __init__(min: CDPL.Math.Vector2D, max: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    # \param min_x 
    # \param min_y 
    # \param max_x 
    # \param max_y 
    #
    def __init__(min_x: float, min_y: float, max_x: float, max_y: float) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %Rectangle2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Rectangle2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Rectangle2D instance \a rect.
    # \param rect The \e %Rectangle2D instance to copy.
    # \return The assignment target \a self.
    #
    def assign(rect: Rectangle2D) -> Rectangle2D: pass

    ##
    # \brief 
    # \return 
    #
    def isDefined() -> bool: pass

    ##
    # \brief 
    # \param pt 
    #
    def addPoint(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def addPoint(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param width 
    # \param height 
    #
    def addMargin(width: float, height: float) -> None: pass

    ##
    # \brief 
    # \param rect 
    #
    def addRectangle(rect: Rectangle2D) -> None: pass

    ##
    # \brief 
    # \param pt 
    # \return 
    #
    def containsPoint(pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    # \return 
    #
    def containsPoint(x: float, y: float) -> bool: pass

    ##
    # \brief 
    # \param rect 
    # \return 
    #
    def containsRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param rect 
    # \return 
    #
    def intersectsRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param pt 
    #
    def setMin(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def setMin(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param pt 
    #
    def setMax(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def setMax(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param min 
    # \param max 
    #
    def setBounds(min: CDPL.Math.Vector2D, max: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param min_x 
    # \param min_y 
    # \param max_x 
    # \param max_y 
    #
    def setBounds(min_x: float, min_y: float, max_x: float, max_y: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMin() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \return 
    #
    def getMax() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \return 
    #
    def getCenter() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param ctr 
    #
    def getCenter(ctr: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getArea() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getWidth() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getHeight() -> float: pass

    ##
    # \brief 
    #
    def reset() -> None: pass

    ##
    # \brief 
    # \param factor 
    #
    def scale(factor: float) -> None: pass

    ##
    # \brief 
    # \param vec 
    #
    def translate(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Returns a string representation of the \e %Rectangle2D instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == rect</tt>.
    # \param rect The \e %Rectangle2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != rect</tt>.
    # \param rect The \e %Rectangle2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>pt in self</tt>.
    # \param pt The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>rect in self</tt>.
    # \param rect The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    defined = property(getDefined)

    ##
    # \brief 
    #
    min = property(getMin, setMin)

    ##
    # \brief 
    #
    max = property(getMax, setMax)

    ##
    # \brief 
    #
    center = property(getCenter)

    ##
    # \brief 
    #
    width = property(getWidth)

    ##
    # \brief 
    #
    height = property(getHeight)

    ##
    # \brief 
    #
    area = property(getArea)
