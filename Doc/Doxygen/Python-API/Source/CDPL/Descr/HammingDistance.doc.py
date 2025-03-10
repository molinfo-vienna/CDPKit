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
# \brief Functor class for calculating the <em>Hamming Distance</em> [\ref WHAM, \ref CITB] between bitsets.
# 
class HammingDistance(Boost.Python.instance):

    ##
    # \brief Initializes the \e %HammingDistance instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %HammingDistance instance \a func.
    # \param func The \e %HammingDistance instance to copy.
    # 
    def __init__(func: HammingDistance) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %HammingDistance instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %HammingDistance instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %HammingDistance instance \a func.
    # \param func The \e %HammingDistance instance to copy.
    # \return \a self
    # 
    def assign(func: HammingDistance) -> HammingDistance: pass

    ##
    # \brief Calculates the <em>Hamming Distance</em> [\ref WHAM, \ref CITB] between the bitsets <em>bs1</em> and <em>bs2</em>.
    # 
    # The <em>Hamming Distance</em> \f$ D_{ab} \f$ is calculated by:
    # 
    # \[ D_{ab} = N_a + N_b \]
    # 
    # where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
    # 
    # If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
    # 
    # \param bs1 The first bitset.
    # \param bs2 The second bitset.
    # 
    # \return The calculated distance.
    # 
    def __call__(bs1: Util.BitSet, bs2: Util.BitSet) -> int: pass

    objectID = property(getObjectID)
