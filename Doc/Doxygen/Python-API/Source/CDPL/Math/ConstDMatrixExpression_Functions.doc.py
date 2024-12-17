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
# \param e 
# \return 
#
def norm1(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstDMatrixExpression) -> float: pass

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
# \param e 
# \return 
#
def trace(e: ConstDMatrixExpression) -> float: pass

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
# \brief Solves \f$ A \cdot X = B \f$ for a matrix \f$ X \f$ where \f$ A \f$ is given by its <em>Singular Value Decomposition</em> [\ref WSVD].
# 
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M \times P \f$-dimensional right-hand side matrix \f$ B \f$.
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
# The \f$ M \times N \f$-dimensional matrix \f$ A \f$ is specified by its singular value decomposition \f$ A = UWV^T \f$, where \f$ U \f$ is given by the \f$ M \times N \f$-dimensional matrix <em>u</em>, \f$ W \f$ by the \f$ N \f$-dimensional vector <em>w</em>, and \f$ V \f$ is provided by the \f$ N \times N \f$-dimensional matrix <em>v</em>. The \f$ M \times P \f$-dimensional right-hand side matrix \f$ B \f$ is given by <em>b</em>, and <em>x</em> is the \f$ N \times P \f$-dimensional output solution matrix \f$ X \f$. No input quantities are destroyed, so the routine may be called sequentially with different arguments <em>b</em>. For implementation details see [\ref NRIC].
# 
# \param u The \f$ M \times N \f$-dimensional matrix \f$ U \f$.
# \param w The \f$ N \f$-dimensional vector \f$ W \f$ holding the singular values of \f$ A \f$.
# \param v The \f$ N \times N \f$-dimensional matrix \f$ V \f$.
# \param b The \f$ M \times P \f$-dimensional right-hand side matrix \f$ B \f$.
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
def imag(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

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
# \return 
#
def conj(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

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
def herm(e: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstDMatrixExpression, i: int) -> ConstDMatrixColumn: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUpper(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUpper(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitUpper(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitUpper(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveLower(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveLower(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitLower(e1: ConstDMatrixExpression, e2: DVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitLower(e1: ConstDMatrixExpression, e2: DMatrixExpression) -> bool: pass

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
# \param e 
# \return 
#
def trans(e: ConstDMatrixExpression) -> ConstDMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstDMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstDMatrixExpression, c: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstDMatrixExpression, e2: ConstDMatrixExpression) -> ConstDMatrixExpression: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstDMatrixExpression, i: int) -> ConstDMatrixRow: pass
