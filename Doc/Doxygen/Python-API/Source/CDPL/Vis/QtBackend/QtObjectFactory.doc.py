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
    # \brief 
    # \param font 
    # \return 
    #
    @staticmethod
    def createQFont(font: Vis.Font) -> PyQt5.QtGui.QFont: pass

    ##
    # \brief 
    # \param color 
    # \return 
    #
    @staticmethod
    def createQColor(color: Vis.Color) -> PyQt5.QtGui.QColor: pass

    ##
    # \brief 
    # \param pen 
    # \return 
    #
    @staticmethod
    def createQPen(pen: Vis.Pen) -> PyQt5.QtGui.QPen: pass

    ##
    # \brief 
    # \param brush 
    # \return 
    #
    @staticmethod
    def createQBrush(brush: Vis.Brush) -> PyQt5.QtGui.QBrush: pass
