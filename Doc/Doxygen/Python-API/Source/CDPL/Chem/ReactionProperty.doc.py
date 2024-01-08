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
# \brief Provides keys for built-in Chem.Reaction properties.
# 
class ReactionProperty(Boost.Python.instance):

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
    MATCH_EXPRESSION = CDPL.Base.LookupKey('MATCH_EXPRESSION')

    ##
    # \brief 
    #
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey('MATCH_CONSTRAINTS')

    ##
    # \brief 
    #
    COMPONENT_GROUPS = CDPL.Base.LookupKey('COMPONENT_GROUPS')

    ##
    # \brief 
    #
    ATOM_MAPPING = CDPL.Base.LookupKey('ATOM_MAPPING')

    ##
    # \brief 
    #
    REACTION_DATA = CDPL.Base.LookupKey('REACTION_DATA')

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
    MDL_MOLECULE_RECORD = CDPL.Base.LookupKey('MDL_MOLECULE_RECORD')

    ##
    # \brief 
    #
    MDL_INTERNAL_REGISTRY_NUMBER = CDPL.Base.LookupKey('MDL_INTERNAL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_EXTERNAL_REGISTRY_NUMBER = CDPL.Base.LookupKey('MDL_EXTERNAL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_RXN_FILE_VERSION = CDPL.Base.LookupKey('MDL_RXN_FILE_VERSION')
