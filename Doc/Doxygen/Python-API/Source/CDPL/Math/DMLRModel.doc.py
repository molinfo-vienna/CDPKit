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
# \brief Performs <em>Multiple Linear Regression</em> [\ref WLIREG] on a set of data points \f$ (y_i, \vec{X}_i) \f$.
# 
# For each data point, \f$ y_i \f$ is the dependent (response) variable and \f$ \vec{X}_i \f$ is a \f$ M \f$-dimensional vector containing the independent (explanatory) variables of the modeled function \f$ y = f(\vec{X}) \f$. It is assumed that the relationship between the dependent variables \f$ y_i \f$ and the independent variables \f$ \vec{X}_i \f$ can be modeled by a linear function of \f$ M \f$ parameters \f$ \beta_i, \, i = 1, 2, \ldots, M \f$ (regression coefficients) plus an error term \f$ \epsilon_i \f$:
# 
# \[ y_i = \beta_1 x_{i1} + \beta_2 x_{i2} + \ldots + \beta_M x_{iM} + \epsilon_i \]
# 
# The parameters \f$ \beta_i \f$ are estimated by <em>Least Squares Analysis</em> [\ref WLSQRS] which minimizes the sum of squared residuals \f$ \chi^2 \f$
# 
# \[ \chi^2 = \sum_{i=1}^{N} (y_i - f(\vec{X}_i, \vec{\beta}))^2 \]
# 
# of the given set of \f$ N \f$ data points with respect to the adjustable parameters \f$ \vec{\beta} \f$. The parameters \f$ \beta_i \f$ are computed using <em>Singular Value Decomposition</em> [\ref WSVD] as implemented in [\ref NRIC]. This method is computationally intensive, but is particularly useful if the \f$ X \f$ matrix is ill-conditioned.
# 
class DMLRModel(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a regression model with an empty data set.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %DMLRModel instance \a model.
    # \param model The \e %DMLRModel instance to copy.
    # 
    def __init__(model: DMLRModel) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %DMLRModel instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %DMLRModel instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %DMLRModel instance \a model.
    # \param model The \c %DMLRModel instance to copy.
    # \return \a self
    # 
    def assign(model: DMLRModel) -> DMLRModel: pass

    ##
    # \brief Resizes the data set to hold <em>num_points</em> data points with <em>num_vars</em> independent variables.
    # 
    # \param num_points The number of data points.
    # \param num_vars The number of independent variables per data point.
    # 
    def resizeDataSet(num_points: int, num_vars: int) -> None: pass

    ##
    # \brief Clears the data set.
    # 
    # Equivalent to calling resizeDataSet() with both arguments beeing zero.
    # 
    def clearDataSet() -> None: pass

    ##
    # \brief Sets the <em>i-th</em> data point \f$ (y_i, \vec{X}_i) \f$ of the data set.
    # 
    # If <em>i</em> is larger or equal to the number of currently stored data points or if the number of independent variables provided by <em>x_vars</em> is larger than the maximum number so far, the data set will be resized accordingly. Emerging space between the data points so far and the new data point is filled up with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number of variables in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param i The zero-based index of the data point in the data set.
    # \param x_vars The vector \f$ \vec{X}_i \f$ with independent variables.
    # \param y The dependent variable \f$ y_i \f$.
    # 
    def setXYData(i: int, x_vars: ConstFVectorExpression, y: float) -> None: pass

    ##
    # \brief Sets the <em>i-th</em> data point \f$ (y_i, \vec{X}_i) \f$ of the data set.
    # 
    # If <em>i</em> is larger or equal to the number of currently stored data points or if the number of independent variables provided by <em>x_vars</em> is larger than the maximum number so far, the data set will be resized accordingly. Emerging space between the data points so far and the new data point is filled up with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number of variables in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param i The zero-based index of the data point in the data set.
    # \param x_vars The vector \f$ \vec{X}_i \f$ with independent variables.
    # \param y The dependent variable \f$ y_i \f$.
    # 
    def setXYData(i: int, x_vars: ConstDVectorExpression, y: float) -> None: pass

    ##
    # \brief Sets the <em>i-th</em> data point \f$ (y_i, \vec{X}_i) \f$ of the data set.
    # 
    # If <em>i</em> is larger or equal to the number of currently stored data points or if the number of independent variables provided by <em>x_vars</em> is larger than the maximum number so far, the data set will be resized accordingly. Emerging space between the data points so far and the new data point is filled up with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number of variables in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param i The zero-based index of the data point in the data set.
    # \param x_vars The vector \f$ \vec{X}_i \f$ with independent variables.
    # \param y The dependent variable \f$ y_i \f$.
    # 
    def setXYData(i: int, x_vars: ConstLVectorExpression, y: float) -> None: pass

    ##
    # \brief Sets the <em>i-th</em> data point \f$ (y_i, \vec{X}_i) \f$ of the data set.
    # 
    # If <em>i</em> is larger or equal to the number of currently stored data points or if the number of independent variables provided by <em>x_vars</em> is larger than the maximum number so far, the data set will be resized accordingly. Emerging space between the data points so far and the new data point is filled up with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number of variables in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param i The zero-based index of the data point in the data set.
    # \param x_vars The vector \f$ \vec{X}_i \f$ with independent variables.
    # \param y The dependent variable \f$ y_i \f$.
    # 
    def setXYData(i: int, x_vars: ConstULVectorExpression, y: float) -> None: pass

    ##
    # \brief Adds a new data point \f$ (y, \vec{X}) \f$ to the current data set.
    # 
    # If the number of independent variables provided by <em>x_vars</em> is larger than the number in the current data set, the data set is resized accordingly and any emerging space will be filled with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ with independent variables.
    # \param y The dependent variable \f$ y \f$.
    # 
    # \note If the final size of the data set is known in advance, a call to resizeDataSet() followed by calls to setXYData() for each data point is more efficient than a build-up of the data set by repeatedly calling <tt>addXYData</tt>().
    # 
    def addXYData(x_vars: ConstFVectorExpression, y: float) -> None: pass

    ##
    # \brief Adds a new data point \f$ (y, \vec{X}) \f$ to the current data set.
    # 
    # If the number of independent variables provided by <em>x_vars</em> is larger than the number in the current data set, the data set is resized accordingly and any emerging space will be filled with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ with independent variables.
    # \param y The dependent variable \f$ y \f$.
    # 
    # \note If the final size of the data set is known in advance, a call to resizeDataSet() followed by calls to setXYData() for each data point is more efficient than a build-up of the data set by repeatedly calling <tt>addXYData</tt>().
    # 
    def addXYData(x_vars: ConstDVectorExpression, y: float) -> None: pass

    ##
    # \brief Adds a new data point \f$ (y, \vec{X}) \f$ to the current data set.
    # 
    # If the number of independent variables provided by <em>x_vars</em> is larger than the number in the current data set, the data set is resized accordingly and any emerging space will be filled with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ with independent variables.
    # \param y The dependent variable \f$ y \f$.
    # 
    # \note If the final size of the data set is known in advance, a call to resizeDataSet() followed by calls to setXYData() for each data point is more efficient than a build-up of the data set by repeatedly calling <tt>addXYData</tt>().
    # 
    def addXYData(x_vars: ConstLVectorExpression, y: float) -> None: pass

    ##
    # \brief Adds a new data point \f$ (y, \vec{X}) \f$ to the current data set.
    # 
    # If the number of independent variables provided by <em>x_vars</em> is larger than the number in the current data set, the data set is resized accordingly and any emerging space will be filled with zeros. If the number of independent variables provided by <em>x_vars</em> is smaller than the number in the current data set, the missing independent variables are assumed to be zero.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ with independent variables.
    # \param y The dependent variable \f$ y \f$.
    # 
    # \note If the final size of the data set is known in advance, a call to resizeDataSet() followed by calls to setXYData() for each data point is more efficient than a build-up of the data set by repeatedly calling <tt>addXYData</tt>().
    # 
    def addXYData(x_vars: ConstULVectorExpression, y: float) -> None: pass

    ##
    # \brief Returns a read-only matrix where each row represents the vector \f$ \vec{X}_i \f$ with independent variables of the currently stored data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
    # 
    # \return A reference to the matrix with the independent variables \f$ \vec{X}_i \f$.
    # 
    def getXMatrix() -> DMatrix: pass

    ##
    # \brief Returns a read-only vector containing the dependent variables \f$ y_i \f$ of the currently stored data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
    # 
    # \return A reference to the vector with the dependent variables \f$ y_i \f$.
    # 
    def getYValues() -> DVector: pass

    ##
    # \brief Performs linear least squares regression modeling of the set of currently stored data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
    # 
    # \throw Base.CalculationFailed if the data set is empty or the singular value decomposition of the \f$ X \f$ matrix failed.
    # 
    def buildModel() -> None: pass

    ##
    # \brief Calculates various statistical parameters describing the built regression model.
    # 
    # \throw Base.CalculationFailed if the data set is in an inconsistent state (e.g. the number of estimated regression coefficients does not match the number of independent variables that make up the data points).
    # 
    # \see buildModel(), getChiSquare(), getGoodnessOfFit(), getCorrelationCoefficient(), getStandardDeviation()
    # 
    def calcStatistics() -> None: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def calcYValue(x_vars: ConstFVectorExpression) -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def calcYValue(x_vars: ConstDVectorExpression) -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def calcYValue(x_vars: ConstLVectorExpression) -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def calcYValue(x_vars: ConstULVectorExpression) -> float: pass

    ##
    # \brief Returns a read-only vector containing the estimated regression coefficients \f$ \beta_i \f$ which were calculated by buildModel().
    # 
    # \return A reference to the vector with the estimated regression coefficients \f$ \beta_i \f$.
    # 
    def getCoefficients() -> DVector: pass

    ##
    # \brief Returns the sum of squared residuals \f$ \chi^2 \f$.
    # 
    # \f$ \chi^2 \f$ is calculated by:
    # 
    # \[ \chi^2 = \sum_{i=1}^{N} (y_i - \sum_{j=1}^{M}(x_{ij} \beta_j))^2 \]
    # 
    # \return The sum of squared residuals \f$ \chi^2 \f$. 
    # 
    # \note The returned value is only valid if calcStatistics() has been called before.
    # 
    def getChiSquare() -> float: pass

    ##
    # \brief Returns the goodness of fit \f$ Q \f$.
    # 
    # The goodness of fit \f$ Q \f$ is given by:
    # 
    # \[ Q = gammaq(\frac{N - 2}{2}, \frac{\chi^2}{2}) \]
    # 
    # where \f$ gammaq \f$ is the incomplete gamma function (see [\ref NRIC] for details).
    # 
    # \return The goodness of fit \f$ Q \f$. 
    # 
    # \note The returned value is only valid if calcStatistics() has been called before. 
    # 
    # \see Math.gammaQ()
    # 
    def getGoodnessOfFit() -> float: pass

    ##
    # \brief Returns the correlation coefficient \f$ r \f$.
    # 
    # The correlation coefficient \f$ r \f$ is calculated by:
    # 
    # \[ r = \frac{\sum_{i=1}^{N} (\hat{y}_i - \bar{\hat{y}})(y_i - \bar{y})} {\sqrt{\sum_{i=1}^{N} (\hat{y}_i - \bar{\hat{y}})^2 \sum_{i=1}^{N} (y_i - \bar{y})^2 }} \]
    # 
    # where
    # 
    # \begin{eqnarray*} \hat{y}_i &=& \sum_{j=1}^{M}(x_{ij} \beta_j) \\ \bar{\hat{y}} &=& \frac{\sum_{i=1}^{N} \hat{y}_i}{N} \\ \bar{y} &=& \frac{\sum_{i=1}^{N} y_i}{N} \end{eqnarray*}
    # 
    # \return The correlation coefficient \f$ r \f$. 
    # 
    # \note The returned value is only valid if calcStatistics() has been called before.
    # 
    def getCorrelationCoefficient() -> float: pass

    ##
    # \brief Returns the standard deviation of the residuals \f$ s_r \f$.
    # 
    # The standard deviation \f$ s_r \f$ is calculated by:
    # 
    # \[ s_r = \sqrt{\frac{\sum_{i=1}^{N} (y_i - \sum_{j=1}^{M} (x_{ij} \beta_j))^2} {N - M}} \]
    # 
    # \return The standard deviation of the residuals \f$ s_r \f$. 
    # 
    # \note \f$ s_r \f$ is only definded if \f$ N > M \f$ and calcStatistics() has been called before.
    # 
    def getStandardDeviation() -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # Equivalent to calling calcYValue().
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def __call__(x_vars: ConstFVectorExpression) -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # Equivalent to calling calcYValue().
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def __call__(x_vars: ConstDVectorExpression) -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # Equivalent to calling calcYValue().
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def __call__(x_vars: ConstLVectorExpression) -> float: pass

    ##
    # \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent variables given by <em>x_vars</em>.
    # 
    # Equivalent to calling calcYValue().
    # 
    # \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
    # 
    # \return The predicted value for \f$ y \f$. 
    # 
    # \throw Base.CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not match the size of <em>x_vars</em>.
    # 
    def __call__(x_vars: ConstULVectorExpression) -> float: pass

    objectID = property(getObjectID)

    xMatrix = property(getXMatrix)

    yValues = property(getYValues)

    coefficients = property(getCoefficients)

    chiSquare = property(getChiSquare)

    goodnessOfFit = property(getGoodnessOfFit)

    correlationCoefficient = property(getCorrelationCoefficient)

    standardDeviation = property(getStandardDeviation)
