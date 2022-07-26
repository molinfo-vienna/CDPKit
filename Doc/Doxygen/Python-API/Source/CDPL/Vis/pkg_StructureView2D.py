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
    # \param self The \e %StructureView2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %StructureView2D instance.
    # \param self The \e %StructureView2D instance to initialize.
    # \param molgraph 
    #
    def __init__(self: object, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    # \param molgraph 
    #
    def setStructure(self: StructureView2D, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    # \return 
    #
    def getStructure(self: StructureView2D) -> CDPL.Chem.MolecularGraph: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    # \return 
    #
    def getFontMetrics(self: StructureView2D) -> FontMetrics: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    # \param anchor_pos 
    # \param prim 
    # \param alignment 
    # \param front 
    #
    def addGraphicsPrimitive(self: StructureView2D, anchor_pos: CDPL.Math.Vector2D, prim: GraphicsPrimitive2D, alignment: int, front: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    # \param anchor_atom 
    # \param prim 
    # \param alignment 
    # \param front 
    #
    def addGraphicsPrimitive(self: StructureView2D, anchor_atom: CDPL.Chem.Atom, prim: GraphicsPrimitive2D, alignment: int, front: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    # \param anchor_atoms 
    # \param prim 
    # \param alignment 
    # \param front 
    #
    def addGraphicsPrimitive(self: StructureView2D, anchor_atoms: CDPL.Chem.Fragment, prim: GraphicsPrimitive2D, alignment: int, front: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureView2D instance this method is called upon.
    #
    def clearGraphicsPrimitives(self: StructureView2D) -> None: pass

    ##
    # \brief 
    #
    structure = property(getStructure, setStructure)

    ##
    # \brief 
    #
    fontMetrics = property(getFontMetrics, setFontMetrics)
