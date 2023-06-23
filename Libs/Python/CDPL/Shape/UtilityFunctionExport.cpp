/* 
 * UtilityFunctionExport.cpp 
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

#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "FunctionExports.hpp"


void CDPLPythonShape::exportUtilityFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("calcQuadrupoleTensorEigenDecomposition", &Shape::calcQuadrupoleTensorEigenDecomposition,
                (python::arg("quad_tensor"), python::arg("eigen_vecs"), python::arg("eigen_vals")));
    python::def("calcPrincipalAxes", &Shape::calcPrincipalAxes,
                (python::arg("quad_tensor"), python::arg("x_axis"), python::arg("y_axis"), python::arg("z_axis"), python::arg("moments")));
    python::def("perceiveSymmetryClass", &Shape::perceiveSymmetryClass,
                (python::arg("moments"), python::arg("eq_thresh") = 0.15));
    python::def("calcCenterAlignmentTransforms", &Shape::calcCenterAlignmentTransforms,
                (python::arg("func"), python::arg("to_ctr_xform"), python::arg("from_ctr_xform"), python::arg("mom_eq_thresh") = 0.15));
    python::def("matrixToQuaternion", &Shape::matrixToQuaternion, (python::arg("mtx"), python::arg("quat")));
    python::def("quaternionToMatrix", &Shape::quaternionToMatrix, (python::arg("quat"), python::arg("mtx")));
}
