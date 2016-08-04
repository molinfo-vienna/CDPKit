/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Biomol::ResidueType.
 */

#ifndef CDPL_BIOMOL_RESIDUETYPE_HPP
#define CDPL_BIOMOL_RESIDUETYPE_HPP


namespace CDPL 
{

    namespace Biomol 
    {

	/**
	 * \addtogroup CDPL_BIOMOL_CONSTANTS
	 * @{
	 */
	
	namespace ResidueType 
	{

	    const unsigned int UNKNOWN                  = 0;
	    const unsigned int OTHER                    = 1;
	    const unsigned int NON_POLYMER              = 2;
	    const unsigned int PEPTIDE_CARBOXY_TERMINUS = 3;
	    const unsigned int PEPTIDE_AMINO_TERMINUS   = 4;
	    const unsigned int PEPTIDE_LINKING          = 5;
	    const unsigned int BETA_PEPTIDE_LINKING     = 6;
	    const unsigned int GAMMA_PEPTIDE_LINKING    = 7;
	    const unsigned int PEPTIDE_LIKE             = 8;
		const unsigned int RNA_HYDROXY_TERMINUS     = 9;
		const unsigned int DNA_HYDROXY_TERMINUS     = 10;
		const unsigned int RNA_LINKING              = 11;
	    const unsigned int DNA_LINKING              = 12;
	    const unsigned int SACCHARIDE_LINKING       = 13;
	    const unsigned int SACCHARIDE               = 14;
	}

	/**
	 * @}
	 */
    }
}

#endif // CDPL_BIOMOL_RESIDUETYPE_HPP
