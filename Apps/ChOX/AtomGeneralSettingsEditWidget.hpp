/* 
 * AtomGeneralSettingsEditWidget.hpp 
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


#ifndef CHOX_ATOMGENERALSETTINGSEDITWIDGET_HPP
#define CHOX_ATOMGENERALSETTINGSEDITWIDGET_HPP

#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "SettingsEditWidget.hpp"


class QCheckBox;


namespace ChOX
{

    class Settings;

    class AtomGeneralSettingsEditWidget : public SettingsEditWidget
    {

        Q_OBJECT

      public:
        AtomGeneralSettingsEditWidget(QWidget*, Settings&);

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

        void handleHCountVisibilityChange(bool);

      private:
        void init();

        Settings&                    settings;
        CDPL::Vis::Font              labelFont;
        CDPL::Vis::Font              secondaryLabelFont;
        CDPL::Vis::SizeSpecification labelSize;
        CDPL::Vis::SizeSpecification secondaryLabelSize;
        CDPL::Vis::SizeSpecification labelMargin;
        CDPL::Vis::SizeSpecification electronDotSize;
        QCheckBox*                   showCarbonsCheckBox;
        QCheckBox*                   showChargesCheckBox;
        QCheckBox*                   showIsotopesCheckBox;
        QCheckBox*                   showExplicitHsCheckBox;
        QCheckBox*                   showHCountsCheckBox;
        QCheckBox*                   showNonCarbonHCountsCheckBox;
        QCheckBox*                   showQueryInfosCheckBox;
        QCheckBox*                   showReactionInfosCheckBox;
        QCheckBox*                   showRadicalElectronsCheckBox;
        QCheckBox*                   useCalcAtomCoordsCheckBox;
        bool                         haveChanges;
    };
} // namespace ChOX

#endif // CHOX_ATOMGENERALSETTINGSEDITWIDGET_HPP
