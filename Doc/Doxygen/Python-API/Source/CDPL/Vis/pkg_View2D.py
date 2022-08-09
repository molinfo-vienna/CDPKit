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
    #
    def __init__() -> None: pass

    ##
    # \brief 
    # \param renderer 
    #
    def render(renderer: Renderer2D) -> None: pass

    ##
    # \brief 
    # \param font_metrics 
    #
    def setFontMetrics(font_metrics: FontMetrics) -> None: pass

    ##
    # \brief 
    # \param bounds 
    #
    def getModelBounds(bounds: Rectangle2D) -> None: pass