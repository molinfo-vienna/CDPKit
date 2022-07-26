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
    # \param self The \e %PharmacophoreFitScreeningScore instance to initialize.
    # \param score 
    #
    def __init__(self: object, score: PharmacophoreFitScreeningScore) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreFitScreeningScore instance.
    # \param self The \e %PharmacophoreFitScreeningScore instance to initialize.
    # \param match_cnt_factor 
    # \param pos_match_factor 
    # \param geom_match_factor 
    #
    def __init__(self: object, match_cnt_factor: float = 0.8, pos_match_factor: float = 0.1, geom_match_factor: float = 0.1) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreFitScreeningScore instance this method is called upon.
    # \param hit 
    # \return 
    #
    def __call__(self: PharmacophoreFitScreeningScore, hit: SearchHit) -> float: pass
