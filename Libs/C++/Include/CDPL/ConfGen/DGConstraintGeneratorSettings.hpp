/* 
 * DGConstraintGeneratorSettings.hpp 
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
 * \brief Definition of class CDPL::ConfGen::DGConstraintGeneratorSettings.
 */

#ifndef CDPL_CONFGEN_DGCONSTRAINTGENERATORSETTINGS_HPP
#define CDPL_CONFGEN_DGCONSTRAINTGENERATORSETTINGS_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Bundle of configuration parameters for distance-geometry constraint generation via class ConfGen::DGConstraintGenerator.
         */
        class CDPL_CONFGEN_API DGConstraintGeneratorSettings
        {

          public:
            /** \brief A static instance providing configuration parameter default values. */
            static const DGConstraintGeneratorSettings DEFAULT;

            /**
             * \brief Constructs the \c %DGConstraintGeneratorSettings instance with default configuration parameter values.
             */
            DGConstraintGeneratorSettings();

            /**
             * \brief Virtual destructor.
             */
            virtual ~DGConstraintGeneratorSettings() {}

            /**
             * \brief Specifies whether hydrogen atoms shall be excluded from the constraint set.
             * \param exclude If \c true, hydrogen atoms are skipped during constraint generation.
             */
            void excludeHydrogens(bool exclude);

            /**
             * \brief Tells whether hydrogen atoms are excluded from the constraint set.
             * \return \c true if hydrogens are excluded, and \c false otherwise.
             */
            bool excludeHydrogens() const;

            /**
             * \brief Specifies whether atom stereo center configurations shall be enforced by volume constraints.
             * \param regard If \c true, atom-configuration constraints are added.
             */
            void regardAtomConfiguration(bool regard);

            /**
             * \brief Tells whether atom stereo center configurations are enforced.
             * \return \c true if atom-configuration constraints are added, and \c false otherwise.
             */
            bool regardAtomConfiguration() const;

            /**
             * \brief Specifies whether bond stereo center configurations (cis/trans) shall be enforced.
             * \param regard If \c true, bond-configuration constraints are added.
             */
            void regardBondConfiguration(bool regard);

            /**
             * \brief Tells whether bond stereo center configurations are enforced.
             * \return \c true if bond-configuration constraints are added, and \c false otherwise.
             */
            bool regardBondConfiguration() const;

          private:
            bool exclHydrogens;
            bool atomConfig;
            bool bondConfig;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_DGCONSTRAINTGENERATORSETTINGS_HPP
