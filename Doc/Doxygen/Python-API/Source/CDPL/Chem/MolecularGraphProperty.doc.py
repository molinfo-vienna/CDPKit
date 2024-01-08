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
# \brief Provides keys for built-in Chem.MolecularGraph properties.
# 
class MolecularGraphProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    NAME = CDPL.Base.LookupKey('NAME')

    ##
    # \brief 
    #
    COMMENT = CDPL.Base.LookupKey('COMMENT')

    ##
    # \brief 
    #
    TIMESTAMP = CDPL.Base.LookupKey('TIMESTAMP')

    ##
    # \brief 
    #
    COMPONENTS = CDPL.Base.LookupKey('COMPONENTS')

    ##
    # \brief 
    #
    RINGS = CDPL.Base.LookupKey('RINGS')

    ##
    # \brief 
    #
    SSSR = CDPL.Base.LookupKey('SSSR')

    ##
    # \brief 
    #
    CYCLIC_SUBSTRUCTURE = CDPL.Base.LookupKey('CYCLIC_SUBSTRUCTURE')

    ##
    # \brief 
    #
    AROMATIC_SUBSTRUCTURE = CDPL.Base.LookupKey('AROMATIC_SUBSTRUCTURE')

    ##
    # \brief 
    #
    PI_ELECTRON_SYSTEMS = CDPL.Base.LookupKey('PI_ELECTRON_SYSTEMS')

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
    COMPONENT_GROUPS = CDPL.Base.LookupKey('COMPONENT_GROUPS')

    ##
    # \brief 
    #
    TOPOLOGICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey('TOPOLOGICAL_DISTANCE_MATRIX')

    ##
    # \brief 
    #
    GEOMETRICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey('GEOMETRICAL_DISTANCE_MATRIX')

    ##
    # \brief 
    #
    STOICHIOMETRIC_NUMBER = CDPL.Base.LookupKey('STOICHIOMETRIC_NUMBER')

    ##
    # \brief 
    #
    CONFORMATION_INDEX = CDPL.Base.LookupKey('CONFORMATION_INDEX')

    ##
    # \brief 
    #
    CONFORMER_ENERGIES = CDPL.Base.LookupKey('CONFORMER_ENERGIES')

    ##
    # \brief 
    #
    STRUCTURE_DATA = CDPL.Base.LookupKey('STRUCTURE_DATA')

    ##
    # \brief 
    #
    HASH_CODE = CDPL.Base.LookupKey('HASH_CODE')

    ##
    # \brief 
    #
    MDL_USER_INITIALS = CDPL.Base.LookupKey('MDL_USER_INITIALS')

    ##
    # \brief 
    #
    MDL_PROGRAM_NAME = CDPL.Base.LookupKey('MDL_PROGRAM_NAME')

    ##
    # \brief 
    #
    MDL_REGISTRY_NUMBER = CDPL.Base.LookupKey('MDL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_CTAB_VERSION = CDPL.Base.LookupKey('MDL_CTAB_VERSION')

    ##
    # \brief 
    #
    MDL_DIMENSIONALITY = CDPL.Base.LookupKey('MDL_DIMENSIONALITY')

    ##
    # \brief 
    #
    MDL_SCALING_FACTOR1 = CDPL.Base.LookupKey('MDL_SCALING_FACTOR1')

    ##
    # \brief 
    #
    MDL_SCALING_FACTOR2 = CDPL.Base.LookupKey('MDL_SCALING_FACTOR2')

    ##
    # \brief 
    #
    MDL_ENERGY = CDPL.Base.LookupKey('MDL_ENERGY')

    ##
    # \brief 
    #
    MDL_CHIRAL_FLAG = CDPL.Base.LookupKey('MDL_CHIRAL_FLAG')

    ##
    # \brief 
    #
    MOL2_CHARGE_TYPE = CDPL.Base.LookupKey('MOL2_CHARGE_TYPE')

    ##
    # \brief 
    #
    MOL2_MOLECULE_TYPE = CDPL.Base.LookupKey('MOL2_MOLECULE_TYPE')
