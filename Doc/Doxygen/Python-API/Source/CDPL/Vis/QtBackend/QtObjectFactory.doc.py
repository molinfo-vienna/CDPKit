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
# \brief Provides methods for the creation of <tt>QFont</tt>, <tt>QColor</tt>, <tt>QPen</tt> and <tt>QBrush</tt> objects from Font, Color, Pen and Brush instances.
# 
# For information about <tt>QFont</tt>, <tt>QColor</tt>, <tt>QPen</tt> and <tt>QBrush</tt> see [\ref QTDOC].
# 
class QtObjectFactory(builtins.object):

    ##
    # \brief Creates a <tt>QFont</tt> object that corresponds to the specified font.
    # 
    # \param font The font object.
    # 
    # \return A <tt>QFont</tt> object equivalent to <em>font</em>.
    # 
    @staticmethod
    def createQFont(font: Vis.Font) -> PyQt5.QtGui.QFont: pass

    ##
    # \brief Creates a <tt>QColor</tt> object that corresponds to the specified color.
    # 
    # \param color The color object.
    # 
    # \return A <tt>QColor</tt> object equivalent to <em>color</em>.
    # 
    @staticmethod
    def createQColor(color: Vis.Color) -> PyQt5.QtGui.QColor: pass

    ##
    # \brief Creates a <tt>QPen</tt> object that corresponds to the specified pen.
    # 
    # \param pen The pen object.
    # 
    # \return A <tt>QPen</tt> object equivalent to <em>pen</em>.
    # 
    @staticmethod
    def createQPen(pen: Vis.Pen) -> PyQt5.QtGui.QPen: pass

    ##
    # \brief Creates a <tt>QBrush</tt> object that corresponds to the specified brush.
    # 
    # \param brush The brush object.
    # 
    # \return A <tt>QBrush</tt> object equivalent to <em>brush</em>.
    # 
    @staticmethod
    def createQBrush(brush: Vis.Brush) -> PyQt5.QtGui.QBrush: pass

    ##
    # \brief Creates a <tt>QPainterPath</tt> object that corresponds to the specified path.
    # 
    # \param path The path object.
    # \param qt_path The QPainterPath object to create.
    # 
    # \return The argument <em>qt_path</em>.
    # 
    @staticmethod
    def createQPainterPath(path: Vis.Path2D, qt_path: PyQt5.QtGui.QPainterPath) -> PyQt5.QtGui.QPainterPath: pass
