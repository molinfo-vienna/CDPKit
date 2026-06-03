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
    # \brief Specifies the dimension of atom coordinates.
    # 
    # A control-parameter value of <em>2</em> specifies 2D-coordinates and a value of <em>3</em> 3D-coordinates. Other values trigger the selection of an implementation defined default dimension.
    # 
    # \valuetype  <tt>std::size_t</tt>
    # 
    COORDINATES_DIMENSION = CDPL.Base.LookupKey('COORDINATES_DIMENSION')

    ##
    # \brief Specifies whether the calculation of a molecular property has to be performed for the ordinary hydrogen deplete input structure.
    # 
    # If the control-parameter is set to <tt>True</tt>, the calculation result will be equivalent to the result that would have been obtained for the ordinary hydrogen deplete input structure. If the control-parameter is set to <tt>False</tt>, the calculation will be performed for the unmodified molecular graph.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    ORDINARY_HYDROGEN_DEPLETE = CDPL.Base.LookupKey('ORDINARY_HYDROGEN_DEPLETE')

    ##
    # \brief Specifies whether non-fatal recoverable I/O errors should be ignored or cause an I/O operation to fail.
    # 
    # If the control-parameter is set to <tt>True</tt>, not only severe errors cause an I/O operation to fail, but also non-fatal errors from which a recovery would be possible. If the control-parameter is set to <tt>False</tt>, I/O operations will proceed even if a non-fatal error has been detected.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    STRICT_ERROR_CHECKING = CDPL.Base.LookupKey('STRICT_ERROR_CHECKING')

    ##
    # \brief Specifies whether unsupported reverse stereo bonds shall be converted to regular stereo bonds by swapping bond start and end atoms.
    # 
    # Most molecule storage formats do not support the concept of reverse stereo bonds (see Chem.BondStereoFlag). To allow the output of such bonds without loss of the provided spatial information, an implicit conversion of the reverse stereo bonds to sterically equivalent regular stereo bonds is required. This may be done either by replacing the reverse stereo specification with a regular stereo specification of the <em>opposite</em> type (e.g. Chem.BondStereoFlag.REVERSE_UP is equivalent to Chem.BondStereoFlag.DOWN), or by swapping the start and end atom of the bond and replacing the reverse stereo flag by a regular stereo flag of the <em>same</em> type (e.g. Chem.BondStereoFlag.REVERSE_UP is equivalent to Chem.BondStereoFlag.UP when the start and end atoms are exchanged).
    # 
    # The value of this control-parameter specifies which method of conversion shall be used. If the control-parameter is set to <tt>True</tt> the latter method will be used, and the former method otherwise.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    BOND_MEMBER_SWAP_STEREO_FIX = CDPL.Base.LookupKey('BOND_MEMBER_SWAP_STEREO_FIX')

    ##
    # \brief Specifies whether to check if data lines exceed the maximum allowed line length when reading or writing data in an <em>MDL</em> [\ref CTFILE] format.
    # 
    # If the control-parameter is set to <tt>True</tt>, the length of data lines that were read from or have to be written to data encoded in one of the above mentioned formats will be checked against the maximum allowed line length. Lines that exceeded the line length limit are considered as an error condition and cause the input or output operation to fail. If <tt>CHECK_LINE_LENGTH</tt> is <tt>False</tt>, the length of data lines will not be checked and has no impact on the success of the performed I/O operation.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    CHECK_LINE_LENGTH = CDPL.Base.LookupKey('CHECK_LINE_LENGTH')

    ##
    # \brief Specifies the separator for <em>SMILES</em>, <em>SMARTS</em>, <em>JME</em> and <em>InChI</em> output data records [\ref SMILES, \ref SMARTS, \ref JME, \ref INCHI].
    # 
    # Typical separators are, for example, space (" "), tab ("\t") or newline ("\n").
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    RECORD_SEPARATOR = CDPL.Base.LookupKey('RECORD_SEPARATOR')

    ##
    # \brief Specifies for the output of data in <em>JME</em> format [\ref JME] whether the components of a molecular graph shall be written separately or all together as a single <em>JME</em> component.
    # 
    # If the control-parameter is set to <tt>True</tt>, each component of a molecular graph will be represented by a corresponding <em>JME</em> molecule component in the output data record. If <tt>JME_SEPARATE_COMPONENTS</tt> is <tt>False</tt>, the components of the output molecular graph are written all together as a single <em>JME</em> component.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    JME_SEPARATE_COMPONENTS = CDPL.Base.LookupKey('JME_SEPARATE_COMPONENTS')

    ##
    # \brief Specifies the desired version of the connection table data format for the output of molecular graphs in <em>MDL SD-</em> or <em>Mol-File</em> format [\ref CTFILE].
    # 
    # The desired data format version is specified by one of the constants defined in namespace CDPL.Chem.MDLDataFormatVersion. If <tt>MDL_CTAB_VERSION</tt> has not been set or the parameter value equals CDPL.Chem.MDLDataFormatVersion.UNDEF, the format specified by the Chem.MolecularGraph property Chem.MolecularGraphProperty.MDL_CTAB_VERSION will take effect.
    # 
    # If, after all, both the control-parameter and the property do not specify a particular connection table format version, a suitable output format is chosen as follows:
    #  - if both the atom and bond count of the molecular graph is less than <em>1000</em>, data will be written in the <em>V2000</em> format
    #  - and in the format <em>V3000</em> otherwise
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    MDL_CTAB_VERSION = CDPL.Base.LookupKey('MDL_CTAB_VERSION')

    ##
    # \brief Specifies whether the stereo parity of atoms shall be ignored when reading or writing data in an <em>MDL CTFile</em> based format [\ref CTFILE].
    # 
    # If the control-parameter is set to <tt>True</tt>, the stereo parity of atoms will be ignored both on reading (i.e. the read MDL parity of an input atom will not be converted to the corresponding Chem.StereoDescriptor object and stored in the Chem.Atom property Chem.AtomProperty.STEREO_DESCRIPTOR) and writing (i.e. the property Chem.AtomProperty.MDL_PARITY is not written to the corresponding connection table data field).
    # 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_IGNORE_PARITY = CDPL.Base.LookupKey('MDL_IGNORE_PARITY')

    ##
    # \brief Specifies the desired data format version for the output of reactions in an <em>MDL Rxn-</em> or <em>RD-File</em> format [\ref CTFILE].
    # 
    # The desired data format version is specified by one of the constants defined in namespace CDPL.Chem.MDLDataFormatVersion. If <tt>MDL_RXN_FILE_VERSION</tt> has not been set or the parameter value equals CDPL.Chem.MDLDataFormatVersion.UNDEF, the format specified by the Chem.Reaction property Chem.ReactionProperty.MDL_RXN_FILE_VERSION will take effect.
    # 
    # If, after all, both the control-parameter and the property do not specify a particular <em>Rxn-File</em> format version, a suitable output format is chosen as follows:
    #  - if both the reactant and product count of the output reaction is less than <em>1000</em>, data will be written in the <em>V2000</em> format
    #  - and in the format <em>V3000</em> otherwise
    # 
    # \valuetype  <tt>unsigned int</tt>
    # 
    MDL_RXN_FILE_VERSION = CDPL.Base.LookupKey('MDL_RXN_FILE_VERSION')

    ##
    # \brief Specifies whether to remove leading and trailing whitespace from data lines when reading or writing data in an <em>MDL CTFile</em> based format [\ref CTFILE].
    # 
    # If the control-parameter is set to <tt>True</tt>, leading and trailing whitespace of data lines will be removed before processing continues. Otherwise, whitespace is considered to be significant and will be preserved.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_TRIM_LINES = CDPL.Base.LookupKey('MDL_TRIM_LINES')

    ##
    # \brief Specifies whether to remove leading and trailing whitespace from string values when reading or writing data in an <em>MDL CTFile</em> based format [\ref CTFILE].
    # 
    # If the control-parameter is set to <tt>True</tt>, leading and trailing whitespace of string data field values will be removed before processing continues. Otherwise, whitespace is considered to be significant and will be preserved.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_TRIM_STRINGS = CDPL.Base.LookupKey('MDL_TRIM_STRINGS')

    ##
    # \brief Specifies whether data lines that exceed the maximum allowed line length may be truncated when writing data in an <em>MDL CTFile</em> based format [\ref CTFILE].
    # 
    # If the control-parameter is set to <tt>True</tt>, output data lines which exceed the maximum allowed line length (according to the <em>MDL CTFile</em> specification) are silently truncated before they get written. If <tt>MDL_TRUNCATE_LINES</tt> is <tt>False</tt>, an attempt to write a data line that exceeds maximum line length is considered as an error condition and causes the output operation to fail.
    # 
    # \valuetype  <tt>bool</tt> \note The setting has only an effect if the control-parameter Chem.ControlParameter.IGNORE_LINE_LENGTH_LIMIT is <tt>False</tt>.
    # 
    MDL_TRUNCATE_LINES = CDPL.Base.LookupKey('MDL_TRUNCATE_LINES')

    ##
    # \brief Specifies whether string values that exceed the size of an output data field may be truncated when writing data in an <em>MDL CTFile</em> based format [\ref CTFILE].
    # 
    # If the control-parameter is set to <tt>True</tt>, output string values whose length exceeds the size of the target data field are silently truncated to the respective field size. If <tt>MDL_TRUNCATE_STRINGS</tt> is <tt>False</tt>, the attempt to write a string value which is too large for the target data field is considered as an error condition and causes the output operation to fail.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_TRUNCATE_STRINGS = CDPL.Base.LookupKey('MDL_TRUNCATE_STRINGS')

    ##
    # \brief Specifies whether to update the timestamp of <em>Mol-</em> and <em>Rxn-File</em> header blocks when writing data in an <em>MDL CTFile</em> based format [\ref CTFILE].
    # 
    # If the control-parameter is set to <tt>True</tt>, the timestamp of molecule and reaction data records will specify the time of their writing. If <tt>MDL_UPDATE_TIMESTAMP</tt> is <tt>False</tt>, the time specified by one of the properties Chem.MolecularGraphProperty.TIMESTAMP (for molecular graph output) or Chem.ReactionProperty.TIMESTAMP (for reaction output) will be used. If the output data object does not provide a value for the timestamp property, the current time will be used as a fallback.
    # 
    # \valuetype  <tt>bool</tt>
    # 
    MDL_UPDATE_TIMESTAMP = CDPL.Base.LookupKey('MDL_UPDATE_TIMESTAMP')

    ##
    # \brief Specifies whether to write conformer energies into the energy field of the molecule header block when writing data in an <em>MDL CTFile</em> based format [\ref CTFILE]. 
    # \valuetype  <tt>bool</tt>.
    # 
    MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD = CDPL.Base.LookupKey('MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD')

    ##
    # \brief Specifies whether to write conformer energies as an SD-file entry when writing data in an <em>MDL CTFile</em> based format [\ref CTFILE]. 
    # \valuetype  <tt>bool</tt>.
    # 
    MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY = CDPL.Base.LookupKey('MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY')

    ##
    # \brief Specifies the SD-file tag used for the conformer energy entry (see MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY). 
    # \valuetype  <tt>std::string</tt>.
    # 
    MDL_CONF_ENERGY_SD_TAG = CDPL.Base.LookupKey('MDL_CONF_ENERGY_SD_TAG')

    ##
    # \brief Specifies whether to output the 'aromatic' bond type value (<tt>4</tt>) in the type field of aromatic bonds when writing molecular graph data in an <em>MDL CTFile</em> based format [\ref CTFILE]. On data reading, the aromaticity flag property of bonds having this type will be set to <tt>True</tt> and to <tt>False</tt> if the bond type specifies a defined bond order. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.3
    # 
    MDL_ENABLE_AROMATIC_BOND_TYPES = CDPL.Base.LookupKey('MDL_ENABLE_AROMATIC_BOND_TYPES')

    ##
    # \brief Specifies the format of <em>SMILES</em> molecular graph or reaction data records [\ref SMILES].
    # 
    # The data record format is specified by one of the two following format strings:
    #  - "S"
    #  - "SN"
    # 
    # The character 'S' denotes the <em>SMILES</em> representation of the molecular graph or reaction, and 'N' the name of the molecular graph/reaction (see Chem.MolecularGraphProperty.NAME and Chem.ReactionProperty.NAME).
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    SMILES_RECORD_FORMAT = CDPL.Base.LookupKey('SMILES_RECORD_FORMAT')

    ##
    # \brief Specifies the minimum ring size that is required for the specification of ring double bond geometries in generated <em>SMILES</em> strings [\ref SMILES].
    # 
    # \valuetype  <tt>std::size_t</tt> \see Chem.ControlParameter.SMILES_OUTPUT_RING_BOND_STEREO
    # 
    SMILES_MIN_STEREO_BOND_RING_SIZE = CDPL.Base.LookupKey('SMILES_MIN_STEREO_BOND_RING_SIZE')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] where all atom symbols are enclosed in brackets.
    # 
    # If the control-parameter is set to <tt>True</tt>, <em>SMILES</em> strings will be generated where all atoms are enclosed in square brackets regardless of their atom type and the necessity to specify additional atom properties. If the value of <tt>SMILES_NO_ORGANIC_SUBSET</tt> is <tt>False</tt>, only those atoms will be enclosed in brackets that require the specification of additional atomic properties (charge, hydrogen count, isotope, ...) or are not part of the organic subset (i.e. <em>C, N, O, S, P, F, Cl, Br</em> and <em>I</em>).
    # 
    # \valuetype  <tt>bool</tt>
    # 
    SMILES_NO_ORGANIC_SUBSET = CDPL.Base.LookupKey('SMILES_NO_ORGANIC_SUBSET')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] with explicit aromatic bond specifications.
    # 
    # If the control-parameter is set to <tt>True</tt>, generated <em>SMILES</em> strings will explicitly specify aromatic bonds. If the value of <tt>SMILES_OUTPUT_AROMATIC_BONDS</tt> is <tt>False</tt>, aromatic bonds are left unspecified.
    # 
    # \valuetype  <tt>bool</tt> \note The setting of this control-parameter has only an effect if Chem.ControlParameter.SMILES_OUTPUT_KEKULE_FORM is set to <tt>False</tt>. 
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_AROMATIC_BONDS = CDPL.Base.LookupKey('SMILES_OUTPUT_AROMATIC_BONDS')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] with isotopic mass specifications.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will specify the isotopic mass of of atoms (if non-standard). If the value of <tt>SMILES_OUTPUT_ISOTOPE</tt> is <tt>False</tt>, the isotopic mass is left unspecified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_OUTPUT_ISOTOPE = CDPL.Base.LookupKey('SMILES_OUTPUT_ISOTOPE')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] with implicit hydrogen count specifications.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will specify the implicit hydrogen count of atoms (if non-standard). If the value of <tt>SMILES_OUTPUT_HYDROGEN_COUNT</tt> is <tt>False</tt>, the implicit hydrogen count is always left unspecified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.3
    # 
    SMILES_OUTPUT_HYDROGEN_COUNT = CDPL.Base.LookupKey('SMILES_OUTPUT_HYDROGEN_COUNT')

    ##
    # \brief Specifies whether to generate molecule <em>SMILES</em> strings [\ref SMILES] that contain atom-atom mapping numbers.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will specify reaction atom-atom mapping numbers (see Chem.AtomProperty.ATOM_MAPPING_ID). If the value of <tt>SMILES_OUTPUT_ATOM_MAPPING_ID</tt> is <tt>False</tt>, atom-atom mapping numbers will not be specified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_MOL_OUTPUT_ATOM_MAPPING_ID = CDPL.Base.LookupKey('SMILES_MOL_OUTPUT_ATOM_MAPPING_ID')

    ##
    # \brief Specifies whether to generate reaction <em>SMILES</em> strings [\ref SMILES] that contain atom-atom mapping numbers.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will specify reaction atom-atom mapping numbers (see Chem.AtomProperty.ATOM_MAPPING_ID). If the value of <tt>SMILES_OUTPUT_ATOM_MAPPING_ID</tt> is <tt>False</tt>, atom-atom mapping numbers will not be specified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_RXN_OUTPUT_ATOM_MAPPING_ID = CDPL.Base.LookupKey('SMILES_RXN_OUTPUT_ATOM_MAPPING_ID')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] with atom parity specifications.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will specify the parity of terahedral stereogenic atoms. If the value of the control-parameter is <tt>False</tt>, the parity of stereogenic atoms is left unspecified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_OUTPUT_ATOM_STEREO = CDPL.Base.LookupKey('SMILES_OUTPUT_ATOM_STEREO')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] that include directional bonds for the definition of double bond geometries.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will contain directional bonds for the specification of chain double bond geometries. If the value of the control-parameter is <tt>False</tt>, the geometry of double bonds is left unspecified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_OUTPUT_BOND_STEREO = CDPL.Base.LookupKey('SMILES_OUTPUT_BOND_STEREO')

    ##
    # \brief Specifies whether to generate canonical <em>SMILES</em> strings [\ref SMILES].
    # 
    # If the control-parameter is set to <tt>True</tt>, canonical <em>SMILES</em> strings will be generated. A canonical <em>SMILES</em> string is unique for a given chemical structure and is always identical regardless of the atom and bond order in the Chem.MolecularGraph object that describes the structure. If the value of <tt>SMILES_OUTPUT_CANONICAL_FORM</tt> is <tt>False</tt>, the form of a generated <em>SMILES</em> string depends on the order of the atoms and bonds in the output molecular graph and thus may differ across a set of Chem.MolecularGraph objects that otherwise represent the same chemical structure.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_OUTPUT_CANONICAL_FORM = CDPL.Base.LookupKey('SMILES_OUTPUT_CANONICAL_FORM')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] with kekulized aromatic rings.
    # 
    # If the control-parameter is set to <tt>True</tt>, aromatic rings will be represented as <em>Kekul&eacute;</em> structures with standard (non-lowercase) atom element symbols and localized bond orders. If the value of <tt>SMILES_OUTPUT_KEKULE_FORM</tt> is <tt>False</tt>, the order of localized aromatic bonds is left unspecified and aromatic atoms of type <em>C, N, O, S, Se, Te</em> or <em>As</em> will be indicated by lowercase atom element symbols.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_OUTPUT_KEKULE_FORM = CDPL.Base.LookupKey('SMILES_OUTPUT_KEKULE_FORM')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] that also include directional bonds for the definition of ring double bond geometries.
    # 
    # If the control-parameter is set to <tt>True</tt>, the generated <em>SMILES</em> string will specify the geometry of any double bond that is not a member of a ring which is smaller than the size specified by Chem.ControlParameter.SMILES_MIN_STEREO_BOND_RING_SIZE. If the value of the control-parameter is <tt>False</tt>, the geometry of ring double bonds will not be specified.
    # 
    # \valuetype  <tt>bool</tt> \note The setting of this control-parameter has only an effect if Chem.ControlParameter.SMILES_OUTPUT_BOND_STEREO is set to <tt>True</tt>. 
    # 
    # \since 1.2
    # 
    SMILES_OUTPUT_RING_BOND_STEREO = CDPL.Base.LookupKey('SMILES_OUTPUT_RING_BOND_STEREO')

    ##
    # \brief Specifies whether to generate <em>SMILES</em> strings [\ref SMILES] with explicit single bond specifications.
    # 
    # If the control-parameter is set to <tt>True</tt>, generated <em>SMILES</em> strings will not only specify double and triple bonds, but also single bonds. If the value of <tt>SMILES_OUTPUT_SINGLE_BONDS</tt> is <tt>False</tt>, single bonds are left unspecified.
    # 
    # \valuetype  <tt>bool</tt> \since 1.2
    # 
    SMILES_OUTPUT_SINGLE_BONDS = CDPL.Base.LookupKey('SMILES_OUTPUT_SINGLE_BONDS')

    ##
    # \brief Specifies options for the input of <em>InChI</em> strings [\ref INCHI].
    # 
    # Please refer to the <em>InChI C-API</em> documentation [\ref INCHI] for further information about the syntax and meaning of the available options.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    INCHI_INPUT_OPTIONS = CDPL.Base.LookupKey('INCHI_INPUT_OPTIONS')

    ##
    # \brief Specifies options for the output of <em>InChI</em> strings [\ref INCHI].
    # 
    # Please refer to the <em>InChI C-API</em> documentation [\ref INCHI] for further information about the syntax and meaning of the available options.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    INCHI_OUTPUT_OPTIONS = CDPL.Base.LookupKey('INCHI_OUTPUT_OPTIONS')

    ##
    # \brief Specifies whether to check for and import multi-conformer molecules. 
    # \valuetype  <tt>bool</tt>.
    # 
    MULTI_CONF_IMPORT = CDPL.Base.LookupKey('MULTI_CONF_IMPORT')

    ##
    # \brief Specifies whether to write all molecule conformations on output. 
    # \valuetype  <tt>bool</tt>.
    # 
    MULTI_CONF_EXPORT = CDPL.Base.LookupKey('MULTI_CONF_EXPORT')

    ##
    # \brief Specifies an instance of Chem.MultiConfMoleculeInputProcessor that implements the logic of multi-conformer molecule detection and conformational data processing. 
    # \valuetype  Chem.MultiConfMoleculeInputProcessor.SharedPointer.
    # 
    MULTI_CONF_INPUT_PROCESSOR = CDPL.Base.LookupKey('MULTI_CONF_INPUT_PROCESSOR')

    ##
    # \brief Specifies whether to write the conformer energy into the molecule comment field on output. 
    # \valuetype  <tt>bool</tt>.
    # 
    OUTPUT_CONF_ENERGY_AS_COMMENT = CDPL.Base.LookupKey('OUTPUT_CONF_ENERGY_AS_COMMENT')

    ##
    # \brief Specifies a format pattern used to derive per-conformer molecule name suffixes from the conformer index.
    # 
    # The pattern is interpreted as a <tt>std::printf</tt> format string with a single integer placeholder for the (one-based) conformer index. An empty value disables the suffix.
    # 
    # \valuetype  <tt>std::string</tt>
    # 
    CONF_INDEX_NAME_SUFFIX_PATTERN = CDPL.Base.LookupKey('CONF_INDEX_NAME_SUFFIX_PATTERN')

    ##
    # \brief Specifies whether floating-point values written to the native CDF format are encoded in single-precision (<tt>True</tt>) or double-precision (<tt>False</tt>). 
    # \valuetype  <tt>bool</tt>.
    # 
    CDF_OUTPUT_SINGLE_PRECISION_FLOATS = CDPL.Base.LookupKey('CDF_OUTPUT_SINGLE_PRECISION_FLOATS')

    ##
    # \brief Specifies whether to enable the extended Sybyl atom-type set when reading or writing <em>Sybyl MOL2</em> data. 
    # \valuetype  <tt>bool</tt>.
    # 
    MOL2_ENABLE_EXTENDED_ATOM_TYPES = CDPL.Base.LookupKey('MOL2_ENABLE_EXTENDED_ATOM_TYPES')

    ##
    # \brief Specifies whether to interpret/write the Sybyl bond type <tt>"ar"</tt> as aromatic on <em>MOL2</em> input/output. 
    # \valuetype  <tt>bool</tt>.
    # 
    MOL2_ENABLE_AROMATIC_BOND_TYPES = CDPL.Base.LookupKey('MOL2_ENABLE_AROMATIC_BOND_TYPES')

    ##
    # \brief Specifies whether to recompute formal charges from atom types on <em>MOL2</em> input. 
    # \valuetype  <tt>bool</tt>.
    # 
    MOL2_CALC_FORMAL_CHARGES = CDPL.Base.LookupKey('MOL2_CALC_FORMAL_CHARGES')

    ##
    # \brief Specifies the charge type recorded in the <tt>@<TRIPOS>MOLECULE</tt> block on <em>MOL2</em> output (see namespace Chem.MOL2ChargeType). 
    # \valuetype  <tt>unsigned int</tt>
    # 
    MOL2_CHARGE_TYPE = CDPL.Base.LookupKey('MOL2_CHARGE_TYPE')

    ##
    # \brief Specifies whether to write the <tt>@<TRIPOS>SUBSTRUCTURE</tt> block on <em>MOL2</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    MOL2_OUTPUT_SUBSTRUCTURES = CDPL.Base.LookupKey('MOL2_OUTPUT_SUBSTRUCTURES')

    ##
    # \brief Specifies the molecule type recorded in the <tt>@<TRIPOS>MOLECULE</tt> block on <em>MOL2</em> output (see namespace Chem.MOL2MoleculeType). 
    # \valuetype  <tt>unsigned int</tt>
    # 
    MOL2_MOLECULE_TYPE = CDPL.Base.LookupKey('MOL2_MOLECULE_TYPE')

    ##
    # \brief Specifies whether to round Sybyl partial charges to the nearest integer formal charges on <em>MOL2</em> input. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2.3
    # 
    MOL2_READ_PARTIAL_AS_FORMAL_CHARGES = CDPL.Base.LookupKey('MOL2_READ_PARTIAL_AS_FORMAL_CHARGES')

    ##
    # \brief Specifies whether to emit formal atomic charges in the partial-charge column on <em>MOL2</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2.3
    # 
    MOL2_OUTPUT_FORMAL_CHARGES = CDPL.Base.LookupKey('MOL2_OUTPUT_FORMAL_CHARGES')

    ##
    # \brief 
    #
    COMMENT_IS_NAME = CDPL.Base.LookupKey('XYZ_COMMENT_IS_NAME')

    ##
    # \brief Specifies whether to perceive bond connectivity from atom 3D coordinates when reading <em>XYZ</em> data (which encodes no explicit bonds). 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.1
    # 
    XYZ_PERCEIVE_CONNECTIVITY = CDPL.Base.LookupKey('XYZ_PERCEIVE_CONNECTIVITY')

    ##
    # \brief Specifies whether to perceive bond orders from the perceived connectivity when reading <em>XYZ</em> data. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.1
    # 
    XYZ_PERCEIVE_BOND_ORDERS = CDPL.Base.LookupKey('XYZ_PERCEIVE_BOND_ORDERS')

    ##
    # \brief Specifies whether to recompute formal atomic charges after the bond perception step on <em>XYZ</em> input. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.1
    # 
    XYZ_CALC_FORMAL_CHARGES = CDPL.Base.LookupKey('XYZ_CALC_FORMAL_CHARGES')

    ##
    # \brief Specifies whether to emit an XML declaration (<tt><?xml version="1.0"?></tt>) at the beginning of <em>CML</em> output records. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_XML_DECLARATION = CDPL.Base.LookupKey('CML_OUTPUT_XML_DECLARATION')

    ##
    # \brief Specifies the XML namespace URI emitted with the root <tt><cml></tt> element on <em>CML</em> output. 
    # \valuetype  <tt>std::string</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_ELEMENT_NAMESPACE = CDPL.Base.LookupKey('CML_OUTPUT_ELEMENT_NAMESPACE')

    ##
    # \brief Specifies whether to encode tetrahedral atom parities on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_ATOM_PARITY = CDPL.Base.LookupKey('CML_OUTPUT_ATOM_PARITY')

    ##
    # \brief Specifies whether to emit wedge/hash stereo flags for single bonds on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_SINGLE_BOND_STEREO = CDPL.Base.LookupKey('CML_OUTPUT_SINGLE_BOND_STEREO')

    ##
    # \brief Specifies whether to encode cis/trans descriptors for double bonds on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_DOUBLE_BOND_STEREO = CDPL.Base.LookupKey('CML_OUTPUT_DOUBLE_BOND_STEREO')

    ##
    # \brief Specifies whether to interpret/write CML's aromatic bond type <tt>"a"</tt> on input/output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.3
    # 
    CML_ENABLE_AROMATIC_BOND_TYPES = CDPL.Base.LookupKey('CML_ENABLE_AROMATIC_BOND_TYPES')

    ##
    # \brief Specifies whether to emit the <tt>title</tt> attribute (molecule name) on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_MOLECULE_NAME = CDPL.Base.LookupKey('CML_OUTPUT_MOLECULE_NAME')

    ##
    # \brief Specifies whether to emit attached structure-data fields on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_STRUCTURE_DATA = CDPL.Base.LookupKey('CML_OUTPUT_STRUCTURE_DATA')

    ##
    # \brief Specifies whether to emit the isotopic mass number of non-standard isotopes on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_ISOTOPE = CDPL.Base.LookupKey('CML_OUTPUT_ISOTOPE')

    ##
    # \brief Specifies whether to emit the atom spin multiplicity on <em>CML</em> output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_SPIN_MULTIPLICITY = CDPL.Base.LookupKey('CML_OUTPUT_SPIN_MULTIPLICITY')

    ##
    # \brief Specifies whether to use CML's compact (array-style) representation for atom data on output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_COMPACT_ATOM_DATA = CDPL.Base.LookupKey('CML_OUTPUT_COMPACT_ATOM_DATA')

    ##
    # \brief Specifies whether to use CML's compact (array-style) representation for bond data on output. 
    # \valuetype  <tt>bool</tt>.
    # 
    # \since 1.2
    # 
    CML_OUTPUT_COMPACT_BOND_DATA = CDPL.Base.LookupKey('CML_OUTPUT_COMPACT_BOND_DATA')
