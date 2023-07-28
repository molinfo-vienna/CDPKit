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
# \brief FeatureAutoCorrelation3DVectorCalculator.
# 
# \see [\ref CITB, \ref HBMD]
# 
class FeatureAutoCorrelation3DVectorCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>FeatureAutoCorrelation3DVectorCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FeatureAutoCorrelation3DVectorCalculator instance.
    # \param self The \e %FeatureAutoCorrelation3DVectorCalculator instance to initialize.
    # \param calc 
    # 
    def __init__(calc: FeatureAutoCorrelation3DVectorCalculator) -> None: pass

    ##
    # \brief Initializes the \e %FeatureAutoCorrelation3DVectorCalculator instance.
    # \param self The \e %FeatureAutoCorrelation3DVectorCalculator instance to initialize.
    # \param cntnr 
    # \param vec 
    # 
    def __init__(cntnr: CDPL.Pharm.FeatureContainer, vec: CDPL.Math.DVector) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FeatureAutoCorrelation3DVectorCalculator instance this method is called upon.
    # 
    # Different Python \e %FeatureAutoCorrelation3DVectorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeatureAutoCorrelation3DVectorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param calc 
    # \return 
    #
    def assign(calc: FeatureAutoCorrelation3DVectorCalculator) -> FeatureAutoCorrelation3DVectorCalculator: pass

    ##
    # \brief 
    # \param func 
    #
    def setEntityPairWeightFunction(func: CDPL.Pharm.DoubleFeature2Functor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setEntity3DCoordinatesFunction(func: CDPL.Pharm.Feature3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param num_steps 
    #
    def setNumSteps(num_steps: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumSteps() -> int: pass

    ##
    # \brief 
    # \param radius_inc 
    #
    def setRadiusIncrement(radius_inc: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRadiusIncrement() -> float: pass

    ##
    # \brief 
    # \param start_radius 
    #
    def setStartRadius(start_radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStartRadius() -> float: pass

    ##
    # \brief 
    # \param cntnr 
    # \param vec 
    #
    def calculate(cntnr: CDPL.Pharm.FeatureContainer, vec: CDPL.Math.DVector) -> None: pass

    objectID = property(getObjectID)

    startRadius = property(getStartRadius, setStartRadius)

    radiusIncrement = property(getRadiusIncrement, setRadiusIncrement)

    numSteps = property(getNumSteps, setNumSteps)
