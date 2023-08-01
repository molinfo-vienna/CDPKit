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
# \brief Provides constants that are used to specify the degeneracy of the electronic state of radical atoms.
# 
class RadicalType(Boost.Python.instance):

    ##
    # \brief Specifies that the atom is not a radical.
    # 
    NOT_RADICALIC = 0

    ##
    # \brief Specifies that the atom is a doublet radical.
    # 
    # Doublet radicals are simple free radicals with one unpaired electron.
    # 
    DOUBLET = 2

    ##
    # \brief Specifies that the atom is a singlet diradical.
    # 
    # Singlet diradicals have two electrons with antiparallel spin (<em>+1/2</em> and <em>–1/2</em>) in one orbital. The other adjacent, degenerate (equal energy) orbital is empty.
    # 
    SINGLET = 1

    ##
    # \brief Specifies that the atom is a triplet diradical.
    # 
    # Triplet diradicals have two spin-up electrons in adjacent, degenerate (equal energy) orbitals.
    # 
    TRIPLET = 3
