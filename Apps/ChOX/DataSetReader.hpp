/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataSetReader.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CHOX_DATASETREADER_HPP
#define CHOX_DATASETREADER_HPP

#include <QObject>
#include <QString>

#include "DataRecordVisitor.hpp"
#include "FileDataRecord.hpp"


class QWidget;


namespace ChOX
{

	class Settings;
	class DataSet;

	class DataSetReader : public QObject, private DataRecordVisitor
	{

		Q_OBJECT

	public:
		DataSetReader(DataSet& data_set, QWidget* parent, const QString& file_name, 
					  const Settings& settings);

		~DataSetReader();

		bool read();

	signals:	
		void errorMessage(const QString&);
		void statusMessage(const QString&);

	private:
		void visit(const ConcreteDataRecord<CDPL::Chem::Reaction>&);
		void visit(const ConcreteDataRecord<CDPL::Chem::Molecule>&);

		template <typename T, typename ImplT>
		bool appendRecords(bool use_file_ext);
		
		DataSet&        dataSet;
		const Settings& settings;
		QWidget*        parent;
		QString         fileName;
		bool            isMoleculeDataSet;
	};
}

#endif // CHOX_DATASETREADER_HPP
