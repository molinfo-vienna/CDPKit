/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MLRModel.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of the class CDPL::Math::MLRModel.
 */

#ifndef CDPL_MATH_MLRMODEL_HPP
#define CDPL_MATH_MLRMODEL_HPP

#include <limits>

#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/CommonType.hpp"
#include "CDPL/Math/TypeTraits.hpp"
#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Math/SpecialFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Math
	{	

		/**
		 * \addtogroup CDPL_MATH_LINEAR_REGRESSION
		 * @{
		 */

		/**
		 * \brief Performs <em>Multiple Linear Regression</em> [\ref WLIREG] on a set of data points
		 *        \f$ (y_i, \vec{X}_i) \f$.
		 *
		 * For each data point, \f$ y_i \f$ is the dependent (response) variable and \f$ \vec{X}_i \f$
		 * is a \f$ M \f$-dimensional vector containing the independent (explanatory) variables of the modeled
		 * function \f$ y = f(\vec{X}) \f$.
		 * It is assumed that the relationship between the dependent variables \f$ y_i \f$ and the independent variables
		 * \f$ \vec{X}_i \f$ can be modeled by a linear function of \f$ M \f$ parameters \f$ \beta_i, \, i = 1, 2, \ldots, M \f$
		 * (regression coefficients) plus an error term \f$ \epsilon_i \f$:
		 *
		 * \f[ 
		 *    y_i = \beta_1 x_{i1} + \beta_2 x_{i2} + \ldots + \beta_M x_{iM} + \epsilon_i 
		 * \f] 
		 *
		 * The parameters \f$ \beta_i \f$ are estimated by <em>Least Squares Analysis</em> [\ref WLSQRS]
		 * which minimizes the sum of squared residuals \f$ \chi^2 \f$ 
		 *
		 * \f[ 
		 *    \chi^2 = \sum_{i=1}^{N} (y_i - f(\vec{X}_i, \vec{\beta}))^2
		 * \f] 
		 *
		 * of the given set of \f$ N \f$ data points with respect to the adjustable parameters \f$ \vec{\beta} \f$. 
		 * The parameters \f$ \beta_i \f$ are computed using <em>Singular Value Decomposition</em> [\ref WSVD] as
		 * implemented in [\ref NRIC]. This method is computationally intensive, but is particularly useful if the \f$ X \f$
		 * matrix is ill-conditioned.
		 *
		 * \tparam T The value type used in calculations and for storage of data points.
		 */
		template <typename T = double>
		class MLRModel
		{

		public:
			typedef typename CommonType<typename Vector<T>::SizeType, typename Matrix<T>::SizeType>::Type SizeType;
			typedef T ValueType;
			typedef Matrix<T> MatrixType;
			typedef Vector<T> VectorType;

			/**
			 * \brief Constructs and initializes a regression model with an empty data set.
			 */
			MLRModel(): chiSquare(0), Q(0), r(0), stdDeviation(0) {}

			/**
			 * \brief Resizes the data set to hold \a num_points data points with \a num_vars independent variables.
			 * \param num_points The number of data points.
			 * \param num_vars The number of independent variables per data point.
			 */
			void resizeDataSet(SizeType num_points, SizeType num_vars);

			/**
			 * \brief Clears the data set.
			 *
			 * Equivalent to calling resizeDataSet() with both arguments beeing zero.
			 */
			void clearDataSet();

			/**
			 * \brief Sets the \a i-th data point \f$ (y_i, \vec{X}_i) \f$ of the data set.
			 *
			 * If \a i is larger or equal to the number of currently stored data points or if the number
			 * of independent variables provided by \a x_vars is larger than the maximum number so far, the data set will
			 * be resized accordingly. Emerging space between the data points so far and the new data point is filled
			 * up with zeros. If the number of independent variables provided by \a x_vars is smaller than the number
			 * of variables in the current data set, the missing independent variables are assumed to be zero.
			 *
			 * \param i The zero-based index of the data point in the data set.
			 * \param x_vars The vector \f$ \vec{X}_i \f$ with independent variables.
			 * \param y The dependent variable \f$ y_i \f$.
			 */
			template <typename V>
			void setXYData(SizeType i, const VectorExpression<V>& x_vars, ValueType y);

			/**
			 * \brief Adds a new data point \f$ (y, \vec{X}) \f$ to the current data set.
			 *
			 * If the number of independent variables provided by \a x_vars is larger than the number in the current data set, the data
			 * set is resized accordingly and any emerging space will be filled with zeros. If the number of independent variables 
			 * provided by \a x_vars is smaller than the number in the current data set, the missing independent variables are assumed
			 * to be zero.
			 *
			 * \param x_vars The vector \f$ \vec{X} \f$ with independent variables.
			 * \param y The dependent variable \f$ y \f$.
			 * \note If the final size of the data set is known in advance, a call to resizeDataSet() followed by
			 *       calls to setXYData() for each data point is more efficient than a build-up of the data set by 
			 *       repeatedly calling \c %addXYData(). 
			 */
			template <typename V>
			void addXYData(const VectorExpression<V>& x_vars, ValueType y);

			/**
			 * \brief Returns a matrix where each row represents the vector \f$ \vec{X}_i \f$ with independent variables
			 *        of the currently stored data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
			 * \return A non-\c const reference to the matrix with the independent variables \f$ \vec{X}_i \f$.
			 */
			MatrixType& getXMatrix();
			
			/**
			 * \brief Returns a read-only matrix where each row represents the vector \f$ \vec{X}_i \f$ with independent variables
			 *        of the currently stored data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
			 * \return A \c const reference to the matrix with the independent variables \f$ \vec{X}_i \f$.
			 */
			const MatrixType& getXMatrix() const;

			/**
			 * \brief Returns a vector containing the dependent variables \f$ y_i \f$ of the currently stored
			 *        data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
			 * \return A non-\c const reference to the vector with the dependent variables \f$ y_i \f$.
			 */
			VectorType& getYValues();

			/**
			 * \brief Returns a read-only vector containing the dependent variables \f$ y_i \f$ of the currently stored
			 *        data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
			 * \return A \c const reference to the vector with the dependent variables \f$ y_i \f$.
			 */
			const VectorType& getYValues() const;

			/**
			 * \brief Performs linear least squares regression modeling of the set of currently stored
			 *        data points \f$ (y_i, \vec{X}_i), \, i = 1, 2, \ldots, N \f$.
			 * \throw Base::CalculationFailed if the data set is empty or the singular value decomposition
			 *        of the \f$ X \f$ matrix failed.
			 */
			void buildModel();

			/**
			 * \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent
			 *        variables given by \a x_vars.
			 * \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
			 * \return The predicted value for \f$ y \f$.
			 * \throw Base::CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not
			 *        match the size of \a x_vars.
			 */
			template <typename V>
			ValueType calcYValue(const VectorExpression<V>& x_vars) const;

			/**
			 * \brief Predicts the value of the dependent variable \f$ y \f$ for a vector \f$ \vec{X} \f$ of independent
			 *        variables given by \a x_vars.
			 *
			 * Equivalent to calling calcYValue().
			 *
			 * \param x_vars The vector \f$ \vec{X} \f$ of independent variables.
			 * \return The predicted value for \f$ y \f$.
			 * \throw Base::CalculationFailed if the number of regression coefficients \f$ \beta_i \f$ does not
			 *        match the size of \a x_vars.
			 */
			template <typename V>
			ValueType operator()(const VectorExpression<V>& x_vars) const;

			/**
			 * \brief Returns a read-only vector containing the estimated regression coefficients \f$ \beta_i \f$ 
			 *        which were calculated by buildModel().
			 * \return A \c const reference to the vector with the estimated regression coefficients \f$ \beta_i \f$.
			 */
			const VectorType& getCoefficients() const;

			/**
			 * \brief Returns the sum of squared residuals \f$ \chi^2 \f$.
			 *
			 * \f$ \chi^2 \f$ is calculated by:
			 *
			 * \f[ 
			 *    \chi^2 = \sum_{i=1}^{N} (y_i - \sum_{j=1}^{M}(x_{ij} \beta_j))^2
			 * \f] 
			 *
			 * \return The sum of squared residuals \f$ \chi^2 \f$.
			 * \note The returned value is only valid if calcStatistics() has been called before.
			 */
		    ValueType getChiSquare() const;
			
			/**
			 * \brief Returns the goodness of fit \f$ Q \f$.
			 *
			 * The goodness of fit \f$ Q \f$ is given by:
			 *
			 * \f[ 
			 *    Q = gammaq(\frac{N - 2}{2}, \frac{\chi^2}{2}) 
			 * \f] 
			 *
			 * where \f$ gammaq \f$ is the incomplete gamma function (see [\ref NRIC] for details).
			 *
			 * \return The goodness of fit \f$ Q \f$.
			 * \note The returned value is only valid if calcStatistics() has been called before.
			 * \see Math::gammaQ()
			 */
		    ValueType getGoodnessOfFit() const;

			/**
			 * \brief Returns the correlation coefficient \f$ r \f$.
			 *
			 * The correlation coefficient \f$ r \f$ is calculated by:
			 *
			 * \f[ 
			 *    r = \frac{\sum_{i=1}^{N} (\hat{y}_i - \bar{\hat{y}})(y_i - \bar{y})} {\sqrt{\sum_{i=1}^{N} 
			 *        (\hat{y}_i - \bar{\hat{y}})^2 \sum_{i=1}^{N} (y_i - \bar{y})^2 }} 
			 * \f] 
			 *
			 * where
			 *
			 * \f{eqnarray*}{
			 *    \hat{y}_i     &=& \sum_{j=1}^{M}(x_{ij} \beta_j) \\
			 *    \bar{\hat{y}} &=& \frac{\sum_{i=1}^{N} \hat{y}_i}{N} \\
			 *    \bar{y}       &=& \frac{\sum_{i=1}^{N} y_i}{N} 
			 * \f}
			 *
			 * \return The correlation coefficient \f$ r \f$.
			 * \note The returned value is only valid if calcStatistics() has been called before.
			 */
		    ValueType getCorrelationCoefficient() const;

			/**
			 * \brief Returns the standard deviation of the residuals \f$ s_r \f$.
			 *
			 * The standard deviation \f$ s_r \f$ is calculated by:
			 *
			 * \f[ 
			 *    s_r = \sqrt{\frac{\sum_{i=1}^{N} (y_i - \sum_{j=1}^{M} (x_{ij} \beta_j))^2} {N - M}} 
			 * \f] 
			 *
			 * \return The standard deviation of the residuals \f$ s_r \f$.
			 * \note \f$ s_r \f$ is only definded if \f$ N > M \f$ and calcStatistics() has been called before.
			 */
		    ValueType getStandardDeviation() const;

			/**
			 * \brief Calculates various statistical parameters describing the built regression model.
			 * \throw Base::CalculationFailed if the data set is in an inconsistent state 
			 *        (e.g. the number of estimated regression coefficients does not match the 
			 *        number of independent variables that make up the data points).
			 * \see buildModel(), getChiSquare(), getGoodnessOfFit(), getCorrelationCoefficient(),
			 *      getStandardDeviation()
			 */
			void calcStatistics();

		private:
			MatrixType  xMatrix;
			VectorType  yValues;
			VectorType  calcYValues;
			VectorType  coefficients;
			MatrixType  svdU;
			MatrixType  svdV;
			VectorType  svdW;
		    ValueType   chiSquare;
		    ValueType   Q;
		    ValueType   r;
		    ValueType   stdDeviation;
		};

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename T>
void CDPL::Math::MLRModel<T>::resizeDataSet(SizeType num_points, SizeType num_vars)
{
	if (num_points == xMatrix.getSize1() && num_vars == xMatrix.getSize2())
		return;

	xMatrix.resize(num_points, num_vars, true, ValueType());	
	yValues.resize(num_points, ValueType());
}

template <typename T>
void CDPL::Math::MLRModel<T>::clearDataSet()
{
	yValues.resize(0);
	xMatrix.resize(0, 0, false);
}

template <typename T>
template <typename V>
void CDPL::Math::MLRModel<T>::setXYData(SizeType i, const VectorExpression<V>& x_vars, ValueType y)
{
	SizeType x_mtx_size1 = xMatrix.getSize1();
	SizeType x_mtx_size2 = xMatrix.getSize2();
	SizeType x_vars_size = x_vars().getSize();
	SizeType y_vals_size = yValues.getSize();

	resizeDataSet(std::max(i + 1, std::max(x_mtx_size1, y_vals_size)), std::max(x_vars_size, x_mtx_size2));

	for (SizeType j = 0; j < x_vars_size; j++)
		xMatrix(i, j) = x_vars()(j);

	if (x_vars_size < x_mtx_size2)
		for (SizeType j = x_vars_size; j < x_mtx_size2; j++)
			xMatrix(i, j) = ValueType();

	yValues(i) = y;
}

template <typename T>
template <typename V>
void CDPL::Math::MLRModel<T>::addXYData(const VectorExpression<V>& x_vars, ValueType y)
{
	SizeType i = xMatrix.getSize1();
	SizeType x_mtx_size2 = xMatrix.getSize2();
	SizeType x_vars_size = x_vars().getSize();

	resizeDataSet(i + 1, std::max(x_mtx_size2, x_vars_size)); 

	for (SizeType j = 0; j < x_vars_size; j++)
		xMatrix(i, j) = x_vars()(j);
	
	if (x_vars_size < x_mtx_size2)
		for (SizeType j = x_vars_size; j < x_mtx_size2; j++)
			xMatrix(i, j) = ValueType();

	yValues(i) = y;
}

template <typename T>
CDPL::Math::Matrix<typename CDPL::Math::MLRModel<T>::ValueType>&
CDPL::Math::MLRModel<T>::getXMatrix()
{
	return xMatrix;
}

template <typename T>
const CDPL::Math::Matrix<typename CDPL::Math::MLRModel<T>::ValueType>&
CDPL::Math::MLRModel<T>::getXMatrix() const
{
	return xMatrix;
}

template <typename T>
CDPL::Math::Vector<typename CDPL::Math::MLRModel<T>::ValueType>&
CDPL::Math::MLRModel<T>::getYValues()
{
	return yValues;
}

template <typename T>
const CDPL::Math::Vector<typename CDPL::Math::MLRModel<T>::ValueType>&
CDPL::Math::MLRModel<T>::getYValues() const
{
	return yValues;
}

template <typename T>
void CDPL::Math::MLRModel<T>::buildModel()
{
	static const ValueType TOLERANCE(1.0e-6);

	SizeType n = xMatrix.getSize1();
	SizeType m = xMatrix.getSize2();

	if (m == 0 || n == 0) 
		throw Base::CalculationFailed("MLRModel: empty data set");

	if (n != SizeType(yValues.getSize()))
		resizeDataSet(std::max(SizeType(yValues.getSize()), n), m); 

	svdU.resize(n, m, false);
	svdV.resize(m, m, false);
	svdW.resize(m, false);

	svdU = xMatrix;
	
	if (!svDecompose(svdU, svdW, svdV))
		throw Base::CalculationFailed("MLRModel: singular value decomposition failed");

	ValueType w_max = svdW(0);

	for (SizeType i = 1; i < m; i++)
		if (svdW(i) > w_max)
			w_max = svdW(i);

	ValueType tresh = TOLERANCE * w_max;

	for (SizeType i = 0; i < m; i++)
		if (svdW(i) < tresh)
			svdW(i) = 0;

	coefficients.resize(m, false);

	svSubstitute(svdU, svdW, svdV, yValues, coefficients);
}

template <typename T>
template <typename V>
typename CDPL::Math::MLRModel<T>::ValueType
CDPL::Math::MLRModel<T>::calcYValue(const VectorExpression<V>& x) const
{	
	if (SizeType(x().getSize()) != SizeType(coefficients.getSize()))
		throw Base::CalculationFailed("MLRModel: number of regression coefficients does not match number of independent variables");

	return innerProd(coefficients, x);
}

template <typename T>
template <typename V>
typename CDPL::Math::MLRModel<T>::ValueType
CDPL::Math::MLRModel<T>::operator()(const VectorExpression<V>& x) const
{	
	return calcYValue(x);
}

template <typename T>
const CDPL::Math::Vector<typename CDPL::Math::MLRModel<T>::ValueType>&
CDPL::Math::MLRModel<T>::getCoefficients() const
{
	return coefficients;
}

template <typename T>
typename CDPL::Math::MLRModel<T>::ValueType
CDPL::Math::MLRModel<T>::getChiSquare() const
{
	return chiSquare;
}

template <typename T>
typename CDPL::Math::MLRModel<T>::ValueType
CDPL::Math::MLRModel<T>::getGoodnessOfFit() const
{
	return Q;
}

template <typename T>
typename CDPL::Math::MLRModel<T>::ValueType
CDPL::Math::MLRModel<T>::getCorrelationCoefficient() const
{
	return r;
}

template <typename T>
typename CDPL::Math::MLRModel<T>::ValueType
CDPL::Math::MLRModel<T>::getStandardDeviation() const
{
	return stdDeviation;
}

template <typename T>
void CDPL::Math::MLRModel<T>::calcStatistics()
{
	ValueType mean_data_y = 0;
	ValueType mean_calc_y = 0;
	
	chiSquare = ValueType();

	SizeType m = xMatrix.getSize2();
	SizeType n = xMatrix.getSize1();

	if (m != SizeType(coefficients.getSize()))
		throw Base::CalculationFailed("MLRModel: number of independent variables does not match number of regression coefficients");

	if (n != SizeType(yValues.getSize()))
		throw Base::CalculationFailed("MLRModel: number of dependent variables does not match number of vectors with independent variables");

	calcYValues.resize(n);

	for (SizeType i = 0; i < n; i++) {
		ValueType data_y = yValues(i);
		ValueType calc_y = innerProd(row(xMatrix, i), coefficients);
		ValueType y_diff = data_y - calc_y;

		mean_data_y += data_y;
		mean_calc_y += calc_y;
		chiSquare += y_diff * y_diff;

		calcYValues(i) = calc_y;
	}

	mean_data_y /= n;
	mean_calc_y /= n;
	
	ValueType sxx = ValueType();
	ValueType syy = ValueType();
	ValueType sxy = ValueType();

	for (SizeType i = 0; i < n; i++) {
		ValueType xt = yValues(i) - mean_data_y;
		ValueType yt = calcYValues(i) - mean_calc_y;

		sxx += xt * xt;
		syy += yt * yt;
		sxy += xt * yt;
	}

	r = sxy / (TypeTraits<ValueType>::sqrt(sxx * syy) + std::numeric_limits<ValueType>::epsilon());

	stdDeviation = TypeTraits<ValueType>::sqrt(chiSquare / (n - m));

	Q = gammaQ(ValueType(n - 2) / 2, chiSquare / 2); 
}

#endif // CDPL_MATH_MLRMODEL_HPP


