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
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.STRICT_ERROR_CHECKING.
    # 
    STRICT_ERROR_CHECKING = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.ORDINARY_HYDROGEN_DEPLETE.
    # 
    ORDINARY_HYDROGEN_DEPLETE = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.BOND_MEMBER_SWAP_STEREO_FIX.
    # 
    BOND_MEMBER_SWAP_STEREO_FIX = True

    ##
    # \brief Default setting (= <tt>"\n"</tt>) for the control-parameter Chem.ControlParameter.RECORD_SEPARATOR.
    # 
    RECORD_SEPARATOR = '\n'

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.JME_SEPARATE_COMPONENTS.
    # 
    JME_SEPARATE_COMPONENTS = True

    ##
    # \brief Default setting (= <tt>1</tt>) for the control-parameter Chem.ControlParameter.COORDINATES_DIMENSION.
    # 
    COORDINATES_DIMENSION = 1

    ##
    # \brief Default setting (= <tt>""</tt>) for the control-parameter Chem.ControlParameter.INCHI_INPUT_OPTIONS.
    # 
    INCHI_INPUT_OPTIONS = ''

    ##
    # \brief Default setting (= <tt>"/WarnOnEmptyStructure /AuxNone /NEWPSOFF"</tt>) for the control-parameter Chem.ControlParameter.INCHI_OUTPUT_OPTIONS.
    # 
    INCHI_OUTPUT_OPTIONS = '/WarnOnEmptyStructure /AuxNone /NEWPSOFF'

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.CHECK_LINE_LENGTH.
    # 
    CHECK_LINE_LENGTH = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.MDL_IGNORE_PARITY.
    # 
    MDL_IGNORE_PARITY = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.MDL_TRIM_STRINGS.
    # 
    MDL_TRIM_STRINGS = True

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.MDL_TRIM_LINES.
    # 
    MDL_TRIM_LINES = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.MDL_TRUNCATE_STRINGS.
    # 
    MDL_TRUNCATE_STRINGS = False

    ##
    # \brief 
    #
    MDL_TRUNCATE_LINESS = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.MDL_UPDATE_TIMESTAMP.
    # 
    MDL_UPDATE_TIMESTAMP = False

    ##
    # \brief Default setting (= <tt>MDLDataFormatVersion.UNDEF</tt>) for the control-parameter Chem.ControlParameter.MDL_CTAB_VERSION.
    # 
    MDL_CTAB_VERSION = 0

    ##
    # \brief Default setting (= <tt>MDLDataFormatVersion.UNDEF</tt>) for the control-parameter Chem.ControlParameter.MDL_RXN_FILE_VERSION.
    # 
    MDL_RXN_FILE_VERSION = 0

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD.
    # 
    MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY.
    # 
    MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY = False

    ##
    # \brief Default setting (= <tt>"<Energy>"</tt>) for the control-parameter Chem.ControlParameter.MDL_CONF_ENERGY_SD_TAG.
    # 
    MDL_CONF_ENERGY_SD_TAG = '<Energy>'

    ##
    # \brief Default setting (= <tt>"S"</tt>) for the control-parameter Chem.ControlParameter.SMILES_RECORD_FORMAT.
    # 
    SMILES_RECORD_FORMAT = 'SN'

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_CANONICAL_FORM.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_CANONICAL_FORM = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_KEKULE_FORM.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_KEKULE_FORM = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_ATOM_STEREO.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_ATOM_STEREO = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_BOND_STEREO.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_BOND_STEREO = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_RING_BOND_STEREO.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_RING_BOND_STEREO = True

    ##
    # \brief Default setting (= <tt>8</tt>) for the control-parameter Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE.
    # 
    SMILES_MIN_STEREO_BOND_RING_SIZE = 8

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_ISOTOPE.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_ISOTOPE = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_HYDROGEN_COUNT.
    # 
    # \since 1.3
    # 
    SMILES_OUTPUT_HYDROGEN_COUNT = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_ATOM_MAPPING_ID on reaction SMILES output.
    # 
    # \since 1.2
    # 
    SMILES_RXN_OUTPUT_ATOM_MAPPING_ID = True

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_ATOM_MAPPING_ID on molecule SMILES output.
    # 
    # \since 1.2
    # 
    SMILES_MOL_OUTPUT_ATOM_MAPPING_ID = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_SINGLE_BONDS.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_SINGLE_BONDS = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.SMILES_OUTPUT_AROMATIC_BONDS.
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_AROMATIC_BONDS = False

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.SMILES_NO_ORGANIC_SUBSET.
    # 
    SMILES_NO_ORGANIC_SUBSET = False

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.MULTI_CONF_IMPORT.
    # 
    MULTI_CONF_IMPORT = True

    ##
    # \brief Default setting (= <tt>True</tt>) for the control-parameter Chem.ControlParameter.MULTI_CONF_EXPORT.
    # 
    MULTI_CONF_EXPORT = True

    ##
    # \brief Default setting (= reference to Chem.DefaultMultiConfMoleculeInputProcessor instance) for the control-parameter Chem.ControlParameter.MULTI_CONF_INPUT_PROCESSOR.
    # 
    MULTI_CONF_INPUT_PROCESSOR = None

    ##
    # \brief Default setting (= <tt>False</tt>) for the control-parameter Chem.ControlParameter.OUTPUT_CONF_ENERGY_AS_COMMENT.
    # 
    OUTPUT_CONF_ENERGY_AS_COMMENT = False

    ##
    # \brief 
    #
    CONF_INDEX_NAME_SUFFIX_PATTERN = ''

    ##
    # \brief 
    #
    CDF_OUTPUT_SINGLE_PRECISION_FLOATS = True

    ##
    # \brief 
    #
    MOL2_ENABLE_EXTENDED_ATOM_TYPES = False

    ##
    # \brief 
    #
    MOL2_ENABLE_AROMATIC_BOND_TYPES = False

    ##
    # \brief 
    #
    MOL2_CALC_FORMAL_CHARGES = True

    ##
    # \brief 
    #
    MOL2_CHARGE_TYPE = 1

    ##
    # \brief 
    #
    MOL2_MOLECULE_TYPE = 1

    ##
    # \brief 
    #
    MOL2_OUTPUT_SUBSTRUCTURES = True

    ##
    # \brief 
    #
    MOL2_READ_PARTIAL_AS_FORMAL_CHARGES = False

    ##
    # \brief 
    #
    MOL2_OUTPUT_FORMAL_CHARGES = False

    ##
    # \brief 
    #
    COMMENT_IS_NAME = True

    ##
    # \brief 
    #
    XYZ_PERCEIVE_CONNECTIVITY = True

    ##
    # \brief 
    #
    XYZ_PERCEIVE_BOND_ORDERS = True

    ##
    # \brief 
    #
    XYZ_CALC_FORMAL_CHARGES = True

    ##
    # \brief 
    #
    CML_OUTPUT_XML_DECLARATION = True

    ##
    # \brief 
    #
    CML_OUTPUT_ELEMENT_NAMESPACE = ''

    ##
    # \brief 
    #
    CML_OUTPUT_ATOM_PARITY = True

    ##
    # \brief 
    #
    CML_OUTPUT_SINGLE_BOND_STEREO = True

    ##
    # \brief 
    #
    CML_OUTPUT_DOUBLE_BOND_STEREO = True

    ##
    # \brief 
    #
    CML_OUTPUT_KEKULE_FORM = True

    ##
    # \brief 
    #
    CML_OUTPUT_MOLECULE_NAME = True

    ##
    # \brief 
    #
    CML_OUTPUT_STRUCTURE_DATA = True

    ##
    # \brief 
    #
    CML_OUTPUT_ISOTOPE = True

    ##
    # \brief 
    #
    CML_OUTPUT_SPIN_MULTIPLICITY = True

    ##
    # \brief 
    #
    CML_OUTPUT_COMPACT_ATOM_DATA = False

    ##
    # \brief 
    #
    CML_OUTPUT_COMPACT_BOND_DATA = False
