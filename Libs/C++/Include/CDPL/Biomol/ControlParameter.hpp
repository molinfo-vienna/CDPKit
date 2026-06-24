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
 * \brief Definition of constants in namespace CDPL::Biomol::ControlParameter.
 */

#ifndef CDPL_BIOMOL_CONTROLPARAMETER_HPP
#define CDPL_BIOMOL_CONTROLPARAMETER_HPP

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }

    namespace Biomol
    {

        /**
         * \brief Provides keys for built-in control-parameters.
         */
        namespace ControlParameter
        {

            /**
             * \brief Specifies whether non-fatal recoverable I/O errors should be ignored or cause an I/O operation to fail.
             *
             * If the parameter is set to \c true, not only severe errors cause an I/O operation to fail, but also
             * non-fatal errors from which a recovery would be possible. 
             * If the parameter is set to \c false, I/O operations will proceed even if a non-fatal error has been
             * detected.
             *
             * \valuetype \c bool
             */
            extern CDPL_BIOMOL_API const Base::LookupKey STRICT_ERROR_CHECKING;

            /**
             * \brief Specifies whether to check if data lines exceed the maximum allowed line length when reading or writing data
             *        in \e PDB format.
             *
             * If the parameter is set to \c true, the length of data lines that were read from or have to
             * be written to data encoded in the \e PDB format will be checked against the maximum
             * allowed line length. Lines that exceeded the line length limit are considered as an error condition and cause
             * the input or output operation to fail. If \c %CHECK_LINE_LENGTH is \c false, the length of data lines will
             * not be checked and has no impact on the success of the performed I/O operation.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey CHECK_LINE_LENGTH;

            /**
             * \brief Specifies the residue dictionary consulted during \e PDB and \e mmCIF I/O when looking up canonical residue
             *        atom names, bonding, atom types, and formal charges.
             *
             * \valuetype Biomol::ResidueDictionary::SharedPointer
             * \see [\ref PDB, \ref MMCIF]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_DICTIONARY;

            /**
             * \brief Specifies whether to apply the formal atom charges provided by the residue dictionary during input data
             *        postprocessing.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey APPLY_DICT_FORMAL_CHARGES;

            /**
             * \brief Specifies whether to apply the atom types provided by the residue dictionary during input data
             *        postprocessing.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey APPLY_DICT_ATOM_TYPES;

            /**
             * \brief Specifies whether to calculate formal atomic charges for atoms whose charge could not be obtained from
             *        the input data or the residue dictionary.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey CALC_MISSING_FORMAL_CHARGES;

            /**
             * \brief Specifies whether to perceive bond orders for bonds whose order could not be obtained from the input
             *        data or the residue dictionary.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PERCEIVE_MISSING_BOND_ORDERS;

            /**
             * \brief Specifies whether to merge alternative residue conformers whose atoms overlap in space.
             *
             * \valuetype \c bool
             * \see Biomol::combineInterferingResidueCoordinates()
             */
            extern CDPL_BIOMOL_API const Base::LookupKey COMBINE_INTERFERING_RESIDUE_COORDINATES;

            /**
             * \brief Specifies whether to use the residue dictionary to generate bonds for atoms of non-standard
             *        residues when reading \e PDB data.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_ATOM_BONDING_TO_NON_STD_RESIDUES;

            /**
             * \brief Specifies whether to use the residue dictionary to generate bonds for atoms of standard residues
             *        when reading \e PDB data.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_ATOM_BONDING_TO_STD_RESIDUES;

            /**
             * \brief Specifies whether to apply the residue dictionary bond orders to bonds of non-standard residues when
             *        reading \e PDB data.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_BOND_ORDERS_TO_NON_STD_RESIDUES;

            /**
             * \brief Specifies whether to apply residue dictionary bond orders to bonds of standard residues when
             *        reading \e PDB data.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_APPLY_DICT_BOND_ORDERS_TO_STD_RESIDUES;

            /**
             * \brief Specifies whether to ignore bonding information provided by \c CONECT records when reading \e PDB data.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_IGNORE_CONECT_RECORDS;

            /**
             * \brief Specifies whether to deduce bond orders from the duplication pattern of bonded atom pairs in \c CONECT
             *        records when reading \e PDB data.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_DEDUCE_BOND_ORDERS_FROM_CONECT_RECORDS;

            /**
             * \brief Specifies whether to ignore the formal charge field of <tt>ATOM/HETATM</tt> records when reading \e PDB data.
             *
             * \valuetype \c bool
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_IGNORE_FORMAL_CHARGE_FIELD;

            /**
             * \brief Specifies whether to verify the record counts in the \e PDB \c MASTER record against the actual numbers
             *        observed during data reading.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_EVALUATE_MASTER_RECORD;

            /**
             * \brief Specifies whether to truncate output \e PDB data lines that exceed the maximum allowed line length instead
             *        of failing the write operation.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_TRUNCATE_LINES;

            /**
             * \brief Specifies whether to write the formal charge field of <tt>ATOM/HETATM</tt> records when generating \e PDB output.
             *
             * \valuetype \c bool
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_OUTPUT_FORMAL_CHARGES;

            /**
             * \brief Specifies whether to write \c CONECT records when generating \e PDB output.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_OUTPUT_CONECT_RECORDS;

            /**
             * \brief Specifies whether \c CONECT records shall be written for all bonds (and not only for non-standard ones)
             *        when generating \e PDB output.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_OUTPUT_CONECT_RECORDS_FOR_ALL_BONDS;

            /**
             * \brief Specifies whether \c CONECT records shall encode the bond order via the duplication count of bonded atom
             *        pairs when generating \e PDB output.
             *
             * \valuetype \c bool
             * \see [\ref PDB]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_OUTPUT_CONECT_RECORDS_REFLECTING_BOND_ORDER;

            /**
             * \brief Specifies the \e PDB format version to use when generating \e PDB output (see Biomol::PDBFormatVersion).
             *
             * \valuetype <tt>unsigned int</tt>
             * \see [\ref PDB]
             */
            extern CDPL_BIOMOL_API const Base::LookupKey PDB_FORMAT_VERSION;

            /**
             * \brief Specifies whether to use residue dictionary information for bond generation when reading \e mmCIF data
             *
             * \valuetype \c bool
             * \see [\ref MMCIF]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey MMCIF_APPLY_DICT_ATOM_BONDING;

            /**
             * \brief Specifies whether to apply residue dictionary bond order information when reading \e mmCIF data.
             *
             * \valuetype \c bool
             * \see [\ref MMCIF]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey MMCIF_APPLY_DICT_BOND_ORDERS;

            /**
             * \brief Specifies whether or not residue structures shall be emitted as \c chem_comp category data
             *        when generating \e mmCIF output.
             *
             * \valuetype \c bool
             * \see [\ref MMCIF]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey MMCIF_OUTPUT_BIOPOLYMERS_AS_CHEM_COMP;

            /**
             * \brief Specifies a postprocessing function that is applied to the constructed \e mmCIF data record before its output.
             *
             * \valuetype Biomol::MMCIFDataProcessingFunction
             * \see [\ref MMCIF]
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey MMCIF_OUTPUT_DATA_POSTPROC_FUNCTION;
        } // namespace ControlParameter
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_CONTROLPARAMETER_HPP
