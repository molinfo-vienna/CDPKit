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
# \brief Implementation of the Bron-Kerbosch clique-detection algorithm [\ref BKA].
# 
class BronKerboschAlgorithm(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>BronKerboschAlgorithm</tt> instance without an associated adjacency matrix.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>BronKerboschAlgorithm</tt> instance <em>bka</em>.
    # 
    # \param bka The <tt>BronKerboschAlgorithm</tt> instance to copy.
    # 
    def __init__(bka: BronKerboschAlgorithm) -> None: pass

    ##
    # \brief Constructs the <tt>BronKerboschAlgorithm</tt> instance and immediately initializes it with the adjacency matrix <em>adj_mtx</em>.
    # 
    # \param adj_mtx The graph adjacency matrix (one Util.BitSet per node).
    # 
    def __init__(adj_mtx: BitSetArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %BronKerboschAlgorithm instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %BronKerboschAlgorithm instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief (Re-)initializes the algorithm with the adjacency matrix <em>adj_mtx</em> and resets the clique iterator.
    # 
    # \param adj_mtx The graph adjacency matrix (one Util.BitSet per node).
    # 
    def init(adj_mtx: BitSetArray) -> None: pass

    ##
    # \brief Advances the clique iterator and writes the next maximal clique into <em>clique</em>.
    # 
    # \param clique The output clique (set of node indices).
    # 
    # \return <tt>True</tt> if a clique was emitted, and <tt>False</tt> when the iteration is exhausted.
    # 
    def nextClique(clique: BitSet) -> bool: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param bka The other <tt>BronKerboschAlgorithm</tt> instance.
    # 
    # \return \a self
    # 
    def assign(bka: BronKerboschAlgorithm) -> BronKerboschAlgorithm: pass

    objectID = property(getObjectID)
