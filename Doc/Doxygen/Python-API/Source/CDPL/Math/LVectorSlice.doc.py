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
# \brief Vector expression proxy that views a strided slice of an underlying vector.
# 
class LVectorSlice(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %LVectorSlice instance \a s.
    # \param s The \c %LVectorSlice instance to copy.
    # 
    def __init__(s: LVectorSlice) -> None: pass

    ##
    # \brief Initializes the \c %LVectorSlice instance.
    # \param e 
    # \param s 
    # 
    def __init__(e: LVectorExpression, s: Slice) -> None: pass

    ##
    # \brief Returns the start index of the slice within the wrapped vector.
    # 
    # \return The start index of the slice.
    # 
    def getStart() -> int: pass

    ##
    # \brief Returns the stride of the slice (step between successive viewed elements).
    # 
    # \return The stride.
    # 
    def getStride() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %LVectorSlice instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %LVectorSlice instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstFVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstDVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstLVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Assigns the vector expression <em>e</em> to this view without intermediate temporary (use only when <em>e</em> does not alias the wrapped vector).
    # 
    # \param e The source vector expression.
    # 
    # \return \a self
    # 
    def assign(e: ConstULVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Copies the elements of <em>s</em> into this view (writing through to the wrapped vector).
    # 
    # \param s The source slice view.
    # 
    # \return \a self
    # 
    def assign(s: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief Tells whether the view is empty (zero-length slice).
    # 
    # \return <tt>True</tt> if the slice is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the size of the view (number of elements covered by the slice).
    # 
    # \return The number of elements in the view.
    # 
    def getSize() -> int: pass

    def getElement(i: int) -> int: pass

    def toArray() -> object: pass

    ##
    # \brief Swaps the elements of this view with those of <em>s</em>.
    # 
    # \param s The view to swap with.
    # 
    def swap(s: LVectorSlice) -> None: pass

    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Returns a reference to the wrapped vector (via its stored closure).
    # 
    # \return A reference to the wrapped vector closure.
    # 
    def getData() -> LVectorExpression: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == s</tt>.
    # \param s The \c %LVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(s: LVectorSlice) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstLVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstLVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != s</tt>.
    # \param s The \c %LVectorSlice instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(s: LVectorSlice) -> bool: pass

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
    # \return A reference to the underlying element <tt>v(slice(i))</tt>.
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
    # \brief Returns the size of the view (number of elements covered by the slice).
    # 
    # \return The number of elements in the view.
    # 
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \c %LVectorSlice instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    def __pos__() -> LVectorSlice: pass

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
    # \return A \c %LVectorSlice instance holding the result of the subtraction.
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

    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += s</tt>.
    # \param s Specifies the second addend.
    # \return The updated \c %LVectorSlice instance \a self.
    # 
    def __iadd__(s: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief Adds the vector expression <em>e</em> componentwise to this view.
    # 
    # \param e The vector expression to add.
    # 
    # \return \a self
    # 
    def __iadd__(e: ConstLVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= s</tt>.
    # \param s Specifies the subtrahend.
    # \return The updated \c %LVectorSlice instance \a self.
    # 
    def __isub__(s: LVectorSlice) -> LVectorSlice: pass

    ##
    # \brief Subtracts the vector expression <em>e</em> componentwise from this view.
    # 
    # \param e The vector expression to subtract.
    # 
    # \return \a self
    # 
    def __isub__(e: ConstLVectorExpression) -> LVectorSlice: pass

    ##
    # \brief Multiplies every element of this view by the scalar <em>t</em>.
    # 
    # \param t The scalar multiplier.
    # 
    # \return \a self
    # 
    def __imul__(t: int) -> LVectorSlice: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %LVectorSlice instance \a self.
    # 
    def __idiv__(t: int) -> LVectorSlice: pass

    def __itruediv__(t: int) -> LVectorSlice: pass

    objectID = property(getObjectID)

    size = property(getSize)

    data = property(getData)

    start = property(getStart)

    stride = property(getStride)
