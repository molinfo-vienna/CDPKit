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
# \brief LogSCalculator.
# 
# \see [\ref LOGS]
# 
class LogSCalculator(Boost.Python.instance):

    ##
    # \brief Specifies the number of different features used by the \f$ \log S \f$ model.
    # 
    FEATURE_VECTOR_SIZE = 79

    ##
    # \brief Constructs the <tt>LogSCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %LogSCalculator instance \a calc.
    # \param calc The \e %LogSCalculator instance to copy.
    # 
    def __init__(calc: LogSCalculator) -> None: pass

    ##
    # \brief Constructs the <tt>LogSCalculator</tt> instance and calculates the \f$ \log S \f$ of the molecular graph <em>molgraph</em>.
    # 
    # The calculated \f$ \log S \f$ can be retrieved by a call to getResult().
    # 
    # \param molgraph The molecular graph for which to calculate the \f$ \log S \f$.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %LogSCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LogSCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LogSCalculator instance \a calc.
    # \param calc The \e %LogSCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: LogSCalculator) -> LogSCalculator: pass

    ##
    # \brief Calculates the \f$ \log S \f$ of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the \f$ \log S \f$.
    # 
    # \return The calculated \f$ \log S \f$ of the molecular graph <em>molgraph</em>.
    # 
    def calculate(molgraph: Chem.MolecularGraph) -> float: pass

    ##
    # \brief Returns the result of the last \f$ \log S \f$ calculation.
    # 
    # \return The result of the last \f$ \log S \f$ calculation, or zero if a calculation has not yet been performed.
    # 
    def getResult() -> float: pass

    ##
    # \brief Returns the feature count vector of the last \f$ \log S \f$ calculation.
    # 
    # The occurrence count of a particular structural feature can be retrieved from the returned vector via its feature index. The feature index correspond to the numerical identifier of the feature's definition in the original publication [\ref LOGS].
    # 
    # \return The feature count vector of the last \f$ \log S \f$ calculation. 
    # 
    # \note The returned feature vector is of size LogSCalculator.FEATURE_VECTOR_SIZE.
    # 
    def getFeatureVector() -> Math.DVector: pass

    objectID = property(getObjectID)

    result = property(getResult)
