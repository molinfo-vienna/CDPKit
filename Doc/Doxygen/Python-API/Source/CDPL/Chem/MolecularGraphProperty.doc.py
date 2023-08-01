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
    NAME = CDPL.Base.LookupKey(id=50, name='NAME')

    ##
    # \brief 
    #
    COMPONENTS = CDPL.Base.LookupKey(id=51, name='COMPONENTS')

    ##
    # \brief 
    #
    RINGS = CDPL.Base.LookupKey(id=52, name='RINGS')

    ##
    # \brief 
    #
    SSSR = CDPL.Base.LookupKey(id=53, name='SSSR')

    ##
    # \brief 
    #
    CYCLIC_SUBSTRUCTURE = CDPL.Base.LookupKey(id=54, name='CYCLIC_SUBSTRUCTURE')

    ##
    # \brief 
    #
    AROMATIC_SUBSTRUCTURE = CDPL.Base.LookupKey(id=55, name='AROMATIC_SUBSTRUCTURE')

    ##
    # \brief 
    #
    PI_ELECTRON_SYSTEMS = CDPL.Base.LookupKey(id=56, name='PI_ELECTRON_SYSTEMS')

    ##
    # \brief 
    #
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey(id=57, name='MATCH_CONSTRAINTS')

    ##
    # \brief 
    #
    MATCH_EXPRESSION = CDPL.Base.LookupKey(id=58, name='MATCH_EXPRESSION')

    ##
    # \brief 
    #
    COMPONENT_GROUPS = CDPL.Base.LookupKey(id=59, name='COMPONENT_GROUPS')

    ##
    # \brief 
    #
    TOPOLOGICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey(id=60, name='TOPOLOGICAL_DISTANCE_MATRIX')

    ##
    # \brief 
    #
    GEOMETRICAL_DISTANCE_MATRIX = CDPL.Base.LookupKey(id=61, name='GEOMETRICAL_DISTANCE_MATRIX')

    ##
    # \brief 
    #
    STOICHIOMETRIC_NUMBER = CDPL.Base.LookupKey(id=62, name='STOICHIOMETRIC_NUMBER')

    ##
    # \brief 
    #
    CONFORMATION_INDEX = CDPL.Base.LookupKey(id=63, name='CONFORMATION_INDEX')

    ##
    # \brief 
    #
    CONFORMER_ENERGIES = CDPL.Base.LookupKey(id=64, name='CONFORMER_ENERGIES')

    ##
    # \brief 
    #
    STRUCTURE_DATA = CDPL.Base.LookupKey(id=65, name='STRUCTURE_DATA')

    ##
    # \brief 
    #
    HASH_CODE = CDPL.Base.LookupKey(id=66, name='HASH_CODE')

    ##
    # \brief 
    #
    MDL_USER_INITIALS = CDPL.Base.LookupKey(id=67, name='MDL_USER_INITIALS')

    ##
    # \brief 
    #
    MDL_PROGRAM_NAME = CDPL.Base.LookupKey(id=68, name='MDL_PROGRAM_NAME')

    ##
    # \brief 
    #
    MDL_TIMESTAMP = CDPL.Base.LookupKey(id=69, name='MDL_TIMESTAMP')

    ##
    # \brief 
    #
    MDL_REGISTRY_NUMBER = CDPL.Base.LookupKey(id=74, name='MDL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_COMMENT = CDPL.Base.LookupKey(id=75, name='MDL_COMMENT')

    ##
    # \brief 
    #
    MDL_CTAB_VERSION = CDPL.Base.LookupKey(id=77, name='MDL_CTAB_VERSION')

    ##
    # \brief 
    #
    MDL_DIMENSIONALITY = CDPL.Base.LookupKey(id=70, name='MDL_DIMENSIONALITY')

    ##
    # \brief 
    #
    MDL_SCALING_FACTOR1 = CDPL.Base.LookupKey(id=71, name='MDL_SCALING_FACTOR1')

    ##
    # \brief 
    #
    MDL_SCALING_FACTOR2 = CDPL.Base.LookupKey(id=72, name='MDL_SCALING_FACTOR2')

    ##
    # \brief 
    #
    MDL_ENERGY = CDPL.Base.LookupKey(id=73, name='MDL_ENERGY')

    ##
    # \brief 
    #
    MDL_CHIRAL_FLAG = CDPL.Base.LookupKey(id=76, name='MDL_CHIRAL_FLAG')

    ##
    # \brief 
    #
    MOL2_CHARGE_TYPE = CDPL.Base.LookupKey(id=78, name='MOL2_CHARGE_TYPE')

    ##
    # \brief 
    #
    MOL2_MOLECULE_TYPE = CDPL.Base.LookupKey(id=79, name='MOL2_MOLECULE_TYPE')
