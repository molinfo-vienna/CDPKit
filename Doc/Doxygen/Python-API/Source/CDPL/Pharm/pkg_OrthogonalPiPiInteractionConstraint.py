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
# \brief OrthogonalPiPiInteractionConstraint.
# 
class OrthogonalPiPiInteractionConstraint(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MIN_H_DISTANCE = 4.0

    ##
    # \brief 
    #
    DEF_MAX_H_DISTANCE = 6.0

    ##
    # \brief 
    #
    DEF_MAX_V_DISTANCE = 1.4

    ##
    # \brief 
    #
    DEF_MAX_ANGLE = 30.0

    ##
    # \brief Initializes the \e %OrthogonalPiPiInteractionConstraint instance.
    # \param self The \e %OrthogonalPiPiInteractionConstraint instance to initialize.
    # \param constr 
    # 
    def __init__(constr: OrthogonalPiPiInteractionConstraint) -> None: pass

    ##
    # \brief Constructs a <tt>OrthogonalPiPiInteractionConstraint</tt> functor with the specified constraints.
    # 
    # \param min_h_dist The minimum allowed aromatic ring center distance in the plane of the vertically oriented ring.
    # \param max_h_dist The maximum allowed aromatic ring center distance in the plane of the vertically oriented ring.
    # \param max_v_dist The maximum allowed distance distance of the center of the horizontally oriented aromatic ring to the plane of the vertically oriented ring.
    # \param max_ang The maximum allowed angle deviation from 90° of the two ring-plane orientation vectors.
    # 
    def __init__(min_h_dist: float = 4.0, max_h_dist: float = 6.0, max_v_dist: float = 1.4, max_ang: float = 30.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %OrthogonalPiPiInteractionConstraint instance this method is called upon.
    # 
    # Different Python \e %OrthogonalPiPiInteractionConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %OrthogonalPiPiInteractionConstraint instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getMinHDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxHDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxVDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAngle() -> float: pass

    ##
    # \brief 
    # \param constr 
    # \return 
    #
    def assign(constr: OrthogonalPiPiInteractionConstraint) -> OrthogonalPiPiInteractionConstraint: pass

    ##
    # \brief 
    # \param ftr1 
    # \param ftr2 
    # \return 
    #
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    objectID = property(getObjectID)

    minHDistance = property(getMinHDistance)

    maxHDistance = property(getMaxHDistance)

    maxVDistance = property(getMaxVDistance)

    maxAngle = property(getMaxAngle)
