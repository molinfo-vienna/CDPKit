/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * INCHIReturnCode.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/INCHIReturnCode.hpp"

#include "LibInChI/inchi_api.h"


namespace CDPL 
{

	namespace Chem
	{
	
		namespace INCHIReturnCode
		{
	
			const int SKIP      = inchi_Ret_SKIP; 
			const int EOF_      = inchi_Ret_EOF; 
			const int OKAY      = inchi_Ret_OKAY;  
			const int WARNING   = inchi_Ret_WARNING;  
			const int ERROR     = inchi_Ret_ERROR; 
			const int FATAL     = inchi_Ret_FATAL;  
			const int UNKNOWN   = inchi_Ret_UNKNOWN;  
			const int BUSY      = inchi_Ret_BUSY;
		}
	}
}
