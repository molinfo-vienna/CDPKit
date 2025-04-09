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
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::SubstructureEditor::SubstructureEditor()
{}

Chem::SubstructureEditor::SubstructureEditor(const SubstructureEditor& editor)
{
    for (auto &ptn : editor.searchPatterns)
        searchPatterns.emplace_back(ptn.pattern, false);

    for (auto &ptn : editor.excludePatterns)
        excludePatterns.emplace_back(ptn.pattern, true);
}

Chem::SubstructureEditor::~SubstructureEditor()
{}

void Chem::SubstructureEditor::addSearchPattern(const MolecularGraph::SharedPointer& pattern)
{
    searchPatterns.emplace_back(pattern, false);
}

std::size_t Chem::SubstructureEditor::getNumSearchPatterns() const
{
    return searchPatterns.size();
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getSearchPattern(std::size_t idx) const
{
    if (idx >= searchPatterns.size())
        throw Base::IndexError("SubstructureEditor: search pattern index out of bounds");

    return searchPatterns[idx].pattern;
}

void Chem::SubstructureEditor::removeSearchPattern(std::size_t idx)
{
    if (idx >= searchPatterns.size())
        throw Base::IndexError("SubstructureEditor: search pattern index out of bounds");

    searchPatterns.erase(searchPatterns.begin() + idx);
}

void Chem::SubstructureEditor::removeSearchPattern(const PatternIterator& it)
{
    const auto& base = it.base();

    if (base < searchPatterns.begin() || base >= searchPatterns.end())
        throw Base::RangeError("SubstructureEditor: search pattern iterator out of valid range");

    searchPatterns.erase(base);
}

void Chem::SubstructureEditor::clearSearchPatterns()
{
    searchPatterns.clear();
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getSearchPatternsBegin()
{
    return {searchPatterns.begin(), &getPattern};
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getSearchPatternsEnd()
{
    return {searchPatterns.end(), &getPattern};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getSearchPatternsBegin() const
{
    return {searchPatterns.begin(), &getPattern};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getSearchPatternsEnd() const
{
    return {searchPatterns.end(), &getPattern};
}

void Chem::SubstructureEditor::addExcludePattern(const MolecularGraph::SharedPointer& pattern)
{
    excludePatterns.emplace_back(pattern, true);
}

std::size_t Chem::SubstructureEditor::getNumExcludePatterns() const
{
    return excludePatterns.size();
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getExcludePattern(std::size_t idx) const
{
    if (idx >= excludePatterns.size())
        throw Base::IndexError("SubstructureEditor: exclude pattern index out of bounds");

    return excludePatterns[idx].pattern;
}

void Chem::SubstructureEditor::removeExcludePattern(std::size_t idx)
{
    if (idx >= excludePatterns.size())
        throw Base::IndexError("SubstructureEditor: exclude pattern index out of bounds");

    excludePatterns.erase(excludePatterns.begin() + idx);
}

void Chem::SubstructureEditor::removeExcludePattern(const PatternIterator& it)
{
    const auto& base = it.base();

    if (base < excludePatterns.begin() || base >= excludePatterns.end())
        throw Base::RangeError("SubstructureEditor: exclude pattern iterator out of valid range");

    excludePatterns.erase(base);
}

void Chem::SubstructureEditor::clearExcludePatterns()
{
    excludePatterns.clear();
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getExcludePatternsBegin()
{
    return {excludePatterns.begin(), &getPattern};
}

Chem::SubstructureEditor::PatternIterator Chem::SubstructureEditor::getExcludePatternsEnd()
{
    return {excludePatterns.end(), &getPattern};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getExcludePatternsBegin() const
{
    return {excludePatterns.begin(), &getPattern};
}

Chem::SubstructureEditor::ConstPatternIterator Chem::SubstructureEditor::getExcludePatternsEnd() const
{
    return {excludePatterns.end(), &getPattern};
}

void Chem::SubstructureEditor::setResultPattern(const MolecularGraph::SharedPointer& pattern)
{
    resultPattern = pattern;
}

const Chem::MolecularGraph::SharedPointer& Chem::SubstructureEditor::getResultPattern() const
{
    return resultPattern;
}

std::size_t Chem::SubstructureEditor::edit(Molecule& mol)
{
    // TODO
    
    return 0;
}

std::size_t Chem::SubstructureEditor::edit(const MolecularGraph& molgraph, Molecule& res_mol)
{
    // TODO
    
    return 0;
}

Chem::SubstructureEditor& Chem::SubstructureEditor::operator=(const SubstructureEditor& editor)
{
    if (this == &editor)
        return *this;

    searchPatterns.clear();

    for (auto &ptn : editor.searchPatterns)
        searchPatterns.emplace_back(ptn.pattern, false);

    excludePatterns.clear();

    for (auto &ptn : editor.excludePatterns)
        excludePatterns.emplace_back(ptn.pattern, true);
 
    return *this;
}
