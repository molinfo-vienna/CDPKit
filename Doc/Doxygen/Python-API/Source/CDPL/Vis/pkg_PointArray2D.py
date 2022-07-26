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
class PointArray2D(CDPL.Math.Vector2DArray):

    ##
    # \brief Initializes the \e %PointArray2D instance.
    # \param self The \e %PointArray2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %PointArray2D instance.
    # \param self The \e %PointArray2D instance to initialize.
    # \param array 
    #
    def __init__(self: object, array: PointArray2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %PointArray2D instance this method is called upon.
    # \param vec 
    #
    def translate(self: PointArray2D, vec: CDPL.Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param self The \e %PointArray2D instance this method is called upon.
    # \param bbox 
    #
    def getBounds(self: PointArray2D, bbox: Rectangle2D) -> None: pass
