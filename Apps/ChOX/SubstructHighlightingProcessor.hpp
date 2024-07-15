/* 
 * SubstructHighlightingProcessor.hpp 
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


#ifndef CHOX_SUBSTRUCTHIGHLIGHTINGPROCESSOR_HPP
#define CHOX_SUBSTRUCTHIGHLIGHTINGPROCESSOR_HPP

#include <vector>
#include <memory>

#include <QObject>

#include "RecordDataVisitor.hpp"
#include "CDPLFwd.hpp"


namespace CDPL
{

    namespace Chem
    {

        class SubstructureSearch;
    }
}


namespace ChOX
{

    class Settings;
    class DataSetPageView;
    
    class SubstructHighlightingProcessor : public QObject, public RecordDataVisitor
    {

        Q_OBJECT

      public:
        SubstructHighlightingProcessor(DataSetPageView* page_view, Settings& settings);

        SubstructHighlightingProcessor(const SubstructHighlightingProcessor&) = delete;

        ~SubstructHighlightingProcessor();
        
        SubstructHighlightingProcessor& operator=(const SubstructHighlightingProcessor&) = delete;
                                                                                      
      private slots:
        void handleControlParamChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& value);
        void handleRecordBecameVisible(int rec_idx);
        
      private:
        void visit(CDPL::Chem::Reaction& rxn);
        void visit(CDPL::Chem::Molecule& mol);

        void initSubSearch();

        void clearHighlightFlags(CDPL::Chem::Molecule& mol) const;
        void highlightMatchingSubstructures(CDPL::Chem::Molecule& mol) const;
        
        typedef std::unique_ptr<CDPL::Chem::SubstructureSearch> SubstructureSearchPtr;
        typedef std::shared_ptr<CDPL::Chem::Molecule>           MoleculePtr;
        typedef std::vector<MoleculePtr>                        MoleculePtrList;

        DataSetPageView*      pageView;
        Settings&             settings;
        SubstructureSearchPtr subSearch;
        MoleculePtrList       queryPatterns;
        bool                  hltgEnabled;
    };
} // namespace ChOX

#endif // CHOX_SUBSTRUCTHIGHLIGHTINGPROCESSOR_HPP
