/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SizeSpecEditWidget.cpp 
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


#include <QBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QDoubleSpinBox>

#include "CDPL/Vis/SizeSpecification.hpp"

#include "SizeSpecEditWidget.hpp"


using namespace ChOx;


SizeSpecEditWidget::SizeSpecEditWidget(QWidget* parent, CDPL::Vis::SizeSpecification& size_spec, 
									   bool type_editable, bool v_layout, bool policy_editable):
	QWidget(parent), sizeSpec(size_spec)
{
	init(type_editable, v_layout, policy_editable);
}

void SizeSpecEditWidget::updateGUI()
{
	using namespace CDPL;
	using namespace Vis;

	if (inputScalingCheckBox && outputScalingCheckBox) {
		inputScalingCheckBox->blockSignals(true);
		inputScalingCheckBox->setChecked(sizeSpec.followsInputScaling());
		inputScalingCheckBox->blockSignals(false);

		outputScalingCheckBox->blockSignals(true);
		outputScalingCheckBox->setChecked(sizeSpec.followsOutputScaling());
		outputScalingCheckBox->blockSignals(false);
	}

	valueSpinBox->blockSignals(true);
	
	if (typeComboBox)
		typeComboBox->blockSignals(true);

	if (sizeSpec.isRelative()) {
		if (typeComboBox) {
			typeComboBox->setCurrentIndex(1);
			
			valueSpinBox->setValue(sizeSpec.getValue() * 100.0);
		}

	} else {
		if (typeComboBox)
			typeComboBox->setCurrentIndex(0);

		valueSpinBox->setValue(sizeSpec.getValue());
	}

	valueSpinBox->blockSignals(false);

	if (typeComboBox)
		typeComboBox->blockSignals(false);
}

void SizeSpecEditWidget::handleValueChange(double value)
{
	if (typeComboBox && sizeSpec.isRelative())
		sizeSpec.setValue(value / 100.0);
	else
		sizeSpec.setValue(value);

	emit sizeSpecChanged();
}

void SizeSpecEditWidget::handleTypeChange(int idx)
{
	if (idx == 0) {
		sizeSpec.setValue(valueSpinBox->value());
		sizeSpec.setRelative(false);
		
	} else {
		sizeSpec.setValue(valueSpinBox->value() / 100.0);
		sizeSpec.setRelative(true);
	}

	emit sizeSpecChanged();
}

void SizeSpecEditWidget::handlePolicyChange(bool)
{
	using namespace CDPL;
	using namespace Vis;

	sizeSpec.followInputScaling(inputScalingCheckBox->isChecked());
	sizeSpec.followOutputScaling(outputScalingCheckBox->isChecked());

	emit sizeSpecChanged();
}

void SizeSpecEditWidget::init(bool type_editable, bool v_layout, bool policy_editable)
{
	QBoxLayout* main_layout = new QBoxLayout(v_layout ? QBoxLayout::TopToBottom : QBoxLayout::LeftToRight, this);

	main_layout->setMargin(0);

// ---------

	QHBoxLayout* h_box_layout = new QHBoxLayout();

	main_layout->addLayout(h_box_layout);

// ---------

	valueSpinBox = new QDoubleSpinBox(this);

	valueSpinBox->setMinimum(0.0);
	valueSpinBox->setSingleStep(0.1);

	setFocusProxy(valueSpinBox);

	h_box_layout->addWidget(valueSpinBox, 2);

	connect(valueSpinBox, SIGNAL(valueChanged(double)), this, SLOT(handleValueChange(double)));

// ---------

	if (type_editable) {
		typeComboBox = new QComboBox(this);

		typeComboBox->addItem("pt");
		typeComboBox->addItem("%");

		h_box_layout->addWidget(typeComboBox, 1);

		connect(typeComboBox, SIGNAL(activated(int)), this, SLOT(handleTypeChange(int)));

	} else {
		QLabel* label = new QLabel("pt", this);

		h_box_layout->addWidget(label, 1);

		typeComboBox = 0;
	}

// ---------

	if (policy_editable) {
		inputScalingCheckBox = new QCheckBox(tr("Follow Bond-Length Normalization"), this);
		outputScalingCheckBox = new QCheckBox(tr("Follow Viewport Scaling"), this);

		if (!v_layout)
			main_layout->addStretch();

		main_layout->addWidget(inputScalingCheckBox);

		if (!v_layout)
			main_layout->addStretch();

		main_layout->addWidget(outputScalingCheckBox);

		if (!v_layout)
			main_layout->addStretch();

		connect(inputScalingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handlePolicyChange(bool)));
		connect(outputScalingCheckBox, SIGNAL(toggled(bool)), this, SLOT(handlePolicyChange(bool)));

	} else {
		if (!v_layout) 
			main_layout->addStretch(1);
		
		inputScalingCheckBox = 0;
		outputScalingCheckBox = 0;
	}

// ---------

	updateGUI();
}
