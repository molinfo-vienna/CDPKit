/* 
 * UtilityFunctions.cpp 
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

 
#include "StaticInit.hpp"

#include <utility>
#include <algorithm>

#include "CDPL/Shape/UtilityFunctions.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/SymmetryClass.hpp"
#include "CDPL/Math/JacobiDiagonalization.hpp"
#include "CDPL/Math/MatrixProxy.hpp"
#include "CDPL/Math/AffineTransform.hpp"


using namespace CDPL;


void Shape::calcQuadrupoleTensorEigenDecomposition(const Math::Matrix3D& quad_tensor, Math::Matrix3D& eigen_vecs,
                           Math::Vector3D& eigen_vals)
{
    Math::Matrix3D tmp_tensor(quad_tensor);
    
    jacobiDiagonalize(tmp_tensor, eigen_vals, eigen_vecs);
}

void Shape::calcPrincipalAxes(const Math::Matrix3D& quad_tensor, Math::Vector3D& x_axis, Math::Vector3D& y_axis,
                  Math::Vector3D& z_axis, Math::Vector3D& moments)
{
    Math::Matrix3D eigen_vecs;
    
    calcQuadrupoleTensorEigenDecomposition(quad_tensor, eigen_vecs, moments);

    Math::Vector3D::Pointer moments_data = moments.getData();
    std::pair<double, int> ordered_moments[3] = {
        std::make_pair(moments_data[0], 0),
        std::make_pair(moments_data[1], 1),
        std::make_pair(moments_data[2], 2)
    };

    std::sort(ordered_moments, ordered_moments + 3);

    moments_data[0] = ordered_moments[2].first;
    moments_data[1] = ordered_moments[1].first;
    moments_data[2] = ordered_moments[0].first;
    
    x_axis.assign(column(eigen_vecs, ordered_moments[2].second));
    y_axis.assign(column(eigen_vecs, ordered_moments[1].second));
    z_axis.assign(crossProd(x_axis, y_axis));
    y_axis.assign(crossProd(z_axis, x_axis));

    x_axis /= length(x_axis);
    y_axis /= length(y_axis);
    z_axis /= length(z_axis);
}

unsigned int Shape::perceiveSymmetryClass(const Math::Vector3D& moments, double eq_thresh)
{
    unsigned int sym_flags = 0;

    for (std::size_t i = 0; i < 2; i++)
        if (((moments[i] - moments[i + 1]) / moments[i]) <= eq_thresh)
            sym_flags |= (1 << i);

    switch (sym_flags) {

        case 0:
            return SymmetryClass::ASYMMETRIC;

        case 0b01:
            return SymmetryClass::PROLATE;

        case 0b10:
            return SymmetryClass::OBLATE;

        case 0b11:
            return SymmetryClass::SPHERICAL;

        default:
            break;
    }

    return SymmetryClass::UNDEF;
}

unsigned int Shape::calcCenterAlignmentTransforms(const Shape::GaussianShapeFunction& func, Math::Matrix4D& to_ctr_xform,
                                                  Math::Matrix4D& from_ctr_xform, double mom_eq_thresh)
{
    if (!func.getShape() || func.getShape()->getNumElements() == 0) { // sanity check
        to_ctr_xform.assign(Math::IdentityMatrix<double>(4, 4));
        from_ctr_xform.assign(Math::IdentityMatrix<double>(4, 4));

        return SymmetryClass::UNDEF;
    }

    Math::Vector3D ctr, x_axis, y_axis, z_axis, moments;
    Math::Matrix3D quad_tensor;

    func.calcCentroid(ctr);
    func.calcQuadrupoleTensor(ctr, quad_tensor);

    calcPrincipalAxes(quad_tensor, x_axis, y_axis, z_axis, moments);
    
    Math::Matrix4D::ArrayPointer xform_data = from_ctr_xform.getData();
    
    xform_data[0][0] = x_axis(0);
    xform_data[1][0] = x_axis(1);
    xform_data[2][0] = x_axis(2);
    
    xform_data[0][1] = y_axis(0);
    xform_data[1][1] = y_axis(1);
    xform_data[2][1] = y_axis(2);
    
    xform_data[0][2] = z_axis(0);
    xform_data[1][2] = z_axis(1);
    xform_data[2][2] = z_axis(2);

    xform_data[0][3] = ctr(0);
    xform_data[1][3] = ctr(1);
    xform_data[2][3] = ctr(2);

    xform_data[3][0] = 0.0;
    xform_data[3][1] = 0.0;
    xform_data[3][2] = 0.0;
    xform_data[3][3] = 1.0;

    xform_data = to_ctr_xform.getData();

    xform_data[0][0] = x_axis(0);
    xform_data[0][1] = x_axis(1);
    xform_data[0][2] = x_axis(2);
    xform_data[0][3] = 0.0;
    
    xform_data[1][0] = y_axis(0);
    xform_data[1][1] = y_axis(1);
    xform_data[1][2] = y_axis(2);
    xform_data[1][3] = 0.0;
    
    xform_data[2][0] = z_axis(0);
    xform_data[2][1] = z_axis(1);
    xform_data[2][2] = z_axis(2);
    xform_data[2][3] = 0.0;

    xform_data[3][0] = 0.0;
    xform_data[3][1] = 0.0;
    xform_data[3][2] = 0.0;
    xform_data[3][3] = 1.0;

    to_ctr_xform = to_ctr_xform * Math::TranslationMatrix<double>(4, -ctr(0), -ctr(1), -ctr(2));

    return perceiveSymmetryClass(moments, mom_eq_thresh);
}
    
void Shape::matrixToQuaternion(const Math::Matrix4D& mtx, QuaternionTransformation& quat)
{
    Math::Matrix4D::ConstArrayPointer mtx_data = mtx.getData();
    QuaternionTransformation::Pointer quat_data = quat.getData();
    Math::Matrix4D tmp;
    Math::Matrix4D::ArrayPointer tmp_data = tmp.getData();
    Math::Vector4D eigen_vals;
    Math::Vector4D::ConstPointer eigen_vals_data = eigen_vals.getData();
    Math::Matrix4D eigen_vecs;
    Math::Matrix4D::ConstArrayPointer eigen_vecs_data = eigen_vecs.getData();

    tmp_data[0][0] = (mtx_data[0][0] - mtx_data[1][1] - mtx_data[2][2]) / 3.0;
    tmp_data[0][1] = (mtx_data[0][1] + mtx_data[1][0]) / 3.0;
    tmp_data[0][2] = (mtx_data[0][2] + mtx_data[2][0]) / 3.0;
    tmp_data[0][3] = (mtx_data[2][1] - mtx_data[1][2]) / 3.0;
    
    tmp_data[1][0] = tmp_data[0][1];
    tmp_data[1][1] = (mtx_data[1][1] - mtx_data[0][0] - mtx_data[2][2]) / 3.0;
    tmp_data[1][2] = (mtx_data[1][2] + mtx_data[2][1]) / 3.0;
    tmp_data[1][3] = (mtx_data[0][2] - mtx_data[2][0]) / 3.0;
    
    tmp_data[2][0] = tmp_data[0][2];
    tmp_data[2][1] = tmp_data[1][2];
    tmp_data[2][2] = (mtx_data[2][2] - mtx_data[0][0] - mtx_data[1][1]) / 3.0;
    tmp_data[2][3] = (mtx_data[1][0] - mtx_data[0][1]) / 3.0;

    tmp_data[3][0] = tmp_data[0][3];
    tmp_data[3][1] = tmp_data[1][3];
    tmp_data[3][2] = tmp_data[2][3];
    tmp_data[3][3] = (mtx_data[0][0] + mtx_data[1][1] + mtx_data[2][2]) / 3.0;
    
    jacobiDiagonalize(tmp, eigen_vals, eigen_vecs);

    std::size_t largest_eval_idx = 0;

    for (std::size_t i = 1; i < 4; i++)
        if (eigen_vals_data[i] > eigen_vals_data[largest_eval_idx])
            largest_eval_idx = i;

    quat_data[0] = eigen_vecs_data[3][largest_eval_idx];
    quat_data[1] = eigen_vecs_data[0][largest_eval_idx];
    quat_data[2] = eigen_vecs_data[1][largest_eval_idx];
    quat_data[3] = eigen_vecs_data[2][largest_eval_idx];
    quat_data[4] = mtx_data[0][3];
    quat_data[5] = mtx_data[1][3];
    quat_data[6] = mtx_data[2][3];
}

void Shape::quaternionToMatrix(const QuaternionTransformation& quat, Math::Matrix4D& mtx)
{
    Math::Matrix4D::ArrayPointer mtx_data = mtx.getData();
    QuaternionTransformation::ConstPointer quat_data = quat.getData();

    mtx_data[0][0] = (quat_data[0] * quat_data[0] + quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3]); // a^2 + b^2 - c^2 - d^2
    mtx_data[0][1] = 2.0 * (quat_data[1] * quat_data[2] - quat_data[0] * quat_data[3]); // 2(bc - ad)
    mtx_data[0][2] = 2.0 * (quat_data[1] * quat_data[3] + quat_data[0] * quat_data[2]); // 2(bd + ac)
    mtx_data[0][3] = quat_data[4];
    mtx_data[1][0] = 2.0 * (quat_data[1] * quat_data[2] + quat_data[0] * quat_data[3]); // 2(bc + ad)
    mtx_data[1][1] = (quat_data[0] * quat_data[0] - quat_data[1] * quat_data[1] + quat_data[2] * quat_data[2] - quat_data[3] * quat_data[3]); // a^2 - b^2 + c^2 - d^2
    mtx_data[1][2] = 2.0 * (quat_data[2] * quat_data[3] - quat_data[0] * quat_data[1]); // 2(cd - ab)
    mtx_data[1][3] = quat_data[5];
    mtx_data[2][0] = 2.0 * (quat_data[1] * quat_data[3] - quat_data[0] * quat_data[2]); // 2(bd - ac)
    mtx_data[2][1] = 2.0 * (quat_data[2] * quat_data[3] + quat_data[0] * quat_data[1]); // 2(cd + ab)
    mtx_data[2][2] = (quat_data[0] * quat_data[0] - quat_data[1] * quat_data[1] - quat_data[2] * quat_data[2] + quat_data[3] * quat_data[3]); // a^2 - b^2 - c^2 + d^2
    mtx_data[2][3] = quat_data[6];
    mtx_data[3][0] = 0.0;
    mtx_data[3][1] = 0.0;
    mtx_data[3][2] = 0.0;
    mtx_data[3][3] = 1.0;
}
