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
class LMatrixSlice(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LMatrixSlice instance.
    # \param self The \e %LMatrixSlice instance to initialize.
    # \param s 
    # 
    def __init__(s: LMatrixSlice) -> None: pass

    ##
    # \brief Initializes the \e %LMatrixSlice instance.
    # \param self The \e %LMatrixSlice instance to initialize.
    # \param e 
    # \param s1 
    # \param s2 
    # 
    def __init__(e: LMatrixExpression, s1: ast.Slice, s2: ast.Slice) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getStart1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStart2() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStride1() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getStride2() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %LMatrixSlice instance this method is called upon.
    # 
    # Different Python \e %LMatrixSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %LMatrixSlice instances \e a and \e b reference different C++ objects. 
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
    def assign(e: ConstFMatrixExpression) -> LMatrixSlice: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstDMatrixExpression) -> LMatrixSlice: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstLMatrixExpression) -> LMatrixSlice: pass

    ##
    # \brief 
    # \param e 
    # \return 
    #
    def assign(e: ConstULMatrixExpression) -> LMatrixSlice: pass

    ##
    # \brief 
    # \param s 
    # \return 
    #
    def assign(s: LMatrixSlice) -> LMatrixSlice: pass

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
    # \param s 
    #
    def swap(s: LMatrixSlice) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param j 
    # \param v 
    #
    def setElement(i: int, j: int, v: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getData() -> LMatrixExpression: pass

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
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param self The \e %LMatrixSlice instance this method is called upon.
    # \param s The \e %LMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(s: LMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %LMatrixSlice instance this method is called upon.
    # \param e The \e %ConstLMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param self The \e %LMatrixSlice instance this method is called upon.
    # \param s The \e %LMatrixSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(s: LMatrixSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %LMatrixSlice instance this method is called upon.
    # \param e The \e %ConstLMatrixExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstLMatrixExpression) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %LMatrixSlice instance.
    # \param self The \e %LMatrixSlice instance this method is called upon.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> LMatrixSlice: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %LMatrixSlice instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstLMatrixExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %LMatrixSlice instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %LMatrixSlice instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %LMatrixSlice instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrixSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstLMatrixExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLMatrixExpression) -> ConstLMatrixExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %LMatrixSlice instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %LMatrixSlice instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstLMatrixExpression instance holding the result of the division.
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
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param self The \e %LMatrixSlice instance acting as in-place addend.
    # \param s Specifies the second addend.
    # \return The updated \e %LMatrixSlice instance \a self.
    # 
    def __iadd__(s: LMatrixSlice) -> LMatrixSlice: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param self The \e %LMatrixSlice instance acting as in-place addend.
    # \param e Specifies the second addend.
    # \return The updated \e %LMatrixSlice instance \a self.
    # 
    def __iadd__(e: ConstLMatrixExpression) -> LMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param self The \e %LMatrixSlice instance acting as in-place minuend.
    # \param s Specifies the subtrahend.
    # \return The updated \e %LMatrixSlice instance \a self.
    # 
    def __isub__(s: LMatrixSlice) -> LMatrixSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param self The \e %LMatrixSlice instance acting as in-place minuend.
    # \param e Specifies the subtrahend.
    # \return The updated \e %LMatrixSlice instance \a self.
    # 
    def __isub__(e: ConstLMatrixExpression) -> LMatrixSlice: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param self The \e %LMatrixSlice instance acting as in-place multiplicand.
    # \param t Specifies the multiplier.
    # \return The updated \e %LMatrixSlice instance \a self.
    # 
    def __imul__(t: int) -> LMatrixSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param self The \e %LMatrixSlice instance acting as in-place dividend.
    # \param t Specifies the divisor.
    # \return The updated \e %LMatrixSlice instance \a self.
    # 
    def __idiv__(t: int) -> LMatrixSlice: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> LMatrixSlice: pass

    objectID = property(getObjectID)

    size1 = property(getSize1)

    size2 = property(getSize2)

    data = property(getData)

    start1 = property(getStart1)

    start2 = property(getStart2)

    stride1 = property(getStride1)

    stride2 = property(getStride2)
