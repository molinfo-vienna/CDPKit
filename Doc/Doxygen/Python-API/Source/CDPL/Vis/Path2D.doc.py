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
# \brief Provides a container for painting operations, enabling arbitrary graphical shapes to be constructed and reused.
# 
# A path consits of a number of graphical building blocks, such as rectangles, ellipses, lines and arcs. Building blocks can be joined to form closed subpaths, for example a rounded rectangle, or they can exist independently as unclosed subpaths, such as lines and curves. A closed path has coinciding start and end points.
# 
# <tt>Path2D</tt> objects can be used for filling, outlining, and clipping. The main advantage over a sequence of basic drawing operations is that complex shapes need to be created only once and can be stored for repeated later uses.
# 
# A <tt>Path2D</tt> object can be constructed as an empty path, or as a copy of another <tt>Path2D</tt> instance. Once created, lines and curves can be added to the path using the lineTo(), arcTo() and arc() functions. The lines and curves stretch from the current position to the position passed as argument. The current position is always the end point of the last drawing operation. Use the moveTo() method to move the current position without adding a component. The moveTo() method implicitly starts a new subpath, and closes the previous one. Another way of starting a new subpath is to call the closePath() method which closes the current path by adding a line from the current position back to the path's start position. The <tt>Path2D</tt> class also provides convenience methods for the generation of common shapes: addEllipse() and addRectangle(). The generation of these shapes is implemented by executing a sequence of appropriate moveTo(), lineTo() and arcTo() calls. The axis-aligned bounding box of a path constructed in this way can be calculated by the method getBounds().
# 
# Whether or not a <tt>Path2D</tt> object contains any elements can be queried by the method isEmpty(). Whether the path also features visual elements (lines and arcs) can be queried by the method hasDrawingElements(). The method clear() deletes all elements added so far and sets the default fill rule (see setFillRule() and getFillRule()).
# 
# Elements added to a <tt>Path2D</tt> object cannot inspected directly. For path analysis and rendering the method convert() is available which calls element type specific methods on a provided instance of a class implementing the Vis.Path2DConverter interface.
# 
# \since 1.1
# 
class Path2D(Boost.Python.instance):

    ##
    # \brief Specifies which method to use for filling closed shapes described by the <tt>Path2D</tt> object.
    # 
    class FillRule(Boost.Python.enum):

        ##
        # \brief Specifies that the path has to be filled using the odd even fill rule.
        # 
        # With this rule, the question whether a point is inside the shape can be answered by the following method: Draw a horizontal line from the point to a location outside the shape, and count the number of intersections. If the number of intersections is an odd number, the point is inside the shape.
        # 
        EVEN_ODD = 0

        ##
        # \brief Specifies that the path has to be filled using the non-zero winding rule.
        # 
        # With this rule, the question whether a point is inside the shape can be answered by the following method: Draw a horizontal line from the point to a location outside the shape. Determine whether the direction of the line at each intersection point is up or down. The winding number is determined by summing the direction of each intersection. If the number is non-zero, the point is inside the shape.
        # 
        WINDING = 1

    ##
    # \brief Constructs an empty <tt>Path2D</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>Path2D</tt> instance <em>path</em>.
    # 
    # \param path The <tt>Path2D</tt> instance to copy.
    # 
    def __init__(path: Path2D) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Path2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Path2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assignment operator.
    # 
    # \param path The <tt>Path2D</tt> instance to copy.
    # 
    # \return \a self
    # 
    def assign(path: Path2D) -> Path2D: pass

    ##
    # \brief Tells whether the <tt>Path2D</tt> instance does not contain any elements.
    # 
    # \return <tt>True</tt> is no elements have been added to the <tt>Path2D</tt> instance so far, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Tells whether the <tt>Path2D</tt> instance contains any elements representing drawing operations (lines and arcs).
    # 
    # \return <tt>True</tt> if the <tt>Path2D</tt> instance contains any visual elements, and <tt>False</tt> otherwise.
    # 
    def hasDrawingElements() -> bool: pass

    ##
    # \brief Deletes all path elements added so far and sets the fill rule to its default.
    # 
    # \see setFillRule()
    # 
    def clear() -> None: pass

    ##
    # \brief Sets the fill rule of the path to the specified value.
    # 
    # \param rule The new fill rule.
    # 
    # \note The default fill rule is Path2D.EVEN_ODD.
    # 
    def setFillRule(rule: FillRule) -> None: pass

    ##
    # \brief Returns the currently set fill rule.
    # 
    # \return The currently set fill rule.
    # 
    def getFillRule() -> FillRule: pass

    ##
    # \brief Sets the current position to <em>(x, y)</em> and starts a new subpath, implicitly closing the previous path.
    # 
    # \param x Specifies the x-coordinate of the new position.
    # \param y Specifies the y-coordinate of the new position.
    # 
    def moveTo(x: float, y: float) -> None: pass

    ##
    # \brief Sets the current position to <em>pos</em> and starts a new subpath, implicitly closing the previous path.
    # 
    # \param pos A 2D vector specifying the new position.
    # 
    def moveTo(pos: Math.Vector2D) -> None: pass

    ##
    # \brief Creates an elliptical arc centered at <em>(cx, cy)</em> with ellipse radii <em>rx</em> and <em>ry</em> beginning at the angle <em>start_ang</em> and extending <em>sweep</em> degrees clockwise.
    # 
    # Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles. After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use the closePath() method.
    # 
    # \param cx The x-coordinate of the ellipse center.
    # \param cy The y-coordinate of the ellipse center.
    # \param rx The x-radius of the ellipse.
    # \param ry The y-radius of the ellipse.
    # \param start_ang The start angle of the arg in degrees.
    # \param sweep The length of the arg in degrees.
    # 
    # \note The method first performs a moveTo() call with the starting point of the arc as argument and thus avoids an implicit line being drawn from the current position to the arc's starting position (see arcTo()).
    # 
    def arc(cx: float, cy: float, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief Creates an elliptical arc centered at <em>ctr</em> with ellipse radii <em>rx</em> and <em>ry</em> beginning at the angle <em>start_ang</em> and extending <em>sweep</em> degrees clockwise.
    # 
    # Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles. After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use the closePath() method.
    # 
    # \param ctr A 2D vector specifying the ellipse center.
    # \param rx The x-radius of the ellipse.
    # \param ry The y-radius of the ellipse.
    # \param start_ang The start angle of the arg in degrees.
    # \param sweep The length of the arg in degrees.
    # 
    # \note The method first performs a moveTo() call with the starting point of the arc as argument and thus avoids an implicit line being drawn from the current position to the arc's starting position (see arcTo()).
    # 
    def arc(ctr: Math.Vector2D, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief Creates an elliptical arc centered at <em>(cx, cy)</em> with ellipse radii <em>rx</em> and <em>ry</em> beginning at the angle <em>start_ang</em> and extending <em>sweep</em> degrees clockwise.
    # 
    # Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles. After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use the closePath() method. <br>
    # 
    # \param cx The x-coordinate of the ellipse center.
    # \param cy The y-coordinate of the ellipse center.
    # \param rx The x-radius of the ellipse.
    # \param ry The y-radius of the ellipse.
    # \param start_ang The start angle of the arg in degrees.
    # \param sweep The length of the arg in degrees.
    # 
    # \note The method implicitly connects the starting point of the arc to the current position if they are not already connected. The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
    # 
    def arcTo(cx: float, cy: float, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief Creates an elliptical arc centered at <em>ctr</em> with ellipse radii <em>rx</em> and <em>ry</em> beginning at the angle <em>start_ang</em> and extending <em>sweep</em> degrees clockwise.
    # 
    # Angles are specified in degrees. Counter-clockwise arcs can be specified using negative angles. After the arc has been added, the current position is the end point of the arc. To draw a line back to the first point, use the closePath() method.
    # 
    # \param ctr A 2D vector specifying the ellipse center.
    # \param rx The x-radius of the ellipse.
    # \param ry The y-radius of the ellipse.
    # \param start_ang The start angle of the arg in degrees.
    # \param sweep The length of the arg in degrees.
    # 
    # \note The method implicitly connects the starting point of the arc to the current position if they are not already connected. The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
    # 
    def arcTo(ctr: Math.Vector2D, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief Adds a straight line from the current position to the point <em>(x, y)</em>.
    # 
    # After the line is drawn, the current position is updated to be at the end point of the line.
    # 
    # \param x Specifies the x-coordinate of the line's end point.
    # \param y Specifies the y-coordinate of the line's end point.
    # 
    # \note The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
    # 
    def lineTo(x: float, y: float) -> None: pass

    ##
    # \brief Adds a straight line from the current position to the point <em>(x, y)</em>.
    # 
    # After the line is drawn, the current position is updated to be at the end point of the line.
    # 
    # \param pos A 2D vector specifying the line end point.
    # 
    # \note The rendering result is undefined if no subpath starting point has been specified (see moveTo())!
    # 
    def lineTo(pos: Math.Vector2D) -> None: pass

    ##
    # \brief Closes the current subpath by drawing a line to the beginning of the subpath, automatically starting a new path.
    # 
    # A call to this methods has no effect if the current subpath does not contain any elements.
    # 
    # \note After closing the subpath the current point is undefined!
    # 
    def closePath() -> None: pass

    ##
    # \brief Calculates the axis-aligned bounding box of the path.
    # 
    # \param bounds The Vis.Rectangle2D instance storing the calculated bounding box.
    # 
    def getBounds(bounds: Rectangle2D) -> None: pass

    ##
    # \brief Iterates over the stored path elements and calls the corresponding method of <em>conv</em> for each visited element.
    # 
    # \param conv An instance of a class implementing the Vis.Path2DConverter interface.
    # 
    def convert(conv: Path2DConverter) -> None: pass

    ##
    # \brief Creates an ellipse positioned at <em>(x, y)</em> with the specified width and height, and adds it to this path as a closed subpath.
    # 
    # \param x The x-coordinate of the ellipse center.
    # \param y The y-coordinate of the ellipse center.
    # \param width The width of the ellipse.
    # \param height The height of the ellipse.
    # 
    def addEllipse(x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief Creates an ellipse positioned at <em>pos</em> with the specified width and height, and adds it to this path as a closed subpath.
    # 
    # \param pos A 2D vector specifying the ellipse center.
    # \param width The width of the ellipse.
    # \param height The height of the ellipse.
    # 
    def addEllipse(pos: Math.Vector2D, width: float, height: float) -> None: pass

    ##
    # \brief Creates a rectangle positioned at <em>(x, y)</em> with the specified width and height, and adds it to this path as a closed subpath.
    # 
    # \param x The x-coordinate of the top-left corner.
    # \param y The y-coordinate of the top-left corner.
    # \param width The width of the rectangle.
    # \param height The height of the rectangle.
    # 
    def addRectangle(x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief Creates a rectangle positioned at <em>pos</em> with the specified width and height, and adds it to this path as a closed subpath.
    # 
    # \param pos A 2D vector specifying the top-left corner.
    # \param width The width of the rectangle.
    # \param height The height of the rectangle.
    # 
    def addRectangle(pos: Math.Vector2D, width: float, height: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += path</tt>.
    # \param path Specifies the second addend.
    # \return The updated \e %Path2D instance \a self.
    # 
    def __iadd__(path: Path2D) -> Path2D: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param path The <tt>Path2D</tt> instance to compare with.
    # 
    # \return <tt>True</tt> if this path is equal to <em>path</em>, and <tt>False</tt> otherwise.
    # 
    def __eq__(path: Path2D) -> bool: pass

    ##
    # \brief Non-equality comparison operator.
    # 
    # \param path The <tt>Path2D</tt> instance to compare with.
    # 
    # \return <tt>True</tt> if this path is not equal to <em>path</em>, and <tt>False</tt> otherwise.
    # 
    def __ne__(path: Path2D) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    objectID = property(getObjectID)

    empty = property(isEmpty)

    hasDrawingElem = property(hasDrawingElements)

    fillRule = property(getFillRule, setFillRule)
