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
# \brief Vector expression proxy that views a contiguous half-open subrange of an underlying vector.
# 
class ConstLVectorRange(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %ConstLVectorRange instance \a r.
    # \param r The \c %ConstLVectorRange instance to copy.
    # 
    def __init__(r: ConstLVectorRange) -> None: pass

    ##
    # \brief Initializes the \c %ConstLVectorRange instance.
    # \param e 
    # \param r 
    # 
    def __init__(e: ConstLVectorExpression, r: Range) -> None: pass

    ##
    # \brief Returns the start index of the viewed range within the wrapped vector.
    # 
    # \return The start index of the range.
    # 
    def getStart() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ConstLVectorRange instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ConstLVectorRange instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Tells whether the view is empty (zero-length range).
    # 
    # \return <tt>True</tt> if the range is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the size of the view (number of elements covered by the range).
    # 
    # \return The number of elements in the view.
    # 
    def getSize() -> int: pass

    def getElement(i: int) -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Returns a reference to the wrapped vector (via its stored closure).
    # 
    # \return A reference to the wrapped vector closure.
    # 
    def getData() -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \c %ConstLVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: ConstLVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstLVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \c %ConstLVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: ConstLVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstLVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns a reference to the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return A reference to the underlying element <tt>v(range(i))</tt>.
    # 
    def __call__(i: int) -> int: pass

    ##
    # \brief Returns a reference to the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return A reference to the underlying element.
    # 
    def __getitem__(i: int) -> int: pass

    ##
    # \brief Returns the size of the view (number of elements covered by the range).
    # 
    # \return The number of elements in the view.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %ConstLVectorRange instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> ConstLVectorRange: pass

    def __neg__() -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstLVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %ConstLVectorRange instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstLVectorExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstLMatrixExpression) -> ConstLVectorExpression: pass

    ##
    # \brief Divides every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __div__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Divides every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __truediv__(t: int) -> ConstLVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstLVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstLVectorExpression: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    start = property(getStart)
