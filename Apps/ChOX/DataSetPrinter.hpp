/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSetPrinter.hpp 
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


#ifndef CHOX_DATASETPRINTER_HPP
#define CHOX_DATASETPRINTER_HPP

#include <vector>

#include <QObject>


class QPainter;
class QPrinter;
class QWidget;


namespace ChOX
{

	class DataSet;
	class Settings;

	class DataSetPrinter : public QObject
	{

		Q_OBJECT

	public:
		DataSetPrinter(const Settings&, const DataSet&);

		void print(QWidget* caller, QPrinter& printer);
		void printPage(QPainter& painter, int page_no, int num_pages, int page_offs, 
					   double width, double height, int num_rows, int num_cols);
		
	signals:
		void errorMessage(const QString&);
		void statusMessage(const QString&);

	private:
		void drawFrame(QPainter& painter, double width, double height) const;
		void drawTextLabels(QPainter& painter, int page_no, int num_pages, 
							double width, double& height) const;

		typedef std::vector<int> RecordIndexList;

		const DataSet&   dataSet;
		const Settings&  settings;
		RecordIndexList  recordList;
	};
}

#endif // CHOX_DATASETPRINTER_HPP
