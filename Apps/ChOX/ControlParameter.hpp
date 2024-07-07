/* 
 * ControlParameter.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifndef CHOX_CONTROLPARAMETER_HPP
#define CHOX_CONTROLPARAMETER_HPP


namespace CDPL
{

    namespace Base
    {

        class LookupKey;
    }
} // namespace CDPL


namespace ChOX
{

    namespace ControlParameter
    {

        extern const CDPL::Base::LookupKey VIEW_BACKGROUND_COLOR;
        extern const CDPL::Base::LookupKey VIEW_SELECTION_COLOR;
        extern const CDPL::Base::LookupKey VIEWPORT_MARGIN;
        extern const CDPL::Base::LookupKey SHOW_GRID;
        extern const CDPL::Base::LookupKey SHOW_RECORD_NUMBERS;
        extern const CDPL::Base::LookupKey SHOW_RECORD_NAMES;
        extern const CDPL::Base::LookupKey GRID_COLUMN_COUNT;
        extern const CDPL::Base::LookupKey GRID_ROW_COUNT;
        extern const CDPL::Base::LookupKey GRID_LINE_STYLE;
        extern const CDPL::Base::LookupKey GRID_LINE_COLOR;
        extern const CDPL::Base::LookupKey GRID_LINE_WIDTH;
        extern const CDPL::Base::LookupKey RECORD_NUMBER_LABEL_FONT;
        extern const CDPL::Base::LookupKey RECORD_NUMBER_LABEL_SIZE;
        extern const CDPL::Base::LookupKey RECORD_NUMBER_LABEL_ALIGNMENT;
        extern const CDPL::Base::LookupKey RECORD_NUMBER_LABEL_COLOR;
        extern const CDPL::Base::LookupKey RECORD_NAME_LABEL_FONT;
        extern const CDPL::Base::LookupKey RECORD_NAME_LABEL_SIZE;
        extern const CDPL::Base::LookupKey RECORD_NAME_LABEL_ALIGNMENT;
        extern const CDPL::Base::LookupKey RECORD_NAME_LABEL_COLOR;

        extern const CDPL::Base::LookupKey PRINT_FRAME;
        extern const CDPL::Base::LookupKey PRINT_DATE;
        extern const CDPL::Base::LookupKey PRINT_PAGE_NUMBER;
        extern const CDPL::Base::LookupKey PRINT_FILE_NAME;
        extern const CDPL::Base::LookupKey FRAME_LINE_STYLE;
        extern const CDPL::Base::LookupKey FRAME_LINE_COLOR;
        extern const CDPL::Base::LookupKey FRAME_LINE_WIDTH;
        extern const CDPL::Base::LookupKey PRINTING_TEXT_LABEL_FONT;
        extern const CDPL::Base::LookupKey PRINTING_TEXT_LABEL_SIZE;
        extern const CDPL::Base::LookupKey PRINTING_TEXT_LABEL_SPACING;
        extern const CDPL::Base::LookupKey PRINTING_TEXT_LABEL_COLOR;
        extern const CDPL::Base::LookupKey PAGE_NUMBER_LABEL_ALIGNMENT;
        extern const CDPL::Base::LookupKey DATE_LABEL_ALIGNMENT;
        extern const CDPL::Base::LookupKey FILE_NAME_LABEL_ALIGNMENT;

        extern const CDPL::Base::LookupKey DEFAULT_MOL_OUTPUT_FORMAT;
        extern const CDPL::Base::LookupKey DEFAULT_RXN_OUTPUT_FORMAT;

        extern const CDPL::Base::LookupKey WRITE_SINGLE_RECORD_FILES;

        extern const CDPL::Base::LookupKey USE_ATOM_COLOR_TABLE;
        extern const CDPL::Base::LookupKey ATOM_COLOR_TABLE;

        extern const CDPL::Base::LookupKey SUBSTRUCT_HIGHLIGHTING_PATTERNS;
        extern const CDPL::Base::LookupKey SUBSTRUCT_HIGHLIGHTING_ENABLED;

        extern const CDPL::Base::LookupKey SUBSTRUCT_SEARCH_QUERY;

    } // namespace ControlParameter
} // namespace ChOX

#endif // CHOX_CONTROLPARAMETER_HPP
