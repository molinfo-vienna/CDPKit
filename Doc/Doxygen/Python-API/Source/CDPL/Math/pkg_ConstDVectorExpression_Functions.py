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
def norm1(e: ConstDVectorExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstDVectorExpression) -> float: pass

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
def innerProd(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> float: pass

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
def crossProd(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

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
# \param e 
# \param s 
# \return 
#
def slice(e: ConstDVectorExpression, s: _ast.Slice) -> ConstDVectorSlice: pass

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
# \return 
#
def normInf(e: ConstDVectorExpression) -> float: pass

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
def imag(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

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
def length(e: ConstDVectorExpression) -> float: pass

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
def real(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

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
def sum(e: ConstDVectorExpression) -> float: pass

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
# \param sd 
# \param clamp 
# \return 
#
def angleCos(e1: ConstDVectorExpression, e2: ConstDVectorExpression, sd: float, clamp: bool = True) -> float: pass

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
def quat(e: ConstDVectorExpression) -> ConstDVectorQuaternionAdapter: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstDVectorExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def normInfIndex(e: ConstDVectorExpression) -> int: pass
