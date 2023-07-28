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
# \brief A bounded 4x4 matrix holding unsigned integers of type <tt>unsigned long</tt>.
# 
class Matrix4UL(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param self The \e %Matrix4UL instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param self The \e %Matrix4UL instance to initialize.
    # \param v 
    # 
    def __init__(v: int) -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param self The \e %Matrix4UL instance to initialize.
    # \param m 
    # 
    def __init__(m: Matrix4UL) -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param arg1 The \e %Matrix4UL instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstFMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param arg1 The \e %Matrix4UL instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstDMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param arg1 The \e %Matrix4UL instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstLMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param arg1 The \e %Matrix4UL instance to initialize.
    # \param e 
    # 
    def __init__(e: ConstULMatrixExpression) -> None: pass

    ##
    # \brief Initializes the \e %Matrix4UL instance.
    # \param arg1 The \e %Matrix4UL instance to initialize.
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
    # \param self The \e %Matrix4UL instance this method is called upon.
    # 
    # Different Python \e %Matrix4UL instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Matrix4UL instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstFMatrixExpression) -> Matrix4UL: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstDMatrixExpression) -> Matrix4UL: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstLMatrixExpression) -> Matrix4UL: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstULMatrixExpression) -> Matrix4UL: pass

    ##
    # \brief 
    # \param m 
    # \return 
    #
    def assign(m: Matrix4UL) -> Matrix4UL: pass

    ##
    # \brief 
    # \param a 
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
    def swap(m: Matrix4UL) -> None: pass

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
    # \param self The \e %Matrix4UL instance this method is called upon.
    # \param m The \e %Matrix4UL instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(m: Matrix4UL) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %Matrix4UL instance this method is called upon.
    # \param e The \e %ConstULMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != m</tt>.
    # \param self The \e %Matrix4UL instance this method is called upon.
    # \param m The \e %Matrix4UL instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(m: Matrix4UL) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %Matrix4UL instance this method is called upon.
    # \param e The \e %ConstULMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstULMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Matrix4UL instance.
    # \param self The \e %Matrix4UL instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> Matrix4UL: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %Matrix4UL instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstULMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %Matrix4UL instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %Matrix4UL instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %Matrix4UL instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %Matrix4UL instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstULMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %Matrix4UL instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %Matrix4UL instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstULMatrixExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstULMatrixExpression: pass

    ##
    # \brief 
    # \param ij 
    # \param v 
    #
    def __setitem__(ij: tuple, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += m</tt>.
    # \param self The \e %Matrix4UL instance acting as in-place addend.
    # \param m Specifies the second addend.
    # \return The updated \e %Matrix4UL instance \a self.
    # 
    def __iadd__(m: Matrix4UL) -> Matrix4UL: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %Matrix4UL instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %Matrix4UL instance \a self.
    # 
    def __iadd__(e: ConstULMatrixExpression) -> Matrix4UL: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= m</tt>.
    # \param self The \e %Matrix4UL instance acting as in-place minuend.
    # \param m Specifies the subtrahend.
    # \return The updated \e %Matrix4UL instance \a self.
    # 
    def __isub__(m: Matrix4UL) -> Matrix4UL: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %Matrix4UL instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %Matrix4UL instance \a self.
    # 
    def __isub__(e: ConstULMatrixExpression) -> Matrix4UL: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %Matrix4UL instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %Matrix4UL instance \a self.
    # 
    def __imul__(t: int) -> Matrix4UL: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %Matrix4UL instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %Matrix4UL instance \a self.
    # 
    def __idiv__(t: int) -> Matrix4UL: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> Matrix4UL: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)
