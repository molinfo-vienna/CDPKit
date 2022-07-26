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
class LMatrixExpression(ConstLMatrixExpression):

    ##
    # \brief 
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param e 
    #
    def swap(self: LMatrixExpression, e: LMatrixExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixExpression instance \a e.
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param e The \e %LMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixExpression, e: LMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixExpression instance \a e.
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param e The \e %LMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixExpression, e: ConstFMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixExpression instance \a e.
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param e The \e %LMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixExpression, e: ConstDMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixExpression instance \a e.
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param e The \e %LMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixExpression, e: ConstLMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixExpression instance \a e.
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param e The \e %LMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixExpression, e: ConstULMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %LMatrixExpression instance \a a.
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param a The \e %LMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: LMatrixExpression, a: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(self: LMatrixExpression, i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param ij 
    # \param v 
    #
    def __setitem__(self: LMatrixExpression, ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LMatrixExpression instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LMatrixExpression instance \a self.
    #
    def __iadd__(self: LMatrixExpression, e: LMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LMatrixExpression instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LMatrixExpression instance \a self.
    #
    def __iadd__(self: LMatrixExpression, e: ConstLMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LMatrixExpression instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LMatrixExpression instance \a self.
    #
    def __isub__(self: LMatrixExpression, e: LMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LMatrixExpression instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LMatrixExpression instance \a self.
    #
    def __isub__(self: LMatrixExpression, e: ConstLMatrixExpression) -> LMatrixExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LMatrixExpression instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LMatrixExpression instance \a self.
    #
    def __imul__(self: LMatrixExpression, t: int) -> LMatrixExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LMatrixExpression instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LMatrixExpression instance \a self.
    #
    def __idiv__(self: LMatrixExpression, t: int) -> LMatrixExpression: pass

    ##
    # \brief 
    # \param self The \e %LMatrixExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: LMatrixExpression, t: int) -> LMatrixExpression: pass
