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
class ControlParameter(Boost.Python.instance):

    ##
    # \brief 
    #
    STRICT_ERROR_CHECKING = CDPL.Base.LookupKey(id=286, name='STRICT_ERROR_CHECKING')

    ##
    # \brief 
    #
    CHECK_LINE_LENGTH = CDPL.Base.LookupKey(id=287, name='CHECK_LINE_LENGTH')

    ##
    # \brief 
    #
    PDB_RESIDUE_DICTIONARY = CDPL.Base.LookupKey(id=288, name='PDB_RESIDUE_DICTIONARY')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES = CDPL.Base.LookupKey(id=289, name='PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES = CDPL.Base.LookupKey(id=290, name='PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES = CDPL.Base.LookupKey(id=291, name='PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES')

    ##
    # \brief 
    #
    PDB_IGNORE_CONECT_RECORDS = CDPL.Base.LookupKey(id=293, name='PDB_IGNORE_CONECT_RECORDS')

    ##
    # \brief 
    #
    PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS = CDPL.Base.LookupKey(id=294, name='PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS')

    ##
    # \brief 
    #
    PDB_IGNORE_FORMAL_CHARGE_FIELD = CDPL.Base.LookupKey(id=295, name='PDB_IGNORE_FORMAL_CHARGE_FIELD')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_FORMAL_ATOM_CHARGES = CDPL.Base.LookupKey(id=296, name='PDB_APPLY_DICT_FORMAL_ATOM_CHARGES')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_TYPES = CDPL.Base.LookupKey(id=297, name='PDB_APPLY_DICT_ATOM_TYPES')

    ##
    # \brief 
    #
    PDB_CALC_MISSING_FORMAL_CHARGES = CDPL.Base.LookupKey(id=298, name='PDB_CALC_MISSING_FORMAL_CHARGES')

    ##
    # \brief 
    #
    PDB_PERCEIVE_MISSING_BOND_ORDERS = CDPL.Base.LookupKey(id=299, name='PDB_PERCEIVE_MISSING_BOND_ORDERS')

    ##
    # \brief 
    #
    PDB_EVALUATE_MASTER_RECORD = CDPL.Base.LookupKey(id=300, name='PDB_EVALUATE_MASTER_RECORD')

    ##
    # \brief 
    #
    PDB_TRUNCATE_LINES = CDPL.Base.LookupKey(id=301, name='PDB_TRUNCATE_LINES')

    ##
    # \brief 
    #
    PDB_WRITE_FORMAL_CHARGES = CDPL.Base.LookupKey(id=302, name='PDB_WRITE_FORMAL_CHARGES')

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS = CDPL.Base.LookupKey(id=303, name='PDB_WRITE_CONECT_RECORDS')

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS = CDPL.Base.LookupKey(id=304, name='PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS')

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER = CDPL.Base.LookupKey(id=305, name='PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER')

    ##
    # \brief 
    #
    PDB_FORMAT_VERSION = CDPL.Base.LookupKey(id=306, name='PDB_FORMAT_VERSION')

    ##
    # \brief 
    #
    COMBINE_INTERFERING_RESIDUE_COORDINATES = CDPL.Base.LookupKey(id=307, name='COMBINE_INTERFERING_RESIDUE_COORDINATES')
