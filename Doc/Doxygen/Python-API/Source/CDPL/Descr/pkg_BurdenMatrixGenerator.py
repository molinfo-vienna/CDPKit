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
# \brief BurdenMatrixGenerator.
# 
# \see [\ref BURMA]
# 
class BurdenMatrixGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>BurdenMatrixGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>BCUTDescriptorGenerator</tt> instance and generates the <em>Burden</em> matrix of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the <em>Burden</em> matrix.
    # \param mtx The generated <em>Burden</em> matrix of the specified molecular graph.
    # 
    def __init__(molgraph: CDPL.Chem.MolecularGraph, mtx: CDPL.Math.DMatrix) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BurdenMatrixGenerator instance this method is called upon.
    # 
    # Different Python \e %BurdenMatrixGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BurdenMatrixGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify a custom atom weight function for the diagonal elements of the <em>Burden</em> matrix.
    # 
    # \param func A BurdenMatrixGenerator.AtomWeightFunction instance that wraps the target function.
    # 
    # \note By default, the diagonal elements of the <em>Burden</em> matrix are atom types (see namespace Chem.AtomType).
    # 
    def setAtomWeightFunction(func: CDPL.ForceField.MMFF94AtomChargeFunction) -> None: pass

    ##
    # \brief Generates the <em>Burden</em> matrix of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the <em>Burden</em> matrix.
    # \param mtx The generated <em>Burden</em> matrix of the specified molecular graph.
    # 
    def generate(molgraph: CDPL.Chem.MolecularGraph, mtx: CDPL.Math.DMatrix) -> None: pass

    objectID = property(getObjectID)
