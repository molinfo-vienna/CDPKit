/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94EnergyCalculator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::ForceField::MMFF94EnergyCalculator.
 */

#ifndef CDPL_FORCEFIELD_MMFF94ENERGYCALCULATOR_HPP
#define CDPL_FORCEFIELD_MMFF94ENERGYCALCULATOR_HPP

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_ENERGY_CALCULATION
		 * @{
		 */

		template <typename ValueType>
		class MMFF94EnergyCalculator
		{

		public:
			MMFF94EnergyCalculator();

			MMFF94EnergyCalculator(const MMFF94InteractionData& ia_data);

			void setup(const MMFF94InteractionData& ia_data);

			template <typename CoordsArray>
			const ValueType& operator()(const CoordsArray& coords);

			const ValueType& getTotalEnergy() const;

			const ValueType& getBondStretchingEnergy() const;

			const ValueType& getAngleBendingEnergy() const;

			const ValueType& getStretchBendEnergy() const;

			const ValueType& getOutOfPlaneBendingEnergy() const;

			const ValueType& getTorsionEnergy() const;

			const ValueType& getElectrostaticEnergy() const;

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
		};

		/**
		 * @}
		 */
    }
}


// Implementation
// \cond UNHIDE_DETAILS

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::MMFF94EnergyCalculator():
    interactionData(0), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(), 
    vanDerWaalsEnergy() 
{}

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::MMFF94EnergyCalculator(const MMFF94InteractionData& ia_data):
    interactionData(&ia_data), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(), 
    vanDerWaalsEnergy() 
{}

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
		totalEnergy = ValueType();
		bondStretchingEnergy = ValueType();
		angleBendingEnergy = ValueType();
		stretchBendEnergy = ValueType();
		outOfPlaneEnergy = ValueType();
		torsionEnergy = ValueType();
		electrostaticEnergy = ValueType();
		vanDerWaalsEnergy = ValueType();

		return totalEnergy;
	}

    bondStretchingEnergy = calcMMFF94BondStretchingEnergy<ValueType>(interactionData->getBondStretchingInteractions().getElementsBegin(),
																	 interactionData->getBondStretchingInteractions().getElementsEnd(), 
																	 coords);
    angleBendingEnergy = calcMMFF94AngleBendingEnergy<ValueType>(interactionData->getAngleBendingInteractions().getElementsBegin(),
																 interactionData->getAngleBendingInteractions().getElementsEnd(), 
																 coords);
    stretchBendEnergy = calcMMFF94StretchBendEnergy<ValueType>(interactionData->getStretchBendInteractions().getElementsBegin(),
															   interactionData->getStretchBendInteractions().getElementsEnd(), 
															   coords);
    outOfPlaneEnergy = calcMMFF94OutOfPlaneBendingEnergy<ValueType>(interactionData->getOutOfPlaneBendingInteractions().getElementsBegin(),
																	interactionData->getOutOfPlaneBendingInteractions().getElementsEnd(), 
																	coords);
    torsionEnergy = calcMMFF94TorsionEnergy<ValueType>(interactionData->getTorsionInteractions().getElementsBegin(),
													   interactionData->getTorsionInteractions().getElementsEnd(), 
													   coords);
    electrostaticEnergy = calcMMFF94ElectrostaticEnergy<ValueType>(interactionData->getElectrostaticInteractions().getElementsBegin(),
																   interactionData->getElectrostaticInteractions().getElementsEnd(), 
																   coords);
    vanDerWaalsEnergy = calcMMFF94VanDerWaalsEnergy<ValueType>(interactionData->getVanDerWaalsInteractions().getElementsBegin(),
															   interactionData->getVanDerWaalsInteractions().getElementsEnd(), 
															   coords);

    totalEnergy = bondStretchingEnergy + angleBendingEnergy + stretchBendEnergy +
		outOfPlaneEnergy + torsionEnergy + electrostaticEnergy + vanDerWaalsEnergy;

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
