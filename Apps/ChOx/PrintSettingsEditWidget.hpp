/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PrintSettingsEditWidget.hpp 
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


#ifndef CHOX_PRINTSETTINGSEDITWIDGET_HPP
#define CHOX_PRINTSETTINGSEDITWIDGET_HPP

#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "SettingsEditWidget.hpp"


class QCheckBox;


namespace ChOx
{

	class Settings;

	class PrintSettingsEditWidget : public SettingsEditWidget
	{

		Q_OBJECT

	public:
		PrintSettingsEditWidget(QWidget*, Settings&);

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

	private:
		void init();

		Settings&                    settings;
		CDPL::Vis::Color             frameColor;
		CDPL::Vis::Color             textLabelColor;
		CDPL::Vis::SizeSpecification frameLineWidth;
		CDPL::Vis::SizeSpecification textLabelSize;
		CDPL::Vis::SizeSpecification textLabelSpacing;
		CDPL::Vis::Pen::LineStyle    frameLineStyle;
		CDPL::Vis::Font              textLabelFont;
		unsigned int                 pageNumberAlignment;
		unsigned int                 fileNameAlignment;
		unsigned int                 dateAlignment;
		QCheckBox*                   printFrameCheckBox;
		QCheckBox*                   printDateCheckBox;
		QCheckBox*                   printPageNumberCheckBox;
		QCheckBox*                   printFileNameCheckBox;
		bool                         haveChanges;
	};
}

#endif // CHOX_PRINTSETTINGSEDITWIDGET_HPP
