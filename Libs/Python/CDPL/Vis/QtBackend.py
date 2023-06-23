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

import CDPL.Vis


__all__ = [ 'QtFontMetrics', 'QtRenderer2D', 'QtObjectFactory' ]


lineStyleMap = { CDPL.Vis.Pen.DASH_LINE         : QtCore.Qt.DashLine,
				 CDPL.Vis.Pen.DOT_LINE          : QtCore.Qt.DotLine,
				 CDPL.Vis.Pen.DASH_DOT_LINE     : QtCore.Qt.DashDotLine,
				 CDPL.Vis.Pen.DASH_DOT_DOT_LINE : QtCore.Qt.DashDotDotLine,
				 CDPL.Vis.Pen.SOLID_LINE        : QtCore.Qt.SolidLine,
				 CDPL.Vis.Pen.NO_LINE           : QtCore.Qt.NoPen }

capStyleMap = { CDPL.Vis.Pen.FLAT_CAP   : QtCore.Qt.FlatCap,
				CDPL.Vis.Pen.SQUARE_CAP : QtCore.Qt.SquareCap,
				CDPL.Vis.Pen.ROUND_CAP  : QtCore.Qt.RoundCap } 

joinStyleMap = { CDPL.Vis.Pen.MITER_JOIN : QtCore.Qt.MiterJoin,
				 CDPL.Vis.Pen.BEVEL_JOIN : QtCore.Qt.BevelJoin,
				 CDPL.Vis.Pen.ROUND_JOIN : QtCore.Qt.RoundJoin }

brushStyleMap = { CDPL.Vis.Brush.SOLID_PATTERN      : QtCore.Qt.SolidPattern, 
				  CDPL.Vis.Brush.DENSE1_PATTERN     : QtCore.Qt.Dense1Pattern, 
				  CDPL.Vis.Brush.DENSE2_PATTERN     : QtCore.Qt.Dense2Pattern, 
				  CDPL.Vis.Brush.DENSE3_PATTERN     : QtCore.Qt.Dense3Pattern, 
				  CDPL.Vis.Brush.DENSE4_PATTERN     : QtCore.Qt.Dense4Pattern,
				  CDPL.Vis.Brush.DENSE5_PATTERN     : QtCore.Qt.Dense5Pattern,
				  CDPL.Vis.Brush.DENSE6_PATTERN     : QtCore.Qt.Dense6Pattern,
				  CDPL.Vis.Brush.DENSE7_PATTERN     : QtCore.Qt.Dense7Pattern,
				  CDPL.Vis.Brush.H_PATTERN          : QtCore.Qt.HorPattern,
				  CDPL.Vis.Brush.V_PATTERN          : QtCore.Qt.VerPattern,
				  CDPL.Vis.Brush.CROSS_PATTERN      : QtCore.Qt.CrossPattern,
				  CDPL.Vis.Brush.LEFT_DIAG_PATTERN  : QtCore.Qt.BDiagPattern,
				  CDPL.Vis.Brush.RIGHT_DIAG_PATTERN : QtCore.Qt.FDiagPattern,
				  CDPL.Vis.Brush.DIAG_CROSS_PATTERN : QtCore.Qt.DiagCrossPattern,
				  CDPL.Vis.Brush.NO_PATTERN         : QtCore.Qt.NoBrush }


class QtObjectFactory(object):

	def createQFont(font):
		"createQFont(Vis.Font font) -> PyQt4.QtGui.QFont :"
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
		"createQColor(Vis.Color color) -> PyQt4.QtGui.QColor :"
		qt_color = QtGui.QColor()
		
		qt_color.setRedF(color.red)
		qt_color.setGreenF(color.green)
		qt_color.setBlueF(color.blue)
		qt_color.setAlphaF(color.alpha)

		return qt_color

	def createQPen(pen):
		"createQPen(Vis.Pen pen) -> PyQt4.QtGui.QPen :"
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

		qt_pen = QtGui.QPen(QtObjectFactory.createQColor(pen.color));

		qt_pen.setStyle(pen_style)
		qt_pen.setCapStyle(cap_style)
		qt_pen.setJoinStyle(join_style)
		qt_pen.setWidthF(pen.width)

		return qt_pen

	def createQBrush(brush):
		"createQBrush(Vis.Brush brush) -> PyQt4.QtGui.QBrush :"
		try:
			brush_style = brushStyleMap[brush.style]
		except KeyError:
			brush_style = QtCore.QtGui.NoBrush

		return QtGui.QBrush(QtObjectFactory.createQColor(brush.color), brush_style)

	createQFont  = staticmethod(createQFont)
	createQColor = staticmethod(createQColor)
	createQPen   = staticmethod(createQPen)
	createQBrush = staticmethod(createQBrush);


class QtFontMetrics(CDPL.Vis.FontMetrics):

	def __init__(self, paint_dev = None):
		"__init__(QtFontMetrics self, PyQt4.QtGui.QPaintDevice paint_dev) -> None :"
		CDPL.Vis.FontMetrics.__init__(self)

		self.__qPaintDevice = paint_dev
		self.__qFontMetrics = QtGui.QFontMetricsF(QtGui.QFont(), paint_dev)

	def setFont(self, font):
		"setFont(QtFontMetrics self, Vis.Font font) -> None :"
		self.__qFontMetrics = QtGui.QFontMetricsF(QtObjectFactory.createQFont(font), self.__qPaintDevice)
			
	def getAscent(self):
		"getAscent(QtFontMetrics self) -> float :"
		return self.__qFontMetrics.ascent()
	
	def getDescent(self):
		"getDescent(QtFontMetrics self) -> float :"
		return self.__qFontMetrics.descent()
	
	def getHeight(self):
		"getHeight(QtFontMetrics self) -> float :"
		return self.__qFontMetrics.height()
	
	def getLeading(self):
		"getLeading(QtFontMetrics self) -> float :"
		return self.__qFontMetrics.leading()
	
	def getWidth(self, string):
		"getWidth(QtFontMetrics self) -> float :"
		return self.__qFontMetrics.width(string)

	def getBounds(self, string, bounds):
		"getBounds(QtFontMetrics self, str string, Vis.Rectangle2D bounds) -> float :"
		str_bounds = self.__qFontMetrics.boundingRect(string)

		bounds.setBounds(str_bounds.left(), str_bounds.top(), str_bounds.right(), str_bounds.bottom())

	
class QtRenderer2D(CDPL.Vis.Renderer2D):

	def __init__(self, painter):
		"__init__(QtRenderer2D self, cairo.Context cairo_ctxt) -> None :"
		CDPL.Vis.Renderer2D.__init__(self)
		self.__qPainter = painter

	def saveState(self):
		"saveState(QtRenderer2D self) -> None :"
		self.__qPainter.save()
	
	def restoreState(self):
		"restoreState(QtRenderer2D self) -> None :"
		self.__qPainter.restore()
	
	def setTransform(self, xform):
		"setTransform(QtRenderer2D self, Math.AffineTransform3D xform) -> None :"
		self.__qPainter.setWorldTransform(QtGui.QTransform(xform(0, 0), xform(1, 0), xform(2, 0), 
														   xform(0, 1), xform(1, 1), xform(2, 1), 
														   xform(0, 2), xform(1, 2), xform(2, 2)), False)
	
	def transform(self, xform):
		"transform(QtRenderer2D self, Math.AffineTransform3D xform) -> None :"
		self.__qPainter.setWorldTransform(QtGui.QTransform(xform(0, 0), xform(1, 0), xform(2, 0), 
														   xform(0, 1), xform(1, 1), xform(2, 1), 
														   xform(0, 2), xform(1, 2), xform(2, 2)), True)

	def setPen(self, pen):
		"setPen(QtRenderer2D self, Vis.Pen pen) -> None :"
		self.__qPainter.setPen(QtObjectFactory.createQPen(pen))
	
	def setBrush(self, brush):
		"setBrush(QtRenderer2D self, Vis.Brush brush) -> None :"
		self.__qPainter.setBrush(QtObjectFactory.createQBrush(brush))
	
	def setFont(self, font):
		"setFont(QtRenderer2D self, Vis.Font font) -> None :"
		self.__qPainter.setFont(QtObjectFactory.createQFont(font))
	
	def drawRectangle(self, x, y, width, height):
		"drawRectangle(QtRenderer2D self, float x, float y, float width, float height) -> None :"
		self.__qPainter.drawRect(QtGui.QRectF(x, y, width, height))
	
	def drawPolygon(self, points):
		"drawPolygon(QtRenderer2D self, Math.Vector2DArray points) -> None :"
		self.__qPainter.drawPolygon(self.__convertToQPolygon(points))
			
	def drawLine(self, x1, y1, x2, y2):
		"drawLine(QtRenderer2D self, float x1, float y1, float x2, float y2) -> None :"
		self.__qPainter.drawLine(QtGui.QPointF(x1, y1), QtGui.QPointF(x2, y2))
	
	def drawPolyline(self, points):
		"drawPolyline(QtRenderer2D self, Math.Vector2DArray points) -> None :"
		self.__qPainter.drawPolyline(self.__convertToQPolygon(points))
	
	def drawLineSegments(self, points):
		"drawLineSegments(QtRenderer2D self, Math.Vector2DArray points) -> None :"
		self.__qPainter.drawLines(self.__convertToQPolygon(points))
	
	def drawPoint(self, x, y):
		"drawPoint(QtRenderer2D self, float x, float y) -> None :"
		self.__qPainter.drawPoint(QtGui.QPointF(x, y))
        
	def drawEllipse(self, x, y, width, height):
		"drawEllipse(QtRenderer2D self, float x, float y, float width, float height) -> None :"
		self.__qPainter.drawEllipse(QtGui.QPointF(x, y), width * 0.5, height * 0.5)

	def drawText(self, x, y, txt):
		"drawText(QtRenderer2D self, float x, float y, str txt) -> None :"
		self.__qPainter.drawText(QtGui.QPointF(x, y), txt)

	def __convertToQPolygon(self, points):
		if not hasattr(self.__qPolygon):
			self.__qPolgyon = QtGui.QPolygonF()

		self.__qPolygon.clear()

		for point in points:
			self.__qPolygon.append(QtGui.QPointF(point[0], point[1]))

		return self.__qPolygon
