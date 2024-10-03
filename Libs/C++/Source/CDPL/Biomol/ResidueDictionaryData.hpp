/*
 * ResidueDictionaryData.hpp
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


#ifndef CDPL_BIOMOL_RESIDUEDICTIONARYDATA_HPP
#define CDPL_BIOMOL_RESIDUEDICTIONARYDATA_HPP

#include <cstddef>
#include <utility>


namespace CDPL
{

    namespace Biomol
    {

        namespace ResidueDictionaryData
        {

            struct ResidueDataEntry
            {

                const char*  code;
                const char*  replacesCode;
                const char*  replacedByCode;
                const char*  parentCode;
                const char*  oneLetterCode;
                unsigned int type;
                bool         obsolete;
                const char*  name;
                std::size_t  molIndex;
            };

            extern const ResidueDataEntry RESIDUE_DATA[];
            extern const std::size_t      NUM_RESIDUE_ENTRIES;

            std::pair<const char*, std::size_t> getStructureData();

        } // namespace ResidueDictionaryData
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_RESIDUEDICTIONARYDATA_HPP
