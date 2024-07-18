/* 
 * RecentFilesList.hpp 
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


#ifndef CHOX_RECENTFILESLIST_HPP
#define CHOX_RECENTFILESLIST_HPP

#include <QObject>
#include <QStringList>


namespace ChOX
{

    class RecentFilesList : public QObject
    {

        Q_OBJECT

      public:
        static RecentFilesList& get();

        void addEntry(const QString&);

        const QStringList& getEntries() const;

      public slots:
        void clear();

      signals:
        void entriesChanged();

      private:
        RecentFilesList();

        ~RecentFilesList();

        QStringList fileNames;
    };
} // namespace ChOX

#endif // CHOX_RECENTFILESLIST_HPP
