/* 
 * SubstructSearchUtilsToolBar.hpp 
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


#ifndef CHOX_SUBSTRUCTSEARCHUTILSTOOLBAR_HPP
#define CHOX_SUBSTRUCTSEARCHUTILSTOOLBAR_HPP

#include <QToolBar>


namespace ChOX
{

    class Settings;
    class SubstructSearchQueryEditDialog;
    
    class SubstructSearchUtilsToolBar : public QToolBar
    {

        Q_OBJECT

      public:
        SubstructSearchUtilsToolBar(QWidget* parent, Settings& settings);

      private slots:
        void editSubSearchQuery();
        void performSubSearch();
        
      private:
        void init();

        Settings&                       settings;
        SubstructSearchQueryEditDialog* subSearchQueryDialog;
    };
} // namespace ChOX

#endif // CHOX_SUBSTRUCTSEARCHUTILSTOOLBAR_HPP
