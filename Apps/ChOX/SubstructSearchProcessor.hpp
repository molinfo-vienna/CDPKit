/* 
 * SubstructSearchProcessor.hpp 
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


#ifndef CHOX_SUBSTRUCTSEARCHPROCESSOR_HPP
#define CHOX_SUBSTRUCTSEARCHPROCESSOR_HPP

#include <vector>
#include <memory>

#include <QObject>

#include "DataRecordVisitor.hpp"
#include "CDPLFwd.hpp"


class QWidget;


namespace CDPL
{

    namespace Chem
    {

        class MultiSubstructureSearch;
    }
}


namespace ChOX
{

    class Settings;
    class DataSet;
    
    class SubstructSearchProcessor : public QObject, public DataRecordVisitor
    {

        Q_OBJECT

      public:
        SubstructSearchProcessor(QWidget* parent, DataSet& data_set, Settings& settings);

        SubstructSearchProcessor(const SubstructSearchProcessor&) = delete;

        ~SubstructSearchProcessor();
        
        SubstructSearchProcessor& operator=(const SubstructSearchProcessor&) = delete;
                                                                                     
      signals:
        void substructSearchEnabled(bool enabled);

      public slots:
        void performSubstructSearch();
                                                 
      private slots:
        void handleControlParamChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& value);
        void handelDataSetSizeChange(int size);
        
      private:
        void visit(const ConcreteDataRecord<CDPL::Chem::Reaction>&);
        void visit(const ConcreteDataRecord<CDPL::Chem::Molecule>&);
        
        typedef std::unique_ptr<CDPL::Chem::MultiSubstructureSearch> SubstructureSearchPtr;

        QWidget*              parent;
        DataSet&              dataSet;
        Settings&             settings;
        SubstructureSearchPtr subSearch;
        bool                  queryValid;
    };
} // namespace ChOX

#endif // CHOX_SUBSTRUCTSEARCHPROCESSOR_HPP
