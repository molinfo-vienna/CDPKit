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
    # \brief 
    # \param x 
    # \param y 
    #
    def moveTo(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param cx 
    # \param cy 
    # \param rx 
    # \param ry 
    # \param start_ang 
    # \param sweep 
    #
    def arcTo(cx: float, cy: float, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def lineTo(x: float, y: float) -> None: pass

    ##
    # \brief 
    #
    def closePath() -> None: pass

    objectID = property(getObjectID)
