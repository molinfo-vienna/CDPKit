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
# \brief Represents the outcome of mathematical expressions/operations that result in a vector.
# 
class ULVectorExpression(ConstULVectorExpression):

    ##
    # \brief Swaps the contents of this vector expression with those of <em>e</em>.
    # 
    # \param e The vector expression to swap with.
    # 
    def swap(e: ULVectorExpression) -> None: pass

    ##
    # \brief Assigns the contents of the vector expression <em>e</em> to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ULVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Assigns the contents of the vector expression <em>e</em> to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Assigns the contents of the vector expression <em>e</em> to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Assigns the contents of the vector expression <em>e</em> to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Assigns the contents of the vector expression <em>e</em> to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this vector expression.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> ULVectorExpression: pass

    ##
    # \brief Sets the value of the element at index \a i to \a v.
    # \param i The zero-based element index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Sets the value of the element at index \a i to \a v.
    # \param i The zero-based element index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Adds the vector expression <em>e</em> element-wise to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ULVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Adds the vector expression <em>e</em> element-wise to this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstULVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> element-wise from this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ULVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> element-wise from this expression.
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstULVectorExpression) -> ULVectorExpression: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: int) -> ULVectorExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: int) -> ULVectorExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: int) -> ULVectorExpression: pass
