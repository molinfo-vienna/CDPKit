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
# \brief The abstract base of classes implementing the 2D visualization of data objects.
# 
# Subclasses of <tt>View2D</tt> implement the generation of two-dimensional visual representations of data objects with a given type. According to the <em>Model-View-Controller</em> [\ref WMVC] concept, a <tt>View2D</tt> instance thus plays the role of the <em>View</em> for a <em>Model</em> represented by the visualized data object. The rendering of a model's visual represention on a given target device is performed by the render() method, which uses a passed Vis.Renderer2DRenderer2D instance for drawing the graphical primitives constituting the overall depiction. The behaviour of a <tt>View2D</tt> instance can be configured using control-parameters and properties (if the type of the data object is a direct or indirect subclass of Base.PropertyContainer). Control-parameters can be modified and queried using the methods provided by Base.ControlParameterContainer which is a public base class of <tt>View2D</tt>.
# 
class View2D(CDPL.Base.ControlParameterContainer):

    ##
    # \brief Initializes the \e %View2D instance.
    # \param self The \e %View2D instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Renders the visual representation of the model using the specified Vis.Renderer2D instance.
    # 
    # \param renderer The Renderer2D instance.
    # 
    def render(renderer: Renderer2D) -> None: pass

    ##
    # \brief Specifies a font metrics object that will be used to measure the dimension of text labels.
    # 
    # \param font_metrics A reference to the font metrics object or <em>None</em>.
    # 
    def setFontMetrics(font_metrics: FontMetrics) -> None: pass

    ##
    # \brief Calculates the bounding rectangle of the visualized model.
    # 
    # \param bounds A Rectangle2D object storing the calculated bounding rectangle.
    # 
    def getModelBounds(bounds: Rectangle2D) -> None: pass
