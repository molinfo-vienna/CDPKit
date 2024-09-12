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
# \brief Provides keys for built-in control-parameters.
# 
class ControlParameter(Boost.Python.instance):

    ##
    # \brief Specifies whether non-fatal recoverable I/O errors should be ignored or cause an I/O operation to fail.
    # 
    # If the control-parameter is set to <tt>True</tt>, not only severe errors cause an I/O operation to fail, but also non-fatal errors from which a recovery would be possible. If the control-parameter is set to <tt>False</tt>, I/O operations will proceed even if a non-fatal error has been detected.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    STRICT_ERROR_CHECKING = CDPL.Base.LookupKey('STRICT_ERROR_CHECKING')

    ##
    # \brief Specifies whether to check if data lines exceed the maximum allowed line length when reading or writing data in <em>PDB</em> [\ref PDB] format.
    # 
    # If the control-parameter is set to <tt>True</tt>, the length of data lines that were read from or have to be written to data encoded in one of the above mentioned formats will be checked against the maximum allowed line length. Lines that exceeded the line length limit are considered as an error condition and cause the input or output operation to fail. If <tt>CHECK_LINE_LENGTH</tt> is <tt>False</tt>, the length of data lines will not be checked and has no impact on the success of the performed I/O operation.
    # 
    # <b>Value Type:</b> <tt>bool</tt>
    # 
    CHECK_LINE_LENGTH = CDPL.Base.LookupKey('CHECK_LINE_LENGTH')

    ##
    # \brief 
    #
    RESIDUE_DICTIONARY = CDPL.Base.LookupKey('RESIDUE_DICTIONARY')

    ##
    # \brief 
    #
    APPLY_DICT_FORMAL_CHARGES = CDPL.Base.LookupKey('APPLY_DICT_FORMAL_CHARGES')

    ##
    # \brief 
    #
    APPLY_DICT_ATOM_TYPES = CDPL.Base.LookupKey('APPLY_DICT_ATOM_TYPES')

    ##
    # \brief 
    #
    CALC_MISSING_FORMAL_CHARGES = CDPL.Base.LookupKey('CALC_MISSING_FORMAL_CHARGES')

    ##
    # \brief 
    #
    PERCEIVE_MISSING_BOND_ORDERS = CDPL.Base.LookupKey('PERCEIVE_MISSING_BOND_ORDERS')

    ##
    # \brief 
    #
    COMBINE_INTERFERING_RESIDUE_COORDINATES = CDPL.Base.LookupKey('COMBINE_INTERFERING_RESIDUE_COORDINATES')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES = CDPL.Base.LookupKey('PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES = CDPL.Base.LookupKey('PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES')

    ##
    # \brief 
    #
    PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES = CDPL.Base.LookupKey('PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES')

    ##
    # \brief 
    #
    PDB_IGNORE_CONECT_RECORDS = CDPL.Base.LookupKey('PDB_IGNORE_CONECT_RECORDS')

    ##
    # \brief 
    #
    PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS = CDPL.Base.LookupKey('PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS')

    ##
    # \brief 
    #
    PDB_IGNORE_FORMAL_CHARGE_FIELD = CDPL.Base.LookupKey('PDB_IGNORE_FORMAL_CHARGE_FIELD')

    ##
    # \brief 
    #
    PDB_EVALUATE_MASTER_RECORD = CDPL.Base.LookupKey('PDB_EVALUATE_MASTER_RECORD')

    ##
    # \brief 
    #
    PDB_TRUNCATE_LINES = CDPL.Base.LookupKey('PDB_TRUNCATE_LINES')

    ##
    # \brief 
    #
    PDB_WRITE_FORMAL_CHARGES = CDPL.Base.LookupKey('PDB_WRITE_FORMAL_CHARGES')

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS = CDPL.Base.LookupKey('PDB_WRITE_CONECT_RECORDS')

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS = CDPL.Base.LookupKey('PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS')

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER = CDPL.Base.LookupKey('PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER')

    ##
    # \brief 
    #
    PDB_FORMAT_VERSION = CDPL.Base.LookupKey('PDB_FORMAT_VERSION')

    ##
    # \brief 
    #
    MMCIF_APPLY_DICT_ATOM_BONDING = CDPL.Base.LookupKey('MMCIF_APPLY_DICT_ATOM_BONDING')

    ##
    # \brief 
    #
    MMCIF_APPLY_DICT_BOND_ORDERS = CDPL.Base.LookupKey('MMCIF_APPLY_DICT_BOND_ORDERS')
