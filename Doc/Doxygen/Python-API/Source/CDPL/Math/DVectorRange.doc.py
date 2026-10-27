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
class DVectorRange(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c DVectorRange instance \a r.
    # \param r The \c DVectorRange instance to copy.
    # 
    def __init__(r: DVectorRange) -> None: pass

    ##
    # \brief Contructs the \c DVectorRange instance.
    # \param e 
    # \param r 
    # 
    def __init__(e: DVectorExpression, r: Range) -> None: pass

    ##
    # \brief Returns the start index of the viewed range within the wrapped vector.
    # 
    # \return The start index of the range.
    # 
    def getStart() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DVectorRange instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DVectorRange instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> DVectorRange: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> DVectorRange: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> DVectorRange: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> DVectorRange: pass

    ##
    # \brief Copies the elements of <em>r</em> into this view (writing through to the wrapped vector).
    # 
    # \param r The source range view.
    # 
    # \return \a self.
    # 
    def assign(r: DVectorRange) -> DVectorRange: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this view.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> DVectorRange: pass

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

    ##
    # \brief Returns the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return The value of the element <tt>v(range(i))</tt>.
    # 
    def getElement(i: int) -> float: pass

    ##
    # \brief Converts the \c DVectorRange instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the elements of this view with those of <em>r</em>.
    # 
    # \param r The view to swap with.
    # 
    def swap(r: DVectorRange) -> None: pass

    ##
    # \brief Sets the value of the element at index \a i of the view to \a v.
    # \param i The zero-based index within the view.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns the wrapped vector.
    # 
    # \return The wrapped vector closure.
    # 
    def getData() -> DVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == r</tt>.
    # \param r The \c DVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(r: DVectorRange) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != r</tt>.
    # \param r The \c DVectorRange instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(r: DVectorRange) -> bool: pass

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
    # \return The value of the element <tt>v(range(i))</tt>.
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns the element at index <em>i</em> of the view.
    # 
    # \param i The zero-based index within the view.
    # 
    # \return The value of the element <tt>v(range(i))</tt>.
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the size of the view (number of elements covered by the range).
    # 
    # \return The number of elements in the view.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c DVectorRange instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DVectorRange: pass

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
    # \return A \c DVectorRange instance holding the result of the subtraction.
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

    ##
    # \brief Sets the value of the element at index \a i of the view to \a v.
    # \param i The zero-based index within the view.
    # \param v The new value of the element.
    # \throw Base.IndexError if \a i is not in the range [0, getSize()).
    # 
    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Adds the vector range <em>r</em> componentwise to this view.
    # 
    # \param r The vector range to add.
    # 
    # \return \a self.
    # 
    def __iadd__(r: DVectorRange) -> DVectorRange: pass

    ##
    # \brief Adds the vector expression <em>e</em> componentwise to this view.
    # 
    # \param e The vector expression to add.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDVectorExpression) -> DVectorRange: pass

    ##
    # \brief Subtracts the vector range <em>r</em> componentwise from this view.
    # 
    # \param r The vector range to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(r: DVectorRange) -> DVectorRange: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> componentwise from this view.
    # 
    # \param e The vector expression to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDVectorExpression) -> DVectorRange: pass

    ##
    # \brief Multiplies every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DVectorRange: pass

    ##
    # \brief Divides every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DVectorRange: pass

    ##
    # \brief Divides every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DVectorRange: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    start = property(getStart)
