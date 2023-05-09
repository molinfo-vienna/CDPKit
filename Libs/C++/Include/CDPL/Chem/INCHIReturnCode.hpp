/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * INCHIReturnCode.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::INCHIReturnCode.
 */

#ifndef CDPL_CHEM_INCHIRETURNCODE_HPP
#define CDPL_CHEM_INCHIRETURNCODE_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief Provides constants that are used to describe the status of an \e %InChI [\ref INCHI] output or input operation.
		 *
		 * The defined constants correspond to the return values of the <em>%InChI C-API</em> functions (see [\ref INCHI])
		 * that were used for the creation or decoding of \e %InChI strings and keys. 
		 */
		namespace INCHIReturnCode
		{
			
			/**
			 * \brief Not used by the \e %InChI C-library.
			 */
			extern CDPL_CHEM_API const int SKIP; 

			/**
			 * \brief Specifies that no structural data were provided for the \e %InChI generation (e.g. empty structure).
			 */
			extern CDPL_CHEM_API const int EOF_; 

			/**
			 * \brief Specifies that the operation was successful and no warnings have been issued.
			 */
			extern CDPL_CHEM_API const int OKAY;  

			/**
			 * \brief Specifies that the operation was successful but warnings have been issued.
			 */
			extern CDPL_CHEM_API const int WARNING;  

			/**
			 * \brief Specifies that the operation was not successful and no \e %InChI has been created.
			 */
			extern CDPL_CHEM_API const int ERROR; 

			/**
			 * \brief Specifies that the operation was not successful because some severe error occurred during processing
			 *        (typically a memory allocation failure).
			 */
			extern CDPL_CHEM_API const int FATAL;  

			/**
			 * \brief Specifies that the operation was not successful because of an unknown program error.
			 */
			extern CDPL_CHEM_API const int UNKNOWN;  

			/**
			 * \brief Specifies that a previous call to the \e %InChI generation function has not yet returned (should
			 *        never happen).
			 */
			extern CDPL_CHEM_API const int BUSY;
  		}
	}
}

#endif // CDPL_CHEM_INCHIRETURNCODE_HPP
