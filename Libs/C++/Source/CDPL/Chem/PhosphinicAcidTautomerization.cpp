/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PhosphinicAcidTautomerization.cpp 
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

#include "CDPL/Chem/PhosphinicAcidTautomerization.hpp"
#include "CDPL/Chem/TautomerizationType.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


Chem::PhosphinicAcidTautomerization::PhosphinicAcidTautomerization(): 
	PatternBasedTautomerizationRule(TautomerizationType::PHOSPHINIC_ACID)
{
	BondOrderChange bond_changes1[]= {
		{ 1, 2, -1 },
		{ 2, 3, -1 },
		{ 1, 3, 1 }
	};

	BondOrderChange bond_changes2[]= {
		{ 1, 2, -1 },
		{ 2, 3, 1 },
		{ 1, 3, 1 }
	};

	addTransformationPattern(parseSMARTS("[#8,#16,#34:1]=[#15;X4:2]-[#1:3]"), 
							 &bond_changes1[0], &bond_changes1[sizeof(bond_changes1) / sizeof(BondOrderChange)]);
	addTransformationPattern(parseSMARTS("[#1:1]-[#8,#16,#34:2]-[#15;X3:3]"), 
							 &bond_changes2[0], &bond_changes2[sizeof(bond_changes2) / sizeof(BondOrderChange)]);
}
