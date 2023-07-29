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
# \brief AutoCorrelation2DVectorCalculator.
# 
# \see [\ref AUCOR, \ref HBMD]
# 
class AutoCorrelation2DVectorCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>AutoCorrelation2DVectorCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AutoCorrelation2DVectorCalculator instance.
    # \param calc 
    # 
    def __init__(calc: AutoCorrelation2DVectorCalculator) -> None: pass

    ##
    # \brief Constructs the <tt>AutoCorrelation2DVectorCalculator</tt> instance and calculates the autocorrelation vector of the molecular graph <em>molgraph</em>.
    # 
    # The calculated autocorrelation vector can be retrieved by a call to getResult().
    # 
    # \param molgraph The molecular graph for which to calculate the autocorrelation vector.
    # \param corr_vec The calculated autocorrelation vector.
    # 
    def __init__(molgraph: Chem.MolecularGraph, corr_vec: Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %AutoCorrelation2DVectorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AutoCorrelation2DVectorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AutoCorrelation2DVectorCalculator instance \a calc.
    # \param calc The \e %AutoCorrelation2DVectorCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: AutoCorrelation2DVectorCalculator) -> AutoCorrelation2DVectorCalculator: pass

    ##
    # \brief Allows to specify that maximum bond path length to consider.
    # 
    # \param max_dist The maximum considered bond path length.
    # 
    # \note The default value is <em>0</em> which signals no path length limit.
    # 
    def setMaxDistance(max_dist: int) -> None: pass

    ##
    # \brief Returns the maximum considered bond path length.
    # 
    # \return The maximum considered bond path length.
    # 
    def getMaxDistance() -> int: pass

    ##
    # \brief Allows to specify a custom atom pair weight function.
    # 
    # \param func An AutoCorrelation2DVectorCalculator.AtomPairWeightFunction instance that wraps the target function.
    # 
    # \note The default atom pair weight function returns the product of the atom types (see namespace Chem.AtomType).
    # 
    def setAtomPairWeightFunction(func: Chem.DoubleAtom2Functor) -> None: pass

    ##
    # \brief Calculates the topological autocorrelation vector of the molecular graph <em>molgraph</em>.
    # 
    # The elements of the calculated vector provide the sum of the weights of all atom pairs with a topological distance equal to the element index. The size of the vector is limited by the topological diameter of the molecular graph or the specified maximum considered bond path length (\see setMaxDistance()).
    # 
    # \param molgraph The molecular graph for which to calculate the autocorrelation vector.
    # \param corr_vec The calculated autocorrelation vector.
    # 
    def calculate(molgraph: Chem.MolecularGraph, corr_vec: Math.DVector) -> None: pass

    objectID = property(getObjectID)

    maxDistance = property(getMaxDistance, setMaxDistance)
