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
# \brief 
#
class GRAILDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    TOTAL_DESCRIPTOR_SIZE = 101

    ##
    # \brief 
    #
    LIGAND_DESCRIPTOR_SIZE = 28

    ##
    # \brief Initializes the \e %GRAILDescriptorCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GRAILDescriptorCalculator instance.
    # \param calc 
    #
    def __init__(calc: GRAILDescriptorCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %GRAILDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GRAILDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GRAILDescriptorCalculator instance \a calc.
    # \param calc The \e %GRAILDescriptorCalculator instance to copy.
    # \return \a self
    #
    def assign(calc: GRAILDescriptorCalculator) -> GRAILDescriptorCalculator: pass

    ##
    # \brief 
    # \param tgt_env 
    # \param coords_func 
    # \param tgt_env_changed 
    #
    def initTargetData(tgt_env: CDPL.Chem.MolecularGraph, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, tgt_env_changed: bool = True) -> None: pass

    ##
    # \brief 
    # \param ligand 
    #
    def initLigandData(ligand: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
