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
class DGridExpression(ConstDGridExpression):

    ##
    # \brief 
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param e 
    #
    def swap(self: DGridExpression, e: DGridExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGridExpression instance \a e.
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param e The \e %DGridExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DGridExpression, e: DGridExpression) -> DGridExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGridExpression instance \a e.
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param e The \e %DGridExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DGridExpression, e: ConstFGridExpression) -> DGridExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGridExpression instance \a e.
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param e The \e %DGridExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DGridExpression, e: ConstDGridExpression) -> DGridExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DGridExpression instance \a e.
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param e The \e %DGridExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DGridExpression, e: object) -> DGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(self: DGridExpression, i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param ijk 
    # \param v 
    #
    def __setitem__(self: DGridExpression, ijk: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DGridExpression instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DGridExpression instance \a self.
    #
    def __iadd__(self: DGridExpression, e: DGridExpression) -> DGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %DGridExpression instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %DGridExpression instance \a self.
    #
    def __iadd__(self: DGridExpression, e: ConstDGridExpression) -> DGridExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DGridExpression instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DGridExpression instance \a self.
    #
    def __isub__(self: DGridExpression, e: DGridExpression) -> DGridExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %DGridExpression instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %DGridExpression instance \a self.
    #
    def __isub__(self: DGridExpression, e: ConstDGridExpression) -> DGridExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %DGridExpression instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %DGridExpression instance \a self.
    #
    def __imul__(self: DGridExpression, t: float) -> DGridExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %DGridExpression instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %DGridExpression instance \a self.
    #
    def __idiv__(self: DGridExpression, t: float) -> DGridExpression: pass

    ##
    # \brief 
    # \param self The \e %DGridExpression instance this method is called upon.
    # \param t 
    # \return 
    #
    def __itruediv__(self: DGridExpression, t: float) -> DGridExpression: pass
