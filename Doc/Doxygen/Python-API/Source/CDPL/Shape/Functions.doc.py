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
# \param res The alignment result.
# \param beta The aligned-side Tversky weighting factor.
# 
# \return The color aligned-normalized Tversky similarity score.
# 
def calcAlignedColorTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Returns the shape-only aligned-normalized Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param beta The aligned-side Tversky weighting factor.
# 
# \return The shape-only aligned-normalized Tversky similarity score.
# 
def calcAlignedShapeTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Returns the (shape + color) total-overlap aligned-normalized Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param beta The aligned-side Tversky weighting factor.
# 
# \return The total-overlap aligned-normalized Tversky similarity score.
# 
def calcAlignedTotalOverlapTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Returns the combined shape + color aligned-normalized Tversky score of <em>res</em>.
# 
# \param res The alignment result.
# \param beta The aligned-side Tversky weighting factor.
# 
# \return The aligned-normalized Tversky combo score (sum of shape and color aligned-Tversky scores).
# 
def calcAlignedTverskyComboScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief Calculates the affine transformations that align a Gaussian shape to its center of mass and back.
# 
# \param func The Gaussian shape function.
# \param to_ctr_xform The output transformation that places the shape at its center of mass with principal axes aligned to the coordinate axes.
# \param from_ctr_xform The output inverse transformation.
# \param mom_eq_thresh The relative threshold below which two principal moments are considered equal.
# 
# \return The perceived symmetry class of the shape (see namespace Shape.SymmetryClass).
# 
def calcCenterAlignmentTransforms(func: GaussianShapeFunction, to_ctr_xform: Math.Matrix4D, from_ctr_xform: Math.Matrix4D, mom_eq_thresh: float = 0.15) -> int: pass

##
# \brief Returns the color (pharmacophore) Tanimoto similarity score of <em>res</em>.
# 
# \param res The alignment result.
# 
# \return The color Tanimoto similarity score.
# 
def calcColorTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the color (pharmacophore) symmetric Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
# \return The color symmetric Tversky similarity score.
# 
def calcColorTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief Calculates the principal axes and principal moments of a quadrupole tensor.
# 
# \param quad_tensor The input symmetric quadrupole tensor.
# \param x_axis The output principal x-axis.
# \param y_axis The output principal y-axis.
# \param z_axis The output principal z-axis.
# \param moments The output principal moments.
# 
def calcPrincipalAxes(quad_tensor: Math.Matrix3D, x_axis: Math.Vector3D, y_axis: Math.Vector3D, z_axis: Math.Vector3D, moments: Math.Vector3D) -> None: pass

##
# \brief Calculates the eigen-decomposition of a 3x3 quadrupole tensor.
# 
# \param quad_tensor The input symmetric quadrupole tensor.
# \param eigen_vecs The output eigenvector matrix (columns are eigenvectors).
# \param eigen_vals The output eigenvalues.
# 
def calcQuadrupoleTensorEigenDecomposition(quad_tensor: Math.Matrix3D, eigen_vecs: Math.Matrix3D, eigen_vals: Math.Vector3D) -> None: pass

##
# \brief Returns the color (pharmacophore) reference-normalized Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The reference-side Tversky weighting factor.
# 
# \return The color reference-normalized Tversky similarity score.
# 
def calcReferenceColorTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the shape-only reference-normalized Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The reference-side Tversky weighting factor.
# 
# \return The shape-only reference-normalized Tversky similarity score.
# 
def calcReferenceShapeTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the (shape + color) total-overlap reference-normalized Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The reference-side Tversky weighting factor.
# 
# \return The total-overlap reference-normalized Tversky similarity score.
# 
def calcReferenceTotalOverlapTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the combined shape + color reference-normalized Tversky score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The reference-side Tversky weighting factor.
# 
# \return The reference-normalized Tversky combo score (sum of shape and color reference-Tversky scores).
# 
def calcReferenceTverskyComboScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief Returns the shape-only Tanimoto similarity score of <em>res</em>.
# 
# \param res The alignment result.
# 
# \return The shape-only Tanimoto similarity score.
# 
def calcShapeTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the shape-only symmetric Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
# \return The shape-only symmetric Tversky similarity score.
# 
def calcShapeTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief Returns the combined shape + color Tanimoto score of <em>res</em>.
# 
# \param res The alignment result.
# 
# \return The Tanimoto combo score (sum of shape and color Tanimoto scores).
# 
def calcTanimotoComboScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the (shape + color) total-overlap Tanimoto similarity score of <em>res</em>.
# 
# \param res The alignment result.
# 
# \return The total-overlap Tanimoto similarity score.
# 
def calcTotalOverlapTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief Returns the (shape + color) total-overlap symmetric Tversky similarity score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
# \return The total-overlap symmetric Tversky similarity score.
# 
def calcTotalOverlapTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief Returns the combined shape + color symmetric Tversky score of <em>res</em>.
# 
# \param res The alignment result.
# \param alpha The weight of the reference self-overlap contribution.
# \param beta The weight of the aligned self-overlap contribution.
# 
# \return The symmetric Tversky combo score (sum of shape and color Tversky scores).
# 
def calcTverskyComboScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief Centers <em>shape</em> at its centroid and aligns its principal axes with the coordinate axes.
# 
# \param shape The Gaussian shape to align (modified in place).
# \param func The associated Shape.GaussianShapeFunction used to compute the principal axes.
# \param back_xform The output transformation that maps the aligned shape back to its original frame.
# \param mom_eq_thresh The relative threshold below which two principal moments are considered equal.
# 
# \return The perceived symmetry class of the shape (see namespace Shape.SymmetryClass).
# 
def centerAndAlignPrincipalAxes(shape: GaussianShape, func: GaussianShapeFunction, back_xform: Math.Matrix4D, mom_eq_thresh: float = 0.15) -> int: pass

##
# \brief Builds a Gaussian shape from the atoms of <em>atoms</em> (using the default atom 3D coordinates accessor).
# 
# \param atoms The atom container.
# \param shape The output Gaussian shape.
# \param append If <tt>True</tt>, the new elements are appended to <em>shape</em>. Otherwise, <em>shape</em> is cleared first.
# \param radius The sphere radius to use for all atoms, or a negative value to use atom-specific Van der Waals radii.
# \param inc_h If <tt>True</tt>, hydrogen atoms are also included in the shape.
# \param p The Gaussian hardness used for all generated spheres.
# 
def generateGaussianShape(atoms: Chem.AtomContainer, shape: GaussianShape, append: bool = False, radius: float = -1.0, inc_h: bool = False, p: float = 2.7) -> None: pass

##
# \brief Builds a Gaussian shape from the atoms of <em>atoms</em> using <em>coords_func</em> to retrieve atom positions.
# 
# \param atoms The atom container.
# \param shape The output Gaussian shape.
# \param coords_func The function used to retrieve atom 3D-coordinates.
# \param append If <tt>True</tt>, the new elements are appended to <em>shape</em>. Otherwise, <em>shape</em> is cleared first.
# \param radius The sphere radius to use for all atoms, or a negative value to use atom-specific Van der Waals radii.
# \param inc_h If <tt>True</tt>, hydrogen atoms are also included in the shape.
# \param p The Gaussian hardness used for all generated spheres.
# 
def generateGaussianShape(atoms: Chem.AtomContainer, shape: GaussianShape, coords_func: Chem.Atom3DCoordinatesFunction, append: bool = False, radius: float = -1.0, inc_h: bool = False, p: float = 2.7) -> None: pass

##
# \brief Builds a Gaussian shape from the pharmacophore features of <em>features</em>.
# 
# \param features The feature container.
# \param shape The output Gaussian shape.
# \param append If <tt>True</tt>, the new elements are appended to <em>shape</em>. Otherwise, <em>shape</em> is cleared first.
# \param radius The sphere radius to use for all features, or a negative value to use feature-specific tolerances.
# \param inc_xv If <tt>True</tt>, exclusion-volume features are also included in the shape.
# \param p The Gaussian hardness used for all generated spheres.
# 
def generateGaussianShape(features: Pharm.FeatureContainer, shape: GaussianShape, append: bool = False, radius: float = -1.0, inc_xv: bool = False, p: float = 5.0) -> None: pass

##
# \brief Converts an affine 4x4 transformation matrix to a quaternion-plus-translation representation.
# 
# \param mtx The input transformation matrix.
# \param quat The output Shape.QuaternionTransformation (<em>4</em> quaternion + <em>3</em> translation components).
# 
def matrixToQuaternion(mtx: Math.Matrix4D, quat: Math.Vector7D) -> None: pass

##
# \brief Classifies the rotational symmetry of a shape from its principal moments.
# 
# \param moments The principal moments.
# \param eq_thresh The relative threshold below which two moments are considered equal.
# 
# \return The perceived symmetry class (see namespace Shape.SymmetryClass).
# 
def perceiveSymmetryClass(moments: Math.Vector3D, eq_thresh: float = 0.15) -> int: pass

##
# \brief Converts a quaternion-plus-translation representation back to an affine 4x4 transformation matrix.
# 
# \param quat The input Shape.QuaternionTransformation (<em>4</em> quaternion + <em>3</em> translation components).
# \param mtx The output transformation matrix.
# 
def quaternionToMatrix(quat: Math.Vector7D, mtx: Math.Matrix4D) -> None: pass

##
# \brief Applies an affine transformation to the element positions of <em>shape</em>.
# 
# \param shape The Gaussian shape to transform (modified in place).
# \param xform The 4x4 transformation matrix.
# 
def transform(shape: GaussianShape, xform: Math.Matrix4D) -> None: pass
