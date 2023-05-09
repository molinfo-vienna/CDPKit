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
class FeatureDistanceScore(FeatureInteractionScore):

    ##
    # \brief Initializes the \e %FeatureDistanceScore instance.
    # \param score 
    #
    def __init__(score: FeatureDistanceScore) -> None: pass

    ##
    # \brief Initializes the \e %FeatureDistanceScore instance.
    # \param min_dist 
    # \param max_dist 
    #
    def __init__(min_dist: float, max_dist: float) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setDistanceScoringFunction(func: DoubleDoubleFunctor) -> None: pass

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
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureDistanceScore instance \a func.
    # \param func The \e %FeatureDistanceScore instance to copy.
    # \return \a self
    #
    def assign(func: FeatureDistanceScore) -> FeatureDistanceScore: pass

    ##
    # \brief 
    #
    minDistance = property(getMinDistance)

    ##
    # \brief 
    #
    maxDistance = property(getMaxDistance)
