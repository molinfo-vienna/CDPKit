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
# \brief Returns the color (pharmacophore) aligned-normalized Tversky similarity score of <em>res</em>.
# 
# \param beta The aligned-side Tversky weighting factor.
# 
def calcAlignedColorTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Returns the shape-only aligned-normalized Tversky similarity score of <em>res</em>.
# 
# \param beta The aligned-side Tversky weighting factor.
# 
def calcAlignedShapeTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Returns the (shape + color) total-overlap aligned-normalized Tversky similarity score of <em>res</em>.
# 
# \param beta The aligned-side Tversky weighting factor.
# 
def calcAlignedTotalOverlapTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Returns the combined shape + color aligned-normalized Tversky score of <em>res</em>.
# 
# \param beta The aligned-side Tversky weighting factor.
# 
def calcAlignedTverskyComboScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief 
# \param func 
# \param to_ctr_xform 
# \param from_ctr_xform 
# \param mom_eq_thresh 
# \return 
#
def calcCenterAlignmentTransforms(func: GaussianShapeFunction, to_ctr_xform: Math.Matrix4D, from_ctr_xform: Math.Matrix4D, mom_eq_thresh: float = 0.15) -> int: pass

##
# \brief Returns the color (pharmacophore) Tanimoto similarity score of <em>res</em>.
# 
def calcColorTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the color (pharmacophore) symmetric Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
def calcColorTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief 
# \param quad_tensor 
# \param x_axis 
# \param y_axis 
# \param z_axis 
# \param moments 
#
def calcPrincipalAxes(quad_tensor: Math.Matrix3D, x_axis: Math.Vector3D, y_axis: Math.Vector3D, z_axis: Math.Vector3D, moments: Math.Vector3D) -> None: pass

##
# \brief 
# \param quad_tensor 
# \param eigen_vecs 
# \param eigen_vals 
#
def calcQuadrupoleTensorEigenDecomposition(quad_tensor: Math.Matrix3D, eigen_vecs: Math.Matrix3D, eigen_vals: Math.Vector3D) -> None: pass

##
# \brief Returns the color (pharmacophore) reference-normalized Tversky similarity score of <em>res</em>.
# 
# \param alpha The reference-side Tversky weighting factor.
# 
def calcReferenceColorTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the shape-only reference-normalized Tversky similarity score of <em>res</em>.
# 
# \param alpha The reference-side Tversky weighting factor.
# 
def calcReferenceShapeTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the (shape + color) total-overlap reference-normalized Tversky similarity score of <em>res</em>.
# 
# \param alpha The reference-side Tversky weighting factor.
# 
def calcReferenceTotalOverlapTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the combined shape + color reference-normalized Tversky score of <em>res</em>.
# 
# \param alpha The reference-side Tversky weighting factor.
# 
def calcReferenceTverskyComboScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the shape-only Tanimoto similarity score of <em>res</em>.
# 
def calcShapeTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the shape-only symmetric Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
def calcShapeTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief Returns the combined shape + color Tanimoto score of <em>res</em>.
# 
def calcTanimotoComboScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the (shape + color) total-overlap Tanimoto similarity score of <em>res</em>.
# 
def calcTotalOverlapTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the (shape + color) total-overlap symmetric Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
def calcTotalOverlapTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief Returns the combined shape + color symmetric Tversky score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
def calcTverskyComboScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief 
# \param shape 
# \param func 
# \param back_xform 
# \param mom_eq_thresh 
# \return 
#
def centerAndAlignPrincipalAxes(shape: GaussianShape, func: GaussianShapeFunction, back_xform: Math.Matrix4D, mom_eq_thresh: float = 0.15) -> int: pass

##
# \brief 
# \param atoms 
# \param shape 
# \param append 
# \param radius 
# \param inc_h 
# \param p 
#
def generateGaussianShape(atoms: Chem.AtomContainer, shape: GaussianShape, append: bool = False, radius: float = -1.0, inc_h: bool = False, p: float = 2.7) -> None: pass

##
# \brief 
# \param atoms 
# \param shape 
# \param coords_func 
# \param append 
# \param radius 
# \param inc_h 
# \param p 
#
def generateGaussianShape(atoms: Chem.AtomContainer, shape: GaussianShape, coords_func: Chem.Atom3DCoordinatesFunction, append: bool = False, radius: float = -1.0, inc_h: bool = False, p: float = 2.7) -> None: pass

##
# \brief 
# \param features 
# \param shape 
# \param append 
# \param radius 
# \param inc_xv 
# \param p 
#
def generateGaussianShape(features: Pharm.FeatureContainer, shape: GaussianShape, append: bool = False, radius: float = -1.0, inc_xv: bool = False, p: float = 5.0) -> None: pass

##
# \brief 
# \param mtx 
# \param quat 
#
def matrixToQuaternion(mtx: Math.Matrix4D, quat: Math.Vector7D) -> None: pass

##
# \brief 
# \param moments 
# \param eq_thresh 
# \return 
#
def perceiveSymmetryClass(moments: Math.Vector3D, eq_thresh: float = 0.15) -> int: pass

##
# \brief 
# \param quat 
# \param mtx 
#
def quaternionToMatrix(quat: Math.Vector7D, mtx: Math.Matrix4D) -> None: pass

##
# \brief 
# \param shape 
# \param xform 
#
def transform(shape: GaussianShape, xform: Math.Matrix4D) -> None: pass
