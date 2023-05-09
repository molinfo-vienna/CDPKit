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
class OrthogonalPiPiInteractionScore(FeatureInteractionScore):

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
    DEF_MAX_ANGLE = 20.0

    ##
    # \brief Initializes the \e %OrthogonalPiPiInteractionScore instance.
    # \param score 
    #
    def __init__(score: OrthogonalPiPiInteractionScore) -> None: pass

    ##
    # \brief Initializes the \e %OrthogonalPiPiInteractionScore instance.
    # \param min_h_dist 
    # \param max_h_dist 
    # \param max_v_dist 
    # \param max_ang 
    #
    def __init__(min_h_dist: float = 4.0, max_h_dist: float = 6.0, max_v_dist: float = 1.4, max_ang: float = 20.0) -> None: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %OrthogonalPiPiInteractionScore instance \a constr.
    # \param constr The \e %OrthogonalPiPiInteractionScore instance to copy.
    # \return \a self
    #
    def assign(constr: OrthogonalPiPiInteractionScore) -> OrthogonalPiPiInteractionScore: pass

    ##
    # \brief 
    #
    minHDistance = property(getMinHDistance)

    ##
    # \brief 
    #
    maxHDistance = property(getMaxHDistance)

    ##
    # \brief 
    #
    maxVDistance = property(getMaxVDistance)

    ##
    # \brief 
    #
    maxAngle = property(getMaxAngle)
