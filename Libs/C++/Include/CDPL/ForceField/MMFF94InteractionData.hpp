/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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
 * \brief Definition of the class CDPL::ForceField::MMFF94InteractionData.
 */

#ifndef CDPL_FORCEFIELD_MMFF94INTERACTIONDATA_HPP
#define CDPL_FORCEFIELD_MMFF94INTERACTIONDATA_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/ForceField/APIPrefix.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionData.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionData.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionData.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionData.hpp"


namespace CDPL 
{

    namespace ForceField 
    {

		class CDPL_FORCEFIELD_API MMFF94InteractionData
		{

		public:
			typedef boost::shared_ptr<MMFF94InteractionData> SharedPointer;

			const MMFF94BondStretchingInteractionData& getBondStretchingInteractions() const;

			MMFF94BondStretchingInteractionData& getBondStretchingInteractions();

			const MMFF94AngleBendingInteractionData& getAngleBendingInteractions() const;

			MMFF94AngleBendingInteractionData& getAngleBendingInteractions();

			const MMFF94StretchBendInteractionData& getStretchBendInteractions() const;

			MMFF94StretchBendInteractionData& getStretchBendInteractions();

			const MMFF94OutOfPlaneBendingInteractionData& getOutOfPlaneBendingInteractions() const;

			MMFF94OutOfPlaneBendingInteractionData& getOutOfPlaneBendingInteractions();

			const MMFF94TorsionInteractionData& getTorsionInteractions() const;

			MMFF94TorsionInteractionData& getTorsionInteractions();

			const MMFF94ElectrostaticInteractionData& getElectrostaticInteractions() const;

			MMFF94ElectrostaticInteractionData& getElectrostaticInteractions();

			const MMFF94VanDerWaalsInteractionData& getVanDerWaalsInteractions() const;

			MMFF94VanDerWaalsInteractionData& getVanDerWaalsInteractions();

			void clear();

			void swap(MMFF94InteractionData& ia_data);

		private:
			MMFF94BondStretchingInteractionData    bondStretchingData;
			MMFF94AngleBendingInteractionData      angleBendingData;
			MMFF94StretchBendInteractionData       stretchBendData;
			MMFF94OutOfPlaneBendingInteractionData outOfPlaneData;
			MMFF94TorsionInteractionData           torsionData;
			MMFF94ElectrostaticInteractionData     electrostaticData;
			MMFF94VanDerWaalsInteractionData       vanDerWaalsData;
		};
    }
}

#endif // CDPL_FORCEFIELD_MMFF94INTERACTIONDATA_HPP
