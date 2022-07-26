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
class View2D(CDPL.Base.ControlParameterContainer):

    ##
    # \brief Initializes the \e %View2D instance.
    # \param self The \e %View2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %View2D instance this method is called upon.
    # \param renderer 
    #
    def render(self: View2D, renderer: Renderer2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %View2D instance this method is called upon.
    # \param font_metrics 
    #
    def setFontMetrics(self: View2D, font_metrics: FontMetrics) -> None: pass

    ##
    # \brief 
    # \param self The \e %View2D instance this method is called upon.
    # \param bounds 
    #
    def getModelBounds(self: View2D, bounds: Rectangle2D) -> None: pass
