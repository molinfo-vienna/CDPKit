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
# \brief 
#
class FGridExpression(ConstFGridExpression):

    ##
    # \brief 
    # \param e 
    #
    def swap(e: FGridExpression) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FGridExpression instance \a e.
    # \param e The \c %FGridExpression instance to copy.
    # \return \a self
    # 
    def assign(e: FGridExpression) -> FGridExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstFGridExpression instance \a e.
    # \param e The \c %ConstFGridExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstFGridExpression) -> FGridExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstDGridExpression instance \a e.
    # \param e The \c %ConstDGridExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstDGridExpression) -> FGridExpression: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a e.
    # \param e The \c %object instance to copy.
    # \return \a self
    # 
    def assign(e: object) -> FGridExpression: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param k 
    # \param v 
    #
    def setElement(i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief 
    # \param ijk 
    # \param v 
    #
    def __setitem__(ijk: tuple, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %FGridExpression instance \a self.
    # 
    def __iadd__(e: FGridExpression) -> FGridExpression: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %FGridExpression instance \a self.
    # 
    def __iadd__(e: ConstFGridExpression) -> FGridExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %FGridExpression instance \a self.
    # 
    def __isub__(e: FGridExpression) -> FGridExpression: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %FGridExpression instance \a self.
    # 
    def __isub__(e: ConstFGridExpression) -> FGridExpression: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %FGridExpression instance \a self.
    # 
    def __imul__(t: float) -> FGridExpression: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %FGridExpression instance \a self.
    # 
    def __idiv__(t: float) -> FGridExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: float) -> FGridExpression: pass
