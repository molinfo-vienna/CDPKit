/* 
 * DataRecordPainter.cpp 
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


#include <string>

#include <QPainter>
#include <QFont>
#include <QColor>
#include <QRect>
#include <QPoint>
#include <QPointF>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"

#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/ReactionView2D.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"
#include "CDPL/Vis/QtFontMetrics.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"

#include "CDPL/Base/Exceptions.hpp"

#include "DataRecordPainter.hpp"
#include "ConcreteDataRecord.hpp"
#include "Settings.hpp"
#include "Utilities.hpp"
#include "ControlParameterFunctions.hpp"


namespace
{

	const double RECORD_NUMBER_LABEL_MARGIN = 3.0;
	const double RECORD_NAME_LABEL_MARGIN   = 3.0;
}


using namespace ChOX;


DataRecordPainter::DataRecordPainter(CDPL::Vis::QtFontMetrics& fm, QPainter& painter, 
									 const Settings& settings, const DataRecord& record):
	painter(painter), settings(settings), renderer(painter), fontMetrics(fm)
{
	record.accept(*this);
}

DataRecordPainter::~DataRecordPainter() {}

void DataRecordPainter::drawRecord(int rec_no, double vp_width, double vp_height)
{
	recordNosVisible = getShowRecordNumbersParameter(settings);
	recordNamesVisible = getShowRecordNamesParameter(settings);

	if (recordNosVisible)
		drawRecordNumber(rec_no, vp_width, vp_height);

	if (recordNamesVisible)
		drawRecordName(vp_width, vp_height);

	QString error_txt("ERROR");

	if (dataView) {
		if (setupViewport(vp_width, vp_height)) {
			try {
				dataView->render(renderer);
				return;
				
			} catch (const std::exception& e) {
				dataView = DataViewPointer();
			}

		} else 
			return;

	}

	painter.setPen(Qt::red);
	painter.setFont(QFont());

	QRect brect = painter.fontMetrics().boundingRect(error_txt);
	QPoint brect_ctr = brect.center();

	painter.drawText(QPointF(vp_width * 0.5 - brect_ctr.x(), vp_height * 0.5 - brect_ctr.y()), error_txt);
}

void DataRecordPainter::drawRecordNumber(int rec_no, double vp_width, double vp_height) const
{
	using namespace CDPL;
	using namespace Vis;

	QColor rec_no_color = QtObjectFactory::createQColor(getRecordNumberLabelColorParameter(settings));
	QFont rec_no_font = QtObjectFactory::createQFont(getRecordNumberLabelFontParameter(settings));
	double rec_no_font_size = getRecordNumberLabelSizeParameter(settings).getValue();

	rec_no_font.setPointSizeF(rec_no_font_size <= 0.0 ? 1.0 : rec_no_font_size);

	painter.setPen(rec_no_color);
	painter.setFont(rec_no_font);

	drawText(painter, QString("#%1").arg(rec_no + 1), 
			 getRecordNumberLabelAlignmentParameter(settings),
			 vp_width, vp_height, RECORD_NUMBER_LABEL_MARGIN);
}

void DataRecordPainter::drawRecordName(double vp_width, double vp_height) const
{
	using namespace CDPL;
	using namespace Vis;

	QColor rec_name_color = QtObjectFactory::createQColor(getRecordNameLabelColorParameter(settings));
	QFont rec_name_font = QtObjectFactory::createQFont(getRecordNameLabelFontParameter(settings));
	double rec_name_font_size = getRecordNameLabelSizeParameter(settings).getValue();

	rec_name_font.setPointSizeF(rec_name_font_size <= 0.0 ? 1.0 : rec_name_font_size);

	painter.setPen(rec_name_color);
	painter.setFont(rec_name_font);

	drawText(painter, recordName, 
			 getRecordNameLabelAlignmentParameter(settings),
			 vp_width, vp_height, RECORD_NAME_LABEL_MARGIN);
}

bool DataRecordPainter::setupViewport(double vp_width, double vp_height) const
{
	using namespace CDPL;
	using namespace Vis;

	double vp_margin = getViewportMarginParameter(settings).getValue();
	double no_label_size = (recordNosVisible ? getRecordNumberLabelSizeParameter(settings).getValue() : 0.0);
	double name_label_size = (recordNamesVisible ? getRecordNameLabelSizeParameter(settings).getValue() : 0.0);

	double min_y_offs = 0.0;
	double max_y_offs = 0.0;

	if (recordNosVisible || recordNamesVisible) {
		if ((getRecordNumberLabelAlignmentParameter(settings) & Alignment::V_ALIGNMENT_MASK) == Alignment::TOP) 
			min_y_offs = no_label_size + RECORD_NUMBER_LABEL_MARGIN * 2.0;
		else 
			max_y_offs = no_label_size + RECORD_NUMBER_LABEL_MARGIN * 2.0;

		if ((getRecordNameLabelAlignmentParameter(settings) & Alignment::V_ALIGNMENT_MASK) == Alignment::TOP) 
			min_y_offs = std::max(min_y_offs, name_label_size + RECORD_NAME_LABEL_MARGIN * 2.0);
		else 
			max_y_offs = std::max(max_y_offs, name_label_size + RECORD_NAME_LABEL_MARGIN * 2.0);

	}

	Rectangle2D vp_rect(vp_margin, vp_margin + min_y_offs, 
						vp_width - vp_margin, vp_height - vp_margin - max_y_offs);

	if (vp_rect.isDefined() && vp_rect.getArea() > 0.0) {
		setViewportParameter(*dataView, vp_rect);
		return true;
	}

	return false;
}

void DataRecordPainter::visit(const ConcreteDataRecord<CDPL::Chem::Reaction>& rxn_record)
{
	using namespace CDPL;

	try {
		Chem::Reaction::SharedPointer rxn_ptr = rxn_record.getData();
		Vis::ReactionView2D::SharedPointer rxn_view_ptr(new Vis::ReactionView2D(rxn_ptr.get()));
		
		rxn_view_ptr->setParent(&settings);
		rxn_view_ptr->setFontMetrics(&fontMetrics);

		data = rxn_ptr;
		dataView = rxn_view_ptr;

		recordName = QString::fromStdString(getName(*rxn_ptr));

	} catch (const Base::Exception&) {}
}

void DataRecordPainter::visit(const ConcreteDataRecord<CDPL::Chem::Molecule>& mol_record)
{
	using namespace CDPL;

	try {
		Chem::Molecule::SharedPointer mol_ptr = mol_record.getData();
		Vis::StructureView2D::SharedPointer mol_view_ptr(new Vis::StructureView2D(mol_ptr.get()));
		
		mol_view_ptr->setParent(&settings);
		mol_view_ptr->setFontMetrics(&fontMetrics);

		data = mol_ptr;
		dataView = mol_view_ptr;
		
		std::size_t num_confs = getNumConformations(*mol_ptr);

		if (num_confs > 0) {
			recordName = QString::fromStdString(getName(*mol_ptr) + " (" + std::to_string(num_confs) + " Confs.)");

		} else
			recordName = QString::fromStdString(getName(*mol_ptr));

	} catch (const Base::Exception& e) {
		//std::cerr << e.what() << std::endl;
	}
}
