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
# \brief A bounded 3 element vector holding unsigned integers of type <tt>unsigned long</tt>.
# 
class Vector3UL(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Vector3UL instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %Vector3UL instance \a v.
    # \param v The \e %Vector3UL instance to copy.
    # 
    def __init__(v: Vector3UL) -> None: pass

    ##
    # \brief Initializes the \e %Vector3UL instance.
    # \param v 
    # 
    def __init__(v: int) -> None: pass

    ##
    # \brief Initializes the \e %Vector3UL instance.
    # \param e 
    # 
    def __init__(e: ConstFVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector3UL instance.
    # \param e 
    # 
    def __init__(e: ConstDVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector3UL instance.
    # \param e 
    # 
    def __init__(e: ConstLVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector3UL instance.
    # \param e 
    # 
    def __init__(e: ConstULVectorExpression) -> None: pass

    ##
    # \brief Initializes the \e %Vector3UL instance.
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
    # 
    # Different Python \c %Vector3UL instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Vector3UL instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstFVectorExpression instance \a e.
    # \param e The \c %ConstFVectorExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstFVectorExpression) -> Vector3UL: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstDVectorExpression instance \a e.
    # \param e The \c %ConstDVectorExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstDVectorExpression) -> Vector3UL: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstLVectorExpression instance \a e.
    # \param e The \c %ConstLVectorExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstLVectorExpression) -> Vector3UL: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ConstULVectorExpression instance \a e.
    # \param e The \c %ConstULVectorExpression instance to copy.
    # \return \a self
    # 
    def assign(e: ConstULVectorExpression) -> Vector3UL: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %Vector3UL instance \a v.
    # \param v The \c %Vector3UL instance to copy.
    # \return \a self
    # 
    def assign(v: Vector3UL) -> Vector3UL: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %object instance \a a.
    # \param a The \c %object instance to copy.
    # \return \a self
    # 
    def assign(a: object) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def getElement(i: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def toArray() -> object: pass

    ##
    # \brief 
    # \param v 
    #
    def swap(v: Vector3UL) -> None: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def setElement(i: int, v: int) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == v</tt>.
    # \param v The \c %Vector3UL instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(v: Vector3UL) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == e</tt>.
    # \param e The \c %ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != v</tt>.
    # \param v The \c %Vector3UL instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(v: Vector3UL) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != e</tt>.
    # \param e The \c %ConstULVectorExpression instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(e: ConstULVectorExpression) -> bool: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __call__(i: int) -> int: pass

    ##
    # \brief 
    # \param i 
    # \return 
    #
    def __getitem__(i: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief Returns a string representation of the \e %Vector3UL instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def __pos__() -> Vector3UL: pass

    ##
    # \brief 
    # \return 
    #
    def __neg__() -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the addition operation <tt>self + e</tt>.
    # \param e Specifies the second addend.
    # \return A \c %ConstULVectorExpression instance holding the result of the addition.
    # 
    def __add__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - e</tt>.
    # \param e Specifies the subtrahend.
    # \return A \c %Vector3UL instance holding the result of the subtraction.
    # 
    def __sub__(e: ConstULVectorExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * t</tt>.
    # \param t Specifies the multiplier.
    # \return A \c %ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the multiplication operation <tt>self * e</tt>.
    # \param e Specifies the multiplier.
    # \return A \c %ConstULVectorExpression instance holding the result of the multiplication.
    # 
    def __mul__(e: ConstULMatrixExpression) -> ConstULVectorExpression: pass

    ##
    # \brief Returns the result of the division operation <tt>self / t</tt>.
    # \param t Specifies the divisor.
    # \return A \c %ConstULVectorExpression instance holding the result of the division.
    # 
    def __div__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __truediv__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __rmul__(t: int) -> ConstULVectorExpression: pass

    ##
    # \brief 
    # \param i 
    # \param v 
    #
    def __setitem__(i: int, v: int) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += v</tt>.
    # \param v Specifies the second addend.
    # \return The updated \c %Vector3UL instance \a self.
    # 
    def __iadd__(v: Vector3UL) -> Vector3UL: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += e</tt>.
    # \param e Specifies the second addend.
    # \return The updated \c %Vector3UL instance \a self.
    # 
    def __iadd__(e: ConstULVectorExpression) -> Vector3UL: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= v</tt>.
    # \param v Specifies the subtrahend.
    # \return The updated \c %Vector3UL instance \a self.
    # 
    def __isub__(v: Vector3UL) -> Vector3UL: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= e</tt>.
    # \param e Specifies the subtrahend.
    # \return The updated \c %Vector3UL instance \a self.
    # 
    def __isub__(e: ConstULVectorExpression) -> Vector3UL: pass

    ##
    # \brief Performs the in-place multiplication operation <tt>self *= t</tt>.
    # \param t Specifies the multiplier.
    # \return The updated \c %Vector3UL instance \a self.
    # 
    def __imul__(t: int) -> Vector3UL: pass

    ##
    # \brief Performs the in-place division operation <tt>self /= t</tt>.
    # \param t Specifies the divisor.
    # \return The updated \c %Vector3UL instance \a self.
    # 
    def __idiv__(t: int) -> Vector3UL: pass

    ##
    # \brief 
    # \param t 
    # \return 
    #
    def __itruediv__(t: int) -> Vector3UL: pass

    objectID = property(getObjectID)

    size = property(getSize)
