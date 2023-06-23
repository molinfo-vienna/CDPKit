/* 
 * FontEditWidget.hpp 
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


#ifndef CHOX_FONTEDITWIDGET_HPP
#define CHOX_FONTEDITWIDGET_HPP

#include <QWidget>

#include "CDPLFwd.hpp"


class QLabel;


namespace ChOX
{

	class FontEditWidget : public QWidget
	{

		Q_OBJECT

	public:
		FontEditWidget(QWidget*, CDPL::Vis::Font&, CDPL::Vis::SizeSpecification&, 
					   const CDPL::Vis::SizeSpecification*, bool = true, bool = true);

	signals:
		void fontChanged();

	public slots:
		void updateGUI();

	private slots:
		void editFont();

	private:
		void init();

		CDPL::Vis::Font&                    font;
		CDPL::Vis::SizeSpecification&       sizeSpec;
		const CDPL::Vis::SizeSpecification* parentSizeSpec;
		QLabel*                             fontLabel;
		bool                                sizeTypeEditable;
		bool                                policyEditable;
	};
}

#endif // CHOX_FONTEDITWIDGET_HPP
