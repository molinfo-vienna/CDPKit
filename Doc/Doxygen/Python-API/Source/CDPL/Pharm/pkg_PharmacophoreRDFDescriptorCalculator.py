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
class PharmacophoreRDFDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %PharmacophoreRDFDescriptorCalculator instance.
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreRDFDescriptorCalculator instance.
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: PharmacophoreRDFDescriptorCalculator) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreRDFDescriptorCalculator instance.
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance to initialize.
    # \param cntnr 
    # \param descr 
    #
    def __init__(self: object, cntnr: FeatureContainer, descr: CDPL.Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    #
    # Different Python \e %PharmacophoreRDFDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PharmacophoreRDFDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: PharmacophoreRDFDescriptorCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PharmacophoreRDFDescriptorCalculator instance \a calculator.
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param calculator The \e %PharmacophoreRDFDescriptorCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: PharmacophoreRDFDescriptorCalculator, calculator: PharmacophoreRDFDescriptorCalculator) -> PharmacophoreRDFDescriptorCalculator: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param func 
    #
    def setFeature3DCoordinatesFunction(self: PharmacophoreRDFDescriptorCalculator, func: Feature3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param func 
    #
    def setFeaturePairWeightFunction(self: PharmacophoreRDFDescriptorCalculator, func: DoubleFeature2UIntFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param num_steps 
    #
    def setNumSteps(self: PharmacophoreRDFDescriptorCalculator, num_steps: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getNumSteps(self: PharmacophoreRDFDescriptorCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param radius_inc 
    #
    def setRadiusIncrement(self: PharmacophoreRDFDescriptorCalculator, radius_inc: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getRadiusIncrement(self: PharmacophoreRDFDescriptorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param start_radius 
    #
    def setStartRadius(self: PharmacophoreRDFDescriptorCalculator, start_radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getStartRadius(self: PharmacophoreRDFDescriptorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param factor 
    #
    def setSmoothingFactor(self: PharmacophoreRDFDescriptorCalculator, factor: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getSmoothingFactor(self: PharmacophoreRDFDescriptorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param factor 
    #
    def setScalingFactor(self: PharmacophoreRDFDescriptorCalculator, factor: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getScalingFactor(self: PharmacophoreRDFDescriptorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param enable 
    #
    def enableDistanceToIntervalCenterRounding(self: PharmacophoreRDFDescriptorCalculator, enable: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def distanceToIntervalsCenterRoundingEnabled(self: PharmacophoreRDFDescriptorCalculator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreRDFDescriptorCalculator instance this method is called upon.
    # \param cntnr 
    # \param descr 
    #
    def calculate(self: PharmacophoreRDFDescriptorCalculator, cntnr: FeatureContainer, descr: CDPL.Math.DVector) -> None: pass

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
