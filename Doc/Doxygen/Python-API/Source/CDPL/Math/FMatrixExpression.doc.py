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
class FMatrixExpression(ConstFMatrixExpression):

    def swap(e: FMatrixExpression) -> None: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: FMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Assigns the matrix expression <em>e</em> to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c object instance \a a.
    # \param a The \c object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Sets the value of the element (\a i, \a j) to \a v.
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def setElement(i: int, j: int, v: float) -> None: pass

    ##
    # \brief Sets the value of the element (\a i, \a j to \a v.
    # \param i The zero-based row index.
    # \param j The zero-based column index.
    # \param v The new value of the element.
    # \throw Base.IndexError if any of the indices is out of range.
    # 
    def __setitem__(ij: tuple, v: float) -> None: pass

    ##
    # \brief Adds the matrix expression <em>e</em> element-wise to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: FMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Adds the matrix expression <em>e</em> element-wise to this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstFMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> element-wise from this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: FMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> element-wise from this matrix (via a temporary to handle aliasing).
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstFMatrixExpression) -> FMatrixExpression: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> FMatrixExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> FMatrixExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> FMatrixExpression: pass
