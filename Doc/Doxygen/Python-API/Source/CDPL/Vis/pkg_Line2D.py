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
class Line2D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param self The \e %Line2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param self The \e %Line2D instance to initialize.
    # \param line 
    #
    def __init__(self: object, line: Line2D) -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param self The \e %Line2D instance to initialize.
    # \param beg 
    # \param end 
    #
    def __init__(self: object, beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param self The \e %Line2D instance to initialize.
    # \param beg_x 
    # \param beg_y 
    # \param end_x 
    # \param end_y 
    #
    def __init__(self: object, beg_x: float, beg_y: float, end_x: float, end_y: float) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Line2D instance this method is called upon.
    #
    # Different Python \e %Line2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Line2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Line2D) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Line2D instance \a line.
    # \param self The \e %Line2D instance this method is called upon.
    # \param line The \e %Line2D instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Line2D, line: Line2D) -> Line2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt 
    #
    def setBegin(self: Line2D, pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def setBegin(self: Line2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getBegin(self: Line2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt 
    #
    def setEnd(self: Line2D, pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def setEnd(self: Line2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getEnd(self: Line2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param beg 
    # \param end 
    #
    def setPoints(self: Line2D, beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param beg_x 
    # \param beg_y 
    # \param end_x 
    # \param end_y 
    #
    def setPoints(self: Line2D, beg_x: float, beg_y: float, end_x: float, end_y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    #
    def swapPoints(self: Line2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getDirection(self: Line2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param dir 
    #
    def getDirection(self: Line2D, dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getCCWPerpDirection(self: Line2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param dir 
    #
    def getCCWPerpDirection(self: Line2D, dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getCWPerpDirection(self: Line2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param dir 
    #
    def getCWPerpDirection(self: Line2D, dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getCenter(self: Line2D) -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param ctr 
    #
    def getCenter(self: Line2D, ctr: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \return 
    #
    def getLength(self: Line2D) -> float: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param vec 
    #
    def translate(self: Line2D, vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param vec 
    #
    def translateBegin(self: Line2D, vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param vec 
    #
    def translateEnd(self: Line2D, vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt 
    # \return 
    #
    def containsPoint(self: Line2D, pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt 
    # \return 
    #
    def getIntersectionPoint(self: Line2D, pt: Line2D) -> object: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param line 
    # \return 
    #
    def clipBeginAgainstLineSeg(self: Line2D, line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param line 
    # \return 
    #
    def clipEndAgainstLineSeg(self: Line2D, line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param line 
    # \return 
    #
    def setBeginToLineSegIntersection(self: Line2D, line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param line 
    # \return 
    #
    def setEndToLineSegIntersection(self: Line2D, line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param rect 
    # \return 
    #
    def clipBeginAgainstRectangle(self: Line2D, rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param rect 
    # \return 
    #
    def clipEndAgainstRectangle(self: Line2D, rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt 
    # \return 
    #
    def getDistance(self: Line2D, pt: CDPL.Math.Vector2D) -> float: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == line</tt>.
    # \param self The \e %Line2D instance this method is called upon.
    # \param line The \e %Line2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Line2D, line: Line2D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != line</tt>.
    # \param self The \e %Line2D instance this method is called upon.
    # \param line The \e %Line2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Line2D, line: Line2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>pt in self</tt>.
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Line2D, pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    length = property(getLength)

    ##
    # \brief 
    #
    begin = property(getBegin, setBegin)

    ##
    # \brief 
    #
    end = property(getEnd, setEnd)

    ##
    # \brief 
    #
    direction = property(getDirection)

    ##
    # \brief FIXME!
    #
    ccwPerpDirection = property(getCcwPerpDirection)

    ##
    # \brief FIXME!
    #
    cwPerpDirection = property(getCwPerpDirection)

    ##
    # \brief 
    #
    center = property(getCenter)
