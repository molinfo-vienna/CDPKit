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
    # \valuetype  <tt>bool</tt>
    # 
    STRICT_ERROR_CHECKING = CDPL.Base.LookupKey('STRICT_ERROR_CHECKING')

    ##
    # \brief Specifies whether to check if data lines exceed the maximum allowed line length when reading or writing data in <em>PDB</em> [\ref PDB] format.
    # 
    # If the control-parameter is set to <tt>True</tt>, the length of data lines that were read from or have to be written to data encoded in one of the above mentioned formats will be checked against the maximum allowed line length. Lines that exceeded the line length limit are considered as an error condition and cause the input or output operation to fail. If <tt>CHECK_LINE_LENGTH</tt> is <tt>False</tt>, the length of data lines will not be checked and has no impact on the success of the performed I/O operation.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    CHECK_LINE_LENGTH = CDPL.Base.LookupKey('CHECK_LINE_LENGTH')

    ##
    # \brief Specifies the residue dictionary consulted during <em>PDB</em> and <em>mmCIF</em> I/O when looking up canonical residue atom names, bonding, atom types, or formal charges.
    # 
    # \valuetype  Biomol.ResidueDictionary.SharedPointer \since 1.2
    # 
    RESIDUE_DICTIONARY = CDPL.Base.LookupKey('RESIDUE_DICTIONARY')

    ##
    # \brief Specifies whether to apply the formal atom charges provided by the residue dictionary during input data post-processing.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    APPLY_DICT_FORMAL_CHARGES = CDPL.Base.LookupKey('APPLY_DICT_FORMAL_CHARGES')

    ##
    # \brief Specifies whether to apply the atom types provided by the residue dictionary during input data post-processing.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    APPLY_DICT_ATOM_TYPES = CDPL.Base.LookupKey('APPLY_DICT_ATOM_TYPES')

    ##
    # \brief Specifies whether to calculate formal atomic charges for atoms whose charge could not be obtained from the input data or the residue dictionary.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    CALC_MISSING_FORMAL_CHARGES = CDPL.Base.LookupKey('CALC_MISSING_FORMAL_CHARGES')

    ##
    # \brief Specifies whether to perceive bond orders for bonds whose order could not be obtained from the input data or the residue dictionary.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    PERCEIVE_MISSING_BOND_ORDERS = CDPL.Base.LookupKey('PERCEIVE_MISSING_BOND_ORDERS')

    ##
    # \brief Specifies whether to merge alternative residue conformers whose atoms overlap in space (see Biomol.combineInterferingResidueCoordinates()).
    # 
    # \valuetype  <tt>bool</tt>
    # 
    COMBINE_INTERFERING_RESIDUE_COORDINATES = CDPL.Base.LookupKey('COMBINE_INTERFERING_RESIDUE_COORDINATES')

    ##
    # \brief Specifies whether to use the residue dictionary to derive atom-bonding for atoms of non-standard residues when reading <em>PDB</em> data.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES = CDPL.Base.LookupKey('PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES')

    ##
    # \brief Specifies whether to use the residue dictionary to derive atom-bonding for atoms of standard residues when reading <em>PDB</em> data.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES = CDPL.Base.LookupKey('PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES')

    ##
    # \brief Specifies whether to apply the residue-dictionary bond orders to bonds of non-standard residues when reading <em>PDB</em> data.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES = CDPL.Base.LookupKey('PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES')

    ##
    # \brief Specifies whether to skip <tt>CONECT</tt> records when reading <em>PDB</em> data.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_IGNORE_CONECT_RECORDS = CDPL.Base.LookupKey('PDB_IGNORE_CONECT_RECORDS')

    ##
    # \brief Specifies whether to deduce bond orders from the duplication pattern of bonded atom pairs in <tt>CONECT</tt> records when reading <em>PDB</em> data.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS = CDPL.Base.LookupKey('PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS')

    ##
    # \brief Specifies whether to ignore the formal-charge field of <tt>ATOM/<tt>HETATM</tt> records</tt> when reading <em>PDB</em> data.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_IGNORE_FORMAL_CHARGE_FIELD = CDPL.Base.LookupKey('PDB_IGNORE_FORMAL_CHARGE_FIELD')

    ##
    # \brief Specifies whether to verify the record counts in the <em>PDB</em> <tt>MASTER</tt> record against the actual numbers observed during input.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_EVALUATE_MASTER_RECORD = CDPL.Base.LookupKey('PDB_EVALUATE_MASTER_RECORD')

    ##
    # \brief Specifies whether to truncate output <em>PDB</em> data lines that exceed the maximum allowed line length instead of failing the write operation.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    PDB_TRUNCATE_LINES = CDPL.Base.LookupKey('PDB_TRUNCATE_LINES')

    ##
    # \brief 
    #
    PDB_WRITE_FORMAL_CHARGES = CDPL.Base.LookupKey('PDB_OUTPUT_FORMAL_CHARGES')

    ##
    # \brief Specifies whether to write <tt>CONECT</tt> records when generating <em>PDB</em> output.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    PDB_OUTPUT_CONECT_RECORDS = CDPL.Base.LookupKey('PDB_OUTPUT_CONECT_RECORDS')

    ##
    # \brief Specifies whether <tt>CONECT</tt> records shall be written for all bonds (and not only for non-standard ones) when generating <em>PDB</em> output.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS = CDPL.Base.LookupKey('PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS')

    ##
    # \brief Specifies whether <tt>CONECT</tt> records shall encode the bond order via the duplication count of bonded atom pairs when generating <em>PDB</em> output.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER = CDPL.Base.LookupKey('PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER')

    ##
    # \brief Specifies the <em>PDB</em> format version to use when generating <em>PDB</em> output (see Biomol.PDBFormatVersion).
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    PDB_FORMAT_VERSION = CDPL.Base.LookupKey('PDB_FORMAT_VERSION')

    ##
    # \brief Specifies whether to use the residue dictionary to derive atom-bonding when reading <em>mmCIF</em> data.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    MMCIF_APPLY_DICT_ATOM_BONDING = CDPL.Base.LookupKey('MMCIF_APPLY_DICT_ATOM_BONDING')

    ##
    # \brief Specifies whether to apply the residue-dictionary bond orders when reading <em>mmCIF</em> data.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    MMCIF_APPLY_DICT_BOND_ORDERS = CDPL.Base.LookupKey('MMCIF_APPLY_DICT_BOND_ORDERS')

    ##
    # \brief Specifies whether to emit biopolymer residues using the <tt>chem_comp</tt> data category (instead of the regular polymer-residue encoding) when generating <em>mmCIF</em> output.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP = CDPL.Base.LookupKey('MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP')

    ##
    # \brief Specifies a post-processing function that is applied to the constructed <em>mmCIF</em> data record before it is written to the output stream.
    # 
    # \valuetype  Biomol.MMCIFDataProcessingFunction \since 1.2
    # 
    MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION = CDPL.Base.LookupKey('MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION')
