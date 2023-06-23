/* 
 * MOL2MoleculeType.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MOL2MoleculeType.
 */

#ifndef CDPL_CHEM_MOL2MOLECULETYPE_HPP
#define CDPL_CHEM_MOL2MOLECULETYPE_HPP


namespace CDPL 
{

    namespace Chem 
    {

	/**
	 * \brief Provides constants for the specification of the molecule type in <em>Tripos MOL2</em> files.
	 */
	namespace MOL2MoleculeType 
	{

	    const unsigned int UNKNOWN      = 0;
	    const unsigned int SMALL        = 1;
	    const unsigned int BIOPOLYMER   = 2;
	    const unsigned int PROTEIN      = 3;
	    const unsigned int NUCLEIC_ACID = 4;
	    const unsigned int SACCHARIDE   = 5;
	}
    }
}

#endif // CDPL_CHEM_MOL2MOLECULETYPE_HPP
