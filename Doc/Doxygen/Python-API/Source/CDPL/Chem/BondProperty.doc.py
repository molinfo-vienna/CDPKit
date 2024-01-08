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
# \brief Provides keys for built-in Chem.Bond properties.
# 
class BondProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    ORDER = CDPL.Base.LookupKey('ORDER')

    ##
    # \brief 
    #
    SYBYL_TYPE = CDPL.Base.LookupKey('SYBYL_TYPE')

    ##
    # \brief 
    #
    RING_FLAG = CDPL.Base.LookupKey('RING_FLAG')

    ##
    # \brief 
    #
    AROMATICITY_FLAG = CDPL.Base.LookupKey('AROMATICITY_FLAG')

    ##
    # \brief 
    #
    STEREO_DESCRIPTOR = CDPL.Base.LookupKey('STEREO_DESCRIPTOR')

    ##
    # \brief 
    #
    STEREO_CENTER_FLAG = CDPL.Base.LookupKey('STEREO_CENTER_FLAG')

    ##
    # \brief 
    #
    CIP_CONFIGURATION = CDPL.Base.LookupKey('CIP_CONFIGURATION')

    ##
    # \brief 
    #
    DIRECTION = CDPL.Base.LookupKey('DIRECTION')

    ##
    # \brief 
    #
    STEREO_2D_FLAG = CDPL.Base.LookupKey('STEREO_2D_FLAG')

    ##
    # \brief 
    #
    REACTION_CENTER_STATUS = CDPL.Base.LookupKey('REACTION_CENTER_STATUS')

    ##
    # \brief 
    #
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief 
    #
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief 
    #
    MATCH_EXPRESSION_STRING = CDPL.Base.LookupKey('MATCH_EXPRESSION_STRING')
