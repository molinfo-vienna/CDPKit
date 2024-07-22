/* 
 * Clipboard.hpp 
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


#ifndef CHOX_CLIPBOARD_HPP
#define CHOX_CLIPBOARD_HPP

#include <QObject>


namespace ChOX
{

    class DataSet;
    class MainWindow;
    
    class Clipboard : public QObject
    {

        Q_OBJECT
        
      public:
        static Clipboard& get();

        void putSelectedData(const DataSet& data_set) const;

        void getData(MainWindow* main_win, DataSet& data_set, int insert_idx = -1) const;

        bool checkDataAvailability() const;
        
      signals:
        void dataAvailable(bool available);

      private slots:
        void handleClipboardChange();
    };
} // namespace ChOX

#endif // CHOX_CLIPBOARD_HPP
