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
# \brief IonicInteractionScore.
# 
class IonicInteractionScore(FeatureDistanceScore):

    ##
    # \brief 
    #
    DEF_MIN_DISTANCE = 1.5

    ##
    # \brief 
    #
    DEF_MAX_DISTANCE = 5.5

    ##
    # \brief Initializes the \e %IonicInteractionScore instance with a copy of the state of the \e %IonicInteractionScore instance \a score.
    # \param score The \e %IonicInteractionScore instance to copy.
    # 
    def __init__(score: IonicInteractionScore) -> None: pass

    ##
    # \brief Constructs a <tt>IonicInteractionScore</tt> functor with a minimum ionic-feature pair distance of <em>min_dist</em> and a maximum distance of <em>max_dist</em>.
    # 
    # \param min_dist The minimum allowed feature pair distance.
    # \param max_dist The maximum allowed feature pair distance.
    # 
    def __init__(min_dist: float = 1.5, max_dist: float = 5.5) -> None: pass
