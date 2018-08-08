/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMFF94GradientCalculator.hpp 
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
 * \brief Definition of the class CDPL::ForceField::MMFF94GradientCalculator.
 */

#ifndef CDPL_FORCEFIELD_MMFF94GRADIENTCALCULATOR_HPP
#define CDPL_FORCEFIELD_MMFF94GRADIENTCALCULATOR_HPP

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94GradientFunctions.hpp"
#include "CDPL/ForceField/GradientVectorTraits.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_GRADIENT_CALCULATION
		 * @{
		 */

		template <typename ValueType>
		class MMFF94GradientCalculator
		{

		public:
			MMFF94GradientCalculator(const MMFF94InteractionData& ia_data);

			void setup(const MMFF94InteractionData& ia_data);

			template <typename CoordsArray, typename GradArray>
			ValueType operator()(const CoordsArray& coords, GradArray& grad);

			ValueType getTotalEnergy() const;

			ValueType getBondStretchingEnergy() const;

			ValueType getAngleBendingEnergy() const;

			ValueType getStretchBendEnergy() const;

			ValueType getOutOfPlaneBendingEnergy() const;

			ValueType getTorsionEnergy() const;

			ValueType getElectrostaticEnergy() const;

			ValueType getVanDerWaalsEnergy() const;

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
CDPL::ForceField::MMFF94GradientCalculator<ValueType>::MMFF94GradientCalculator(const MMFF94InteractionData& ia_data):
    interactionData(&ia_data), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(), 
    vanDerWaalsEnergy() 
{}

template <typename ValueType>
void CDPL::ForceField::MMFF94GradientCalculator<ValueType>::setup(const MMFF94InteractionData& ia_data)
{
    interactionData = &ia_data;
}

template <typename ValueType>
template <typename CoordsArray, typename GradArray>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::operator()(const CoordsArray& coords, GradArray& grad)
{
	GradientVectorTraits<GradArray>::clear(grad);

    bondStretchingEnergy = calcMMFF94BondStretchingGradient<ValueType>(interactionData->getBondStretchingInteractions().getElementsBegin(),
																	   interactionData->getBondStretchingInteractions().getElementsEnd(), 
																	   coords, grad);
    angleBendingEnergy = calcMMFF94AngleBendingGradient<ValueType>(interactionData->getAngleBendingInteractions().getElementsBegin(),
																   interactionData->getAngleBendingInteractions().getElementsEnd(), 
																   coords, grad);
    stretchBendEnergy = calcMMFF94StretchBendGradient<ValueType>(interactionData->getStretchBendInteractions().getElementsBegin(),
																 interactionData->getStretchBendInteractions().getElementsEnd(), 
																 coords, grad);
    outOfPlaneEnergy = calcMMFF94OutOfPlaneBendingGradient<ValueType>(interactionData->getOutOfPlaneBendingInteractions().getElementsBegin(),
																	  interactionData->getOutOfPlaneBendingInteractions().getElementsEnd(), 
																	  coords, grad);
    torsionEnergy = calcMMFF94TorsionGradient<ValueType>(interactionData->getTorsionInteractions().getElementsBegin(),
														 interactionData->getTorsionInteractions().getElementsEnd(), 
														 coords, grad);
    electrostaticEnergy = calcMMFF94ElectrostaticGradient<ValueType>(interactionData->getElectrostaticInteractions().getElementsBegin(),
																	 interactionData->getElectrostaticInteractions().getElementsEnd(), 
																	 coords, grad);
    vanDerWaalsEnergy = calcMMFF94VanDerWaalsGradient<ValueType>(interactionData->getVanDerWaalsInteractions().getElementsBegin(),
																 interactionData->getVanDerWaalsInteractions().getElementsEnd(), 
																 coords, grad);

    totalEnergy = bondStretchingEnergy + angleBendingEnergy + stretchBendEnergy +
		outOfPlaneEnergy + torsionEnergy + electrostaticEnergy + vanDerWaalsEnergy;

    return totalEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getTotalEnergy() const
{
    return totalEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getBondStretchingEnergy() const
{
    return bondStretchingEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getAngleBendingEnergy() const
{
    return angleBendingEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getStretchBendEnergy() const
{
    return stretchBendEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getOutOfPlaneBendingEnergy() const
{
    return outOfPlaneEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getTorsionEnergy() const
{
    return torsionEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getElectrostaticEnergy() const
{
    return electrostaticEnergy;
}

template <typename ValueType>
ValueType CDPL::ForceField::MMFF94GradientCalculator<ValueType>::getVanDerWaalsEnergy() const
{
    return vanDerWaalsEnergy;
}

// \endcond

#endif // CDPL_FORCEFIELD_MMFF94GRADIENTCALCULATOR_HPP
