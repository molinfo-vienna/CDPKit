/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ForceFieldInteractionMasks.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::ForceFieldInteractionMasks.
 */

#ifndef CDPL_CONFGEN_FORCEFIELDINTERACTIONMASKS_HPP
#define CDPL_CONFGEN_FORCEFIELDINTERACTIONMASKS_HPP

#include <cstddef>

#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace ForceField
	{

		class MMFF94InteractionData;
	}
	
    namespace ConfGen 
    {
	
		struct ForceFieldInteractionMasks 
		{

			void init(std::size_t num_bs_ia, std::size_t num_ab_ia, std::size_t num_sb_ia,
					  std::size_t num_oop_ia, std::size_t num_tor_ia, std::size_t num_vdw_ia,
					  std::size_t num_els_ia) {

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
			
			Util::BitSet bondStretching;
			Util::BitSet angleBending;
			Util::BitSet stretchBend;
			Util::BitSet outOfPlaneBending;
			Util::BitSet torsion;
			Util::BitSet vanDerWaals;
			Util::BitSet electrostatic;
		};

		void initForceFieldInteractionMasks(const ForceField::MMFF94InteractionData& ia_data, ForceFieldInteractionMasks& ia_masks); 
    }
}

#endif // CDPL_CONFGEN_FORCEFIELDINTERACTIONMASKS_HPP
