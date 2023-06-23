/* 
 * RDFileIOSettingsEditWidget.hpp 
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


#ifndef CHOX_RDFILEIOSETTINGSEDITWIDGET_HPP
#define CHOX_RDFILEIOSETTINGSEDITWIDGET_HPP

#include "SettingsEditWidget.hpp"


class QCheckBox;


namespace ChOX
{

    class Settings;
    class CTabVersionEditWidget;

    class RDFileIOSettingsEditWidget : public SettingsEditWidget
    {

        Q_OBJECT

    public:
        RDFileIOSettingsEditWidget(QWidget*, Settings&);

        bool haveChangedSettings() const;

    signals:
        void updateGUI();

    public slots:
        void apply();
        void reset();
        void setDefaults();

    private slots:
        void handleRXNFileVersionChange();

        void handleSettingsChange();
        void handleSettingsChange(bool);

    private:
        void init();

        Settings&              settings;
        QCheckBox*             iptStrictErrorCheckingCheckBox;
        QCheckBox*             iptIgnoreParityCheckBox;
        QCheckBox*             iptTrimStringsCheckBox;
        QCheckBox*             iptTrimLinesCheckBox;
        QCheckBox*             iptCheckLineLengthCheckBox;
        QCheckBox*             optStrictErrorCheckingCheckBox;
        QCheckBox*             optUpdateTimeStampCheckBox;
        QCheckBox*             optTrimStringsCheckBox;
        QCheckBox*             optTrimLinesCheckBox;
        QCheckBox*             optTruncateStringsCheckBox;
        QCheckBox*             optTruncateLinesCheckBox;
        QCheckBox*             optCheckLineLengthCheckBox;
        QCheckBox*             optIgnoreParityCheckBox;
        QCheckBox*             optSplitRecordsCheckBox;
        CTabVersionEditWidget* optCTabVersionEditWidget;
        unsigned int           optCTabVersion;
        unsigned int           optRXNFileVersion;
        bool                   haveChanges;
    };
}

#endif // CHOX_RDFILEIOSETTINGSEDITWIDGET_HPP
