/* 
 * ControlParameter.cpp 
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
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include "CDPL/Base/LookupKeyDefinition.hpp"

#include "ControlParameter.hpp"


namespace ChOX
{

    namespace ControlParameter
    {

        CDPL_DEFINE_LOOKUP_KEY(VIEW_BACKGROUND_COLOR);
        CDPL_DEFINE_LOOKUP_KEY(VIEW_SELECTION_COLOR);
        CDPL_DEFINE_LOOKUP_KEY(VIEWPORT_MARGIN);
        CDPL_DEFINE_LOOKUP_KEY(SHOW_GRID);
        CDPL_DEFINE_LOOKUP_KEY(SHOW_RECORD_NUMBERS);
        CDPL_DEFINE_LOOKUP_KEY(SHOW_RECORD_NAMES);
        CDPL_DEFINE_LOOKUP_KEY(SHOW_RECORD_PROPERTIES);
        CDPL_DEFINE_LOOKUP_KEY(GRID_COLUMN_COUNT);
        CDPL_DEFINE_LOOKUP_KEY(GRID_ROW_COUNT);
        CDPL_DEFINE_LOOKUP_KEY(GRID_LINE_STYLE);
        CDPL_DEFINE_LOOKUP_KEY(GRID_LINE_COLOR);
        CDPL_DEFINE_LOOKUP_KEY(GRID_LINE_WIDTH);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NUMBER_LABEL_FONT);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NUMBER_LABEL_SIZE);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NUMBER_LABEL_ALIGNMENT);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NUMBER_LABEL_COLOR);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NAME_LABEL_FONT);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NAME_LABEL_SIZE);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NAME_LABEL_ALIGNMENT);
        CDPL_DEFINE_LOOKUP_KEY(RECORD_NAME_LABEL_COLOR);

        CDPL_DEFINE_LOOKUP_KEY(PRINT_FRAME);
        CDPL_DEFINE_LOOKUP_KEY(PRINT_DATE);
        CDPL_DEFINE_LOOKUP_KEY(PRINT_PAGE_NUMBER);
        CDPL_DEFINE_LOOKUP_KEY(PRINT_FILE_NAME);
        CDPL_DEFINE_LOOKUP_KEY(FRAME_LINE_STYLE);
        CDPL_DEFINE_LOOKUP_KEY(FRAME_LINE_COLOR);
        CDPL_DEFINE_LOOKUP_KEY(FRAME_LINE_WIDTH);
        CDPL_DEFINE_LOOKUP_KEY(PRINTING_TEXT_LABEL_FONT);
        CDPL_DEFINE_LOOKUP_KEY(PRINTING_TEXT_LABEL_SIZE);
        CDPL_DEFINE_LOOKUP_KEY(PRINTING_TEXT_LABEL_SPACING);
        CDPL_DEFINE_LOOKUP_KEY(PRINTING_TEXT_LABEL_COLOR);
        CDPL_DEFINE_LOOKUP_KEY(PAGE_NUMBER_LABEL_ALIGNMENT);
        CDPL_DEFINE_LOOKUP_KEY(DATE_LABEL_ALIGNMENT);
        CDPL_DEFINE_LOOKUP_KEY(FILE_NAME_LABEL_ALIGNMENT);

        CDPL_DEFINE_LOOKUP_KEY(DEFAULT_MOL_OUTPUT_FORMAT);
        CDPL_DEFINE_LOOKUP_KEY(DEFAULT_RXN_OUTPUT_FORMAT);

        CDPL_DEFINE_LOOKUP_KEY(OUTPUT_SINGLE_RECORD_FILES);

        CDPL_DEFINE_LOOKUP_KEY(USE_ATOM_COLOR_TABLE);
        CDPL_DEFINE_LOOKUP_KEY(ATOM_COLOR_TABLE);

        CDPL_DEFINE_LOOKUP_KEY(SUBSTRUCT_HIGHLIGHTING_PATTERNS);
        CDPL_DEFINE_LOOKUP_KEY(SUBSTRUCT_HIGHLIGHTING_ENABLED);

        CDPL_DEFINE_LOOKUP_KEY(SUBSTRUCT_SEARCH_QUERY);
    }
}
