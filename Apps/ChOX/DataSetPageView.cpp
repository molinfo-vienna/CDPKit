/* 
 * DataSetPageView.cpp 
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


#include <algorithm>

#include <QColor>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QPaintEvent>
#include <QMenu>
#include <QRectF>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#include "DataSetPageView.hpp"
#include "DataSet.hpp"
#include "DataRecord.hpp"
#include "DataSetPagePainter.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterFunctions.hpp"
#include "Settings.hpp"


using namespace ChOX;


DataSetPageView::DataSetPageView(QWidget* parent, Settings& settings, DataSet& data_set): 
	QWidget(parent), contextMenu(0), xorSelection(false), selectionStartIdx(-1), selectionEndIdx(-1), 
	numRows(1), numColumns(1), pageOffset(0), gridVisible(true), dataSet(data_set), settings(settings),
	fontMetrics(this)
{
	init();
}

DataSetPageView::~DataSetPageView() {}

void DataSetPageView::setNumRows(int num_rows)
{
	if (num_rows != numRows) {
		numRows = std::max(1, num_rows);

		setGridRowCountParameter(settings, numRows);
		updateDataRecordPainters(pageOffset);
		
		emit numRowsChanged(numRows);

		update();
	}
}

void DataSetPageView::setNumColumns(int num_cols)
{
	if (num_cols != numColumns) {
		numColumns = std::max(1, num_cols);

		setGridColumnCountParameter(settings, numColumns);
		updateDataRecordPainters(pageOffset);
		
		emit numColumnsChanged(numColumns);

		update();
	}
}

void DataSetPageView::setPageOffset(int page_offs)
{
	if (page_offs != pageOffset && page_offs < dataSet.getSize()) {
		int old_page_offs = pageOffset;

		pageOffset = std::max(0, page_offs);
		
		updateDataRecordPainters(old_page_offs);

		emit pageOffsetChanged(pageOffset);

		update();
	}
}

int DataSetPageView::getNumRows() const
{
	return numRows;
}

int DataSetPageView::getNumColumns() const
{
	return numColumns;
}

int DataSetPageView::getPageOffset() const
{
	return pageOffset;
}

DataSet& DataSetPageView::getDataSet() const
{
	return dataSet;
}

void DataSetPageView::setContextMenu(QMenu* menu)
{
	contextMenu = menu;
}

void DataSetPageView::addRow()
{
	setNumRows(numRows + 1);
}

void DataSetPageView::deleteRow()
{
	setNumRows(numRows - 1);
}

void DataSetPageView::addColumn()
{
	setNumColumns(numColumns + 1);
}

void DataSetPageView::deleteColumn()
{
	setNumColumns(numColumns - 1);
}

void DataSetPageView::toNextPage()
{
	setPageOffset(pageOffset + numColumns * numRows);
}

void DataSetPageView::toPrevPage()
{
	setPageOffset(pageOffset - numColumns * numRows);
}

void DataSetPageView::toNextRow()
{
	setPageOffset(pageOffset + numColumns);
}

void DataSetPageView::toPrevRow()
{
	setPageOffset(pageOffset - numColumns);
}

void DataSetPageView::toFirstRecord()
{
	setPageOffset(0);
}

void DataSetPageView::toLastRecord()
{
	setPageOffset(dataSet.getSize() - 1);
}

void DataSetPageView::showGrid(bool show)
{
	if (gridVisible == show)
		return;

	gridVisible = show;

	setShowGridParameter(settings, gridVisible);

	emit gridVisibilityChanged(show);

	update();
}

void DataSetPageView::showRecordNumbers(bool show)
{
	if (recordNosVisible == show)
		return;

	recordNosVisible = show;

	setShowRecordNumbersParameter(settings, recordNosVisible);
	
	emit recordNoVisibilityChanged(show);

	update();
}

void DataSetPageView::showRecordNames(bool show)
{
	if (recordNamesVisible == show)
		return;

	recordNamesVisible = show;

	setShowRecordNamesParameter(settings, recordNamesVisible);
	
	emit recordNameVisibilityChanged(show);

	update();
}

void DataSetPageView::handleDataSetSizeChange(int new_size)
{
	if (pageOffset >= new_size)
		setPageOffset(new_size - int(dataRecordPainters.size()));

	updateDataRecordPainters(-1);

	selectionStartIdx = selectionEndIdx = -1;

	update();
}

void DataSetPageView::handleControlParamChange(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& val)
{
	if (key == ControlParameter::SHOW_GRID) {
		showGrid(getShowGridParameter(settings));
		return;
	} 

	if (key == ControlParameter::SHOW_RECORD_NUMBERS) {
		showRecordNumbers(getShowRecordNumbersParameter(settings));
		return;
	}

	if (key == ControlParameter::SHOW_RECORD_NAMES) {
		showRecordNames(getShowRecordNamesParameter(settings));
		return;
	}

	if (key == ControlParameter::GRID_ROW_COUNT) {
		setNumRows(getGridRowCountParameter(settings));
		return;
	}

	if (key == ControlParameter::GRID_COLUMN_COUNT) {
		setNumColumns(getGridColumnCountParameter(settings));
		return;
	}

	update();
}

void DataSetPageView::handleSelectionStatusChange(bool)
{
	update();
}

void DataSetPageView::init()
{
	connect(&dataSet, SIGNAL(selectionStatusChanged(bool)), this, SLOT(handleSelectionStatusChange(bool)));
	connect(&dataSet, SIGNAL(sizeChanged(int)), this, SLOT(handleDataSetSizeChange(int)));
	connect(&settings, SIGNAL(controlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)), 
			this, SLOT(handleControlParamChange(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)));

	setAttribute(Qt::WA_OpaquePaintEvent);
	setAutoFillBackground(false);
}

void DataSetPageView::paintEvent(QPaintEvent* e)
{	
	using namespace CDPL;
	using namespace Vis;

	painter.begin(this);
	painter.setRenderHint(QPainter::Antialiasing, true);

	painter.fillRect(e->rect(), QtObjectFactory::createQColor(getViewBackgroundColorParameter(settings)));

	QColor sel_color = QtObjectFactory::createQColor(getViewSelectionColorParameter(settings));
	DataSetPagePainter page_painter(painter, settings);

	double vp_width = double(width()) / numColumns;
	double vp_height = double(height()) / numRows;

	int num_rec_painters = int(dataRecordPainters.size());

	for (int i = 0, painter_idx = 0; i < numRows && painter_idx < num_rec_painters; i++) {
		for (int j = 0; j < numColumns && painter_idx < num_rec_painters; j++, painter_idx++) {
			int rec_idx = pageOffset + painter_idx;

			bool mouse_selected = (selectionStartIdx >= 0 && selectionEndIdx >= 0 
								   && std::min(selectionStartIdx, selectionEndIdx) <= rec_idx 
								   && std::max(selectionStartIdx, selectionEndIdx) >= rec_idx);

			if (dataSet.isRecordSelected(rec_idx)) {
				if (mouse_selected && xorSelection)
					continue;

			} else if (!mouse_selected)
				continue;

			painter.fillRect(QRectF(j * vp_width, i * vp_height, vp_width, vp_height), sel_color);
		}
	}
	
	for (int i = 0, painter_idx = 0; i < numRows && painter_idx < num_rec_painters; i++) {
		for (int j = 0; j < numColumns && painter_idx < num_rec_painters; j++, painter_idx++) {
			int rec_idx = pageOffset + painter_idx;
		
			page_painter.drawRecord(i, j, vp_width, vp_height, rec_idx, *dataRecordPainters[painter_idx].get());
		}
	}

	if (gridVisible)
		page_painter.drawGrid(vp_width, vp_height, numRows, numColumns);

	painter.end();
}

void DataSetPageView::mousePressEvent(QMouseEvent* e)
{
	QWidget::mousePressEvent(e);

	if (e->button() != Qt::LeftButton)
		return;
	
	if (!(e->modifiers() & Qt::ControlModifier) && !(e->modifiers() & Qt::ShiftModifier))
		dataSet.unselectAll();

	selectionStartPos = e->pos();
	selectionStartIdx = getRecordIndexAt(e->pos());
	selectionEndIdx = -1;
} 

void DataSetPageView::mouseReleaseEvent(QMouseEvent* e)
{
	QWidget::mouseReleaseEvent(e);

	if (e->button() != Qt::LeftButton)
		return;

	if (selectionStartIdx < 0 || selectionEndIdx < 0)
		return;

	dataSet.selectRecordRange(std::min(selectionStartIdx, selectionEndIdx), 
							  std::max(selectionStartIdx, selectionEndIdx), 
							  true, xorSelection);

	selectionStartIdx = selectionEndIdx = -1;
	
	update();
}

void DataSetPageView::mouseDoubleClickEvent(QMouseEvent* e)
{
	QWidget::mouseDoubleClickEvent(e);
}

void DataSetPageView::mouseMoveEvent(QMouseEvent* e)
{
	QWidget::mouseMoveEvent(e);

	if (selectionStartIdx < 0)
		return;

	if (selectionEndIdx < 0 && std::abs(e->x() - selectionStartPos.x()) < 5 && 
		std::abs(e->y() - selectionStartPos.y()) < 5)
		return;

	xorSelection = e->modifiers() & Qt::ShiftModifier;

	selectionEndIdx = getRecordIndexAt(e->pos());

	update();
}

void DataSetPageView::contextMenuEvent(QContextMenuEvent* e)
{
	if (!contextMenu)
		return;

	e->accept();
		
	contextMenu->popup(e->globalPos());
}

void DataSetPageView::updateDataRecordPainters(int old_page_offs)
{
	int page_size = numColumns * numRows;
	int old_page_size = int(dataRecordPainters.size());

	tmpDataRecordPainters.clear();
	tmpDataRecordPainters.reserve(DataRecordPainterList::size_type(page_size));

	for (int i = pageOffset; i < pageOffset + page_size && i < dataSet.getSize(); i++) {
		if (old_page_offs >= 0 && i >= old_page_offs && i < old_page_offs + old_page_size) {
			tmpDataRecordPainters.push_back(dataRecordPainters[i - old_page_offs]);
			
		} else {
			DataRecordPainter::SharedPointer painter_ptr(new DataRecordPainter(fontMetrics, painter, settings, dataSet.getRecord(i)));
					
			tmpDataRecordPainters.push_back(painter_ptr);
		}
	}

	dataRecordPainters.swap(tmpDataRecordPainters);
}

int DataSetPageView::getRecordIndexAt(const QPoint& pos) const
{
	int row = (pos.y() >= height() ? numRows - 1 : pos.y() < 0 ? 0 : pos.y() * numRows / height());
	int col = (pos.x() >= width() ? numColumns - 1 : pos.x() < 0 ? 0 : pos.x() * numColumns / width());

	return (pageOffset + row * numColumns + col);
}
