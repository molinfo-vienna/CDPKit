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
class FMLRModel(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FMLRModel instance.
    # \param self The \e %FMLRModel instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FMLRModel instance.
    # \param self The \e %FMLRModel instance to initialize.
    # \param model 
    #
    def __init__(self: object, model: FMLRModel) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FMLRModel instance this method is called upon.
    #
    # Different Python \e %FMLRModel instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FMLRModel instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FMLRModel) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMLRModel instance \a model.
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param model The \e %FMLRModel instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FMLRModel, model: FMLRModel) -> FMLRModel: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param num_points 
    # \param num_vars 
    #
    def resizeDataSet(self: FMLRModel, num_points: int, num_vars: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    #
    def clearDataSet(self: FMLRModel) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(self: FMLRModel, i: int, x_vars: ConstFVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(self: FMLRModel, i: int, x_vars: ConstDVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(self: FMLRModel, i: int, x_vars: ConstLVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param i 
    # \param x_vars 
    # \param y 
    #
    def setXYData(self: FMLRModel, i: int, x_vars: ConstULVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \param y 
    #
    def addXYData(self: FMLRModel, x_vars: ConstFVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \param y 
    #
    def addXYData(self: FMLRModel, x_vars: ConstDVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \param y 
    #
    def addXYData(self: FMLRModel, x_vars: ConstLVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \param y 
    #
    def addXYData(self: FMLRModel, x_vars: ConstULVectorExpression, y: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getXMatrix(self: FMLRModel) -> FMatrix: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getYValues(self: FMLRModel) -> FVector: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    #
    def buildModel(self: FMLRModel) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    #
    def calcStatistics(self: FMLRModel) -> None: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def calcYValue(self: FMLRModel, x_vars: ConstFVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def calcYValue(self: FMLRModel, x_vars: ConstDVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def calcYValue(self: FMLRModel, x_vars: ConstLVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def calcYValue(self: FMLRModel, x_vars: ConstULVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getCoefficients(self: FMLRModel) -> FVector: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getChiSquare(self: FMLRModel) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getGoodnessOfFit(self: FMLRModel) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getCorrelationCoefficient(self: FMLRModel) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \return 
    #
    def getStandardDeviation(self: FMLRModel) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def __call__(self: FMLRModel, x_vars: ConstFVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def __call__(self: FMLRModel, x_vars: ConstDVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def __call__(self: FMLRModel, x_vars: ConstLVectorExpression) -> float: pass

    ##
    # \brief 
    # \param self The \e %FMLRModel instance this method is called upon.
    # \param x_vars 
    # \return 
    #
    def __call__(self: FMLRModel, x_vars: ConstULVectorExpression) -> float: pass

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
