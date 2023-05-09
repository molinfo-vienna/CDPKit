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
class BondMatchExpression(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BondMatchExpression instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %BondMatchExpression instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondMatchExpression instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param query_bond 
    # \param query_molgraph 
    # \param target_bond 
    # \param target_molgraph 
    # \param aux_data 
    # \return 
    #
    def matches(query_bond: Bond, query_molgraph: MolecularGraph, target_bond: Bond, target_molgraph: MolecularGraph, aux_data: CDPL.Base.Variant) -> bool: pass

    ##
    # \brief 
    # \param query_bond 
    # \param query_molgraph 
    # \param target_bond 
    # \param target_molgraph 
    # \param mapping 
    # \param aux_data 
    # \return 
    #
    def mappingMatches(query_bond: Bond, query_molgraph: MolecularGraph, target_bond: Bond, target_molgraph: MolecularGraph, mapping: AtomBondMapping, aux_data: CDPL.Base.Variant) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def requiresAtomBondMapping() -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
