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
def norm1(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def normFrob(e: ConstLMatrixExpression) -> int: pass

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
# \param e 
# \return 
#
def trace(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param s1 
# \param s2 
# \return 
#
def slice(e: ConstLMatrixExpression, s1: _ast.Slice, s2: _ast.Slice) -> ConstLMatrixSlice: pass

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
# \param u 
# \param w 
# \param v 
# \param b 
# \param x 
#
def svSubstitute(u: ConstLMatrixExpression, w: ConstLVectorExpression, v: ConstLMatrixExpression, b: ConstLVectorExpression, x: LVectorExpression) -> None: pass

##
# \brief 
# \param u 
# \param w 
# \param v 
# \param b 
# \param x 
#
def svSubstitute(u: ConstLMatrixExpression, w: ConstLVectorExpression, v: ConstLMatrixExpression, b: ConstLMatrixExpression, x: LMatrixExpression) -> None: pass

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
def imag(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

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
# \return 
#
def conj(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

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
def herm(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def column(e: ConstLMatrixExpression, i: int) -> ConstLMatrixColumn: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUpper(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUpper(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitUpper(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitUpper(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveLower(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveLower(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitLower(e1: ConstLMatrixExpression, e2: LVectorExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def solveUnitLower(e1: ConstLMatrixExpression, e2: LMatrixExpression) -> bool: pass

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
# \param e 
# \return 
#
def trans(e: ConstLMatrixExpression) -> ConstLMatrixTranspose: pass

##
# \brief 
# \param e 
# \return 
#
def det(e: ConstLMatrixExpression) -> int: pass

##
# \brief 
# \param e 
# \param c 
# \return 
#
def invert(e: ConstLMatrixExpression, c: LMatrixExpression) -> bool: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstLMatrixExpression, e2: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

##
# \brief 
# \param e 
# \param i 
# \return 
#
def row(e: ConstLMatrixExpression, i: int) -> ConstLMatrixRow: pass
