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
class XBondingInteractionConstraint(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MIN_AX_DISTANCE = 1.6

    ##
    # \brief 
    #
    DEF_MAX_AX_DISTANCE = 3.75

    ##
    # \brief 
    #
    DEF_MIN_AXB_ANGLE = 140.0

    ##
    # \brief 
    #
    DEF_ACC_ANGLE_TOLERANCE = 45.0

    ##
    # \brief Initializes the \e %XBondingInteractionConstraint instance.
    # \param constr 
    #
    def __init__(constr: XBondingInteractionConstraint) -> None: pass

    ##
    # \brief Initializes the \e %XBondingInteractionConstraint instance.
    # \param don_acc 
    # \param min_ax_dist 
    # \param max_ax_dist 
    # \param min_axb_ang 
    # \param acc_ang_tol 
    #
    def __init__(don_acc: bool, min_ax_dist: float = 1.6, max_ax_dist: float = 1.6, min_axb_ang: float = 140.0, acc_ang_tol: float = 45.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %XBondingInteractionConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %XBondingInteractionConstraint instances \e a and \e b reference different C++ objects. 
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
    def getMinAXDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAXDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMinAXBAngle() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getAcceptorAngleTolerance() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %XBondingInteractionConstraint instance \a constr.
    # \param constr The \e %XBondingInteractionConstraint instance to copy.
    # \return \a self
    #
    def assign(constr: XBondingInteractionConstraint) -> XBondingInteractionConstraint: pass

    ##
    # \brief 
    # \param ftr1 
    # \param ftr2 
    # \return 
    #
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    minAXDistance = property(getMinAXDistance)

    ##
    # \brief 
    #
    maxAXDistance = property(getMaxAXDistance)

    ##
    # \brief 
    #
    minAXBAngle = property(getMinAXBAngle)

    ##
    # \brief 
    #
    acceptorAngleTolerance = property(getAcceptorAngleTolerance)
