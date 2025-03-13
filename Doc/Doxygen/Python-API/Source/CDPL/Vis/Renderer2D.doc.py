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
# \brief An interface that provides methods for low level 2D drawing operations.
# 
# For the drawing of graphical primitives the following methods are provided:
#  - drawPoint() for drawing points
#  - drawLine() for drawing single line segments
#  - drawPolyline() for drawing connected line segments
#  - drawLineSegments() for drawing a set of disjoint line segments
#  - drawPolygon() for drawing polygons
#  - drawRectangle() for drawing axis aligned rectangles
#  - drawPath() for drawing arbitrary shapes
#  - and drawText() for drawing text
# 
# Drawing operations can be clipped to arbitrary shapes defined by a Vis.Path2D object. A new clip region is set by calling the method setClipPath() and disabled by calling clearClipPath().
# 
# Coordinates of points that define the geometry of graphical primitives are normally directly mapped to the coordinate system of the drawing device (e.g. an off-screen image buffer). This 1:1 mapping can be changed by applying affine transformations to the input coordinates.
# 
# Affine coordinate transformations can be specified by calling the methods:
#  - setTransform()
#  - and transform()
# 
# The former method replaces the current transformation matrix by a matrix that was provided as argument. When the latter method is called, the current matrix gets multiplied with the argument matrix to produce a combined affine transformation. To restore the 1:1 coordinate mapping, call setTransform() with a default constructed Math.AffineTransform3D instance.
# 
# The style and color of lines and shape outlines is defined by the current pen which is specified by setPen(). The current pen also defines the color of rendered text and the color and diameter of points. The fill pattern and fill color of shapes (rectangles and polygons) is defined by the current brush which is specified by setBrush().
# 
# The current state of the renderer (brush, pen, font and transformation matrix) may be saved by saveState() and restored by restoreState().
# 
class Renderer2D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Renderer2D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %Renderer2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Renderer2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Saves the current renderer state.
    # 
    # The method saves the current pen, brush, font and transformation matrix on an internal stack. The last saved state can be restored later on by a call to restoreState().
    # 
    # \see restoreState()
    # 
    def saveState() -> None: pass

    ##
    # \brief Restores the last renderer state saved by a call to saveState().
    # 
    # \see saveState()
    # 
    def restoreState() -> None: pass

    ##
    # \brief Sets the applied affine transformation matrix to <em>xform</em>.
    # 
    # \param xform The new affine transformation matrix.
    # 
    def setTransform(xform: Math.Matrix3D) -> None: pass

    ##
    # \brief Multiplies the current affine transformation matrix by <em>xform</em>.
    # 
    # \param xform The matrix by which the current affine transformation matrix is multiplied.
    # 
    def transform(xform: Math.Matrix3D) -> None: pass

    ##
    # \brief Sets the pen to be used in subsequent drawing operations.
    # 
    # \param pen The new pen for subsequent drawing operations.
    # 
    # \see Vis.Pen
    # 
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief Sets the brush to be used in subsequent drawing operations.
    # 
    # \param brush The new brush for subsequent drawing operations.
    # 
    # \see Vis.Brush
    # 
    def setBrush(brush: Brush) -> None: pass

    ##
    # \brief Sets the font to be used in subsequent text drawing operations.
    # 
    # \param font The new font used in subsequent text drawing operations.
    # 
    # \see Vis.Font
    # 
    def setFont(font: Font) -> None: pass

    ##
    # \brief Draws an axis aligned rectangle of the specified width and height whose upper-left corner is located at <em>(x, y)</em>.
    # 
    # The rectangle is filled as specified by the current brush and the outline will be drawn as specified by the current pen.
    # 
    # \param x The x-coordinate of the upper-left corner.
    # \param y The y-coordinate of the upper-left corner.
    # \param width The width of the rectangle.
    # \param height The height of the rectangle.
    # 
    # \see setPen(), setBrush()
    # 
    def drawRectangle(x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief Draws an ellipse with the given width and height around the center position <em>(x, y)</em>.
    # 
    # The ellipse is filled as specified by the current brush and the outline will be drawn as specified by the current pen.
    # 
    # \param x The x-coordinate of the center point.
    # \param y The y-coordinate of the center point.
    # \param width The width of the ellipse.
    # \param height The height of the ellipse.
    # 
    # \see setPen(), setBrush()
    # 
    def drawEllipse(x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief Draws the polygon defined by <em>points</em>.
    # 
    # For a given set of \f$ N \f$ corner points \f$ p_i \f$ with \f$ i = 1, 2, \ldots, N \f$, the polygon's \f$ N \f$ edges are given by \f$ (p_1, p_2), (p_2, p_3), \ldots, (p_N, p_0) \f$. The polygon is filled as specified by the current brush and the outline will be drawn as specified by the current pen.
    # 
    # \param points An array of points specifying the corners of the polygon.
    # 
    # \see setPen(), setBrush()
    # 
    def drawPolygon(points: Math.Vector2DArray) -> None: pass

    ##
    # \brief Draws a line segment from <em>(x1, y1)</em> to <em>(x2, y2)</em>.
    # 
    # The line style, color, cap style and line width is specified by the current pen.
    # 
    # \param x1 The x-coordinate of the starting point.
    # \param y1 The y-coordinate of the starting point.
    # \param x2 The x-coordinate of the end point.
    # \param y2 The y-coordinate of the end point.
    # 
    # \see setPen()
    # 
    def drawLine(x1: float, y1: float, x2: float, y2: float) -> None: pass

    ##
    # \brief Draws the polyline defined by <em>points</em>.
    # 
    # For a given set of \f$ N \f$ points \f$ p_i \f$ with \f$ i = 1, 2, \ldots, N \f$, \f$ N - 1 \f$ connected line segments \f$ (p_1, p_2), (p_2, p_3), \ldots, (p_{N - 1}, p_N) \f$ will be drawn. The line style, color, cap style, join style and line width is specified by the current pen.
    # 
    # \param points An array of points defining the polyline.
    # 
    # \see setPen()
    # 
    def drawPolyline(points: Math.Vector2DArray) -> None: pass

    ##
    # \brief Draws the sequence of disjoint line segments defined by <em>points</em>.
    # 
    # For a given set of \f$ 2N \f$ points \f$ p_i \f$ with \f$ i = 1, 2, \ldots, 2N \f$, \f$ N \f$ disjoint line segments \f$ (p_1, p_2), (p_3, p_4), \ldots, (p_{2N - 1}, p_2N) \f$ will be drawn. The line style, color, cap style and line width is specified by the current pen.
    # 
    # \param points An array of points defining the line segments.
    # 
    # \see setPen()
    # 
    def drawLineSegments(points: Math.Vector2DArray) -> None: pass

    ##
    # \brief Draws a point at the position <em>(x, y)</em>.
    # 
    # The diameter and color of the point is specified by the current pen.
    # 
    # \param x The x-coordinate of the point.
    # \param y The y-coordinate of the point.
    # 
    # \see setPen()
    # 
    def drawPoint(x: float, y: float) -> None: pass

    ##
    # \brief Draws the specified text at the position <em>(x, y)</em>.
    # 
    # The text color is specified by the current pen. The font has to be specified by setFont().
    # 
    # \param x The x-position of the drawn text.
    # \param y The y-position of the baseline.
    # \param txt The text to draw.
    # 
    # \see setPen(), setFont()
    # 
    def drawText(x: float, y: float, txt: str) -> None: pass

    ##
    # \brief Draws the given path.
    # 
    # The path is filled as specified by the current brush and the outline will be drawn as specified by the current pen.
    # 
    # \param path The path to draw.
    # 
    # \see setPen(), setBrush()
    # 
    def drawPath(path: Path2D) -> None: pass

    ##
    # \brief 
    # \param path 
    #
    def setClipPath(path: Path2D) -> None: pass

    ##
    # \brief Disables clipping.
    # 
    def clearClipPath() -> None: pass

    objectID = property(getObjectID)
