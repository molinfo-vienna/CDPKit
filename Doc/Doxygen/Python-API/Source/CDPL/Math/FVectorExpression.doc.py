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
class FVectorExpression(ConstFVectorExpression):

    def swap(e: FVectorExpression) -> None: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: FVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c object instance \a a.
    # \param a The \c object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Sets the value of the element at index \a i to \a v.
    # \param i The zero-based element index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Sets the value of the element at index \a i to \a v.
    # \param i The zero-based element index.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Adds the vector expression <em>e</em> element-wise to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: FVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Adds the vector expression <em>e</em> element-wise to this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstFVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> element-wise from this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: FVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> element-wise from this vector (via a temporary to handle aliasing).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstFVectorExpression) -> FVectorExpression: pass

    ##
    # \brief Multiplies every element by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> FVectorExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> FVectorExpression: pass

    ##
    # \brief Divides every element by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> FVectorExpression: pass
