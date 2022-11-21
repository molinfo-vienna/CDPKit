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
# \param t1 
# \param t2 
# \return 
#
def vec(t1: int, t2: int) -> Vector2L: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def vec(t1: int, t2: int, t3: int) -> Vector3L: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def vec(t1: int, t2: int, t3: int, t4: int) -> Vector4L: pass

##
# \brief 
# \param start 
# \param stride 
# \param size 
# \return 
#
def slice(start: int, stride: int, size: int) -> _ast.Slice: pass

##
# \brief 
# \param start 
# \param stop 
# \return 
#
def range(start: int, stop: int) -> Range: pass

##
# \brief 
# \param i 
# \return 
#
def prime(i: int) -> int: pass

##
# \brief 
# \param n 
# \return 
#
def factorial(n: int) -> int: pass

##
# \brief 
# \param t 
# \return 
#
def quat(t: int) -> LRealQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def quat(t1: int, t2: int) -> LQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def quat(t1: int, t2: int, t3: int) -> LQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def quat(t1: int, t2: int, t3: int, t4: int) -> LQuaternion: pass
