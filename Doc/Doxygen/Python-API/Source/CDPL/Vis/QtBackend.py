# 
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
#


##
# \brief class QtObjectFactory.
#
class QtObjectFactory:

    def createQFont(font):

    def createQColor(color):

    def createQPen(pen):

    def createQBrush(brush):

##
# \brief class QtFontMetrics.
#
class QtFontMetrics(CDPL.Vis.FontMetrics):

    def __init__(self, paint_dev = None):

    def setFont(self, font):
            
    def getAscent(self):
    
    def getDescent(self):
    
    def getHeight(self):
    
    def getLeading(self):
    
    def getWidth(self, string):

    def getBounds(self, string, bounds):

##
# \brief class QtRenderer2D.
#    
class QtRenderer2D(CDPL.Vis.Renderer2D):

    def __init__(self, painter):

    def saveState(self):
    
    def restoreState(self):
    
    def setTransform(self, xform):
    
    def transform(self, xform):

    def setPen(self, pen):
    
    def setBrush(self, brush):
    
    def setFont(self, font):
    
    def drawRectangle(self, x, y, width, height):
    
    def drawPolygon(self, points):
            
    def drawLine(self, x1, y1, x2, y2):
    
    def drawPolyline(self, points):
    
    def drawLineSegments(self, points):
    
    def drawPoint(self, x, y):
        
    def drawEllipse(self, x, y, width, height):

    def drawText(self, x, y, txt):
