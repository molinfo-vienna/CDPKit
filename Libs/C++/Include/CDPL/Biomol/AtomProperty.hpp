/* 
 * AtomProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Biomol::AtomProperty.
 */

#ifndef CDPL_BIOMOL_ATOMPROPERTY_HPP
#define CDPL_BIOMOL_ATOMPROPERTY_HPP

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
         * \brief Provides keys for built-in Chem::Atom properties.
         */
        namespace AtomProperty
        {

            /**
             * \brief Specifies the residue name of the atom (e.g. \e CA, \e CB).
             *
             * \valuetype \c std::string
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_ATOM_NAME;

            /**
             * \brief Specifies the alternative residue name of the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_ALT_ATOM_NAME;

            /**
             * \brief Specifies whether the atom is a leaving atom in the parent residue.
             *
             * \valuetype \c bool
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_LEAVING_ATOM_FLAG;

            /**
             * \brief Specifies whether the atom is a linking atom between residues.
             *
             * \valuetype \c bool
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_LINKING_ATOM_FLAG;

            /**
             * \brief Specifies the three-letter code of the residue the atom belongs to.
             *
             * \valuetype \c std::string
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_CODE;

            /**
             * \brief Specifies the sequence number of the residue the atom belongs to.
             *
             * \valuetype \c long
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_SEQUENCE_NUMBER;

            /**
             * \brief Specifies the insertion code of the residue the atom belongs to.
             *
             * \valuetype \c char
             */
            extern CDPL_BIOMOL_API const Base::LookupKey RESIDUE_INSERTION_CODE;

            /**
             * \brief Specifies whether the atom is a heteroatom.
             *
             * \valuetype \c bool
             */
            extern CDPL_BIOMOL_API const Base::LookupKey HETERO_ATOM_FLAG;

            /**
             * \brief Specifies the serial number of the atom.
             *
             * \valuetype \c long
             */
            extern CDPL_BIOMOL_API const Base::LookupKey SERIAL_NUMBER;

            /**
             * \brief Specifies the identifier of the chain the atom belongs to.
             *
             * \valuetype \c std::string
             */
            extern CDPL_BIOMOL_API const Base::LookupKey CHAIN_ID;

            /**
             * \brief Specifies the alternate location identifier of the atom.
             *
             * \valuetype \c char
             */
            extern CDPL_BIOMOL_API const Base::LookupKey ALT_LOCATION_ID;

            /**
             * \brief Specifies the identifier of the entity the atom belongs to).
             *
             * \valuetype \c std::string
             * \since 1.2
             */
            extern CDPL_BIOMOL_API const Base::LookupKey ENTITY_ID;

            /**
             * \brief Specifies the number of the model the atom belongs to.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_BIOMOL_API const Base::LookupKey MODEL_NUMBER;

            /**
             * \brief Specifies the occupancy of the atom.
             *
             * \valuetype \c double
             */
            extern CDPL_BIOMOL_API const Base::LookupKey OCCUPANCY;

            /**
             * \brief Specifies the isotropic temperature (B) factor of the atom.
             *
             * \valuetype \c double
             */
            extern CDPL_BIOMOL_API const Base::LookupKey B_FACTOR;
        } // namespace AtomProperty
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_ATOMPROPERTY_HPP
