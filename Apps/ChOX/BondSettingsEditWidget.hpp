/* 
 * BondSettingsEditWidget.hpp 
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


#ifndef CHOX_BONDSETTINGSEDITWIDGET_HPP
#define CHOX_BONDSETTINGSEDITWIDGET_HPP

#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "SettingsEditWidget.hpp"


class QCheckBox;


namespace ChOX
{

    class Settings;

    class BondSettingsEditWidget : public SettingsEditWidget
    {

        Q_OBJECT

      public:
        BondSettingsEditWidget(QWidget*, Settings&);

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
        CDPL::Vis::Color             color;
        CDPL::Vis::Color             configLabelColor;
        CDPL::Vis::Font              labelFont;
        CDPL::Vis::Font              configLabelFont;
        CDPL::Vis::SizeSpecification labelSize;
        CDPL::Vis::SizeSpecification configLabelSize;
        CDPL::Vis::SizeSpecification labelMargin;
        CDPL::Vis::SizeSpecification bondLength;
        CDPL::Vis::SizeSpecification bondLineWidth;
        CDPL::Vis::SizeSpecification bondLineSpacing;
        CDPL::Vis::SizeSpecification wedgeWidth;
        CDPL::Vis::SizeSpecification hashSpacing;
        CDPL::Vis::SizeSpecification rxnCenterLineLength;
        CDPL::Vis::SizeSpecification rxnCenterLineSpacing;
        CDPL::Vis::SizeSpecification doubleBondTrimLength;
        CDPL::Vis::SizeSpecification tripleBondTrimLength;
        QCheckBox*                   showQueryInfosCheckBox;
        QCheckBox*                   showReactionInfosCheckBox;
        QCheckBox*                   showBondStereoCheckBox;
        QCheckBox*                   showBondConfigLabelsCheckBox;
        bool                         haveChanges;
    };
} // namespace ChOX

#endif // CHOX_BONDSETTINGSEDITWIDGET_HPP
