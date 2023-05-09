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
# \brief 
#
class LinePrimitive2D(Line2D, GraphicsPrimitive2D):

    ##
    # \brief Initializes the \e %LinePrimitive2D instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %LinePrimitive2D instance.
    # \param prim 
    #
    def __init__(prim: LinePrimitive2D) -> None: pass

    ##
    # \brief Initializes the \e %LinePrimitive2D instance.
    # \param line 
    #
    def __init__(line: Line2D) -> None: pass

    ##
    # \brief Initializes the \e %LinePrimitive2D instance.
    # \param beg 
    # \param end 
    #
    def __init__(beg: CDPL.Math.Vector2D, end: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LinePrimitive2D instance \a prim.
    # \param prim The \e %LinePrimitive2D instance to copy.
    # \return \a self
    #
    def assign(prim: LinePrimitive2D) -> LinePrimitive2D: pass

    ##
    # \brief 
    # \param pen 
    #
    def setPen(pen: Pen) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPen() -> Pen: pass

    ##
    # \brief 
    #
    pen = property(getPen, setPen)
