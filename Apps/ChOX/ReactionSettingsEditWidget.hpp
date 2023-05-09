/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionSettingsEditWidget.hpp 
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


#ifndef CHOX_REACTIONSETTINGSEDITWIDGET_HPP
#define CHOX_REACTIONSETTINGSEDITWIDGET_HPP

#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "SettingsEditWidget.hpp"


class QCheckBox;


namespace ChOX
{

	class Settings;

	class ReactionSettingsEditWidget : public SettingsEditWidget
	{

		Q_OBJECT

	public:
		ReactionSettingsEditWidget(QWidget*, Settings&);

		bool haveChangedSettings() const;

	signals:
		void updateGUI();

	public slots:
		void apply();
		void reset();
		void setDefaults();

	private slots:
		void handleSettingsChange();
		void handleSettingsChange(int);
		void handleSettingsChange(bool);

	private:
		void init();

		Settings&                    settings;
		CDPL::Vis::Color             arrowColor;
		CDPL::Vis::Color             plusSignColor;
		CDPL::Vis::SizeSpecification plusSignSize;
		CDPL::Vis::SizeSpecification plusSignLineWidth;
		CDPL::Vis::SizeSpecification componentMargin;
		CDPL::Vis::SizeSpecification arrowLength;
		CDPL::Vis::SizeSpecification arrowHeadLength;
		CDPL::Vis::SizeSpecification arrowHeadWidth;
		CDPL::Vis::SizeSpecification arrowShaftWidth;
		CDPL::Vis::SizeSpecification arrowLineWidth;
		QCheckBox*                   showPlusSignsCheckBox;
		QCheckBox*                   showReactantsCheckBox;
		QCheckBox*                   showAgentsCheckBox;
		QCheckBox*                   showProductsCheckBox;
		unsigned int                 componentLayoutStyle;
		unsigned int                 componentLayoutDir;
		unsigned int                 agentLayoutStyle;
		unsigned int                 agentLayoutDir;
		unsigned int                 agentAlignment;
		unsigned int                 arrowStyle;
		bool                         haveChanges;
	};
}

#endif // CHOX_REACTIONSETTINGSEDITWIDGET_HPP
