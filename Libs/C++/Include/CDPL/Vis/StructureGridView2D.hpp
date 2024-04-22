/* 
 * StructureGridView2D.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Vis::StructureGridView2D.
 */

#ifndef CDPL_VIS_STRUCTUREGRIDVIEW2D_HPP
#define CDPL_VIS_STRUCTUREGRIDVIEW2D_HPP

#include <memory>
#include <utility>
#include <cstddef>
#include <iosfwd>
#include <iterator>

#include <boost/unordered_map.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/TextBlockPrimitive2D.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataFormat;
    }
    
    namespace Vis
    {

        /**
         * \brief Implements the 2D visualization of multiple chemical structures arrange in a grid.
         *
         * \c %StructureGridView2D visualizes multiple chemical structures as 2D structure diagrams 
         * arranged in a grid of arbitrary size.
         *
         * \c %StructureGridView2D relies on Vis::StructureView2D for structure visualization and thus supports all 
         * all of its parameters controlling the graphical details of the generated structure diagrams (colors, fonts,
         * line-widths etc.). Structure visualization parameters of a \c %StructureGridView2D instance can be set for individual grid
         * cells as well as for the whole grid. Furthermore, any Chem::Atom, Chem::Bond and Chem::MolecularGraph relevant for 2D visualization
         * properties will also be regarded (see Vis::StructureView2D for the list of supported properties).
         * Properties of the visualized structures have a higher priority than the corresponding control-parameters of
         * the grid cells hosting the structures.
         * Likewise, control-parameters set for individual grid cells override the corresponding settings of the \c %StructureGridView2D instance.
         *
         * Each grid cell can host up to nine text blocks which are located at the corners, edges and the cell center. Text blocks are stored
         * as Vis::TextBlockPrimitive2D instances which allow the text to span multiple lines and support the styling (colors, italic, bold, sub/super-scripting, etc.)
         * of individual text fragments.
         *
         * \c %StructureGridView2D supports the following control-parameters in addition to the ones regarded by Vis::StructureView2D:
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Control-Parameter</th> <th>Description</th>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::OUTPUT_SCALING_FACTOR</td>
         *   <td>Specifies a factor for the scaling of logical to drawing surface coordinates</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_BORDER_PEN</td>
         *   <td>Specifies the pen used for drawing a rectangle enclosing all cells of the grid</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_ROW_SEPARATOR_PEN</td>
         *   <td>Specifies the pen used for drawing lines separating the grid rows</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_COLUMN_SEPARATOR_PEN</td>
         *   <td>Specifies the pen used for drawing lines separating the grid columns</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_MARGIN</td>
         *   <td>Specifies the amount of free space added around the grid borderline</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_CELL_PADDING</td>
         *   <td>Specifies the amount of free space added around the content of the grid cells</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_TEXT_FONT</td>
         *   <td>Specifies the font used for text blocks</td>
         *  </tr>
         *  <tr>
         *   <td>Vis::ControlParameter::GRID_VIEW_TEXT_COLOR</td>
         *   <td>Specifies the default text color</td>
         *  </tr>
         * </table>
         *
         * Default values for most of the control-parameters are defined in namespace Vis::ControlParameterDefault.
         *
         * \since 1.2
         */
        class CDPL_VIS_API StructureGridView2D : public View2D
        {

          public:
            /** 
             * \brief The default grid cell width.
             */ 
            static constexpr double DEF_CELL_WIDTH  = 250.0;

            /** 
             * \brief The default grid cell height.
             */ 
            static constexpr double DEF_CELL_HEIGHT = 250.0;
            
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %StructureGridView2D instances.
             */
            typedef std::shared_ptr<StructureGridView2D> SharedPointer;

            /**
             * \brief Data structure storing the contents of a grid cell.
             */
            class CDPL_VIS_API Cell : public Base::ControlParameterContainer
            {

              public:
                /**
                 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Cell instances.
                 */
                typedef std::shared_ptr<Cell> SharedPointer;

                /** 
                 * \brief The default position of text blocks.
                 */ 
                static constexpr unsigned int DEF_TEXT_POSITION = Alignment::BOTTOM | Alignment::H_CENTER;
                
                Cell(const Cell&) = delete;

                /**
                 * \brief Specifies the molecular structure that shall be displayed in this cell.
                 *
                 * The cell will store a deep copy of the specified Chem::MolecularGraph instance which can then be safely
                 * modified or destroyed after the method call.
                 *
                 * \param molgraph A Chem::MolecularGraph instance specifying the molecular structure to display.
                 */
                void setStructure(const Chem::MolecularGraph& molgraph);

                /**
                 * \brief Returns the stored data of the currently displayed molecular structure (if any).
                 * \param A reference to the stored Chem::MolecularGraph instance.
                 */
                const Chem::MolecularGraph& getStructure() const;

                /**
                 * \brief Hides the dcurrently displayed molecular structure (if any) and clears the stored data.
                 */
                void clearStructure();

                /**
                 * \brief Tells whether this cell displays a molecular structure.
                 * \return \c true if a molecular structure is shown and \c false otherwise.
                 */
                bool hasStructure() const;

                /**
                 * \brief Specifies the text that shall be displayed at the given position.
                 *
                 * The position \a pos of the text block is specified as a combination of horizontal and vertical alignment flags defined in
                 * namespace Vis::Alignment. If the text spans multiple lines, the horizontal alignment of the lines within the text block can be controlled by
                 * specifying horizontal algnment flags via the \a line_almnt argument. By default, lines of text blocks located on the left side
                 * of the cell will be left-aligned, horizontal center positioned text blocks have the lines center-aligned and text blocks on the
                 * right side have the lines right-aligned.
                 *
                 * \param text The text to display.
                 * \param pos The position of the text block within this cell.
                 * \param line_almnt The horizontal alignment of the lines within the text block.
                 */
                void setText(const std::string& text, unsigned int pos = DEF_TEXT_POSITION,
                             unsigned int line_almnt = Alignment::NONE);

                /**
                 * \brief Returns the text displayed at the specified position.
                 * \param pos The position of the text block (see setText()).
                 * \return A reference to the string storing the displayed text.
                 */
                const std::string& getText(unsigned int pos = DEF_TEXT_POSITION) const;

                /**
                 * \brief Clears the text displayed at the specified position.
                 * \param pos The position of the text block (see setText()).
                 */
                void clearText(unsigned int pos = DEF_TEXT_POSITION);

                /**
                 * \brief Tells whether any text is displayed at the specified position.
                 * \param pos The position of the text block (see setText()).
                 */
                bool hasText(unsigned int pos = DEF_TEXT_POSITION) const;

                /**
                 * \brief Clears all text blocks.
                 */
                void clearAllText();

                /**
                 * \brief Tells whether this cell displays any text.
                 * \return \c true if any text is shown and \c false otherwise.
                 */
                bool hasAnyText() const;

                /**
                 * \brief Performs a copy assignment of the specified \c %Cell instance.
                 * \param cell The \c %Cell instance to copy.
                 * \return A reference to itslef.
                 */
                Cell& operator=(const Cell& cell);
                
              private:
                friend class StructureGridView2D;
                
                Cell();
                ~Cell();
                
                void setFontMetrics(FontMetrics* font_metrics);

                void setSize(double width, double height);
                
                void parameterChanged(const Base::LookupKey& key, const Base::Any& value);
                void parameterRemoved(const Base::LookupKey& key);
                void parentChanged();
                
                void layout();
                void render(Renderer2D& renderer);

                static std::size_t posToArrayIndex(unsigned int pos);
                    
                StructureView2D      structView;
                TextBlockPrimitive2D textBlocks[9];
                Chem::BasicMolecule  molecule;
                FontMetrics*         fontMetrics;
                double               width;
                double               height;
                bool                 layoutValid;
            };
            
            /**
             * \brief Constructs and initializes a \c %StructureGridView2D instance for the visualization of multiple chemical
             *        structures.
             */
            StructureGridView2D();

            /**
             * \brief Constructs a copy of the \c %StructureGridView2D instance \a grid_view.
             * \param grid_view The \c %StructureGridView2D instance to copy;
             */
            StructureGridView2D(const StructureGridView2D& grid_view);
            
            /**
             * \brief Destructor.
             */
            ~StructureGridView2D();

            void render(Renderer2D& renderer);

#ifdef HAVE_CAIRO

            /**
             * \brief Renders the grid with the specified cell contents and stores the generated image in the file \a file_name.
             *
             * The output format will be deduced from the file name extension. Supported formats are \e PNG, \e SVG, \e PDF and \e PS.
             *
             * \param file_name The path to the file storing the rendered image.
             * \return \c true if no errors occurred and \c false otherwise.
             * \throw Base::IOError if the file format is invalid/not supported.
             */
            bool write(const std::string& file_name);

            /**
             * \brief Renders the grid with the specified cell contents and stores the generated image in the file \a file_name.
             *
             * The output format is specified by the second argument \a fmt. Supported formats are \c "PNG", \c "SVG", \c "PDF" and \c "PS"
             * (not case sensitive).
             *
             * \param file_name The path to the file storing the rendered image.
             * \param fmt A string specifying the desired output format.
             * \return \c true if no errors occurred and \c false otherwise.
             * \throw Base::IOError if the file format is invalid/not supported.
             */
            bool write(const std::string& file_name, const std::string& fmt);

            /**
             * \brief Renders the grid with the specified cell contents and stores the generated image in the file \a file_name.
             *
             * The output format is specified by the second argument \a fmt. Supported formats are Vis::DataFormat::PNG, Vis::DataFormat::SVG, 
             * Vis::DataFormat::PDF and Vis::DataFormat::PS.
             *
             * \param file_name The path to the file storing the rendered image.
             * \param fmt A descriptor specifying the desired output format.
             * \return \c true if no errors occurred and \c false otherwise.
             * \throw Base::IOError if the file format is invalid/not supported.
             */
            bool write(const std::string& file_name, const Base::DataFormat& fmt);

            /**
             * \brief Renders the grid with the specified cell contents and writes the generated image data to the output stream \a os.
             *
             * The output format is specified by the second argument \a fmt. Supported formats are \c "PNG", \c "SVG", \c "PDF" and \c "PS" 
             * (not case sensitive).
             *
             * \param os A \c %std::ostream instance storing the generated image data.
             * \param fmt A string specifying the desired output format.
             * \return \c true if no errors occurred and \c false otherwise.
             * \throw Base::IOError if the file format is invalid/not supported.
             */
            bool write(std::ostream& os, const std::string& fmt);

            /**
             * \brief Renders the grid with the specified cell contents and writes the generated image data to the output stream \a os.
             *
             * The output format is specified by the second argument \a fmt. Supported formats are Vis::DataFormat::PNG, Vis::DataFormat::SVG, 
             * Vis::DataFormat::PDF and Vis::DataFormat::PS. 
             *
             * \param os A \c %std::ostream instance storing the generated image data.
             * \param fmt A string specifying the desired output format.
             * \return \c true if no errors occurred and \c false otherwise.
             * \throw Base::IOError if the file format is invalid/not supported.
             */
            bool write(std::ostream& os, const Base::DataFormat& fmt);

#endif // HAVE_CAIRO
            
            void setFontMetrics(FontMetrics* font_metrics);

            /**
             * \brief Returns a pointer to the used font metrics object.
             * \return A pointer to the used font metrics object, or \e null if none was specified.
             */
            FontMetrics* getFontMetrics() const;

            void getModelBounds(Rectangle2D& bounds);

            /**
             * \brief Returns the Cell instance storing the contents of the specified grid cell.
             *
             * If \a row and \a col specify a cell outside of the current grid bounds the grid will be
             * automatically resized to accommodate the new cell.
             *
             * \param row The zero-based row index of the cell.
             * \param col The zero-based columns index of the cell.
             * \return A non-\c const reference to the Cell instance.
             */
            Cell& operator()(std::size_t row, std::size_t col);

            /**
             * \brief Returns the Cell instance storing the contents of the specified grid cell.
             *
             * If \a row and \a col specify a cell outside of the current grid bounds the grid will \e not be
             * automatically resized to accommodate the new cell. For such cells a reference to an "empty" Cell instance 
             * is returned. The same is done for not yet touched cells (within the current grid bounds).
             *
             * \param row The zero-based row index of the cell.
             * \param col The zero-based columns index of the cell.
             * \return A \c const reference to the Cell instance.
             */
            const Cell& operator()(std::size_t row, std::size_t col) const;

            /**
             * \brief Allows to specify the desired width and height of the cells in grid output renderings.
             *
             * The default width and height is given by the constants DEF_CELL_WIDTH and DEF_CELL_HEIGHT, respectively.
             *
             * \param width The new cell width.
             * \param height The new cell height.
             * \throw Base::ValueError if either \a width or \a height is negative.
             */
            void setCellSize(double width, double height);

            /**
             * \brief Returns the active grid cell width.
             * \return The active grid cell width.
             */
            double getCellWidth() const;

            /**
             * \brief Returns the active grid cell height.
             * \return The active grid cell height.
             */
            double getCellHeight() const;

            /**
             * \brief Chnages the current number of grid rows and columns.
             *
             * The grid gets resized dynamically if a cell outside the currently sized grid is requested by operator(). Calling
             * this method is thus only necessary if a specific grid size is desired. Any already existing
             * cells that are located outside the new grid dimensions will be deleted.
             *
             * \param num_rows The new numer of grid rows.
             * \param num_cols The new numer of grid columns.
             */
            void resize(std::size_t num_rows, std::size_t num_cols);

            /**
             * \brief Returns the current number of grid rows.
             * \return The current number of grid rows.
             */
            std::size_t getNumRows() const;

            /**
             * \brief Returns the current number of grid columns.
             * \return The current number of grid columns.
             */
            std::size_t getNumColumns() const;

            /**
             * \brief Clears all specified structures.
             * \see Cell::clearStructure()
             */
            void clearStructures();

            /**
             * \brief Clears all specified text blocks.
             * \see Cell::clearAllText()
             */
            void clearAllText();

            /**
             * \brief Performs a copy assignment of the specified \c %StructureGridView2D instance.
             * \param grid_view The \c %StructureGridView2D instance to copy.
             * \return A reference to itslef.
             */
            StructureGridView2D& operator=(const StructureGridView2D& grid_view);
            
          private:
            typedef Util::ObjectPool<Cell>         CellCache;
            typedef CellCache::SharedObjectPointer CellPointer;

            void copy(const StructureGridView2D& grid_view);

            void getGridPosition(Math::Vector2D& pos);
            
            CellPointer allocCell();
                
            static Cell* newCell();
            static void deleteCell(Cell* cell);
            static void cleanupCell(Cell& cell);

            typedef std::pair<std::size_t, std::size_t>               CellID;
            typedef boost::unordered_map<CellID, Cell::SharedPointer> CellMap;

            CellCache    cellCache;
            FontMetrics* fontMetrics;
            CellMap      cells;
            double       cellWidth;
            double       cellHeight;
            std::size_t  numRows;
            std::size_t  numColumns;
        };
    } // namespace Vis
} // namespace CDPL

#endif // CDPL_VIS_STRUCTUREGRIDVIEW2D_HPP
