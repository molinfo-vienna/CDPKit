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
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.STRICT_ERROR_CHECKING.
    # 
    STRICT_ERROR_CHECKING = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.CHECK_LINE_LENGTH.
    # 
    CHECK_LINE_LENGTH = False

    ##
    # \brief Default value (= <tt>ResidueDictionary.SharedPointer()</tt>) of the control-parameter Biomol.ControlParameter.RESIDUE_DICTIONARY (an empty shared reference selects the built-in default dictionary).
    # 
    # \since 1.2
    # 
    RESIDUE_DICTIONARY = None

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.COMBINE_INTERFERING_RESIDUE_COORDINATES.
    # 
    COMBINE_INTERFERING_RESIDUE_COORDINATES = True

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.APPLY_DICT_FORMAL_CHARGES.
    # 
    # \since 1.2
    # 
    APPLY_DICT_FORMAL_CHARGES = True

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.APPLY_DICT_ATOM_TYPES.
    # 
    # \since 1.2
    # 
    APPLY_DICT_ATOM_TYPES = True

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.CALC_MISSING_FORMAL_CHARGES.
    # 
    # \since 1.2
    # 
    CALC_MISSING_FORMAL_CHARGES = False

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.PERCEIVE_MISSING_BOND_ORDERS.
    # 
    # \since 1.2
    # 
    PERCEIVE_MISSING_BOND_ORDERS = True

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES.
    # 
    PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES = False

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES.
    # 
    PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES = True

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES.
    # 
    PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES = True

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_IGNORE_CONECT_RECORDS.
    # 
    PDB_IGNORE_CONECT_RECORDS = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS.
    # 
    PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_IGNORE_FORMAL_CHARGE_FIELD.
    # 
    PDB_IGNORE_FORMAL_CHARGE_FIELD = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_EVALUATE_MASTER_RECORD.
    # 
    PDB_EVALUATE_MASTER_RECORD = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_TRUNCATE_LINES.
    # 
    PDB_TRUNCATE_LINES = False

    ##
    # \brief 
    #
    PDB_WRITE_FORMAL_CHARGES = True

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS.
    # 
    # \since 1.2
    # 
    PDB_OUTPUT_CONECT_RECORDS = True

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS.
    # 
    # \since 1.2
    # 
    PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS = False

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER.
    # 
    # \since 1.2
    # 
    PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER = False

    ##
    # \brief Default value (= Biomol.PDBFormatVersion.V3) of the control-parameter Biomol.ControlParameter.PDB_FORMAT_VERSION.
    # 
    PDB_FORMAT_VERSION = 3

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.MMCIF_APPLY_DICT_ATOM_BONDING.
    # 
    # \since 1.2
    # 
    MMCIF_APPLY_DICT_ATOM_BONDING = True

    ##
    # \brief Default value (= <tt>True</tt>) of the control-parameter Biomol.ControlParameter.MMCIF_APPLY_DICT_BOND_ORDERS.
    # 
    # \since 1.2
    # 
    MMCIF_APPLY_DICT_BOND_ORDERS = True

    ##
    # \brief Default value (= <tt>False</tt>) of the control-parameter Biomol.ControlParameter.MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP.
    # 
    # \since 1.2
    # 
    MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP = False

    ##
    # \brief Default value (= <tt>MMCIFDataProcessingFunction()</tt>) of the control-parameter Biomol.ControlParameter.MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION.
    # 
    # \since 1.2
    # 
    MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION = _HIDDEN_VALUE_
