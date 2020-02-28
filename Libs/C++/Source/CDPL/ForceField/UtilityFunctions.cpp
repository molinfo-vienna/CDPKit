/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include "StaticInit.hpp"

#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"


using namespace CDPL;


void ForceField::filterInteractions(const MMFF94InteractionData& ia_data, MMFF94InteractionData& filtered_ia_data, 
									const Util::BitSet& inc_atom_mask)
{
    for (MMFF94BondStretchingInteractionData::ConstElementIterator it = ia_data.getBondStretchingInteractions().getElementsBegin(),
			 end = ia_data.getBondStretchingInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94BondStretchingInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getAtom2Index()))
			continue; 

		filtered_ia_data.getBondStretchingInteractions().addElement(iactn);
    }

    for (MMFF94VanDerWaalsInteractionData::ConstElementIterator it = ia_data.getVanDerWaalsInteractions().getElementsBegin(),
			 end = ia_data.getVanDerWaalsInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94VanDerWaalsInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getAtom2Index()))
			continue; 

		filtered_ia_data.getVanDerWaalsInteractions().addElement(iactn);
    }

    for (MMFF94ElectrostaticInteractionData::ConstElementIterator it = ia_data.getElectrostaticInteractions().getElementsBegin(),
			 end = ia_data.getElectrostaticInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94ElectrostaticInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getAtom2Index()))
			continue; 

		filtered_ia_data.getElectrostaticInteractions().addElement(iactn);
    }

    for (MMFF94AngleBendingInteractionData::ConstElementIterator it = ia_data.getAngleBendingInteractions().getElementsBegin(),
			 end = ia_data.getAngleBendingInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94AngleBendingInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getTerminalAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getCenterAtomIndex()))
			continue;

		if (!inc_atom_mask.test(iactn.getTerminalAtom2Index()))
			continue; 

		filtered_ia_data.getAngleBendingInteractions().addElement(iactn);
    }

    for (MMFF94StretchBendInteractionData::ConstElementIterator it = ia_data.getStretchBendInteractions().getElementsBegin(),
			 end = ia_data.getStretchBendInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94StretchBendInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getTerminalAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getCenterAtomIndex()))
			continue;

		if (!inc_atom_mask.test(iactn.getTerminalAtom2Index()))
			continue; 

		filtered_ia_data.getStretchBendInteractions().addElement(iactn);
    }

    for (MMFF94OutOfPlaneBendingInteractionData::ConstElementIterator it = ia_data.getOutOfPlaneBendingInteractions().getElementsBegin(),
			 end = ia_data.getOutOfPlaneBendingInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94OutOfPlaneBendingInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getTerminalAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getCenterAtomIndex()))
			continue;

		if (!inc_atom_mask.test(iactn.getTerminalAtom2Index()))
			continue; 

		if (!inc_atom_mask.test(iactn.getOutOfPlaneAtomIndex()))
			continue; 

		filtered_ia_data.getOutOfPlaneBendingInteractions().addElement(iactn);
    }

    for (MMFF94TorsionInteractionData::ConstElementIterator it = ia_data.getTorsionInteractions().getElementsBegin(),
			 end = ia_data.getTorsionInteractions().getElementsEnd(); it != end; ++it) {
		const MMFF94TorsionInteraction& iactn = *it;

		if (!inc_atom_mask.test(iactn.getTerminalAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getCenterAtom1Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getCenterAtom2Index()))
			continue;

		if (!inc_atom_mask.test(iactn.getTerminalAtom2Index()))
			continue; 

		filtered_ia_data.getTorsionInteractions().addElement(iactn);
    }
}
