/* 
 * SubstructSearchResultDialog.hpp 
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


#ifndef CHOX_SUBSTRUCTSEARCHRESULTDIALOG_HPP
#define CHOX_SUBSTRUCTSEARCHRESULTDIALOG_HPP

#include <QDialog>
#include <QPixmap>


class QLabel;
class QButtonGroup;


namespace ChOX
{

    class SubstructSearchResultDialog : public QDialog
    {

        Q_OBJECT

      public:
        enum ViewAction {

            NONE = 0,
            SEL_MATCHING,
            SEL_NON_MATCHING,
            DEL_MATCHING,
            DEL_NON_MATCHING
        };
            
        SubstructSearchResultDialog(QWidget* = 0, Qt::WindowFlags = 0);

        void setup(int num_matches);

        ViewAction getViewAction() const;

      signals:
        void saveMatchingRequested();
        void saveNonMatchingRequested();
        
      private:
        void init();

        QLabel*       infoIconLabel;
        QLabel*       infoTextLabel;
        QButtonGroup* viewActionGroup;
        QPixmap       haveMatchesIcon;
        QPixmap       noMatchesIcon;
    };
} // namespace ChOX

#endif // CHOX_SUBSTRUCTSEARCHRESULTDIALOG_HPP
