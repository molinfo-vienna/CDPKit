## 
# QtObjectFactoryTest.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##


import unittest

from PyQt5.QtGui import QBrush
from PyQt5.QtGui import QPen
from PyQt5.QtGui import QColor
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt

from CDPL.Vis import Pen
from CDPL.Vis import Brush
from CDPL.Vis import Font
from CDPL.Vis import Color

from CDPL.Vis.QtBackend import QtObjectFactory


class TestCase(unittest.TestCase):
    
    def compareColors(self, lhs, rhs):
        self.assertAlmostEqual(lhs.redF(), rhs.redF(), 2)
        self.assertAlmostEqual(lhs.greenF(), rhs.greenF(), 2)
        self.assertAlmostEqual(lhs.blueF(), rhs.blueF(), 2)
        self.assertAlmostEqual(lhs.alphaF(), rhs.alphaF(), 2)
    
    def comparePens(self, lhs, rhs):
        self.compareColors(lhs.color(), rhs.color())
    
        self.assertAlmostEqual(lhs.widthF(), rhs.widthF(), 2)
        self.assert_(lhs.capStyle() == rhs.capStyle())
        self.assert_(lhs.joinStyle() == rhs.joinStyle())
        self.assert_(lhs.style() == rhs.style())
    
    def compareBrushes(self, lhs, rhs):
        self.compareColors(lhs.color(), rhs.color())
    
        self.assert_(lhs.style() == rhs.style())
    
    def compareFonts(self, lhs, rhs):
        self.assert_(lhs.family() == rhs.family())
        self.assert_(lhs.pointSizeF() == rhs.pointSizeF())
        self.assert_(lhs.bold() == rhs.bold())
        self.assert_(lhs.italic() == rhs.italic())
        self.assert_(lhs.underline() == rhs.underline())
        self.assert_(lhs.overline() == rhs.overline())
        self.assert_(lhs.strikeOut() == rhs.strikeOut())
        self.assert_(lhs.fixedPitch() == rhs.fixedPitch())
    
    def runTest(self):
        """Testing QtObjectFactory"""
    
        self.compareColors(QColor(0, 0, 0, 255), QtObjectFactory.createQColor(Color.BLACK))
        self.compareColors(QColor(255, 0, 0), QtObjectFactory.createQColor(Color.RED))
        self.compareColors(QColor(0, 255, 0), QtObjectFactory.createQColor(Color.GREEN))
        self.compareColors(QColor(0, 0, 255, 255), QtObjectFactory.createQColor(Color.BLUE))
        self.compareColors(QColor(255, 255, 255, 255), QtObjectFactory.createQColor(Color.WHITE))
    
        self.compareColors(QColor(25, 51, 153, 255), QtObjectFactory.createQColor(Color(25.0 / 255.0, 51.3 / 255.0, 152.9 / 255.0)))
        self.compareColors(QColor(25, 51, 153, 0), QtObjectFactory.createQColor(Color(25.0 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 0.0)))
        self.compareColors(QColor(25, 51, 153, 150), QtObjectFactory.createQColor(Color(25.1 / 255.0, 51.2 / 255.0, 153.0 / 255.0, 150.0 / 255.0)))
        self.compareColors(QColor(25, 51, 153, 255), QtObjectFactory.createQColor(Color(25.1 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 1.0)))
        self.compareColors(QColor(25, 51, 153, 255), QtObjectFactory.createQColor(Color(25.2 / 255.0, 51.0 / 255.0, 153.0 / 255.0, 2.0)))
        self.compareColors(QColor(25, 51, 153, 0), QtObjectFactory.createQColor(Color(25.2 / 255.0, 51.1 / 255.0, 153.0 / 255.0, -1.2)))
    
        #-----
    
        self.compareBrushes(QBrush(), QtObjectFactory.createQBrush(Brush(Color.BLACK, Brush.NO_PATTERN)))
        self.compareBrushes(QBrush(Qt.red), QtObjectFactory.createQBrush(Brush(Color.RED, Brush.SOLID_PATTERN)))
        self.compareBrushes(QBrush(Qt.Dense1Pattern), QtObjectFactory.createQBrush(Brush(Color.BLACK, Brush.DENSE1_PATTERN)))
        self.compareBrushes(QBrush(Qt.green, Qt.CrossPattern), QtObjectFactory.createQBrush(Brush(Color.GREEN, Brush.CROSS_PATTERN)))
    
        #-----
    
        self.comparePens(QPen(), QtObjectFactory.createQPen(Pen(Color.BLACK, 1.0, Pen.SOLID_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN)))
        self.comparePens(QPen(Qt.DotLine), QtObjectFactory.createQPen(Pen(Color.BLACK, 1.0, Pen.DOT_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN)))
        self.comparePens(QPen(Qt.red), QtObjectFactory.createQPen(Pen(Color.RED, 1.0, Pen.SOLID_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN)))
        self.comparePens(QPen(Qt.green, 2), QtObjectFactory.createQPen(Pen(Color.GREEN, 2.0, Pen.SOLID_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN)))
        self.comparePens(QPen(Qt.blue, 3, Qt.DashDotLine), QtObjectFactory.createQPen(Pen(Color.BLUE, 3.0, Pen.DASH_DOT_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN)))
        self.comparePens(QPen(Qt.yellow, 1, Qt.DashLine, Qt.RoundCap, Qt.MiterJoin), QtObjectFactory.createQPen(Pen(Color.YELLOW, 1.0, Pen.DASH_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN)))
    
        #-----
    
        self.compareFonts(QFont('', 12), QtObjectFactory.createQFont(Font()))
    
        font = Font('Times', 13.0)
        qfont = QFont('Times', 13)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setBold(True)
        qfont.setBold(True)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setItalic(True)
        qfont.setItalic(True)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setUnderlined(True)
        qfont.setUnderline(True)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setOverlined(True)
        qfont.setOverline(True)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setStrikedOut(True)
        qfont.setStrikeOut(True)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setFixedPitch(True)
        qfont.setFixedPitch(True)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setFamily('Arial')
        qfont.setFamily('Arial')
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
        font.setSize(11.5)
        qfont.setPointSizeF(11.5)
    
        self.compareFonts(qfont, QtObjectFactory.createQFont(font))
    
