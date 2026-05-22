/* 
 * MMFF94GradientCalculator.hpp 
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
 * \brief Definition of class CDPL::ForceField::MMFF94GradientCalculator.
 */

#ifndef CDPL_FORCEFIELD_MMFF94GRADIENTCALCULATOR_HPP
#define CDPL_FORCEFIELD_MMFF94GRADIENTCALCULATOR_HPP

#include <cstddef>

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/MMFF94GradientFunctions.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/GradientVectorTraits.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL
{

    namespace ForceField
    {

        /**
         * \brief Evaluates the total MMFF94 force-field energy and its gradient with respect to the atomic coordinates.
         *
         * The calculator takes a ForceField::MMFF94InteractionData instance and the atom count of the molecule
         * and computes both the total MMFF94 energy and the analytical Cartesian gradient
         * \f$ \partial E / \partial \mathbf{r}_i \f$ for each atom. The per-component energies are retained
         * and made available via the dedicated accessors. A bit mask can be set to mark atoms whose gradient
         * contributions are zeroed, freezing them during an energy minimization.
         *
         * \tparam ValueType The floating-point value type used to represent the computed energies and gradients.
         */
        template <typename ValueType>
        class MMFF94GradientCalculator
        {

          public:
            /**
             * \brief Constructs the calculator without any associated interaction data.
             *
             * Operator() will return zero until setup() has been called.
             */
            MMFF94GradientCalculator();

            /**
             * \brief Constructs the calculator and associates it with the supplied MMFF94 interaction data.
             * \param ia_data The MMFF94 interaction data to use during energy/gradient evaluation.
             * \param num_atoms The number of atoms in the parameterized molecular graph.
             */
            MMFF94GradientCalculator(const MMFF94InteractionData& ia_data, std::size_t num_atoms);

            /**
             * \brief Enables/disables specific MMFF94 interaction-type contributions.
             * \param types Bitwise-OR combination of ForceField::InteractionType flags. Only the listed contributions are evaluated.
             */
            void setEnabledInteractionTypes(unsigned int types);

            /**
             * \brief Returns the currently enabled interaction-type contributions.
             * \return The bitwise-OR combination of ForceField::InteractionType flags.
             */
            unsigned int getEnabledInteractionTypes() const;

            /**
             * \brief Associates the calculator with the supplied MMFF94 interaction data and atom count.
             * \param ia_data The new MMFF94 interaction data.
             * \param num_atoms The number of atoms in the parameterized molecular graph.
             */
            void setup(const MMFF94InteractionData& ia_data, std::size_t num_atoms);

            /**
             * \brief Computes the total MMFF94 energy of the conformation \a coords without evaluating the gradient.
             * \tparam CoordsArray The coordinate-array type.
             * \param coords The 3D coordinates of the molecule.
             * \return A \c const reference to the computed total energy.
             */
            template <typename CoordsArray>
            const ValueType& operator()(const CoordsArray& coords);

            /**
             * \brief Computes the total MMFF94 energy and the per-atom gradient of the conformation \a coords.
             *
             * Gradients of atoms marked in the fixed-atom mask (see setFixedAtomMask()) are zeroed after evaluation.
             *
             * \tparam CoordsArray The coordinate-array type.
             * \tparam GradVector The gradient-vector type (must satisfy ForceField::GradientVectorTraits requirements).
             * \param coords The 3D coordinates of the molecule.
             * \param grad The output gradient vector.
             * \return A \c const reference to the computed total energy.
             */
            template <typename CoordsArray, typename GradVector>
            const ValueType& operator()(const CoordsArray& coords, GradVector& grad);

            /**
             * \brief Returns the total MMFF94 energy computed by the most recent operator() call.
             * \return A \c const reference to the total energy.
             */
            const ValueType& getTotalEnergy() const;

            /**
             * \brief Returns the bond-stretching energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the bond-stretching energy.
             */
            const ValueType& getBondStretchingEnergy() const;

            /**
             * \brief Returns the angle-bending energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the angle-bending energy.
             */
            const ValueType& getAngleBendingEnergy() const;

            /**
             * \brief Returns the stretch-bend coupling energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the stretch-bend energy.
             */
            const ValueType& getStretchBendEnergy() const;

            /**
             * \brief Returns the out-of-plane bending energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the out-of-plane bending energy.
             */
            const ValueType& getOutOfPlaneBendingEnergy() const;

            /**
             * \brief Returns the torsion energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the torsion energy.
             */
            const ValueType& getTorsionEnergy() const;

            /**
             * \brief Returns the electrostatic energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the electrostatic energy.
             */
            const ValueType& getElectrostaticEnergy() const;

            /**
             * \brief Returns the van der Waals energy contribution computed by the most recent operator() call.
             * \return A \c const reference to the van der Waals energy.
             */
            const ValueType& getVanDerWaalsEnergy() const;

            /**
             * \brief Returns the bit mask flagging atoms whose gradient components are zeroed after evaluation.
             * \return A \c const reference to the fixed-atom bit mask.
             */
            const Util::BitSet& getFixedAtomMask() const;

            /**
             * \brief Sets the bit mask flagging atoms whose gradient components shall be zeroed after evaluation.
             * \param mask The new fixed-atom bit mask (bit \e i set freezes atom \e i during minimization).
             */
            void setFixedAtomMask(const Util::BitSet& mask);

            /**
             * \brief Clears the fixed-atom mask so that all atoms contribute to the gradient.
             */
            void resetFixedAtomMask();

          private:
            const MMFF94InteractionData* interactionData;
            std::size_t                  numAtoms;
            ValueType                    totalEnergy;
            ValueType                    bondStretchingEnergy;
            ValueType                    angleBendingEnergy;
            ValueType                    stretchBendEnergy;
            ValueType                    outOfPlaneEnergy;
            ValueType                    torsionEnergy;
            ValueType                    electrostaticEnergy;
            ValueType                    vanDerWaalsEnergy;
            unsigned int                 interactionTypes;
            Util::BitSet                 fixedAtomMask;
        };
    } // namespace ForceField
} // namespace CDPL


// Implementation
// \cond DOC_IMPL_DETAILS

template <typename ValueType>
CDPL::ForceField::MMFF94GradientCalculator<ValueType>::MMFF94GradientCalculator():
    interactionData(0), numAtoms(0), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(),
    vanDerWaalsEnergy(), interactionTypes(InteractionType::ALL)
{}

template <typename ValueType>
CDPL::ForceField::MMFF94GradientCalculator<ValueType>::MMFF94GradientCalculator(const MMFF94InteractionData& ia_data, std::size_t num_atoms):
    interactionData(&ia_data), numAtoms(num_atoms), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(),
    vanDerWaalsEnergy(), interactionTypes(InteractionType::ALL)
{}

template <typename ValueType>
void CDPL::ForceField::MMFF94GradientCalculator<ValueType>::setEnabledInteractionTypes(unsigned int types)
{
    interactionTypes = types;
}

template <typename ValueType>
unsigned int CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getEnabledInteractionTypes() const
{
    return interactionTypes;
}

template <typename ValueType>
void CDPL::ForceField::MMFF94GradientCalculator<ValueType>::setup(const MMFF94InteractionData& ia_data, std::size_t num_atoms)
{
    interactionData = &ia_data;
    numAtoms        = num_atoms;
}

template <typename ValueType>
template <typename CoordsArray>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::operator()(const CoordsArray& coords)
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
template <typename CoordsArray, typename GradVector>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::operator()(const CoordsArray& coords, GradVector& grad)
{
    GradientVectorTraits<GradVector>::clear(grad, numAtoms);

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
        bondStretchingEnergy = calcMMFF94BondStretchingGradient<ValueType>(interactionData->getBondStretchingInteractions().getElementsBegin(),
                                                                           interactionData->getBondStretchingInteractions().getElementsEnd(),
                                                                           coords, grad);
        totalEnergy += bondStretchingEnergy;

    } else
        bondStretchingEnergy = ValueType();

    if (interactionTypes & InteractionType::ANGLE_BENDING) {
        angleBendingEnergy = calcMMFF94AngleBendingGradient<ValueType>(interactionData->getAngleBendingInteractions().getElementsBegin(),
                                                                       interactionData->getAngleBendingInteractions().getElementsEnd(),
                                                                       coords, grad);
        totalEnergy += angleBendingEnergy;

    } else
        angleBendingEnergy = ValueType();

    if (interactionTypes & InteractionType::STRETCH_BEND) {
        stretchBendEnergy = calcMMFF94StretchBendGradient<ValueType>(interactionData->getStretchBendInteractions().getElementsBegin(),
                                                                     interactionData->getStretchBendInteractions().getElementsEnd(),
                                                                     coords, grad);
        totalEnergy += stretchBendEnergy;

    } else
        stretchBendEnergy = ValueType();

    if (interactionTypes & InteractionType::OUT_OF_PLANE_BENDING) {
        outOfPlaneEnergy = calcMMFF94OutOfPlaneBendingGradient<ValueType>(interactionData->getOutOfPlaneBendingInteractions().getElementsBegin(),
                                                                          interactionData->getOutOfPlaneBendingInteractions().getElementsEnd(),
                                                                          coords, grad);
        totalEnergy += outOfPlaneEnergy;

    } else
        outOfPlaneEnergy = ValueType();

    if (interactionTypes & InteractionType::TORSION) {
        torsionEnergy = calcMMFF94TorsionGradient<ValueType>(interactionData->getTorsionInteractions().getElementsBegin(),
                                                             interactionData->getTorsionInteractions().getElementsEnd(),
                                                             coords, grad);
        totalEnergy += torsionEnergy;

    } else
        torsionEnergy = ValueType();

    if (interactionTypes & InteractionType::ELECTROSTATIC) {
        electrostaticEnergy = calcMMFF94ElectrostaticGradient<ValueType>(interactionData->getElectrostaticInteractions().getElementsBegin(),
                                                                         interactionData->getElectrostaticInteractions().getElementsEnd(),
                                                                         coords, grad);
        totalEnergy += electrostaticEnergy;

    } else
        electrostaticEnergy = ValueType();

    if (interactionTypes & InteractionType::VAN_DER_WAALS) {
        vanDerWaalsEnergy = calcMMFF94VanDerWaalsGradient<ValueType>(interactionData->getVanDerWaalsInteractions().getElementsBegin(),
                                                                     interactionData->getVanDerWaalsInteractions().getElementsEnd(),
                                                                     coords, grad);
        totalEnergy += vanDerWaalsEnergy;

    } else
        vanDerWaalsEnergy = ValueType();

    if (!fixedAtomMask.empty())
        for (Util::BitSet::size_type i = fixedAtomMask.find_first(); i != Util::BitSet::npos; i = fixedAtomMask.find_next(i))
            grad[i].clear(ValueType());

    return totalEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getTotalEnergy() const
{
    return totalEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getBondStretchingEnergy() const
{
    return bondStretchingEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getAngleBendingEnergy() const
{
    return angleBendingEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getStretchBendEnergy() const
{
    return stretchBendEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getOutOfPlaneBendingEnergy() const
{
    return outOfPlaneEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getTorsionEnergy() const
{
    return torsionEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getElectrostaticEnergy() const
{
    return electrostaticEnergy;
}

template <typename ValueType>
const ValueType& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getVanDerWaalsEnergy() const
{
    return vanDerWaalsEnergy;
}

template <typename ValueType>
const CDPL::Util::BitSet& CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getFixedAtomMask() const
{
    return fixedAtomMask;
}

template <typename ValueType>
void CDPL::ForceField::MMFF94GradientCalculator<ValueType>::setFixedAtomMask(const Util::BitSet& mask)
{
    fixedAtomMask = mask;
}

template <typename ValueType>
void CDPL::ForceField::MMFF94GradientCalculator<ValueType>::resetFixedAtomMask()
{
    fixedAtomMask.clear();
}

// \endcond

#endif // CDPL_FORCEFIELD_MMFF94GRADIENTCALCULATOR_HPP
