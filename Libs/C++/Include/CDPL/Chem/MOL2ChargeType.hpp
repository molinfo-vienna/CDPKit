/* 
 * MOL2ChargeType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MOL2ChargeType.
 */

#ifndef CDPL_CHEM_MOL2CHARGETYPE_HPP
#define CDPL_CHEM_MOL2CHARGETYPE_HPP


namespace CDPL 
{

    namespace Chem 
    {

	/**
	 * \brief Provides constants for the specification of the atom charge type in <em>Tripos MOL2</em> files.
	 */
	namespace MOL2ChargeType 
	{

	    const unsigned int UNKNOWN     = 0;
	    const unsigned int NO_CHARGES  = 1;
	    const unsigned int DEL_RE      = 2;
	    const unsigned int GASTEIGER   = 3;
	    const unsigned int GAST_HUCK   = 4;
	    const unsigned int HUCKEL      = 5;
	    const unsigned int PULLMAN     = 6;
	    const unsigned int GAUSS80     = 7;
	    const unsigned int AMPAC       = 8;
	    const unsigned int MULLIKEN    = 9;
	    const unsigned int DICT        = 10;
	    const unsigned int MMFF94      = 11;
	    const unsigned int USER        = 12;
	}
    }
}

#endif // CDPL_CHEM_MOL2CHARGETYPE_HPP
