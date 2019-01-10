/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomPropertyDefault.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/AtomPropertyDefault.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"
#include "CDPL/Chem/RadicalType.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/SybylAtomType.hpp"


namespace CDPL
{

	namespace Chem
	{

		namespace AtomPropertyDefault
		{

			const std::string SYMBOL                                   = "";
			const std::string NAME                                     = "";
			const long FORMAL_CHARGE                                   = 0;
			const std::size_t ISOTOPE                                  = 0;
			const std::size_t UNPAIRED_ELECTRON_COUNT                  = 0;
            const unsigned int TYPE                                    = AtomType::UNKNOWN;
            const unsigned int SYBYL_TYPE                              = SybylAtomType::UNKNOWN;
            const unsigned int RADICAL_TYPE                            = RadicalType::NOT_RADICALIC;
			const unsigned int REACTION_CENTER_STATUS                  = ReactionCenterStatus::NONE;
			const StereoDescriptor STEREO_DESCRIPTOR                   = StereoDescriptor(AtomConfiguration::UNDEF);
			const std::size_t COMPONENT_GROUP_ID                       = 0;
			const std::size_t ATOM_MAPPING_ID                          = 0;
			const MatchConstraintList::SharedPointer MATCH_CONSTRAINTS = MatchConstraintList::SharedPointer(new MatchConstraintList());
			const double MOL2_CHARGE                                   = 0.0;
			const std::string MOL2_NAME                                = "";
			const bool MDL_DB_STEREO_CARE_FLAG                         = false;
		}

		void initAtomPropertyDefaults() {}
	}
}
