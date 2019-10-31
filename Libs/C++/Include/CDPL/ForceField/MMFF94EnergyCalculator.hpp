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

#include <memory>

#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/Math/Matrix.hpp"


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

			MMFF94EnergyCalculator(const MMFF94EnergyCalculator& calc);

			MMFF94EnergyCalculator(const MMFF94InteractionData& ia_data, std::size_t num_atoms);

			void setEnabledInteractionTypes(unsigned int types);

			unsigned int getEnabledInteractionTypes() const;

			void setup(const MMFF94InteractionData& ia_data, std::size_t num_atoms);

			void enableSpeedOptimizations(bool enable);

			bool enableSpeedOptimizations() const;

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

			MMFF94EnergyCalculator& operator=(const MMFF94EnergyCalculator& calc);

		private:
			typedef Math::Matrix<ValueType> DistanceMatrix;
			typedef std::auto_ptr<DistanceMatrix> DistanceMatrixPtr;

			const MMFF94InteractionData* interactionData;
			std::size_t                  numAtoms;
			bool                         optEnabled;
			ValueType                    totalEnergy;
			ValueType                    bondStretchingEnergy;
			ValueType                    angleBendingEnergy;
			ValueType                    stretchBendEnergy;
			ValueType                    outOfPlaneEnergy;
			ValueType                    torsionEnergy;
			ValueType                    electrostaticEnergy;
			ValueType                    vanDerWaalsEnergy;
			unsigned int                 interactionTypes;
			DistanceMatrixPtr            distMatrix;
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
    interactionData(0), numAtoms(0), optEnabled(false), totalEnergy(), bondStretchingEnergy(), angleBendingEnergy(),
    stretchBendEnergy(), outOfPlaneEnergy(), torsionEnergy(), electrostaticEnergy(), 
    vanDerWaalsEnergy(), interactionTypes(InteractionType::ALL)
{}

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::MMFF94EnergyCalculator(const MMFF94EnergyCalculator& calc):
    interactionData(calc.interactionData), numAtoms(calc.numAtoms), optEnabled(calc.optEnabled),
	totalEnergy(calc.totalEnergy), bondStretchingEnergy(calc.bondStretchingEnergy), 
	angleBendingEnergy(calc.angleBendingEnergy), stretchBendEnergy(calc.stretchBendEnergy), 
	outOfPlaneEnergy(calc.outOfPlaneEnergy), torsionEnergy(calc.torsionEnergy), 
	electrostaticEnergy(calc.electrostaticEnergy), vanDerWaalsEnergy(calc.vanDerWaalsEnergy),
	interactionTypes(calc.interactionTypes)
{}

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::MMFF94EnergyCalculator(const MMFF94InteractionData& ia_data, std::size_t num_atoms):
    interactionData(&ia_data), numAtoms(num_atoms), optEnabled(false), totalEnergy(), bondStretchingEnergy(),
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
void CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::setup(const MMFF94InteractionData& ia_data, std::size_t num_atoms)
{
    interactionData = &ia_data;
	numAtoms = num_atoms;
}

template <typename ValueType>
void CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::enableSpeedOptimizations(bool enable)
{
	optEnabled = enable;
}

template <typename ValueType>
bool CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::enableSpeedOptimizations() const
{
	return optEnabled;
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

	totalEnergy = ValueType();

	if (optEnabled) {
		if (!distMatrix.get())
			distMatrix.reset(new DistanceMatrix(numAtoms, numAtoms));
		else if (distMatrix->getSize1() != numAtoms)
			distMatrix->resize(numAtoms, numAtoms, false);
				
		DistanceMatrix& dist_mtx = *distMatrix;

		for (std::size_t i = 0; i < numAtoms; i++) {
			for (std::size_t j = 0; j < numAtoms; j++) {
				if (i == j) {
					dist_mtx(i, j) = ValueType();
					continue;
				}

				ValueType dist = calcDistance<ValueType>(coords[i], coords[j]);

				dist_mtx(i, j) = dist;
				dist_mtx(j, i) = dist;
			}
		}

		if (interactionTypes & InteractionType::BOND_STRETCHING) {
			bondStretchingEnergy = calcMMFF94BondStretchingEnergy<ValueType>(interactionData->getBondStretchingInteractions().getElementsBegin(),
																			 interactionData->getBondStretchingInteractions().getElementsEnd(), 
																			 dist_mtx, coords);
			totalEnergy += bondStretchingEnergy;

		} else 
			bondStretchingEnergy = ValueType();


		if (interactionTypes & InteractionType::ANGLE_BENDING){
			angleBendingEnergy = calcMMFF94AngleBendingEnergy<ValueType>(interactionData->getAngleBendingInteractions().getElementsBegin(),
																		 interactionData->getAngleBendingInteractions().getElementsEnd(), 
																		 dist_mtx, coords);
			totalEnergy += angleBendingEnergy;

		} else 
			angleBendingEnergy = ValueType();

		if (interactionTypes & InteractionType::STRETCH_BEND) {
			stretchBendEnergy = calcMMFF94StretchBendEnergy<ValueType>(interactionData->getStretchBendInteractions().getElementsBegin(),
																	   interactionData->getStretchBendInteractions().getElementsEnd(), 
																	   dist_mtx, coords);
			totalEnergy += stretchBendEnergy;

		} else 
			stretchBendEnergy = ValueType();

		if (interactionTypes & InteractionType::OUT_OF_PLANE_BENDING) {
			outOfPlaneEnergy = calcMMFF94OutOfPlaneBendingEnergy<ValueType>(interactionData->getOutOfPlaneBendingInteractions().getElementsBegin(),
																			interactionData->getOutOfPlaneBendingInteractions().getElementsEnd(), 
																			dist_mtx, coords);
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
																		   dist_mtx, coords);
			totalEnergy += electrostaticEnergy;

		} else 
			electrostaticEnergy = ValueType();

		if (interactionTypes & InteractionType::VAN_DER_WAALS) {
			vanDerWaalsEnergy = calcMMFF94VanDerWaalsEnergy<ValueType>(interactionData->getVanDerWaalsInteractions().getElementsBegin(),
																	   interactionData->getVanDerWaalsInteractions().getElementsEnd(), 
																	   dist_mtx, coords);
			totalEnergy += vanDerWaalsEnergy;

		} else 
			vanDerWaalsEnergy = ValueType();

	} else {
		if (interactionTypes & InteractionType::BOND_STRETCHING) {
			bondStretchingEnergy = calcMMFF94BondStretchingEnergy<ValueType>(interactionData->getBondStretchingInteractions().getElementsBegin(),
																			 interactionData->getBondStretchingInteractions().getElementsEnd(), 
																			 coords);
			totalEnergy += bondStretchingEnergy;

		} else 
			bondStretchingEnergy = ValueType();


		if (interactionTypes & InteractionType::ANGLE_BENDING){
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
	}

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

template <typename ValueType>
CDPL::ForceField::MMFF94EnergyCalculator<ValueType>& CDPL::ForceField::MMFF94EnergyCalculator<ValueType>::operator=(const MMFF94EnergyCalculator& calc)
{
	if (this == &calc)
		return *this;

	interactionData = calc.interactionData; 
	numAtoms = calc.numAtoms; 
	optEnabled = calc.optEnabled;
	totalEnergy = calc.totalEnergy; 
	bondStretchingEnergy = calc.bondStretchingEnergy; 
	angleBendingEnergy = calc.angleBendingEnergy; 
	stretchBendEnergy = calc.stretchBendEnergy; 
	outOfPlaneEnergy = calc.outOfPlaneEnergy;
	torsionEnergy = calc.torsionEnergy; 
	electrostaticEnergy = calc.electrostaticEnergy; 
	vanDerWaalsEnergy = calc.vanDerWaalsEnergy;
	interactionTypes = calc.interactionTypes;

    return *this;
}

// \endcond

#endif // CDPL_FORCEFIELD_MMFF94ENERGYCALCULATOR_HPP
