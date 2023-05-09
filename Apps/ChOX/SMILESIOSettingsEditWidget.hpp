/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMILESIOSettingsEditWidget.hpp 
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


#ifndef CHOX_SMILESIOSETTINGSEDITWIDGET_HPP
#define CHOX_SMILESIOSETTINGSEDITWIDGET_HPP

#include <cstddef>

#include "SettingsEditWidget.hpp"


class QCheckBox;
class QSpinBox;


namespace ChOX
{

	class Settings;

	class SMILESIOSettingsEditWidget : public SettingsEditWidget
	{

		Q_OBJECT

	public:
		SMILESIOSettingsEditWidget(QWidget*, Settings&);

		bool haveChangedSettings() const;

	signals:
		void updateGUI();

	public slots:
		void apply();
		void reset();
		void setDefaults();

	private slots:
		void handleSettingsChange();
		void handleSettingsChange(bool);
		void handleSettingsChange(int);

		void handleBondStereoSettingsChange(bool);
		void handleKekuleFormSettingChange(bool);

	private:
		void init();

		Settings&    settings;
		QCheckBox*   iptStrictErrorCheckingCheckBox;
		QCheckBox*   optStrictErrorCheckingCheckBox;
		QCheckBox*   optOrdinaryHDepleteCheckBox;
		QCheckBox*   optCanonicalFormCheckBox;
		QCheckBox*   optKekuleFormCheckBox;
		QCheckBox*   optIsotopeCheckBox;
		QCheckBox*   optAtomStereoCheckBox;
		QCheckBox*   optBondStereoCheckBox;
		QCheckBox*   optRingBondStereoCheckBox;
		QCheckBox*   optAtomAtomMappingsCheckBox;
		QCheckBox*   optExplicitSingleBondsCheckBox;
		QCheckBox*   optExplicitAromaticBondsCheckBox;
		QCheckBox*   optNoOrganicSubsetCheckBox;
		QCheckBox*   optConcatenateRecordsCheckBox;
		QSpinBox*    optMinRingSizeSpinBox;
		std::string  iptRecordFormat;
		std::string  optRecordFormat;
		bool         haveChanges;
	};
}

#endif // CHOX_SMILESIOSETTINGSEDITWIDGET_HPP
