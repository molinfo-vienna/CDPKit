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
# \brief Vector expression that exposes a vector as its homogeneous-coordinate extension by appending an implicit <em>1</em> at the end.
# 
class ConstDHomogenousCoordsAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ConstDHomogenousCoordsAdapter instance \a va.
    # \param va The \c ConstDHomogenousCoordsAdapter instance to copy.
    # 
    def __init__(va: ConstDHomogenousCoordsAdapter) -> None: pass

    ##
    # \brief Constructs the adapter wrapping <em>v</em>.
    # 
    # \param v The vector to be viewed as its homogeneous-coordinate extension.
    # 
    def __init__(v: ConstDVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ConstDHomogenousCoordsAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ConstDHomogenousCoordsAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Tells whether the view is empty (always <tt>False</tt>).
    # 
    # \return <tt>False</tt>.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the dimensionality of the view (wrapped vector size + <em>1</em>).
    # 
    # \return The view size.
    # 
    def getSize() -> int: pass

    ##
    # \brief Returns the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return The value of the element.
    # 
    def getElement(i: int) -> float: pass

    ##
    # \brief Converts the \c ConstDHomogenousCoordsAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Returns the wrapped vector.
    # 
    # \return The wrapped vector closure.
    # 
    def getData() -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == va</tt>.
    # \param va The \c ConstDHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(va: ConstDHomogenousCoordsAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != va</tt>.
    # \param va The \c ConstDHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(va: ConstDHomogenousCoordsAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return The value of the element.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return The value of the element.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the dimensionality of the view (wrapped vector size + <em>1</em>).
    # 
    # \return The view size.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c ConstDHomogenousCoordsAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ConstDHomogenousCoordsAdapter: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstDVectorExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstDVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ConstDHomogenousCoordsAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstDVectorExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstDMatrixExpression) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDVectorExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstDVectorExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstDVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstDVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstDVectorExpression: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)
