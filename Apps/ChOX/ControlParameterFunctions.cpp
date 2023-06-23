/* 
 * ControlParameterFunctions.cpp 
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


#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "CDPL/Base/ControlParameterContainer.hpp"

#include "ControlParameterFunctions.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterDefault.hpp"


#define MAKE_CONTROL_PARAM_FUNCTIONS(PARAM_NAME, TYPE, FUNC_INFIX)                            \
TYPE ChOX::get##FUNC_INFIX##Parameter(const CDPL::Base::ControlParameterContainer& cntnr)     \
{                                                                                             \
	return cntnr.getParameterOrDefault<TYPE>(ControlParameter::PARAM_NAME,                    \
											 ControlParameterDefault::PARAM_NAME);            \
}                                                                                             \
                                                                                              \
void ChOX::set##FUNC_INFIX##Parameter(CDPL::Base::ControlParameterContainer& cntnr, TYPE arg) \
{                                                                                             \
	cntnr.setParameter(ControlParameter::PARAM_NAME, arg);                                    \
}


MAKE_CONTROL_PARAM_FUNCTIONS(VIEW_BACKGROUND_COLOR, const CDPL::Vis::Color&, ViewBackgroundColor)
MAKE_CONTROL_PARAM_FUNCTIONS(VIEW_SELECTION_COLOR, const CDPL::Vis::Color&, ViewSelectionColor)
MAKE_CONTROL_PARAM_FUNCTIONS(VIEWPORT_MARGIN, const CDPL::Vis::SizeSpecification&, ViewportMargin)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_GRID, bool, ShowGrid)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_RECORD_NUMBERS, bool, ShowRecordNumbers)
MAKE_CONTROL_PARAM_FUNCTIONS(SHOW_RECORD_NAMES, bool, ShowRecordNames)
MAKE_CONTROL_PARAM_FUNCTIONS(GRID_COLUMN_COUNT, std::size_t, GridColumnCount)
MAKE_CONTROL_PARAM_FUNCTIONS(GRID_ROW_COUNT, std::size_t, GridRowCount)
MAKE_CONTROL_PARAM_FUNCTIONS(GRID_LINE_STYLE, CDPL::Vis::Pen::LineStyle, GridLineStyle)
MAKE_CONTROL_PARAM_FUNCTIONS(GRID_LINE_COLOR, const CDPL::Vis::Color&, GridLineColor)
MAKE_CONTROL_PARAM_FUNCTIONS(GRID_LINE_WIDTH, const CDPL::Vis::SizeSpecification&, GridLineWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NUMBER_LABEL_FONT, const CDPL::Vis::Font&, RecordNumberLabelFont)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NUMBER_LABEL_SIZE, const CDPL::Vis::SizeSpecification&, RecordNumberLabelSize)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NUMBER_LABEL_ALIGNMENT, unsigned int, RecordNumberLabelAlignment)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NUMBER_LABEL_COLOR, const CDPL::Vis::Color&, RecordNumberLabelColor)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NAME_LABEL_FONT, const CDPL::Vis::Font&, RecordNameLabelFont)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NAME_LABEL_SIZE, const CDPL::Vis::SizeSpecification&, RecordNameLabelSize)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NAME_LABEL_ALIGNMENT, unsigned int, RecordNameLabelAlignment)
MAKE_CONTROL_PARAM_FUNCTIONS(RECORD_NAME_LABEL_COLOR, const CDPL::Vis::Color&, RecordNameLabelColor)

MAKE_CONTROL_PARAM_FUNCTIONS(PRINT_FRAME, bool, PrintFrame)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINT_DATE, bool, PrintDate)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINT_PAGE_NUMBER, bool, PrintPageNumber)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINT_FILE_NAME, bool, PrintFileName)
MAKE_CONTROL_PARAM_FUNCTIONS(FRAME_LINE_STYLE, CDPL::Vis::Pen::LineStyle, FrameLineStyle)
MAKE_CONTROL_PARAM_FUNCTIONS(FRAME_LINE_COLOR, const CDPL::Vis::Color&, FrameLineColor)
MAKE_CONTROL_PARAM_FUNCTIONS(FRAME_LINE_WIDTH, const CDPL::Vis::SizeSpecification&, FrameLineWidth)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINTING_TEXT_LABEL_FONT, const CDPL::Vis::Font&, PrintingTextLabelFont)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINTING_TEXT_LABEL_SIZE, const CDPL::Vis::SizeSpecification&, PrintingTextLabelSize)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINTING_TEXT_LABEL_SPACING, const CDPL::Vis::SizeSpecification&, PrintingTextLabelSpacing)
MAKE_CONTROL_PARAM_FUNCTIONS(PRINTING_TEXT_LABEL_COLOR, const CDPL::Vis::Color&, PrintingTextLabelColor)
MAKE_CONTROL_PARAM_FUNCTIONS(PAGE_NUMBER_LABEL_ALIGNMENT, unsigned int, PageNumberLabelAlignment)
MAKE_CONTROL_PARAM_FUNCTIONS(DATE_LABEL_ALIGNMENT, unsigned int, DateLabelAlignment)
MAKE_CONTROL_PARAM_FUNCTIONS(FILE_NAME_LABEL_ALIGNMENT, unsigned int, FileNameLabelAlignment)

MAKE_CONTROL_PARAM_FUNCTIONS(DEFAULT_MOL_OUTPUT_FORMAT, const std::string&, DefaultMolOutputFormat)
MAKE_CONTROL_PARAM_FUNCTIONS(DEFAULT_RXN_OUTPUT_FORMAT, const std::string&, DefaultRxnOutputFormat)

MAKE_CONTROL_PARAM_FUNCTIONS(WRITE_SINGLE_RECORD_FILES, bool, WriteSingleRecordFiles)

MAKE_CONTROL_PARAM_FUNCTIONS(IMG_OUTPUT_ERASE_BACKGROUND, bool, ImgOutputEraseBackground)
MAKE_CONTROL_PARAM_FUNCTIONS(IMG_OUTPUT_BACKGROUND_COLOR, const CDPL::Vis::Color&, ImgOutputBackgroundColor)

MAKE_CONTROL_PARAM_FUNCTIONS(USE_ATOM_COLOR_TABLE, bool, UseAtomColorTable)
MAKE_CONTROL_PARAM_FUNCTIONS(ATOM_COLOR_TABLE, const CDPL::Vis::ColorTable::SharedPointer&, AtomColorTable)
