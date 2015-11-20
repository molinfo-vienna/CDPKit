/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSetPrinter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <cstddef>
#include <algorithm>
#include <cmath>

#include <QApplication>
#include <QColor>
#include <QFont>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QRectF>
#include <QDateTime>
#include <QStringList>
#include <QFileInfo>

#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"
#include "CDPL/Vis/QtFontMetrics.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "DataSetPrinter.hpp"
#include "DataSet.hpp"
#include "DataRecord.hpp"
#include "DataRecordPainter.hpp"
#include "DataSetPagePainter.hpp"
#include "Utilities.hpp"
#include "ControlParameterFunctions.hpp"
#include "Settings.hpp"
#include "PrintProgressDialog.hpp"


using namespace ChOx;


DataSetPrinter::DataSetPrinter(const Settings& settings, const DataSet& data_set): 
	QObject(), dataSet(data_set), settings(settings)
{
}

void DataSetPrinter::print(QWidget* caller, QPrinter& printer)
{
	using namespace CDPL;
	using namespace Vis;

	int max_rec_no = std::max(int(1), dataSet.getSize());

	QPrintDialog print_dlg(&printer, caller);

	print_dlg.setMinMax(1, max_rec_no);

	print_dlg.addEnabledOption(QAbstractPrintDialog::PrintToFile);
	print_dlg.addEnabledOption(QAbstractPrintDialog::PrintPageRange);

	if (dataSet.hasSelectedRecords())
		print_dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);

	if (!print_dlg.exec() == QDialog::Accepted)
		return;

	QPainter painter(&printer);

	painter.setRenderHint(QPainter::Antialiasing, true);

	double page_width = printer.pageRect().width();
	double page_height = printer.pageRect().height();

	int num_rows = getGridRowCountParameter(settings);
	int num_cols = getGridColumnCountParameter(settings);
	int num_recs_per_page = num_rows * num_cols;

	recordList.clear();

	if (printer.printRange() == QPrinter::Selection) {
		for (int i = 0; i < dataSet.getSize(); i++)
			if (dataSet.isRecordSelected(i))
				recordList.push_back(i);

	} else if (printer.printRange() == QPrinter::PageRange) {
		for (int i = printer.fromPage(); i <= printer.toPage(); i++)
			recordList.push_back(i - 1);
		
	} else {
		for (int i = 0; i < dataSet.getSize(); i++)
			recordList.push_back(i);
	}

	int num_pages = int(std::ceil(double(recordList.size()) / num_recs_per_page));

	PrintProgressDialog progress_dlg(caller, dataSet, num_pages);

	progress_dlg.setWindowModality(Qt::ApplicationModal);
	progress_dlg.show();

	for (int i = 0; i < num_pages; i++) {
		if (progress_dlg.aborted()) {
			painter.end();
			emit statusMessage(tr("Printing Aborted."));
			return;
		}

		int page_no = i + 1;

		progress_dlg.setProgress(page_no);

		emit statusMessage(tr("Printing Page %1 of %2 ...").arg(page_no).arg(num_pages));

		qApp->processEvents();

		if (printer.pageOrder() == QPrinter::LastPageFirst) 
			printPage(painter, num_pages - i, num_pages, (num_pages - i - 1) * num_recs_per_page,
					  page_width, page_height, num_rows, num_cols);			
		else
			printPage(painter, page_no, num_pages, i * num_recs_per_page, 
					  page_width, page_height, num_rows, num_cols);			

		if (i < (num_pages - 1) && !printer.newPage()) {
			emit errorMessage(tr("Printing Failed!"));
			painter.end();
			return;
		}
	}

	painter.end();

	emit statusMessage(QString());
}

void DataSetPrinter::printPage(QPainter& painter, int page_no, int num_pages, int page_offs, double width, double height, 
							   int num_rows, int num_cols)
{
	using namespace CDPL;
	using namespace Vis;

	painter.save();
	painter.setClipping(false);

	drawTextLabels(painter, page_no, num_pages, width, height);

	painter.fillRect(QRectF(0.0, 0.0, width, height),
					 QtObjectFactory::createQColor(getViewBackgroundColorParameter(settings)));

	drawFrame(painter, width, height);

	double vp_width = width / num_cols;
	double vp_height = height / num_rows;

	DataSetPagePainter page_painter(painter, settings);

	if (getShowGridParameter(settings))
		page_painter.drawGrid(vp_width, vp_height, num_rows, num_cols);

	QtFontMetrics font_metrics(painter.device());

	for (int i = 0, rec_idx_idx = page_offs; i < num_rows && rec_idx_idx < int(recordList.size()); i++) {
		for (int j = 0; j < num_cols && rec_idx_idx < int(recordList.size()); j++, rec_idx_idx++) {
			DataRecordPainter rec_painter(font_metrics, painter, settings, dataSet.getRecord(recordList.at(rec_idx_idx)));

			page_painter.drawRecord(i, j, vp_width, vp_height, recordList.at(rec_idx_idx) + 1, rec_painter);
		}
	}

	painter.restore();
}

void DataSetPrinter::drawFrame(QPainter& painter, double width, double height) const
{
	using namespace CDPL;
	using namespace Vis;

	if (!getPrintFrameParameter(settings))
		return;

	Pen::LineStyle line_style = getFrameLineStyleParameter(settings);
	double line_width = getFrameLineWidthParameter(settings).getValue();
	const Color& line_color = getFrameLineColorParameter(settings);

	painter.setPen(QtObjectFactory::createQPen(Pen(line_color, line_width, line_style)));
	painter.drawRect(QRectF(0.0, 0.0, width, height)); 
}

void DataSetPrinter::drawTextLabels(QPainter& painter, int page_no, int num_pages, double width, double& height) const
{
	using namespace CDPL;
	using namespace Vis;
	
	bool print_date = getPrintDateParameter(settings);
	bool print_page_no = getPrintPageNumberParameter(settings);
	bool print_file_name = getPrintFileNameParameter(settings);

	if (!(print_date || print_page_no || print_file_name))
		return;

	QColor color = QtObjectFactory::createQColor(getPrintingTextLabelColorParameter(settings));
	QFont font = QtObjectFactory::createQFont(getPrintingTextLabelFontParameter(settings));
	double font_size = getPrintingTextLabelSizeParameter(settings).getValue();

	font.setPointSizeF(font_size <= 0.0 ? 1.0 : font_size);

	painter.setPen(color);
	painter.setFont(font);

	if (print_date) {
		drawText(painter, QDateTime::currentDateTime().toString(),
				 getDateLabelAlignmentParameter(settings),
				 width, height, 0.0);
	}
	
	if (print_page_no) {
		drawText(painter, QString(tr("Page %1/%2")).arg(page_no).arg(num_pages),
				 getPageNumberLabelAlignmentParameter(settings),
				 width, height, 0.0);
	}
	
	if (print_file_name) {
		const QStringList& file_list = dataSet.getFileNames();
		QString file_list_str;

		for (QStringList::ConstIterator it = file_list.begin(); it != file_list.end(); ) {
			file_list_str.append("'" + QFileInfo(*it).fileName() + "'");

			if (++it != file_list.end())
				file_list_str.append(" + ");
		}

		drawText(painter, file_list_str,
				 getFileNameLabelAlignmentParameter(settings),
				 width, height, 0.0);
	}

	double label_spacing = getPrintingTextLabelSpacingParameter(settings).getValue();

	height -= 2.0 * (font_size + label_spacing);

	painter.translate(0, font_size + label_spacing);
}
