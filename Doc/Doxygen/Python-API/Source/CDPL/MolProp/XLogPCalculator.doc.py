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
# \brief XLogPCalculator.
# 
# \see [\ref XLOGP]
# 
class XLogPCalculator(Boost.Python.instance):

    ##
    # \brief Specifies the number of different structural features used by the \f$ \log P \f$ model.
    # 
    FEATURE_VECTOR_SIZE = 101

    ##
    # \brief Constructs the <tt>XLogPCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %XLogPCalculator instance \a calc.
    # \param calc The \e %XLogPCalculator instance to copy.
    # 
    def __init__(calc: XLogPCalculator) -> None: pass

    ##
    # \brief Constructs the <tt>LogSCalculator</tt> instance and calculates the \f$ \log P \f$ of the molecular graph <em>molgraph</em>.
    # 
    # The calculated \f$ \log P \f$ can be retrieved by a call to getResult().
    # 
    # \param molgraph The molecular graph for which to calculate the \f$ \log P \f$.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %XLogPCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %XLogPCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %XLogPCalculator instance \a calc.
    # \param calc The \e %XLogPCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: XLogPCalculator) -> XLogPCalculator: pass

    ##
    # \brief Calculates the \f$ \log P \f$ of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the \f$ \log P \f$.
    # 
    # \return The calculated \f$ \log P \f$ of the molecular graph <em>molgraph</em>.
    # 
    def calculate(molgraph: Chem.MolecularGraph) -> float: pass

    ##
    # \brief Returns the result of the last \f$ \log P \f$ calculation.
    # 
    # \return The result of the last \f$ \log P \f$ calculation, or zero if a calculation has not yet been performed.
    # 
    def getResult() -> float: pass

    ##
    # \brief Returns the feature count vector of the last \f$ \log P \f$ calculation.
    # 
    # The occurrence count of a particular structural feature (atom type or correction factor feature) can be retrieved from the returned vector via its feature index. For atom type related features, the feature index correspond to the numerical identifier of the atom type in the original publication [\ref XLOGP] minus <em>1</em>. The feature indices of the various correction factors start at index <em>90</em> and are ordered according to their definition in the paper.
    # 
    # \return The feature count vector of the last \f$ \log P \f$ calculation. 
    # 
    # \note The returned feature vector is of size XLogPCalculator.FEATURE_VECTOR_SIZE.
    # 
    def getFeatureVector() -> Math.DVector: pass

    ##
    # \brief Returns the contribution of each atom the total obtained by the last \f$ \log P \f$ calculation.
    # 
    # \return The contribution of each atom the total \f$ \log P \f$. 
    # 
    # \note The sum of the atom contributions does not necessarily equal the calculated molecule \f$ \log P \f$ and might be lower! 
    # 
    # \see XLogPCalculator.calculate()
    # 
    def getAtomContributions() -> Math.DVector: pass

    objectID = property(getObjectID)

    result = property(getResult)
