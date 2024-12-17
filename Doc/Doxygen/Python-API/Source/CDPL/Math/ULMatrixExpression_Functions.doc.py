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
# \return 
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
# \param i 
# \return 
#
def column(e: ULMatrixExpression, i: int) -> ULMatrixColumn: pass

##
# \brief 
# \param e 
# \return 
#
def trans(e: ULMatrixExpression) -> ULMatrixTranspose: pass

##
# \brief 
# \param c 
# \return 
#
def invert(c: ULMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ULMatrixExpression, i: int) -> ULMatrixRow: pass
