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
class CationPiInteractionScore(FeatureInteractionScore):

    ##
    # \brief 
    #
    DEF_MIN_DISTANCE = 3.5

    ##
    # \brief 
    #
    DEF_MAX_DISTANCE = 5.5

    ##
    # \brief 
    #
    DEF_MAX_ANGLE = 60.0

    ##
    # \brief Initializes the \e %CationPiInteractionScore instance.
    # \param score 
    #
    def __init__(score: CationPiInteractionScore) -> None: pass

    ##
    # \brief Initializes the \e %CationPiInteractionScore instance.
    # \param aro_cat 
    # \param min_dist 
    # \param max_dist 
    # \param max_ang 
    #
    def __init__(aro_cat: bool, min_dist: float = 3.5, max_dist: float = 5.5, max_ang: float = 60.0) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setNormalizationFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CationPiInteractionScore instance \a constr.
    # \param constr The \e %CationPiInteractionScore instance to copy.
    # \return \a self
    #
    def assign(constr: CationPiInteractionScore) -> CationPiInteractionScore: pass

    ##
    # \brief 
    #
    minDistance = property(getMinDistance)

    ##
    # \brief 
    #
    maxDistance = property(getMaxDistance)

    ##
    # \brief 
    #
    maxAngle = property(getMaxAngle)
