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
# \brief ParallelPiPiInteractionScore.
# 
class ParallelPiPiInteractionScore(FeatureInteractionScore):

    ##
    # \brief 
    #
    DEF_MIN_V_DISTANCE = 3.0

    ##
    # \brief 
    #
    DEF_MAX_V_DISTANCE = 5.5

    ##
    # \brief 
    #
    DEF_MAX_H_DISTANCE = 2.8

    ##
    # \brief 
    #
    DEF_MAX_ANGLE = 20.0

    ##
    # \brief Initializes a copy of the \e %ParallelPiPiInteractionScore instance \a score.
    # \param score The \e %ParallelPiPiInteractionScore instance to copy.
    # 
    def __init__(score: ParallelPiPiInteractionScore) -> None: pass

    ##
    # \brief Constructs a <tt>ParallelPiPiInteractionScore</tt> functor with the specified constraints.
    # 
    # \param min_v_dist The minimum allowed distance of the two feature-positions orthogonal to the ring-planes.
    # \param max_v_dist The maximum allowed distance of the two feature-positions orthogonal to the ring-planes.
    # \param max_h_dist The maximum allowed distance of the feature-position along the their ring-planes.
    # \param max_ang The maximum allowed angle deviation from 0° of the two ring-plane orientation vectors.
    # 
    def __init__(min_v_dist: float = 3.0, max_v_dist: float = 5.5, max_h_dist: float = 2.8, max_ang: float = 20.0) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setDistanceScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinVDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxVDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxHDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ParallelPiPiInteractionScore instance \a constr.
    # \param constr The \c %ParallelPiPiInteractionScore instance to copy.
    # \return \a self
    # 
    def assign(constr: ParallelPiPiInteractionScore) -> ParallelPiPiInteractionScore: pass

    minVDistance = property(getMinVDistance)

    maxVDistance = property(getMaxVDistance)

    maxHDistance = property(getMaxHDistance)

    maxAngle = property(getMaxAngle)
