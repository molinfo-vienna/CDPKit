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
class FeatureRDFCodeCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FeatureRDFCodeCalculator instance.
    # \param self The \e %FeatureRDFCodeCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FeatureRDFCodeCalculator instance.
    # \param self The \e %FeatureRDFCodeCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: FeatureRDFCodeCalculator) -> None: pass

    ##
    # \brief Initializes the \e %FeatureRDFCodeCalculator instance.
    # \param self The \e %FeatureRDFCodeCalculator instance to initialize.
    # \param cntnr 
    # \param rdf_code 
    #
    def __init__(self: object, cntnr: FeatureContainer, rdf_code: CDPL.Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    #
    # Different Python \e %FeatureRDFCodeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeatureRDFCodeCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FeatureRDFCodeCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureRDFCodeCalculator instance \a calculator.
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param calculator The \e %FeatureRDFCodeCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FeatureRDFCodeCalculator, calculator: FeatureRDFCodeCalculator) -> FeatureRDFCodeCalculator: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param func 
    #
    def setEntityPairWeightFunction(self: FeatureRDFCodeCalculator, func: DoubleFeature2Functor) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param func 
    #
    def setEntity3DCoordinatesFunction(self: FeatureRDFCodeCalculator, func: Feature3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param num_steps 
    #
    def setNumSteps(self: FeatureRDFCodeCalculator, num_steps: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \return 
    #
    def getNumSteps(self: FeatureRDFCodeCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param radius_inc 
    #
    def setRadiusIncrement(self: FeatureRDFCodeCalculator, radius_inc: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \return 
    #
    def getRadiusIncrement(self: FeatureRDFCodeCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param start_radius 
    #
    def setStartRadius(self: FeatureRDFCodeCalculator, start_radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \return 
    #
    def getStartRadius(self: FeatureRDFCodeCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param factor 
    #
    def setSmoothingFactor(self: FeatureRDFCodeCalculator, factor: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \return 
    #
    def getSmoothingFactor(self: FeatureRDFCodeCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param factor 
    #
    def setScalingFactor(self: FeatureRDFCodeCalculator, factor: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \return 
    #
    def getScalingFactor(self: FeatureRDFCodeCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param enable 
    #
    def enableDistanceToIntervalCenterRounding(self: FeatureRDFCodeCalculator, enable: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \return 
    #
    def distanceToIntervalsCenterRoundingEnabled(self: FeatureRDFCodeCalculator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %FeatureRDFCodeCalculator instance this method is called upon.
    # \param cntnr 
    # \param rdf_code 
    #
    def calculate(self: FeatureRDFCodeCalculator, cntnr: FeatureContainer, rdf_code: CDPL.Math.DVector) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    distanceToIntervalCenterRounding = property(getDistanceToIntervalCenterRounding, setDistanceToIntervalCenterRounding)

    ##
    # \brief 
    #
    smoothingFactor = property(getSmoothingFactor, setSmoothingFactor)

    ##
    # \brief 
    #
    scalingFactor = property(getScalingFactor, setScalingFactor)

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
