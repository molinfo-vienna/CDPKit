/* 
 * BondProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondProperty.
 */

#ifndef CDPL_CHEM_BONDPROPERTY_HPP
#define CDPL_CHEM_BONDPROPERTY_HPP

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
         * \brief Provides keys for built-in Chem::Bond properties.
         */
        namespace BondProperty
        {

            /**
             * \brief Specifies the bond order.
             *
             * \valuetype \c std::size_t
             */
            extern CDPL_CHEM_API const Base::LookupKey ORDER;

            /**
             * \brief Specifies whether the bond is a member of any ring.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey RING_FLAG;

            /**
             * \brief Specifies whether the bond is a member of an aromatic ring system.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey AROMATICITY_FLAG;

            /**
             * \brief Specifies the stereochemical descriptor of the bond.
             *
             * \valuetype Chem::StereoDescriptor
             */
            extern CDPL_CHEM_API const Base::LookupKey STEREO_DESCRIPTOR;

            /**
             * \brief Specifies whether the bond is a stereogenic center.
             *
             * \valuetype \c bool
             */
            extern CDPL_CHEM_API const Base::LookupKey STEREO_CENTER_FLAG;

            /**
             * \brief Specifies the CIP stereochemical configuration label of the bond (see namespace Chem::CIPDescriptor).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey CIP_CONFIGURATION;

            /**
             * \brief Specifies the bond direction in SMILES and SMARTS strings (see [\ref SMILES, \ref SMARTS], namespace Chem::BondDirection).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey DIRECTION;

            /**
             * \brief Specifies the 2D stereo flag of the bond (see namespace Chem::BondStereoFlag).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey STEREO_2D_FLAG;

            /**
             * \brief Specifies the SYBYL bond type (see namespace Chem::SybylBondType).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey SYBYL_TYPE;

            /**
             * \brief Specifies the reaction center status of the bond (see namespace Chem::ReactionCenterStatus).
             *
             * \valuetype <tt>unsigned int</tt>
             */
            extern CDPL_CHEM_API const Base::LookupKey REACTION_CENTER_STATUS;

            /**
             * \brief Specifies the substructure matching constraints associated with the bond.
             *
             * \valuetype Chem::MatchConstraintList::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;

            /**
             * \brief Specifies the substructure matching expression associated with the bond.
             *
             * \valuetype Chem::MatchExpression<Chem::Bond, Chem::MolecularGraph>::SharedPointer
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;

            /**
             * \brief Specifies a string representation of the substructure matching expression associated with the bond.
             *
             * \valuetype \c std::string
             */
            extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION_STRING;
        } // namespace BondProperty
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDPROPERTY_HPP
