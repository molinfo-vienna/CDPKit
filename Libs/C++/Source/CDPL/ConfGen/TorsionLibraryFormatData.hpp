/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionLibraryFormatData.hpp
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


#ifndef CDPL_CONFGEN_TORSIONLIBRARYFORMATDATA_HPP
#define CDPL_CONFGEN_TORSIONLIBRARYFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace ConfGen
    {

		namespace TorsionLibraryFormatData
		{
			
			const std::string LIBRARY_TAG               = "library";
			const std::string CATEGORY_TAG              = "category";
			const std::string RULE_TAG                  = "rule";
			const std::string ANGLE_LIST_TAG            = "torsions";
			const std::string ANGLE_TAG                 = "angle";
			const std::string NOTE_TAG                  = "note";

			const std::string CATEGORY_NAME_ATTR        = "name";
			const std::string CATEGORY_PATTERN_ATTR     = "pattern";
			const std::string CATEGORY_ATOM_TYPE1_ATTR  = "atomType1";
			const std::string CATEGORY_ATOM_TYPE2_ATTR  = "atomType2";

			const std::string RULE_PATTERN_ATTR         = "pattern";

			const std::string ANGLE_VALUE_ATTR          = "value";
			const std::string ANGLE_TOLERANCE1_ATTR     = "tolerance1";
			const std::string ANGLE_TOLERANCE2_ATTR     = "tolerance2";
			const std::string ANGLE_SCORE_ATTR          = "score";
		}
    }
}

#endif // CDPL_CONFGEN_TORSIONLIBRARYFORMATDATA_HPP
