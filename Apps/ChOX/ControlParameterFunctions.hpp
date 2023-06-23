/* 
 * ControlParameterFunctions.hpp 
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


#ifndef CHOX_CONTROLPARAMETERFUNCTIONS_HPP
#define CHOX_CONTROLPARAMETERFUNCTIONS_HPP

#include <string>
#include <cstddef>

#include "CDPL/Vis/ColorTable.hpp"
#include "CDPL/Vis/Pen.hpp"
	
#include "CDPLFwd.hpp"


namespace ChOX 
{

	const CDPL::Vis::Color& getViewBackgroundColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setViewBackgroundColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	const CDPL::Vis::Color& getViewSelectionColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setViewSelectionColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	const CDPL::Vis::SizeSpecification& getViewportMarginParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setViewportMarginParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& margin);

	bool getShowGridParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setShowGridParameter(CDPL::Base::ControlParameterContainer& cntnr, bool show);

	bool getShowRecordNumbersParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setShowRecordNumbersParameter(CDPL::Base::ControlParameterContainer& cntnr, bool show);

	bool getShowRecordNamesParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setShowRecordNamesParameter(CDPL::Base::ControlParameterContainer& cntnr, bool show);

	std::size_t getGridColumnCountParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setGridColumnCountParameter(CDPL::Base::ControlParameterContainer& cntnr, std::size_t count);

	std::size_t getGridRowCountParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setGridRowCountParameter(CDPL::Base::ControlParameterContainer& cntnr, std::size_t count);

	CDPL::Vis::Pen::LineStyle getGridLineStyleParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setGridLineStyleParameter(CDPL::Base::ControlParameterContainer& cntnr, CDPL::Vis::Pen::LineStyle style);

	const CDPL::Vis::Color& getGridLineColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setGridLineColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	const CDPL::Vis::SizeSpecification& getGridLineWidthParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setGridLineWidthParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& width);

	const CDPL::Vis::Font& getRecordNumberLabelFontParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNumberLabelFontParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Font& font);

	const CDPL::Vis::SizeSpecification& getRecordNumberLabelSizeParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNumberLabelSizeParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& size);

	unsigned int getRecordNumberLabelAlignmentParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNumberLabelAlignmentParameter(CDPL::Base::ControlParameterContainer& cntnr, unsigned int alignment);

	const CDPL::Vis::Color& getRecordNumberLabelColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNumberLabelColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	const CDPL::Vis::Font& getRecordNameLabelFontParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNameLabelFontParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Font& font);

	const CDPL::Vis::SizeSpecification& getRecordNameLabelSizeParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNameLabelSizeParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& size);

	unsigned int getRecordNameLabelAlignmentParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNameLabelAlignmentParameter(CDPL::Base::ControlParameterContainer& cntnr, unsigned int alignment);

	const CDPL::Vis::Color& getRecordNameLabelColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setRecordNameLabelColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	bool getPrintFrameParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintFrameParameter(CDPL::Base::ControlParameterContainer& cntnr, bool print);

	bool getPrintDateParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintDateParameter(CDPL::Base::ControlParameterContainer& cntnr, bool print);

	bool getPrintPageNumberParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintPageNumberParameter(CDPL::Base::ControlParameterContainer& cntnr, bool print);

	bool getPrintFileNameParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintFileNameParameter(CDPL::Base::ControlParameterContainer& cntnr, bool print);

	CDPL::Vis::Pen::LineStyle getFrameLineStyleParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setFrameLineStyleParameter(CDPL::Base::ControlParameterContainer& cntnr, CDPL::Vis::Pen::LineStyle style);

	const CDPL::Vis::Color& getFrameLineColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setFrameLineColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	const CDPL::Vis::SizeSpecification& getFrameLineWidthParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setFrameLineWidthParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& width);

	const CDPL::Vis::Font& getPrintingTextLabelFontParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintingTextLabelFontParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Font& font);

	const CDPL::Vis::SizeSpecification& getPrintingTextLabelSizeParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintingTextLabelSizeParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& size);

	const CDPL::Vis::SizeSpecification& getPrintingTextLabelSpacingParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintingTextLabelSpacingParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::SizeSpecification& spacing);

	const CDPL::Vis::Color& getPrintingTextLabelColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPrintingTextLabelColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	unsigned int getPageNumberLabelAlignmentParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setPageNumberLabelAlignmentParameter(CDPL::Base::ControlParameterContainer& cntnr, unsigned int alignment);

	unsigned int getDateLabelAlignmentParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setDateLabelAlignmentParameter(CDPL::Base::ControlParameterContainer& cntnr, unsigned int alignment);

	unsigned int getFileNameLabelAlignmentParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setFileNameLabelAlignmentParameter(CDPL::Base::ControlParameterContainer& cntnr, unsigned int alignment);

	const std::string& getDefaultMolOutputFormatParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setDefaultMolOutputFormatParameter(CDPL::Base::ControlParameterContainer& cntnr, const std::string& format);

	const std::string& getDefaultRxnOutputFormatParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setDefaultRxnOutputFormatParameter(CDPL::Base::ControlParameterContainer& cntnr, const std::string& format);

	bool getWriteSingleRecordFilesParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setWriteSingleRecordFilesParameter(CDPL::Base::ControlParameterContainer& cntnr, bool write);

	bool getImgOutputEraseBackgroundParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setImgOutputEraseBackgroundParameter(CDPL::Base::ControlParameterContainer& cntnr, bool erase);

	const CDPL::Vis::Color& getImgOutputBackgroundColorParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setImgOutputBackgroundColorParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::Color& color);

	bool getUseAtomColorTableParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setUseAtomColorTableParameter(CDPL::Base::ControlParameterContainer& cntnr, bool use);

	const CDPL::Vis::ColorTable::SharedPointer& getAtomColorTableParameter(const CDPL::Base::ControlParameterContainer& cntnr);
	void setAtomColorTableParameter(CDPL::Base::ControlParameterContainer& cntnr, const CDPL::Vis::ColorTable::SharedPointer& colors);
}

#endif // CHOX_CONTROLPARAMETERFUNCTIONS_HPP
 
