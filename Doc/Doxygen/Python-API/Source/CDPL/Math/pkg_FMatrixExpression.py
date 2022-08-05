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
class FMatrixExpression(ConstFMatrixExpression):

    ##
    # \brief 
    # \param e 
    #
    def swap(e: FMatrixExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixExpression instance \a e.
    # \param e The \e %FMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: FMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixExpression instance \a e.
    # \param e The \e %FMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixExpression instance \a e.
    # \param e The \e %FMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixExpression instance \a e.
    # \param e The \e %FMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixExpression instance \a e.
    # \param e The \e %FMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FMatrixExpression instance \a a.
    # \param a The \e %FMatrixExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief 
    # \param ij 
    # \param v 
    #
    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %FMatrixExpression instance \a self.
    #
    def __iadd__(e: FMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %FMatrixExpression instance \a self.
    #
    def __iadd__(e: ConstFMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FMatrixExpression instance \a self.
    #
    def __isub__(e: FMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FMatrixExpression instance \a self.
    #
    def __isub__(e: ConstFMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %FMatrixExpression instance \a self.
    #
    def __imul__(t: float) -> FMatrixExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %FMatrixExpression instance \a self.
    #
    def __idiv__(t: float) -> FMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FMatrixExpression: pass
