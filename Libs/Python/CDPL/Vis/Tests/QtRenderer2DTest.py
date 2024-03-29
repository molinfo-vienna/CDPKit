## 
# QtRenderer2DTest.py 
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
import sys

from PyQt5.QtGui import QPainter
from PyQt5.QtGui import QImage
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication

from CDPL.Vis import Pen
from CDPL.Vis import Brush
from CDPL.Vis import Color
from CDPL.Vis import Font
from CDPL.Vis import PointArray2D
from CDPL.Vis import Path2D
from CDPL.Math import Vector2D
from CDPL.Math import vec
from CDPL.Math import Matrix3D
from CDPL.Math import DTranslationMatrix
from CDPL.Math import DScalingMatrix
    
from CDPL.Vis.QtBackend import QtRenderer2D


class TestCase(unittest.TestCase):

    def runTest(self):
        """Testing QtRenderer2D"""
    
        test_pens = [
            Pen(Color.BLACK, 0.0, Pen.NO_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN),
            Pen(Color.BLACK, 0.5, Pen.SOLID_LINE, Pen.ROUND_CAP, Pen.BEVEL_JOIN),
            Pen(Color.BLACK, 0.5, Pen.DASH_LINE, Pen.ROUND_CAP, Pen.ROUND_JOIN),
            Pen(Color.BLACK, 0.5, Pen.DOT_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN),
            Pen(Color.BLACK, 0.5, Pen.DASH_DOT_LINE, Pen.ROUND_CAP, Pen.BEVEL_JOIN),
            Pen(Color.BLACK, 0.5, Pen.DASH_DOT_DOT_LINE, Pen.ROUND_CAP, Pen.ROUND_JOIN),
            
            Pen(Color.RED, 1.0, Pen.NO_LINE, Pen.FLAT_CAP, Pen.BEVEL_JOIN),
            Pen(Color.RED, 1.0, Pen.SOLID_LINE, Pen.FLAT_CAP, Pen.ROUND_JOIN),
            Pen(Color.RED, 1.0, Pen.DASH_LINE, Pen.FLAT_CAP, Pen.MITER_JOIN),
            Pen(Color.RED, 1.0, Pen.DOT_LINE, Pen.FLAT_CAP, Pen.BEVEL_JOIN),
            Pen(Color.RED, 1.0, Pen.DASH_DOT_LINE, Pen.FLAT_CAP, Pen.ROUND_JOIN),
            Pen(Color.RED, 1.0, Pen.DASH_DOT_DOT_LINE, Pen.FLAT_CAP, Pen.MITER_JOIN),
            
            Pen(Color.GREEN, 1.5, Pen.NO_LINE, Pen.SQUARE_CAP, Pen.ROUND_JOIN),
            Pen(Color.GREEN, 1.5, Pen.SOLID_LINE, Pen.SQUARE_CAP, Pen.MITER_JOIN),
            Pen(Color.GREEN, 1.5, Pen.DASH_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN),
            Pen(Color.GREEN, 1.5, Pen.DOT_LINE, Pen.SQUARE_CAP, Pen.ROUND_JOIN),
            Pen(Color.GREEN, 1.5, Pen.DASH_DOT_LINE, Pen.SQUARE_CAP, Pen.MITER_JOIN),
            Pen(Color.GREEN, 1.5, Pen.DASH_DOT_DOT_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN),
            
            Pen(Color.BLUE, 2.0, Pen.NO_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN),
            Pen(Color.BLUE, 2.0, Pen.SOLID_LINE, Pen.ROUND_CAP, Pen.BEVEL_JOIN),
            Pen(Color.BLUE, 2.0, Pen.DASH_LINE, Pen.ROUND_CAP, Pen.ROUND_JOIN),
            Pen(Color.BLUE, 2.0, Pen.DOT_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN),
            Pen(Color.BLUE, 2.0, Pen.DASH_DOT_LINE, Pen.ROUND_CAP, Pen.BEVEL_JOIN),
            Pen(Color.BLUE, 2.0, Pen.DASH_DOT_DOT_LINE, Pen.ROUND_CAP, Pen.ROUND_JOIN),
        
            Pen(Color.MAGENTA, 3.0, Pen.NO_LINE, Pen.FLAT_CAP, Pen.BEVEL_JOIN),
            Pen(Color.MAGENTA, 3.0, Pen.SOLID_LINE, Pen.FLAT_CAP, Pen.ROUND_JOIN),
            Pen(Color.MAGENTA, 3.0, Pen.DASH_LINE, Pen.FLAT_CAP, Pen.MITER_JOIN),
            Pen(Color.MAGENTA, 3.0, Pen.DOT_LINE, Pen.FLAT_CAP, Pen.BEVEL_JOIN),
            Pen(Color.MAGENTA, 3.0, Pen.DASH_DOT_LINE, Pen.FLAT_CAP, Pen.ROUND_JOIN),
            Pen(Color.MAGENTA, 3.0, Pen.DASH_DOT_DOT_LINE, Pen.FLAT_CAP, Pen.MITER_JOIN),
            
            Pen(Color.CYAN, 5.0, Pen.NO_LINE, Pen.SQUARE_CAP, Pen.ROUND_JOIN),
            Pen(Color.CYAN, 5.0, Pen.SOLID_LINE, Pen.SQUARE_CAP, Pen.MITER_JOIN),
            Pen(Color.CYAN, 5.0, Pen.DASH_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN),
            Pen(Color.CYAN, 5.0, Pen.DOT_LINE, Pen.SQUARE_CAP, Pen.ROUND_JOIN),
            Pen(Color.CYAN, 5.0, Pen.DASH_DOT_LINE, Pen.SQUARE_CAP, Pen.MITER_JOIN),
            Pen(Color.CYAN, 5.0, Pen.DASH_DOT_DOT_LINE, Pen.SQUARE_CAP, Pen.BEVEL_JOIN),
            
            Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen.NO_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN),
            Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen.SOLID_LINE, Pen.ROUND_CAP, Pen.BEVEL_JOIN),
            Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen.DASH_LINE, Pen.ROUND_CAP, Pen.ROUND_JOIN),
            Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen.DOT_LINE, Pen.ROUND_CAP, Pen.MITER_JOIN),
            Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen.DASH_DOT_LINE, Pen.ROUND_CAP, Pen.BEVEL_JOIN),
            Pen(Color(1.0, 1.0, 0.0, 0.5), 10.0, Pen.DASH_DOT_DOT_LINE, Pen.ROUND_CAP, Pen.ROUND_JOIN)
        ]
    
        test_brushes = [
            Brush(Color.RED, Brush.SOLID_PATTERN),
            Brush(Color(1.0, 1.0, 1.0, 0.5), Brush.DENSE1_PATTERN),
            Brush(Color.BLUE, Brush.DENSE2_PATTERN),
            Brush(Color.YELLOW, Brush.DENSE3_PATTERN),
            Brush(Color.MAGENTA, Brush.DENSE4_PATTERN),
            Brush(Color.WHITE, Brush.DENSE5_PATTERN),
            Brush(Color.GREEN, Brush.DENSE6_PATTERN),
            Brush(Color.CYAN, Brush.DENSE7_PATTERN),
            Brush(Color.DARK_MAGENTA, Brush.H_PATTERN),
            Brush(Color.DARK_GREEN, Brush.V_PATTERN),
            Brush(Color.DARK_BLUE, Brush.CROSS_PATTERN),
            Brush(Color.DARK_YELLOW, Brush.LEFT_DIAG_PATTERN),
            Brush(Color.DARK_CYAN, Brush.RIGHT_DIAG_PATTERN),
            Brush(Color.DARK_RED, Brush.DIAG_CROSS_PATTERN),
            Brush(Color.BLACK, Brush.NO_PATTERN)
        ]
    
        points = PointArray2D()
    
        #-----
    
        app = QApplication(sys.argv)
    
        image1 = QImage(600, 500, QImage.Format_ARGB32)
        view1 = QPainter(image1)
    
        view1.fillRect(0, 0, 600, 500, Qt.gray)
    
        renderer1 = QtRenderer2D(view1)
    
        points.resize(5, Vector2D())
    
        y = 35.0
    
        for i in range(7):
            x = 60.0
    
            for j in range(6):
                renderer1.setPen(test_pens[i * 6 + j])
                renderer1.setBrush(test_brushes[(i * 6 + j) % 15])
    
                points[0][0] = -1.0 * 30.0
                points[0][1] = 1.0 * 30.0
    
                points[1][0] = 1.0 * 30.0
                points[1][1] = 1.0 * 30.0
    
                points[2][0] = 0.5 * 30.0
                points[2][1] = -1.0 * 30.0
                
                points[3][0] = -1.5 * 30.0
                points[3][1] = -0.5 * 30.0
    
                points[4][0] = -1.8 * 30.0
                points[4][1] = 0.5 * 30.0
    
                points.translate(vec(x, y))
    
                renderer1.drawPolygon(points)
                x += 100.0
                    
            y += 70.0
                    
        view1.end()
    
        self.assert_(image1.save('QtRenderer2DTest_1.png', 'PNG'))
    
        #-----
    
        image2 = QImage(310, 1300, QImage.Format_ARGB32)
        view2 = QPainter(image2)
    
        view2.fillRect(0, 0, 310, 1300, Qt.gray)
    
        renderer2 = QtRenderer2D(view2)
    
        points.resize(8, Vector2D())
    
        y = 140.0
    
        for i in range(7):
            for j in range(6):
                renderer2.setPen(test_pens[i * 6 + j])
    
                points[0][0] = -0.9 * 20.0 * j
                points[0][1] = 1.0 * 20.0 * j
    
                points[1][0] = 0.9 * 20.0 * j
                points[1][1] = 1.0 * 20.0 * j
    
                points[2][0] = 1.0 * 20.0 * j
                points[2][1] = 0.9 * 20.0 * j
                
                points[3][0] = 1.0 * 20.0 * j
                points[3][1] = -0.9 * 20.0 * j
    
                points[4][0] = 0.9 * 20.0 * j
                points[4][1] = -1.0 * 20.0 * j
                
                points[5][0] = -0.9 * 20.0 * j
                points[5][1] = -1.0 * 20.0 * j
    
                points[6][0] = -1.0 * 20.0 * j
                points[6][1] = -0.9 * 20.0 * j
                
                points[7][0] = -1.0 * 20.0 * j
                points[7][1] = 0.9 * 20.0 * j
    
                points.translate(vec(160.0, y))
    
                renderer2.drawLineSegments(points)

            y += 170.0
    
        view2.end()
    
        self.assert_(image2.save('QtRenderer2DTest_2.png', 'PNG'))
    
        #-----
    
        image3 = QImage(310, 1300, QImage.Format_ARGB32)
        view3 = QPainter(image3)
    
        view3.fillRect(0, 0, 310, 1300, Qt.gray)
    
        renderer3 = QtRenderer2D(view3)
    
        points.resize(5, Vector2D())
    
        y = 140.0
    
        for i in range(7):
            for j in range(6):
                renderer3.setPen(test_pens[i * 6 + j])
    
                points[0][0] = -1.0 * 20.0 * j
                points[0][1] = 1.0 * 20.0 * j
    
                points[1][0] = 1.0 * 20.0 * j
                points[1][1] = 1.0 * 20.0 * j
    
                points[2][0] = 0.5 * 20.0 * j
                points[2][1] = -1.0 * 20.0 * j
                
                points[3][0] = -1.5 * 20.0 * j
                points[3][1] = -0.5 * 20.0 * j
    
                points[4][0] = -1.8 * 20.0 * j
                points[4][1] = 0.5 * 20.0 * j
    
                points.translate(vec(195.0, y))
    
                renderer3.drawPolyline(points)

            y += 170.0
                
        view3.end()
    
        self.assert_(image3.save('QtRenderer2DTest_3.png', 'PNG'))
    
        #-----
    
        image4 = QImage(120, 150, QImage.Format_ARGB32)
        view4 = QPainter(image4)
    
        view4.fillRect(0, 0, 120, 150, Qt.gray)
    
        renderer4 = QtRenderer2D(view4)
    
        y = 5.0
        k = 0
        
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                renderer4.setPen(test_pens[k])
    
                renderer4.drawPoint(x, y)

                x += 20.0
                k += 1
                
            y += 20.0
                    
        view4.end()
    
        self.assert_(image4.save('QtRenderer2DTest_4.png', 'PNG'))
    
        #-----
    
        image5 = QImage(160, 900, QImage.Format_ARGB32)
        view5 = QPainter(image5)
    
        view5.fillRect(0, 0, 160, 900, Qt.gray)
    
        renderer5 = QtRenderer2D(view5)
    
        y = 5.0
    
        for i in range(6 * 7):
            renderer5.setPen(test_pens[i])
    
            renderer5.drawLine(10.0, y, 150.0, y)

            y += 20.0
                
        view5.end()
    
        self.assert_(image5.save('QtRenderer2DTest_5.png', 'PNG'))
    
        #-----
    
        image6 = QImage(680, 150, QImage.Format_ARGB32)
        view6 = QPainter(image6)
    
        view6.fillRect(0, 0, 780, 150, Qt.gray)
    
        renderer6 = QtRenderer2D(view6)
    
        renderer6.setPen(Color.GREEN)
        renderer6.setFont(Font())
    
        renderer6.drawText(10.0, 15.0, 'The Quick Brown Fox...')
        
        renderer6.setPen(Pen(Color.RED, Pen.NO_LINE))
        renderer6.setFont(Font('Times', 15.0))
    
        renderer6.drawText(20.0, 35.0, 'The Quick Brown Fox...')
    
        f = Font('Helvetica', 20.0)
    
        f.setItalic(True)
        f.setStrikedOut(True)
        
        renderer6.setPen(Pen(Color.BLUE))
        renderer6.setFont(f)
    
        renderer6.drawText(30.0, 60.0, 'The Quick Brown Fox...')
    
        f.setItalic(False)
        f.setBold(True)
        f.setStrikedOut(False)
        f.setUnderlined(True)
        f.setFamily('Courier')
        f.setSize(40.0)
    
        renderer6.setPen(Color(1.0, 1.0, 0.0, 0.7))
        renderer6.setFont(f)
    
        renderer6.drawText(40.0, 90.0, 'The Quick Brown Fox...')
    
        f.setItalic(True)
        f.setUnderlined(False)
        f.setOverlined(True)
        f.setFamily('Serif')
        f.setSize(60.0)
    
        renderer6.setPen(Color(0.0, 1.0, 0.0, 0.8))
        renderer6.setFont(f)
    
        renderer6.drawText(50.0, 130.0, 'The Quick Brown Fox...')
    
        view6.end()
    
        self.assert_(image6.save('QtRenderer2DTest_6.png', 'PNG'))
    
        #-----
    
        image7 = QImage(200, 200, QImage.Format_ARGB32)
        view7 = QPainter(image7)
    
        view7.fillRect(0, 0, 200, 200, Qt.gray)
    
        renderer7 = QtRenderer2D(view7)
    
        renderer7.setPen(Pen(Color.RED, 2.0))
        renderer7.setBrush(Brush(Color.BLUE, Brush.CROSS_PATTERN))
    
        points[0][0] = -20.0
        points[0][1] = 20.0
    
        points[1][0] = 20.0
        points[1][1] = 20.0
    
        points[2][0] = 10.0
        points[2][1] = -20.0
    
        points[3][0] = -30.0
        points[3][1] = -10.0
    
        points[4][0] = -36.0
        points[4][1] = 10.0
    
        renderer7.transform(DTranslationMatrix(3, 100.0))
        renderer7.transform(DTranslationMatrix(3, 0.0, 100.0))
    
        renderer7.saveState()
    
        renderer7.transform(DTranslationMatrix(3, -100.0))
        renderer7.transform(DTranslationMatrix(3, 0.0, -100.0))
    
        renderer7.transform(DTranslationMatrix(3, 70.0))
        renderer7.transform(DTranslationMatrix(3, 0.0, 50.0))
    
        renderer7.transform(DScalingMatrix(3, 1.5))
        renderer7.transform(DScalingMatrix(3, 1.0, 0.8))
    
        renderer7.setPen(Pen(Color.GREEN, 5.0))
        renderer7.setBrush(Brush(Color.YELLOW, Brush.DENSE3_PATTERN))
    
        renderer7.drawPolygon(points)
    
        renderer7.restoreState()
    
        renderer7.drawPolygon(points)
    
        view7.end()
    
        self.assert_(image7.save('QtRenderer2DTest_7.png', 'PNG'))
    
        #-----
    
        image8 = QImage(600, 480, QImage.Format_ARGB32)
        view8 = QPainter(image8)
    
        view8.fillRect(0, 0, 600, 480, Qt.gray)
    
        renderer8 = QtRenderer2D(view8)
    
        y = 15.0
    
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                renderer8.setPen(test_pens[i * 6 + j])
                renderer8.setBrush(test_brushes[(i * 6 + j) % 15])
    
                renderer8.drawRectangle(x, y, 70.0, 45.0)

                x += 100.0
                    
            y += 65.0
                    
        view8.end()
    
        self.assert_(image8.save('QtRenderer2DTest_8.png', 'PNG'))
    
        #-----
    
        image9 = QImage(600, 480, QImage.Format_ARGB32)
        view9 = QPainter(image9)
    
        view9.fillRect(0, 0, 600, 480, Qt.gray)
    
        renderer9 = QtRenderer2D(view9)
        path = Path2D()
    
        path.moveTo(0, -20)
        path.lineTo(50, -20)
        path.arcTo(50, 0, 20, 20, -90, 180)
        path.lineTo(0, 20)
        path.arcTo(0, 0, 15, 20, 90, -180)
        path.closePath()
        
        y = 45.0
    
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                renderer9.setPen(test_pens[i * 6 + j])
                renderer9.setBrush(test_brushes[(i * 6 + j) % 15])
    
                renderer9.saveState()
                renderer9.setTransform(Matrix3D([ [ 1.0, 0.0, x ], [ 0.0, 1.0, y ], [ 0.0, 0.0, 1.0 ] ]))
                renderer9.drawPath(path)
                renderer9.restoreState()

                x += 100.0

            y += 65.0

        view9.end()
                    
        self.assert_(image9.save('QtRenderer2DTest_9.png', 'PNG'))
    
        #-----
    
        image10 = QImage(600, 480, QImage.Format_ARGB32)
        view10 = QPainter(image10)
    
        view10.fillRect(0, 0, 600, 480, Qt.gray)
    
        renderer10 = QtRenderer2D(view10)
        clp_path = Path2D()
    
        clp_path.moveTo(450, 240)
        clp_path.arcTo(300, 240, 150, 90, 0, 360)
        clp_path.closePath()
    
        renderer10.setPen(Color.BLACK)
        renderer10.drawPath(clp_path)
        
        y = 45.0
    
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                if ((i * 7 + j) % 2 == 0):
                    renderer10.setClipPath(clp_path)
                else:
                    renderer10.clearClipPath()
                
                renderer10.setPen(test_pens[i * 6 + j])
                renderer10.setBrush(test_brushes[(i * 6 + j) % 15])
    
                renderer10.saveState()
                renderer10.setTransform(Matrix3D([ [ 1.0, 0.0, x ], [ 0.0, 1.0, y ], [ 0.0, 0.0, 1.0 ] ]))
                renderer10.drawPath(path)
                renderer10.restoreState()

                x += 100.0
                    
            y += 65.0

        view10.end()

        self.assert_(image10.save('QtRenderer2DTest_10.png', 'PNG'))
