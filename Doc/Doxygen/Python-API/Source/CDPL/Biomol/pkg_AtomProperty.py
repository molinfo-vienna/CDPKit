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
    RESIDUE_ATOM_NAME = CDPL.Base.LookupKey(id=265, name='RESIDUE_ATOM_NAME')

    ##
    # \brief 
    #
    RESIDUE_ALT_ATOM_NAME = CDPL.Base.LookupKey(id=266, name='RESIDUE_ALT_ATOM_NAME')

    ##
    # \brief 
    #
    RESIDUE_LEAVING_ATOM_FLAG = CDPL.Base.LookupKey(id=267, name='RESIDUE_LEAVING_ATOM_FLAG')

    ##
    # \brief 
    #
    RESIDUE_LINKING_ATOM_FLAG = CDPL.Base.LookupKey(id=268, name='RESIDUE_LINKING_ATOM_FLAG')

    ##
    # \brief 
    #
    RESIDUE_CODE = CDPL.Base.LookupKey(id=269, name='RESIDUE_CODE')

    ##
    # \brief 
    #
    RESIDUE_SEQUENCE_NUMBER = CDPL.Base.LookupKey(id=270, name='RESIDUE_SEQUENCE_NUMBER')

    ##
    # \brief 
    #
    RESIDUE_INSERTION_CODE = CDPL.Base.LookupKey(id=271, name='RESIDUE_INSERTION_CODE')

    ##
    # \brief 
    #
    HETERO_ATOM_FLAG = CDPL.Base.LookupKey(id=272, name='HETERO_ATOM_FLAG')

    ##
    # \brief 
    #
    CHAIN_ID = CDPL.Base.LookupKey(id=273, name='CHAIN_ID')

    ##
    # \brief 
    #
    ALT_LOCATION_ID = CDPL.Base.LookupKey(id=274, name='ALT_LOCATION_ID')

    ##
    # \brief 
    #
    MODEL_NUMBER = CDPL.Base.LookupKey(id=275, name='MODEL_NUMBER')

    ##
    # \brief 
    #
    SERIAL_NUMBER = CDPL.Base.LookupKey(id=276, name='SERIAL_NUMBER')

    ##
    # \brief 
    #
    OCCUPANCY = CDPL.Base.LookupKey(id=277, name='OCCUPANCY')

    ##
    # \brief 
    #
    B_FACTOR = CDPL.Base.LookupKey(id=278, name='B_FACTOR')
