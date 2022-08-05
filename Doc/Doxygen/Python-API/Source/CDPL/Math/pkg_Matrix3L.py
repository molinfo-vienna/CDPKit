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
class Matrix3L(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Matrix3L instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param v 
    #
    def __init__(v: int) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param m 
    #
    def __init__(m: Matrix3L) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param e 
    #
    def __init__(e: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param e 
    #
    def __init__(e: ConstDMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param e 
    #
    def __init__(e: ConstLMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param e 
    #
    def __init__(e: ConstULMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix3L instance.
    # \param a 
    #
    def __init__(a: object) -> None: pass

    ##
    # \brief 
    # \param v 
    #
    def clear(v: int = 0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %Matrix3L instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Matrix3L instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3L instance \a e.
    # \param e The \e %Matrix3L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstFMatrixExpression) -> Matrix3L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3L instance \a e.
    # \param e The \e %Matrix3L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstDMatrixExpression) -> Matrix3L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3L instance \a e.
    # \param e The \e %Matrix3L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstLMatrixExpression) -> Matrix3L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3L instance \a e.
    # \param e The \e %Matrix3L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(e: ConstULMatrixExpression) -> Matrix3L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3L instance \a m.
    # \param m The \e %Matrix3L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(m: Matrix3L) -> Matrix3L: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Matrix3L instance \a a.
    # \param a The \e %Matrix3L instance to copy.
    # \return The assignment target \a self.
    #
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSize1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getSize2() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def getElement(i: int, j: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param m 
    #
    def swap(m: Matrix3L) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \return 
    #
    def __call__(i: int, j: int) -> int: pass

    ##
    # \brief 
    # \param ij 
    # \return 
    #
    def __getitem__(ij: tuple) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == m</tt>.
    # \param m The \e %Matrix3L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(m: Matrix3L) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \e %Matrix3L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param m The \e %Matrix3L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(m: Matrix3L) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \e %Matrix3L instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Matrix3L instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> Matrix3L: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \e %Matrix3L instance holding the result of the addition.
    #
    def __add__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \e %Matrix3L instance holding the result of the subtraction.
    #
    def __sub__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \e %Matrix3L instance holding the result of the multiplication.
    #
    def __mul__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %Matrix3L instance holding the result of the multiplication.
    #
    def __mul__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \e %Matrix3L instance holding the result of the multiplication.
    #
    def __mul__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \e %Matrix3L instance holding the result of the division.
    #
    def __div__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief 
    # \param ij 
    # \param v 
    #
    def __setitem__(ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += m</tt>.
    # \param m Specifies the second addend.
    # \return The updated \e %Matrix3L instance \a self.
    #
    def __iadd__(m: Matrix3L) -> Matrix3L: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \e %Matrix3L instance \a self.
    #
    def __iadd__(e: ConstLMatrixExpression) -> Matrix3L: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= m</tt>.
    # \param m Specifies the subtrahend.
    # \return The updated \e %Matrix3L instance \a self.
    #
    def __isub__(m: Matrix3L) -> Matrix3L: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \e %Matrix3L instance \a self.
    #
    def __isub__(e: ConstLMatrixExpression) -> Matrix3L: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \e %Matrix3L instance \a self.
    #
    def __imul__(t: int) -> Matrix3L: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \e %Matrix3L instance \a self.
    #
    def __idiv__(t: int) -> Matrix3L: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> Matrix3L: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    size1 = property(getSize1)

    ##
    # \brief 
    #
    size2 = property(getSize2)
