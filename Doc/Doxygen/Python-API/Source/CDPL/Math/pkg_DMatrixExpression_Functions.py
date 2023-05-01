#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
def slice(e: DMatrixExpression, s1: ast.Slice, s2: ast.Slice) -> DMatrixSlice: pass

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
# \return 
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
# \brief 
# \param a 
# \param w 
# \param v 
# \param max_iter 
# \return 
#
def svDecompose(a: DMatrixExpression, w: DVectorExpression, v: DMatrixExpression, max_iter: int = 0) -> bool: pass

##
# \brief 
# \param a 
# \param d 
# \param v 
# \param max_iter 
# \return 
#
def jacobiDiagonalize(a: DMatrixExpression, d: DVectorExpression, v: DMatrixExpression, max_iter: int = 50) -> bool: pass

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
# \return 
#
def trans(e: DMatrixExpression) -> DMatrixTranspose: pass

##
# \brief 
# \param c 
# \return 
#
def invert(c: DMatrixExpression) -> bool: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: DMatrixExpression, i: int) -> DMatrixRow: pass
