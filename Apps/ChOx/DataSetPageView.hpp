/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSetPageView.hpp 
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


#ifndef CHOX_DATASETPAGEVIEW_HPP
#define CHOX_DATASETPAGEVIEW_HPP

#include <vector>

#include <QWidget>
#include <QPoint>
#include <QPainter>

#include "CDPL/Vis/QtFontMetrics.hpp"

#include "DataRecordPainter.hpp"


class QMenu;


namespace ChOx
{

	class DataSet;
	class Settings;

	class DataSetPageView : public QWidget
	{

		Q_OBJECT

	public:
		DataSetPageView(QWidget*, Settings&, DataSet&);

		~DataSetPageView();

		int getNumRows() const;
		int getNumColumns() const;
		int getPageOffset() const;

		DataSet& getDataSet() const;

		void setContextMenu(QMenu*);

	signals:
		void numRowsChanged(int);
		void numColumnsChanged(int);
		void pageOffsetChanged(int);

		void gridVisibilityChanged(bool);
		void recordNoVisibilityChanged(bool);
		void recordNameVisibilityChanged(bool);

	public slots:
		void addRow();
		void deleteRow();

		void addColumn();
		void deleteColumn();

		void toNextPage();
		void toPrevPage();

		void toNextRow();
		void toPrevRow();

		void toFirstRecord();
		void toLastRecord();

		void setNumRows(int);
		void setNumColumns(int);
		void setPageOffset(int);

		void showGrid(bool);
		void showRecordNumbers(bool);
		void showRecordNames(bool);

	private slots:
		void handleDataSetSizeChange(int);
		void handleControlParamChange(const CDPL::Base::LookupKey&, const CDPL::Base::Variant&);
		void handleSelectionStatusChange(bool);

	private:
		void init();

		void paintEvent(QPaintEvent*);

		void mousePressEvent(QMouseEvent*); 
		void mouseReleaseEvent(QMouseEvent*); 
		void mouseDoubleClickEvent(QMouseEvent*); 
		void mouseMoveEvent(QMouseEvent*); 

		void contextMenuEvent(QContextMenuEvent*);

		void updateDataRecordPainters(int);

		int getRecordIndexAt(const QPoint&) const;

		typedef std::vector<DataRecordPainter::SharedPointer> DataRecordPainterList;

		QMenu*                   contextMenu;
		QPainter                 painter;
		QPoint                   selectionStartPos;
		bool                     xorSelection;
		int                      selectionStartIdx;
		int                      selectionEndIdx;
		int                      numRows;
		int                      numColumns;
		int                      pageOffset;
		bool                     gridVisible;
		bool                     recordNosVisible;
		bool                     recordNamesVisible;
		DataSet&                 dataSet;
		Settings&                settings;
		DataRecordPainterList    dataRecordPainters;
		DataRecordPainterList    tmpDataRecordPainters;
		CDPL::Vis::QtFontMetrics fontMetrics;
	};
}

#endif // CHOX_DATASETPAGEVIEW_HPP
