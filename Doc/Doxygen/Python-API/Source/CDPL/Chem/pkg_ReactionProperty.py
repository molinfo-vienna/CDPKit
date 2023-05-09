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
# \brief 
#
class ReactionProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    NAME = CDPL.Base.LookupKey(id=80, name='NAME')

    ##
    # \brief 
    #
    MATCH_EXPRESSION = CDPL.Base.LookupKey(id=81, name='MATCH_EXPRESSION')

    ##
    # \brief 
    #
    MATCH_CONSTRAINTS = CDPL.Base.LookupKey(id=82, name='MATCH_CONSTRAINTS')

    ##
    # \brief 
    #
    COMPONENT_GROUPS = CDPL.Base.LookupKey(id=83, name='COMPONENT_GROUPS')

    ##
    # \brief 
    #
    ATOM_MAPPING = CDPL.Base.LookupKey(id=84, name='ATOM_MAPPING')

    ##
    # \brief 
    #
    REACTION_DATA = CDPL.Base.LookupKey(id=85, name='REACTION_DATA')

    ##
    # \brief 
    #
    MDL_USER_INITIALS = CDPL.Base.LookupKey(id=86, name='MDL_USER_INITIALS')

    ##
    # \brief 
    #
    MDL_PROGRAM_NAME = CDPL.Base.LookupKey(id=87, name='MDL_PROGRAM_NAME')

    ##
    # \brief 
    #
    MDL_TIMESTAMP = CDPL.Base.LookupKey(id=88, name='MDL_TIMESTAMP')

    ##
    # \brief 
    #
    MDL_REGISTRY_NUMBER = CDPL.Base.LookupKey(id=89, name='MDL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_COMMENT = CDPL.Base.LookupKey(id=90, name='MDL_COMMENT')

    ##
    # \brief 
    #
    MDL_MOLECULE_RECORD = CDPL.Base.LookupKey(id=91, name='MDL_MOLECULE_RECORD')

    ##
    # \brief 
    #
    MDL_INTERNAL_REGISTRY_NUMBER = CDPL.Base.LookupKey(id=92, name='MDL_INTERNAL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_EXTERNAL_REGISTRY_NUMBER = CDPL.Base.LookupKey(id=93, name='MDL_EXTERNAL_REGISTRY_NUMBER')

    ##
    # \brief 
    #
    MDL_RXN_FILE_VERSION = CDPL.Base.LookupKey(id=94, name='MDL_RXN_FILE_VERSION')
