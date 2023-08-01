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
# \param va1 
# \param va2 
# \return 
#
def calcRMSD(va1: Vector2LArray, va2: Vector2LArray) -> int: pass

##
# \brief 
# \param va1 
# \param va2 
# \param va1_xform 
# \return 
#
def calcRMSD(va1: Vector2LArray, va2: Vector2LArray, va1_xform: Matrix3L) -> int: pass

##
# \brief 
# \param va 
# \param ctr 
# \return 
#
def calcCentroid(va: Vector2LArray, ctr: Vector2L) -> bool: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2LArray, xform: Matrix2L) -> None: pass

##
# \brief 
# \param va 
# \param xform 
#
def transform(va: Vector2LArray, xform: Matrix3L) -> None: pass
