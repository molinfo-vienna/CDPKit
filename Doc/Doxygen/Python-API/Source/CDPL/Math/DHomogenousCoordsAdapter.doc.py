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
class DHomogenousCoordsAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c DHomogenousCoordsAdapter instance \a va.
    # \param va The \c DHomogenousCoordsAdapter instance to copy.
    # 
    def __init__(va: DHomogenousCoordsAdapter) -> None: pass

    ##
    # \brief Constructs the adapter wrapping <em>v</em>.
    # 
    # \param v The vector to be viewed as its homogeneous-coordinate extension.
    # 
    def __init__(v: DVectorExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c DHomogenousCoordsAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c DHomogenousCoordsAdapter instances \e a and \e b reference different C++ objects. 
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
    def assign(e: ConstFVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Copies the elements of <em>va</em> into this view (writing through to the wrapped vector and to the extension element).
    # 
    # \param va The source adapter.
    # 
    # \return \a self.
    # 
    def assign(va: DHomogenousCoordsAdapter) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this view.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> DHomogenousCoordsAdapter: pass

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
    # \brief Converts the \c DHomogenousCoordsAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the contents of this view with those of <em>va</em>.
    # 
    # \param va The view to swap with.
    # 
    def swap(va: DHomogenousCoordsAdapter) -> None: pass

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
    # \brief Returns the result of the comparison operation <tt>self == va</tt>.
    # \param va The \c DHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(va: DHomogenousCoordsAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstDVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstDVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != va</tt>.
    # \param va The \c DHomogenousCoordsAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(va: DHomogenousCoordsAdapter) -> bool: pass

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
    # \brief Returns a string representation of the \c DHomogenousCoordsAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> DHomogenousCoordsAdapter: pass

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
    # \return A \c DHomogenousCoordsAdapter instance holding the result of the subtraction.
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
    # \brief Adds the vector adapter <em>va</em> componentwise to this view.
    # 
    # \param va The vector adapter to add.
    # 
    # \return \a self.
    # 
    def __iadd__(va: DHomogenousCoordsAdapter) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Adds the vector expression <em>e</em> componentwise to this view.
    # 
    # \param e The vector expression to add.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstDVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Subtracts the vector adapter <em>va</em> componentwise from this view.
    # 
    # \param va The vector adapter to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(va: DHomogenousCoordsAdapter) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> componentwise from this view.
    # 
    # \param e The vector expression to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstDVectorExpression) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Multiplies every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: float) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Divides every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: float) -> DHomogenousCoordsAdapter: pass

    ##
    # \brief Divides every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: float) -> DHomogenousCoordsAdapter: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)
