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
#include <fstream>

#include "CDPL/Vis/StructureGridView2D.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/AffineTransform.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataOutputHandler.hpp"

#ifdef HAVE_CAIRO
# include <cairo.h>

# ifdef HAVE_CAIRO_SVG_SUPPORT
#  include <cairo-svg.h>
# endif

# ifdef HAVE_CAIRO_PS_SUPPORT
#  include <cairo-ps.h>
# endif

# ifdef HAVE_CAIRO_PDF_SUPPORT
#  include <cairo-pdf.h>
# endif

# include "CDPL/Vis/CairoRenderer2D.hpp"
# include "CDPL/Vis/CairoFontMetrics.hpp"
# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/StreamWriteFunc.hpp"
#endif // HAVE_CAIRO


using namespace CDPL;


namespace
{

    constexpr std::size_t MAX_CELL_CACHE_SIZE = 100;
}


constexpr double Vis::StructureGridView2D::DEF_CELL_WIDTH;
constexpr double Vis::StructureGridView2D::DEF_CELL_HEIGHT;

constexpr unsigned int Vis::StructureGridView2D::Cell::DEF_TEXT_POSITION;


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
    renderer.saveState();
    
    Math::Vector2D grid_pos;

    getGridPosition(grid_pos);
    
    auto& bg_brush = getBackgroundBrushParameter(*this);
    
    if (bg_brush.getStyle() != Brush::NO_PATTERN) {
        renderer.setBrush(bg_brush);
        renderer.setPen(Pen::NO_LINE);
        renderer.drawRectangle(0, 0, grid_pos(0) * 2.0 + numColumns * cellWidth,
                               grid_pos(1) * 2.0 + numRows * cellHeight);
    }

    auto& col_sep_pen = getGridViewColumnSeparatorPenParameter(*this);

    if (col_sep_pen.getLineStyle() != Pen::NO_LINE) {
        renderer.setPen(col_sep_pen);

        for (std::size_t i = 1; i < numColumns; i++)
            renderer.drawLine(i * cellWidth + grid_pos(0), grid_pos(1),
                              i * cellWidth + grid_pos(0), grid_pos(1) + numRows * cellHeight);
    }

    auto& row_sep_pen = getGridViewRowSeparatorPenParameter(*this);

    if (row_sep_pen.getLineStyle() != Pen::NO_LINE) {
        renderer.setPen(row_sep_pen);

        for (std::size_t i = 1; i < numRows; i++)
            renderer.drawLine(grid_pos(0), i * cellHeight + grid_pos(1),
                              grid_pos(0) + numColumns * cellWidth, i * cellHeight + grid_pos(1));
    }
    
    auto& border_pen = getGridViewBorderPenParameter(*this);

    if (border_pen.getLineStyle() != Pen::NO_LINE) {
        renderer.setBrush(Brush::NO_PATTERN);
        renderer.setPen(border_pen);
        renderer.drawRectangle(grid_pos(0), grid_pos(1), numColumns * cellWidth,
                               numRows * cellHeight);
    }

    Math::Matrix3D trans(Math::IdentityMatrix<double>(3, 3));
    
    for (auto& ce : cells) {
        ce.second->layout();

        trans(0, 2) = grid_pos(0) + ce.first.second * cellWidth;
        trans(1, 2) = grid_pos(1) + ce.first.first * cellHeight;
        
        renderer.saveState();
        renderer.transform(trans);

        ce.second->render(renderer);

        renderer.restoreState();
    }

    renderer.restoreState();
}

#ifdef HAVE_CAIRO

bool Vis::StructureGridView2D::write(const std::string& file_name)
{
    Base::DataIOManager<Chem::MolecularGraph>::OutputHandlerPointer handler;
    
    for (auto i = file_name.find_first_of('.', 0); i != std::string::npos; i = file_name.find_first_of('.', i)) {
        handler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_name.substr(++i));

        if (handler)
            break;
    }

    if (!handler)
        throw Base::IOError("StructureGridView2D: could not deduce image output format from '" + file_name + "'");

    return write(file_name, handler->getDataFormat());
}

bool Vis::StructureGridView2D::write(const std::string& file_name, const std::string& fmt)
{
    auto handler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(fmt);

    if (!handler)
        throw Base::IOError("StructureGridView2D: invalid/unsupported image output format '" + fmt + "'");

    return write(file_name, handler->getDataFormat());
}

bool Vis::StructureGridView2D::write(const std::string& file_name, const Base::DataFormat& fmt)
{
    std::ofstream os(file_name.c_str(), std::ios_base::out |
                     std::ios_base::trunc | std::ios_base::binary);

    return write(os, fmt);
}

bool Vis::StructureGridView2D::write(std::ostream& os, const std::string& fmt)
{
    auto handler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(fmt);

    if (!handler)
        throw Base::IOError("StructureGridView2D: invalid/unsupported image output format '" + fmt + "'");

    return write(os, handler->getDataFormat());
}

bool Vis::StructureGridView2D::write(std::ostream& os, const Base::DataFormat& fmt)
{
    if (!os.good())
        return false;

    Rectangle2D grid_bbox;
    auto scaling_fact = getOutputScalingFactorParameter(*this);
    
    getModelBounds(grid_bbox);

    auto render_surf_width = grid_bbox.getWidth() * scaling_fact;
    auto render_surf_height = grid_bbox.getHeight() * scaling_fact;
    
    CairoPointer<cairo_surface_t> render_surf;
    
    if (fmt == DataFormat::PNG) {
#ifdef HAVE_CAIRO_PNG_SUPPORT
        render_surf.reset(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, std::ceil(render_surf_width), std::ceil(render_surf_height)));
#endif
    } else if (fmt ==  DataFormat::SVG) {
#ifdef HAVE_CAIRO_SVG_SUPPORT
        render_surf.reset(cairo_svg_surface_create_for_stream(&streamWriteFunc, &os, render_surf_width, render_surf_height));
#endif
    } else if (fmt == DataFormat::PDF) {
#ifdef HAVE_CAIRO_PDF_SUPPORT
        render_surf.reset(cairo_pdf_surface_create_for_stream(&streamWriteFunc, &os, render_surf_width, render_surf_height));
#endif
    } else if (fmt == DataFormat::PS) {
#ifdef HAVE_CAIRO_PS_SUPPORT
        render_surf.reset(cairo_ps_surface_create_for_stream(&streamWriteFunc, &os, render_surf_width, render_surf_height));
#endif
    }

    if (!render_surf)
        throw Base::IOError("StructureGridView2D: image output format '" + fmt.getName() + "' not supported");
    
    CairoPointer<cairo_t> render_ctxt(cairo_create(render_surf.get()));

    if (cairo_status(render_ctxt.get()) != CAIRO_STATUS_SUCCESS ||
        cairo_surface_status(render_surf.get()) != CAIRO_STATUS_SUCCESS) 
        return false;
   
    CairoRenderer2D renderer(render_ctxt);
    CairoFontMetrics font_metrics(render_ctxt);

    renderer.transform(Math::DScalingMatrix(3, scaling_fact, scaling_fact, 1.0));
    
    setFontMetrics(&font_metrics);
    render(renderer);

    cairo_show_page(render_ctxt.get());

    if (fmt == DataFormat::PNG)
        cairo_surface_write_to_png_stream(render_surf.get(), &streamWriteFunc, &os);
    
    if (cairo_status(render_ctxt.get()) != CAIRO_STATUS_SUCCESS ||
        cairo_surface_status(render_surf.get()) != CAIRO_STATUS_SUCCESS)
        return false;
  
    os.flush();
    
    return os.good();
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
    Math::Vector2D grid_pos;

    getGridPosition(grid_pos);

    bounds.setBounds(0.0, 0.0, grid_pos(0) * 2.0 + numColumns * cellWidth,
                     grid_pos(1) * 2.0 + numRows * cellHeight);
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
    static Cell DUMMY_CELL;
    
    auto it = cells.find({row, col});

    if (it == cells.end())
        return DUMMY_CELL;
    
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

void Vis::StructureGridView2D::clearAllText()
{
    for (auto& ce : cells)
        ce.second->clearAllText();
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

void Vis::StructureGridView2D::getGridPosition(Math::Vector2D& pos)
{
    pos.clear();

    auto& border_pen = getGridViewBorderPenParameter(*this);

    if (border_pen.getLineStyle() != Pen::NO_LINE)
        pos.clear(border_pen.getWidth() * 0.5);

    auto& col_sep_pen = getGridViewColumnSeparatorPenParameter(*this);

    if (col_sep_pen.getLineStyle() != Pen::NO_LINE && col_sep_pen.getCapStyle() != Pen::FLAT_CAP)
        pos(1) = std::max(pos(1), col_sep_pen.getWidth() * 0.5);

    auto& row_sep_pen = getGridViewRowSeparatorPenParameter(*this);

    if (row_sep_pen.getLineStyle() != Pen::NO_LINE && row_sep_pen.getCapStyle() != Pen::FLAT_CAP)
        pos(0) = std::max(pos(0), row_sep_pen.getWidth() * 0.5);

    auto margin = getGridViewMarginParameter(*this);

    pos(0) += margin;
    pos(1) += margin;
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
    fontMetrics(nullptr), width(0.0), height(0.0), layoutValid(false)
{
    setBackgroundBrushParameter(structView, Brush::NO_PATTERN);

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
    line_almnt = (line_almnt & Alignment::H_ALIGNMENT_MASK);
    
    if (line_almnt != Alignment::LEFT && line_almnt != Alignment::H_CENTER && line_almnt != Alignment::RIGHT)
        line_almnt = (pos & Alignment::H_ALIGNMENT_MASK);
    
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

void Vis::StructureGridView2D::Cell::clearAllText()
{
    for (auto& tb : textBlocks)
        tb.clearText();

    layoutValid = false;
}

bool Vis::StructureGridView2D::Cell::hasAnyText() const
{
    for (auto& tb : textBlocks)
        if (tb.hasText())
            return true;

    return false;
}

bool Vis::StructureGridView2D::Cell::hasText(unsigned int pos) const
{
    return textBlocks[posToArrayIndex(pos)].hasText();
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

    for (std::size_t i = 0; i < 9; i++)
        textBlocks[i].setText(cell.textBlocks[i].getText());

    layoutValid  = false;
 
    return *this;
}

void Vis::StructureGridView2D::Cell::setFontMetrics(FontMetrics* font_metrics)
{
    structView.setFontMetrics(font_metrics);

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
    using namespace ControlParameter;
    
    if (key == GRID_VIEW_TEXT_FONT) {
        auto& font = getGridViewTextFontParameter(*this);

        for (auto& tb : textBlocks)
            tb.setFont(font);
        
        layoutValid = false;
        return;
    }

    if (key == GRID_VIEW_TEXT_COLOR) {
        auto& color = getGridViewTextColorParameter(*this);

        for (auto& tb : textBlocks)
            tb.setPen(color);
        
        return;
    }

    if (key == GRID_VIEW_CELL_PADDING)
        layoutValid = false;
}

void Vis::StructureGridView2D::Cell::parameterRemoved(const Base::LookupKey& key)
{
    parameterChanged(key, Base::Any());
}

void Vis::StructureGridView2D::Cell::parentChanged()
{
    using namespace ControlParameter;
    
    parameterChanged(GRID_VIEW_TEXT_FONT, Base::Any());
    parameterChanged(GRID_VIEW_TEXT_COLOR, Base::Any());
    parameterChanged(GRID_VIEW_CELL_PADDING, Base::Any());
}
                
void Vis::StructureGridView2D::Cell::layout()
{
    if (layoutValid)
        return;

    auto padding = getGridViewCellPaddingParameter(*this);

    double max_top_tb_h = 0.0;
    double max_btm_tb_h = 0.0;
    Rectangle2D bbox;
    
    auto idx = posToArrayIndex(Alignment::TOP | Alignment::LEFT);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].setPosition({ padding, padding });
        textBlocks[idx].getBounds(bbox, fontMetrics);

        max_top_tb_h = bbox.getHeight();
    }

    idx = posToArrayIndex(Alignment::TOP | Alignment::H_CENTER);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ 0.5 * (width - bbox.getWidth()), padding });

        max_top_tb_h = std::max(max_top_tb_h, bbox.getHeight());
    }

    idx = posToArrayIndex(Alignment::TOP | Alignment::RIGHT);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ width - padding - bbox.getWidth(), padding });

        max_top_tb_h = std::max(max_top_tb_h, bbox.getHeight());
    }
//
    idx = posToArrayIndex(Alignment::V_CENTER | Alignment::LEFT);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ padding, 0.5 * (height - bbox.getHeight()) });
    }

    idx = posToArrayIndex(Alignment::V_CENTER | Alignment::H_CENTER);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ 0.5 * (width - bbox.getWidth()), 0.5 * (height - bbox.getHeight()) });
    }

    idx = posToArrayIndex(Alignment::V_CENTER | Alignment::RIGHT);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ width - padding - bbox.getWidth(), 0.5 * (height - bbox.getHeight()) });

    }
//
    idx = posToArrayIndex(Alignment::BOTTOM | Alignment::LEFT);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ padding, height - padding - bbox.getHeight()});

        max_btm_tb_h = bbox.getHeight();
    }

    idx = posToArrayIndex(Alignment::BOTTOM | Alignment::H_CENTER);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ 0.5 * (width - bbox.getWidth()), height - padding - bbox.getHeight() });

        max_btm_tb_h = std::max(max_btm_tb_h, bbox.getHeight());
    }

    idx = posToArrayIndex(Alignment::BOTTOM | Alignment::RIGHT);

    if (textBlocks[idx].hasText()) {
        textBlocks[idx].layout(*fontMetrics);
        textBlocks[idx].getBounds(bbox, fontMetrics);
        textBlocks[idx].setPosition({ width - padding - bbox.getWidth(), height - padding - bbox.getHeight() });

        max_btm_tb_h = std::max(max_btm_tb_h, bbox.getHeight());
    }

    bbox.setBounds(padding, padding + max_top_tb_h, width - padding, height - padding - max_btm_tb_h);

    setViewportParameter(structView, bbox);
    
    layoutValid = true;
}

void Vis::StructureGridView2D::Cell::render(Renderer2D& renderer)
{
    layout();
    
    for (auto& tb : textBlocks)
        if (tb.hasText())
            tb.render(renderer);

    if (hasStructure())
        structView.render(renderer);
}

std::size_t Vis::StructureGridView2D::Cell::posToArrayIndex(unsigned int pos)
{
    std::size_t row = 0;
    std::size_t col = 0;
    
    switch (pos & Alignment::V_ALIGNMENT_MASK) {

        case Alignment::TOP:
            row = 0;
            break;

        case Alignment::V_CENTER:
            row = 1;
            break;

        case Alignment::BOTTOM:
            row = 2;
            break;

        default:
            throw Base::ValueError("StructureGridView2D::Cell: invalid vertical text block position");
    }

    switch (pos & Alignment::H_ALIGNMENT_MASK) {

        case Alignment::LEFT:
            col = 0;
            break;

        case Alignment::H_CENTER:
            col = 1;
            break;
            
        case Alignment::RIGHT:
            col = 2;
            break;

        default:
            throw Base::ValueError("StructureGridView2D::Cell: invalid vhorizontal text block position");
    }

    return (row * 3 + col);
}
