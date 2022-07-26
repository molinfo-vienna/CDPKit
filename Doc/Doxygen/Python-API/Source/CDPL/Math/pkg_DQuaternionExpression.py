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
#
class DQuaternionExpression(ConstDQuaternionExpression):

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e 
    #
    def swap(self: DQuaternionExpression, e: DQuaternionExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DQuaternionExpression instance \a e.
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e The \e %DQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DQuaternionExpression, e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DQuaternionExpression instance \a e.
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e The \e %DQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DQuaternionExpression, e: ConstFQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DQuaternionExpression instance \a e.
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e The \e %DQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DQuaternionExpression, e: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DQuaternionExpression instance \a e.
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e The \e %DQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DQuaternionExpression, e: ConstLQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DQuaternionExpression instance \a e.
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e The \e %DQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DQuaternionExpression, e: ConstULQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DQuaternionExpression instance \a a.
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param a The \e %DQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DQuaternionExpression, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC1(self: DQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC2(self: DQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC3(self: DQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC4(self: DQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    #
    def set(self: DQuaternionExpression, c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place addend.
    # \param t Specifies the second addend.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __iadd__(self: DQuaternionExpression, t: float) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __iadd__(self: DQuaternionExpression, e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __iadd__(self: DQuaternionExpression, q: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place minuend.
    # \param t Specifies the subtrahend.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __isub__(self: DQuaternionExpression, t: float) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __isub__(self: DQuaternionExpression, e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __isub__(self: DQuaternionExpression, q: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __imul__(self: DQuaternionExpression, t: float) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= e</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place multiplicand.
    # \param e Specifies the multiplier.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __imul__(self: DQuaternionExpression, e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __imul__(self: DQuaternionExpression, q: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __idiv__(self: DQuaternionExpression, t: float) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= e</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place dividend.
    # \param e Specifies the divisor.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __idiv__(self: DQuaternionExpression, e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %DQuaternionExpression instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %DQuaternionExpression instance \a self.
    #
    def __idiv__(self: DQuaternionExpression, q: ConstDQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DQuaternionExpression, t: float) -> DQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param e 
    # \return 
    #
    def __itruediv__(self: DQuaternionExpression, e: DQuaternionExpression) -> DQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %DQuaternionExpression instance this method is called upon.
    # \param q 
    # \return 
    #
    def __itruediv__(self: DQuaternionExpression, q: ConstDQuaternionExpression) -> DQuaternionExpression: pass
