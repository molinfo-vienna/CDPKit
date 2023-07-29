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
    # \brief Initializes the \e %BronKerboschAlgorithm instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BronKerboschAlgorithm instance.
    # \param bka 
    # 
    def __init__(bka: BronKerboschAlgorithm) -> None: pass

    ##
    # \brief Initializes the \e %BronKerboschAlgorithm instance.
    # \param adj_mtx 
    # 
    def __init__(adj_mtx: BitSetArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %BronKerboschAlgorithm instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BronKerboschAlgorithm instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param adj_mtx 
    #
    def init(adj_mtx: BitSetArray) -> None: pass

    ##
    # \brief 
    # \param clique 
    # \return 
    #
    def nextClique(clique: BitSet) -> bool: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BronKerboschAlgorithm instance \a bka.
    # \param bka The \e %BronKerboschAlgorithm instance to copy.
    # \return \a self
    # 
    def assign(bka: BronKerboschAlgorithm) -> BronKerboschAlgorithm: pass

    objectID = property(getObjectID)
