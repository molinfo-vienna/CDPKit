/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SubstituentBulkinessCalculator.hpp
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
 * \brief Definition of the class CDPL::ConfGen::SubstituentBulkinessCalculator.
 */

#ifndef CDPL_CONFGEN_SUBSTITUENTBULKINESSCALCULATOR_HPP
#define CDPL_CONFGEN_SUBSTITUENTBULKINESSCALCULATOR_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
    }
	
    namespace ConfGen 
    {
	
		class SubstituentBulkinessCalculator 
		{

		public:
			void calculate(const Chem::MolecularGraph& molgraph);

			std::size_t operator[](std::size_t i) const {
				return ecArray[i];
			}

		private:
			typedef std::vector<std::size_t> ECArray;

			ECArray      ecArray;	
			ECArray      tmpECArray;	
			Util::BitSet hAtomMask;
		};
    }
}

#endif // CDPL_CONFGEN_SUBSTITUENTBULKINESSCALCULATOR_HPP
