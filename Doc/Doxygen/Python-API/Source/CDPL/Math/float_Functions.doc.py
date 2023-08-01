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
# \brief Computes the incomplete gamma function \f$ Q(a, x) = 1 - P(a, x) \f$ (see [\ref NRIC] for details).
# 
# \param a The function argument <em>a</em>.
# \param x The function argument <em>x</em>.
# 
# \return The computed value of the incomplete gamma function.
# 
def gammaQ(a: float, x: float) -> float: pass

##
# \brief Computes \f$ \ln[\Gamma(z)] \f$ for \f$ z > 0 \f$.
# 
# \param z The argument to the gamma function.
# 
# \return The computed logarithm of the gamma function value for <em>z</em>.
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
# \brief Computes \f$ \sqrt{a^2 + b^2} \f$ without destructive underflow or overflow.
# 
# \param a The variable <em>a</em>.
# \param b The variable <em>b</em>.
# 
# \return The result of computing \f$ \sqrt{a^2 + b^2} \f$.
# 
def pythag(a: float, b: float) -> float: pass

##
# \brief Computes the generalized bell function \f$ Bell(x) = \frac{1}{1 + |\frac{x-c}{a}|^{2b}} \f$ at <em>x</em>.
# 
# \param x The generalized bell function argument
# \param a Controls the width of the curve at \f$f(x) = 0.5 \f$.
# \param b Controls the slope of the curve at \f$ x = c - a \f$ and \f$ x = c + a \f$.
# \param c Locates the center of the curve.
# 
# \return The generalized bell function value at <em>x</em>.
# 
def generalizedBell(x: float, a: float, b: float, c: float) -> float: pass

##
# \brief Returns the magnitude of parameter <em>a</em> times the sign of parameter <em>b</em>.
# 
# \param a The parameter <em>a</em>.
# \param b The parameter <em>b</em>.
# 
# \return <em>a</em> times the sign of parameter <em>b</em>.
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
