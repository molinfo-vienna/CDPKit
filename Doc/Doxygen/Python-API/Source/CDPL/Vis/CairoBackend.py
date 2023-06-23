#
# CairoBackend.py 
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
#


##
# \brief class CairoFontMetrics.
#
class CairoFontMetrics(CDPL.Vis.FontMetrics):

	def __init__(self, cairo_ctxt): pass

	def setFont(self, font): pass
		
	def getAscent(self): pass
	
	def getDescent(self): pass
	
	def getHeight(self): pass
	
	def getLeading(self): pass
	
	def getWidth(self, string): pass

	def getBounds(self, string, bounds): pass

##
# \brief class CairoRenderer2D.
#
class CairoRenderer2D(CDPL.Vis.Renderer2D):

	def __init__(self, cairo_ctxt): pass

	def saveState(self): pass

	def restoreState(self): pass

	def setTransform(self, xform): pass

	def transform(self, xform): pass

	def setPen(self, pen): pass

	def setBrush(self, brush): pass

	def setFont(self, font): pass

	def drawRectangle(self, x, y, width, height): pass

	def drawPolygon(self, points): pass

	def drawLine(self, x1, y1, x2, y2): pass

	def drawPolyline(self, points): pass

	def drawLineSegments(self, points): pass

	def drawPoint(self, x, y): pass

	def drawEllipse(self, x, y, width, height): pass

	def drawText(self, x, y, txt): pass
