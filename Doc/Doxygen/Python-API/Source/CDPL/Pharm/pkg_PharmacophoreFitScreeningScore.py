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
class PharmacophoreFitScreeningScore(PharmacophoreFitScore):

    ##
    # \brief Initializes the \e %PharmacophoreFitScreeningScore instance.
    # \param score 
    #
    def __init__(score: PharmacophoreFitScreeningScore) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreFitScreeningScore instance.
    # \param match_cnt_weight 
    # \param pos_match_weight 
    # \param geom_match_weight 
    #
    def __init__(match_cnt_weight: float = 1.0, pos_match_weight: float = 0.5, geom_match_weight: float = 0.4) -> None: pass

    ##
    # \brief 
    # \param hit 
    # \return 
    #
    def __call__(hit: SearchHit) -> float: pass
