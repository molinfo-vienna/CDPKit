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
# \brief Implements the Renderer2D interface on top of the <em>Qt Toolkit</em>.
# 
# <tt>QtRenderer2D</tt> is implemented by forwarding the drawing operations to a provided <tt>QPainter</tt> instance which has been created for the desired output device (screen, printer, off-screen image, ...). For more information about <tt>QPainter</tt> and the <em>Qt Toolkit</em> see [\ref QTDOC].
# 
class QtRenderer2D(Vis.Renderer2D):

    ##
    # \brief Constructs a renderer object which uses the <tt>QPainter</tt> instance <em>painter</em> for its drawing operations.
    # 
    # \param painter The wrapped <tt>QPainter</tt> instance.
    # 
    def __init__(painter: PyQt5.QtGui.QPainter) -> None: pass

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
    def setPen(pen: Vis.Pen) -> None: pass

    ##
    # \brief Sets the brush to be used in subsequent drawing operations.
    # 
    # \param brush The new brush for subsequent drawing operations.
    # 
    # \see Vis.Brush
    # 
    def setBrush(brush: Vis.Brush) -> None: pass

    ##
    # \brief Sets the font to be used in subsequent text drawing operations.
    # 
    # \param font The new font used in subsequent text drawing operations.
    # 
    # \see Vis.Font
    # 
    def setFont(font: Vis.Font) -> None: pass

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
