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
def slice(e: ConstDMatrixExpression, s1: _ast.Slice, s2: _ast.Slice) -> ConstDMatrixSlice: pass

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
# \brief 
# \param u 
# \param w 
# \param v 
# \param b 
# \param x 
#
def svSubstitute(u: ConstDMatrixExpression, w: ConstDVectorExpression, v: ConstDMatrixExpression, b: ConstDVectorExpression, x: DVectorExpression) -> None: pass

##
# \brief 
# \param u 
# \param w 
# \param v 
# \param b 
# \param x 
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
