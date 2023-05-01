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
    COORDINATES_DIMENSION = CDPL.Base.LookupKey(id=98, name='COORDINATES_DIMENSION')

    ##
    # \brief 
    #
    ORDINARY_HYDROGEN_DEPLETE = CDPL.Base.LookupKey(id=97, name='ORDINARY_HYDROGEN_DEPLETE')

    ##
    # \brief 
    #
    STRICT_ERROR_CHECKING = CDPL.Base.LookupKey(id=95, name='STRICT_ERROR_CHECKING')

    ##
    # \brief 
    #
    BOND_MEMBER_SWAP_STEREO_FIX = CDPL.Base.LookupKey(id=99, name='BOND_MEMBER_SWAP_STEREO_FIX')

    ##
    # \brief 
    #
    CHECK_LINE_LENGTH = CDPL.Base.LookupKey(id=100, name='CHECK_LINE_LENGTH')

    ##
    # \brief 
    #
    RECORD_SEPARATOR = CDPL.Base.LookupKey(id=96, name='RECORD_SEPARATOR')

    ##
    # \brief 
    #
    JME_SEPARATE_COMPONENTS = CDPL.Base.LookupKey(id=112, name='JME_SEPARATE_COMPONENTS')

    ##
    # \brief 
    #
    MDL_CTAB_VERSION = CDPL.Base.LookupKey(id=101, name='MDL_CTAB_VERSION')

    ##
    # \brief 
    #
    MDL_IGNORE_PARITY = CDPL.Base.LookupKey(id=102, name='MDL_IGNORE_PARITY')

    ##
    # \brief 
    #
    MDL_RXN_FILE_VERSION = CDPL.Base.LookupKey(id=108, name='MDL_RXN_FILE_VERSION')

    ##
    # \brief 
    #
    MDL_TRIM_LINES = CDPL.Base.LookupKey(id=105, name='MDL_TRIM_LINES')

    ##
    # \brief 
    #
    MDL_TRIM_STRINGS = CDPL.Base.LookupKey(id=104, name='MDL_TRIM_STRINGS')

    ##
    # \brief 
    #
    MDL_TRUNCATE_LINES = CDPL.Base.LookupKey(id=107, name='MDL_TRUNCATE_LINES')

    ##
    # \brief 
    #
    MDL_TRUNCATE_STRINGS = CDPL.Base.LookupKey(id=106, name='MDL_TRUNCATE_STRINGS')

    ##
    # \brief 
    #
    MDL_UPDATE_TIMESTAMP = CDPL.Base.LookupKey(id=103, name='MDL_UPDATE_TIMESTAMP')

    ##
    # \brief 
    #
    MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD = CDPL.Base.LookupKey(id=109, name='MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD')

    ##
    # \brief 
    #
    MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY = CDPL.Base.LookupKey(id=110, name='MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY')

    ##
    # \brief 
    #
    MDL_CONF_ENERGY_SD_TAG = CDPL.Base.LookupKey(id=111, name='MDL_CONF_ENERGY_SD_TAG')

    ##
    # \brief 
    #
    SMILES_RECORD_FORMAT = CDPL.Base.LookupKey(id=113, name='SMILES_RECORD_FORMAT')

    ##
    # \brief 
    #
    SMILES_MIN_STEREO_BOND_RING_SIZE = CDPL.Base.LookupKey(id=125, name='SMILES_MIN_STEREO_BOND_RING_SIZE')

    ##
    # \brief 
    #
    SMILES_NO_ORGANIC_SUBSET = CDPL.Base.LookupKey(id=124, name='SMILES_NO_ORGANIC_SUBSET')

    ##
    # \brief 
    #
    SMILES_WRITE_AROMATIC_BONDS = CDPL.Base.LookupKey(id=123, name='SMILES_WRITE_AROMATIC_BONDS')

    ##
    # \brief 
    #
    SMILES_WRITE_ISOTOPE = CDPL.Base.LookupKey(id=116, name='SMILES_WRITE_ISOTOPE')

    ##
    # \brief 
    #
    SMILES_MOL_WRITE_ATOM_MAPPING_ID = CDPL.Base.LookupKey(id=121, name='SMILES_MOL_WRITE_ATOM_MAPPING_ID')

    ##
    # \brief 
    #
    SMILES_RXN_WRITE_ATOM_MAPPING_ID = CDPL.Base.LookupKey(id=120, name='SMILES_RXN_WRITE_ATOM_MAPPING_ID')

    ##
    # \brief 
    #
    SMILES_WRITE_ATOM_STEREO = CDPL.Base.LookupKey(id=117, name='SMILES_WRITE_ATOM_STEREO')

    ##
    # \brief 
    #
    SMILES_WRITE_BOND_STEREO = CDPL.Base.LookupKey(id=118, name='SMILES_WRITE_BOND_STEREO')

    ##
    # \brief 
    #
    SMILES_WRITE_CANONICAL_FORM = CDPL.Base.LookupKey(id=114, name='SMILES_WRITE_CANONICAL_FORM')

    ##
    # \brief 
    #
    SMILES_WRITE_KEKULE_FORM = CDPL.Base.LookupKey(id=115, name='SMILES_WRITE_KEKULE_FORM')

    ##
    # \brief 
    #
    SMILES_WRITE_RING_BOND_STEREO = CDPL.Base.LookupKey(id=119, name='SMILES_WRITE_RING_BOND_STEREO')

    ##
    # \brief 
    #
    SMILES_WRITE_SINGLE_BONDS = CDPL.Base.LookupKey(id=122, name='SMILES_WRITE_SINGLE_BONDS')

    ##
    # \brief 
    #
    INCHI_INPUT_OPTIONS = CDPL.Base.LookupKey(id=126, name='INCHI_INPUT_OPTIONS')

    ##
    # \brief 
    #
    INCHI_OUTPUT_OPTIONS = CDPL.Base.LookupKey(id=127, name='INCHI_OUTPUT_OPTIONS')

    ##
    # \brief 
    #
    MULTI_CONF_IMPORT = CDPL.Base.LookupKey(id=128, name='MULTI_CONF_IMPORT')

    ##
    # \brief 
    #
    MULTI_CONF_EXPORT = CDPL.Base.LookupKey(id=129, name='MULTI_CONF_EXPORT')

    ##
    # \brief 
    #
    MULTI_CONF_INPUT_PROCESSOR = CDPL.Base.LookupKey(id=130, name='MULTI_CONF_INPUT_PROCESSOR')

    ##
    # \brief 
    #
    OUTPUT_CONF_ENERGY_AS_COMMENT = CDPL.Base.LookupKey(id=131, name='OUTPUT_CONF_ENERGY_AS_COMMENT')

    ##
    # \brief 
    #
    CONF_INDEX_NAME_SUFFIX_PATTERN = CDPL.Base.LookupKey(id=132, name='CONF_INDEX_NAME_SUFFIX_PATTERN')

    ##
    # \brief 
    #
    CDF_WRITE_SINGLE_PRECISION_FLOATS = CDPL.Base.LookupKey(id=133, name='CDF_WRITE_SINGLE_PRECISION_FLOATS')

    ##
    # \brief 
    #
    MOL2_ENABLE_EXTENDED_ATOM_TYPES = CDPL.Base.LookupKey(id=134, name='MOL2_ENABLE_EXTENDED_ATOM_TYPES')

    ##
    # \brief 
    #
    MOL2_ENABLE_AROMATIC_BOND_TYPES = CDPL.Base.LookupKey(id=135, name='MOL2_ENABLE_AROMATIC_BOND_TYPES')

    ##
    # \brief 
    #
    MOL2_CALC_FORMAL_CHARGES = CDPL.Base.LookupKey(id=136, name='MOL2_CALC_FORMAL_CHARGES')

    ##
    # \brief 
    #
    MOL2_CHARGE_TYPE = CDPL.Base.LookupKey(id=137, name='MOL2_CHARGE_TYPE')

    ##
    # \brief 
    #
    MOL2_OUTPUT_SUBSTRUCTURES = CDPL.Base.LookupKey(id=139, name='MOL2_OUTPUT_SUBSTRUCTURES')

    ##
    # \brief 
    #
    MOL2_MOLECULE_TYPE = CDPL.Base.LookupKey(id=138, name='MOL2_MOLECULE_TYPE')
