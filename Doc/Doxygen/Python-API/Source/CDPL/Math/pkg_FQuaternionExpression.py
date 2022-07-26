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
class FQuaternionExpression(ConstFQuaternionExpression):

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e 
    #
    def swap(self: FQuaternionExpression, e: FQuaternionExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FQuaternionExpression, e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FQuaternionExpression, e: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FQuaternionExpression, e: ConstDQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FQuaternionExpression, e: ConstLQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FQuaternionExpression, e: ConstULQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a a.
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param a The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: FQuaternionExpression, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC1(self: FQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC2(self: FQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC3(self: FQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param v 
    #
    def setC4(self: FQuaternionExpression, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    #
    def set(self: FQuaternionExpression, c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place addend.
    # \param t Specifies the second addend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __iadd__(self: FQuaternionExpression, t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __iadd__(self: FQuaternionExpression, e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place addend.
    # \param q Specifies the second addend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __iadd__(self: FQuaternionExpression, q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place minuend.
    # \param t Specifies the subtrahend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __isub__(self: FQuaternionExpression, t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __isub__(self: FQuaternionExpression, e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place minuend.
    # \param q Specifies the subtrahend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __isub__(self: FQuaternionExpression, q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __imul__(self: FQuaternionExpression, t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= e</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place multiplicand.
    # \param e Specifies the multiplier.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __imul__(self: FQuaternionExpression, e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place multiplicand.
    # \param q Specifies the multiplier.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __imul__(self: FQuaternionExpression, q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __idiv__(self: FQuaternionExpression, t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= e</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place dividend.
    # \param e Specifies the divisor.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __idiv__(self: FQuaternionExpression, e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param self The \e %FQuaternionExpression instance acting as in-place dividend.
    # \param q Specifies the divisor.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __idiv__(self: FQuaternionExpression, q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: FQuaternionExpression, t: float) -> FQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param e 
    # \return 
    #
    def __itruediv__(self: FQuaternionExpression, e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief 
    # \param self The \e %FQuaternionExpression instance this method is called upon.
    # \param q 
    # \return 
    #
    def __itruediv__(self: FQuaternionExpression, q: ConstFQuaternionExpression) -> FQuaternionExpression: pass
