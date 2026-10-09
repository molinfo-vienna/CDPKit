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
# \brief Data structure for the storage and processing of variably sized bit sets.
# 
# For further information see [\ref BDBS].
# 
class BitSet(Boost.Python.instance):

    ##
    # \brief Specifies an invalid bit index.
    # 
    npos = 18446744073709551615

    ##
    # \brief Constructs a \c BitSet instance of size zero.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c BitSet instance \a bs.
    # \param bs The \c BitSet instance to copy.
    # 
    def __init__(bs: BitSet) -> None: pass

    ##
    # \brief Constructs a \c BitSet instance of size \a num_bits initialized to the bits in \a value.
    # 
    # The first \e M bits (where \e M is the number of bits of the data type <tt>unsigned long</tt>) are initialized to the corresponding bits in
    # \a value and all other bits, if any, to zero.
    # 
    # \param num_bits The size of the bitset.
    # \param value The value to initialize the bitset from.
    # 
    def __init__(num_bits: int, value: int = 0) -> None: pass

    ##
    # \brief Constructs a \c BitSet instance with size and bit values specified by the string \a bit_str.
    # 
    # The value of bit \e i is specified by the character '1' (= on) or '0' (= off) at index \e i of \a bit_str. 
    # 
    # \param bit_str The string specifying the desired bit values.
    # 
    def __init__(bit_str: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c BitSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c BitSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Swaps the contents of this bitset and the bitset \a bs.
    # \param bs The other \c BitSet instance.
    # 
    def swap(bs: BitSet) -> None: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c BitSet instance \a bs.
    # \param bs The \c BitSet instance to copy.
    # \return \a self
    # 
    def assign(bs: BitSet) -> BitSet: pass

    ##
    # \brief Changes the number of bits to \a num_bits.
    # \param num_bits The new size of the bitset.
    # \param value The value of emerging new bits.
    # 
    def resize(num_bits: int, value: bool = False) -> None: pass

    ##
    # \brief Resizes the bitset to zero length.
    # 
    def clear() -> None: pass

    ##
    # \brief Increases the size of the bitset by one, and sets the value of the new most significant bit to \a value.
    # \param value The value of the new bit.
    # 
    def append(value: bool) -> None: pass

    ##
    # \brief Toggles the value of every bit.
    # \return \a self.
    # 
    def flip() -> BitSet: pass

    ##
    # \brief Toggles the value of the bit at index \a idx.
    # \param idx The zero-based index of the bit.
    # \return \a self.
    # 
    def flip(idx: int) -> BitSet: pass

    ##
    # \brief Sets all bits to \c True.
    # \return \a self.
    # 
    def set() -> BitSet: pass

    ##
    # \brief Sets the bit at index \a idx to \a value.
    # \param idx The zero-based index of the bit.
    # \param value The new value of the bit.
    # \return \a self.
    # 
    def set(idx: int, value: bool = True) -> BitSet: pass

    ##
    # \brief Sets all bits to \c False.
    # \return \a self.
    # 
    def reset() -> BitSet: pass

    ##
    # \brief Sets the bit at index \a idx to \c False.
    # \param idx The zero-based index of the bit.
    # \return \a self.
    # 
    def reset(idx: int) -> BitSet: pass

    ##
    # \brief Returns the value of the bit at index \a idx.
    # \param idx The zero-based index of the bit.
    # \return The value of the bit.
    # 
    def test(idx: int) -> bool: pass

    ##
    # \brief Returns the index of the first set bit (if any).
    # \return The lowest zero-based index of a set bit or npos if no such bit exists.
    # 
    def findFirst() -> int: pass

    ##
    # \brief Returns the index of the first set bit after \a idx (if any).
    # \return The lowest zero-based index > \a idx of a set bit or npos if no such bit exists.
    # 
    def findNext(idx: int) -> int: pass

    ##
    # \brief Checks whether this bitset is a subset of the bitset \a bs.
    # \param bs The other \c BitSet instance to test against.
    # \return \c True if for every bit that is set in this bitset the corresponding bit in \a bs is also set, and \c False otherwise.
    # 
    def isSubsetOf(bs: BitSet) -> bool: pass

    ##
    # \brief Checks whether this bitset is a proper subset of the bitset \a bs.
    # \param bs The other \c BitSet instance to test against.
    # \return \c True if for every bit that is set in this bitset the corresponding bit in \a bs is also set and furthermore
    #         <tt>self.getCount() < bs.getCount()</tt>. Otherwise \c False is returned.
    # 
    def isProperSubsetOf(bs: BitSet) -> bool: pass

    ##
    # \brief Checks whether this bitset has size zero.
    # \return \c True if the size is zero, and \c False  otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Returns the number of set bits.
    # \return The number of set bits.
    # 
    def getCount() -> int: pass

    ##
    # \brief Returns the size of the bitset.
    # \return The size of the bitset.
    # 
    def getSize() -> int: pass

    def getMaxSize() -> int: pass

    def hasAny() -> bool: pass

    def hasNone() -> bool: pass

    def __getitem__(idx: int) -> bool: pass

    def __setitem__(idx: int, value: bool) -> None: pass

    def __and__(bs: BitSet) -> BitSet: pass

    def __or__(bs: BitSet) -> BitSet: pass

    def __xor__(bs: BitSet) -> BitSet: pass

    def __sub__(bs: BitSet) -> BitSet: pass

    def __iand__(bs: BitSet) -> BitSet: pass

    def __ior__(bs: BitSet) -> BitSet: pass

    def __ixor__(bs: BitSet) -> BitSet: pass

    def __isub__(bs: BitSet) -> BitSet: pass

    def __long__() -> int: pass

    def __ilshift__(num_bits: int) -> BitSet: pass

    def __lshift__(num_bits: int) -> BitSet: pass

    def __irshift__(num_bits: int) -> BitSet: pass

    def __rshift__(num_bits: int) -> BitSet: pass

    def __invert__() -> BitSet: pass

    def __eq__(bs: BitSet) -> bool: pass

    def __ne__(bs: BitSet) -> bool: pass

    def __lt__(bs: BitSet) -> bool: pass

    def __le__(bs: BitSet) -> bool: pass

    def __gt__(bs: BitSet) -> bool: pass

    def __ge__(bs: BitSet) -> bool: pass

    ##
    # \brief Returns the size of the bitset.
    # \return The size of the bitset.
    # 
    def __len__() -> int: pass

    def __nonzero__() -> bool: pass

    def __bool__() -> bool: pass

    ##
    # \brief Returns a string representation of the \c BitSet instance.
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
