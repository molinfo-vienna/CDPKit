/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ForceFieldInteractionMask.cpp
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

 
#include "StaticInit.hpp"

#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "ForceFieldInteractionMask.hpp"


using namespace CDPL;


void ConfGen::ForceFieldInteractionMask::setup(std::size_t num_bs_ia, std::size_t num_ab_ia, std::size_t num_sb_ia,
											  std::size_t num_oop_ia, std::size_t num_tor_ia, std::size_t num_vdw_ia,
											  std::size_t num_els_ia) 
{
	bondStretching.resize(num_bs_ia);
	bondStretching.set();

	angleBending.resize(num_ab_ia);
	angleBending.set();

	stretchBend.resize(num_sb_ia);
	stretchBend.set();

	outOfPlaneBending.resize(num_oop_ia);
	outOfPlaneBending.set();

	torsion.resize(num_tor_ia);
	torsion.set();

	vanDerWaals.resize(num_vdw_ia);
	vanDerWaals.set();

	electrostatic.resize(num_els_ia);
	electrostatic.set();
}

void ConfGen::ForceFieldInteractionMask::setup(const ForceField::MMFF94InteractionData& ia_data)
{
    setup(ia_data.getBondStretchingInteractions().getSize(),
		  ia_data.getAngleBendingInteractions().getSize(),
		  ia_data.getStretchBendInteractions().getSize(),
		  ia_data.getOutOfPlaneBendingInteractions().getSize(),
		  ia_data.getTorsionInteractions().getSize(),
		  ia_data.getVanDerWaalsInteractions().getSize(),
		  ia_data.getElectrostaticInteractions().getSize());
}
