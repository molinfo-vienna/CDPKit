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
# \brief Dynamic bitset class.
# 
# For further information see [\ref BDBS].
# 
class BitSet(Boost.Python.instance):

    ##
    # \brief 
    #
    npos = 18446744073709551615

    ##
    # \brief Initializes the \c %BitSet instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %BitSet instance \a bs.
    # \param bs The \c %BitSet instance to copy.
    # 
    def __init__(bs: BitSet) -> None: pass

    ##
    # \brief Initializes the \c %BitSet instance.
    # \param num_bits 
    # \param value 
    # 
    def __init__(num_bits: int, value: int = 0) -> None: pass

    ##
    # \brief Initializes the \c %BitSet instance.
    # \param bit_str 
    # 
    def __init__(bit_str: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %BitSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %BitSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def swap(bs: BitSet) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %BitSet instance \a bs.
    # \param bs The \c %BitSet instance to copy.
    # \return \a self
    # 
    def assign(bs: BitSet) -> BitSet: pass

    def resize(num_bits: int, value: bool = False) -> None: pass

    def clear() -> None: pass

    def append(value: bool) -> None: pass

    def flip() -> BitSet: pass

    def flip(idx: int) -> BitSet: pass

    def set() -> BitSet: pass

    def set(idx: int, value: bool = True) -> BitSet: pass

    def reset() -> BitSet: pass

    def reset(idx: int) -> BitSet: pass

    def test(idx: int) -> bool: pass

    def findFirst() -> int: pass

    def findNext(idx: int) -> int: pass

    def isSubsetOf(bs: BitSet) -> bool: pass

    def isProperSubsetOf(bs: BitSet) -> bool: pass

    def isEmpty() -> bool: pass

    def getCount() -> int: pass

    def getSize() -> int: pass

    def getMaxSize() -> int: pass

    def hasAny() -> bool: pass

    def hasNone() -> bool: pass

    def __getitem__(idx: int) -> bool: pass

    def __setitem__(idx: int, value: bool) -> None: pass

    def __and__(bs: BitSet) -> BitSet: pass

    def __or__(bs: BitSet) -> BitSet: pass

    def __xor__(bs: BitSet) -> BitSet: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - bs</tt>.
    # \param bs Specifies the subtrahend.
    # \return A \c %BitSet instance holding the result of the subtraction.
    # 
    def __sub__(bs: BitSet) -> BitSet: pass

    def __iand__(bs: BitSet) -> BitSet: pass

    def __ior__(bs: BitSet) -> BitSet: pass

    def __ixor__(bs: BitSet) -> BitSet: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= bs</tt>.
    # \param bs Specifies the subtrahend.
    # \return The updated \c %BitSet instance \a self.
    # 
    def __isub__(bs: BitSet) -> BitSet: pass

    def __long__() -> int: pass

    def __ilshift__(num_bits: int) -> BitSet: pass

    def __lshift__(num_bits: int) -> BitSet: pass

    def __irshift__(num_bits: int) -> BitSet: pass

    def __rshift__(num_bits: int) -> BitSet: pass

    def __invert__() -> BitSet: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == bs</tt>.
    # \param bs The \c %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != bs</tt>.
    # \param bs The \c %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < bs</tt>.
    # \param bs The \c %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __lt__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= bs</tt>.
    # \param bs The \c %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __le__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > bs</tt>.
    # \param bs The \c %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __gt__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= bs</tt>.
    # \param bs The \c %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ge__(bs: BitSet) -> bool: pass

    def __len__() -> int: pass

    def __nonzero__() -> bool: pass

    def __bool__() -> bool: pass

    ##
    # \brief Returns a string representation of the \c %BitSet instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    empty = property(isEmpty)

    count = property(getCount)

    size = property(getSize)

    maxSize = property(getMaxSize)

    any = property(hasAny)

    none = property(hasNone)
