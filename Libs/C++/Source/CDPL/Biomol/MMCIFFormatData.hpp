/* 
 * MMCIFFormatData.hpp 
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


#ifndef CDPL_BIOMOL_MMCIFFORMATDATA_HPP
#define CDPL_BIOMOL_MMCIFFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Biomol
    {

        namespace MMCIF
        {

            constexpr char END_OF_LINE                = '\n';
            constexpr char COMMENT_PREFIX             = '#';
            constexpr char QUOTED_STRING_DELIMITER_1  = '\'';
            constexpr char QUOTED_STRING_DELIMITER_2  = '"';
            constexpr char TEXT_FIELD_DELIMITER       = ';';
            constexpr char CATEGORY_NAME_SEPARATOR    = '.';
            constexpr char DATA_NAME_PREFIX           = '_';

            const std::string DATA_BLOCK_ID_PREFIX = "data_";
            const std::string SAVE_FRAME_PREFIX    = "save_";
            const std::string LOOP_KEYWORD         = "loop_";
            const std::string STOP_KEYWORD         = "stop_";
            const std::string GLOBAL_KEYWORD       = "global_";

            const std::string UNDEFINED_DATA_VALUE = ".";
            const std::string MISSING_DATA_VALUE   = "?";
        } // namespace MMCIF
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFFORMATDATA_HPP
