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
    fontMetrics(0)
{}

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

    return *cell;
}

const Vis::StructureGridView2D::Cell& Vis::StructureGridView2D::operator()(std::size_t row, std::size_t col) const
{
    auto it = cells.find({row, col});

    if (it == cells.end())
        throw Base::ItemNotFound("StructureGridView2D: data for requested cell not available");
    
    return *it->second;
}

Vis::StructureGridView2D::CellPointer Vis::StructureGridView2D::allocCell()
{
    CellPointer cell_ptr = cellCache.get();

// TODO
    
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

// -- Cell --

Vis::StructureGridView2D::Cell::Cell()
{}

Vis::StructureGridView2D::Cell::~Cell()
{}
