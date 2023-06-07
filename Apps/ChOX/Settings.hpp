/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Settings.hpp 
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


#ifndef CHOX_SETTINGS_HPP
#define CHOX_SETTINGS_HPP

#include <map>
#include <string>

#include <QObject>

#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Pharm/ScreeningDBCreator.hpp"

#include "SettingsContainer.hpp"
#include "CDPLFwd.hpp"


class QSettings;


namespace ChOX
{

	class Settings : public QObject, public SettingsContainer
	{

		Q_OBJECT

	public:
		Settings(QObject* parent = 0);

		const SettingsContainer& getReaderControlParameters(const std::string&) const;
		const SettingsContainer& getWriterControlParameters(const std::string&) const;

		SettingsContainer& getReaderControlParameters(const std::string&);
		SettingsContainer& getWriterControlParameters(const std::string&);

	public slots:
		void load();
		void save() const;

	signals:
		void controlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&);

	private:
		void writeLineStyleParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;
		void writeFontParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;
		void writeColorParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;
		void writeSizeSpecParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;

		void writeAtomColorTableParam(QSettings&) const;

		void writeDBCreationModeParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;

		void writeStrParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;

		template <typename T>
		void writeParameter(const SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&) const;

		void readLineStyleParameter(SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&, const CDPL::Vis::Pen::LineStyle&);
		void readFontParameter(SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&, const CDPL::Vis::Font&);
		void readColorParameter(SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&, const CDPL::Vis::Color&);
		void readSizeSpecParameter(SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&, const CDPL::Vis::SizeSpecification&);

		void readAtomColorTableParam(QSettings&);

		void readDBCreationModeParameter(SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&, CDPL::Pharm::ScreeningDBCreator::Mode) const;

		template <typename T>
		void readParameter(SettingsContainer&, QSettings&, const CDPL::Base::LookupKey&, const T&);

		void parameterChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&);

		typedef std::map<std::string, SettingsContainer> IOControlParamMap;

		IOControlParamMap readerControlParams;
		IOControlParamMap writerControlParams;
	};
}

#endif // CHOX_SETTINGS_HPP
