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
def norm1(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstFMatrixExpression) -> float: pass

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
# \param e 
# \return 
#
def trace(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ConstFMatrixExpression, s1: ast.Slice, s2: ast.Slice) -> ConstFMatrixSlice: pass

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
# \param u 
# \param w 
# \param v 
# \param b 
# \param x 
#
def svSubstitute(u: ConstFMatrixExpression, w: ConstFVectorExpression, v: ConstFMatrixExpression, b: ConstFVectorExpression, x: FVectorExpression) -> None: pass

##
# \brief 
# \param u 
# \param w 
# \param v 
# \param b 
# \param x 
#
def svSubstitute(u: ConstFMatrixExpression, w: ConstFVectorExpression, v: ConstFMatrixExpression, b: ConstFMatrixExpression, x: FMatrixExpression) -> None: pass

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
def imag(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

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
# \return 
#
def conj(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

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
def herm(e: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstFMatrixExpression, i: int) -> ConstFMatrixColumn: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUpper(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUpper(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitUpper(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitUpper(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveLower(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveLower(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitLower(e1: ConstFMatrixExpression, e2: FVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitLower(e1: ConstFMatrixExpression, e2: FMatrixExpression) -> bool: pass

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
# \param e 
# \return 
#
def trans(e: ConstFMatrixExpression) -> ConstFMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstFMatrixExpression) -> float: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstFMatrixExpression, c: FMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstFMatrixExpression, e2: ConstFMatrixExpression) -> ConstFMatrixExpression: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstFMatrixExpression, i: int) -> ConstFMatrixRow: pass
