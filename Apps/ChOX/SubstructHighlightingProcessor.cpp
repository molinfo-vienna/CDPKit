/* 
 * SubstructHighlightingProcessor.cpp 
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


#include <exception>
#include <sstream>

#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Vis/AtomFunctions.hpp"
#include "CDPL/Vis/BondFunctions.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/Pen.hpp"

#include "SubstructHighlightingProcessor.hpp"
#include "Settings.hpp"
#include "DataSetPageView.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterFunctions.hpp"


using namespace ChOX;


SubstructHighlightingProcessor::SubstructHighlightingProcessor(DataSetPageView* page_view, Settings& settings):
    QObject(page_view), pageView(page_view), settings(settings), hltgEnabled(false)
{
    connect(page_view, SIGNAL(recordBecameVisible(int)), this, SLOT(handleRecordBecameVisible(int)));
    connect(&settings, SIGNAL(controlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)),
            this, SLOT(handleControlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)));

    using namespace CDPL::Vis;

    setAtomHighlightAreaOutlinePenParameter(settings, Pen(Pen::NO_LINE));
    setBondHighlightAreaOutlinePenParameter(settings, Pen(Pen::NO_LINE));
}

SubstructHighlightingProcessor::~SubstructHighlightingProcessor()
{}

void SubstructHighlightingProcessor::handleControlParamChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& value)
{
    if (key == ControlParameter::SUBSTRUCT_HIGHLIGHTING_PATTERNS) {
        auto& patterns = getSubstructHighlightingPatternsParameter(settings);

        queryPatterns.clear();
        
        for (int i = 0; i < (patterns.count() / 2); i++) {
            if (patterns[i * 2] != "X")
                continue;

            try {
                using namespace CDPL::Chem;

                MoleculePtr mol_ptr(new BasicMolecule());
                std::istringstream iss(patterns[i * 2 + 1].toStdString());
                SMARTSMoleculeReader reader(iss);

                setStrictErrorCheckingParameter(reader, true);

                if (!reader.read(*mol_ptr))
                    continue;

                initSubstructureSearchQuery(*mol_ptr, false);
                
                queryPatterns.push_back(std::move(mol_ptr));

            } catch (const std::exception& e) {
                continue;
            }
        }
        
    } else if (key == ControlParameter::SUBSTRUCT_HIGHLIGHTING_ENABLED)
        hltgEnabled = getSubstructHighlightingEnabledParameter(settings);

    else
        return;

    pageView->accept(*this);
    pageView->updateRecordPainters();
}

void SubstructHighlightingProcessor::handleRecordBecameVisible(int rec_idx)
{
    pageView->accept(rec_idx, *this);
}

void SubstructHighlightingProcessor::visit(CDPL::Chem::Reaction& rxn)
{
    using namespace CDPL;

    for (auto& mol : rxn) {
        clearHighlightFlags(mol);

        if (!hltgEnabled || queryPatterns.empty())
            continue;

        initSubSearch();
        initSubstructureSearchTarget(mol, false);

        for (auto& ptn : queryPatterns) {
            subSearch->setQuery(*ptn);

            highlightMatchingSubstructures(mol);
        }
    }
}

void SubstructHighlightingProcessor::visit(CDPL::Chem::Molecule& mol)
{
    clearHighlightFlags(mol);
    
    if (!hltgEnabled || queryPatterns.empty())
        return;

    initSubSearch();
    initSubstructureSearchTarget(mol, false);

    for (auto& ptn : queryPatterns) {
        subSearch->setQuery(*ptn);

        highlightMatchingSubstructures(mol);
    }
}

void SubstructHighlightingProcessor::clearHighlightFlags(CDPL::Chem::Molecule& mol) const
{
    using namespace CDPL;
    
    for (auto& atom : mol.getAtoms())
        Vis::setHighlightedFlag(atom, false);

    for (auto& bond : mol.getBonds())
        Vis::setHighlightedFlag(bond, false);
}

void SubstructHighlightingProcessor::highlightMatchingSubstructures(CDPL::Chem::Molecule& mol) const
{
    using namespace CDPL;
    
    if (!subSearch->findMappings(mol))
        return;

    for (auto& ab_mpg : *subSearch) {
        for (auto& ap : ab_mpg.getAtomMapping())
            Vis::setHighlightedFlag(mol.getAtom(ap.second->getIndex()), true);

        for (auto& bp : ab_mpg.getBondMapping())
            Vis::setHighlightedFlag(mol.getBond(bp.second->getIndex()), true);
    }
}

void SubstructHighlightingProcessor::initSubSearch()
{
    if (!subSearch) {
        subSearch.reset(new CDPL::Chem::SubstructureSearch);
        subSearch->uniqueMappingsOnly(true);
    } 
}
