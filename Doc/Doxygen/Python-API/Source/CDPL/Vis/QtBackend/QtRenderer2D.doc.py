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
    # \brief Pushes the current pen, brush, font, transformation and clip path onto an internal state stack.
    # 
    def saveState() -> None: pass

    ##
    # \brief Pops the topmost stack entry and restores the renderer to the saved state.
    # 
    def restoreState() -> None: pass

    ##
    # \brief Replaces the current transformation matrix by <em>xform</em>.
    # 
    # \param xform The new transformation matrix.
    # 
    def setTransform(xform: Math.Matrix3D) -> None: pass

    ##
    # \brief Right-multiplies the current transformation matrix by <em>xform</em>.
    # 
    # \param xform The transformation matrix to append.
    # 
    def transform(xform: Math.Matrix3D) -> None: pass

    ##
    # \brief Sets the pen used for drawing outlines and lines.
    # 
    # \param pen The new pen.
    # 
    def setPen(pen: Vis.Pen) -> None: pass

    ##
    # \brief Sets the brush used for filling shapes.
    # 
    # \param brush The new brush.
    # 
    def setBrush(brush: Vis.Brush) -> None: pass

    ##
    # \brief Sets the font used for rendering text.
    # 
    # \param font The new font.
    # 
    def setFont(font: Vis.Font) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    # \param width 
    # \param height 
    #
    def drawRectangle(x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief Draws the (filled) polygon defined by the vertex sequence <em>points</em>.
    # 
    # \param points The polygon's vertex sequence.
    # 
    def drawPolygon(points: Math.Vector2DArray) -> None: pass

    ##
    # \brief Draws a single line segment from <em>(x1, y1)</em> to <em>(x2, y2)</em>.
    # 
    # \param x1 The x-coordinate of the line's start point.
    # \param y1 The y-coordinate of the line's start point.
    # \param x2 The x-coordinate of the line's end point.
    # \param y2 The y-coordinate of the line's end point.
    # 
    def drawLine(x1: float, y1: float, x2: float, y2: float) -> None: pass

    ##
    # \brief Draws the open polyline defined by the vertex sequence <em>points</em>.
    # 
    # \param points The polyline's vertex sequence.
    # 
    def drawPolyline(points: Math.Vector2DArray) -> None: pass

    ##
    # \brief Draws the disjoint line segments defined by consecutive vertex pairs in <em>points</em>.
    # 
    # \param points The vertex sequence (size must be even).
    # 
    def drawLineSegments(points: Math.Vector2DArray) -> None: pass

    ##
    # \brief Draws a single point at <em>(x, y)</em>.
    # 
    # \param x The point's x-coordinate.
    # \param y The point's y-coordinate.
    # 
    def drawPoint(x: float, y: float) -> None: pass

    ##
    # \brief Draws an axis-aligned ellipse centered at <em>(x, y)</em> with the given <em>width</em> and <em>height</em>.
    # 
    # \param x The x-coordinate of the ellipse's center.
    # \param y The y-coordinate of the ellipse's center.
    # \param width The width of the ellipse.
    # \param height The height of the ellipse.
    # 
    def drawEllipse(x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief Draws the text <em>txt</em> with its baseline starting at <em>(x, y)</em>.
    # 
    # \param x The baseline x-coordinate.
    # \param y The baseline y-coordinate.
    # \param txt The text to draw.
    # 
    def drawText(x: float, y: float, txt: str) -> None: pass

    ##
    # \brief Draws (strokes and fills) the 2D path <em>path</em>.
    # 
    # \param path The path to draw.
    # 
    def drawPath(path: Vis.Path2D) -> None: pass

    ##
    # \brief Sets the renderer's active clipping region to <em>path</em>.
    # 
    # \param path The path defining the new clipping region.
    # 
    def setClipPath(path: Vis.Path2D) -> None: pass

    ##
    # \brief Disables any currently active clipping region.
    # 
    def clearClipPath() -> None: pass
