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
class AtomAutoCorrelation3DVectorCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AtomAutoCorrelation3DVectorCalculator instance.
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %AtomAutoCorrelation3DVectorCalculator instance.
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: AtomAutoCorrelation3DVectorCalculator) -> None: pass

    ##
    # \brief Initializes the \e %AtomAutoCorrelation3DVectorCalculator instance.
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance to initialize.
    # \param cntnr 
    # \param vec 
    #
    def __init__(self: object, cntnr: AtomContainer, vec: CDPL.Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    #
    # Different Python \e %AtomAutoCorrelation3DVectorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomAutoCorrelation3DVectorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: AtomAutoCorrelation3DVectorCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AtomAutoCorrelation3DVectorCalculator instance \a calculator.
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param calculator The \e %AtomAutoCorrelation3DVectorCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: AtomAutoCorrelation3DVectorCalculator, calculator: AtomAutoCorrelation3DVectorCalculator) -> AtomAutoCorrelation3DVectorCalculator: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param func 
    #
    def setEntityPairWeightFunction(self: AtomAutoCorrelation3DVectorCalculator, func: DoubleAtom2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param func 
    #
    def setEntity3DCoordinatesFunction(self: AtomAutoCorrelation3DVectorCalculator, func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param num_steps 
    #
    def setNumSteps(self: AtomAutoCorrelation3DVectorCalculator, num_steps: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \return 
    #
    def getNumSteps(self: AtomAutoCorrelation3DVectorCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param radius_inc 
    #
    def setRadiusIncrement(self: AtomAutoCorrelation3DVectorCalculator, radius_inc: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \return 
    #
    def getRadiusIncrement(self: AtomAutoCorrelation3DVectorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param start_radius 
    #
    def setStartRadius(self: AtomAutoCorrelation3DVectorCalculator, start_radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \return 
    #
    def getStartRadius(self: AtomAutoCorrelation3DVectorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %AtomAutoCorrelation3DVectorCalculator instance this method is called upon.
    # \param cntnr 
    # \param vec 
    #
    def calculate(self: AtomAutoCorrelation3DVectorCalculator, cntnr: AtomContainer, vec: CDPL.Math.DVector) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    startRadius = property(getStartRadius, setStartRadius)

    ##
    # \brief 
    #
    radiusIncrement = property(getRadiusIncrement, setRadiusIncrement)

    ##
    # \brief 
    #
    numSteps = property(getNumSteps, setNumSteps)
