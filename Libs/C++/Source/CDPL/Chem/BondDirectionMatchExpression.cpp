/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondDirectionMatchExpression.cpp
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

#include "CDPL/Chem/BondDirectionMatchExpression.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Base/Any.hpp"


using namespace CDPL;


Chem::BondDirectionMatchExpression::BondDirectionMatchExpression(unsigned int dir_flags, bool not_match): 
	dirFlags(dir_flags & (BondDirection::UP | BondDirection::DOWN | BondDirection::UNSPECIFIED)), notMatch(not_match) {}

bool Chem::BondDirectionMatchExpression::operator()(const Bond&, const MolecularGraph&, const Bond&, const MolecularGraph&,
													const AtomBondMapping&, const Base::Any& target_bond_dir) const
{
	if (dirFlags == 0)
		return true;

	if (target_bond_dir.isEmpty())
		return true;

	if (notMatch)
		return ((dirFlags & target_bond_dir.getData<unsigned int>()) == 0);

	return ((dirFlags & target_bond_dir.getData<unsigned int>()) != 0);
}
