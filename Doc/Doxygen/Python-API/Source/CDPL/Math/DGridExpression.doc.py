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
class DGridExpression(ConstDGridExpression):

    def swap(e: DGridExpression) -> None: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def assign(e: DGridExpression) -> DGridExpression: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFGridExpression) -> DGridExpression: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDGridExpression) -> DGridExpression: pass

    ##
    # \brief Assigns the grid expression <em>e</em> to this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def assign(e: object) -> DGridExpression: pass

    ##
    # \brief Sets the value of the element (\a i, \a j, \a k) to \a v.
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def setElement(i: int, j: int, k: int, v: float) -> None: pass

    ##
    # \brief Sets the value of the element (\a i, \a j, \a k) to \a v.
    # \param i The zero-based first-axis index.
    # \param j The zero-based second-axis index.
    # \param k The zero-based third-axis index.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __setitem__(ijk: tuple, v: float) -> None: pass

    ##
    # \brief Adds the grid expression <em>e</em> element-wise to this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: DGridExpression) -> DGridExpression: pass

    ##
    # \brief Adds the grid expression <em>e</em> element-wise to this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDGridExpression) -> DGridExpression: pass

    ##
    # \brief Subtracts the grid expression <em>e</em> element-wise from this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: DGridExpression) -> DGridExpression: pass

    ##
    # \brief Subtracts the grid expression <em>e</em> element-wise from this grid (via a temporary to handle aliasing).
    # 
    # \param e The source grid expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDGridExpression) -> DGridExpression: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DGridExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DGridExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DGridExpression: pass
