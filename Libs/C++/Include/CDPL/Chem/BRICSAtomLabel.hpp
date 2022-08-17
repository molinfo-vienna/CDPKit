/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BRICSAtomLabel.hpp 
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

/**
 * \file
 * \brief Definition of constants in namespace CDPL::Chem::BRICSAtomLabel.
 */

#ifndef CDPL_CHEM_BRICSATOMLABEL_HPP
#define CDPL_CHEM_BRICSATOMLABEL_HPP


namespace CDPL 
{

    namespace Chem 
    {

	/**
	 * \brief Provides constants for the labeling of atoms in bonds matched by a BRICS fragmentation rule.
	 * \see [\ref BRICS]
	 */
	namespace BRICSAtomLabel 
	{

	    const unsigned int NONE = 0;
		const unsigned int L1   = 1;
		const unsigned int L2   = 2;
		const unsigned int L3   = 3;
		const unsigned int L4   = 4;
		const unsigned int L5   = 5;
		const unsigned int L6   = 6;
		const unsigned int L7   = 7;
		const unsigned int L8   = 8;
		const unsigned int L9   = 9;
		const unsigned int L10  = 10;
		const unsigned int L11  = 11;
		const unsigned int L12  = 12;
		const unsigned int L13  = 13;
		const unsigned int L14  = 14;
		const unsigned int L15  = 15;
		const unsigned int L16  = 16;
	}
    }
}

#endif // CDPL_CHEM_BRICSATOMLABEL_HPP
