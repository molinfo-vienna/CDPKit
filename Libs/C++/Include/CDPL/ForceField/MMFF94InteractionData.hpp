/* 
 * MMFF94InteractionData.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94InteractionData.
 */

#ifndef CDPL_FORCEFIELD_MMFF94INTERACTIONDATA_HPP
#define CDPL_FORCEFIELD_MMFF94INTERACTIONDATA_HPP

#include <memory>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionList.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionList.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionList.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionList.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Container holding the full set of MMFF94 interaction parameter records for a molecular graph.
         *
         * The class aggregates the seven per-interaction lists that together describe the energy expression
         * of the MMFF94 force field (bond stretching, angle bending, stretch-bend coupling, out-of-plane bending,
         * torsion, electrostatic and Van der Waals interactions). Instances are typically produced by
         * ForceField::MMFF94InteractionParameterizer and consumed by ForceField::MMFF94EnergyCalculator or
         * ForceField::MMFF94GradientCalculator.
         *
         * \see [\ref MMFF94]
         */
        class CDPL_FORCEFIELD_API MMFF94InteractionData
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %MMFF94InteractionData instances.
             */
            typedef std::shared_ptr<MMFF94InteractionData> SharedPointer;

            /**
             * \brief Returns the list of MMFF94 bond-stretching interactions.
             * \return A \c const reference to the bond-stretching interaction list.
             */
            const MMFF94BondStretchingInteractionList& getBondStretchingInteractions() const;

            /**
             * \brief Returns the list of MMFF94 bond-stretching interactions.
             * \return A reference to the bond-stretching interaction list.
             */
            MMFF94BondStretchingInteractionList& getBondStretchingInteractions();

            /**
             * \brief Returns the list of MMFF94 angle-bending interactions.
             * \return A \c const reference to the angle-bending interaction list.
             */
            const MMFF94AngleBendingInteractionList& getAngleBendingInteractions() const;

            /**
             * \brief Returns the list of MMFF94 angle-bending interactions.
             * \return A reference to the angle-bending interaction list.
             */
            MMFF94AngleBendingInteractionList& getAngleBendingInteractions();

            /**
             * \brief Returns the list of MMFF94 stretch-bend interactions.
             * \return A \c const reference to the stretch-bend interaction list.
             */
            const MMFF94StretchBendInteractionList& getStretchBendInteractions() const;

            /**
             * \brief Returns the list of MMFF94 stretch-bend interactions.
             * \return A reference to the stretch-bend interaction list.
             */
            MMFF94StretchBendInteractionList& getStretchBendInteractions();

            /**
             * \brief Returns the list of MMFF94 out-of-plane bending interactions.
             * \return A \c const reference to the out-of-plane bending interaction list.
             */
            const MMFF94OutOfPlaneBendingInteractionList& getOutOfPlaneBendingInteractions() const;

            /**
             * \brief Returns the list of MMFF94 out-of-plane bending interactions.
             * \return A reference to the out-of-plane bending interaction list.
             */
            MMFF94OutOfPlaneBendingInteractionList& getOutOfPlaneBendingInteractions();

            /**
             * \brief Returns the list of MMFF94 torsion interactions.
             * \return A \c const reference to the torsion interaction list.
             */
            const MMFF94TorsionInteractionList& getTorsionInteractions() const;

            /**
             * \brief Returns the list of MMFF94 torsion interactions.
             * \return A reference to the torsion interaction list.
             */
            MMFF94TorsionInteractionList& getTorsionInteractions();

            /**
             * \brief Returns the list of MMFF94 electrostatic interactions.
             * \return A \c const reference to the electrostatic interaction list.
             */
            const MMFF94ElectrostaticInteractionList& getElectrostaticInteractions() const;

            /**
             * \brief Returns the list of MMFF94 electrostatic interactions.
             * \return A reference to the electrostatic interaction list.
             */
            MMFF94ElectrostaticInteractionList& getElectrostaticInteractions();

            /**
             * \brief Returns the list of MMFF94 Van der Waals interactions.
             * \return A \c const reference to the Van der Waals interaction list.
             */
            const MMFF94VanDerWaalsInteractionList& getVanDerWaalsInteractions() const;

            /**
             * \brief Returns the list of MMFF94 Van der Waals interactions.
             * \return A reference to the Van der Waals interaction list.
             */
            MMFF94VanDerWaalsInteractionList& getVanDerWaalsInteractions();

            /**
             * \brief Removes all stored interactions from every interaction list.
             */
            void clear();

            /**
             * \brief Swaps the contents (all interaction lists) of this instance with \a ia_data.
             * \param ia_data The other interaction data instance.
             */
            void swap(MMFF94InteractionData& ia_data);

          private:
            MMFF94BondStretchingInteractionList    bondStretchingData;
            MMFF94AngleBendingInteractionList      angleBendingData;
            MMFF94StretchBendInteractionList       stretchBendData;
            MMFF94OutOfPlaneBendingInteractionList outOfPlaneData;
            MMFF94TorsionInteractionList           torsionData;
            MMFF94ElectrostaticInteractionList     electrostaticData;
            MMFF94VanDerWaalsInteractionList       vanDerWaalsData;
        };
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94INTERACTIONDATA_HPP
