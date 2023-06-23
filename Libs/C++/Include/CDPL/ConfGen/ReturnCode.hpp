/* 
 * ReturnCode.hpp 
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
 * \brief Definition of constants in namespace CDPL::Confgen::ReturnCode.
 */

#ifndef CDPL_CONFGEN_RETURNCODE_HPP
#define CDPL_CONFGEN_RETURNCODE_HPP


namespace CDPL 
{

    namespace ConfGen
    {

		/**
		 * \brief Provides constants that are used to describe the result of operations related to conformer generation.
		 */
		namespace ReturnCode
		{
			
			const int SUCCESS                         = 0; 

			const int UNINITIALIZED                   = 1;

			const int TIMEOUT                         = 2;

			const int ABORTED                         = 3;

			const int FORCEFIELD_SETUP_FAILED         = 4;

			const int FORCEFIELD_MINIMIZATION_FAILED  = 5;

			const int FRAGMENT_LIBRARY_NOT_SET        = 6;
 	
			const int FRAGMENT_CONF_GEN_FAILED        = 7;

			const int FRAGMENT_CONF_GEN_TIMEOUT       = 8;

			const int FRAGMENT_ALREADY_PROCESSED      = 9;

			const int TORSION_DRIVING_FAILED          = 10;

			const int CONF_GEN_FAILED                 = 11;

			const int TOO_MUCH_SYMMETRY               = 12;
		}
    }
}

#endif // CDPL_CONFGEN_RETURNCODE_HPP
