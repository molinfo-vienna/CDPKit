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
# \brief Specifies an axis aligned rectangular area in 2D space.
# 
# The rectangle is defined by a minimum point \f$ (x_{min}, y_{min}) \f$ and a maximum point \f$ (x_{max}, y_{max}) \f$. For a well defined rectangle the coordinates of the minimum and maximum point must satisfy the follwing inequalities: \f$ x_{min} \leq x_{max} \f$ and \f$ y_{min} \leq y_{max} \f$. <br>
# 
class Rectangle2D(Boost.Python.instance):

    ##
    # \brief Constructs an undefined rectangle.
    # 
    # The coordinates of the minimum point are set to <tt>std::numeric_limits<double>.max()</tt> and the coordinates of the maximum point are set to <tt>-<tt>std::numeric_limits<double>.max()</tt></tt>.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Rectangle2D instance with a copy of the state of the \e %Rectangle2D instance \a rect.
    # \param rect The \e %Rectangle2D instance to copy.
    # 
    def __init__(rect: Rectangle2D) -> None: pass

    ##
    # \brief Constructs a rectangle with the minimum point set to <em>min</em> and the maximum point set to <em>max</em>.
    # 
    # \param min The minimum point.
    # \param max The maximum point.
    # 
    def __init__(min: Math.Vector2D, max: Math.Vector2D) -> None: pass

    ##
    # \brief Constructs a rectangle with the minimum point set to <em>(min_x, min_y)</em> and the maximum point set to <em>(max_x, max_y)</em>.
    # 
    # \param min_x The x-coordinate of the minimum point.
    # \param min_y The y-coordinate of the minimum point.
    # \param max_x The x-coordinate of the maximum point.
    # \param max_y The y-coordinate of the maximum point.
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
    # \return \a self
    # 
    def assign(rect: Rectangle2D) -> Rectangle2D: pass

    ##
    # \brief Tells if the rectangle is well defined.
    # 
    # The rectangle is well defined if neither the height nor the width of the rectangle is negative.
    # 
    # \return <tt>True</tt> if the rectangle is defined, and <tt>False</tt> otherwise. 
    # 
    # \see getWidth(), getHeight()
    # 
    def isDefined() -> bool: pass

    ##
    # \brief Adds the point <em>pt</em> to the current rectangle.
    # 
    # The resulting (adjusted) rectangle represents the smallest rectangular area that contains both the original rectangle and the specified point <em>pt</em>.
    # 
    # \param pt The point to add.
    # 
    def addPoint(pt: Math.Vector2D) -> None: pass

    ##
    # \brief Adds the point <em>(x, y)</em> to the current rectangle.
    # 
    # The resulting (adjusted) rectangle represents the smallest rectangular area that contains both the original rectangle and the specified point <em>(x, y)</em>.
    # 
    # \param x The x-coordinate of the point to add.
    # \param y The y-coordinate of the point to add.
    # 
    def addPoint(x: float, y: float) -> None: pass

    ##
    # \brief Extends the rectangle by adding a margin with the specified width and height.
    # 
    # The minimum point gets translated by <em>(-width, -height)</em> and the maximum point by <em>(width, height)</em>.
    # 
    # \param width The amount the rectangle will be extended horizontally.
    # \param height The amount the rectangle will be extended vertically.
    # 
    def addMargin(width: float, height: float) -> None: pass

    ##
    # \brief Adds the rectangle <em>rect</em> to the current rectangle.
    # 
    # The resulting rectangle is the union of the two rectangle objects and contains both the original rectangle and the specified rectangle <em>rect</em>.
    # 
    # \param rect The other rectangle to add.
    # 
    def addRectangle(rect: Rectangle2D) -> None: pass

    ##
    # \brief Tests if the point <em>pt</em> is within the boundary of the rectangle.
    # 
    # A point lying exactly on one of the edges or corners is also considered to be within the boundaries.
    # 
    # \param pt The point to test.
    # 
    # \return <tt>True</tt> if <em>pt</em> is within the boundary of the rectangle, and <tt>False</tt> otherwise. <br>
    # 
    def containsPoint(pt: Math.Vector2D) -> bool: pass

    ##
    # \brief Tests if the point <em>(x, y)</em> is within the boundary of the rectangle.
    # 
    # A point lying exactly on one of the edges or corners is also considered to be within the boundaries.
    # 
    # \param x The x-coordinate of the point to test.
    # \param y The y-coordinate of the point to test.
    # 
    # \return <tt>True</tt> if the point <em>(x, y)</em> is within the boundary of the rectangle, and <tt>False</tt> otherwise. <br>
    # 
    def containsPoint(x: float, y: float) -> bool: pass

    ##
    # \brief Tests if the specified rectangle <em>rect</em> is within the boundary of this rectangle.
    # 
    # The result is equivalent to <tt>(this->containsPoint(rect.getMin()) && this->containsPoint(rect.getMax()))</tt>.
    # 
    # \param rect The rectangle to test.
    # 
    # \return <tt>True</tt> if the rectangle <em>rect</em> is within the boundary of this rectangle, and <tt>False</tt> otherwise.
    # 
    def containsRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Tests if the interior of this rectangle intersects the rectangle <em>rect</em>.
    # 
    # If the rectangles overlap only on one of their edges or corners, they are also considered to intersect.
    # 
    # \param rect The rectangle to test.
    # 
    # \return <tt>True</tt> if the rectangles intersect, and <tt>False</tt> otherwise.
    # 
    def intersectsRectangle(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Sets the minimum point of the rectangle to <em>pt</em>.
    # 
    # \param pt The new minimum point.
    # 
    def setMin(pt: Math.Vector2D) -> None: pass

    ##
    # \brief Sets the minimum point of the rectangle to <em>(x, y)</em>.
    # 
    # \param x The x-coordinate of the new minimum point.
    # \param y The y-coordinate of the new minimum point.
    # 
    def setMin(x: float, y: float) -> None: pass

    ##
    # \brief Sets the maximum point of the rectangle to <em>pt</em>.
    # 
    # \param pt The new maximum point.
    # 
    def setMax(pt: Math.Vector2D) -> None: pass

    ##
    # \brief Sets the maximum point of the rectangle to <em>(x, y)</em>.
    # 
    # \param x The x-coordinate of the new maximum point.
    # \param y The y-coordinate of the new maximum point.
    # 
    def setMax(x: float, y: float) -> None: pass

    ##
    # \brief Sets the minimum point of the rectangle to <em>min</em> and the maximum point to <em>max</em>.
    # 
    # \param min The new minimum point.
    # \param max The new maximum point.
    # 
    def setBounds(min: Math.Vector2D, max: Math.Vector2D) -> None: pass

    ##
    # \brief Sets the minimum point of the rectangle to <em>(min_x, min_y)</em> and the maximum point to <em>(max_x, max_y)</em>.
    # 
    # \param min_x The x-coordinate of the new minimum point.
    # \param min_y The y-coordinate of the new minimum point.
    # \param max_x The x-coordinate of the new maximum point.
    # \param max_y The y-coordinate of the new maximum point.
    # 
    def setBounds(min_x: float, min_y: float, max_x: float, max_y: float) -> None: pass

    ##
    # \brief Returns the minimum point of the rectangle.
    # 
    # \return The minimum point of the rectangle.
    # 
    def getMin() -> Math.Vector2D: pass

    ##
    # \brief Returns the maximum point of the rectangle.
    # 
    # \return The maximum point of the rectangle.
    # 
    def getMax() -> Math.Vector2D: pass

    ##
    # \brief Calculates the center of the rectangle.
    # 
    # \return The center of the rectangle.
    # 
    def getCenter() -> Math.Vector2D: pass

    ##
    # \brief Calculates the center of the rectangle and stores the result in <em>ctr</em>.
    # 
    # \param ctr A vector storing the calculated center point.
    # 
    def getCenter(ctr: Math.Vector2D) -> None: pass

    ##
    # \brief Calculates the area of the rectangle.
    # 
    # \return The calculated area of the rectangle.
    # 
    def getArea() -> float: pass

    ##
    # \brief Returns the width of the rectangle.
    # 
    # The width of the rectangle is the difference \f$ x_{max} - x_{min} \f$ between the x-coordinate of the maximum point \f$ x_{max} \f$ and the x-coordinate of the minimum point \f$ x_{min} \f$.
    # 
    # \return The width of the rectangle.
    # 
    def getWidth() -> float: pass

    ##
    # \brief Returns the height of the rectangle.
    # 
    # The height of the rectangle is the difference \f$ y_{max} - y_{min} \f$ between the y-coordinate of the maximum point \f$ y_{max} \f$ and the y-coordinate of the minimum point \f$ y_{min} \f$.
    # 
    # \return The height of the rectangle.
    # 
    def getHeight() -> float: pass

    ##
    # \brief Resets the rectangle to an undefinded state.
    # 
    # The coordinates of the minimum point are set to <tt>std::numeric_limits<double>.max()</tt> and the coordinates of the maximum point are set to <tt>-<tt>std::numeric_limits<double>.max()</tt></tt>.
    # 
    def reset() -> None: pass

    ##
    # \brief Scales the minimum and maximum point of the rectangle by the specified factor.
    # 
    # \param factor The scaling factor.
    # 
    def scale(factor: float) -> None: pass

    ##
    # \brief Translates the minimum and maximum point of the rectangle by <em>vec</em>.
    # 
    # \param vec The translation vector.
    # 
    def translate(vec: Math.Vector2D) -> None: pass

    ##
    # \brief Returns a string representation of the \e %Rectangle2D instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param rect The other <tt>Rectangle2D</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the minimum and maximum points compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == rect)</tt>.
    # 
    # \param rect The other <tt>Rectangle2D</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if either the minimum or maximum points compare non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(rect: Rectangle2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>pt in self</tt>.
    # \param pt The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(pt: Math.Vector2D) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>rect in self</tt>.
    # \param rect The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(rect: Rectangle2D) -> bool: pass

    objectID = property(getObjectID)

    defined = property(isDefined)

    min = property(getMin, setMin)

    max = property(getMax, setMax)

    center = property(getCenter)

    width = property(getWidth)

    height = property(getHeight)

    area = property(getArea)
