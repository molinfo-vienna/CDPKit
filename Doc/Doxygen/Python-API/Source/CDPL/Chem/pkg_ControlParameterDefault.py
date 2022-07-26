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
class ControlParameterDefault(Boost.Python.instance):

    ##
    # \brief 
    #
    STRICT_ERROR_CHECKING = False

    ##
    # \brief 
    #
    ORDINARY_HYDROGEN_DEPLETE = True

    ##
    # \brief 
    #
    BOND_MEMBER_SWAP_STEREO_FIX = True

    ##
    # \brief 
    #
    RECORD_SEPARATOR = '\n'

    ##
    # \brief 
    #
    JME_SEPARATE_COMPONENTS = True

    ##
    # \brief 
    #
    COORDINATES_DIMENSION = 1

    ##
    # \brief 
    #
    INCHI_INPUT_OPTIONS = ''

    ##
    # \brief 
    #
    INCHI_OUTPUT_OPTIONS = '/WarnOnEmptyStructure /AuxNone /NEWPSOFF'

    ##
    # \brief 
    #
    CHECK_LINE_LENGTH = False

    ##
    # \brief 
    #
    MDL_IGNORE_PARITY = False

    ##
    # \brief 
    #
    MDL_TRIM_STRINGS = True

    ##
    # \brief 
    #
    MDL_TRIM_LINES = False

    ##
    # \brief 
    #
    MDL_TRUNCATE_STRINGS = False

    ##
    # \brief 
    #
    MDL_TRUNCATE_LINESS = False

    ##
    # \brief 
    #
    MDL_UPDATE_TIMESTAMP = False

    ##
    # \brief 
    #
    MDL_CTAB_VERSION = 0

    ##
    # \brief 
    #
    MDL_RXN_FILE_VERSION = 0

    ##
    # \brief 
    #
    MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD = False

    ##
    # \brief 
    #
    MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY = False

    ##
    # \brief 
    #
    MDL_CONF_ENERGY_SD_TAG = '<Energy>'

    ##
    # \brief 
    #
    SMILES_RECORD_FORMAT = 'S'

    ##
    # \brief 
    #
    SMILES_WRITE_CANONICAL_FORM = False

    ##
    # \brief 
    #
    SMILES_WRITE_KEKULE_FORM = False

    ##
    # \brief 
    #
    SMILES_WRITE_ATOM_STEREO = True

    ##
    # \brief 
    #
    SMILES_WRITE_BOND_STEREO = True

    ##
    # \brief 
    #
    SMILES_WRITE_RING_BOND_STEREO = True

    ##
    # \brief 
    #
    SMILES_MIN_STEREO_BOND_RING_SIZE = 8

    ##
    # \brief 
    #
    SMILES_WRITE_ISOTOPE = True

    ##
    # \brief 
    #
    SMILES_RXN_WRITE_ATOM_MAPPING_ID = True

    ##
    # \brief 
    #
    SMILES_MOL_WRITE_ATOM_MAPPING_ID = False

    ##
    # \brief 
    #
    SMILES_WRITE_SINGLE_BONDS = False

    ##
    # \brief 
    #
    SMILES_WRITE_AROMATIC_BONDS = False

    ##
    # \brief 
    #
    SMILES_NO_ORGANIC_SUBSET = False

    ##
    # \brief 
    #
    MULTI_CONF_IMPORT = True

    ##
    # \brief 
    #
    MULTI_CONF_EXPORT = True

    ##
    # \brief 
    #
    MULTI_CONF_INPUT_PROCESSOR = None

    ##
    # \brief 
    #
    OUTPUT_CONF_ENERGY_AS_COMMENT = False

    ##
    # \brief 
    #
    CONF_INDEX_NAME_SUFFIX_PATTERN = ''

    ##
    # \brief 
    #
    CDF_WRITE_SINGLE_PRECISION_FLOATS = True

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
