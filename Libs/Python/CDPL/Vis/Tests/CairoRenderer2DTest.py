## 
# CairoRenderer2DTest.py 
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

import cairo

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
    
from CDPL.Vis.CairoBackend import CairoRenderer2D


class TestCase(unittest.TestCase):

    def runTest(self):
        """Testing CairoRenderer2D"""
    
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
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 600, 500)
        ctxt = cairo.Context(surf)
    
        renderer = CairoRenderer2D(ctxt)
    
        points.resize(5, Vector2D())
    
        y = 35.0
    
        for i in range(7):
            x = 60.0
    
            for j in range(6):
                renderer.setPen(test_pens[i * 6 + j])
                renderer.setBrush(test_brushes[(i * 6 + j) % 15])
    
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
    
                renderer.drawPolygon(points)
                x += 100.0
                    
            y += 70.0
                    
        surf.write_to_png('CairoRenderer2DTest_1.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 310, 1300)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)
    
        points.resize(8, Vector2D())
    
        y = 140.0
    
        for i in range(7):
            for j in range(6):
                renderer.setPen(test_pens[i * 6 + j])
    
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
    
                renderer.drawLineSegments(points)

            y += 170.0
       
        surf.write_to_png('CairoRenderer2DTest_2.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 310, 1300)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)
          
        points.resize(5, Vector2D())
    
        y = 140.0
    
        for i in range(7):
            for j in range(6):
                renderer.setPen(test_pens[i * 6 + j])
    
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
    
                renderer.drawPolyline(points)

            y += 170.0
                
        surf.write_to_png('CairoRenderer2DTest_3.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 120, 150)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)
    
        y = 5.0
        k = 0
        
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                renderer.setPen(test_pens[k])
    
                renderer.drawPoint(x, y)

                x += 20.0
                k += 1
                
            y += 20.0
    
        surf.write_to_png('CairoRenderer2DTest_4.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 160, 900)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)

        y = 5.0
    
        for i in range(6 * 7):
            renderer.setPen(test_pens[i])
    
            renderer.drawLine(10.0, y, 150.0, y)

            y += 20.0
                        
        surf.write_to_png('CairoRenderer2DTest_5.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 680, 150)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)

        renderer.setPen(Color.GREEN)
        renderer.setFont(Font())
    
        renderer.drawText(10.0, 15.0, 'The Quick Brown Fox...')
        
        renderer.setPen(Pen(Color.RED, Pen.NO_LINE))
        renderer.setFont(Font('Times', 15.0))
    
        renderer.drawText(20.0, 35.0, 'The Quick Brown Fox...')
    
        f = Font('Helvetica', 20.0)
    
        f.setItalic(True)
    
        renderer.setPen(Pen(Color.BLUE))
        renderer.setFont(f)
    
        renderer.drawText(30.0, 60.0, 'The Quick Brown Fox...')
    
        f.setItalic(False)
        f.setBold(True)
        f.setFamily('Courier')
        f.setSize(40.0)
    
        renderer.setPen(Color(1.0, 1.0, 0.0, 0.7))
        renderer.setFont(f)
    
        renderer.drawText(40.0, 90.0, 'The Quick Brown Fox...')
    
        f.setItalic(True)
        f.setFamily('Serif')
        f.setSize(60.0)
    
        renderer.setPen(Color(0.0, 1.0, 0.0, 0.8))
        renderer.setFont(f)
    
        renderer.drawText(50.0, 130.0, 'The Quick Brown Fox...')
    
        surf.write_to_png('CairoRenderer2DTest_6.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 200, 200)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)

        renderer.setPen(Pen(Color.RED, 2.0))
        renderer.setBrush(Brush(Color.BLUE, Brush.CROSS_PATTERN))
    
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
    
        renderer.transform(DTranslationMatrix(3, 100.0))
        renderer.transform(DTranslationMatrix(3, 0.0, 100.0))
    
        renderer.saveState()
    
        renderer.transform(DTranslationMatrix(3, -100.0))
        renderer.transform(DTranslationMatrix(3, 0.0, -100.0))
    
        renderer.transform(DTranslationMatrix(3, 70.0))
        renderer.transform(DTranslationMatrix(3, 0.0, 50.0))
    
        renderer.transform(DScalingMatrix(3, 1.5))
        renderer.transform(DScalingMatrix(3, 1.0, 0.8))
    
        renderer.setPen(Pen(Color.GREEN, 5.0))
        renderer.setBrush(Brush(Color.YELLOW, Brush.DENSE3_PATTERN))
    
        renderer.drawPolygon(points)
    
        renderer.restoreState()
    
        renderer.drawPolygon(points)
            
        surf.write_to_png('CairoRenderer2DTest_7.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 600, 480)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)

        y = 15.0
    
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                renderer.setPen(test_pens[i * 6 + j])
                renderer.setBrush(test_brushes[(i * 6 + j) % 15])
    
                renderer.drawRectangle(x, y, 70.0, 45.0)

                x += 100.0
                    
            y += 65.0
            
        surf.write_to_png('CairoRenderer2DTest_8.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 600, 480)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)
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
                renderer.setPen(test_pens[i * 6 + j])
                renderer.setBrush(test_brushes[(i * 6 + j) % 15])
    
                renderer.saveState()
                renderer.setTransform(Matrix3D([ [ 1.0, 0.0, x ], [ 0.0, 1.0, y ], [ 0.0, 0.0, 1.0 ] ]))
                renderer.drawPath(path)
                renderer.restoreState()

                x += 100.0

            y += 65.0

        surf.write_to_png('CairoRenderer2DTest_9.png')
    
        #-----
    
        surf = cairo.ImageSurface(cairo.FORMAT_ARGB32, 600, 480)
        ctxt = cairo.Context(surf)
        
        renderer = CairoRenderer2D(ctxt)
        clp_path = Path2D()
    
        clp_path.moveTo(450, 240)
        clp_path.arcTo(300, 240, 150, 90, 0, 360)
        clp_path.closePath()
    
        renderer.setPen(Color.BLACK)
        renderer.drawPath(clp_path)
        
        y = 45.0
    
        for i in range(7):
            x = 10.0
    
            for j in range(6):
                if ((i * 7 + j) % 2 == 0):
                    renderer.setClipPath(clp_path)
                else:
                    renderer.clearClipPath()
                
                renderer.setPen(test_pens[i * 6 + j])
                renderer.setBrush(test_brushes[(i * 6 + j) % 15])
    
                renderer.saveState()
                renderer.setTransform(Matrix3D([ [ 1.0, 0.0, x ], [ 0.0, 1.0, y ], [ 0.0, 0.0, 1.0 ] ]))
                renderer.drawPath(path)
                renderer.restoreState()

                x += 100.0
                    
            y += 65.0

        surf.write_to_png('CairoRenderer2DTest_10.png')
