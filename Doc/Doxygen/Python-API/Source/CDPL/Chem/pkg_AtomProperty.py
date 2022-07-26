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
class AtomProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    NAME = CDPL.Base.LookupKey(id=5, name='NAME')

    ##
    # \brief 
    #
    SYMBOL = CDPL.Base.LookupKey(id=6, name='SYMBOL')

    ##
    # \brief 
    #
    TYPE = CDPL.Base.LookupKey(id=7, name='TYPE')

    ##
    # \brief 
    #
    FORMAL_CHARGE = CDPL.Base.LookupKey(id=8, name='FORMAL_CHARGE')

    ##
    # \brief 
    #
    ISOTOPE = CDPL.Base.LookupKey(id=9, name='ISOTOPE')

    ##
    # \brief 
    #
    RADICAL_TYPE = CDPL.Base.LookupKey(id=10, name='RADICAL_TYPE')

    ##
    # \brief 
    #
    HYBRIDIZATION = CDPL.Base.LookupKey(id=11, name='HYBRIDIZATION')

    ##
    # \brief 
    #
    RING_FLAG = CDPL.Base.LookupKey(id=12, name='RING_FLAG')

    ##
    # \brief 
    #
    AROMATICITY_FLAG = CDPL.Base.LookupKey(id=13, name='AROMATICITY_FLAG')

    ##
    # \brief 
    #
    UNPAIRED_ELECTRON_COUNT = CDPL.Base.LookupKey(id=14, name='UNPAIRED_ELECTRON_COUNT')

    ##
    # \brief 
    #
    IMPLICIT_HYDROGEN_COUNT = CDPL.Base.LookupKey(id=15, name='IMPLICIT_HYDROGEN_COUNT')

    ##
    # \brief 
    #
    COORDINATES_2D = CDPL.Base.LookupKey(id=16, name='COORDINATES_2D')

    ##
    # \brief 
    #
    COORDINATES_3D_ARRAY = CDPL.Base.LookupKey(id=17, name='COORDINATES_3D_ARRAY')

    ##
    # \brief 
    #
    MORGAN_NUMBER = CDPL.Base.LookupKey(id=18, name='MORGAN_NUMBER')

    ##
    # \brief 
    #
    CANONICAL_NUMBER = CDPL.Base.LookupKey(id=19, name='CANONICAL_NUMBER')

    ##
    # \brief 
    #
    CIP_PRIORITY = CDPL.Base.LookupKey(id=20, name='CIP_PRIORITY')

    ##
    # \brief 
    #
    SYMMETRY_CLASS = CDPL.Base.LookupKey(id=21, name='SYMMETRY_CLASS')

    ##
    # \brief 
    #
    HYDROPHOBICITY = CDPL.Base.LookupKey(id=22, name='HYDROPHOBICITY')

    ##
    # \brief 
    #
    STEREO_DESCRIPTOR = CDPL.Base.LookupKey(id=23, name='STEREO_DESCRIPTOR')

    ##
    # \brief 
    #
    STEREO_CENTER_FLAG = CDPL.Base.LookupKey(id=24, name='STEREO_CENTER_FLAG')

    ##
    # \brief 
    #
    CIP_CONFIGURATION = CDPL.Base.LookupKey(id=25, name='CIP_CONFIGURATION')

    ##
    # \brief 
    #
    MDL_PARITY = CDPL.Base.LookupKey(id=26, name='MDL_PARITY')

    ##
    # \brief 
    #
    MDL_DB_STEREO_CARE_FLAG = CDPL.Base.LookupKey(id=27, name='MDL_DB_STEREO_CARE_FLAG')

    ##
    # \brief 
    #
    SYBYL_TYPE = CDPL.Base.LookupKey(id=28, name='SYBYL_TYPE')

    ##
    # \brief 
    #
    MOL2_NAME = CDPL.Base.LookupKey(id=30, name='MOL2_NAME')

    ##
    # \brief 
    #
    MOL2_CHARGE = CDPL.Base.LookupKey(id=29, name='MOL2_CHARGE')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_ID = CDPL.Base.LookupKey(id=31, name='MOL2_SUBSTRUCTURE_ID')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_NAME = CDPL.Base.LookupKey(id=32, name='MOL2_SUBSTRUCTURE_NAME')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_SUBTYPE = CDPL.Base.LookupKey(id=33, name='MOL2_SUBSTRUCTURE_SUBTYPE')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_CHAIN = CDPL.Base.LookupKey(id=34, name='MOL2_SUBSTRUCTURE_CHAIN')

    ##
    # \brief 
    #
    PEOE_CHARGE = CDPL.Base.LookupKey(id=35, name='PEOE_CHARGE')

    ##
    # \brief 
    #
    REACTION_CENTER_STATUS = CDPL.Base.LookupKey(id=36, name='REACTION_CENTER_STATUS')

    ##
    # \brief 
    #
    ATOM_MAPPING_ID = CDPL.Base.LookupKey(id=37, name='ATOM_MAPPING_ID')

    ##
    # \brief 
    #
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey(id=38, name='MATCH_CONSTRAINTS')

    ##
    # \brief 
    #
    MATCH_EXPRESSION = CDPL.Base.LookupKey(id=39, name='MATCH_EXPRESSION')

    ##
    # \brief 
    #
    MATCH_EXPRESSION_STRING = CDPL.Base.LookupKey(id=40, name='MATCH_EXPRESSION_STRING')

    ##
    # \brief 
    #
    COMPONENT_GROUP_ID = CDPL.Base.LookupKey(id=41, name='COMPONENT_GROUP_ID')
