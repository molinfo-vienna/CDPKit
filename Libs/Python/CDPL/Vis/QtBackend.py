## 
# QtBackend.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
##


from __future__ import absolute_import

import PyQt5.QtCore as QtCore
import PyQt5.QtGui as QtGui

import CDPL.Vis as Vis


__all__ = [ 'QtFontMetrics', 'QtRenderer2D', 'QtObjectFactory' ]


lineStyleMap = { Vis.Pen.DASH_LINE         : QtCore.Qt.DashLine,
                 Vis.Pen.DOT_LINE          : QtCore.Qt.DotLine,
                 Vis.Pen.DASH_DOT_LINE     : QtCore.Qt.DashDotLine,
                 Vis.Pen.DASH_DOT_DOT_LINE : QtCore.Qt.DashDotDotLine,
                 Vis.Pen.SOLID_LINE        : QtCore.Qt.SolidLine,
                 Vis.Pen.NO_LINE           : QtCore.Qt.NoPen }

capStyleMap = { Vis.Pen.FLAT_CAP   : QtCore.Qt.FlatCap,
                Vis.Pen.SQUARE_CAP : QtCore.Qt.SquareCap,
                Vis.Pen.ROUND_CAP  : QtCore.Qt.RoundCap } 

joinStyleMap = { Vis.Pen.MITER_JOIN : QtCore.Qt.MiterJoin,
                 Vis.Pen.BEVEL_JOIN : QtCore.Qt.BevelJoin,
                 Vis.Pen.ROUND_JOIN : QtCore.Qt.RoundJoin }

brushStyleMap = { Vis.Brush.SOLID_PATTERN      : QtCore.Qt.SolidPattern, 
                  Vis.Brush.DENSE1_PATTERN     : QtCore.Qt.Dense1Pattern, 
                  Vis.Brush.DENSE2_PATTERN     : QtCore.Qt.Dense2Pattern, 
                  Vis.Brush.DENSE3_PATTERN     : QtCore.Qt.Dense3Pattern, 
                  Vis.Brush.DENSE4_PATTERN     : QtCore.Qt.Dense4Pattern,
                  Vis.Brush.DENSE5_PATTERN     : QtCore.Qt.Dense5Pattern,
                  Vis.Brush.DENSE6_PATTERN     : QtCore.Qt.Dense6Pattern,
                  Vis.Brush.DENSE7_PATTERN     : QtCore.Qt.Dense7Pattern,
                  Vis.Brush.H_PATTERN          : QtCore.Qt.HorPattern,
                  Vis.Brush.V_PATTERN          : QtCore.Qt.VerPattern,
                  Vis.Brush.CROSS_PATTERN      : QtCore.Qt.CrossPattern,
                  Vis.Brush.LEFT_DIAG_PATTERN  : QtCore.Qt.BDiagPattern,
                  Vis.Brush.RIGHT_DIAG_PATTERN : QtCore.Qt.FDiagPattern,
                  Vis.Brush.DIAG_CROSS_PATTERN : QtCore.Qt.DiagCrossPattern,
                  Vis.Brush.NO_PATTERN         : QtCore.Qt.NoBrush }

class ToQPainterPathConverter(Vis.Path2DConverter):

    def __init__(self, path, qt_path):
        Vis.Path2DConverter.__init__(self)
        self._qPainterPath = qt_path
        
        if qt_path.elementCount() > 0:
            QtGui.QPainterPath().swap(qt_path)

        if path.getFillRule() == Vis.Path2D.WINDING:
            fill_rule = QtCore.Qt.WindingFill
        else:
            fill_rule = QtCore.Qt.OddEvenFill
            
        qt_path.setFillRule(fill_rule)
        path.convert(self)

    def moveTo(self, x, y):
        self._qPainterPath.moveTo(x, y)

    def arcTo(self, cx, cy, rx, ry, start_ang, sweep):
        self._qPainterPath.arcTo(cx - rx, cy - ry, 2.0 * rx, 2.0 * ry, -start_ang, -sweep)

    def lineTo(self, x, y):
        self._qPainterPath.lineTo(x, y)

    def closePath(self):
        self._qPainterPath.closeSubpath()


class QtObjectFactory(object):

    def createQFont(font):
        "createQFont(Vis.Font font) -> PyQt5.QtGui.QFont :"
        if isinstance(font, str):
            font = Vis.Font(font)
        
        qt_font = QtGui.QFont(font.family)

        if (font.size <= 1.0):
            qt_font.setPointSizeF(1.0)
        else:
            qt_font.setPointSizeF(font.size)

        qt_font.setBold(font.bold)
        qt_font.setItalic(font.italic)
        qt_font.setUnderline(font.underlined)
        qt_font.setOverline(font.overlined)
        qt_font.setStrikeOut(font.strikedOut)
        qt_font.setFixedPitch(font.fixedPitch)

        return qt_font

    def createQColor(color):
        "createQColor(Vis.Color color) -> PyQt5.QtGui.QColor :"
        qt_color = QtGui.QColor()
        
        qt_color.setRedF(color.red)
        qt_color.setGreenF(color.green)
        qt_color.setBlueF(color.blue)
        qt_color.setAlphaF(color.alpha)

        return qt_color

    def createQPen(pen):
        "createQPen(Vis.Pen pen) -> PyQt5.QtGui.QPen :"
        if isinstance(pen, Vis.Color):
            pen = Vis.Pen(pen)
        
        try:
            pen_style = lineStyleMap[pen.lineStyle]
        except KeyError:
            pen_style = QtCore.QtGui.SolidLine

        try:
            cap_style = capStyleMap[pen.capStyle]
        except KeyError:
            cap_style = QtCore.QtGui.RoundCap

        try:
            join_style = joinStyleMap[pen.joinStyle]
        except KeyError:
            join_style = QtCore.QtGui.RoundJoin

        qt_pen = QtGui.QPen(QtObjectFactory.createQColor(pen.color))

        qt_pen.setStyle(pen_style)
        qt_pen.setCapStyle(cap_style)
        qt_pen.setJoinStyle(join_style)
        qt_pen.setWidthF(pen.width)

        return qt_pen

    def createQBrush(brush):
        "createQBrush(Vis.Brush brush) -> PyQt5.QtGui.QBrush :"
        if isinstance(brush, Vis.Color):
            brush = Vis.Brush(brush)
            
        try:
            brush_style = brushStyleMap[brush.style]
        except KeyError:
            brush_style = QtCore.QtGui.NoBrush

        return QtGui.QBrush(QtObjectFactory.createQColor(brush.color), brush_style)

    def createQPainterPath(path, qt_path):
        "createQPainterPath(Vis.Path2D path, PyQt5.QtGui.QPainterPath qt_path) -> PyQt5.QtGui.QPainterPath :"
        ToQPainterPathConverter(path, qt_path)

        return qt_path
    
    createQFont        = staticmethod(createQFont)
    createQColor       = staticmethod(createQColor)
    createQPen         = staticmethod(createQPen)
    createQBrush       = staticmethod(createQBrush)
    createQPainterPath = staticmethod(createQPainterPath)


class QtFontMetrics(Vis.FontMetrics):

    def __init__(self, paint_dev = None):
        "__init__(QtFontMetrics self, PyQt5.QtGui.QPaintDevice paint_dev) -> None :"
        Vis.FontMetrics.__init__(self)

        self._qPaintDevice = paint_dev
        self._qFontMetrics = QtGui.QFontMetricsF(QtGui.QFont(), paint_dev)

    def setFont(self, font):
        "setFont(QtFontMetrics self, Vis.Font font) -> None :"
        self._qFontMetrics = QtGui.QFontMetricsF(QtObjectFactory.createQFont(font), self._qPaintDevice)
            
    def getAscent(self):
        "getAscent(QtFontMetrics self) -> float :"
        return self._qFontMetrics.ascent()
    
    def getDescent(self):
        "getDescent(QtFontMetrics self) -> float :"
        return self._qFontMetrics.descent()
    
    def getHeight(self):
        "getHeight(QtFontMetrics self) -> float :"
        return self._qFontMetrics.height()
    
    def getLeading(self):
        "getLeading(QtFontMetrics self) -> float :"
        return self._qFontMetrics.leading()
    
    def getWidth(self, string):
        "getWidth(QtFontMetrics self) -> float :"
        return self._qFontMetrics.width(string)

    def getBounds(self, string, bounds):
        "getBounds(QtFontMetrics self, str string, Vis.Rectangle2D bounds) -> float :"
        if len(string) == 1:
            if string.isspace():
                bounds.setBounds(0.0, 0.0, self._qFontMetrics.width(string), 0.0)
                return

            ch_bounds = self._qFontMetrics.boundingRectChar(string)
            bounds.setBounds(ch_bounds.left(), ch_bounds.top(), ch_bounds.right(), ch_bounds.bottom())            
            return

        str_bounds = self._qFontMetrics.boundingRect(string)
            
        bounds.setMin(str_bounds.left(), 0.0);
        bounds.setMax(str_bounds.right(), 0.0);

        for c in string:
            str_bounds = self._qFontMetrics.boundingRectChar(c)

            bounds.addPoint(bounds.getMin()[0], str_bounds.top());
            bounds.addPoint(bounds.getMax()[0], str_bounds.bottom());

        if not string:
            return

        if string[-1].isspace():
            bounds.addPoint(self._qFontMetrics.width(string), 0.0)

        if string.isspace():
            bounds.addPoint(0.0, 0.0)


class QtRenderer2D(Vis.Renderer2D):

    def __init__(self, painter):
        "__init__(QtRenderer2D self, PyQt5.QtGui.QPainter painter) -> None :"
        Vis.Renderer2D.__init__(self)
        self._qPainter = painter
        self._qPainterPath = None
        self._qPolygon = None
        
    def saveState(self):
        "saveState(QtRenderer2D self) -> None :"
        self._qPainter.save()
    
    def restoreState(self):
        "restoreState(QtRenderer2D self) -> None :"
        self._qPainter.restore()
    
    def setTransform(self, xform):
        "setTransform(QtRenderer2D self, Math.Matrix3D xform) -> None :"
        self._qPainter.setWorldTransform(QtGui.QTransform(xform(0, 0), xform(1, 0), xform(2, 0), 
                                                           xform(0, 1), xform(1, 1), xform(2, 1), 
                                                           xform(0, 2), xform(1, 2), xform(2, 2)), False)
    
    def transform(self, xform):
        "transform(QtRenderer2D self, Math.Matrix3D xform) -> None :"
        self._qPainter.setWorldTransform(QtGui.QTransform(xform(0, 0), xform(1, 0), xform(2, 0), 
                                                           xform(0, 1), xform(1, 1), xform(2, 1), 
                                                           xform(0, 2), xform(1, 2), xform(2, 2)), True)

    def setPen(self, pen):
        "setPen(QtRenderer2D self, Vis.Pen pen) -> None :"
        self._qPainter.setPen(QtObjectFactory.createQPen(pen))
    
    def setBrush(self, brush):
        "setBrush(QtRenderer2D self, Vis.Brush brush) -> None :"
        self._qPainter.setBrush(QtObjectFactory.createQBrush(brush))
    
    def setFont(self, font):
        "setFont(QtRenderer2D self, Vis.Font font) -> None :"
        self._qPainter.setFont(QtObjectFactory.createQFont(font))
    
    def drawRectangle(self, x, y, width, height):
        "drawRectangle(QtRenderer2D self, float x, float y, float width, float height) -> None :"
        self._qPainter.drawRect(QtCore.QRectF(x, y, width, height))
    
    def drawPolygon(self, points):
        "drawPolygon(QtRenderer2D self, Math.Vector2DArray points) -> None :"
        self._qPainter.drawPolygon(self._convertToQPolygon(points))
            
    def drawLine(self, x1, y1, x2, y2):
        "drawLine(QtRenderer2D self, float x1, float y1, float x2, float y2) -> None :"
        self._qPainter.drawLine(QtCore.QPointF(x1, y1), QtCore.QPointF(x2, y2))
    
    def drawPolyline(self, points):
        "drawPolyline(QtRenderer2D self, Math.Vector2DArray points) -> None :"
        self._qPainter.drawPolyline(self._convertToQPolygon(points))
    
    def drawLineSegments(self, points):
        "drawLineSegments(QtRenderer2D self, Math.Vector2DArray points) -> None :"
        for i in range(0, len(points), 2):
            point1 = points[i]
            point2 = points[i + 1]
            
            self._qPainter.drawLine(point1[0], point1[1], point2[0], point2[1])
    
    def drawPoint(self, x, y):
        "drawPoint(QtRenderer2D self, float x, float y) -> None :"
        self._qPainter.drawPoint(QtCore.QPointF(x, y))
        
    def drawEllipse(self, x, y, width, height):
        "drawEllipse(QtRenderer2D self, float x, float y, float width, float height) -> None :"
        self._qPainter.drawEllipse(QtCore.QPointF(x, y), width * 0.5, height * 0.5)

    def drawText(self, x, y, txt):
        "drawText(QtRenderer2D self, float x, float y, str txt) -> None :"
        self._qPainter.drawText(QtCore.QPointF(x, y), txt)

    def drawPath(self, path):
        "drawPath(QtRenderer2D self, Vis.Path2D path) -> None :"
        if path.isEmpty():
            return
        
        if self._qPainterPath == None:
            self._qPainterPath = QtGui.QPainterPath()

        self._qPainter.drawPath(QtObjectFactory.createQPainterPath(path, self._qPainterPath))

    def setClipPath(self, path):
        "setClipPath(QtRenderer2D self, Vis.Path2D path) -> None :"
        if path.isEmpty():
            return

        if self._qPainterPath == None:
            self._qPainterPath = QtGui.QPainterPath()
            
        self._qPainter.setClipPath(QtObjectFactory.createQPainterPath(path, self._qPainterPath))
        
    def clearClipPath(self):
        "clearClipPath(QtRenderer2D self) -> None :"
        self._qPainter.setClipping(False)

    def _convertToQPolygon(self, points):
        if self._qPolygon == None:
            self._qPolygon = QtGui.QPolygonF()

        self._qPolygon.clear()

        for point in points:
            self._qPolygon.append(QtCore.QPointF(point[0], point[1]))

        return self._qPolygon
