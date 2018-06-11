/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/*
 * BuiltinResidueDictionaryData.hpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2015 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_BIOMOL_BUILTINRESIDUEDICTIONARYDATA_HPP
#define CDPL_BIOMOL_BUILTINRESIDUEDICTIONARYDATA_HPP

#include <cstddef>


namespace CDPL
{

	namespace Biomol
	{

		namespace BuiltinResidueDictionaryData
		{

			struct ResidueDataEntry
			{

				const char*  code;
				const char*  replacesCode;
				const char*  replacedByCode;
				unsigned int type;
				bool         obsolete;
				const char*  name;
				std::size_t  molIndex;
			};

			extern const ResidueDataEntry residueData[];
			extern const std::size_t NUM_RESIDUE_ENTRIES;

			extern const char* residueStructureData;
			extern const std::size_t RESIDUE_STRUCTURE_DATA_LEN;
		}
	}
}

#endif // CDPL_BIOMOL_BUILTINRESIDUEDICTIONARYDATA_HPP
