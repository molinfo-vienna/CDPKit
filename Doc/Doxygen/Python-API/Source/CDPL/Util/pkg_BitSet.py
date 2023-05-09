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
# \brief 
#
class BitSet(Boost.Python.instance):

    ##
    # \brief 
    #
    npos = 18446744073709551615

    ##
    # \brief Initializes the \e %BitSet instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BitSet instance.
    # \param bs 
    #
    def __init__(bs: BitSet) -> None: pass

    ##
    # \brief Initializes the \e %BitSet instance.
    # \param num_bits 
    # \param value 
    #
    def __init__(num_bits: int, value: int = 0) -> None: pass

    ##
    # \brief Initializes the \e %BitSet instance.
    # \param bit_str 
    #
    def __init__(bit_str: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %BitSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BitSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param bs 
    #
    def swap(bs: BitSet) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BitSet instance \a bs.
    # \param bs The \e %BitSet instance to copy.
    # \return \a self
    #
    def assign(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param num_bits 
    # \param value 
    #
    def resize(num_bits: int, value: bool = False) -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param value 
    #
    def append(value: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def flip() -> BitSet: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def flip(idx: int) -> BitSet: pass

    ##
    # \brief 
    # \return 
    #
    def set() -> BitSet: pass

    ##
    # \brief 
    # \param idx 
    # \param value 
    # \return 
    #
    def set(idx: int, value: bool = True) -> BitSet: pass

    ##
    # \brief 
    # \return 
    #
    def reset() -> BitSet: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def reset(idx: int) -> BitSet: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def test(idx: int) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def findFirst() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def findNext(idx: int) -> int: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def isSubsetOf(bs: BitSet) -> bool: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def isProperSubsetOf(bs: BitSet) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getCount() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxSize() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def hasAny() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def hasNone() -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \param value 
    #
    def __setitem__(idx: int, value: bool) -> None: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def __and__(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def __or__(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def __xor__(bs: BitSet) -> BitSet: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - bs</tt>.
    # \param bs Specifies the subtrahend.
    # \return A \e %BitSet instance holding the result of the subtraction.
    #
    def __sub__(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def __iand__(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def __ior__(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param bs 
    # \return 
    #
    def __ixor__(bs: BitSet) -> BitSet: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= bs</tt>.
    # \param bs Specifies the subtrahend.
    # \return The updated \e %BitSet instance \a self.
    #
    def __isub__(bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \return 
    #
    def __long__() -> int: pass

    ##
    # \brief 
    # \param num_bits 
    # \return 
    #
    def __ilshift__(num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param num_bits 
    # \return 
    #
    def __lshift__(num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param num_bits 
    # \return 
    #
    def __irshift__(num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param num_bits 
    # \return 
    #
    def __rshift__(num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \return 
    #
    def __invert__() -> BitSet: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == bs</tt>.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != bs</tt>.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < bs</tt>.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= bs</tt>.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __le__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > bs</tt>.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __gt__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= bs</tt>.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ge__(bs: BitSet) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def __nonzero__() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    ##
    # \brief Returns a string representation of the \e %BitSet instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    empty = property(getEmpty)

    ##
    # \brief 
    #
    count = property(getCount)

    ##
    # \brief 
    #
    size = property(getSize)

    ##
    # \brief 
    #
    maxSize = property(getMaxSize)

    ##
    # \brief FIXME!
    #
    any = property(getAny)

    ##
    # \brief FIXME!
    #
    none = property(getNone)
