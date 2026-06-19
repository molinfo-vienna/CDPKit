/* 
 * MolecularGraphProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MolecularGraphProperty.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHPROPERTY_HPP
#define CDPL_CHEM_MOLECULARGRAPHPROPERTY_HPP

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
         * \brief Provides keys for built-in Chem::MolecularGraph properties.
         */
        namespace MolecularGraphProperty
        {

            /**
             * \brief Specifies the name (or title) of the molecular graph.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey NAME;

            /**
             * \brief Specifies a free-text comment associated with the molecular graph.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey COMMENT;

            /**
             * \brief Specifies a creation/modification timestamp associated with the molecular graph.
             *
             * \valuetype \c std::time_t
             */
            extern CDPL_CHEM_API const Base::LookupKey TIMESTAMP;

            /**
             * \brief Specifies the components of the molecular graph.
             *
             * \valuetype Chem::FragmentList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey COMPONENTS;

            /**
             * \brief Specifies the complete set of rings of the molecular graph.
             *
             * \valuetype Chem::FragmentList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey RINGS;

            /**
             * \brief Specifies the smallest set of smallest rings (SSSR) of the molecular graph.
             *
             * \valuetype Chem::FragmentList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey SSSR;

            /**
             * \brief Specifies the union of all rings (the cyclic substructure) of the molecular graph.
             *
             * \valuetype Chem::Fragment::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey CYCLIC_SUBSTRUCTURE;

            /**
             * \brief Specifies the union of all aromatic rings (the aromatic substructure) of the molecular graph.
             *
             * \valuetype Chem::Fragment::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey AROMATIC_SUBSTRUCTURE;

            /**
             * \brief Specifies the perceived &pi;-electron systems of the molecular graph.
             *
             * \valuetype Chem::ElectronSystemList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey PI_ELECTRON_SYSTEMS;

            /**
             * \brief Specifies the substructure match constraints associated with the molecular graph.
             *
             * \valuetype Chem::MatchConstraintList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;

            /**
             * \brief Specifies the substructure match expression associated with the molecular graph.
             *
             * \valuetype Chem::MatchExpression<Chem::MolecularGraph>::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;

            /**
             * \brief Specifies molecular graph component groups for substructure searching.
             *
             * \valuetype Chem::FragmentList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey COMPONENT_GROUPS;

            /**
             * \brief Specifies the topological (bond count) all-pair distance matrix.
             *
             * \valuetype Math::ULMatrix::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey TOPOLOGICAL_DISTANCE_MATRIX;

            /**
             * \brief Specifies the geometrical (Euclidean) all-pair distance matrix.
             *
             * \valuetype Math::DMatrix::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey GEOMETRICAL_DISTANCE_MATRIX;

            /**
             * \brief Specifies the stoichiometric multiplier of the molecular graph in a reaction (defaults to \e 1).
             *
             * \valuetype \c double
             */
            extern CDPL_CHEM_API const Base::LookupKey STOICHIOMETRIC_NUMBER;

            /**
             * \brief Specifies the index of the active conformation (within the per-atom 3D coordinates arrays).
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey CONFORMATION_INDEX;

            /**
             * \brief Specifies the conformer energy values.
             *
             * \valuetype Util::DArray::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey CONFORMER_ENERGIES;

            /**
             * \brief Specifies structured data tags attached to the molecular graph (e.g. \e MDL SD-file data fields).
             *
             * \valuetype Chem::StringDataBlock::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey STRUCTURE_DATA;

            /**
             * \brief Specifies the 64-bit topological hash code of the molecular graph.
             *
             * \valuetype \c std::uint64_t
             */
            extern CDPL_CHEM_API const Base::LookupKey HASH_CODE;

            /**
             * \brief Specifies the user initials stored in the MDL CTAB header.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_USER_INITIALS;

            /**
             * \brief Specifies the program name stored in the MDL CTAB header.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_PROGRAM_NAME;

            /**
             * \brief Specifies the registry number stored in the MDL CTAB header.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_REGISTRY_NUMBER;

            /**
             * \brief Specifies the CTAB version of the MDL connection table.
             *
             * \valuetype <tt>unsigned int</tt> (Chem::MDLDataFormatVersion value)
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_CTAB_VERSION;

            /**
             * \brief Specifies the dimensionality flag stored in the MDL CTAB header (\e 0 = unspecified, \e 2 = 2D, \e 3 = 3D).
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_DIMENSIONALITY;

            /**
             * \brief Specifies the first (integer) scaling factor stored in the MDL CTAB header.
             *
             * \valuetype \c long
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_SCALING_FACTOR1;

            /**
             * \brief Specifies the second (floating-point) scaling factor stored in the MDL CTAB header.
             *
             * \valuetype \c double
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_SCALING_FACTOR2;

            /**
             * \brief Specifies the energy value stored in the MDL CTAB header.
             *
             * \valuetype \c double
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_ENERGY;

            /**
             * \brief Specifies the chiral flag stored in the MDL CTAB header.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey MDL_CHIRAL_FLAG;

            /**
             * \brief Specifies the partial-charge type of the molecular graph in the <em>Sybyl MOL2</em> format.
             *
             * \valuetype <tt>unsigned int</tt> (Chem::MOL2ChargeType value)
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_CHARGE_TYPE;

            /**
             * \brief Specifies the molecule type of the molecular graph in the <em>Sybyl MOL2</em> format.
             *
             * \valuetype <tt>unsigned int</tt> (Chem::MOL2MoleculeType value)
             */
            extern CDPL_CHEM_API const Base::LookupKey MOL2_MOLECULE_TYPE;
        } // namespace MolecularGraphProperty
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPHPROPERTY_HPP
