#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class StructureView2D(View2D):

    ##
    # \brief Initializes the \e %StructureView2D instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %StructureView2D instance.
    # \param molgraph 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def setStructure(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStructure() -> CDPL.Chem.MolecularGraph: pass

    ##
    # \brief 
    # \return 
    #
    def getFontMetrics() -> FontMetrics: pass

    ##
    # \brief 
    # \param anchor_pos 
    # \param prim 
    # \param alignment 
    # \param front 
    #
    def addGraphicsPrimitive(anchor_pos: CDPL.Math.Vector2D, prim: GraphicsPrimitive2D, alignment: int, front: bool) -> None: pass

    ##
    # \brief 
    # \param anchor_atom 
    # \param prim 
    # \param alignment 
    # \param front 
    #
    def addGraphicsPrimitive(anchor_atom: CDPL.Chem.Atom, prim: GraphicsPrimitive2D, alignment: int, front: bool) -> None: pass

    ##
    # \brief 
    # \param anchor_atoms 
    # \param prim 
    # \param alignment 
    # \param front 
    #
    def addGraphicsPrimitive(anchor_atoms: CDPL.Chem.Fragment, prim: GraphicsPrimitive2D, alignment: int, front: bool) -> None: pass

    ##
    # \brief 
    #
    def clearGraphicsPrimitives() -> None: pass

    ##
    # \brief 
    #
    structure = property(getStructure, setStructure)

    ##
    # \brief 
    #
    fontMetrics = property(getFontMetrics, setFontMetrics)