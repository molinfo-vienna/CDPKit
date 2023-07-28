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
# \brief Specifies a line segment in 2D space.
# 
class Line2D(Boost.Python.instance):

    ##
    # \brief Constructs a line whose starting and end point is set to <em>(0, 0)</em>.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Line2D instance.
    # \param self The \e %Line2D instance to initialize.
    # \param line 
    # 
    def __init__(line: Line2D) -> None: pass

    ##
    # \brief Constructs a line with the specified starting and end point.
    # 
    # \param beg The starting point.
    # \param end The end point.
    # 
    def __init__(beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Constructs a line with the starting point set to <em>(beg_x, beg_y)</em> and the end point set to <em>(end_x, end_y)</em>.
    # 
    # \param beg_x The x-coordinate of the starting point.
    # \param beg_y The y-coordinate of the starting point.
    # \param end_x The x-coordinate of the end point.
    # \param end_y The y-coordinate of the end point.
    # 
    def __init__(beg_x: float, beg_y: float, end_x: float, end_y: float) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param line 
    # \return 
    #
    def assign(line: Line2D) -> Line2D: pass

    ##
    # \brief Sets the starting point of the line to <em>pt</em>.
    # 
    # \param pt The new starting point of the line.
    # 
    def setBegin(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Sets the starting point of the line to <em>(x, y)</em>.
    # 
    # \param x The x-coordinate of the new starting point.
    # \param y The y-coordinate of the new starting point.
    # 
    def setBegin(x: float, y: float) -> None: pass

    ##
    # \brief Returns the starting point of the line.
    # 
    # \return The starting point of the line.
    # 
    def getBegin() -> CDPL.Math.Vector2D: pass

    ##
    # \brief Sets the end point of the line to <em>pt</em>.
    # 
    # \param pt The new end point of the line.
    # 
    def setEnd(pt: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Sets the end point of the line to <em>(x, y)</em>.
    # 
    # \param x The x-coordinate of the new end point.
    # \param y The y-coordinate of the new end point.
    # 
    def setEnd(x: float, y: float) -> None: pass

    ##
    # \brief Returns the end point of the line.
    # 
    # \return The end point of the line.
    # 
    def getEnd() -> CDPL.Math.Vector2D: pass

    ##
    # \brief Sets the starting point of the line to <em>beg</em> and the end point to <em>end</em>.
    # 
    # \param beg The new starting point.
    # \param end The new end point.
    # 
    def setPoints(beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Sets the starting point of the line to <em>(beg_x, beg_y)</em> and the end point to <em>(end_x, end_y)</em>.
    # 
    # \param beg_x The x-coordinate of the new starting point.
    # \param beg_y The y-coordinate of the new starting point.
    # \param end_x The x-coordinate of the new end point.
    # \param end_y The y-coordinate of the new end point.
    # 
    def setPoints(beg_x: float, beg_y: float, end_x: float, end_y: float) -> None: pass

    ##
    # \brief Swaps the starting and end point of the line.
    # 
    # The old starting point becomes the new end point and the old end point becomes the new starting point.
    # 
    def swapPoints() -> None: pass

    ##
    # \brief Calculates the normalized direction vector of the line.
    # 
    # \return The calculated direction vector.
    # 
    def getDirection() -> CDPL.Math.Vector2D: pass

    ##
    # \brief Calculates the normalized direction vector of the line and stores the result in <em>dir</em>.
    # 
    # \param dir Holds the calculated direction vector.
    # 
    def getDirection(dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in counter-clockwise direction.
    # 
    # \return The calculated rotated direction vector.
    # 
    def getCCWPerpDirection() -> CDPL.Math.Vector2D: pass

    ##
    # \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in counter-clockwise direction and stores the result in <em>dir</em>.
    # 
    # \param dir Holds the calculated rotated direction vector.
    # 
    def getCCWPerpDirection(dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in clockwise direction.
    # 
    # \return The calculated rotated direction vector.
    # 
    def getCWPerpDirection() -> CDPL.Math.Vector2D: pass

    ##
    # \brief Calculates the normalized direction vector rotated by <em>90</em> degrees in clockwise direction and stores the result in <em>dir</em>.
    # 
    # \param dir Holds the calculated rotated direction vector.
    # 
    def getCWPerpDirection(dir: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Calculates the center point of the line.
    # 
    # \return The calculated center point of the line.
    # 
    def getCenter() -> CDPL.Math.Vector2D: pass

    ##
    # \brief Calculates the center point of the line and stores the result in <em>ctr</em>.
    # 
    # \param ctr Holds the calculated center point of the line.
    # 
    def getCenter(ctr: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Returns the length of the line segment.
    # 
    # \return The length of the line segment.
    # 
    def getLength() -> float: pass

    ##
    # \brief Translates the starting and end point of the line by <em>vec</em>.
    # 
    # \param vec The translation vector.
    # 
    def translate(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Translates the starting point of the line by <em>vec</em>.
    # 
    # \param vec The translation vector.
    # 
    def translateBegin(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Translates the end of the line point by <em>vec</em>.
    # 
    # \param vec The translation vector.
    # 
    def translateEnd(vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Tests if the point <em>pt</em> is contained within the boundary of the line segment.
    # 
    # The point <em>pt</em> is considered to be contained within the boundary of the line segment if the dot product of the line's direction vector and the vector from the starting point to <em>pt</em> is positive or zero, and furthermore the dot product of the direction vector and the vector from the end point to <em>pt</em> is negative or zero.
    # 
    # \param pt The point to test.
    # 
    # \return <tt>True</tt> if <em>pt</em> is contained within the boundary of the line segment, and <tt>False</tt> otherwise.
    # 
    def containsPoint(pt: CDPL.Math.Vector2D) -> bool: pass

    ##
    # \brief 
    # \param pt 
    # \return 
    #
    def getIntersectionPoint(pt: Line2D) -> object: pass

    ##
    # \brief Sets the starting point of the line to the point of intersection with the specified line segment.
    # 
    # If the lines are parallel or the point of intersection is not within the boundaries of <em>both</em> line segments, the starting point of the line is left unaltered and <tt>False</tt> is returned.
    # 
    # \param line The other line segment to clip against.
    # 
    # \return <tt>False</tt> if the lines are parallel or the intersection point is not within the boundaries of both line segments, and <tt>True</tt> otherwise.
    # 
    def clipBeginAgainstLineSeg(line: Line2D) -> bool: pass

    ##
    # \brief Sets the end point of the line to the point of intersection with the specified line segment.
    # 
    # If the lines are parallel or the point of intersection is not within the boundaries of <em>both</em> line segments, the end point of the line is left unaltered and <tt>False</tt> is returned.
    # 
    # \param line The other line segment to clip against.
    # 
    # \return <tt>False</tt> if the lines are parallel or the intersection point is not within the boundaries of both line segments, and <tt>True</tt> otherwise.
    # 
    def clipEndAgainstLineSeg(line: Line2D) -> bool: pass

    ##
    # \brief Sets the starting point of the line to the point of intersection with the specified line segment.
    # 
    # If the lines are parallel or the point of intersection is not within the boundary of the line segment <em>line</em>, the starting point of the line is left unaltered and <tt>False</tt> is returned.
    # 
    # \param line The other line segment.
    # 
    # \return <tt>False</tt> if the lines are parallel or the intersection point is not within the boundary of <em>line</em>, and <tt>True</tt> otherwise.
    # 
    def setBeginToLineSegIntersection(line: Line2D) -> bool: pass

    ##
    # \brief Sets the end point of the line to the point of intersection with the specified line segment.
    # 
    # If the lines are parallel or the point of intersection is not within the boundary of the line segment <em>line</em>, the end point of the line is left unaltered and <tt>False</tt> is returned.
    # 
    # \param line The other line segment.
    # 
    # \return <tt>False</tt> if the lines are parallel or the intersection point is not within the boundary of <em>line</em>, and <tt>True</tt> otherwise.
    # 
    def setEndToLineSegIntersection(line: Line2D) -> bool: pass

    ##
    # \brief Sets the starting point of the line to the point of intersection between this line segment and the edges of the rectangle <em>rect</em>.
    # 
    # If the line segment intersects with more than one edge of <em>rect</em>, the starting point is set to the intersection point which results in the shortest clipped line segment. If the line segment does not intersect with an edge of <em>rect</em>, the starting point is left unaltered and <tt>False</tt> is returned.
    # 
    # \param rect The rectangle to clip againts.
    # 
    # \return <tt>True</tt> if the line segment was clipped against an edge of <em>rect</em>, and <tt>False</tt> otherwise.
    # 
    def clipBeginAgainstRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Sets the end point of the line to the point of intersection between this line segment and the edges of the rectangle <em>rect</em>.
    # 
    # If the line segment intersects with more than one edge of <em>rect</em>, the end point is set to the intersection point which results in the shortest clipped line segment. If the line segment does not intersect with an edge of <em>rect</em>, the end point is left unaltered and <tt>False</tt> is returned.
    # 
    # \param rect The rectangle to clip againts.
    # 
    # \return <tt>True</tt> if the line segment was clipped against an edge of <em>rect</em>, and <tt>False</tt> otherwise.
    # 
    def clipEndAgainstRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Returns the perpendicular distance of the point <em>pt</em> to this line.
    # 
    # The measured distance is the distance between the point <em>pt</em> and the closest point on the infinitely extended line. If <em>pt</em> intersects the line, the method returns <em>0.0</em>.
    # 
    # \param pt The point for which to calculate the shortest distance.
    # 
    # \return The shortest distance between <em>pt</em> and the infinitely extended line.
    # 
    def getDistance(pt: CDPL.Math.Vector2D) -> float: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param line The other <tt>Line2D</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the starting and end points compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(line: Line2D) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == line)</tt>.
    # 
    # \param line The other <tt>Line2D</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if either the starting or end points compare non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(line: Line2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>pt in self</tt>.
    # \param self The \e %Line2D instance this method is called upon.
    # \param pt The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(pt: CDPL.Math.Vector2D) -> bool: pass

    objectID = property(getObjectID)

    length = property(getLength)

    begin = property(getBegin, setBegin)

    end = property(getEnd, setEnd)

    direction = property(getDirection)

    ##
    # \brief FIXME!
    # \brief 
    #
    ccwPerpDirection = property(getCcwPerpDirection)

    ##
    # \brief FIXME!
    # \brief 
    #
    cwPerpDirection = property(getCwPerpDirection)

    center = property(getCenter)
