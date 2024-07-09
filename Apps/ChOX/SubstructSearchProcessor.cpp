/* 
 * SubstructSearchProcessor.cpp 
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

#include <QWidget>

#include "CDPL/Chem/MultiSubstructureSearch.hpp"
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

#include "SubstructSearchProcessor.hpp"
#include "Settings.hpp"
#include "DataSet.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterFunctions.hpp"


using namespace ChOX;


SubstructSearchProcessor::SubstructSearchProcessor(QWidget* parent, DataSet& data_set, Settings& settings):
    QObject(parent), parent(parent), dataSet(data_set), settings(settings), queryValid(false)
{
    connect(&settings, SIGNAL(controlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)),
            this, SLOT(handleControlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)));
    connect(&dataSet, SIGNAL(sizeChanged(int)), this, SLOT(handelDataSetSizeChange(int)));
}

SubstructSearchProcessor::~SubstructSearchProcessor()
{}

void SubstructSearchProcessor::handleControlParamChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& value)
{
    using namespace CDPL::Chem;
    
    if (key != ControlParameter::SUBSTRUCT_SEARCH_QUERY)
        return;
  
    auto& query = getSubstructSearchQueryParameter(settings);

    if (query.count() <= 1) {
        queryValid = false;
        emit(substructSearchEnabled(false));
        return;
    }
    
    queryValid = true;
    
    if (!subSearch)
        subSearch.reset(new MultiSubstructureSearch());
    else
        subSearch->clear();

    for (int i = 0; i < int(query.count()) - 1; i++) {
        try {
            Molecule::SharedPointer mol_ptr(new BasicMolecule());
            std::istringstream iss(query[i].toStdString());
            SMARTSMoleculeReader reader(iss);

            setStrictErrorCheckingParameter(reader, true);

            if (!reader.read(*mol_ptr)) {
                queryValid = false;
                break;
            }
            
            initSubstructureSearchQuery(*mol_ptr, false);

            subSearch->addSubstructure(mol_ptr);

        } catch (const std::exception& e) {
            queryValid = false;
            break;
        }
    }

    if (queryValid) {
        try {
            subSearch->setup(query.last().toStdString());
            
        } catch (const std::exception& e) {
            queryValid = false;
        }
    }

    emit(substructSearchEnabled(queryValid && dataSet.getSize() > 0));
}

void SubstructSearchProcessor::handelDataSetSizeChange(int size)
{
    emit(substructSearchEnabled(queryValid && size > 0));
}

void SubstructSearchProcessor::performSubstructSearch()
{
    // TODO
}

void SubstructSearchProcessor::visit(const ConcreteDataRecord<CDPL::Chem::Reaction>& record)
{
    // TODO
}

void SubstructSearchProcessor::visit(const ConcreteDataRecord<CDPL::Chem::Molecule>& record)
{
    // TODO
}
