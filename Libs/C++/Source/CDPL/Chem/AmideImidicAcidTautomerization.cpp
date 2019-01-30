/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AmideImidicAcidTautomerization.cpp 
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

 
#include "StaticInit.hpp"

#include "CDPL/Chem/AmideImidicAcidTautomerization.hpp"
#include "CDPL/Chem/TautomerizationType.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"


using namespace CDPL;


Chem::AmideImidicAcidTautomerization::AmideImidicAcidTautomerization(): 
	PatternBasedTautomerizationRule(TautomerizationType::AMIDE_IMIDIC_ACID)
{
	BondOrderChange bond_changes[]= {
		{ 1, 2, -1 },
		{ 2, 3, 1 },
		{ 3, 4, -1 },
		{ 1, 4, 1 }
	};

	addTransformationPattern(parseSMARTS("[#8,#16,#34:1]=;!@[#6:2]-;!@[#7:3]-[#1:4]"), 
							 &bond_changes[0], &bond_changes[sizeof(bond_changes) / sizeof(BondOrderChange)]);
	addTransformationPattern(parseSMARTS("[#1:1]-[#8,#16,#34:2]-;!@[#6:3]=;!@[#7:4]"), 
							 &bond_changes[0], &bond_changes[sizeof(bond_changes) / sizeof(BondOrderChange)]);
}
