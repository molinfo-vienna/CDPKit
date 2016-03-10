/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreFeatureType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::PharmacophoreFeatureType.
 */

#ifndef CDPL_CHEM_PHARMACOPHOREFEATURETYPE_HPP
#define CDPL_CHEM_PHARMACOPHOREFEATURETYPE_HPP


namespace CDPL 
{

    namespace Chem 
    {

	/**
	 * \addtogroup CDPL_CHEM_CONSTANTS
	 * @{
	 */

	/**
	 * \brief Provides constants for the specification of the generic type of a pharmacophore feature.
	 */
	namespace PharmacophoreFeatureType 
	{
		
	    const unsigned int UNKNOWN         = 0x00;

	    const unsigned int LIPOPHILIC      = 0x01;

	    const unsigned int AROMATIC        = 0x02;

	    const unsigned int NEG_IONIZABLE   = 0x04;

	    const unsigned int POS_IONIZABLE   = 0x08;

	    const unsigned int H_BOND_DONOR    = 0x10;

	    const unsigned int H_BOND_ACCEPTOR = 0x20;
	}

	/**
	 * @}
	 */
    }
}

#endif // CDPL_CHEM_PHARMACOPHOREFEATURETYPE_HPP
