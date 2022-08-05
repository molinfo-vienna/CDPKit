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
class SparseLVector(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SparseLVector instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param v 
    #
    def __init__(v: SparseLVector) -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param n 
    #
    def __init__(n: int) -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param e 
    #
    def __init__(e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param e 
    #
    def __init__(e: ConstDVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param e 
    #
    def __init__(e: ConstLVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param e 
    #
    def __init__(e: ConstULVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %SparseLVector instance.
    # \param a 
    #
    def __init__(a: object) -> None: pass

    ##
    # \brief 
    # \param n 
    #
    def resize(n: int) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumElements() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %SparseLVector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SparseLVector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseLVector instance \a e.
    # \param e The \e %SparseLVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFVectorExpression) -> SparseLVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseLVector instance \a e.
    # \param e The \e %SparseLVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDVectorExpression) -> SparseLVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseLVector instance \a e.
    # \param e The \e %SparseLVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLVectorExpression) -> SparseLVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseLVector instance \a e.
    # \param e The \e %SparseLVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULVectorExpression) -> SparseLVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseLVector instance \a v.
    # \param v The \e %SparseLVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(v: SparseLVector) -> SparseLVector: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SparseLVector instance \a a.
    # \param a The \e %SparseLVector instance to copy.
    # \return The assignment target \a self.
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getElement(i: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param v 
    #
    def swap(v: SparseLVector) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \e %SparseLVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(v: SparseLVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %SparseLVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \e %SparseLVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(v: SparseLVector) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %SparseLVector instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __call__(i: int) -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \e %SparseLVector instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> SparseLVector: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %SparseLVector instance holding the result of the addition.
    #
    def __add__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %SparseLVector instance holding the result of the subtraction.
    #
    def __sub__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %SparseLVector instance holding the result of the multiplication.
    #
    def __mul__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %SparseLVector instance holding the result of the multiplication.
    #
    def __mul__(e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %SparseLVector instance holding the result of the division.
    #
    def __div__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += v</tt>.
    # \param v Specifies the second addend.
    # \return The updated \e %SparseLVector instance \a self.
    #
    def __iadd__(v: SparseLVector) -> SparseLVector: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %SparseLVector instance \a self.
    #
    def __iadd__(e: ConstLVectorExpression) -> SparseLVector: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= v</tt>.
    # \param v Specifies the subtrahend.
    # \return The updated \e %SparseLVector instance \a self.
    #
    def __isub__(v: SparseLVector) -> SparseLVector: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %SparseLVector instance \a self.
    #
    def __isub__(e: ConstLVectorExpression) -> SparseLVector: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %SparseLVector instance \a self.
    #
    def __imul__(t: int) -> SparseLVector: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %SparseLVector instance \a self.
    #
    def __idiv__(t: int) -> SparseLVector: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> SparseLVector: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size = property(getSize)

    ##
    # \brief 
    #
    numElements = property(getNumElements)
