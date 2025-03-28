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
# \return 
#
def elemProd(e1: ConstDGridExpression, e2: ConstDGridExpression) -> ConstDGridExpression: pass

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
def conj(e: ConstDGridExpression) -> ConstDGridExpression: pass

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
def herm(e: ConstDGridExpression) -> ConstDGridExpression: pass

##
# \brief 
# \param e 
# \return 
#
def sum(e: ConstDGridExpression) -> float: pass

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
# \return 
#
def elemDiv(e1: ConstDGridExpression, e2: ConstDGridExpression) -> ConstDGridExpression: pass
