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

        class CDPL_FORCEFIELD_API MMFF94InteractionData
        {

          public:
            typedef std::shared_ptr<MMFF94InteractionData> SharedPointer;

            const MMFF94BondStretchingInteractionList& getBondStretchingInteractions() const;

            MMFF94BondStretchingInteractionList& getBondStretchingInteractions();

            const MMFF94AngleBendingInteractionList& getAngleBendingInteractions() const;

            MMFF94AngleBendingInteractionList& getAngleBendingInteractions();

            const MMFF94StretchBendInteractionList& getStretchBendInteractions() const;

            MMFF94StretchBendInteractionList& getStretchBendInteractions();

            const MMFF94OutOfPlaneBendingInteractionList& getOutOfPlaneBendingInteractions() const;

            MMFF94OutOfPlaneBendingInteractionList& getOutOfPlaneBendingInteractions();

            const MMFF94TorsionInteractionList& getTorsionInteractions() const;

            MMFF94TorsionInteractionList& getTorsionInteractions();

            const MMFF94ElectrostaticInteractionList& getElectrostaticInteractions() const;

            MMFF94ElectrostaticInteractionList& getElectrostaticInteractions();

            const MMFF94VanDerWaalsInteractionList& getVanDerWaalsInteractions() const;

            MMFF94VanDerWaalsInteractionList& getVanDerWaalsInteractions();

            void clear();

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
