/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FontChooserWidget.hpp 
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


#ifndef CHOX_FONTCHOOSERWIDGET_HPP
#define CHOX_FONTCHOOSERWIDGET_HPP

#include <QWidget>

#include "CDPLFwd.hpp"


class QListWidget;
class QListWidgetItem;
class QLineEdit;


namespace ChOX
{

	class SizeSpecEditWidget;

	class FontChooserWidget : public QWidget
	{

		Q_OBJECT

	public:
		FontChooserWidget(QWidget*, CDPL::Vis::Font&, CDPL::Vis::SizeSpecification&, 
						  const CDPL::Vis::SizeSpecification* = 0, bool = true, bool = true);

	signals:
		void fontChanged();
		void sizeSpecChanged();

	public slots:
		void updateGUI();

	private slots:
		void handleFamilyChange(QListWidgetItem*);
		void handleStyleChange(QListWidgetItem*);
		void handleSizeChange();

	private:
		void updateStyles(const QFont&) const;
		void setPointSize(QFont&) const;

		void init(bool, bool);

		CDPL::Vis::Font&                    font;
		CDPL::Vis::SizeSpecification&       sizeSpec;
		const CDPL::Vis::SizeSpecification* parentSizeSpec;
		QListWidget*                        familyListWidget;
		QListWidget*                        styleListWidget;
		QLineEdit*                          sampleLineEdit;
		SizeSpecEditWidget*                 sizeEditWidget; 
	};
}

#endif // CHOX_FONTCHOOSERWIDGET_HPP
