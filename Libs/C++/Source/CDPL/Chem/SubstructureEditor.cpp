/* 
 * SubstructureEditor.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

 
#include "StaticInit.hpp"

#include "CDPL/Chem/SubstructureEditor.hpp"


using namespace CDPL;


Chem::SubstructureEditor::SubstructureEditor()
{}

Chem::SubstructureEditor::SubstructureEditor(const SubstructureEditor& editor)
{
    for (auto &ptn : editor.searchPatterns)
        searchPatterns.emplace_back(ptn.pattern);

    for (auto &ptn : editor.excludePatterns)
        excludePatterns.emplace_back(ptn.pattern);
}

Chem::SubstructureEditor::~SubstructureEditor()
{}

void Chem::SubstructureEditor::addSearchPattern(const Chem::MolecularGraph::SharedPointer& pattern)
{
    searchPatterns.emplace_back(pattern);
}

void Chem::SubstructureEditor::addExcludePattern(const Chem::MolecularGraph::SharedPointer& pattern)
{
    excludePatterns.emplace_back(pattern);
}

void Chem::SubstructureEditor::clearSearchPatterns()
{
    searchPatterns.clear();
}

void Chem::SubstructureEditor::clearExcludePatterns()
{
    excludePatterns.clear();
}

Chem::SubstructureEditor& Chem::SubstructureEditor::operator=(const SubstructureEditor& editor)
{
    if (this == &editor)
        return *this;

    searchPatterns.clear();

    for (auto &ptn : editor.searchPatterns)
        searchPatterns.emplace_back(ptn.pattern);

    excludePatterns.clear();

    for (auto &ptn : editor.excludePatterns)
        excludePatterns.emplace_back(ptn.pattern);
 
    return *this;
}
