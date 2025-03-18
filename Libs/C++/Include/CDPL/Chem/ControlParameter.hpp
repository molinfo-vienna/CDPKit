/* 
 * ControlParameter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of constants in namespace CDPL::Chem::ControlParameter.
 */

#ifndef CDPL_CHEM_CONTROLPARAMETER_HPP
#define CDPL_CHEM_CONTROLPARAMETER_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Chem
    {

        /**
         * \brief Provides keys for built-in control-parameters.
         */
        namespace ControlParameter
        {

            /**
             * \brief Specifies whether the calculation of a molecular property has to be performed for the ordinary hydrogen
             *        deplete input structure.
             *
             * If the control-parameter is set to \c true, the calculation result will be equivalent to the
             * result that would have been obtained for the ordinary hydrogen deplete input structure.
             * If the control-parameter is set to \c false, the calculation will be performed for the unmodified molecular
             * graph.
             *
             * \valuetype \c bool
             * \see Chem::AtomProperty::IS_ORDINARY_H for the definition of ordinary hydrogens.    
             */
            extern CDPL_CHEM_API const Base::LookupKey ORDINARY_HYDROGEN_DEPLETE;

            /**
             * \brief Specifies the dimension of atom coordinates.
             *
             * A control-parameter value of \e 2 specifies 2D-coordinates and a value of \e 3 3D-coordinates. 
             * Other values trigger the selection of an implementation defined default dimension.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey COORDINATES_DIMENSION;

            /**
             * \brief Specifies whether non-fatal recoverable I/O errors should be ignored or cause an I/O operation to fail.
             *
             * If the control-parameter is set to \c true, not only severe errors cause an I/O operation to fail, but also
             * non-fatal errors from which a recovery would be possible. 
             * If the control-parameter is set to \c false, I/O operations will proceed even if a non-fatal error has been
             * detected.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey STRICT_ERROR_CHECKING;

            /**
             * \brief Specifies the separator for \e SMILES, \e SMARTS, \e JME and \e InChI output data records
             *        [\ref SMILES, \ref SMARTS, \ref JME, \ref INCHI].
             *
             * Typical separators are, for example, space (" "), tab ("\t") or newline ("\n").
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey RECORD_SEPARATOR;

            /**
             * \brief Specifies whether unsupported reverse stereo bonds shall be converted to regular stereo bonds by
             *        swapping bond start and end atoms.
             *
             * Most molecule storage formats do not support the concept of reverse stereo bonds (see Chem::BondStereoFlag).
             * To allow the output of such bonds without loss of the provided spatial information, an implicit conversion of the
             * reverse stereo bonds to sterically equivalent regular stereo bonds is required. This may be done either by replacing
             * the reverse stereo specification with a regular stereo specification of the \e opposite type (e.g. 
             * Chem::BondStereoFlag::REVERSE_UP is equivalent to Chem::BondStereoFlag::DOWN), or by swapping the start and end
             * atom of the bond and replacing the reverse stereo flag by a regular stereo flag of the \e same type (e.g.
             * Chem::BondStereoFlag::REVERSE_UP is equivalent to Chem::BondStereoFlag::UP when the start and end atoms are exchanged).
             *
             * The value of this control-parameter specifies which method of conversion shall be used. If the control-parameter
             * is set to \c true the latter method will be used, and the former method otherwise.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey BOND_MEMBER_SWAP_STEREO_FIX;

            /**
             * \brief Specifies the desired version of the connection table data format for the output of molecular graphs in
             *        <em>MDL SD-</em> or \e Mol-File format [\ref CTFILE].
             *
             * The desired data format version is specified by one of the constants defined in namespace CDPL::Chem::MDLDataFormatVersion.
             * If \c %MDL_CTAB_VERSION has not been set or the parameter value equals CDPL::Chem::MDLDataFormatVersion::UNDEF, the
             * format specified by the Chem::MolecularGraph property Chem::MolecularGraphProperty::MDL_CTAB_VERSION will take effect. 
             *
             * If, after all, both the control-parameter and the property do not specify a particular connection table format version,
             * a suitable output format is chosen as follows:
             * - if both the atom and bond count of the molecular graph is less than \e 1000, data will be written in the 
             *   <em>V2000</em> format
             * - and in the format <em>V3000</em> otherwise
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_CTAB_VERSION;

            /**
             * \brief Specifies whether the stereo parity of atoms shall be ignored when reading or writing data 
             *        in a <em>MDL CTFile</em> based format [\ref CTFILE].
             *
             * If the control-parameter is set to \c true, the stereo parity of atoms will be ignored both on
             * reading (i.e. the read MDL parity of an input atom will not be converted to the corresponding Chem::StereoDescriptor
             * object and stored in the Chem::Atom property Chem::AtomProperty::STEREO_DESCRIPTOR) and writing (i.e. the property
             * Chem::AtomProperty::MDL_PARITY is not written to the corresponding connection table data field).
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_IGNORE_PARITY;

            /**
             * \brief Specifies whether to update the timestamp of \e Mol- and \e Rxn-File header blocks when writing data
             *        in a <em>MDL CTFile</em> based format [\ref CTFILE].
             *
             * If the control-parameter is set to \c true, the timestamp of molecule and reaction data records will
             * specify the time of their writing. If \c %MDL_UPDATE_TIMESTAMP is \c false, the time specified by one of the
             * properties Chem::MolecularGraphProperty::MDL_TIMESTAMP (for molecular graph output) or 
             * Chem::ReactionProperty::MDL_TIMESTAMP (for reaction output) will be used. If the output data object does not
             * provide a value for the timestamp property, the current time will be used as a fallback.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_UPDATE_TIMESTAMP;

            /**
             * \brief Specifies whether to remove leading and trailing whitespace from string values when reading or writing data
             *        in a <em>MDL CTFile</em> based format [\ref CTFILE].
             *
             * If the control-parameter is set to \c true, leading and trailing whitespace of string data field
             * values will be removed before processing continues.
             * Otherwise, whitespace is considered to be significant and will be preserved.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_TRIM_STRINGS;

            /**
             * \brief Specifies whether to remove leading and trailing whitespace from data lines when reading or writing data 
             *        in a <em>MDL CTFile</em> based format [\ref CTFILE].
             *
             * If the control-parameter is set to \c true, leading and trailing whitespace of data lines 
             * will be removed before processing continues.
             * Otherwise, whitespace is considered to be significant and will be preserved.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_TRIM_LINES;

            /**
             * \brief Specifies whether string values that exceed the size of an output data field may be truncated when writing data
             *        in a <em>MDL CTFile</em> based format [\ref CTFILE].
             *
             * If the control-parameter is set to \c true, output string values whose length exceeds the size of the target data
             * field are silently truncated to the respective field size.
             * If \c %MDL_TRUNCATE_STRINGS is \c false, the attempt to write a string value which is too large for the target
             * data field is considered as an error condition and causes the output operation to fail.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_TRUNCATE_STRINGS;

            /**
             * \brief Specifies whether data lines that exceed the maximum allowed line length may be truncated when writing data
             *        in a <em>MDL CTFile</em> based format [\ref CTFILE].
             *
             * If the control-parameter is set to \c true, output data lines which exceed the maximum allowed line length
             * (according to the <em>MDL CTFile</em> specification) are silently truncated before they get written.
             * If \c %MDL_TRUNCATE_LINES is \c false, an attempt to write a data line that exceeds maximum line length is considered
             * as an error condition and causes the output operation to fail.
             *
             * \valuetype \c bool
             * \note The setting has only an effect if the control-parameter Chem::ControlParameter::IGNORE_LINE_LENGTH_LIMIT
             *       is \c false.
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_TRUNCATE_LINES;

            extern CDPL_CHEM_API const Base::LookupKey MDL_OUTPUT_CONF_ENERGY_TO_ENERGY_FIELD;

            extern CDPL_CHEM_API const Base::LookupKey MDL_OUTPUT_CONF_ENERGY_AS_SD_ENTRY;

            extern CDPL_CHEM_API const Base::LookupKey MDL_CONF_ENERGY_SD_TAG;

            /**
             * \brief Specifies whether to check if data lines exceed the maximum allowed line length when reading or writing data
             *        in a <em>MDL</em> [\ref CTFILE] format.
             *
             * If the control-parameter is set to \c true, the length of data lines that were read from or have to
             * be written to data encoded in one of the above mentioned formats will be checked against the maximum
             * allowed line length. Lines that exceeded the line length limit are considered as an error condition and cause
             * the input or output operation to fail. If \c %CHECK_LINE_LENGTH is \c false, the length of data lines will
             * not be checked and has no impact on the success of the performed I/O operation.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey CHECK_LINE_LENGTH;

            /**
             * \brief Specifies the desired data format version for the output of reactions in <em>MDL Rxn-</em> or \e RD-File
             *        format [\ref CTFILE].
             *
             * The desired data format version is specified by one of the constants defined in namespace CDPL::Chem::MDLDataFormatVersion.
             * If \c %MDL_RXN_FILE_VERSION has not been set or the parameter value equals CDPL::Chem::MDLDataFormatVersion::UNDEF, the
             * format specified by the Chem::Reaction property Chem::ReactionProperty::MDL_RXN_FILE_VERSION will take effect. 
             *
             * If, after all, both the control-parameter and the property do not specify a particular \e Rxn-File format version,
             * a suitable output format is chosen as follows:
             * - if both the reactant and product count of the output reaction is less than \e 1000, data will be written in
             *   the <em>V2000</em> format
             * - and in the format <em>V3000</em> otherwise
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_RXN_FILE_VERSION;

            /**
             * \brief Specifies for the output of data in \e JME format [\ref JME] whether the components of a molecular graph
             *        shall be written separately or all together as a single \e JME component.
             *
             * If the control-parameter is set to \c true, each component of a molecular graph will be represented by a
             * corresponding \e JME molecule component in the output data record. If \c %JME_SEPARATE_COMPONENTS is \c false,
             * the components of the output molecular graph are written all together as a single \e JME component.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey JME_SEPARATE_COMPONENTS;

            /**
             * \brief Specifies the format of \e SMILES molecular graph or reaction data records [\ref SMILES].
             *
             * The data record format is specified by one of the two following format strings:
             * - "S"
             * - "SN"
             *
             * The character 'S' denotes the \e SMILES representation of the molecular graph or reaction, and 'N' the name of the
             * molecular graph/reaction (see Chem::MolecularGraphProperty::NAME and Chem::ReactionProperty::NAME).
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_RECORD_FORMAT;

            /**
             * \brief Specifies whether to generate canonical \e SMILES strings [\ref SMILES].
             *
             * If the control-parameter is set to \c true, canonical \e SMILES strings will be generated. A canonical \e SMILES
             * string is unique for a given chemical structure and is always identical regardless of the atom and bond order in
             * the Chem::MolecularGraph object that describes the structure.
             * If the value of \c %SMILES_OUTPUT_CANONICAL_FORM is \c false, the form of a generated \e SMILES string depends
             * on the order of the atoms and bonds in the output molecular graph and thus may differ across a set of 
             * Chem::MolecularGraph objects that otherwise represent the same chemical structure.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_CANONICAL_FORM;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] with kekulized aromatic rings.
             *
             * If the control-parameter is set to \c true, aromatic rings will be represented as \e Kekul&eacute; structures with
             * standard (non-lowercase) atom element symbols and localized bond orders.
             * If the value of \c %SMILES_OUTPUT_KEKULE_FORM is \c false, the order of localized aromatic bonds is left unspecified
             * and aromatic atoms of type <em>C, N, O, S, Se, Te</em> or \e As will be indicated by lowercase atom element
             * symbols.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_KEKULE_FORM;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] with atom parity specifications.
             *
             * If the control-parameter is set to \c true, the generated \e SMILES string will specify the parity
             * of terahedral stereogenic atoms. If the value of the control-parameter is \c false, the parity of
             * stereogenic atoms is left unspecified.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_ATOM_STEREO;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] that include directional bonds for the definition of
             *        double bond geometries.
             *
             * If the control-parameter is set to \c true, the generated \e SMILES string will contain directional bonds for
             * the specification of chain double bond geometries. If the value of the control-parameter is \c false, the 
             * geometry of double bonds is left unspecified.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_BOND_STEREO;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] that also include directional bonds for the definition of
             *        ring double bond geometries.
             *
             * If the control-parameter is set to \c true, the generated \e SMILES string will specify the geometry of
             * any double bond that is not a member of a ring which is smaller than the size specified by
             * Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE. 
             * If the value of the control-parameter is \c false, the geometry of ring double bonds will not be specified.
             *
             * \valuetype \c bool
             * \note The setting of this control-parameter has only an effect if Chem::ControlParameter::SMILES_OUTPUT_BOND_STEREO
             *       is set to \c true.
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_RING_BOND_STEREO;

            /**
             * \brief Specifies the minimum ring size that is required for the specification of ring double bond geometries
             *        in generated \e SMILES strings [\ref SMILES].
             * 
             * \valuetype \c std::size_t
             * \see Chem::ControlParameter::SMILES_OUTPUT_RING_BOND_STEREO
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_MIN_STEREO_BOND_RING_SIZE;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] with isotopic mass specifications.
             *
             * If the control-parameter is set to \c true, the generated \e SMILES string will specify the isotopic mass of
             * of atoms (if non-standard). 
             * If the value of \c %SMILES_OUTPUT_ISOTOPE is \c false, the isotopic mass is left unspecified.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_ISOTOPE;

            /**
             * \brief Specifies whether to generate molecule \e SMILES strings [\ref SMILES] that contain reaction atom-atom mapping numbers.
             *
             * If the control-parameter is set to \c true, the generated \e SMILES string will specify reaction atom-atom
             * mapping numbers (see Chem::AtomProperty::REACTION_ATOM_MAPPING_ID). 
             * If the value of \c %SMILES_OUTPUT_ATOM_MAPPING_ID is \c false, atom-atom mapping numbers will not be specified.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_MOL_OUTPUT_ATOM_MAPPING_ID;

            /**
             * \brief Specifies whether to generate reaction \e SMILES strings [\ref SMILES] that contain reaction atom-atom mapping numbers.
             *
             * If the control-parameter is set to \c true, the generated \e SMILES string will specify reaction atom-atom
             * mapping numbers (see Chem::AtomProperty::REACTION_ATOM_MAPPING_ID). 
             * If the value of \c %SMILES_OUTPUT_ATOM_MAPPING_ID is \c false, atom-atom mapping numbers will not be specified.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_RXN_OUTPUT_ATOM_MAPPING_ID;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] with explicit single bond specifications.
             *
             * If the control-parameter is set to \c true, generated \e SMILES strings will not only specify double and triple
             * bonds, but also single bonds.
             * If the value of \c %SMILES_OUTPUT_SINGLE_BONDS is \c false, single bonds are left unspecified.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_SINGLE_BONDS;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] with explicit aromatic bond specifications.
             *
             * If the control-parameter is set to \c true, generated \e SMILES strings will explicitly specify aromatic bonds.
             * If the value of \c %SMILES_OUTPUT_AROMATIC_BONDS is \c false, aromatic bonds are left unspecified.
             *
             * \valuetype \c bool
             * \note The setting of this control-parameter has only an effect if Chem::ControlParameter::SMILES_OUTPUT_KEKULE_FORM
             *       is set to \c false.
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_OUTPUT_AROMATIC_BONDS;

            /**
             * \brief Specifies whether to generate \e SMILES strings [\ref SMILES] where all atom symbols are enclosed in brackets.
             *
             * If the control-parameter is set to \c true, \e SMILES strings will be generated where all atoms are enclosed in
             * square brackets regardless of their atom type and the necessity to specify additional atom properties.
             * If the value of \c %SMILES_NO_ORGANIC_SUBSET is \c false, only those atoms will be enclosed in brackets that
             * require the specification of additional atomic properties (charge, hydrogen count, isotope, ...)
             * or are not part of the organic subset (i.e. <em>C, N, O, S, P, F, Cl, Br</em> and <em>I</em>).
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey SMILES_NO_ORGANIC_SUBSET;

            /**
             * \brief Specifies options for the input of \e InChI strings [\ref INCHI].
             *
             * Please refer to the <em>%InChI C-API</em> documentation [\ref INCHI] for further information about the syntax and
             * meaning of the available options.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey INCHI_INPUT_OPTIONS;

            /**
             * \brief Specifies options for the output of \e InChI strings [\ref INCHI].
             *
             * Please refer to the <em>%InChI C-API</em> documentation [\ref INCHI] for further information about the syntax and
             * meaning of the available options.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey INCHI_OUTPUT_OPTIONS;

            /**
             * \brief Specifies whether to check for and import multi-conformer molecules.
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MULTI_CONF_IMPORT;

            /**
             * \brief Specifies whether to write all molecule conformations on output.
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MULTI_CONF_EXPORT;

            extern CDPL_CHEM_API const Base::LookupKey OUTPUT_CONF_ENERGY_AS_COMMENT;

            extern CDPL_CHEM_API const Base::LookupKey CONF_INDEX_NAME_SUFFIX_PATTERN;

            /**
             * \brief Specifies an instance of Chem::MultiConfMoleculeInputProcessor that implements the logic of
             *        multi-conformer molecule detection and conformational data processing.
             * \valuetype \c Chem::MultiConfMoleculeInputProcessor::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MULTI_CONF_INPUT_PROCESSOR;

            extern CDPL_CHEM_API const Base::LookupKey CDF_OUTPUT_SINGLE_PRECISION_FLOATS;

            extern CDPL_CHEM_API const Base::LookupKey MOL2_ENABLE_EXTENDED_ATOM_TYPES;

            extern CDPL_CHEM_API const Base::LookupKey MOL2_ENABLE_AROMATIC_BOND_TYPES;

            /**
             * \since 1.2.3
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_READ_PARTIAL_AS_FORMAL_CHARGES;

            extern CDPL_CHEM_API const Base::LookupKey MOL2_CALC_FORMAL_CHARGES;

            extern CDPL_CHEM_API const Base::LookupKey MOL2_CHARGE_TYPE;

            extern CDPL_CHEM_API const Base::LookupKey MOL2_MOLECULE_TYPE;

            extern CDPL_CHEM_API const Base::LookupKey MOL2_OUTPUT_SUBSTRUCTURES;

            /**
             * \since 1.2.3
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_OUTPUT_FORMAL_CHARGES;

            extern CDPL_CHEM_API const Base::LookupKey XYZ_COMMENT_IS_NAME;
            
            extern CDPL_CHEM_API const Base::LookupKey XYZ_PERCEIVE_CONNECTIVITY;

            extern CDPL_CHEM_API const Base::LookupKey XYZ_PERCEIVE_BOND_ORDERS;

            extern CDPL_CHEM_API const Base::LookupKey XYZ_CALC_FORMAL_CHARGES;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_XML_DECLARATION;

            /**
             * \valuetype \c std::string
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_ELEMENT_NAMESPACE;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_ATOM_PARITY;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_SINGLE_BOND_STEREO;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_DOUBLE_BOND_STEREO;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_KEKULE_FORM;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_MOLECULE_NAME;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_STRUCTURE_DATA;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_ISOTOPE;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_SPIN_MULTIPLICITY;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_COMPACT_ATOM_DATA;

            /**
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_CHEM_API const Base::LookupKey CML_OUTPUT_COMPACT_BOND_DATA;

        } // namespace ControlParameter
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CONTROLPARAMETER_HPP
