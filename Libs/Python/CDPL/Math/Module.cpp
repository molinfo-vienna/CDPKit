/* 
 * Module.cpp 
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


#include <boost/python.hpp>
#include "CDPL/Config.hpp"

#include "ClassExports.hpp"
#include "FunctionExports.hpp"
#include "ConverterRegistration.hpp"

#ifdef HAVE_NUMPY
# include "NumPy.hpp"
#endif


BOOST_PYTHON_MODULE(_math)
{
    using namespace CDPLPythonMath;

#ifdef HAVE_NUMPY
    NumPy::import();
#endif

    exportVectorExpressionTypes();
    exportMatrixExpressionTypes();
    exportQuaternionExpressionTypes();
    exportGridExpressionTypes();

    exportVectorTypes();
    exportSparseVectorTypes();
    exportCVectorTypes1();
    exportCVectorTypes2();
    exportCVectorTypes3();
    exportScalarVectorTypes();
    exportZeroVectorTypes();
    exportUnitVectorTypes();
    
    exportMatrixTypes();
    exportSparseMatrixTypes();
    exportTranslationMatrixTypes();
    exportScalingMatrixTypes();
    exportRotationMatrixTypes();
    exportCMatrixTypes1();
    exportCMatrixTypes2();
    exportCMatrixTypes3();
    exportZeroMatrixTypes();
    exportScalarMatrixTypes();
    exportIdentityMatrixTypes();
            
    exportQuaternionTypes();
    exportRealQuaternionTypes();

    exportGridTypes();
    exportZeroGridTypes();
    exportScalarGridTypes();
    exportRegularSpatialGridTypes();

    exportRange();
    exportSlice();

    exportConstVectorSliceTypes();
    exportVectorSliceTypes();
    exportConstVectorRangeTypes();
    exportVectorRangeTypes();

    exportConstMatrixRangeTypes();
    exportMatrixRangeTypes();
    exportConstMatrixSliceTypes();
    exportMatrixSliceTypes();
    exportConstMatrixRowTypes();
    exportMatrixRowTypes();
    exportConstMatrixColumnTypes();
    exportMatrixColumnTypes();

    exportVectorQuaternionAdapterTypes();
    exportConstVectorQuaternionAdapterTypes();
    exportHomogenousCoordsAdapterTypes();
    exportConstHomogenousCoordsAdapterTypes();

    exportTriangularMatrixTypes();
    exportTriangularMatrixAdapterTypes1();
    exportTriangularMatrixAdapterTypes2();
    exportTriangularMatrixAdapterTypes3();
    exportTriangularMatrixAdapterTypes4();
    exportConstMatrixTransposeTypes();
    exportMatrixTransposeTypes();

    exportQuaternionAdapterTypes();

    exportVectorArrayTypes();
    exportMLRModelTypes();
    exportBFGSMinimizerTypes();
    exportKabschAlgorithmTypes();
    exportVectorArrayAlignmentCalculatorTypes();

    exportVectorFunctions();
    exportMatrixFunctions();
    exportQuaternionFunctions();
    exportGridFunctions();
    exportRegularSpatialGridFunctions();
    exportSpecialFunctions();
    exportVectorArrayFunctions();

    exportFunctionWrappers();

    registerToPythonConverters();

    registerFromPythonToCVectorConverters();
    registerFromPythonToVectorConverters();
    registerFromPythonToCMatrixConverters();
    registerFromPythonToMatrixConverters();
    registerFromPythonToGridConverters();
    registerFromPythonToQuaternionConverters();
    registerFromPythonToVectorArrayConverters();
    registerFromPythonToExpressionPointerConverters();
    registerFromPythonToAnyConverters();
}
