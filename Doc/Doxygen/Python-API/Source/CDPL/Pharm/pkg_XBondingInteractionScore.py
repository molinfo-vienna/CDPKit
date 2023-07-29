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
# \brief XBondingInteractionScore.
# 
class XBondingInteractionScore(FeatureInteractionScore):

    ##
    # \brief 
    #
    DEF_MIN_AX_DISTANCE = 1.6

    ##
    # \brief 
    #
    DEF_MAX_AX_DISTANCE = 4.0

    ##
    # \brief 
    #
    DEF_MIN_AXB_ANGLE = 150.0

    ##
    # \brief 
    #
    DEF_MAX_ACC_ANGLE = 35.0

    ##
    # \brief Initializes the \e %XBondingInteractionScore instance.
    # \param score 
    # 
    def __init__(score: XBondingInteractionScore) -> None: pass

    ##
    # \brief Constructs a <tt>XBondingInteractionScore</tt> functor with the specified scores.
    # 
    # \param don_acc <tt>True</tt> if the first feature argument represents the donor- and the second one the acceptor-feature, and <tt>False</tt> otherwise.
    # \param min_ax_dist The minimum allowed distance between the halogen-atom and the acceptor-feature.
    # \param max_ax_dist The maximum allowed distance between the halogen-atom and the acceptor-feature.
    # \param min_axb_ang The minimum allowed angle between the vectors halogen->acceptor snd halogen->bound atom.
    # \param max_acc_ang The maximum allowed angle deviation from the acceptor's preferred X-bonding direction.
    # 
    def __init__(don_acc: bool, min_ax_dist: float = 1.6, max_ax_dist: float = 4.0, min_axb_ang: float = 150.0, max_acc_ang: float = 35.0) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setDistanceScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAcceptorAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAXBAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

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
    def getMaxAcceptorAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %XBondingInteractionScore instance \a constr.
    # \param constr The \e %XBondingInteractionScore instance to copy.
    # \return \a self
    # 
    def assign(constr: XBondingInteractionScore) -> XBondingInteractionScore: pass

    minAXDistance = property(getMinAXDistance)

    maxAXDistance = property(getMaxAXDistance)

    minAXBAngle = property(getMinAXBAngle)

    maxAcceptorAngle = property(getMaxAcceptorAngle)
