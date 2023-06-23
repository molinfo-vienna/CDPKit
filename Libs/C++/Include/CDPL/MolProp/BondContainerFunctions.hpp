/* 
 * BondContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::BondContainer instances.
 */

#ifndef CDPL_MOLPROP_BONDCONTAINERFUNCTIONS_HPP
#define CDPL_MOLPROP_BONDCONTAINERFUNCTIONS_HPP

#include <cstddef>

#include "CDPL/MolProp/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class BondContainer;
	}
	
	namespace MolProp
	{

		CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::BondContainer& cntnr);

		CDPL_MOLPROP_API std::size_t getExplicitBondCount(const Chem::BondContainer& cntnr, std::size_t order, bool inc_aro = true);

		CDPL_MOLPROP_API std::size_t getExplicitHydrogenBondCount(const Chem::BondContainer& cntnr);

		CDPL_MOLPROP_API std::size_t getExplicitChainBondCount(const Chem::BondContainer& cntnr);

		CDPL_MOLPROP_API std::size_t getRingBondCount(const Chem::BondContainer& cntnr);

		CDPL_MOLPROP_API std::size_t getAromaticBondCount(const Chem::BondContainer& cntnr);

		CDPL_MOLPROP_API std::size_t getHeavyBondCount(const Chem::BondContainer& cntnr);
	}
}

#endif // CDPL_MOLPROP_BONDCONTAINERFUNCTIONS_HPP
 
