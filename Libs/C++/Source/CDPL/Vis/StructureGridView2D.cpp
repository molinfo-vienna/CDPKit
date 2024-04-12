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
#include <functional>

#ifdef HAVE_CAIRO
# include <cairo.h>
#endif // HAVE_CAIRO

#include "CDPL/Vis/StructureGridView2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

    constexpr std::size_t MAX_CELL_CACHE_SIZE = 100;
}


Vis::StructureGridView2D::StructureGridView2D(): 
    cellCache(&StructureGridView2D::newCell, &StructureGridView2D::deleteCell, MAX_CELL_CACHE_SIZE),
    fontMetrics(0), cellWidth(DEF_CELL_WIDTH), cellHeight(DEF_CELL_HEIGHT), numRows(0), numColumns(0)
{
    cellCache.setCleanupFunction(&StructureGridView2D::cleanupCell);
}

Vis::StructureGridView2D::StructureGridView2D(const StructureGridView2D& grid_view):
    cellCache(&StructureGridView2D::newCell, &StructureGridView2D::deleteCell, MAX_CELL_CACHE_SIZE)
{
    copy(grid_view);
}

Vis::StructureGridView2D::~StructureGridView2D()
{}

void Vis::StructureGridView2D::render(Renderer2D& renderer)
{
    // TODO
}

#ifdef HAVE_CAIRO

bool Vis::StructureGridView2D::write(const std::string& file_name)
{
    // TODO
    return false;
}

bool Vis::StructureGridView2D::write(const std::string& file_name, const std::string& fmt)
{
    // TODO
    return false;
}

bool Vis::StructureGridView2D::write(const std::string& file_name, const Base::DataFormat& fmt)
{
    // TODO
    return false;
}

bool Vis::StructureGridView2D::write(std::ostream& os, const std::string& fmt)
{
    // TODO
    return false;
}

bool Vis::StructureGridView2D::write(std::ostream& os, const Base::DataFormat& fmt)
{
    // TODO
    return false;
}

#endif // HAVE_CAIRO

void Vis::StructureGridView2D::setFontMetrics(FontMetrics* font_metrics)
{
    fontMetrics = font_metrics;

    for (auto& ce : cells)
        ce.second->setFontMetrics(font_metrics);
}

Vis::FontMetrics* Vis::StructureGridView2D::getFontMetrics() const
{
    return fontMetrics;
}

void Vis::StructureGridView2D::getModelBounds(Rectangle2D& bounds)
{
    bounds.reset();
    // TODO
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
 
void Vis::StructureGridView2D::setCellSize(double width, double height)
{
    if (width < 0.0)
        throw Base::ValueError("StructureGridView2D: width must not be negative");

    if (height < 0.0)
        throw Base::ValueError("StructureGridView2D: height must not be negative");
    
    cellWidth = width;
    cellHeight = height;

    for (auto& ce : cells)
        ce.second->setSize(width, height);
}
          
double Vis::StructureGridView2D::getCellWidth() const
{
    return cellWidth;
}

double Vis::StructureGridView2D::getCellHeight() const
{
    return cellHeight;
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

std::size_t Vis::StructureGridView2D::getNumRows() const
{
    return numRows;
}

std::size_t Vis::StructureGridView2D::getNumColumns() const
{
    return numColumns;
}

void Vis::StructureGridView2D::clearStructures()
{
    for (auto& ce : cells)
        ce.second->clearStructure();
}

void Vis::StructureGridView2D::clearTextBlocks()
{
    for (auto& ce : cells)
        ce.second->clearText();
}

Vis::StructureGridView2D& Vis::StructureGridView2D::operator=(const StructureGridView2D& grid_view)
{
    if (this == &grid_view)
        return *this;

    copy(grid_view);
    
    return *this;
}

void Vis::StructureGridView2D::copy(const StructureGridView2D& grid_view)
{
    cells.clear();

    copyParameters(grid_view);

    fontMetrics = grid_view.fontMetrics;
    cellWidth   = grid_view.cellWidth;
    cellHeight  = grid_view.cellHeight;
    numRows     = grid_view.numRows;
    numColumns  = grid_view.numColumns;
    
    for (auto& ce : grid_view.cells) {
        auto cell_ptr = allocCell();

        *cell_ptr = *ce.second;
        
        cells.emplace(ce.first, cell_ptr);
    }
}

Vis::StructureGridView2D::CellPointer Vis::StructureGridView2D::allocCell()
{
    CellPointer cell_ptr = cellCache.get();

    cell_ptr->setParent(this);
    cell_ptr->setFontMetrics(fontMetrics);
    cell_ptr->setSize(cellWidth, cellHeight);
    
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
    cell.clearStructure();
    cell.clearText();
    cell.clearParameters();
    cell.setParent(nullptr);
}

// -- Cell --

Vis::StructureGridView2D::Cell::Cell():
    fontMetrics(nullptr), width(0.0), height(0.0), layoutValid(false),
    fontChanged(true), colorChanged(true)
{
    structView.setParent(this);

    using namespace std::placeholders;
 
    registerParameterRemovedCallback(std::bind(&Cell::parameterRemoved, this, _1));
    registerParameterChangedCallback(std::bind(&Cell::parameterChanged, this, _1, _2));
    registerParentChangedCallback(std::bind(&Cell::parentChanged, this));
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

void Vis::StructureGridView2D::Cell::clearStructure()
{
    molecule.clear();
    structView.setStructure(nullptr);
}

bool Vis::StructureGridView2D::Cell::hasStructure() const
{
    return structView.getStructure();
}

void Vis::StructureGridView2D::Cell::setText(const std::string& text, unsigned int pos, unsigned int line_almnt)
{
    if (!(line_almnt & Alignment::H_ALIGNMENT_MASK)) {
        line_almnt = (pos & Alignment::H_ALIGNMENT_MASK);

        if (!line_almnt)
            line_almnt = Alignment::H_CENTER;
    }

    auto idx = posToArrayIndex(pos);
    
    textBlocks[idx].setText(text);
    textBlocks[idx].setAlignment(line_almnt);
}

const std::string& Vis::StructureGridView2D::Cell::getText(unsigned int pos) const
{
    return textBlocks[posToArrayIndex(pos)].getText();
}

void Vis::StructureGridView2D::Cell::clearText(unsigned int pos)
{
    textBlocks[posToArrayIndex(pos)].clearText();

    layoutValid = false;
}

void Vis::StructureGridView2D::Cell::clearText()
{
    for (auto& tb : textBlocks)
        tb.clearText();

    layoutValid = false;
}

bool Vis::StructureGridView2D::Cell::hasText() const
{
    for (auto& tb : textBlocks)
        if (!tb.getText().empty())
            return true;

    return false;
}

bool Vis::StructureGridView2D::Cell::hasText(unsigned int pos) const
{
    return !textBlocks[posToArrayIndex(pos)].getText().empty();
}
                
Vis::StructureGridView2D::Cell& Vis::StructureGridView2D::Cell::operator=(const Cell& cell)
{
    if (this == &cell)
        return *this;

    copyParameters(cell);

    if (cell.hasStructure())
        setStructure(cell.getStructure());
    else
        clearStructure();

    std::copy(cell.textBlocks, cell.textBlocks + std::size(cell.textBlocks), textBlocks);

    layoutValid  = false;
    fontChanged  = true;
    colorChanged = true;

    return *this;
}

void Vis::StructureGridView2D::Cell::setFontMetrics(FontMetrics* font_metrics)
{
    fontMetrics = font_metrics;
    layoutValid = false;
}

void Vis::StructureGridView2D::Cell::setSize(double width, double height)
{
    if ((this->width != width) || (this->height != height)) {
        this->width = width;
        this->height = height;
        
        layoutValid = false;
    }
}

void Vis::StructureGridView2D::Cell::parameterChanged(const Base::LookupKey& key, const Base::Any& value)
{
    if (key == ControlParameter::GRID_VIEW_TEXT_FONT) {
        fontChanged = true;
        layoutValid = false;
        return;
    }

    if (key == ControlParameter::GRID_VIEW_TEXT_COLOR) {
        colorChanged = true;
        return;
    }

    if (key == ControlParameter::GRID_VIEW_CELL_PADDING)
        layoutValid = false;
}

void Vis::StructureGridView2D::Cell::parameterRemoved(const Base::LookupKey& key)
{
    parameterChanged(key, Base::Any());
}

void Vis::StructureGridView2D::Cell::parentChanged()
{
    fontChanged = true;
    colorChanged = true;
    layoutValid = false;
}
                
void Vis::StructureGridView2D::Cell::layout()
{
    // TODO
    layoutValid = true;
}

std::size_t Vis::StructureGridView2D::Cell::posToArrayIndex(unsigned int pos)
{
    std::size_t row = 1;
    std::size_t col = 1;
    
    switch (pos & Alignment::V_ALIGNMENT_MASK) {

        case Alignment::TOP:
            row = 0;
            break;

        case Alignment::BOTTOM:
            row = 2;
    }

    switch (pos & Alignment::H_ALIGNMENT_MASK) {

        case Alignment::LEFT:
            col = 0;
            break;

        case Alignment::RIGHT:
            col = 2;
    }

    return (row * 3 + col);
}
