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
# \brief Represents the outcome of mathematical expressions/operations that result in a matrix.
# 
class DMatrixExpression(ConstDMatrixExpression):

    ##
    # \brief Swaps the contents of this matrix expression with those of <em>e</em>.
    # 
    # \param e The matrix expression to swap with.
    # 
    def swap(e: DMatrixExpression) -> None: pass

    ##
    # \brief Assigns the contents of the matrix expression <em>e</em> to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: DMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Assigns the contents of the matrix expression <em>e</em> to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Assigns the contents of the matrix expression <em>e</em> to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Assigns the contents of the matrix expression <em>e</em> to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Assigns the contents of the matrix expression <em>e</em> to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Assigns the contents of the 2D \c numpy.ndarray object \a a to this matrix expression.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
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
    # \brief Adds the matrix expression <em>e</em> element-wise to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: DMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Adds the matrix expression <em>e</em> element-wise to this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> element-wise from this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: DMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Subtracts the matrix expression <em>e</em> element-wise from this expression.
    # 
    # \param e The source matrix expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDMatrixExpression) -> DMatrixExpression: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DMatrixExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DMatrixExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DMatrixExpression: pass
