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
# \brief Represents the outcome of mathematical expressions/operations that result in a quaternion.
# 
class DQuaternionExpression(ConstDQuaternionExpression):

    ##
    # \brief Swaps the four components of this quaternion expression with those of <em>e</em>.
    # 
    # \param e The quaternion expression to swap with.
    # 
    def swap(e: DQuaternionExpression) -> None: pass

    ##
    # \brief Assigns the contents of the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Assigns the contents of the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Assigns the contents of the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Assigns the contents of the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Assigns the contents of the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this quaternion expression.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Sets the value of the real component \e C1 to \a v.
    # \param v The new value of the real component \e C1.
    # 
    def setC1(v: float) -> None: pass

    ##
    # \brief Sets the value of the imaginary component \e C2 to \a v.
    # \param v The new value of the imaginary component \e C2.
    # 
    def setC2(v: float) -> None: pass

    ##
    # \brief Sets the value of the imaginary component \e C3 to \a v.
    # \param v The new value of the imaginary component \e C3.
    # 
    def setC3(v: float) -> None: pass

    ##
    # \brief Sets the value of the imaginary component \e C4 to \a v.
    # \param v The new value of the imaginary component \e C4.
    # 
    def setC4(v: float) -> None: pass

    ##
    # \brief Sets the four quaternion components to the supplied values.
    # 
    # \param c1 The new real component.
    # \param c2 The new first imaginary component.
    # \param c3 The new second imaginary component.
    # \param c4 The new third imaginary component.
    # 
    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Adds the scalar <em>t</em> to the real component.
    # 
    # \param t The scalar addend.
    # 
    # \return \a self.
    # 
    def __iadd__(t: float) -> DQuaternionExpression: pass

    ##
    # \brief Adds the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Adds the quaternion expression <em>e</em> to this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Subtracts the scalar <em>t</em> from the real component.
    # 
    # \param t The scalar subtrahend.
    # 
    # \return \a self.
    # 
    def __isub__(t: float) -> DQuaternionExpression: pass

    ##
    # \brief Subtracts the quaternion expression <em>e</em> from this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Subtracts the quaternion expression <em>e</em> from this expression.
    # 
    # \param e The source quaternion expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Multiplies every component by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DQuaternionExpression: pass

    ##
    # \brief Right-multiplies this quaternion by the quaternion expression <em>e</em> (Hamilton product, via a temporary).
    # 
    # \param e The right-hand quaternion expression.
    # 
    # \return \a self.
    # 
    def __imul__(e: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Divides every component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DQuaternionExpression: pass

    ##
    # \brief Right-divides this quaternion by the quaternion expression <em>e</em> (Hamilton-product inverse, via a temporary).
    # 
    # \param e The right-hand quaternion expression.
    # 
    # \return \a self.
    # 
    def __idiv__(e: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Divides every component by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DQuaternionExpression: pass

    ##
    # \brief Right-divides this quaternion by the quaternion expression <em>e</em> (Hamilton-product inverse, via a temporary).
    # 
    # \param e The right-hand quaternion expression.
    # 
    # \return \a self.
    # 
    def __itruediv__(e: ConstDQuaternionExpression) -> DQuaternionExpression: pass
