/* 
 * FontEditWidget.cpp 
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


#include <memory>

#include <QHBoxLayout>
#include <QLabel>
#include <QFont>
#include <QPushButton>
#include <QApplication>

#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#include "FontEditWidget.hpp"
#include "FontChooserDialog.hpp"


using namespace ChOX;


FontEditWidget::FontEditWidget(QWidget* parent, CDPL::Vis::Font& font, CDPL::Vis::SizeSpecification& size_spec, 
							   const CDPL::Vis::SizeSpecification* parent_size_spec, bool size_type_editable,
							   bool policy_editable):
	QWidget(parent), font(font), sizeSpec(size_spec), parentSizeSpec(parent_size_spec),
	sizeTypeEditable(size_type_editable), policyEditable(policy_editable)
{
	init();
}

void FontEditWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	QFont qt_font = QtObjectFactory::createQFont(font);

	if (font.getFamily().empty())
		qt_font.setFamily(QApplication::font().family());

	QString text = qt_font.family();

	if (sizeSpec.isRelative()) {
		if (parentSizeSpec) {
			text = text + QString(", %1 (%2% of %3)")
				.arg(parentSizeSpec->getValue() * sizeSpec.getValue(), 0, 'f', 1)
				.arg(sizeSpec.getValue() * 100.0)
				.arg(parentSizeSpec->getValue());

			double pt_size = parentSizeSpec->getValue() * sizeSpec.getValue();

			qt_font.setPointSizeF(pt_size <= 0.0 ? 1.0 : pt_size);

		} else {
			text = text + QString(", %1%").arg(sizeSpec.getValue() * 100.0);

			qt_font.setPointSize(12);
		}

	} else {
		text = text + QString(", %1").arg(sizeSpec.getValue(), 0, 'f', 1);

		double pt_size = sizeSpec.getValue();

		qt_font.setPointSizeF(pt_size <= 0.0 ? 1.0 : pt_size);
	}

	fontLabel->setText(text);
	fontLabel->setFont(qt_font);
}

void FontEditWidget::editFont()
{
	std::auto_ptr<FontChooserDialog> chooser_dlg(new FontChooserDialog(this, font, sizeSpec, parentSizeSpec, 
																	   sizeTypeEditable, policyEditable));

	if (chooser_dlg->exec() == QDialog::Accepted) {
		updateGUI();

		emit fontChanged();
	}
}

void FontEditWidget::init()
{
	QBoxLayout* main_layout = new QHBoxLayout(this);

	main_layout->setMargin(0);

	fontLabel = new QLabel(this);

	fontLabel->setFrameStyle(QFrame::StyledPanel);
	fontLabel->setMinimumWidth(50);
	fontLabel->setFixedHeight(25);

	main_layout->addWidget(fontLabel, 1);

	QPushButton* button = new QPushButton(tr("Change..."), this);

	setFocusProxy(button);

	connect(button, SIGNAL(clicked()), this, SLOT(editFont()));

	main_layout->addWidget(button);

	updateGUI();
}
