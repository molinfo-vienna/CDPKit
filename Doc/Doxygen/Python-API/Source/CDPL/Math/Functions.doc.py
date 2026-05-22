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
# \param e1 
# \param e2 
# \param sd 
# \param clamp 
# \return 
#
def angleCos(e1: ConstDVectorExpression, e2: ConstDVectorExpression, sd: float, clamp: bool = True) -> float: pass

##
# \brief 
# \param e1 
# \param e2 
# \param sd 
# \param clamp 
# \return 
#
def angleCos(e1: ConstFVectorExpression, e2: ConstFVectorExpression, sd: float, clamp: bool = True) -> float: pass

##
# \brief 
# \param e1 
# \param e2 
# \param sd 
# \param clamp 
# \return 
#
def angleCos(e1: ConstLVectorExpression, e2: ConstLVectorExpression, sd: int, clamp: bool = True) -> int: pass

##
# \brief 
# \param e1 
# \param e2 
# \param sd 
# \param clamp 
# \return 
#
def angleCos(e1: ConstULVectorExpression, e2: ConstULVectorExpression, sd: int, clamp: bool = True) -> int: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector2DArray, ctr: Vector2D) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector2FArray, ctr: Vector2F) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector2LArray, ctr: Vector2L) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector2ULArray, ctr: Vector2UL) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector3DArray, ctr: Vector3D) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector3FArray, ctr: Vector3F) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector3LArray, ctr: Vector3L) -> bool: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector3ULArray, ctr: Vector3UL) -> bool: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector2DArray, va2: Vector2DArray) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector2DArray, va2: Vector2DArray, va1_xform: Matrix3D) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector2FArray, va2: Vector2FArray) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector2FArray, va2: Vector2FArray, va1_xform: Matrix3F) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector2LArray, va2: Vector2LArray) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector2LArray, va2: Vector2LArray, va1_xform: Matrix3L) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector2ULArray, va2: Vector2ULArray) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector2ULArray, va2: Vector2ULArray, va1_xform: Matrix3UL) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector3DArray, va2: Vector3DArray) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector3DArray, va2: Vector3DArray, va1_xform: Matrix4D) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector3FArray, va2: Vector3FArray) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector3FArray, va2: Vector3FArray, va1_xform: Matrix4F) -> float: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector3LArray, va2: Vector3LArray) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector3LArray, va2: Vector3LArray, va1_xform: Matrix4L) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector3ULArray, va2: Vector3ULArray) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector3ULArray, va2: Vector3ULArray, va1_xform: Matrix4UL) -> int: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstDMatrixExpression, i: int) -> ConstDMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstFMatrixExpression, i: int) -> ConstFMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstLMatrixExpression, i: int) -> ConstLMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstULMatrixExpression, i: int) -> ConstULMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: DMatrixExpression, i: int) -> DMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: FMatrixExpression, i: int) -> FMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: LMatrixExpression, i: int) -> LMatrixColumn: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ULMatrixExpression, i: int) -> ULMatrixColumn: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstFGridExpression) -> ConstFGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def conj(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def cross(e: ConstDVectorExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def cross(e: ConstFVectorExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def cross(e: ConstLVectorExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def cross(e: ConstULVectorExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def crossProd(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def crossProd(e1: ConstFVectorExpression, e2: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def crossProd(e1: ConstLVectorExpression, e2: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def crossProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def diag(e: ConstDVectorExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def diag(e: ConstFVectorExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def diag(e: ConstLVectorExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def diag(e: ConstULVectorExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstDGridExpression, e2: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstDMatrixExpression, e2: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstDQuaternionExpression, e2: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstFGridExpression, e2: ConstFGridExpression) -> ConstFGridExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstFMatrixExpression, e2: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstFQuaternionExpression, e2: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstFVectorExpression, e2: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstLMatrixExpression, e2: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstLQuaternionExpression, e2: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstLVectorExpression, e2: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstULMatrixExpression, e2: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstULQuaternionExpression, e2: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstDGridExpression, e2: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstDMatrixExpression, e2: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstDQuaternionExpression, e2: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstFGridExpression, e2: ConstFGridExpression) -> ConstFGridExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstFMatrixExpression, e2: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstFQuaternionExpression, e2: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstFVectorExpression, e2: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstLMatrixExpression, e2: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstLQuaternionExpression, e2: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstLVectorExpression, e2: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstULMatrixExpression, e2: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstULQuaternionExpression, e2: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstDGridExpression, e2: ConstDGridExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstDMatrixExpression, e2: ConstDMatrixExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstDQuaternionExpression, e2: ConstDQuaternionExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstDVectorExpression, e2: ConstDVectorExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstFGridExpression, e2: ConstFGridExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstFMatrixExpression, e2: ConstFMatrixExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstFQuaternionExpression, e2: ConstFQuaternionExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstFVectorExpression, e2: ConstFVectorExpression, eps: float) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstLMatrixExpression, e2: ConstLMatrixExpression, eps: int) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstLQuaternionExpression, e2: ConstLQuaternionExpression, eps: int) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstLVectorExpression, e2: ConstLVectorExpression, eps: int) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstULMatrixExpression, e2: ConstULMatrixExpression, eps: int) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstULQuaternionExpression, e2: ConstULQuaternionExpression, eps: int) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstULVectorExpression, e2: ConstULVectorExpression, eps: int) -> bool: pass

##
# \brief Computes the factorial \f$ n! \f$ of the non-negative integer <em>n</em>.
# 
# \param n The non-negative integer for which to compute the factorial.
# 
# \return The computed factorial of <em>n</em>.
# 
def factorial(n: int) -> int: pass

##
# \brief Computes the incomplete gamma function \f$ Q(a, x) = 1 - P(a, x) \f$ (see [\ref NRIC] for details).
# 
# \param a The function argument <em>a</em>.
# \param x The function argument <em>x</em>.
# 
# \return The computed value of the incomplete gamma function.
# 
def gammaQ(a: float, x: float) -> float: pass

##
# \brief Computes the generalized bell function \f$ Bell(x) = \frac{1}{1 + |\frac{x-c}{a}|^{2b}} \f$ at <em>x</em>.
# 
# \param x The generalized bell function argument
# \param a Controls the width of the curve at \f$f(x) = 0.5 \f$.
# \param b Controls the slope of the curve at \f$ x = c - a \f$ and \f$ x = c + a \f$.
# \param c Locates the center of the curve.
# 
# \return The generalized bell function value at <em>x</em>.
# 
def generalizedBell(x: float, a: float, b: float, c: float) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstFGridExpression) -> ConstFGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def herm(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: ConstDVectorExpression) -> ConstDHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: ConstFVectorExpression) -> ConstFHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: ConstLVectorExpression) -> ConstLHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: ConstULVectorExpression) -> ConstULHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: DVectorExpression) -> DHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: FVectorExpression) -> FHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: LVectorExpression) -> LHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def homog(e: ULVectorExpression) -> ULHomogenousCoordsAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstFGridExpression) -> ConstFGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def innerProd(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def innerProd(e1: ConstFVectorExpression, e2: ConstFVectorExpression) -> float: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def innerProd(e1: ConstLVectorExpression, e2: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def innerProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param grid 
# \param pos 
# \param local_pos 
# \return 
#
def interpolateTrilinear(grid: DRegularSpatialGrid, pos: Vector3D, local_pos: bool) -> float: pass

##
# \brief 
# \param grid 
# \param pos 
# \param local_pos 
# \return 
#
def interpolateTrilinear(grid: FRegularSpatialGrid, pos: Vector3F, local_pos: bool) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def inv(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def inv(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def inv(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def inv(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstDMatrixExpression, c: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstFMatrixExpression, c: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstLMatrixExpression, c: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstULMatrixExpression, c: ULMatrixExpression) -> bool: pass

##
# \brief 
# \param c 
# \return 
#
def invert(c: DMatrixExpression) -> bool: pass

##
# \brief 
# \param c 
# \return 
#
def invert(c: FMatrixExpression) -> bool: pass

##
# \brief 
# \param c 
# \return 
#
def invert(c: LMatrixExpression) -> bool: pass

##
# \brief 
# \param c 
# \return 
#
def invert(c: ULMatrixExpression) -> bool: pass

##
# \brief Computes all eigenvalues and eigenvectors of a real symmetric matrix <em>an</em> using Jacobi's algorithm [\ref WJACO ].
# 
# On output, elements of <em>a</em> above the diagonal are destroyed. The vector <em>d</em> returns the eigenvalues of <em>a</em>. The columns of matrix <em>v</em> contain, on output, the normalized eigenvectors of <em>a</em>. For implementation details see [\ref NRIC].
# 
# \param a The real symmetric matrix for which to compute eigenvalues and eigenvectors.
# \param d The output vector which will contain the eigenvalues of <em>a</em>.
# \param v The matrix whose columns will contain the normalized eigenvectors of <em>a</em>.
# \param max_iter The maximum number of iterations to perform.
# 
# \return <tt>True</tt> if <em>a</em> is a non-empty symmetric matrix and convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <em>a</em> is symmetric and non-empty, i.e. <tt>a().getSize1() == a().getSize2() && a().getSize1() != 0</tt>, and furthermore <tt>d().getSize() >= a().getSize1()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def jacobiDiagonalize(a: DMatrixExpression, d: DVectorExpression, v: DMatrixExpression, max_iter: int = 50) -> bool: pass

##
# \brief Computes all eigenvalues and eigenvectors of a real symmetric matrix <em>an</em> using Jacobi's algorithm [\ref WJACO ].
# 
# On output, elements of <em>a</em> above the diagonal are destroyed. The vector <em>d</em> returns the eigenvalues of <em>a</em>. The columns of matrix <em>v</em> contain, on output, the normalized eigenvectors of <em>a</em>. For implementation details see [\ref NRIC].
# 
# \param a The real symmetric matrix for which to compute eigenvalues and eigenvectors.
# \param d The output vector which will contain the eigenvalues of <em>a</em>.
# \param v The matrix whose columns will contain the normalized eigenvectors of <em>a</em>.
# \param max_iter The maximum number of iterations to perform.
# 
# \return <tt>True</tt> if <em>a</em> is a non-empty symmetric matrix and convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <em>a</em> is symmetric and non-empty, i.e. <tt>a().getSize1() == a().getSize2() && a().getSize1() != 0</tt>, and furthermore <tt>d().getSize() >= a().getSize1()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def jacobiDiagonalize(a: FMatrixExpression, d: FVectorExpression, v: FMatrixExpression, max_iter: int = 50) -> bool: pass

##
# \brief Computes all eigenvalues and eigenvectors of a real symmetric matrix <em>an</em> using Jacobi's algorithm [\ref WJACO ].
# 
# On output, elements of <em>a</em> above the diagonal are destroyed. The vector <em>d</em> returns the eigenvalues of <em>a</em>. The columns of matrix <em>v</em> contain, on output, the normalized eigenvectors of <em>a</em>. For implementation details see [\ref NRIC].
# 
# \param a The real symmetric matrix for which to compute eigenvalues and eigenvectors.
# \param d The output vector which will contain the eigenvalues of <em>a</em>.
# \param v The matrix whose columns will contain the normalized eigenvectors of <em>a</em>.
# \param max_iter The maximum number of iterations to perform.
# 
# \return <tt>True</tt> if <em>a</em> is a non-empty symmetric matrix and convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <em>a</em> is symmetric and non-empty, i.e. <tt>a().getSize1() == a().getSize2() && a().getSize1() != 0</tt>, and furthermore <tt>d().getSize() >= a().getSize1()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def jacobiDiagonalize(a: LMatrixExpression, d: LVectorExpression, v: LMatrixExpression, max_iter: int = 50) -> bool: pass

##
# \brief Computes all eigenvalues and eigenvectors of a real symmetric matrix <em>an</em> using Jacobi's algorithm [\ref WJACO ].
# 
# On output, elements of <em>a</em> above the diagonal are destroyed. The vector <em>d</em> returns the eigenvalues of <em>a</em>. The columns of matrix <em>v</em> contain, on output, the normalized eigenvectors of <em>a</em>. For implementation details see [\ref NRIC].
# 
# \param a The real symmetric matrix for which to compute eigenvalues and eigenvectors.
# \param d The output vector which will contain the eigenvalues of <em>a</em>.
# \param v The matrix whose columns will contain the normalized eigenvectors of <em>a</em>.
# \param max_iter The maximum number of iterations to perform.
# 
# \return <tt>True</tt> if <em>a</em> is a non-empty symmetric matrix and convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <em>a</em> is symmetric and non-empty, i.e. <tt>a().getSize1() == a().getSize2() && a().getSize1() != 0</tt>, and furthermore <tt>d().getSize() >= a().getSize1()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def jacobiDiagonalize(a: ULMatrixExpression, d: ULVectorExpression, v: ULMatrixExpression, max_iter: int = 50) -> bool: pass

##
# \brief 
# \param e 
# \return 
#
def length(e: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def length(e: ConstFVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def length(e: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def length(e: ConstULVectorExpression) -> int: pass

##
# \brief Computes \f$ \ln[\Gamma(z)] \f$ for \f$ z > 0 \f$.
# 
# \param z The argument to the gamma function.
# 
# \return The computed logarithm of the gamma function value for <em>z</em>.
# 
def lnGamma(z: float) -> float: pass

##
# \brief Computes an in-place LU decomposition of the matrix <em>e</em> without partial pivoting.
# 
# \param e The matrix to decompose (modified in place).
# 
# \return The 1-based row index of the first singular pivot, or <em>0</em> if the matrix is non-singular.
# 
def luDecompose(e: DMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param pv 
# \return 
#
def luDecompose(e: DMatrixExpression, pv: ULVectorExpression) -> int: pass

##
# \brief Computes an in-place LU decomposition of the matrix <em>e</em> without partial pivoting.
# 
# \param e The matrix to decompose (modified in place).
# 
# \return The 1-based row index of the first singular pivot, or <em>0</em> if the matrix is non-singular.
# 
def luDecompose(e: FMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param pv 
# \return 
#
def luDecompose(e: FMatrixExpression, pv: ULVectorExpression) -> int: pass

##
# \brief Computes an in-place LU decomposition of the matrix <em>e</em> without partial pivoting.
# 
# \param e The matrix to decompose (modified in place).
# 
# \return The 1-based row index of the first singular pivot, or <em>0</em> if the matrix is non-singular.
# 
def luDecompose(e: LMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param pv 
# \return 
#
def luDecompose(e: LMatrixExpression, pv: ULVectorExpression) -> int: pass

##
# \brief Computes an in-place LU decomposition of the matrix <em>e</em> without partial pivoting.
# 
# \param e The matrix to decompose (modified in place).
# 
# \return The 1-based row index of the first singular pivot, or <em>0</em> if the matrix is non-singular.
# 
def luDecompose(e: ULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param pv 
# \return 
#
def luDecompose(e: ULMatrixExpression, pv: ULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstDMatrixExpression, b: DVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstDMatrixExpression, pv: ConstULVectorExpression, b: DVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstDMatrixExpression, b: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstDMatrixExpression, pv: ConstULVectorExpression, b: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstFMatrixExpression, b: FVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstFMatrixExpression, pv: ConstULVectorExpression, b: FVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstFMatrixExpression, b: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstFMatrixExpression, pv: ConstULVectorExpression, b: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstLMatrixExpression, b: LVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstLMatrixExpression, pv: ConstULVectorExpression, b: LVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstLMatrixExpression, b: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstLMatrixExpression, pv: ConstULVectorExpression, b: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstULMatrixExpression, b: ULVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstULMatrixExpression, pv: ConstULVectorExpression, b: ULVectorExpression) -> bool: pass

##
# \brief 
# \param e 
# \param b 
# \return 
#
def luSubstitute(e: ConstULMatrixExpression, b: ULMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param pv 
# \param b 
# \return 
#
def luSubstitute(e: ConstULMatrixExpression, pv: ConstULVectorExpression, b: ULMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstFVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm1(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstDQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstFQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstFVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstLQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstULQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm(e: ConstDQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm(e: ConstFQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm(e: ConstLQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm(e: ConstULQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstFVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInf(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInfIndex(e: ConstDVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInfIndex(e: ConstFVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInfIndex(e: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normInfIndex(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def outerProd(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def outerProd(e1: ConstFVectorExpression, e2: ConstFVectorExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def outerProd(e1: ConstLVectorExpression, e2: ConstLVectorExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def outerProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param i 
# \return 
#
def prime(i: int) -> int: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstDMatrixExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstDMatrixExpression, e2: ConstDVectorExpression, c: DVectorExpression) -> DVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstDMatrixExpression, e2: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstDMatrixExpression, e2: ConstDMatrixExpression, c: DMatrixExpression) -> DMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstDVectorExpression, e2: ConstDMatrixExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstDVectorExpression, e2: ConstDMatrixExpression, c: DVectorExpression) -> DVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstFMatrixExpression, e2: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstFMatrixExpression, e2: ConstFVectorExpression, c: FVectorExpression) -> FVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstFMatrixExpression, e2: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstFMatrixExpression, e2: ConstFMatrixExpression, c: FMatrixExpression) -> FMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstFVectorExpression, e2: ConstFMatrixExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstFVectorExpression, e2: ConstFMatrixExpression, c: FVectorExpression) -> FVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstLMatrixExpression, e2: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstLMatrixExpression, e2: ConstLVectorExpression, c: LVectorExpression) -> LVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstLMatrixExpression, e2: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstLMatrixExpression, e2: ConstLMatrixExpression, c: LMatrixExpression) -> LMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstLVectorExpression, e2: ConstLMatrixExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstLVectorExpression, e2: ConstLMatrixExpression, c: LVectorExpression) -> LVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstULMatrixExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstULMatrixExpression, e2: ConstULVectorExpression, c: ULVectorExpression) -> ULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstULMatrixExpression, e2: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstULMatrixExpression, e2: ConstULMatrixExpression, c: ULMatrixExpression) -> ULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def prod(e1: ConstULVectorExpression, e2: ConstULMatrixExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \param c 
# \return 
#
def prod(e1: ConstULVectorExpression, e2: ConstULMatrixExpression, c: ULVectorExpression) -> ULVectorExpression: pass

##
# \brief Computes \f$ \sqrt{a^2 + b^2} \f$ without destructive underflow or overflow.
# 
# \param a The variable <em>a</em>.
# \param b The variable <em>b</em>.
# 
# \return The result of computing \f$ \sqrt{a^2 + b^2} \f$.
# 
def pythag(a: float, b: float) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: ConstDVectorExpression) -> ConstDVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: ConstFVectorExpression) -> ConstFVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: ConstLVectorExpression) -> ConstLVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: ConstULVectorExpression) -> ConstULVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: DVectorExpression) -> DVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: FVectorExpression) -> FVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: LVectorExpression) -> LVectorQuaternionAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: ULVectorExpression) -> ULVectorQuaternionAdapter: pass

##
# \brief 
# \param t 
# \return 
#
def quat(t: float) -> FRealQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def quat(t1: float, t2: float) -> FQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def quat(t1: float, t2: float, t3: float) -> FQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def quat(t1: float, t2: float, t3: float, t4: float) -> FQuaternion: pass

##
# \brief 
# \param t 
# \return 
#
def quat(t: int) -> LRealQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def quat(t1: int, t2: int) -> LQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def quat(t1: int, t2: int, t3: int) -> LQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def quat(t1: int, t2: int, t3: int, t4: int) -> LQuaternion: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: ConstDMatrixExpression, r1: Range, r2: Range) -> ConstDMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: ConstDMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> ConstDMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: ConstDVectorExpression, r: Range) -> ConstDVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: ConstDVectorExpression, start: int, stop: int) -> ConstDVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: ConstFMatrixExpression, r1: Range, r2: Range) -> ConstFMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: ConstFMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> ConstFMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: ConstFVectorExpression, r: Range) -> ConstFVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: ConstFVectorExpression, start: int, stop: int) -> ConstFVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: ConstLMatrixExpression, r1: Range, r2: Range) -> ConstLMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: ConstLMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> ConstLMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: ConstLVectorExpression, r: Range) -> ConstLVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: ConstLVectorExpression, start: int, stop: int) -> ConstLVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: ConstULMatrixExpression, r1: Range, r2: Range) -> ConstULMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: ConstULMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> ConstULMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: ConstULVectorExpression, r: Range) -> ConstULVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: ConstULVectorExpression, start: int, stop: int) -> ConstULVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: DMatrixExpression, r1: Range, r2: Range) -> DMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: DMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> DMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: DVectorExpression, r: Range) -> DVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: DVectorExpression, start: int, stop: int) -> DVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: FMatrixExpression, r1: Range, r2: Range) -> FMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: FMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> FMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: FVectorExpression, r: Range) -> FVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: FVectorExpression, start: int, stop: int) -> FVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: LMatrixExpression, r1: Range, r2: Range) -> LMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: LMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> LMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: LVectorExpression, r: Range) -> LVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: LVectorExpression, start: int, stop: int) -> LVectorRange: pass

##
# \brief 
# \param e 
# \param r1 
# \param r2 
# \return 
#
def range(e: ULMatrixExpression, r1: Range, r2: Range) -> ULMatrixRange: pass

##
# \brief 
# \param e 
# \param start1 
# \param stop1 
# \param start2 
# \param stop2 
# \return 
#
def range(e: ULMatrixExpression, start1: int, stop1: int, start2: int, stop2: int) -> ULMatrixRange: pass

##
# \brief 
# \param e 
# \param r 
# \return 
#
def range(e: ULVectorExpression, r: Range) -> ULVectorRange: pass

##
# \brief 
# \param e 
# \param start 
# \param stop 
# \return 
#
def range(e: ULVectorExpression, start: int, stop: int) -> ULVectorRange: pass

##
# \brief Convenience factory for Math.Range with <tt>std::size_t</tt> indices.
# 
# \param start The lower (inclusive) bound.
# \param stop The upper (exclusive) bound.
# 
# \return The constructed Math.Range instance.
# 
def range(start: int, stop: int) -> Range: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstDQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstFGridExpression) -> ConstFGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstFQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstLQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstULQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def real(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def rotate(e1: ConstDQuaternionExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def rotate(e1: ConstFQuaternionExpression, e2: ConstFVectorExpression) -> ConstFVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def rotate(e1: ConstLQuaternionExpression, e2: ConstLVectorExpression) -> ConstLVectorExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def rotate(e1: ConstULQuaternionExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstDMatrixExpression, i: int) -> ConstDMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstFMatrixExpression, i: int) -> ConstFMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstLMatrixExpression, i: int) -> ConstLMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstULMatrixExpression, i: int) -> ConstULMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: DMatrixExpression, i: int) -> DMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: FMatrixExpression, i: int) -> FMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: LMatrixExpression, i: int) -> LMatrixRow: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ULMatrixExpression, i: int) -> ULMatrixRow: pass

##
# \brief Returns the magnitude of parameter <em>a</em> times the sign of parameter <em>b</em>.
# 
# \param a The parameter <em>a</em>.
# \param b The parameter <em>b</em>.
# 
# \return <em>a</em> times the sign of parameter <em>b</em>.
# 
def sign(a: float, b: float) -> float: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ConstDMatrixExpression, s1: Slice, s2: Slice) -> ConstDMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: ConstDMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> ConstDMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: ConstDVectorExpression, s: Slice) -> ConstDVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: ConstDVectorExpression, start: int, stride: int, size: int) -> ConstDVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ConstFMatrixExpression, s1: Slice, s2: Slice) -> ConstFMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: ConstFMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> ConstFMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: ConstFVectorExpression, s: Slice) -> ConstFVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: ConstFVectorExpression, start: int, stride: int, size: int) -> ConstFVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ConstLMatrixExpression, s1: Slice, s2: Slice) -> ConstLMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: ConstLMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> ConstLMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: ConstLVectorExpression, s: Slice) -> ConstLVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: ConstLVectorExpression, start: int, stride: int, size: int) -> ConstLVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ConstULMatrixExpression, s1: Slice, s2: Slice) -> ConstULMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: ConstULMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> ConstULMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: ConstULVectorExpression, s: Slice) -> ConstULVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: ConstULVectorExpression, start: int, stride: int, size: int) -> ConstULVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: DMatrixExpression, s1: Slice, s2: Slice) -> DMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: DMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> DMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: DVectorExpression, s: Slice) -> DVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: DVectorExpression, start: int, stride: int, size: int) -> DVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: FMatrixExpression, s1: Slice, s2: Slice) -> FMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: FMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> FMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: FVectorExpression, s: Slice) -> FVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: FVectorExpression, start: int, stride: int, size: int) -> FVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: LMatrixExpression, s1: Slice, s2: Slice) -> LMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: LMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> LMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: LVectorExpression, s: Slice) -> LVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: LVectorExpression, start: int, stride: int, size: int) -> LVectorSlice: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ULMatrixExpression, s1: Slice, s2: Slice) -> ULMatrixSlice: pass

##
# \brief 
# \param e 
# \param start1 
# \param stride1 
# \param size1 
# \param start2 
# \param stride2 
# \param size2 
# \return 
#
def slice(e: ULMatrixExpression, start1: int, stride1: int, size1: int, start2: int, stride2: int, size2: int) -> ULMatrixSlice: pass

##
# \brief 
# \param e 
# \param s 
# \return 
#
def slice(e: ULVectorExpression, s: Slice) -> ULVectorSlice: pass

##
# \brief 
# \param e 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(e: ULVectorExpression, start: int, stride: int, size: int) -> ULVectorSlice: pass

##
# \brief Convenience factory for Math.Slice with <tt>std::size_t</tt> indices and <tt>std::ptrdiff_t</tt> stride.
# 
# \param start The starting global index.
# \param stride The signed step size between consecutive entries.
# \param size The number of entries.
# 
# \return The constructed Math.Slice instance.
# 
def slice(start: int, stride: int, size: int) -> Slice: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstULMatrixExpression, e2: ULVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a lower-triangular matrix.
# 
# \param e1 The lower-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveLower(e1: ConstULMatrixExpression, e2: ULMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstULMatrixExpression, e2: ULVectorExpression) -> bool: pass

##
# \brief Solves \f$ L\,X = B \f$ in place column-wise by forward-substitution, where <em>e1</em> is a unit lower-triangular matrix.
# 
# \param e1 The unit lower-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitLower(e1: ConstULMatrixExpression, e2: ULMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstULMatrixExpression, e2: ULVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is a unit upper-triangular matrix.
# 
# \param e1 The unit upper-triangular coefficient matrix (diagonal entries are taken as 1).
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square or dimensions do not match.
# 
def solveUnitUpper(e1: ConstULMatrixExpression, e2: ULMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstULMatrixExpression, e2: ULVectorExpression) -> bool: pass

##
# \brief Solves \f$ U\,X = B \f$ in place column-wise by back-substitution, where <em>e1</em> is an upper-triangular matrix.
# 
# \param e1 The upper-triangular coefficient matrix.
# \param e2 The right-hand side matrix, overwritten with the solution.
# 
# \return <tt>True</tt> if the substitution succeeded, and <tt>False</tt> if the system is not square, dimensions do not match, or a zero diagonal pivot is encountered.
# 
def solveUpper(e1: ConstULMatrixExpression, e2: ULMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDGridExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstFGridExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstFQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstFVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstLQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstLVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstULQuaternionExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: object) -> int: pass

##
# \brief Computes the <em>Singular Value Decomposition</em> [\ref WSVD] \f$ A = UWV^T \f$ of a \f$ M \times N \f$-dimensional matrix <em>a</em>.
# 
# The matrix \f$ U \f$ replaces <em>a</em> on output. The diagonal matrix of singular values \f$ W \f$ is output as the \f$ N \f$-dimensional vector <em>w</em>. The matrix \f$ V \f$ (not the transpose \f$ V^T \f$) is output as the \f$ N \times N \f$-dimensional matrix <em>v</em>. For implementation details see [\ref NRIC].
# 
# \param a The decomposed \f$ M \times N \f$-matrix \f$ A \f$ which will be replaced by \f$ U \f$ on output.
# \param w The \f$ N \f$-dimensional output vector \f$ W \f$ holding the singular values.
# \param v The \f$ N \times N \f$-dimensional output matrix \f$ V \f$.
# \param max_iter The maximum number of iterations to perform, or <em>0</em> if no limit.
# 
# \return <tt>True</tt> if convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <tt>w().getSize() >= a().getSize2()</tt>, <tt>v().getSize1() >= a().getSize2() and v().getSize2() >= a().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def svDecompose(a: DMatrixExpression, w: DVectorExpression, v: DMatrixExpression, max_iter: int = 0) -> bool: pass

##
# \brief Computes the <em>Singular Value Decomposition</em> [\ref WSVD] \f$ A = UWV^T \f$ of a \f$ M \times N \f$-dimensional matrix <em>a</em>.
# 
# The matrix \f$ U \f$ replaces <em>a</em> on output. The diagonal matrix of singular values \f$ W \f$ is output as the \f$ N \f$-dimensional vector <em>w</em>. The matrix \f$ V \f$ (not the transpose \f$ V^T \f$) is output as the \f$ N \times N \f$-dimensional matrix <em>v</em>. For implementation details see [\ref NRIC].
# 
# \param a The decomposed \f$ M \times N \f$-matrix \f$ A \f$ which will be replaced by \f$ U \f$ on output.
# \param w The \f$ N \f$-dimensional output vector \f$ W \f$ holding the singular values.
# \param v The \f$ N \times N \f$-dimensional output matrix \f$ V \f$.
# \param max_iter The maximum number of iterations to perform, or <em>0</em> if no limit.
# 
# \return <tt>True</tt> if convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <tt>w().getSize() >= a().getSize2()</tt>, <tt>v().getSize1() >= a().getSize2() and v().getSize2() >= a().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def svDecompose(a: FMatrixExpression, w: FVectorExpression, v: FMatrixExpression, max_iter: int = 0) -> bool: pass

##
# \brief Computes the <em>Singular Value Decomposition</em> [\ref WSVD] \f$ A = UWV^T \f$ of a \f$ M \times N \f$-dimensional matrix <em>a</em>.
# 
# The matrix \f$ U \f$ replaces <em>a</em> on output. The diagonal matrix of singular values \f$ W \f$ is output as the \f$ N \f$-dimensional vector <em>w</em>. The matrix \f$ V \f$ (not the transpose \f$ V^T \f$) is output as the \f$ N \times N \f$-dimensional matrix <em>v</em>. For implementation details see [\ref NRIC].
# 
# \param a The decomposed \f$ M \times N \f$-matrix \f$ A \f$ which will be replaced by \f$ U \f$ on output.
# \param w The \f$ N \f$-dimensional output vector \f$ W \f$ holding the singular values.
# \param v The \f$ N \times N \f$-dimensional output matrix \f$ V \f$.
# \param max_iter The maximum number of iterations to perform, or <em>0</em> if no limit.
# 
# \return <tt>True</tt> if convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <tt>w().getSize() >= a().getSize2()</tt>, <tt>v().getSize1() >= a().getSize2() and v().getSize2() >= a().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def svDecompose(a: LMatrixExpression, w: LVectorExpression, v: LMatrixExpression, max_iter: int = 0) -> bool: pass

##
# \brief Computes the <em>Singular Value Decomposition</em> [\ref WSVD] \f$ A = UWV^T \f$ of a \f$ M \times N \f$-dimensional matrix <em>a</em>.
# 
# The matrix \f$ U \f$ replaces <em>a</em> on output. The diagonal matrix of singular values \f$ W \f$ is output as the \f$ N \f$-dimensional vector <em>w</em>. The matrix \f$ V \f$ (not the transpose \f$ V^T \f$) is output as the \f$ N \times N \f$-dimensional matrix <em>v</em>. For implementation details see [\ref NRIC].
# 
# \param a The decomposed \f$ M \times N \f$-matrix \f$ A \f$ which will be replaced by \f$ U \f$ on output.
# \param w The \f$ N \f$-dimensional output vector \f$ W \f$ holding the singular values.
# \param v The \f$ N \times N \f$-dimensional output matrix \f$ V \f$.
# \param max_iter The maximum number of iterations to perform, or <em>0</em> if no limit.
# 
# \return <tt>True</tt> if convergence has been reached in <em>max_iter</em> iterations, and <tt>False</tt> otherwise. 
# 
# \pre <tt>w().getSize() >= a().getSize2()</tt>, <tt>v().getSize1() >= a().getSize2() and v().getSize2() >= a().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
def svDecompose(a: ULMatrixExpression, w: ULVectorExpression, v: ULMatrixExpression, max_iter: int = 0) -> bool: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstDMatrixExpression, w: ConstDVectorExpression, v: ConstDMatrixExpression, b: ConstDVectorExpression, x: DVectorExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstDMatrixExpression, w: ConstDVectorExpression, v: ConstDMatrixExpression, b: ConstDMatrixExpression, x: DMatrixExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstFMatrixExpression, w: ConstFVectorExpression, v: ConstFMatrixExpression, b: ConstFVectorExpression, x: FVectorExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstFMatrixExpression, w: ConstFVectorExpression, v: ConstFMatrixExpression, b: ConstFMatrixExpression, x: FMatrixExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstLMatrixExpression, w: ConstLVectorExpression, v: ConstLMatrixExpression, b: ConstLVectorExpression, x: LVectorExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstLMatrixExpression, w: ConstLVectorExpression, v: ConstLMatrixExpression, b: ConstLMatrixExpression, x: LMatrixExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstULMatrixExpression, w: ConstULVectorExpression, v: ConstULMatrixExpression, b: ConstULVectorExpression, x: ULVectorExpression) -> None: pass

##
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M  \times P \f$-dimensional right-hand side matrix \f$ B \f$.
# \param x The \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$.
# 
# \pre <tt>w().getSize() == u().getSize2()</tt>, <tt>v().getSize1() == u().getSize2() && v().getSize2() == u().getSize2()</tt>, <tt>x().getSize1() == u().getSize2()</tt> and <tt>b().getSize1() == u().getSize1() && b().getSize2() == x().getSize2()</tt>. 
# 
# \throw Base.SizeError if preconditions are violated.
# 
# \see svDecomposition()
# 
def svSubstitute(u: ConstULMatrixExpression, w: ConstULVectorExpression, v: ConstULMatrixExpression, b: ConstULMatrixExpression, x: ULMatrixExpression) -> None: pass

##
# \brief 
# \param e 
# \return 
#
def trace(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def trace(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def trace(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def trace(e: ConstULMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: ConstDMatrixExpression) -> ConstDMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: ConstFMatrixExpression) -> ConstFMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: ConstLMatrixExpression) -> ConstLMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: ConstULMatrixExpression) -> ConstULMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: DMatrixExpression) -> DMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: FMatrixExpression) -> FMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: LMatrixExpression) -> LMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: ULMatrixExpression) -> ULMatrixTranspose: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2DArray, xform: Matrix2D) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2DArray, xform: Matrix3D) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2FArray, xform: Matrix2F) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2FArray, xform: Matrix3F) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2LArray, xform: Matrix2L) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2LArray, xform: Matrix3L) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2ULArray, xform: Matrix2UL) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2ULArray, xform: Matrix3UL) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3DArray, xform: Matrix3D) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3DArray, xform: Matrix4D) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3FArray, xform: Matrix3F) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3FArray, xform: Matrix4F) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3LArray, xform: Matrix3L) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3LArray, xform: Matrix4L) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3ULArray, xform: Matrix3UL) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector3ULArray, xform: Matrix4UL) -> None: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstDMatrixExpression, type: Upper) -> ConstUpperTriangularDMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstDMatrixExpression, type: UnitUpper) -> ConstUnitUpperTriangularDMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstDMatrixExpression, type: Lower) -> ConstLowerTriangularDMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstDMatrixExpression, type: UnitLower) -> ConstUnitLowerTriangularDMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstFMatrixExpression, type: Upper) -> ConstUpperTriangularFMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstFMatrixExpression, type: UnitUpper) -> ConstUnitUpperTriangularFMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstFMatrixExpression, type: Lower) -> ConstLowerTriangularFMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstFMatrixExpression, type: UnitLower) -> ConstUnitLowerTriangularFMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstLMatrixExpression, type: Upper) -> ConstUpperTriangularLMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstLMatrixExpression, type: UnitUpper) -> ConstUnitUpperTriangularLMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstLMatrixExpression, type: Lower) -> ConstLowerTriangularLMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstLMatrixExpression, type: UnitLower) -> ConstUnitLowerTriangularLMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstULMatrixExpression, type: Upper) -> ConstUpperTriangularULMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstULMatrixExpression, type: UnitUpper) -> ConstUnitUpperTriangularULMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstULMatrixExpression, type: Lower) -> ConstLowerTriangularULMatrixAdapter: pass

##
# \brief 
# \param e 
# \param type 
# \return 
#
def triang(e: ConstULMatrixExpression, type: UnitLower) -> ConstUnitLowerTriangularULMatrixAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def unreal(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def unreal(e: ConstFQuaternionExpression) -> ConstFQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def unreal(e: ConstLQuaternionExpression) -> ConstLQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def unreal(e: ConstULQuaternionExpression) -> ConstULQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def vec(e: ConstDQuaternionExpression) -> ConstDQuaternionVectorAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def vec(e: ConstFQuaternionExpression) -> ConstFQuaternionVectorAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def vec(e: ConstLQuaternionExpression) -> ConstLQuaternionVectorAdapter: pass

##
# \brief 
# \param e 
# \return 
#
def vec(e: ConstULQuaternionExpression) -> ConstULQuaternionVectorAdapter: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def vec(t1: float, t2: float) -> Vector2F: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def vec(t1: float, t2: float, t3: float) -> Vector3F: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def vec(t1: float, t2: float, t3: float, t4: float) -> Vector4F: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def vec(t1: int, t2: int) -> Vector2L: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def vec(t1: int, t2: int, t3: int) -> Vector3L: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def vec(t1: int, t2: int, t3: int, t4: int) -> Vector4L: pass
