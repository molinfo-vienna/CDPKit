/* 
 * OtherIOSettingsEditWidget.hpp 
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


#ifndef CHOX_OTHERIOSETTINGSEDITWIDGET_HPP
#define CHOX_OTHERIOSETTINGSEDITWIDGET_HPP

#include "SettingsEditWidget.hpp"

#include "CDPL/Vis/Color.hpp"


class QCheckBox;
class QLineEdit;
class QDoubleSpinBox;


namespace ChOX
{

    class Settings;
    class ColorEditWidget;

    class OtherIOSettingsEditWidget : public SettingsEditWidget
    {

        Q_OBJECT

      public:
        OtherIOSettingsEditWidget(QWidget*, Settings&);

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
        void handleSettingsChange(const QString&);
        void handleImgBackgroundSettingsChange(bool);

      private:
        void init();

        Settings&        settings;
        QCheckBox*       jmeIptStrictErrorCheckingCheckBox;
        QCheckBox*       jmeOptStrictErrorCheckingCheckBox;
        QCheckBox*       jmeOptConcatenateRecordsCheckBox;
        std::string      jmeOptRecordSeparator;
        QCheckBox*       smartsIptStrictErrorCheckingCheckBox;
        QCheckBox*       smartsOptStrictErrorCheckingCheckBox;
        QCheckBox*       smartsOptConcatenateRecordsCheckBox;
        std::string      smartsOptRecordSeparator;
        QCheckBox*       inchiIptStrictErrorCheckingCheckBox;
        QLineEdit*       inchiIptOptionsLineEdit;
        QCheckBox*       inchiOptStrictErrorCheckingCheckBox;
        QCheckBox*       inchiOptConcatenateRecordsCheckBox;
        QLineEdit*       inchiOptOptionsLineEdit;
        std::string      inchiOptRecordSeparator;
        QDoubleSpinBox*  imgOptOutputScalingFactorSpinBox;
        QCheckBox*       imgOptEraseBackgroundCheckBox;
        CDPL::Vis::Color imgOptBackgroundColor;
        ColorEditWidget* imgBackgroundColorWidget;
        bool             haveChanges;
    };
} // namespace ChOX

#endif // CHOX_OTHERIOSETTINGSEDITWIDGET_HPP
