/* 
 * MMFF94EnergyCalculator.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94EnergyCalculator.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ENERGYCALCULATOR_HPP
#define CDPL_FORCEFIELD_MMFF94ENERGYCALCULATOR_HPP

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/ForceField/InteractionType.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Calculates the total MMFF94 force field energy for a set of atom 3D coordinates.
         *
         * The calculator takes a ForceField::MMFF94InteractionData instance (typically produced by
         * ForceField::MMFF94InteractionParameterizer) and computes the bond-stretching, angle-bending,
         * stretch-bend, out-of-plane bending, torsion, electrostatic and Van der Waals energy contributions
         * for a supplied set of atom 3D coordinates. The per-component energies are retained and made available
         * via the dedicated accessors, the calculated sum is returned by operator()() and getTotalEnergy().
         *
         * \tparam ValueType The floating-point value type used to represent the computed energies.
         * \see [\ref MMFF94]
         */
        template <typename ValueType>
        class MMFF94EnergyCalculator
        {

          public:
            /**
             * \brief Constructs the calculator without an associated ForceField::MMFF94InteractionData instance.
             *
             * operator()() will return zero until setup() has been called.
             */
            MMFF94EnergyCalculator();

            /**
             * \brief Constructs the calculator and associates it with the supplied ForceField::MMFF94InteractionData instance.
             * \param ia_data The MMFF94 interaction data to use for energy calculation.
             */
            MMFF94EnergyCalculator(const MMFF94InteractionData& ia_data);

            /**
             * \brief Enables/disables specific MMFF94 interaction-type contributions.
             * \param types Bitwise-OR combination of ForceField::InteractionType flags.
             * \note Only enabled contributions are evaluated.
             */
            void setEnabledInteractionTypes(unsigned int types);

            /**
             * \brief Returns the currently enabled interaction-type contributions.
             * \return The bitwise-OR combination of ForceField::InteractionType flags.
             */
            unsigned int getEnabledInteractionTypes() const;

            /**
             * \brief Associates the calculator with the supplied ForceField::MMFF94InteractionData instance.
             * \param ia_data The new MMFF94 interaction data to use for energy calculation.
             */
            void setup(const MMFF94InteractionData& ia_data);

            /**
             * \brief Computes the total MMFF94 energy of the conformation specified by \a coords.
             *
             * The per-component energies are stored internally and can be retrieved via the dedicated accessors.
             *
             * \tparam CoordsArray The atom coordinate array type.
             * \param coords The atom 3D coordinates.
             * \return A \c const reference to the computed total energy.
             */
            template <typename CoordsArray>
            const ValueType& operator()(const CoordsArray& coords);

            /**
             * \brief Returns the total MMFF94 energy computed by the most recent operator()() call.
             * \return A \c const reference to the total energy.
             */
            const ValueType& getTotalEnergy() const;

            /**
             * \brief Returns the bond-stretching energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the bond-stretching energy.
             */
            const ValueType& getBondStretchingEnergy() const;

            /**
             * \brief Returns the angle-bending energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the angle-bending energy.
             */
            const ValueType& getAngleBendingEnergy() const;

            /**
             * \brief Returns the stretch-bend coupling energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the stretch-bend energy.
             */
            const ValueType& getStretchBendEnergy() const;

            /**
             * \brief Returns the out-of-plane bending energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the out-of-plane bending energy.
             */
            const ValueType& getOutOfPlaneBendingEnergy() const;

            /**
             * \brief Returns the torsion energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the torsion energy.
             */
            const ValueType& getTorsionEnergy() const;

            /**
             * \brief Returns the electrostatic energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the electrostatic energy.
             */
            const ValueType& getElectrostaticEnergy() const;

            /**
             * \brief Returns the Van der Waals energy contribution computed by the most recent operator()() call.
             * \return A \c const reference to the Van der Waals energy.
             */
            const ValueType& getVanDerWaalsEnergy() const;

          private:
            const MMFF94InteractionData* interactionData;
            ValueType                    totalEnergy;
            ValueType                    bondStretchingEnergy;
            ValueType                    angleBendingEnergy;
            ValueType                    stretchBendEnergy;
            ValueType                    outOfPlaneEnergy;
            ValueType                    torsionEnergy;
            ValueType                    electrostaticEnergy;
            ValueType                    vanDerWaalsEnergy;
            unsigned int                 interactionTypes;
        };
    } // namespace ForceField
} // namespace CDPL


// Implementation
// \cond DOC_IMPL_DETAILS

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::MMFF94EnergyCalculator():
    interactionData(0), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(),
    vanDerWaalsEnergy(), interactionTypes(InteractionType::ALL)
{}

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::MMFF94EnergyCalculator(const MMFF94InteractionData& ia_data):
    interactionData(&ia_data), totalEnergy(), bondStretchingEnergy(),
    angleBendingEnergy(), stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(),
    vanDerWaalsEnergy(), interactionTypes(InteractionType::ALL)
{}

template <typename ValueType>
void CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::setEnabledInteractionTypes(unsigned int types)
{
    interactionTypes = types;
}

template <typename ValueType>
unsigned int CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getEnabledInteractionTypes() const
{
    return interactionTypes;
}

template <typename ValueType>
void CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::setup(const MMFF94InteractionData& ia_data)
{
    interactionData = &ia_data;
}

template <typename ValueType>
template <typename CoordsArray>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::operator()(const CoordsArray& coords)
{
    if (!interactionData) {
        totalEnergy          = ValueType();
        bondStretchingEnergy = ValueType();
        angleBendingEnergy   = ValueType();
        stretchBendEnergy    = ValueType();
        outOfPlaneEnergy     = ValueType();
        torsionEnergy        = ValueType();
        electrostaticEnergy  = ValueType();
        vanDerWaalsEnergy    = ValueType();

        return totalEnergy;
    }

    totalEnergy = ValueType();

    if (interactionTypes & InteractionType::BOND_STRETCHING) {
        bondStretchingEnergy = calcMMFF94BondStretchingEnergy<ValueType>(interactionData->getBondStretchingInteractions().getElementsBegin(),
                                                                         interactionData->getBondStretchingInteractions().getElementsEnd(),
                                                                         coords);
        totalEnergy += bondStretchingEnergy;

    } else
        bondStretchingEnergy = ValueType();


    if (interactionTypes & InteractionType::ANGLE_BENDING) {
        angleBendingEnergy = calcMMFF94AngleBendingEnergy<ValueType>(interactionData->getAngleBendingInteractions().getElementsBegin(),
                                                                     interactionData->getAngleBendingInteractions().getElementsEnd(),
                                                                     coords);
        totalEnergy += angleBendingEnergy;

    } else
        angleBendingEnergy = ValueType();

    if (interactionTypes & InteractionType::STRETCH_BEND) {
        stretchBendEnergy = calcMMFF94StretchBendEnergy<ValueType>(interactionData->getStretchBendInteractions().getElementsBegin(),
                                                                   interactionData->getStretchBendInteractions().getElementsEnd(),
                                                                   coords);
        totalEnergy += stretchBendEnergy;

    } else
        stretchBendEnergy = ValueType();

    if (interactionTypes & InteractionType::OUT_OF_PLANE_BENDING) {
        outOfPlaneEnergy = calcMMFF94OutOfPlaneBendingEnergy<ValueType>(interactionData->getOutOfPlaneBendingInteractions().getElementsBegin(),
                                                                        interactionData->getOutOfPlaneBendingInteractions().getElementsEnd(),
                                                                        coords);
        totalEnergy += outOfPlaneEnergy;

    } else
        outOfPlaneEnergy = ValueType();

    if (interactionTypes & InteractionType::TORSION) {
        torsionEnergy = calcMMFF94TorsionEnergy<ValueType>(interactionData->getTorsionInteractions().getElementsBegin(),
                                                           interactionData->getTorsionInteractions().getElementsEnd(),
                                                           coords);
        totalEnergy += torsionEnergy;

    } else
        torsionEnergy = ValueType();

    if (interactionTypes & InteractionType::ELECTROSTATIC) {
        electrostaticEnergy = calcMMFF94ElectrostaticEnergy<ValueType>(interactionData->getElectrostaticInteractions().getElementsBegin(),
                                                                       interactionData->getElectrostaticInteractions().getElementsEnd(),
                                                                       coords);
        totalEnergy += electrostaticEnergy;

    } else
        electrostaticEnergy = ValueType();

    if (interactionTypes & InteractionType::VAN_DER_WAALS) {
        vanDerWaalsEnergy = calcMMFF94VanDerWaalsEnergy<ValueType>(interactionData->getVanDerWaalsInteractions().getElementsBegin(),
                                                                   interactionData->getVanDerWaalsInteractions().getElementsEnd(),
                                                                   coords);
        totalEnergy += vanDerWaalsEnergy;

    } else
        vanDerWaalsEnergy = ValueType();

    return totalEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getTotalEnergy() const
{
    return totalEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getBondStretchingEnergy() const
{
    return bondStretchingEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getAngleBendingEnergy() const
{
    return angleBendingEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getStretchBendEnergy() const
{
    return stretchBendEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getOutOfPlaneBendingEnergy() const
{
    return outOfPlaneEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getTorsionEnergy() const
{
    return torsionEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getElectrostaticEnergy() const
{
    return electrostaticEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::getVanDerWaalsEnergy() const
{
    return vanDerWaalsEnergy;
}

// \endcond

#endif // CDPL_FORCEFIELD_MMFF94ENERGYCALCULATOR_HPP
