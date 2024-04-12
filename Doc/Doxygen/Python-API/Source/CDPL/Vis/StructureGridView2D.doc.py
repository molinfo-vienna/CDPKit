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
# <tt>StructureGridView2D</tt> visualizes multiple chemical structures in the form of 2D structure diagrams arranged in a grid of arbitrary size.
# 
# <tt>StructureGridView2D</tt> relies on Vis.StructureView2D for structure visualization and thus support all all of its configuration parameters regarding the graphical details of the generated structure diagrams (colors, fonts, line-widths etc.). Configuration can be performed on a grid cell level or for all cells at once using the control-parameters supported by Vis.StructureView2D and on a visualized structure level by setting appropriate Chem.Atom, Chem.Bond or Chem.MolecularGraph properties. Graphical properties of the visualized structures always have a higher priority than equivalent control-parameters of individual grid cells. Likewise, control-parameters specified for particular grid cells override the corresponding settings that were specified for for the whole grid.
# 
# <tt>StructureGridView2D</tt> supports the following control-parameters in addition to the ones supported by Vis.StructureView2D:
# 
# <table>
#  <tr><th>Control-Parameter</th><th>Description</th></tr>
#  <tr><td>TODO</td><td>TODO TOO</td></tr>
# </table>
# 
# Default values for most of the control-parameters are defined in namespace Vis.ControlParameterDefault.
# 
# \since 1.2
# 
class StructureGridView2D(View2D):

    ##
    # \brief 
    #
    class Cell(Boost.Python.instance):

        ##
        # \brief 
        # \param molgraph 
        #
        def setStructure(molgraph: Chem.MolecularGraph) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getStructure() -> Chem.MolecularGraph: pass

        ##
        # \brief 
        #
        def clearStructure() -> None: pass

        ##
        # \brief 
        # \return 
        #
        def hashStructure() -> bool: pass

        ##
        # \brief 
        # \param pos 
        # \return 
        #
        def getText(pos: int) -> object: pass

        ##
        # \brief 
        # \param pos 
        #
        def clearText(pos: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def hasText() -> bool: pass

        ##
        # \brief 
        # \param pos 
        # \return 
        #
        def hasText(pos: int) -> bool: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Cell instance \a cell.
        # \param cell The \e %Cell instance to copy.
        # \return \a self
        # 
        def assign(cell: Cell) -> Cell: pass

        structure = property(getStructure, setStructure)

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
    # \brief 
    # \param width 
    # \param height 
    #
    def setCellSize(width: float, height: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCellWidth() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getCellHeight() -> float: pass

    ##
    # \brief 
    # \param num_rows 
    # \param num_cols 
    #
    def resize(num_rows: int, num_cols: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumRows() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumColumns() -> int: pass

    ##
    # \brief 
    #
    def clearStructures() -> None: pass

    ##
    # \brief 
    #
    def clearTextBlocks() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %StructureGridView2D instance \a grid_view.
    # \param grid_view The \e %StructureGridView2D instance to copy.
    # \return \a self
    # 
    def assign(grid_view: StructureGridView2D) -> StructureGridView2D: pass

    ##
    # \brief 
    # \param row 
    # \param col 
    # \return 
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
