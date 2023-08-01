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
# \brief CIPPriorityCalculator.
# 
# \see [\ref TCIP]
# 
class CIPPriorityCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>CIPPriorityCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>CIPPriorityCalculator</tt> instance and calculates the topological <em>CIP</em> priorities of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the <em>CIP</em> priorities.
    # \param priorities An array containing the calculated <em>CIP</em> priorities. The <em>CIP</em> priorities are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the <em>CIP</em> priority of an atom is accessible via its index).
    # 
    def __init__(molgraph: MolecularGraph, priorities: Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %CIPPriorityCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CIPPriorityCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setImplicitHydrogenCountFunction(func: SizeTypeAtomFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getImplicitHydrogenCountFunction() -> SizeTypeAtomFunctor: pass

    ##
    # \brief Calculates the topological <em>CIP</em> priorities of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to calculate the <em>CIP</em> priorities.
    # \param priorities An array containing the calculated <em>CIP</em> priorities. The <em>CIP</em> priorities are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the <em>CIP</em> priority of an atom is accessible via its index).
    # 
    def calculate(molgraph: MolecularGraph, priorities: Util.STArray) -> None: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    implHydrogenCountFunc = property(getImplHydrogenCountFunc, setImplHydrogenCountFunc)
