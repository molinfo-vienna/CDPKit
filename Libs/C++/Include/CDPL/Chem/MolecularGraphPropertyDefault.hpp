/* 
 * MolecularGraphPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MolecularGraphPropertyDefault.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHPROPERTYDEFAULT_HPP
#define CDPL_CHEM_MOLECULARGRAPHPROPERTYDEFAULT_HPP

#include <string>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief Provides default values for built-in Chem::MolecularGraph properties.
         */
        namespace MolecularGraphPropertyDefault
        {

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::NAME property.
             */
            extern CDPL_CHEM_API const std::string                        NAME;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::COMMENT property.
             */
            extern CDPL_CHEM_API const std::string                        COMMENT;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::STOICHIOMETRIC_NUMBER property.
             */
            extern CDPL_CHEM_API const double                             STOICHIOMETRIC_NUMBER;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MATCH_CONSTRAINTS property.
             */
            extern CDPL_CHEM_API const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_CTAB_VERSION property.
             */
            extern CDPL_CHEM_API const unsigned int                       MDL_CTAB_VERSION;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_PROGRAM_NAME property.
             */
            extern CDPL_CHEM_API const std::string                        MDL_PROGRAM_NAME;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_USER_INITIALS property.
             */
            extern CDPL_CHEM_API const std::string                        MDL_USER_INITIALS;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_DIMENSIONALITY property.
             */
            extern CDPL_CHEM_API const std::size_t                        MDL_DIMENSIONALITY;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_ENERGY property.
             */
            extern CDPL_CHEM_API const double                             MDL_ENERGY;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_CHIRAL_FLAG property.
             */
            extern CDPL_CHEM_API const bool                               MDL_CHIRAL_FLAG;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR1 property.
             */
            extern CDPL_CHEM_API const long                               MDL_SCALING_FACTOR1;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MDL_SCALING_FACTOR2 property.
             */
            extern CDPL_CHEM_API const double                             MDL_SCALING_FACTOR2;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MOL2_MOLECULE_TYPE property.
             */
            extern CDPL_CHEM_API const unsigned int                       MOL2_MOLECULE_TYPE;

            /**
             * \brief Default value of the Chem::MolecularGraphProperty::MOL2_CHARGE_TYPE property.
             */
            extern CDPL_CHEM_API const unsigned int                       MOL2_CHARGE_TYPE;
        } // namespace MolecularGraphPropertyDefault
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MOLECULARGRAPHPROPERTYDEFAULT_HPP
