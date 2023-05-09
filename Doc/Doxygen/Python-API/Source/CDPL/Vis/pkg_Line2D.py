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
# \brief 
#
class Line2D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Line2D instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param line 
    #
    def __init__(line: Line2D) -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param beg 
    # \param end 
    #
    def __init__(beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param beg_x 
    # \param beg_y 
    # \param end_x 
    # \param end_y 
    #
    def __init__(beg_x: float, beg_y: float, end_x: float, end_y: float) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %Line2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Line2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Line2D instance \a line.
    # \param line The \e %Line2D instance to copy.
    # \return \a self
    #
    def assign(line: Line2D) -> Line2D: pass

    ##
    # \brief 
    # \param pt 
    #
    def setBegin(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def setBegin(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBegin() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param pt 
    #
    def setEnd(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def setEnd(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEnd() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param beg 
    # \param end 
    #
    def setPoints(beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param beg_x 
    # \param beg_y 
    # \param end_x 
    # \param end_y 
    #
    def setPoints(beg_x: float, beg_y: float, end_x: float, end_y: float) -> None: pass

    ##
    # \brief 
    #
    def swapPoints() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getDirection() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param dir 
    #
    def getDirection(dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCCWPerpDirection() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param dir 
    #
    def getCCWPerpDirection(dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCWPerpDirection() -> CDPL.Math.Vector2D: pass

    ##
    # \brief 
    # \param dir 
    #
    def getCWPerpDirection(dir: CDPL.Math.Vector2D) -> None: pass

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
    def getLength() -> float: pass

    ##
    # \brief 
    # \param vec 
    #
    def translate(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param vec 
    #
    def translateBegin(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param vec 
    #
    def translateEnd(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param pt 
    # \return 
    #
    def containsPoint(pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief 
    # \param pt 
    # \return 
    #
    def getIntersectionPoint(pt: Line2D) -> object: pass

    ##
    # \brief 
    # \param line 
    # \return 
    #
    def clipBeginAgainstLineSeg(line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param line 
    # \return 
    #
    def clipEndAgainstLineSeg(line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param line 
    # \return 
    #
    def setBeginToLineSegIntersection(line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param line 
    # \return 
    #
    def setEndToLineSegIntersection(line: Line2D) -> bool: pass

    ##
    # \brief 
    # \param rect 
    # \return 
    #
    def clipBeginAgainstRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param rect 
    # \return 
    #
    def clipEndAgainstRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief 
    # \param pt 
    # \return 
    #
    def getDistance(pt: CDPL.Math.Vector2D) -> float: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == line</tt>.
    # \param line The \e %Line2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(line: Line2D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != line</tt>.
    # \param line The \e %Line2D instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(line: Line2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>pt in self</tt>.
    # \param pt The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(pt: CDPL.Math.Vector2D) -> bool: pass

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
