/* 
 * SettingsEditDialog.hpp 
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


#ifndef CHOX_SETTINGSEDITDIALOG_HPP
#define CHOX_SETTINGSEDITDIALOG_HPP

#include <vector>

#include <QDialog>
#include <QStringList>


class QLabel;
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QPushButton;


namespace ChOX
{

    class Settings;
    class SettingsEditWidget;

    class SettingsEditDialog : public QDialog
    {

        Q_OBJECT

      public:
        SettingsEditDialog(QWidget*, Settings&, Qt::WindowFlags = 0);

        int exec();

      private slots:
        void acceptChanges();
        void resetChanges();
        void applyChanges();
        void setDefaults();

        void handleCategorySelection(QListWidgetItem*);
        void handleSettingsChange();

      private:
        void addCategoryEditWidget(SettingsEditWidget*, const QString&, const QString&);

        void init();

        typedef std::vector<SettingsEditWidget*> EditWidgetList;

        Settings&       settings;
        QListWidget*    categoryMenu;
        QLabel*         categoryDescrLabel;
        QStringList     categoryDescriptions;
        QStackedWidget* categoryEditWidgetStack;
        QPushButton*    applyChangesButton;
        EditWidgetList  categoryEditWidgetList;
    };
} // namespace ChOX

#endif // CHOX_SETTINGSEDITDIALOG_HPP
