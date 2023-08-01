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
# \brief HBondingInteractionScore.
# 
class HBondingInteractionScore(FeatureInteractionScore):

    ##
    # \brief 
    #
    DEF_MIN_HB_LENGTH = 1.2

    ##
    # \brief 
    #
    DEF_MAX_HB_LENGTH = 2.8

    ##
    # \brief 
    #
    DEF_MIN_AHD_ANGLE = 150.0

    ##
    # \brief 
    #
    DEF_MAX_ACC_ANGLE = 75.0

    ##
    # \brief Initializes the \e %HBondingInteractionScore instance with a copy of the state of the \e %HBondingInteractionScore instance \a score.
    # \param score The \e %HBondingInteractionScore instance to copy.
    # 
    def __init__(score: HBondingInteractionScore) -> None: pass

    ##
    # \brief Constructs a <tt>HBondingInteractionScore</tt> functor with the specified constraints.
    # 
    # \param don_acc <tt>True</tt> if the first feature argument represents the donor- and the second one the acceptor-feature, and <tt>False</tt> otherwise.
    # \param min_len The minimum allowed length of the H-bond (distance between the hydrogen-atom and acceptor-feature).
    # \param max_len The maximum allowed length of the H-bond (distance between the hydrogen-atom and acceptor-feature).
    # \param min_ahd_ang The minimum allowed angle between the acceptor-feature, hydrogen-atom and donor-feature.
    # \param max_acc_ang The maximum allowed angle between the H-bond direction and the acceptor-feature vector.
    # 
    def __init__(don_acc: bool, min_len: float = 1.2, max_len: float = 2.8, min_ahd_ang: float = 150.0, max_acc_ang: float = 75.0) -> None: pass

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
    def setAHDAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinLength() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxLength() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMinAHDAngle() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAcceptorAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %HBondingInteractionScore instance \a constr.
    # \param constr The \e %HBondingInteractionScore instance to copy.
    # \return \a self
    # 
    def assign(constr: HBondingInteractionScore) -> HBondingInteractionScore: pass

    minLength = property(getMinLength)

    maxLength = property(getMaxLength)

    minAHDAngle = property(getMinAHDAngle)

    maxAcceptorAngle = property(getMaxAcceptorAngle)
