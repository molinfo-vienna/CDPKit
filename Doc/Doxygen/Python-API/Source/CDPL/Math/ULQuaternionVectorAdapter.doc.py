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
# \brief Adapter that exposes a quaternion as a <em>4</em> element vector expression (indices map to the components <em>C1</em>, <em>C2</em>, <em>C3</em>, <em>C4</em>).
# 
class ULQuaternionVectorAdapter(Boost.Python.instance):

    ##
    # \brief Contructs a copy of the \c ULQuaternionVectorAdapter instance \a qa.
    # \param qa The \c ULQuaternionVectorAdapter instance to copy.
    # 
    def __init__(qa: ULQuaternionVectorAdapter) -> None: pass

    ##
    # \brief Constructs the adapter wrapping the quaternion <em>q</em>.
    # 
    # \param q The quaternion to be viewed as a <em>4</em> element vector.
    # 
    def __init__(q: ULQuaternionExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ULQuaternionVectorAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ULQuaternionVectorAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstFVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstDVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstLVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view (writing through to the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self.
    # 
    def assign(e: ConstULVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Copies the components of <em>qa</em> into this view (writing through to the wrapped quaternion).
    # 
    # \param qa The source adapter.
    # 
    # \return \a self.
    # 
    def assign(qa: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the contents of the \c numpy.ndarray object \a a to this view.
    # \param a The \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def assign(a: object) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Tells whether the view is empty (always <tt>False</tt>).
    # 
    # \return <tt>False</tt>.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the dimensionality of the view (always <em>4</em>).
    # 
    # \return <em>4</em>.
    # 
    def getSize() -> int: pass

    ##
    # \brief Returns the quaternion component at index <em>i</em>.
    # 
    # \param i The zero-based component index (<em>0</em> = <em>C1</em>, <em>1</em> = <em>C2</em>, <em>2</em> = <em>C3</em>, <em>3</em> = <em>C4</em>).
    # 
    # \return The value of the component. 
    # 
    # \throw Base.IndexError if <em>i</em> is not in the range [0, 3].
    # 
    def getElement(i: int) -> int: pass

    ##
    # \brief Converts the \c ULQuaternionVectorAdapter instance into a corresponding \c numpy.ndarray object.
    # \return The generated \c numpy.ndarray object.
    # \see [\ref NUMPY]
    # 
    def toArray() -> object: pass

    ##
    # \brief Swaps the components of this view with those of <em>qa</em>.
    # 
    # \param qa The adapter to swap with.
    # 
    def swap(qa: ULQuaternionVectorAdapter) -> None: pass

    ##
    # \brief Sets the value of the quaternion component at index \a i to \a v.
    # \param i The zero-based component index (\e 0 = C1, \e 1 = C2, \e 2 = C3, \e 3 = C4).
    # \param v The new value of the component.
    # \throw Base.IndexError if \a i is not in the range [0, 3].
    # 
    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Returns the wrapped quaternion.
    # 
    # \return The wrapped quaternion closure.
    # 
    def getData() -> ULQuaternionExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == qa</tt>.
    # \param qa The \c ULQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(qa: ULQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != qa</tt>.
    # \param qa The \c ULQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(qa: ULQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the quaternion component at index <em>i</em>.
    # 
    # \param i The zero-based component index (<em>0</em> = <em>C1</em>, <em>1</em> = <em>C2</em>, <em>2</em> = <em>C3</em>, <em>3</em> = <em>C4</em>).
    # 
    # \return The value of the component. 
    # 
    # \throw Base.IndexError if <em>i</em> is not in the range [0, 3].
    # 
    def __call__(i: int) -> int: pass

    ##
    # \brief Returns the quaternion component at index <em>i</em>.
    # 
    # \param i The zero-based component index (<em>0</em> = <em>C1</em>, <em>1</em> = <em>C2</em>, <em>2</em> = <em>C3</em>, <em>3</em> = <em>C4</em>).
    # 
    # \return The value of the component. 
    # 
    # \throw Base.IndexError if <em>i</em> is not in the range [0, 3].
    # 
    def __getitem__(i: int) -> int: pass

    ##
    # \brief Returns the dimensionality of the view (always <em>4</em>).
    # 
    # \return <em>4</em>.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c ULQuaternionVectorAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief Returns \a self.
    # \return \a self.
    # 
    def __pos__() -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Returns the result of the operation <tt>self * -1</tt>.
    # \return A \c ConstULVectorExpression instance holding the result of the element negation.
    # 
    def __neg__() -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c ConstULVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c ULQuaternionVectorAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstULVectorExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c ConstULVectorExpression instance holding the result of the division.
    # 
    def __truediv__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Sets the value of the quaternion component at index \a i to \a v.
    # \param i The zero-based component index (\e 0 = C1, \e 1 = C2, \e 2 = C3, \e 3 = C4).
    # \param v The new value of the component.
    # \throw Base.IndexError if \a i is not in the range [0, 3].
    # 
    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Adds the quaternion adapter <em>qa</em> componentwise to this view.
    # 
    # \param qa The quaternion adapter to add.
    # 
    # \return \a self.
    # 
    def __iadd__(qa: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Adds the vector expression <em>e</em> componentwise to this view.
    # 
    # \param e The vector expression to add.
    # 
    # \return \a self.
    # 
    def __iadd__(e: ConstULVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Subtracts the quaternion adapter <em>qa</em> componentwise from this view.
    # 
    # \param qa The quaternion adapter to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(qa: ULQuaternionVectorAdapter) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> componentwise from this view.
    # 
    # \param e The vector expression to subtract.
    # 
    # \return \a self.
    # 
    def __isub__(e: ConstULVectorExpression) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Multiplies every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self.
    # 
    def __imul__(t: int) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Divides every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __idiv__(t: int) -> ULQuaternionVectorAdapter: pass

    ##
    # \brief Divides every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self.
    # 
    def __itruediv__(t: int) -> ULQuaternionVectorAdapter: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)
