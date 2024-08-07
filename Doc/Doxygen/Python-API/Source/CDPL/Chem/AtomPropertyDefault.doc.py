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
# \brief Provides default values for built-in Chem.Atom properties.
# 
class AtomPropertyDefault(Boost.Python.instance):

    ##
    # \brief 
    #
    SYMBOL = ''

    ##
    # \brief 
    #
    NAME = ''

    ##
    # \brief 
    #
    FORMAL_CHARGE = 0

    ##
    # \brief 
    #
    ISOTOPE = 0

    ##
    # \brief 
    #
    UNPAIRED_ELECTRON_COUNT = 0

    ##
    # \brief 
    #
    RADICAL_TYPE = 0

    ##
    # \brief 
    #
    TYPE = 0

    ##
    # \brief 
    #
    SYBYL_TYPE = 0

    ##
    # \brief 
    #
    REACTION_CENTER_STATUS = 0

    ##
    # \brief 
    #
    STEREO_DESCRIPTOR = StereoDescriptor(config=0)

    ##
    # \brief 
    #
    COMPONENT_GROUP_ID = 0

    ##
    # \brief 
    #
    ATOM_MAPPING_ID = 0

    ##
    # \brief 
    #
    MATCH_CONSTRAINTS = MatchConstraintList()

    ##
    # \brief 
    #
    MOL2_NAME = ''

    ##
    # \brief 
    #
    MOL2_CHARGE = 0.0

    ##
    # \brief 
    #
    MDL_DB_STEREO_CARE_FLAG = False
