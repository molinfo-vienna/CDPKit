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
class AlignedShapeTverskyScore(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AlignedShapeTverskyScore instance.
    # \param beta 
    #
    def __init__(beta: float = 0.95) -> None: pass

    ##
    # \brief Initializes the \e %AlignedShapeTverskyScore instance.
    # \param score 
    #
    def __init__(score: AlignedShapeTverskyScore) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %AlignedShapeTverskyScore instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AlignedShapeTverskyScore instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AlignedShapeTverskyScore instance \a score.
    # \param score The \e %AlignedShapeTverskyScore instance to copy.
    # \return \a self
    #
    def assign(score: AlignedShapeTverskyScore) -> AlignedShapeTverskyScore: pass

    ##
    # \brief 
    # \param res 
    # \return 
    #
    def __call__(res: AlignmentResult) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
