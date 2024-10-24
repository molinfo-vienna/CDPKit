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
# \brief Provides default values for built-in control-parameters.
# 
class ControlParameterDefault(Boost.Python.instance):

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Biomol.ControlParameter.STRICT_ERROR_CHECKING.
    # 
    STRICT_ERROR_CHECKING = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Biomol.ControlParameter.CHECK_LINE_LENGTH.
    # 
    CHECK_LINE_LENGTH = False

    ##
    # \brief 
    #
    RESIDUE_DICTIONARY = None

    ##
    # \brief 
    #
    COMBINE_INTERFERING_RESIDUE_COORDINATES = True

    ##
    # \brief 
    #
    APPLY_DICT_FORMAL_CHARGES = True

    ##
    # \brief 
    #
    APPLY_DICT_ATOM_TYPES = True

    ##
    # \brief 
    #
    CALC_MISSING_FORMAL_CHARGES = False

    ##
    # \brief 
    #
    PERCEIVE_MISSING_BOND_ORDERS = True

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES = False

    ##
    # \brief 
    #
    PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES = True

    ##
    # \brief 
    #
    PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES = True

    ##
    # \brief 
    #
    PDB_IGNORE_CONECT_RECORDS = False

    ##
    # \brief 
    #
    PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS = False

    ##
    # \brief 
    #
    PDB_IGNORE_FORMAL_CHARGE_FIELD = False

    ##
    # \brief 
    #
    PDB_EVALUATE_MASTER_RECORD = False

    ##
    # \brief 
    #
    PDB_TRUNCATE_LINES = False

    ##
    # \brief 
    #
    PDB_WRITE_FORMAL_CHARGES = True

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS = True

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS_FOR_ALL_BONDS = False

    ##
    # \brief 
    #
    PDB_WRITE_CONECT_RECORDS_REFLECTING_BOND_ORDER = False

    ##
    # \brief 
    #
    PDB_FORMAT_VERSION = 3

    ##
    # \brief 
    #
    MMCIF_APPLY_DICT_ATOM_BONDING = True

    ##
    # \brief 
    #
    MMCIF_APPLY_DICT_BOND_ORDERS = True

    ##
    # \brief 
    #
    MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP = False

    ##
    # \brief 
    #
    MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION = _HIDDEN_VALUE_
