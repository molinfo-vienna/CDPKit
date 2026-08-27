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
# \brief Adapter that exposes a quaternion as a <em>4</em> element vector expression (indices map to the components C1, C2, C3, C4).
# 
class FQuaternionVectorAdapter(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %FQuaternionVectorAdapter instance \a a.
    # \param a The \c %FQuaternionVectorAdapter instance to copy.
    # 
    def __init__(a: FQuaternionVectorAdapter) -> None: pass

    ##
    # \brief Initializes the \c %FQuaternionVectorAdapter instance.
    # \param e 
    # 
    def __init__(e: FQuaternionExpression) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FQuaternionVectorAdapter instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FQuaternionVectorAdapter instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFVectorExpression) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDVectorExpression) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLVectorExpression) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped quaternion).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULVectorExpression) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Copies the components of <em>a</em> into this view (writing through to the wrapped quaternion).
    # 
    # \param a The source adapter.
    # 
    # \return \a self
    # 
    def assign(a: FQuaternionVectorAdapter) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Copies the components of <em>a</em> into this view (writing through to the wrapped quaternion).
    # 
    # \param a The source adapter.
    # 
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Tells whether the view is empty (always <tt>False</tt>, the view is fixed-size with 4 components).
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

    def getElement(i: int) -> float: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the components of this view with those of <em>a</em>.
    # 
    # \param a The adapter to swap with.
    # 
    def swap(a: FQuaternionVectorAdapter) -> None: pass

    def setElement(i: int, v: float) -> None: pass

    ##
    # \brief Returns a reference to the wrapped quaternion (via its stored closure).
    # 
    # \return A reference to the wrapped quaternion closure.
    # 
    def getData() -> FQuaternionExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == a</tt>.
    # \param a The \c %FQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(a: FQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != a</tt>.
    # \param a The \c %FQuaternionVectorAdapter instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(a: FQuaternionVectorAdapter) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstFVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstFVectorExpression) -> bool: pass

    ##
    # \brief Returns a reference to the quaternion component at index <em>i</em>.
    # 
    # \param i The zero-based component index (<em>0</em> = C1, <em>1</em> = C2, <em>2</em> = C3, <em>3</em> = C4).
    # 
    # \return A reference to the component. 
    # 
    # \throw Base.IndexError if <em>i</em> is not in the range [0, 3].
    # 
    def __call__(i: int) -> float: pass

    ##
    # \brief Returns a reference to the quaternion component at index <em>i</em>.
    # 
    # \param i The zero-based component index.
    # 
    # \return A reference to the component. 
    # 
    # \throw Base.IndexError if <em>i</em> is not in the range [0, 3].
    # 
    def __getitem__(i: int) -> float: pass

    ##
    # \brief Returns the dimensionality of the view (always <em>4</em>).
    # 
    # \return <em>4</em>.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %FQuaternionVectorAdapter instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> FQuaternionVectorAdapter: pass

    def __neg__() -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstFVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %FQuaternionVectorAdapter instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstFVectorExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstFMatrixExpression) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self // t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstFVectorExpression instance holding the result of the division.
    # 
    def __div__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the \e true division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstFVectorExpression instance holding the result of the division.
    # 
    def __truediv__(t: float) -> ConstFVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>t * self</tt>.
    # \param t Specifies the multiplicand.
    # \return A \c %ConstFVectorExpression instance holding the result of the multiplication.
    # 
    def __rmul__(t: float) -> ConstFVectorExpression: pass

    def __setitem__(i: int, v: float) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += a</tt>.
    # \param a Specifies the second addend.
    # \return The updated \c %FQuaternionVectorAdapter instance \a self.
    # 
    def __iadd__(a: FQuaternionVectorAdapter) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Adds the vector expression <em>e</em> componentwise to this view.
    # 
    # \param e The vector expression to add.
    # 
    # \return \a self
    # 
    def __iadd__(e: ConstFVectorExpression) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= a</tt>.
    # \param a Specifies the subtrahend.
    # \return The updated \c %FQuaternionVectorAdapter instance \a self.
    # 
    def __isub__(a: FQuaternionVectorAdapter) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> componentwise from this view.
    # 
    # \param e The vector expression to subtract.
    # 
    # \return \a self
    # 
    def __isub__(e: ConstFVectorExpression) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Multiplies every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: float) -> FQuaternionVectorAdapter: pass

    ##
    # \brief Divides every component of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar divisor.
    # 
    # \return \a self
    # 
    def __idiv__(t: float) -> FQuaternionVectorAdapter: pass

    def __itruediv__(t: float) -> FQuaternionVectorAdapter: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)
