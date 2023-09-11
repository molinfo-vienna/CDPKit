/* 
 * ResidueDictionaryData.cpp 
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


#include "StaticInit.hpp"

#ifdef _MSC_VER
# include <winbase.h>
#endif

#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "ResidueDictionaryData.hpp"


namespace CDPL
{

    namespace Biomol
    {

        namespace ResidueDictionaryData
        {
            // clang-format off
            
#ifndef _MSC_VER

            const char RESIDUE_STRUCTURE_DATA[] =
                #include "ResidueDictionaryStructureData.cdf.str"
                ;

            std::pair<const char*, std::size_t> getStructureData()
            {
                return std::make_pair(RESIDUE_STRUCTURE_DATA, sizeof(RESIDUE_STRUCTURE_DATA) - 1);
            }
#else
            std::pair<const char*, std::size_t> getStructureData()
            {
                // NOTE: providing g_hInstance is important, NULL might not work
                HRSRC res = FindResource(g_hInstance, "RES_DICT_STRUCT_DATA", RT_RCDATA);

                if (!res)
                    throw Base::IOError(std::string("ResidueDictionaryData: could not find structure data resource record");

                HGLOBAL res_handle = LoadResource(NULL, res);

                if (!res_handle)
                    throw Base::IOError(std::string("ResidueDictionaryData: could not load structure data resource");

                const char* res_data = static_cast<const char*>(LockResource(res_handle));

                DWORD res_data_len = SizeofResource(NULL, res);

                return std::make_pair(res_data, res_data_len);
            }

#endif // !_MSC_VER            

            #include "ResidueDictionaryEntries.hpp"

            const std::size_t NUM_RESIDUE_ENTRIES = sizeof(RESIDUE_DATA) / sizeof(ResidueDataEntry);

            // clang-format on
            
        } // namespace ResidueDictionaryData
    }     // namespace Biomol
} // namespace CDPL
