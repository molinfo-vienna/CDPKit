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

#include <boost/unordered_map.hpp>

#include "CDPL/Vis/APIPrefix.hpp"
#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/TextBlockPrimitive2D.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL
{

    namespace Vis
    {

        /**
         * \brief Implements the 2D visualization of multiple chemical structures arrange in a grid.
         *
         * \c %StructureGridView2D visualizes multiple chemical structures in the form of 2D structure diagrams 
         * arranged in a grid of arbitrary size.
         *
         * \c %StructureGridView2D relies on Vis::StructureView2D for structure visualization and thus support all 
         * all of its configuration parameters regarding the graphical details of the generated structure diagrams (colors, fonts,
         * line-widths etc.). Configuration can be performed on a grid cell level or for all cells at once using the
         * control-parameters supported by Vis::StructureView2D and on a visualized structure level
         * by setting appropriate Chem::Atom, Chem::Bond or Chem::MolecularGraph properties. Graphical properties of the
         * visualized structures always have a higher priority than equivalent control-parameters of individual grid cells.
         * Likewise, control-parameters specified for particular grid cells override the corresponding settings that were specified for
         * for the whole grid.
         *
         * \c %StructureGridView2D supports the following control-parameters in addition to the ones supported by Vis::StructureView2D:
         *
         * <table width="95%" bgcolor="#FAFAFA" border="1" align="center" rules="all" cellpadding="3">
         *  <tr bgcolor="#DDDDDD" align="center" valign="middle">
         *   <th>Control-Parameter</th> <th>Description</th>
         *  </tr>
         *  <tr>
         *   <td>TODO</td>
         *   <td>TODO TOO</td>
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
            static constexpr double DEF_CELL_WIDTH  = 150.0;
            static constexpr double DEF_CELL_HEIGHT = 150.0;
            
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %StructureGridView2D instances.
             */
            typedef std::shared_ptr<StructureGridView2D> SharedPointer;

            class CDPL_VIS_API Cell : public Base::ControlParameterContainer
            {

              public:
                /**
                 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %StructureGridView2D instances.
                 */
                typedef std::shared_ptr<Cell> SharedPointer;

                void setStructure(const Chem::MolecularGraph& molgraph);

                const Chem::MolecularGraph& getStructure() const;
                
                void clear(bool structure = true, bool text = true);

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

                StructureView2D      structView;
                TextBlockPrimitive2D textBlocks[3][3];
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
             * \brief Destructor.
             */
            ~StructureGridView2D();

            void render(Renderer2D& renderer);

            void setFontMetrics(FontMetrics* font_metrics);

            /**
             * \brief Returns a pointer to the used font metrics object.
             * \return A pointer to the used font metrics object, or \e null if none was specified.
             */
            FontMetrics* getFontMetrics() const;

            void getModelBounds(Rectangle2D& bounds);

            Cell& operator()(std::size_t row, std::size_t col);

            const Cell& operator()(std::size_t row, std::size_t col) const;

            void setCellSize(double width, double height);

            double getCellWidth() const;

            double getCellHeight() const;
            
            void resize(std::size_t num_rows, std::size_t num_cols);

            std::size_t getNumRows() const;

            std::size_t getNumColumns() const;

            void clear(bool resize = true, bool structure = true, bool text = true);
            
          private:
            typedef Util::ObjectPool<Cell>         CellCache;
            typedef CellCache::SharedObjectPointer CellPointer;

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
