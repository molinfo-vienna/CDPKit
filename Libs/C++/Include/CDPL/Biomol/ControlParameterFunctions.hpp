/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterFunctions.hpp 
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
 * \brief Declaration of convenience functions for control-parameter handling.
 */

#ifndef CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP
#define CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP

#include "CDPL/Biomol/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		class ControlParameterContainer;
	}

	namespace Biomol 
	{
	
		/**
		 * \addtogroup CDPL_BIOMOL_CONTROL_PARAMETER_FUNCTIONS
		 * @{
		 */
		
		CDPL_BIOMOL_API bool getStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr, bool strict);

		CDPL_BIOMOL_API bool hasStrictErrorCheckingParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearStrictErrorCheckingParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setCheckLineLengthParameter(Base::ControlParameterContainer& cntnr, bool check);

		CDPL_BIOMOL_API bool hasCheckLineLengthParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void clearCheckLineLengthParameter(Base::ControlParameterContainer& cntnr);


		CDPL_BIOMOL_API bool getCDFWriteSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);

		CDPL_BIOMOL_API void setCDFWriteSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr, bool single_prec);

		CDPL_BIOMOL_API bool hasCDFWriteSinglePrecisionFloatsParameter(const Base::ControlParameterContainer& cntnr);
	
		CDPL_BIOMOL_API void clearCDFWriteSinglePrecisionFloatsParameter(Base::ControlParameterContainer& cntnr);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_BIOMOL_CONTROLPARAMETERFUNCTIONS_HPP
 
