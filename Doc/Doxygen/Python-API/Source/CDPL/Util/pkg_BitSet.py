#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    # \param self The \e %BitSet instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BitSet instance.
    # \param self The \e %BitSet instance to initialize.
    # \param bs 
    #
    def __init__(self: object, bs: BitSet) -> None: pass

    ##
    # \brief Initializes the \e %BitSet instance.
    # \param self The \e %BitSet instance to initialize.
    # \param num_bits 
    # \param value 
    #
    def __init__(self: object, num_bits: int, value: int = 0) -> None: pass

    ##
    # \brief Initializes the \e %BitSet instance.
    # \param self The \e %BitSet instance to initialize.
    # \param bit_str 
    #
    def __init__(self: object, bit_str: str) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BitSet instance this method is called upon.
    #
    # Different Python \e %BitSet instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BitSet instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    #
    def swap(self: BitSet, bs: BitSet) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BitSet instance \a bs.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param num_bits 
    # \param value 
    #
    def resize(self: BitSet, num_bits: int, value: bool = False) -> None: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    #
    def clear(self: BitSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param value 
    #
    def append(self: BitSet, value: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def flip(self: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def flip(self: BitSet, idx: int) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def set(self: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \param value 
    # \return 
    #
    def set(self: BitSet, idx: int, value: bool = True) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def reset(self: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def reset(self: BitSet, idx: int) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def test(self: BitSet, idx: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def findFirst(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def findNext(self: BitSet, idx: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def isSubsetOf(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def isProperSubsetOf(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def isEmpty(self: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def getCount(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def getSize(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def getMaxSize(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def hasAny(self: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def hasNone(self: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: BitSet, idx: int) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param idx 
    # \param value 
    #
    def __setitem__(self: BitSet, idx: int, value: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def __and__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def __or__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def __xor__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief Returns the result of the subtraction operation <tt>self - bs</tt>.
    # \param self The \e %BitSet instance acting as minuend.
    # \param bs Specifies the subtrahend.
    # \return A \e %BitSet instance holding the result of the subtraction.
    #
    def __sub__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def __iand__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def __ior__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs 
    # \return 
    #
    def __ixor__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief Performs the in-place subtraction operation <tt>self -= bs</tt>.
    # \param self The \e %BitSet instance acting as in-place minuend.
    # \param bs Specifies the subtrahend.
    # \return The updated \e %BitSet instance \a self.
    #
    def __isub__(self: BitSet, bs: BitSet) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def __long__(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param num_bits 
    # \return 
    #
    def __ilshift__(self: BitSet, num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param num_bits 
    # \return 
    #
    def __lshift__(self: BitSet, num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param num_bits 
    # \return 
    #
    def __irshift__(self: BitSet, num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \param num_bits 
    # \return 
    #
    def __rshift__(self: BitSet, num_bits: int) -> BitSet: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def __invert__(self: BitSet) -> BitSet: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == bs</tt>.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != bs</tt>.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < bs</tt>.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= bs</tt>.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __le__(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > bs</tt>.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __gt__(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= bs</tt>.
    # \param self The \e %BitSet instance this method is called upon.
    # \param bs The \e %BitSet instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ge__(self: BitSet, bs: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def __len__(self: BitSet) -> int: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def __nonzero__(self: BitSet) -> bool: pass

    ##
    # \brief 
    # \param self The \e %BitSet instance this method is called upon.
    # \return 
    #
    def __bool__(self: BitSet) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %BitSet instance.
    # \param self The \e %BitSet instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: BitSet) -> str: pass

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
