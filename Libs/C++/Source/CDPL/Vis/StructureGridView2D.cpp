/* 
 * StructureGridView2D.cpp 
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

#include <algorithm>

#include "CDPL/Vis/StructureGridView2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

    constexpr std::size_t MAX_CELL_CACHE_SIZE = 100;
}


Vis::StructureGridView2D::StructureGridView2D(): 
    cellCache(&StructureGridView2D::newCell, &StructureGridView2D::deleteCell, MAX_CELL_CACHE_SIZE),
    fontMetrics(0), numRows(0), numColumns(0)
{
    cellCache.setCleanupFunction(&StructureGridView2D::cleanupCell);
}

Vis::StructureGridView2D::~StructureGridView2D()
{}

void Vis::StructureGridView2D::render(Renderer2D& renderer)
{}

void Vis::StructureGridView2D::setFontMetrics(FontMetrics* font_metrics)
{
    fontMetrics = font_metrics;
}

Vis::FontMetrics* Vis::StructureGridView2D::getFontMetrics() const
{
    return fontMetrics;
}

void Vis::StructureGridView2D::getModelBounds(Rectangle2D& bounds)
{
    bounds.reset(); // TODO
}


Vis::StructureGridView2D::Cell& Vis::StructureGridView2D::operator()(std::size_t row, std::size_t col)
{
    auto& cell = cells[{row, col}];

    if (!cell)
        cell = allocCell();

    numRows = std::max(numRows, row + 1);
    numColumns = std::max(numColumns, col + 1);

    return *cell;
}

const Vis::StructureGridView2D::Cell& Vis::StructureGridView2D::operator()(std::size_t row, std::size_t col) const
{
    auto it = cells.find({row, col});

    if (it == cells.end())
        throw Base::ItemNotFound("StructureGridView2D: data for requested cell not available");
    
    return *it->second;
}
 
void Vis::StructureGridView2D::resize(std::size_t num_rows, std::size_t num_cols)
{
    numRows = num_rows;
    numColumns = num_cols;

    for (auto it = cells.begin(), end = cells.end(); it != end; )
        if (it->first.first >= num_rows || it->first.second >= num_cols)
            it = cells.erase(it);
        else
            ++it;
}

void Vis::StructureGridView2D::clear(bool resize, bool structure, bool text)
{
    if (resize) {
        cells.clear();
        
        numRows = 0;
        numColumns = 0;
        return;
    }

    for (auto& ce : cells)
        ce.second->clear(structure, text);
}

std::size_t Vis::StructureGridView2D::getNumRows() const
{
    return numRows;
}

std::size_t Vis::StructureGridView2D::getNumColumns() const
{
    return numColumns;
}

Vis::StructureGridView2D::CellPointer Vis::StructureGridView2D::allocCell()
{
    CellPointer cell_ptr = cellCache.get();

    cell_ptr->setParent(this);
 
    return cell_ptr;
}
 
Vis::StructureGridView2D::Cell* Vis::StructureGridView2D::newCell()
{
    return new Cell();
}

void Vis::StructureGridView2D::deleteCell(Cell* cell)
{
    delete cell;
}
   
void Vis::StructureGridView2D::cleanupCell(Cell& cell)
{
    cell.molecule.clear();
    cell.setParent(nullptr);
}

// -- Cell --

Vis::StructureGridView2D::Cell::Cell() 
{
    structView.setParent(this);
}

Vis::StructureGridView2D::Cell::~Cell()
{}

void Vis::StructureGridView2D::Cell::setStructure(const Chem::MolecularGraph& molgraph)
{
    molecule = molgraph;

    structView.setStructure(&molecule);
}

const Chem::MolecularGraph& Vis::StructureGridView2D::Cell::getStructure() const
{
    return molecule;
}

void Vis::StructureGridView2D::Cell::clear(bool structure, bool text)
{
    if (structure) {
        molecule.clear();
        structView.setStructure(nullptr);
    }

    // TODO
}
