/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ClassExports.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_PYTHON_MATH_CLASSEXPORTS_HPP
#define CDPL_PYTHON_MATH_CLASSEXPORTS_HPP


namespace CDPLPythonMath
{

	void exportVectorExpressionTypes();
	void exportMatrixExpressionTypes();
	void exportQuaternionExpressionTypes();
	void exportGridExpressionTypes();

	void exportVectorTypes();
	void exportSparseVectorTypes();
	void exportCVectorTypes1();
	void exportCVectorTypes2();
	void exportCVectorTypes3();
	void exportScalarVectorTypes();
	void exportZeroVectorTypes();
	void exportUnitVectorTypes();
	
	void exportMatrixTypes();
	void exportSparseMatrixTypes();
	void exportTranslationMatrixTypes();
	void exportScalingMatrixTypes();
	void exportRotationMatrixTypes();
	void exportCMatrixTypes1();
	void exportCMatrixTypes2();
	void exportCMatrixTypes3();
	void exportZeroMatrixTypes();
	void exportScalarMatrixTypes();
	void exportIdentityMatrixTypes();
	
	void exportQuaternionTypes();
	void exportRealQuaternionTypes();
	
	void exportGridTypes();
	void exportZeroGridTypes();
	void exportScalarGridTypes();
	void exportRegularSpatialGridTypes();

	void exportRange();
	void exportSlice();
	
	void exportVectorSliceTypes();
	void exportConstVectorSliceTypes();
	void exportVectorRangeTypes();
	void exportConstVectorRangeTypes();

	void exportMatrixRangeTypes();
	void exportConstMatrixRangeTypes();
	void exportMatrixSliceTypes();
	void exportConstMatrixSliceTypes();
	void exportMatrixRowTypes();
	void exportConstMatrixRowTypes();
	void exportMatrixColumnTypes();
	void exportConstMatrixColumnTypes();

	void exportVectorQuaternionAdapterTypes();
	void exportConstVectorQuaternionAdapterTypes();
	void exportHomogenousCoordsAdapterTypes();
	void exportConstHomogenousCoordsAdapterTypes();
		
	void exportTriangularMatrixTypes();
	void exportTriangularMatrixAdapterTypes1();
	void exportTriangularMatrixAdapterTypes2();
	void exportTriangularMatrixAdapterTypes3();
	void exportTriangularMatrixAdapterTypes4();
	void exportMatrixTransposeTypes();
	void exportConstMatrixTransposeTypes();
	
	void exportQuaternionAdapterTypes();

	void exportMLRModelTypes();
	void exportBFGSMinimizerTypes();
	void exportKabschAlgorithmTypes();
	void exportVectorArrayAlignmentCalculatorTypes();

	void exportVectorArrayTypes();

	void exportBoostFunctionWrappers();
}

#endif // CDPL_PYTHON_MATH_CLASSEXPORTS_HPP
