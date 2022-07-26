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
class PharmacophoreAutoCorr3DDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %PharmacophoreAutoCorr3DDescriptorCalculator instance.
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreAutoCorr3DDescriptorCalculator instance.
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: PharmacophoreAutoCorr3DDescriptorCalculator) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreAutoCorr3DDescriptorCalculator instance.
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance to initialize.
    # \param cntnr 
    # \param descr 
    #
    def __init__(self: object, cntnr: FeatureContainer, descr: CDPL.Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    #
    # Different Python \e %PharmacophoreAutoCorr3DDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PharmacophoreAutoCorr3DDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: PharmacophoreAutoCorr3DDescriptorCalculator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PharmacophoreAutoCorr3DDescriptorCalculator instance \a calculator.
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param calculator The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: PharmacophoreAutoCorr3DDescriptorCalculator, calculator: PharmacophoreAutoCorr3DDescriptorCalculator) -> PharmacophoreAutoCorr3DDescriptorCalculator: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param func 
    #
    def setFeature3DCoordinatesFunction(self: PharmacophoreAutoCorr3DDescriptorCalculator, func: Feature3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param func 
    #
    def setFeaturePairWeightFunction(self: PharmacophoreAutoCorr3DDescriptorCalculator, func: DoubleFeature2UIntFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param num_steps 
    #
    def setNumSteps(self: PharmacophoreAutoCorr3DDescriptorCalculator, num_steps: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getNumSteps(self: PharmacophoreAutoCorr3DDescriptorCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param radius_inc 
    #
    def setRadiusIncrement(self: PharmacophoreAutoCorr3DDescriptorCalculator, radius_inc: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getRadiusIncrement(self: PharmacophoreAutoCorr3DDescriptorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param start_radius 
    #
    def setStartRadius(self: PharmacophoreAutoCorr3DDescriptorCalculator, start_radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \return 
    #
    def getStartRadius(self: PharmacophoreAutoCorr3DDescriptorCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %PharmacophoreAutoCorr3DDescriptorCalculator instance this method is called upon.
    # \param cntnr 
    # \param descr 
    #
    def calculate(self: PharmacophoreAutoCorr3DDescriptorCalculator, cntnr: FeatureContainer, descr: CDPL.Math.DVector) -> None: pass

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
