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
# \brief Provides constants for selecting which alignment results are kept by alignment routines.
# 
class AlignmentResultSelectionMode(Boost.Python.instance):

    ##
    # \brief Keep all alignment results.
    # 
    ALL = 0

    ##
    # \brief Keep only the best alignment result per (reference shape, aligned shape) combination.
    # 
    BEST_PER_SHAPE_COMBINATION = 1

    ##
    # \brief Keep only the best alignment result per reference shape.
    # 
    BEST_PER_REFERENCE_SHAPE = 2

    ##
    # \brief Keep only the best alignment result per reference shape set.
    # 
    BEST_PER_REFERENCE_SET = 3

    ##
    # \brief Keep only the single best alignment result overall.
    # 
    BEST_OVERALL = 4
