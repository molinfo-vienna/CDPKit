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
# \brief Provides keys for built-in Chem.Atom properties.
# 
class AtomProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    NAME = CDPL.Base.LookupKey('NAME')

    ##
    # \brief 
    #
    SYMBOL = CDPL.Base.LookupKey('SYMBOL')

    ##
    # \brief 
    #
    TYPE = CDPL.Base.LookupKey('TYPE')

    ##
    # \brief 
    #
    FORMAL_CHARGE = CDPL.Base.LookupKey('FORMAL_CHARGE')

    ##
    # \brief 
    #
    ISOTOPE = CDPL.Base.LookupKey('ISOTOPE')

    ##
    # \brief 
    #
    RADICAL_TYPE = CDPL.Base.LookupKey('RADICAL_TYPE')

    ##
    # \brief 
    #
    HYBRIDIZATION = CDPL.Base.LookupKey('HYBRIDIZATION')

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
    UNPAIRED_ELECTRON_COUNT = CDPL.Base.LookupKey('UNPAIRED_ELECTRON_COUNT')

    ##
    # \brief 
    #
    IMPLICIT_HYDROGEN_COUNT = CDPL.Base.LookupKey('IMPLICIT_HYDROGEN_COUNT')

    ##
    # \brief 
    #
    COORDINATES_2D = CDPL.Base.LookupKey('COORDINATES_2D')

    ##
    # \brief 
    #
    COORDINATES_3D_ARRAY = CDPL.Base.LookupKey('COORDINATES_3D_ARRAY')

    ##
    # \brief 
    #
    MORGAN_NUMBER = CDPL.Base.LookupKey('MORGAN_NUMBER')

    ##
    # \brief 
    #
    CANONICAL_NUMBER = CDPL.Base.LookupKey('CANONICAL_NUMBER')

    ##
    # \brief 
    #
    CIP_PRIORITY = CDPL.Base.LookupKey('CIP_PRIORITY')

    ##
    # \brief 
    #
    SYMMETRY_CLASS = CDPL.Base.LookupKey('SYMMETRY_CLASS')

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
    MDL_PARITY = CDPL.Base.LookupKey('MDL_PARITY')

    ##
    # \brief 
    #
    MDL_DB_STEREO_CARE_FLAG = CDPL.Base.LookupKey('MDL_DB_STEREO_CARE_FLAG')

    ##
    # \brief 
    #
    SYBYL_TYPE = CDPL.Base.LookupKey('SYBYL_TYPE')

    ##
    # \brief 
    #
    MOL2_NAME = CDPL.Base.LookupKey('MOL2_NAME')

    ##
    # \brief 
    #
    MOL2_CHARGE = CDPL.Base.LookupKey('MOL2_CHARGE')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_ID = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_ID')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_NAME = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_NAME')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_SUBTYPE = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_SUBTYPE')

    ##
    # \brief 
    #
    MOL2_SUBSTRUCTURE_CHAIN = CDPL.Base.LookupKey('MOL2_SUBSTRUCTURE_CHAIN')

    ##
    # \brief 
    #
    REACTION_CENTER_STATUS = CDPL.Base.LookupKey('REACTION_CENTER_STATUS')

    ##
    # \brief 
    #
    ATOM_MAPPING_ID = CDPL.Base.LookupKey('ATOM_MAPPING_ID')

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

    ##
    # \brief 
    #
    COMPONENT_GROUP_ID = CDPL.Base.LookupKey('COMPONENT_GROUP_ID')
