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
# \brief 
#
class DMLRModel(Boost.Python.instance):

    ##
    # \brief Initializes the \e %DMLRModel instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DMLRModel instance.
    # \param model 
    #
    def __init__(model: DMLRModel) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %DMLRModel instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DMLRModel instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DMLRModel instance \a model.
    # \param model The \e %DMLRModel instance to copy.
    # \return \a self
    #
    def assign(model: DMLRModel) -> DMLRModel: pass

    ##
    # \brief 
    # \param num_points 
    # \param num_vars 
    #
    def resizeDataSet(num_points: int, num_vars: int) -> None: pass

    ##
    # \brief 
    #
    def clearDataSet() -> None: pass

    ##
    # \brief 
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(i: int, x_vars: ConstFVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(i: int, x_vars: ConstDVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(i: int, x_vars: ConstLVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(i: int, x_vars: ConstULVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param x_vars 
    # \param y 
    #
    def addXYData(x_vars: ConstFVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param x_vars 
    # \param y 
    #
    def addXYData(x_vars: ConstDVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param x_vars 
    # \param y 
    #
    def addXYData(x_vars: ConstLVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param x_vars 
    # \param y 
    #
    def addXYData(x_vars: ConstULVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getXMatrix() -> DMatrix: pass

    ##
    # \brief 
    # \return 
    #
    def getYValues() -> DVector: pass

    ##
    # \brief 
    #
    def buildModel() -> None: pass

    ##
    # \brief 
    #
    def calcStatistics() -> None: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def calcYValue(x_vars: ConstFVectorExpression) -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def calcYValue(x_vars: ConstDVectorExpression) -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def calcYValue(x_vars: ConstLVectorExpression) -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def calcYValue(x_vars: ConstULVectorExpression) -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getCoefficients() -> DVector: pass

    ##
    # \brief 
    # \return 
    #
    def getChiSquare() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getGoodnessOfFit() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getCorrelationCoefficient() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getStandardDeviation() -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def __call__(x_vars: ConstFVectorExpression) -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def __call__(x_vars: ConstDVectorExpression) -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def __call__(x_vars: ConstLVectorExpression) -> float: pass

    ##
    # \brief 
    # \param x_vars 
    # \return 
    #
    def __call__(x_vars: ConstULVectorExpression) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    xMatrix = property(getXMatrix)

    ##
    # \brief 
    #
    yValues = property(getYValues)

    ##
    # \brief 
    #
    coefficients = property(getCoefficients)

    ##
    # \brief 
    #
    chiSquare = property(getChiSquare)

    ##
    # \brief 
    #
    goodnessOfFit = property(getGoodnessOfFit)

    ##
    # \brief 
    #
    correlationCoefficient = property(getCorrelationCoefficient)

    ##
    # \brief 
    #
    standardDeviation = property(getStandardDeviation)
