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
class MolecularGraphProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    RESIDUE_CODE = CDPL.Base.LookupKey(id=279, name='RESIDUE_CODE')

    ##
    # \brief 
    #
    RESIDUE_SEQUENCE_NUMBER = CDPL.Base.LookupKey(id=280, name='RESIDUE_SEQUENCE_NUMBER')

    ##
    # \brief 
    #
    RESIDUE_INSERTION_CODE = CDPL.Base.LookupKey(id=281, name='RESIDUE_INSERTION_CODE')

    ##
    # \brief 
    #
    CHAIN_ID = CDPL.Base.LookupKey(id=282, name='CHAIN_ID')

    ##
    # \brief 
    #
    MODEL_NUMBER = CDPL.Base.LookupKey(id=283, name='MODEL_NUMBER')

    ##
    # \brief 
    #
    PDB_DATA = CDPL.Base.LookupKey(id=284, name='PDB_DATA')
