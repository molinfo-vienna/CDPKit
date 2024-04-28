#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief Implements the 2D visualization of multiple chemical structures arrange in a grid.
# 
# <tt>StructureGridView2D</tt> visualizes multiple chemical structures as 2D structure diagrams arranged in a grid of arbitrary size.
# 
# <tt>StructureGridView2D</tt> relies on Vis.StructureView2D for structure visualization and thus supports all all of its parameters controlling the graphical details of the generated structure diagrams (colors, fonts, line-widths etc.). Structure visualization parameters of a <tt>StructureGridView2D</tt> instance can be set for individual grid cells as well as for the whole grid. Furthermore, any Chem.Atom, Chem.Bond and Chem.MolecularGraph relevant for 2D visualization properties will also be regarded (see Vis.StructureView2D for the list of supported properties). Properties of the visualized structures have a higher priority than the corresponding control-parameters of the grid cells hosting the structures. Likewise, control-parameters set for individual grid cells override the corresponding settings of the <tt>StructureGridView2D</tt> instance.
# 
# Each grid cell can host up to nine text blocks which are located at the corners, edges and the cell center. Text blocks are stored as Vis.TextBlockPrimitive2D instances which allow the text to span multiple lines and support the styling (colors, italic, bold, sub/super-scripting, etc.) of individual text fragments.
# 
# <tt>StructureGridView2D</tt> supports the following control-parameters in addition to the ones regarded by Vis.StructureView2D:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Description</th></tr>
#  <tr><td>Vis.ControlParameter.OUTPUT_SCALING_FACTOR</td><td>Specifies a factor for the scaling of logical to drawing surface coordinates</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_BORDER_PEN</td><td>Specifies the pen used for drawing a rectangle enclosing all cells of the grid</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_ROW_SEPARATOR_PEN</td><td>Specifies the pen used for drawing lines separating the grid rows</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_COLUMN_SEPARATOR_PEN</td><td>Specifies the pen used for drawing lines separating the grid columns</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_MARGIN</td><td>Specifies the amount of free space added around the grid borderline</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_CELL_PADDING</td><td>Specifies the amount of free space added around the content of the grid cells</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_TEXT_FONT</td><td>Specifies the font used for text blocks</td></tr>
#  <tr><td>Vis.ControlParameter.GRID_VIEW_TEXT_COLOR</td><td>Specifies the default text color</td></tr>
# </table>
# 
# Default values for most of the control-parameters are defined in namespace Vis.ControlParameterDefault.
# 
# \since 1.2
# 
class StructureGridView2D(View2D):

    ##
    # \brief Data structure storing the contents of a grid cell.
    # 
    class Cell(Boost.Python.instance):

        ##
        # \brief The default position of text blocks.
        # 
        DEF_TEXT_POSITION = 11

        ##
        # \brief Specifies the molecular structure that shall be displayed in this cell.
        # 
        # The cell will store a deep copy of the specified Chem.MolecularGraph instance which can then be safely modified or destroyed after the method call.
        # 
        # \param molgraph A Chem.MolecularGraph instance specifying the molecular structure to display.
        # 
        def setStructure(molgraph: Chem.MolecularGraph) -> None: pass

        ##
        # \brief Returns the stored data of the currently displayed molecular structure (if any).
        # 
        # \param A reference to the stored Chem.MolecularGraph instance.
        # 
        def getStructure() -> Chem.MolecularGraph: pass

        ##
        # \brief Hides the dcurrently displayed molecular structure (if any) and clears the stored data.
        # 
        def clearStructure() -> None: pass

        ##
        # \brief 
        # \return 
        #
        def hashStructure() -> bool: pass

        ##
        # \brief Returns the text displayed at the specified position.
        # 
        # \param pos The position of the text block (see setText()).
        # 
        # \return A reference to the string storing the displayed text.
        # 
        def getText(pos: int = 11) -> object: pass

        ##
        # \brief Clears the text displayed at the specified position.
        # 
        # \param pos The position of the text block (see setText()).
        # 
        def clearText(pos: int = 11) -> None: pass

        ##
        # \brief Clears all text blocks.
        # 
        def clearAllText() -> None: pass

        ##
        # \brief Tells whether this cell displays any text.
        # 
        # \return <tt>True</tt> if any text is shown and <tt>False</tt> otherwise.
        # 
        def hasAnyText() -> bool: pass

        ##
        # \brief Tells whether any text is displayed at the specified position.
        # 
        # \param pos The position of the text block (see setText()).
        # 
        def hasText(pos: int) -> bool: pass

        ##
        # \brief Performs a copy assignment of the specified <tt>Cell</tt> instance.
        # 
        # \param cell The <tt>Cell</tt> instance to copy.
        # 
        # \return A reference to itslef.
        # 
        def assign(cell: Cell) -> Cell: pass

        structure = property(getStructure, setStructure)

    ##
    # \brief The default grid cell width.
    # 
    DEF_CELL_WIDTH = 250.0

    ##
    # \brief The default grid cell height.
    # 
    DEF_CELL_HEIGHT = 250.0

    ##
    # \brief Constructs and initializes a <tt>StructureGridView2D</tt> instance for the visualization of multiple chemical structures.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>StructureGridView2D</tt> instance <em>grid_view</em>.
    # 
    # \param grid_view The <tt>StructureGridView2D</tt> instance to copy;
    # 
    def __init__(grid_view: StructureGridView2D) -> None: pass

    ##
    # \brief 
    # \param file_name 
    # \return 
    #
    def write(file_name: str) -> bool: pass

    ##
    # \brief 
    # \param file_name 
    # \param fmt 
    # \return 
    #
    def write(file_name: str, fmt: str) -> bool: pass

    ##
    # \brief 
    # \param file_name 
    # \param fmt 
    # \return 
    #
    def write(file_name: str, fmt: Base.DataFormat) -> bool: pass

    ##
    # \brief 
    # \param os 
    # \param fmt 
    # \return 
    #
    def write(os: Base.OStream, fmt: str) -> bool: pass

    ##
    # \brief 
    # \param os 
    # \param fmt 
    # \return 
    #
    def write(os: Base.OStream, fmt: Base.DataFormat) -> bool: pass

    ##
    # \brief Returns a reference to the used font metrics object.
    # 
    # \return A reference to the used font metrics object, or <em>None</em> if none was specified.
    # 
    def getFontMetrics() -> FontMetrics: pass

    ##
    # \brief Allows to specify the desired width and height of the cells in grid output renderings.
    # 
    # The default width and height is given by the constants DEF_CELL_WIDTH and DEF_CELL_HEIGHT, respectively.
    # 
    # \param width The new cell width.
    # \param height The new cell height.
    # 
    # \throw Base.ValueError if either <em>width</em> or <em>height</em> is negative.
    # 
    def setCellSize(width: float, height: float) -> None: pass

    ##
    # \brief Returns the active grid cell width.
    # 
    # \return The active grid cell width.
    # 
    def getCellWidth() -> float: pass

    ##
    # \brief Returns the active grid cell height.
    # 
    # \return The active grid cell height.
    # 
    def getCellHeight() -> float: pass

    ##
    # \brief Chnages the current number of grid rows and columns.
    # 
    # The grid gets resized dynamically if a cell outside the currently sized grid is requested by __call__. Calling this method is thus only necessary if a specific grid size is desired. Any already existing cells that are located outside the new grid dimensions will be deleted.
    # 
    # \param num_rows The new numer of grid rows.
    # \param num_cols The new numer of grid columns.
    # 
    def resize(num_rows: int, num_cols: int) -> None: pass

    ##
    # \brief Returns the current number of grid rows.
    # 
    # \return The current number of grid rows.
    # 
    def getNumRows() -> int: pass

    ##
    # \brief Returns the current number of grid columns.
    # 
    # \return The current number of grid columns.
    # 
    def getNumColumns() -> int: pass

    ##
    # \brief Clears all specified structures.
    # 
    # \see Cell.clearStructure()
    # 
    def clearStructures() -> None: pass

    ##
    # \brief Clears all specified text blocks.
    # 
    # \see Cell.clearAllText()
    # 
    def clearAllText() -> None: pass

    ##
    # \brief Performs a copy assignment of the specified <tt>StructureGridView2D</tt> instance.
    # 
    # \param grid_view The <tt>StructureGridView2D</tt> instance to copy.
    # 
    # \return A reference to itslef.
    # 
    def assign(grid_view: StructureGridView2D) -> StructureGridView2D: pass

    ##
    # \brief Returns the Cell instance storing the contents of the specified grid cell.
    # 
    # If <em>row</em> and <em>col</em> specify a cell outside of the current grid bounds the grid will <em>not</em> be automatically resized to accommodate the new cell. For such cells a reference to an "empty" Cell instance is returned. The same is done for not yet touched cells (within the current grid bounds).
    # 
    # \param row The zero-based row index of the cell.
    # \param col The zero-based columns index of the cell.
    # 
    # \return A reference to the Cell instance.
    # 
    def __call__(row: int, col: int) -> Cell: pass

    ##
    # \brief 
    # \param row_and_col 
    # \return 
    #
    def __getitem__(row_and_col: tuple) -> Cell: pass

    cellWidth = property(getCellWidth)

    cellHeight = property(getCellHeight)

    numRows = property(getNumRows)

    numColumns = property(getNumColumns)

    fontMetrics = property(getFontMetrics, setFontMetrics)
