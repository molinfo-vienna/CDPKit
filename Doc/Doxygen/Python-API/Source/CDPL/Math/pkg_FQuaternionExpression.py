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
    # \param e 
    #
    def swap(e: FQuaternionExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a e.
    # \param e The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FQuaternionExpression instance \a a.
    # \param a The \e %FQuaternionExpression instance to copy.
    # \return The assignment target \a self.
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC1(v: float) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC2(v: float) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC3(v: float) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def setC4(v: float) -> None: pass

    ##
    # \brief 
    # \param c1 
    # \param c2 
    # \param c3 
    # \param c4 
    #
    def set(c1: float = 0.0, c2: float = 0.0, c3: float = 0.0, c4: float = 0.0) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += t</tt>.
    # \param t Specifies the second addend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __iadd__(t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __iadd__(e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += q</tt>.
    # \param q Specifies the second addend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __iadd__(q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= t</tt>.
    # \param t Specifies the subtrahend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __isub__(t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __isub__(e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= q</tt>.
    # \param q Specifies the subtrahend.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __isub__(q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __imul__(t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= e</tt>.
    # \param e Specifies the multiplier.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __imul__(e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= q</tt>.
    # \param q Specifies the multiplier.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __imul__(q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __idiv__(t: float) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= e</tt>.
    # \param e Specifies the divisor.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __idiv__(e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= q</tt>.
    # \param q Specifies the divisor.
    # \return The updated \e %FQuaternionExpression instance \a self.
    #
    def __idiv__(q: ConstFQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FQuaternionExpression: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def __itruediv__(e: FQuaternionExpression) -> FQuaternionExpression: pass

    ##
    # \brief 
    # \param q 
    # \return 
    #
    def __itruediv__(q: ConstFQuaternionExpression) -> FQuaternionExpression: pass
