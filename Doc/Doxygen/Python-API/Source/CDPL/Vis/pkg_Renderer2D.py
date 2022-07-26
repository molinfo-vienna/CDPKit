#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class Renderer2D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Renderer2D instance.
    # \param self The \e %Renderer2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Renderer2D instance this method is called upon.
    #
    # Different Python \e %Renderer2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Renderer2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Renderer2D) -> int: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    #
    def saveState(self: Renderer2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    #
    def restoreState(self: Renderer2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param xform 
    #
    def setTransform(self: Renderer2D, xform: CDPL.Math.Matrix3D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param xform 
    #
    def transform(self: Renderer2D, xform: CDPL.Math.Matrix3D) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param pen 
    #
    def setPen(self: Renderer2D, pen: Pen) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param brush 
    #
    def setBrush(self: Renderer2D, brush: Brush) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param font 
    #
    def setFont(self: Renderer2D, font: Font) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param x 
    # \param y 
    # \param width 
    # \param height 
    #
    def drawRectangle(self: Renderer2D, x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param x 
    # \param y 
    # \param width 
    # \param height 
    #
    def drawEllipse(self: Renderer2D, x: float, y: float, width: float, height: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param points 
    #
    def drawPolygon(self: Renderer2D, points: CDPL.Math.Vector2DArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param x1 
    # \param y1 
    # \param x2 
    # \param y2 
    #
    def drawLine(self: Renderer2D, x1: float, y1: float, x2: float, y2: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param points 
    #
    def drawPolyline(self: Renderer2D, points: CDPL.Math.Vector2DArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param points 
    #
    def drawLineSegments(self: Renderer2D, points: CDPL.Math.Vector2DArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param x 
    # \param y 
    #
    def drawPoint(self: Renderer2D, x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Renderer2D instance this method is called upon.
    # \param x 
    # \param y 
    # \param txt 
    #
    def drawText(self: Renderer2D, x: float, y: float, txt: str) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
