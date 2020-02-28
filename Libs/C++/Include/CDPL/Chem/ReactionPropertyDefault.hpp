/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionPropertyDefault.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::ReactionPropertyDefault.
 */

#ifndef CDPL_CHEM_REACTIONPROPERTYDEFAULT_HPP
#define CDPL_CHEM_REACTIONPROPERTYDEFAULT_HPP

#include <string>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_REACTION_PROPERTIES
		 * @{
		 */

		/**
		 * \brief Provides default values for built-in Chem::Reaction properties.
		 */
		namespace ReactionPropertyDefault
		{

			extern CDPL_CHEM_API const std::string NAME;
			extern CDPL_CHEM_API const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS;
			extern CDPL_CHEM_API const unsigned int MDL_RXN_FILE_VERSION;
			extern CDPL_CHEM_API const std::string MDL_COMMENT;
			extern CDPL_CHEM_API const std::string MDL_PROGRAM_NAME;
			extern CDPL_CHEM_API const std::string MDL_USER_INITIALS;
		}

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_REACTIONPROPERTYDEFAULT_HPP
