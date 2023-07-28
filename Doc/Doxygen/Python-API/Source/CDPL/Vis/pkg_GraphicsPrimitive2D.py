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
# \brief The abstract base class of all 2D graphics primitives.
# 
# Graphics primitives are simple (atomic) geometrical objects which can be used as building blocks for larger and more complex drawings (e.g. the 2D depiction of a molecular structure). The actual type (e.g. point, line, polygon, ...) and look (e.g. color, font, ...) of an graphics primitive is defined by subclasses of <tt>GraphicsPrimitive2D</tt>. Subclasses have to implement the render() method that visualizes the primitive by means of a Renderer2D implementation instance.
# 
class GraphicsPrimitive2D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GraphicsPrimitive2D instance.
    # \param self The \e %GraphicsPrimitive2D instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GraphicsPrimitive2D instance this method is called upon.
    # 
    # Different Python \e %GraphicsPrimitive2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GraphicsPrimitive2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Visualizes the graphics primitive by means of the Renderer2D instance <em>renderer</em>.
    # 
    # \param renderer The renderer that performs the drawing operations.
    # 
    def render(renderer: Renderer2D) -> None: pass

    ##
    # \brief Calculates the bounds of the graphics primitive.
    # 
    # \param bounds The object storing the calculated bounding box.
    # \param font_metrics The font metrics object to use for bounds calculation (if required).
    # 
    def getBounds(bounds: Rectangle2D, font_metrics: FontMetrics = 0) -> None: pass

    ##
    # \brief Creates a dynamically allocated copy of the graphics primitive.
    # 
    # \return The copy of the graphics primitive.
    # 
    def clone() -> GraphicsPrimitive2D: pass

    objectID = property(getObjectID)
