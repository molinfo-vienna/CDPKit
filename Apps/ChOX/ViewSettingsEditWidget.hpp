/* 
 * ViewSettingsEditWidget.hpp 
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


#ifndef CHOX_VIEWSETTINGSEDITWIDGET_HPP
#define CHOX_VIEWSETTINGSEDITWIDGET_HPP

#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"

#include "SettingsEditWidget.hpp"


class QCheckBox;


namespace ChOX
{

    class Settings;

    class ViewSettingsEditWidget : public SettingsEditWidget
    {

        Q_OBJECT

      public:
        ViewSettingsEditWidget(QWidget*, Settings&);

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
        CDPL::Vis::Color             backgroundColor;
        CDPL::Vis::Color             selectionColor;
        CDPL::Vis::SizeSpecification viewportMargin;
        CDPL::Vis::Color             recordNumberColor;
        CDPL::Vis::Color             recordNameColor;
        CDPL::Vis::Color             gridColor;
        CDPL::Vis::Font              recordNumberFont;
        CDPL::Vis::Font              recordNameFont;
        CDPL::Vis::SizeSpecification gridLineWidth;
        CDPL::Vis::SizeSpecification recordNumberSize;
        CDPL::Vis::SizeSpecification recordNameSize;
        CDPL::Vis::Pen::LineStyle    gridLineStyle;
        unsigned int                 recordNumberAlignment;
        unsigned int                 recordNameAlignment;
        unsigned int                 recordSizeAdjustment;
        unsigned int                 recordAlignment;
        QCheckBox*                   showGridCheckBox;
        QCheckBox*                   showRecordNumbersCheckBox;
        QCheckBox*                   showRecordNamesCheckBox;
        QCheckBox*                   showRecordPropertiesCheckBox;
        QCheckBox*                   showHighlightedSubstructsCheckBox;
        bool                         haveChanges;
    };
} // namespace ChOX

#endif // CHOX_VIEWSETTINGSEDITWIDGET_HPP
