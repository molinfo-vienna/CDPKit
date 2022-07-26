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
# \param a 
# \param x 
# \return 
#
def gammaQ(a: float, x: float) -> float: pass

##
# \brief 
# \param z 
# \return 
#
def lnGamma(z: float) -> float: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def vec(t1: float, t2: float) -> Vector2F: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def vec(t1: float, t2: float, t3: float) -> Vector3F: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def vec(t1: float, t2: float, t3: float, t4: float) -> Vector4F: pass

##
# \brief 
# \param a 
# \param b 
# \return 
#
def pythag(a: float, b: float) -> float: pass

##
# \brief 
# \param x 
# \param a 
# \param b 
# \param c 
# \return 
#
def generalizedBell(x: float, a: float, b: float, c: float) -> float: pass

##
# \brief 
# \param a 
# \param b 
# \return 
#
def sign(a: float, b: float) -> float: pass

##
# \brief 
# \param t 
# \return 
#
def quat(t: float) -> FRealQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \return 
#
def quat(t1: float, t2: float) -> FQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \return 
#
def quat(t1: float, t2: float, t3: float) -> FQuaternion: pass

##
# \brief 
# \param t1 
# \param t2 
# \param t3 
# \param t4 
# \return 
#
def quat(t1: float, t2: float, t3: float, t4: float) -> FQuaternion: pass
