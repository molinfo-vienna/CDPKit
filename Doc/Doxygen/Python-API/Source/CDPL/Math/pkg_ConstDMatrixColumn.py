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
class ConstDMatrixColumn(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ConstDMatrixColumn instance.
    # \param self The \e %ConstDMatrixColumn instance to initialize.
    # \param c 
    #
    def __init__(self: object, c: ConstDMatrixColumn) -> None: pass

    ##
    # \brief Initializes the \e %ConstDMatrixColumn instance.
    # \param self The \e %ConstDMatrixColumn instance to initialize.
    # \param e 
    # \param i 
    #
    def __init__(self: object, e: ConstDMatrixExpression, i: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def getIndex(self: ConstDMatrixColumn) -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    #
    # Different Python \e %ConstDMatrixColumn instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ConstDMatrixColumn instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ConstDMatrixColumn) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def isEmpty(self: ConstDMatrixColumn) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def getSize(self: ConstDMatrixColumn) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param i 
    # \return 
    #
    def getElement(self: ConstDMatrixColumn, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def toArray(self: ConstDMatrixColumn) -> object: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def getData(self: ConstDMatrixColumn) -> ConstDMatrixExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == c</tt>.
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param c The \e %ConstDMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ConstDMatrixColumn, c: ConstDMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param e The \e %ConstDMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: ConstDMatrixColumn, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != c</tt>.
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param c The \e %ConstDMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ConstDMatrixColumn, c: ConstDMatrixColumn) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param e The \e %ConstDMatrixColumn instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: ConstDMatrixColumn, e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param i 
    # \return 
    #
    def __call__(self: ConstDMatrixColumn, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param i 
    # \return 
    #
    def __getitem__(self: ConstDMatrixColumn, i: int) -> float: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def __len__(self: ConstDMatrixColumn) -> int: pass

    ##
    # \brief Returns a string representation of the \e %ConstDMatrixColumn instance.
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: ConstDMatrixColumn) -> str: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def __pos__(self: ConstDMatrixColumn) -> ConstDMatrixColumn: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \return 
    #
    def __neg__(self: object) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param self The \e %ConstDMatrixColumn instance representing the first addend.
    # \param e Specifies the second addend.
    # \return A \e %ConstDMatrixColumn instance holding the result of the addition.
    #
    def __add__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param self The \e %ConstDMatrixColumn instance acting as minuend.
    # \param e Specifies the subtrahend.
    # \return A \e %ConstDMatrixColumn instance holding the result of the subtraction.
    #
    def __sub__(self: object, e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param self The \e %ConstDMatrixColumn instance acting as multiplicand.
    # \param t Specifies the multiplier.
    # \return A \e %ConstDMatrixColumn instance holding the result of the multiplication.
    #
    def __mul__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param self The \e %ConstDMatrixColumn instance acting as multiplicand.
    # \param e Specifies the multiplier.
    # \return A \e %ConstDMatrixColumn instance holding the result of the multiplication.
    #
    def __mul__(self: object, e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param self The \e %ConstDMatrixColumn instance acting as dividend.
    # \param t Specifies the divisor.
    # \return A \e %ConstDMatrixColumn instance holding the result of the division.
    #
    def __div__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param t 
    # \return 
    #
    def __truediv__(self: object, t: float) -> ConstDVectorExpression: pass

    ##
    # \brief 
    # \param self The \e %ConstDMatrixColumn instance this method is called upon.
    # \param t 
    # \return 
    #
    def __rmul__(self: object, t: float) -> ConstDVectorExpression: pass

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
    data = property(getData)

    ##
    # \brief 
    #
    index = property(getIndex)
