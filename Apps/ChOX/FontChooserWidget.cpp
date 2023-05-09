/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FontChooserWidget.cpp 
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


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFontDatabase>
#include <QApplication>

#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#include "FontChooserWidget.hpp"
#include "SizeSpecEditWidget.hpp"


using namespace ChOX;


FontChooserWidget::FontChooserWidget(QWidget* parent, CDPL::Vis::Font& font, CDPL::Vis::SizeSpecification& size_spec, 
									 const CDPL::Vis::SizeSpecification* parent_size_spec, bool size_type_editable,
									 bool policy_editable):
	QWidget(parent), font(font), sizeSpec(size_spec), parentSizeSpec(parent_size_spec)
{
	init(size_type_editable, policy_editable);
}

void FontChooserWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	QFont qt_font = QtObjectFactory::createQFont(font);

	setPointSize(qt_font);

	if (qt_font.family().isEmpty())
		qt_font.setFamily(QApplication::font().family());

	sampleLineEdit->setFont(qt_font);

	familyListWidget->blockSignals(true);

	QList<QListWidgetItem*> items = familyListWidget->findItems(qt_font.family(), Qt::MatchFixedString);
	
	if (!items.isEmpty()) 
		familyListWidget->setCurrentItem(items.first());
	else 
		familyListWidget->clearSelection();
	
	familyListWidget->blockSignals(false);

	updateStyles(qt_font);

	sizeEditWidget->updateGUI();
}

void FontChooserWidget::updateStyles(const QFont& qt_font) const
{
	styleListWidget->blockSignals(true);
	styleListWidget->clear();

	QFontDatabase font_db;

	styleListWidget->insertItems(0, font_db.styles(qt_font.family()));

	QList<QListWidgetItem*> items = styleListWidget->findItems(font_db.styleString(qt_font), Qt::MatchFixedString);

	if (!items.isEmpty()) 
		styleListWidget->setCurrentItem(items.first());
	else
		styleListWidget->clearSelection();

	styleListWidget->blockSignals(false);
}

void FontChooserWidget::setPointSize(QFont& qt_font) const
{
	using namespace CDPL;
	using namespace Vis;

	double point_size = (!sizeSpec.isRelative() ? sizeSpec.getValue() 
						 : parentSizeSpec ? sizeSpec.getValue() * parentSizeSpec->getValue() : 12.0);

	qt_font.setPointSizeF(point_size <= 0.0 ? 0.01 : point_size);
}

void FontChooserWidget::handleFamilyChange(QListWidgetItem* item)
{
	QString family = item->text();

	font.setFamily(family.toStdString());

	QFont qt_font = sampleLineEdit->font();

	qt_font.setFamily(family);

	updateStyles(qt_font);

	sampleLineEdit->setFont(qt_font);

	emit fontChanged();
}

void FontChooserWidget::handleStyleChange(QListWidgetItem* item)
{
	QString style_str = item->text();

	QFontDatabase font_db;

	QString family = sampleLineEdit->font().family();

	QFont qt_font = font_db.font(family, style_str, sampleLineEdit->font().pointSize());

	sampleLineEdit->setFont(qt_font);

	font.setBold(font_db.bold(family, style_str));
	font.setItalic(font_db.italic(family, style_str));
	font.setFixedPitch(font_db.isFixedPitch(family, style_str));

	emit fontChanged();
}

void FontChooserWidget::handleSizeChange()
{
	QFont qt_font = sampleLineEdit->font();

	setPointSize(qt_font);

	sampleLineEdit->setFont(qt_font);

	emit sizeSpecChanged();
}

void FontChooserWidget::init(bool size_type_editable, bool policy_editable)
{
	QVBoxLayout* main_layout = new QVBoxLayout(this);
	
// ---------

	QHBoxLayout* h_box_layout = new QHBoxLayout();
	
	main_layout->addLayout(h_box_layout);

// ---------

	QVBoxLayout* v_box_layout = new QVBoxLayout();

	h_box_layout->addLayout(v_box_layout);
	h_box_layout->setStretchFactor(v_box_layout, 2);

// +++

	QLabel* label = new QLabel(tr("&Font:"), this);

	v_box_layout->addWidget(label);

	familyListWidget = new QListWidget(this);
	familyListWidget->setSelectionMode(QListWidget::SingleSelection);

	label->setBuddy(familyListWidget);

	setFocusProxy(familyListWidget);

	familyListWidget->insertItems(0, QFontDatabase().families());

	connect(familyListWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(handleFamilyChange(QListWidgetItem*)));

	v_box_layout->addWidget(familyListWidget);

// ---------

	v_box_layout = new QVBoxLayout();

	h_box_layout->addLayout(v_box_layout);
	h_box_layout->setStretchFactor(v_box_layout, 1);

// +++

	label = new QLabel(tr("St&yle:"), this);

	v_box_layout->addWidget(label);

	styleListWidget = new QListWidget(this);
	styleListWidget->setSelectionMode(QListWidget::SingleSelection);

	label->setBuddy(styleListWidget);

	connect(styleListWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(handleStyleChange(QListWidgetItem*)));

	v_box_layout->addWidget(styleListWidget, 1);

// ---------

	v_box_layout = new QVBoxLayout();

	h_box_layout->addLayout(v_box_layout);

// +++

	label = new QLabel(tr("&Size:"), this);

	v_box_layout->addWidget(label);

	sizeEditWidget = new SizeSpecEditWidget(this, sizeSpec, size_type_editable, true, policy_editable);

	label->setBuddy(sizeEditWidget);

	connect(sizeEditWidget, SIGNAL(sizeSpecChanged()), this, SLOT(handleSizeChange()));

	v_box_layout->addWidget(sizeEditWidget);
	v_box_layout->addStretch();

// ---------

	sampleLineEdit = new QLineEdit(tr("Sample Text"), this);

	sampleLineEdit->setAlignment(Qt::AlignHCenter);
	sampleLineEdit->setFixedHeight(100);

	main_layout->addWidget(sampleLineEdit);

// ---------

	updateGUI();
}
