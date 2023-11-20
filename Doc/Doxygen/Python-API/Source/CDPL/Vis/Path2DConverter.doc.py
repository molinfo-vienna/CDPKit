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
# \brief Provides an interface for classes that implement the conversion of Vis.Path2D objects into rendering backend specific path descriptions or drawing operations.
# 
# \see Vis.Renderer2D 
# 
# \since 1.1
# 
class Path2DConverter(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Path2DConverter instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Path2DConverter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Path2DConverter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Called when a Vis.Path2D element created by a Vis.Path2D.moveTo() call is encountered.
    # 
    # \param x The x-coordinate of the newly set current position.
    # \param y The y-coordinate of the newly set current position.
    # 
    def moveTo(x: float, y: float) -> None: pass

    ##
    # \brief Called when a Vis.Path2D element created by a Vis.Path2D.arcTo() call is encountered.
    # 
    # \param cx The x-coordinate of the ellipse center.
    # \param cy The y-coordinate of the ellipse center.
    # \param rx The x-radius of the ellipse.
    # \param ry The y-radius of the ellipse.
    # \param start_ang The start angle of the arg in degrees.
    # \param sweep The length of the arg in degrees.
    # 
    def arcTo(cx: float, cy: float, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief Called when a Vis.Path2D element created by a Vis.Path2D.lineTo() call is encountered.
    # 
    # \param x Specifies the x-coordinate of the line's end point.
    # \param y Specifies the y-coordinate of the line's end point.
    # 
    def lineTo(x: float, y: float) -> None: pass

    ##
    # \brief Called when a Vis.Path2D element created by a Vis.Path2D.closePath() call is encountered.
    # 
    def closePath() -> None: pass

    objectID = property(getObjectID)
