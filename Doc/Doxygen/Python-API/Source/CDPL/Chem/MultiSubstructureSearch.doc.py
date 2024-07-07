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
# \brief MultiSubstructureSearch.
# 
# \since 1.2
# 
class MultiSubstructureSearch(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a <tt>MultiSubstructureSearch</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %MultiSubstructureSearch instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MultiSubstructureSearch instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def addSubstructure(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumSubstructures() -> int: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param target 
    # \return 
    #
    def matches(target: MolecularGraph) -> bool: pass

    ##
    # \brief 
    # \param expr 
    #
    def setup(expr: str = '') -> None: pass

    ##
    # \brief 
    # \param expr 
    # \param max_substr_id 
    # \return 
    #
    def validate(expr: str, max_substr_id: int) -> str: pass

    objectID = property(getObjectID)

    numSubstructures = property(getNumSubstructures)
