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
# \brief BCUTDescriptorCalculator.
# 
# \see [\ref BCUT]
# 
class BCUTDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>BCUTDescriptorCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>BCUTDescriptorCalculator</tt> instance and calculates the <em>BCUT</em> descriptor of the molecular graph <em>molgraph</em>.
    # 
    # The calculated descriptor can be retrieved by a call to getResult().
    # 
    # \param molgraph The molecular graph for which to calculate the <em>BCUT</em> descriptor.
    # \param descr The calculated <em>BCUT</em> descriptor.
    # 
    def __init__(molgraph: Chem.MolecularGraph, descr: Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %BCUTDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BCUTDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify a custom atom weight function for the initialization of the underlying <em>Burden</em> matrix [\ref BURMA].
    # 
    # \param func A BCUTDescriptorCalculator.AtomWeightFunction instance that wraps the target function.
    # 
    # \see Descr.BurdenMatrixGenerator.setAtomWeightFunction()
    # 
    def setAtomWeightFunction(func: ForceField.MMFF94AtomChargeFunction) -> None: pass

    ##
    # \brief Calculates the <em>BCUT</em> descriptor of the molecular graph <em>molgraph</em>.
    # 
    # The calculated <em>BCUT</em> descriptor is a vector that contains the calculated eigenvalues of the underlying <em>Burden</em> matrix [\ref BURMA]. The elements of the vector are sorted in ascending order. Note that explicit hydrogen atoms are included in the calculation of the <em>BCUT</em> descriptor. In order to calculate the descriptor for a hydrogen depleted molecular graph, any hydrogen atoms have to be removed from the molecular graph <em>before</em> the calculation is performed.
    # 
    # \param molgraph The molecular graph for which to calculate the <em>BCUT</em> descriptor.
    # \param descr The calculated <em>BCUT</em> descriptor.
    # 
    def calculate(molgraph: Chem.MolecularGraph, descr: Math.DVector) -> None: pass

    objectID = property(getObjectID)
