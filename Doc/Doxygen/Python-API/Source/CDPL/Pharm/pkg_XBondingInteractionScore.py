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
class XBondingInteractionScore(FeatureInteractionScore):

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
    # \brief Initializes the \e %XBondingInteractionScore instance.
    # \param score 
    #
    def __init__(score: XBondingInteractionScore) -> None: pass

    ##
    # \brief Initializes the \e %XBondingInteractionScore instance.
    # \param don_acc 
    # \param min_ax_dist 
    # \param max_ax_dist 
    # \param min_axb_ang 
    # \param acc_ang_tol 
    #
    def __init__(don_acc: bool, min_ax_dist: float = 1.6, max_ax_dist: float = 3.75, min_axb_ang: float = 140.0, acc_ang_tol: float = 45.0) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setNormalizationFunction(func: DoubleDoubleFunctor) -> None: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %XBondingInteractionScore instance \a constr.
    # \param constr The \e %XBondingInteractionScore instance to copy.
    # \return \a self
    #
    def assign(constr: XBondingInteractionScore) -> XBondingInteractionScore: pass

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
