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
    # \param self The \e %Rectangle2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    # \param self The \e %Rectangle2D instance to initialize.
    # \param rect 
    #
    def __init__(self: object, rect: Rectangle2D) -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    # \param self The \e %Rectangle2D instance to initialize.
    # \param min 
    # \param max 
    #
    def __init__(self: object, min: CDPL.Math.Vector2D, max: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance.
    # \param self The \e %Rectangle2D instance to initialize.
    # \param min_x 
    # \param min_y 
    # \param max_x 
    # \param max_y 
    #
    def __init__(self: object, min_x: float, min_y: float, max_x: float, max_y: float) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Rectangle2D instance this method is called upon.
    #
    # Different Python \e %Rectangle2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Rectangle2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Rectangle2D) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Rectangle2D instance \a rect.
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect The \e %Rectangle2D instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Rectangle2D, rect: Rectangle2D) -> Rectangle2D: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def isDefined(self: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param pt 
    #
    def addPoint(self: Rectangle2D, pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def addPoint(self: Rectangle2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param width 
    # \param height 
    #
    def addMargin(self: Rectangle2D, width: float, height: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect 
    #
    def addRectangle(self: Rectangle2D, rect: Rectangle2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param pt 
    # \return 
    #
    def containsPoint(self: Rectangle2D, pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param x 
    # \param y 
    # \return 
    #
    def containsPoint(self: Rectangle2D, x: float, y: float) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect 
    # \return 
    #
    def containsRectangle(self: Rectangle2D, rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect 
    # \return 
    #
    def intersectsRectangle(self: Rectangle2D, rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param pt 
    #
    def setMin(self: Rectangle2D, pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def setMin(self: Rectangle2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param pt 
    #
    def setMax(self: Rectangle2D, pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def setMax(self: Rectangle2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param min 
    # \param max 
    #
    def setBounds(self: Rectangle2D, min: CDPL.Math.Vector2D, max: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param min_x 
    # \param min_y 
    # \param max_x 
    # \param max_y 
    #
    def setBounds(self: Rectangle2D, min_x: float, min_y: float, max_x: float, max_y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def getMin(self: Rectangle2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def getMax(self: Rectangle2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def getCenter(self: Rectangle2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param ctr 
    #
    def getCenter(self: Rectangle2D, ctr: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def getArea(self: Rectangle2D) -> float: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def getWidth(self: Rectangle2D) -> float: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return 
    #
    def getHeight(self: Rectangle2D) -> float: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    #
    def reset(self: Rectangle2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param factor 
    #
    def scale(self: Rectangle2D, factor: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param vec 
    #
    def translate(self: Rectangle2D, vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Returns a string representation of the \e %Rectangle2D instance.
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: Rectangle2D) -> str: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == rect</tt>.
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect The \e %Rectangle2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Rectangle2D, rect: Rectangle2D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != rect</tt>.
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect The \e %Rectangle2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Rectangle2D, rect: Rectangle2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>pt in self</tt>.
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param pt The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Rectangle2D, pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>rect in self</tt>.
    # \param self The \e %Rectangle2D instance this method is called upon.
    # \param rect The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Rectangle2D, rect: Rectangle2D) -> bool: pass

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
