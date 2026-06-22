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
 * \brief Definition of constants in namespace CDPL::Chem::AtomProperty.
 */

#ifndef CDPL_CHEM_ATOMPROPERTY_HPP
#define CDPL_CHEM_ATOMPROPERTY_HPP

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
         * \brief Provides keys for built-in Chem::Atom properties.
         */
        namespace AtomProperty
        {

            /**
             * \brief Specifies the name of the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey NAME;

            /**
             * \brief Specifies the element symbol of the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey SYMBOL;

            /**
             * \brief Specifies the atom type (see namespace Chem::AtomType).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey TYPE;

            /**
             * \brief Specifies the formal charge of the atom.
             *
             * \valuetype \c long
             */
            extern CDPL_CHEM_API const Base::LookupKey FORMAL_CHARGE;

            /**
             * \brief Specifies the isotopic mass number of the atom.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey ISOTOPE;

            /**
             * \brief Specifies the radical type of the atom (see namespace Chem::RadicalType).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey RADICAL_TYPE;

            /**
             * \brief Specifies the orbital hybridization state of the atom (see namespace Chem::HybridizationState).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey HYBRIDIZATION;

            /**
             * \brief Specifies whether the atom is a member of a ring system.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey RING_FLAG;

            /**
             * \brief Specifies whether the atom is a member of an aromatic ring system.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey AROMATICITY_FLAG;

            /**
             * \brief Specifies the number of unpaired electrons of the atom.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey UNPAIRED_ELECTRON_COUNT;

            /**
             * \brief Specifies the number of implicit hydrogens attached to the atom.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey IMPLICIT_HYDROGEN_COUNT;

            /**
             * \brief Specifies the 2D coordinates of the atom.
             *
             * \valuetype Math::Vector2D
             */
            extern CDPL_CHEM_API const Base::LookupKey COORDINATES_2D;

            /**
             * \brief Specifies an array of atom 3D coordinates for one or more molecular conformations.
             *
             * \valuetype Math::Vector3DArray::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey COORDINATES_3D_ARRAY;

            /**
             * \brief Specifies the canonical number of the atom obtained by the Morgan algorithm.
             * \see  [\ref MOCAN]
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey MORGAN_NUMBER;

            /**
             * \brief Specifies the canonical number of the atom.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey CANONICAL_NUMBER;

            /**
             * \brief Specifies the topological CIP priority of the atom.
             * \see [\ref TCIP]
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey CIP_PRIORITY;

            /**
             * \brief Specifies the topological symmetry class of the atom.
             * \see [\ref TOPSY]
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey SYMMETRY_CLASS;

            /**
             * \brief Specifies the stereochemical descriptor of the atom.
             *
             * \valuetype Chem::StereoDescriptor
             */
            extern CDPL_CHEM_API const Base::LookupKey STEREO_DESCRIPTOR;

            /**
             * \brief Specifies whether the atom is a stereogenic center.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey STEREO_CENTER_FLAG;

            /**
             * \brief Specifies the \e CIP stereochemical configuration label of the atom (see namespace Chem::CIPDescriptor).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey CIP_CONFIGURATION;

            /**
             * \brief Specifies the \e MDL stereo parity of the atom (see namespace Chem::MDLParity).
             * \see [\ref CTFILE]
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_PARITY;

            /**
             * \brief Specifies the value of the \e MDL <em>stereo care</em> flag of the atom.
             * \see [\ref CTFILE]
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_DB_STEREO_CARE_FLAG;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> atom type (see namespace Chem::SybylAtomType).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey SYBYL_TYPE;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> atomic partial charge.
             *
             * \valuetype \c double
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_CHARGE;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> atom name.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_NAME;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> numeric substructure identifier associated with the atom.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_SUBSTRUCTURE_ID;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> substructure name associated with the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_SUBSTRUCTURE_NAME;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> substructure subtype associated with the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_SUBSTRUCTURE_SUBTYPE;

            /**
             * \brief Specifies the <em>Sybyl MOL2</em> chain identifier associated with the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_SUBSTRUCTURE_CHAIN;

            /**
             * \brief Specifies the reaction center status of the atom (see namespace Chem::ReactionCenterStatus).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey REACTION_CENTER_STATUS;

            /**
             * \brief Specifies the atom-atom mapping ID relating reaction reactant atoms to product atoms.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey ATOM_MAPPING_ID;

            /**
             * \brief Specifies the substructure match constraints associated with the atom.
             *
             * \valuetype Chem::MatchConstraintList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;

            /**
             * \brief Specifies the substructure match expression associated with the atom.
             *
             * \valuetype Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;

            /**
             * \brief Specifies a string representation of the substructure match expression associated with the atom.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION_STRING;

            /**
             * \brief Specifies the ID of the component group the atom belongs to.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUP_ID;
        } // namespace AtomProperty
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ATOMPROPERTY_HPP
