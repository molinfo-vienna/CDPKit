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
def norm2(e: ConstDQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def vec(e: ConstDQuaternionExpression) -> ConstDQuaternionVectorAdapter: pass

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
def rotate(e1: ConstDQuaternionExpression, e2: ConstDVectorExpression) -> ConstDVectorExpression: pass

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
def real(e: ConstDQuaternionExpression) -> float: pass

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
def norm(e: ConstDQuaternionExpression) -> float: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDQuaternionExpression) -> float: pass

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
# \return 
#
def elemDiv(e1: ConstDQuaternionExpression, e2: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass

##
# \brief 
# \param e 
# \return 
#
def inv(e: ConstDQuaternionExpression) -> ConstDQuaternionExpression: pass
