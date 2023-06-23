/* 
 * SizeAdjustmentEditWidget.cpp 
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


#include <QHBoxLayout>
#include <QComboBox>

#include "CDPL/Vis/SizeAdjustment.hpp"

#include "SizeAdjustmentEditWidget.hpp"


using namespace ChOX;


SizeAdjustmentEditWidget::SizeAdjustmentEditWidget(QWidget* parent, unsigned int& size_adjustment):
    QWidget(parent), sizeAdjustment(size_adjustment)
{
    init();
}

void SizeAdjustmentEditWidget::updateGUI()
{
    using namespace CDPL;
    using namespace Vis;

    sizeAdjustmentComboBox->blockSignals(true);

    switch (sizeAdjustment) {

        case SizeAdjustment::NONE:
            sizeAdjustmentComboBox->setCurrentIndex(0);
            break;

        case SizeAdjustment::BEST_FIT:
            sizeAdjustmentComboBox->setCurrentIndex(2);
            break;

        default:
            sizeAdjustmentComboBox->setCurrentIndex(1);
    }

    sizeAdjustmentComboBox->blockSignals(false);
}

void SizeAdjustmentEditWidget::handleAdjustmentSelection(int idx)
{
    using namespace CDPL;
    using namespace Vis;

    switch (idx) {

        case 0:
            sizeAdjustment = SizeAdjustment::NONE;
            break;

        case 2:
            sizeAdjustment = SizeAdjustment::BEST_FIT;
            break;

        default:
            sizeAdjustment = SizeAdjustment::IF_REQUIRED;
    }

    emit sizeAdjustmentChanged();
}

void SizeAdjustmentEditWidget::init()
{
    QHBoxLayout* main_layout = new QHBoxLayout(this);

    main_layout->setMargin(0);

    sizeAdjustmentComboBox = new QComboBox(this);

    connect(sizeAdjustmentComboBox, SIGNAL(activated(int)), this, SLOT(handleAdjustmentSelection(int)));

    setFocusProxy(sizeAdjustmentComboBox);

    sizeAdjustmentComboBox->addItem(tr("None"));
    sizeAdjustmentComboBox->addItem(tr("Ensure Visibility"));
    sizeAdjustmentComboBox->addItem(tr("Best Fit"));

    main_layout->addWidget(sizeAdjustmentComboBox);

    updateGUI();
}
