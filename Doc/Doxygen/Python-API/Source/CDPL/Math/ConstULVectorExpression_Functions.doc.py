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
def norm1(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def norm2(e: ConstULVectorExpression) -> int: pass

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
# \return 
#
def innerProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def outerProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def crossProd(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

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
# \return 
#
def normInf(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e 
# \return 
#
def diag(e: ConstULVectorExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def imag(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

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
def length(e: ConstULVectorExpression) -> int: pass

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
def real(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

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
def sum(e: ConstULVectorExpression) -> int: pass

##
# \brief 
# \param e1 
# \param e2 
# \param eps 
# \return 
#
def equals(e1: ConstULVectorExpression, e2: ConstULVectorExpression, eps: int) -> bool: pass

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
# \param e 
# \return 
#
def cross(e: ConstULVectorExpression) -> ConstULMatrixExpression: pass

##
# \brief 
# \param e 
# \return 
#
def quat(e: ConstULVectorExpression) -> ConstULVectorQuaternionAdapter: pass

##
# \brief 
# \param e1 
# \param e2 
# \return 
#
def elemDiv(e1: ConstULVectorExpression, e2: ConstULVectorExpression) -> ConstULVectorExpression: pass

##
# \brief 
# \param e 
# \return 
#
def normInfIndex(e: ConstULVectorExpression) -> int: pass
