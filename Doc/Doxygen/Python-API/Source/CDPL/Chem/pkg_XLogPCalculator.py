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
class XLogPCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    FEATURE_VECTOR_SIZE = 101

    ##
    # \brief Initializes the \e %XLogPCalculator instance.
    # \param self The \e %XLogPCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %XLogPCalculator instance.
    # \param self The \e %XLogPCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: XLogPCalculator) -> None: pass

    ##
    # \brief Initializes the \e %XLogPCalculator instance.
    # \param self The \e %XLogPCalculator instance to initialize.
    # \param molgraph 
    #
    def __init__(self: object, molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %XLogPCalculator instance this method is called upon.
    #
    # Different Python \e %XLogPCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %XLogPCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: XLogPCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %XLogPCalculator instance \a calculator.
    # \param self The \e %XLogPCalculator instance this method is called upon.
    # \param calculator The \e %XLogPCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: XLogPCalculator, calculator: XLogPCalculator) -> XLogPCalculator: pass

    ##
    # \brief 
    # \param self The \e %XLogPCalculator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def calculate(self: XLogPCalculator, molgraph: MolecularGraph) -> float: pass

    ##
    # \brief 
    # \param self The \e %XLogPCalculator instance this method is called upon.
    # \return 
    #
    def getResult(self: XLogPCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %XLogPCalculator instance this method is called upon.
    # \return 
    #
    def getFeatureVector(self: XLogPCalculator) -> CDPL.Math.DVector: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    result = property(getResult)
