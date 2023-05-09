/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondProperty.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::BondProperty.
 */

#ifndef CDPL_CHEM_BONDPROPERTY_HPP
#define CDPL_CHEM_BONDPROPERTY_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		class LookupKey;
	}

	namespace Chem
	{

		/**
		 * \brief Provides keys for built-in Chem::Bond properties.
		 */
		namespace BondProperty
		{

			extern CDPL_CHEM_API const Base::LookupKey ORDER;

			extern CDPL_CHEM_API const Base::LookupKey RING_FLAG;
			extern CDPL_CHEM_API const Base::LookupKey AROMATICITY_FLAG;

			extern CDPL_CHEM_API const Base::LookupKey STEREO_DESCRIPTOR;
			extern CDPL_CHEM_API const Base::LookupKey STEREO_CENTER_FLAG;
			extern CDPL_CHEM_API const Base::LookupKey CIP_CONFIGURATION;
			extern CDPL_CHEM_API const Base::LookupKey DIRECTION;
			extern CDPL_CHEM_API const Base::LookupKey STEREO_2D_FLAG;

			extern CDPL_CHEM_API const Base::LookupKey SYBYL_TYPE;

			extern CDPL_CHEM_API const Base::LookupKey REACTION_CENTER_STATUS;

			extern CDPL_CHEM_API const Base::LookupKey MATCH_CONSTRAINTS;
			extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION;
			extern CDPL_CHEM_API const Base::LookupKey MATCH_EXPRESSION_STRING;
		}
	}
}

#endif // CDPL_CHEM_BONDPROPERTY_HPP
