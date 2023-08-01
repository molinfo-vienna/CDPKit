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
# \brief FeatureInteractionScoreCombiner.
# 
class FeatureInteractionScoreCombiner(FeatureInteractionScore):

    ##
    # \brief Initializes the \e %FeatureInteractionScoreCombiner instance with a copy of the state of the \e %FeatureInteractionScoreCombiner instance \a comb.
    # \param comb The \e %FeatureInteractionScoreCombiner instance to copy.
    # 
    def __init__(comb: FeatureInteractionScoreCombiner) -> None: pass

    ##
    # \brief Constructs a <tt>FeatureInteractionScoreCombiner</tt> that combines the score values calculated by two feature interaction scoring functions.
    # 
    # \param score1 The first interaction scoring function.
    # \param score2 The second interaction scoring function.
    # \param comb_func The function calculating the final score value.
    # 
    def __init__(score1: FeatureInteractionScore, score2: FeatureInteractionScore, comb_func: DoubleDouble2Functor) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureInteractionScoreCombiner instance \a con.
    # \param con The \e %FeatureInteractionScoreCombiner instance to copy.
    # \return \a self
    # 
    def assign(con: FeatureInteractionScoreCombiner) -> FeatureInteractionScoreCombiner: pass
