/* 
 * DataSetViewControl.hpp 
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


#ifndef CHOX_DATASETVIEWCONTROL_HPP
#define CHOX_DATASETVIEWCONTROL_HPP

#include <QToolBar>


class QToolButton;
class QSpinBox;
class QLineEdit;
class QIntValidator;


namespace ChOX
{

    class DataSetView;

    class DataSetViewControl : public QToolBar
    {

        Q_OBJECT

      public:
        DataSetViewControl(QMainWindow*, DataSetView&);

      signals:
        void numRowsChanged(int);
        void numColumnsChanged(int);
        void pageOffsetChanged(int);

      private slots:
        void handlePageOffsetInput();

        void handleNextPageButtonClick();
        void handlePrevPageButtonClick();
        void handleNextLineButtonClick();
        void handlePrevLineButtonClick();

        void updateGUI(int);

      private:
        void init();

        DataSetView&   dataSetView;
        QSpinBox*      rowCountSpinBox;
        QSpinBox*      columnCountSpinBox;
        QLineEdit*     pageOffsetLineEdit;
        QIntValidator* pageOffsetValidator;
        QToolButton*   nextLineButton;
        QToolButton*   nextPageButton;
        QToolButton*   prevLineButton;
        QToolButton*   prevPageButton;
    };
} // namespace ChOX

#endif // CHOX_DATASETVIEWCONTROL_HPP
